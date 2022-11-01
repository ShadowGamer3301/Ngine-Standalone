#pragma once
#include <exception>
#include <sstream>
#include <iostream>

#include "Macro.hxx"

namespace Ngine {
	class NAPI Exception : std::exception {
	public:
		Exception(unsigned int line, std::string file, std::string desc) : line(line), file(file), desc(desc) {}
		const char* what() const noexcept override;
	private:
		unsigned int line;
		std::string file, desc;
		mutable std::string wBuffer;
	};
}