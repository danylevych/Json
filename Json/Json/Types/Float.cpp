#include "Float.h"

using namespace Core::Types;

Float::Float()
	: BaseType(Core::JsonTypes::Float),
	value()
{	}

Float::Float(double value)
	: BaseType(Core::JsonTypes::Float),
	value(value)
{	}

Float::Float(Float && other) noexcept
	: BaseType(Core::JsonTypes::Float)
{
	this->operator=(other);
}

Float::Float(const Float& other)
	: BaseType(Core::JsonTypes::Float)
{
	this->operator=(other);
}

Float& Float::operator=(Float&& other) noexcept
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;
}

Float& Float::operator=(const Float& other)
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;
}

Core::Types::Float::operator double&()
{
	return value;
}

Core::Types::Float::operator const double&() const
{
	return value;
}

Float::operator double() const
{
	return value;
}

Core::Types::Float::operator Float() const
{
	return Float(value);
}

double& Core::Types::Float::Value()
{
	return value;
}

const double& Core::Types::Float::Value() const
{
	return value;
}