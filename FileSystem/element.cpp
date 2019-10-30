#include "folder.hpp"

namespace fs {

	std::string const Element::getAbsoluteName() const {
		if (getParent() != nullptr) {
			return '/' + getParent()->getAbsoluteName() + '/' + this->getName();
		}
		return this->getName();
	}
}
