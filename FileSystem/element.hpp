#pragma once

#include "util.hpp"

namespace fs {
	class Element : NonCopyable {

	private:
		const class Folder* m_parent;
		const std::string	name;

		Element(const Element&) = delete;
		Element& operator= (const Element&) = delete;

	protected:

		Element(const std::string& name, const Folder* parent) : name{ name }, m_parent{ parent } {
			if (name.empty()) {
				throw std::domain_error::exception("Empty element name.");
			}
		}

		const Folder* getParent() const { return m_parent; }

		~Element() = default;
		friend std::default_delete<const Element>;

	public:
		Size		virtual getSize() const = 0;
		const std::string	getName() const { return this->name; }
		std::string const	getAbsoluteName() const;
	};
}