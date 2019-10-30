#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <optional>
#include <functional>

using Size = unsigned;

Size operator"" _bytes(unsigned long long value) {return static_cast<Size>(value);}
Size operator"" _KBytes(unsigned long long value) {return static_cast<Size>(value * 1000);}

class NonCopyable {
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator= (const NonCopyable&) = delete;
protected:
	NonCopyable() = default;
};

class Element: NonCopyable {
	Element(const Element&) = delete;
	Element& operator= (const Element&) = delete;
protected:
	const std::string name;
	Element(const std::string& name, const Folder* parent) : name{ name }, m_parent{ parent } {
		if (name.empty()) {
			throw std::domain_error::exception("Empty element name.");
		}
	}
	const class Folder* m_parent;
public:
	Size		virtual getSize() const = 0;
};

class File : public Element {
private:
	Size		m_file_size;

public:
	File(const std::string& name, const Size size, const Folder* parent) : Element{ name, parent }, m_file_size{ size } {}

	Size		getSize() const override {
		return this->m_file_size;
	}
};

class Folder : public Element {
	Element::Element;

	void checkNameAvailibility(const std::string& element_name) {
		auto itorLb = this->m_elements.lower_bound(element_name);
		if (itorLb != end(this->m_elements) && !(this->m_elements.key_comp()(element_name, itorLb->first)))
		{
			throw std::domain_error(element_name + " already taken");
		}
	}

public:

	static Folder&		getRoot() {
		static Folder root{ "R1", nullptr };
		return root;
	}

	class File& createFile(const std::string& file_name, Size file_size) {
		checkNameAvailibility(file_name);
		File* file{ new File(file_name, file_size, this) };

		this->m_elements[file_name] = file;

		this->m_calculated_size.reset();

		return *file;
	}

	Folder& createFolder(const std::string& folder_name, Folder* parent) {
		checkNameAvailibility(folder_name);
		Folder* folder{ new Folder(folder_name, parent) };

		this->m_elements[folder_name] = folder;
		return *folder;
	}

	Size	getSize() const override {
		if (!this->m_calculated_size.has_value()) {
			Size result{};
			for (const auto& pair : this->m_elements) {
				result += pair.second->getSize();
			}
			this->m_calculated_size = result;
			return this->m_calculated_size.value();
		}
		return this->m_calculated_size.value();
	}

private:
	std::map<const std::string, const Element*>		m_elements;
	std::string										m_file_name;
	mutable std::optional<Size>						m_calculated_size;
};

int main()
{
	try {
		Folder& root{ Folder::getRoot() };
		root.createFile("F1", 899_bytes);
		Folder& r2{ root.createFolder("R2", &root) };
		r2.createFile("F2", 12_KBytes);
		std::cout << root.getSize() << std::endl;
	} catch (const std::domain_error::exception & e) {
		std::cout << e.what() << std::endl;
	}
}
