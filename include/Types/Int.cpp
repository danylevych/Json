#include "Int.h"

using namespace Core::Types;

Int::Int()
	: BaseType(JsonTypes::Int),
	value()
{	}

Int::Int(int value)
	: BaseType(JsonTypes::Int),
	value(value)
{	}

Int::Int(Int && other) noexcept
	: BaseType(JsonTypes::Int)
{
	this->operator=(other);
}

Int::Int(const Int& other)
	: BaseType(JsonTypes::Int)
{
	this->operator=(other);
}

Int& Int::operator=(Int&& other) noexcept
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;
}

Int& Int::operator=(const Int& other)
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;
}

Core::Types::Int::operator int& ()
{
	return value;
}

Core::Types::Int::operator const int& () const
{
	return value;
}

Int::operator int() const
{
	return value;
}

Core::Types::Int::operator Int() const
{
	return Int(value);
}

int& Int::Value()
{
	return this->value;
}

const int& Int::Value() const
{
	return this->value;
}