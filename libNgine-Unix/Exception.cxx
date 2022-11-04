#include "Exception.hxx"

const char* Ngine::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << "Exception Caught!" << std::endl
		<< "File: " << file << std::endl
		<< "Line: " << line << std::endl
		<< "Description: " << desc << std::endl;

	wBuffer = oss.str();

	return wBuffer.c_str();
}
