#pragma once

#include "folder.hpp"

namespace fs {

	class Partition final: public Folder {
	public:
		friend File& Folder::createFile(const std::string& file_name, Size file_size);

		static Partition& getInstance() noexcept {
			static Partition instance{ "R1", 1000_KBytes };
			return instance;
		}


	private:
		Partition(const std::string& name, Capacity size) noexcept(false) : Folder{ name , nullptr }, m_capacity{ size } {}
		~Partition() = default;

		void checkRemainingSize(Size desired_size) const noexcept(false);

		const Capacity	m_capacity{};
	};

}