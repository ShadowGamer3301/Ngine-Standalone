#pragma once
#include <exception>
#include <sstream>
#include <string>

namespace Ngine
{
	class Exception : public std::exception
	{
	public:
		Exception(unsigned int line, std::string file);
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const char* GetFile() const noexcept;
	private:
		unsigned int line;
		std::string file;

	protected:
		mutable std::string wBuffer;
	};
}
