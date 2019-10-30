#include "folder.hpp"
#include "partition.hpp"

namespace fs {
	class File& Folder::createFile(const std::string& file_name, Size file_size) {
		checkNameAvailibility(file_name);

		Partition::getInstance().checkRemainingSize(file_size);

		invalidateSize();
		File* file{ new File(file_name, file_size, this) };

		this->m_elements[file_name] = file;

		return *file;
	}

	Folder& Folder::createFolder(const std::string& folder_name) {
		checkNameAvailibility(folder_name);
		invalidateSize();
		Folder* folder{ new Folder(folder_name, this) };

		this->m_elements[folder_name] = folder;
		return *folder;
	}

	void Folder::deleteElement(const std::string& element_name) {
		auto itorLb = this->m_elements.lower_bound(element_name);
		if (itorLb != end(this->m_elements) && !(this->m_elements.key_comp()(element_name, itorLb->first)))
		{
			delete itorLb->second;
			this->m_elements.erase(itorLb);
		}
		else {
			throw std::domain_error(element_name + " not found");
		}
	}

	Size	Folder::getSize() const {
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

}