#pragma once

#include "folder.hpp"

namespace fs {

	class Partition final: public Folder {
	public:

		static Partition& getInstance() {
			static Partition instance{ "R1", 1000_KBytes };
			return instance;
		}

	private:
		Partition(const std::string& name, Capacity size) : Folder{ name , nullptr }, m_capacity{ size } {}
		~Partition() = default;
		const Capacity	m_capacity{};

	};

}