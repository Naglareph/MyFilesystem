#include <iostream>
#include <ostream>

class Ratio {
	int num{};
	int denum{};

public:
	Ratio(int i, int j) :
		num{ i },
		denum{ j } 
	{
	}

	Ratio& operator+= (const Ratio& r) { 
		this->num = (this->num * r.getDenum()) + (this->denum * r.getNum());
		this->denum = this->getDenum()* r.getDenum();
		return *this;
	}

	Ratio& operator-= (const Ratio& r) {
		this->num = (this->num * r.getDenum()) - (this->denum * r.getNum());
		this->denum = this->getDenum() * r.getDenum();
		return *this;
	}

	int getNum() const { return this->num; }
	int getDenum() const { return this->denum; }

	friend std::ostream&	operator<< (std::ostream& os, const Ratio r) {
		return os << r.getNum() << '/' << r.getDenum();
	}

};

Ratio	operator+ (const Ratio r1, const Ratio r2) {
	return Ratio{ r1 } += r2;
}

Ratio	operator- (const Ratio r1, const Ratio r2) {
	return Ratio{ r1 } -= r2;
}

int main()
{
	Ratio r1{ 3, 8 };
	Ratio r2{ 8, 5 };

	std::cout << "R1: " << r1 << std::endl; // 3/8
	std::cout << "R2: " << r2 << std::endl; // 8/5

	std::cout << "R1 + R2: " << r1 + r2 << std::endl; // member function
	std::cout << "R1 - R2: " << r1 - r2 << std::endl; // non member function

	std::cout << "R1 += R2: " << (r1 += r2) << std::endl;
	std::cout << "R1 -= R2: " << (r1 -= r2) << std::endl;
}
