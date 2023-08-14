#include "Boolean.h"

using namespace Core::Types;

Boolean::Boolean()
	: BaseType(Core::JsonTypes::Boolean),
	value()
{	}

Boolean::Boolean(bool value)
	: BaseType(Core::JsonTypes::Boolean),
	value(value)
{	}

Boolean::Boolean(Boolean&& other) noexcept
	: BaseType(Core::JsonTypes::Boolean)
{
	this->operator=(other);
}

Boolean::Boolean(const Boolean& other)
	: BaseType(Core::JsonTypes::Boolean)
{
	this->operator=(other);
}

Boolean& Boolean::operator=(Boolean&& other) noexcept
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;
}

Boolean& Boolean::operator=(const Boolean& other)
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;
}

Core::Types::Boolean::operator bool&()
{
	return value;
}

Core::Types::Boolean::operator const bool&() const
{
	return value;
}

Boolean::operator bool() const
{
	return value;
}

Core::Types::Boolean::operator Boolean() const
{
	return Boolean(value);
}

bool& Boolean::Value()
{
	return this->value;
}

const bool& Boolean::Value() const
{
	return this->value;
}

std::ostream& Core::Types::operator<<(std::ostream& out, const Boolean& boolean)
{
	if (boolean.value)
	{
		return out << "true";
	}
	return out << "false";
}
