#include "BaseType.h"

Core::Types::BaseType::BaseType(JsonTypes&& type)
	: type(type)
{	}

Core::Types::BaseType::BaseType(const JsonTypes & type)
	: type(type)
{	}

bool Core::Types::BaseType::IsObject() const
{
	return type == Core::JsonTypes::Object;
}

bool Core::Types::BaseType::IsArray() const
{
	return type == Core::JsonTypes::Array;
}

bool Core::Types::BaseType::IsString() const
{
	return type == Core::JsonTypes::String;
}

bool Core::Types::BaseType::IsInt() const
{
	return type == Core::JsonTypes::Int;
}

bool Core::Types::BaseType::IsFloat() const
{
	return type == Core::JsonTypes::Float;
}

bool Core::Types::BaseType::IsBoolean() const
{
	return type == Core::JsonTypes::Boolean;
}

bool Core::Types::BaseType::IsNull() const
{
	return type == Core::JsonTypes::Null;
}
