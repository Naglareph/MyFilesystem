#pragma once

#include "folder.hpp"

namespace fs {

	class Partition final: public Folder {
	public:
		friend File& Folder::createFile(const std::string& file_name, Size file_size);

		static Partition& getInstance() {
			static Partition instance{ "R1", 1000_KBytes };
			return instance;
		}


	private:
		Partition(const std::string& name, Capacity size) : Folder{ name , nullptr }, m_capacity{ size } {}
		~Partition() = default;

		void checkRemainingSize(Size desired_size) const;

		const Capacity	m_capacity{};
	};

}