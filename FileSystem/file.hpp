#pragma once

#include "element.hpp"

namespace fs {
	class File : public Element {
	private:
		Size		m_file_size;
		File(const std::string& name, const Size size, const Folder* parent) : Element{ name, parent }, m_file_size{ size } {}

	public:

		Size		getSize() const override {
			return this->m_file_size;
		}

		friend class Folder;
	};
}