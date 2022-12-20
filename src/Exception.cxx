#include "Exception.h"

Ngine::Exception::Exception(unsigned int line, std::string file) : line(line), file(file)
{
}

const char* Ngine::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << "Exception caught! \n"
		<< "[TYPE] " << GetType() << "\n"
		<< "[LINE] " << GetLine() << "\n"
		<< "[FILE] " << GetFile() << "\n";

	wBuffer = oss.str();
	return wBuffer.c_str();
}

const char* Ngine::Exception::GetType() const noexcept
{
	return "Ngine standard exception";
}

int Ngine::Exception::GetLine() const noexcept
{
	return line;
}

const char* Ngine::Exception::GetFile() const noexcept
{
	return file.c_str();
}
