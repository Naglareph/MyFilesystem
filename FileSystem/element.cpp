#include "folder.hpp"

namespace fs {

	std::string const Element::getAbsoluteName() const noexcept {
		if (getParent() != nullptr) {
			return '/' + getParent()->getAbsoluteName() + '/' + this->getName();
		}
		return this->getName();
	}
}
