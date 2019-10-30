#pragma once
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <optional>
#include <functional>

namespace fs {

	using Size = unsigned;

	inline Size operator"" _bytes(unsigned long long value) { return static_cast<Size>(value); }
	inline Size operator"" _KBytes(unsigned long long value) { return static_cast<Size>(value * 1000); }

	class NonCopyable {
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator= (const NonCopyable&) = delete;
	protected:
		NonCopyable() = default;
	};
}