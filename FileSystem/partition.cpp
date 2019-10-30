#include "partition.hpp"

namespace fs {
	
	void Partition::checkRemainingSize(Size desired_size) {
		if (this->m_capacity - getSize() < desired_size) {
			throw std::domain_error("Capacity overflow");
		}
	}
}
