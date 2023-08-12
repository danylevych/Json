#include "Null.h"
#include <iostream>

using namespace Core::Types;

Null::Null()
	: BaseType(JsonTypes::Null),
	value(nullptr)
{	}

Null::operator std::string() const
{
	return std::string("null");
}

Core::Types::Null::operator bool() const
{
	return false;
}

const std::nullptr_t& Null::Value() const
{
	return value;
}

std::ostream& Core::Types::operator<<(std::ostream& out, const Null& null)
{
	return out << "null";
}
