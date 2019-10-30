#include "partition.hpp"

using namespace fs;

int main()
{
	try {
		Folder& root{ Partition::getInstance() };
		root.createFile("F1", Size{ 899_bytes });
		Folder& r2{ root.createFolder("R2") };
		r2.createFile("F2", Size{ 12_KBytes });
		std::cout << root.getSize() << "\n";
		std::cout << r2.getAbsoluteName() << "\n";
	} catch (const std::domain_error::exception & e) {
		std::cout << e.what() << "\n";
	}
}
