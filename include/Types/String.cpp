#include "String.h"

using namespace Core::Types;

String::String()
	: BaseType(Core::JsonTypes::String),
	value()
{	}

String::String(const char* value)
	: BaseType(Core::JsonTypes::String)
{
	std::string tempVal{ value };
	this->value = ToWString(tempVal);
}

String::String(std::string&& value)
	: BaseType(Core::JsonTypes::String)
{	
	std::string tempVal{ value };
	this->value = ToWString(tempVal);
}

String::String(const std::string& value)
	: BaseType(Core::JsonTypes::String)
{	
	this->value = ToWString(value);
}

String::String(std::wstring && value)
	: BaseType(Core::JsonTypes::String),
	value(value)
{	}

String::String(const std::wstring& value)
	: BaseType(Core::JsonTypes::String),
	value(value)
{	}

String::String(String && other) noexcept
	: BaseType(Core::JsonTypes::String)
{
	this->operator=(other);
}

String::String(const String& other)
	: BaseType(Core::JsonTypes::String)
{
	this->operator=(other);
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		value = other.value;
	}
	return *this;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		value = other.value;
	}
	return *this;
}

Core::Types::String::operator std::wstring&()
{
	return value;
}

Core::Types::String::operator const std::wstring&() const
{
	return value;
}

String::operator std::string() const
{
	std::wstring tempVal = value;
	return ToString(tempVal);
}

std::wstring& String::Value()
{
	return value;
}

const std::wstring& String::Value() const
{
	return value;
}

std::string Core::Types::String::ToString(const std::wstring& str) const
{
	return converter.to_bytes(str);
}

std::wstring Core::Types::String::ToWString(const std::string& str) const
{
	return converter.from_bytes(str);
}

bool String::operator<(const String& other) const
{
	return value < other.value;
}

bool String::operator>(const String& other) const
{
	return value > other.value;
}

bool String::operator==(const String& other) const
{
	return value == other.value;
}

bool String::operator!=(const String& other) const
{
	return value != other.value;
}

std::ostream& Core::Types::operator<<(std::ostream& out, const String& str)
{
	out << "\"";
	out << str.ToString(str.value);
	out << "\"";
	return out;
}