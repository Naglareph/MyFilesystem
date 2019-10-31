#pragma once

#include "file.hpp"

namespace fs {
	class Folder : public Element {

	private:
		std::map<const std::string, std::unique_ptr<const Element>>	m_elements;
		std::string													m_file_name;
		mutable std::optional<Size>									m_calculated_size;

		void checkNameAvailibility(const std::string& element_name) const noexcept(false) {
			auto itorLb = this->m_elements.lower_bound(element_name);
			if (itorLb != end(this->m_elements) && !(this->m_elements.key_comp()(element_name, itorLb->first)))
			{
				throw std::domain_error(element_name + " already taken");
			}
		}

		void invalidateSize() const noexcept {
			this->m_calculated_size.reset();
			if (getParent() != nullptr) {
				getParent()->invalidateSize();
			}
		}

	protected:
		Element::Element;
		~Folder() = default;

	public:

		class File& createFile(const std::string& file_name, Size file_size) noexcept(false);
		Folder&		createFolder(const std::string& folder_name) noexcept(false);
		void		deleteElement(const std::string& element_name) noexcept(false);
		Size		getSize() const noexcept override;
	};
}