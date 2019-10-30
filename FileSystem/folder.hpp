#pragma once

#include "file.hpp"

namespace fs {
	class Folder : public Element {

	private:
		std::map<const std::string, const Element*>		m_elements;
		std::string										m_file_name;
		mutable std::optional<Size>						m_calculated_size;
		Element::Element;

		void checkNameAvailibility(const std::string& element_name) {
			auto itorLb = this->m_elements.lower_bound(element_name);
			if (itorLb != end(this->m_elements) && !(this->m_elements.key_comp()(element_name, itorLb->first)))
			{
				throw std::domain_error(element_name + " already taken");
			}
		}

		void invalidateSize() const {
			this->m_calculated_size.reset();
			if (getParent() != nullptr) {
				getParent()->invalidateSize();
			}
		}

	public:

		static Folder& getRoot() {
			static Folder root{ "R1", nullptr };
			return root;
		}

		class File& createFile(const std::string& file_name, Size file_size) {
			checkNameAvailibility(file_name);
			invalidateSize();
			File* file{ new File(file_name, file_size, this) };

			this->m_elements[file_name] = file;

			return *file;
		}

		Folder& createFolder(const std::string& folder_name) {
			checkNameAvailibility(folder_name);
			invalidateSize();
			Folder* folder{ new Folder(folder_name, this) };

			this->m_elements[folder_name] = folder;
			return *folder;
		}

		Size	getSize() const override {
			if (!this->m_calculated_size.has_value()) {
				Size result{};
				for (const auto& pair : this->m_elements) {
					result += pair.second->getSize();
				}
				this->m_calculated_size = result;
				return this->m_calculated_size.value();
			}
			return this->m_calculated_size.value();
		}
	};
}