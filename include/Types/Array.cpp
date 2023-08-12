#include "Array.h"
#include <sstream>


using namespace Core::Types;

Array::Array()
	: BaseType(Core::JsonTypes::Array),
	values()
{   }

Array::Array(const std::initializer_list<BaseTypePtrT>& list)
	: BaseType(Core::JsonTypes::Array),
	values()
{
	for (auto& item : list)
	{
		values.push_back(std::move(BaseSmartPtrT(item)));
	}
}

Array::Array(Array&& other) noexcept
	: BaseType(Core::JsonTypes::Array)
{
	values = std::move(other.values);
}

Array& Array::operator=(Array&& other) noexcept
{
	if (this != &other)
	{
		values = std::move(other.values);
	}
	return *this;
}

Array& Array::operator=(const std::initializer_list<BaseTypePtrT>& list)
{
	values.clear();
	for (auto& item : list)
	{
		values.push_back(std::move(BaseSmartPtrT(item)));
	}

	return *this;
}

Core::Types::ReturnedDataJson Array::operator[](size_t index)
{
	{
		if (index < values.size())
		{
			return ReturnedDataJson(values[index]);
		}

		throw std::out_of_range("Index out of bounds.");
	}
}

const Core::Types::ReturnedDataJson Array::operator[](size_t index) const
{
	{
		if (index < values.size())
		{
			return ReturnedDataJson(values[index]);
		}

		throw std::out_of_range("Index out of bounds.");
	}
}

std::vector<Array::BaseSmartPtrT>& Array::Value()
{
	return values;
}

const std::vector<Array::BaseSmartPtrT>& Array::Value() const
{
	return values;
}

void Array::PushBack(Array::BaseSmartPtrT&& ptr)
{
	values.push_back(std::move(ptr));
}

Array::operator std::string() const
{
	std::stringstream sout;
	sout << *this;
	return sout.str();
}

void Array::PushBack(BaseTypePtrT ptr)
{
	values.push_back(std::move(Array::BaseSmartPtrT(ptr)));
}

std::ostream& Core::Types::operator<<(std::ostream& out, const Array& array)
{
	out << "[";
	for (auto& item : array.values)
	{
		if (item->GetType() == Core::JsonTypes::Object)
		{
			Object* elem = dynamic_cast<Object*>(item.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item->GetType() == Core::JsonTypes::Array)
		{
			Array* elem = dynamic_cast<Array*>(item.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item->GetType() == Core::JsonTypes::String)
		{
			String* elem = dynamic_cast<String*>(item.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item->GetType() == Core::JsonTypes::Int)
		{
			Int* elem = dynamic_cast<Int*>(item.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item->GetType() == Core::JsonTypes::Float)
		{
			Float* elem = dynamic_cast<Float*>(item.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item->GetType() == Core::JsonTypes::Boolean)
		{
			Boolean* elem = dynamic_cast<Boolean*>(item.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item->GetType() == Core::JsonTypes::Null)
		{
			Null* elem = dynamic_cast<Null*>(item.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}

		if (item == array.values[array.values.size() - 1])
		{
			continue;
		}
		out << ",";
	}
	out << "]";
	return out;
}



/*
--------------------------- ITERATORS ---------------------------
*/

Core::Types::Array::iterator::iterator()
	: base_iterator(),
	iter()
{	}

Core::Types::Array::iterator::iterator(const raw_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::iterator::iterator(raw_iterator&& iter) noexcept
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::iterator::iterator(const iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Array::iterator::iterator(iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Array::iterator& Core::Types::Array::iterator::operator=(const iterator& other)
{
	if (this != &other)
	{
		this->iter = other.iter;
	}

	return *this;
}

Core::Types::Array::iterator& Core::Types::Array::iterator::operator=(iterator&& other) noexcept
{
	if (this != &other)
	{
		this->iter = std::move(other.iter);
	}

	return *this;
}

BaseType& Core::Types::Array::iterator::operator*()
{
	return *(iter->get());
}

BaseType* Core::Types::Array::iterator::operator->()
{
	return iter->get();
}

const BaseType& Core::Types::Array::iterator::operator*() const
{
	return *(iter->get());
}

const BaseType* Core::Types::Array::iterator::operator->() const
{
	return iter->get();
}

Core::Types::Array::iterator Core::Types::Array::iterator::operator++(int)
{
	iterator temp = *this;
	++this->iter;
	return temp;
}

Core::Types::Array::iterator& Core::Types::Array::iterator::operator++()
{
	++iter;
	return *this;
}

Core::Types::Array::iterator Core::Types::Array::iterator::operator--(int)
{
	iterator temp = *this;
	--this->iter;
	return temp;
}

Core::Types::Array::iterator& Core::Types::Array::iterator::operator--()
{
	--iter;
	return *this;
}

bool Core::Types::Array::iterator::operator!=(const iterator& other) const
{
	return this->iter != other.iter;
}

bool Core::Types::Array::iterator::operator==(const iterator& other) const
{
	return this->iter == other.iter;
}



Core::Types::Array::const_iterator::const_iterator()
	: base_iterator(),
	iter()
{	}

Core::Types::Array::const_iterator::const_iterator(const raw_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::const_iterator::const_iterator(raw_iterator&& iter) noexcept
	: base_iterator(),
	iter(std::move(iter))
{	}

Core::Types::Array::const_iterator::const_iterator(const raw_const_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::const_iterator::const_iterator(raw_const_iterator&& iter) noexcept
	: base_iterator(),
	iter(std::move(iter))
{	}

Core::Types::Array::const_iterator::const_iterator(const iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Array::const_iterator::const_iterator(iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Array::const_iterator::const_iterator(const const_iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Array::const_iterator::const_iterator(const_iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Array::const_iterator& Core::Types::Array::const_iterator::operator=(const iterator& other)
{
	this->iter = other.iter;
	return *this;
}

Core::Types::Array::const_iterator& Core::Types::Array::const_iterator::operator=(iterator&& other) noexcept
{
	this->iter = std::move(other.iter);
	return *this;
}

Core::Types::Array::const_iterator& Core::Types::Array::const_iterator::operator=(const const_iterator& other)
{
	if (this != &other)
	{
		this->iter = other.iter;
	}

	return *this;
}

Core::Types::Array::const_iterator& Core::Types::Array::const_iterator::operator=(const_iterator&& other) noexcept
{
	if (this != &other)
	{
		this->iter = std::move(other.iter);
	}

	return *this;
}

const BaseType& Core::Types::Array::const_iterator::operator*() const
{
	return *(iter->get());
}

const BaseType* Core::Types::Array::const_iterator::operator->() const
{
	return iter->get();
}

Core::Types::Array::const_iterator Core::Types::Array::const_iterator::operator++(int)
{
	const_iterator temp = *this;
	++this->iter;
	return temp;
}

Core::Types::Array::const_iterator& Core::Types::Array::const_iterator::operator++()
{
	++iter;
	return *this;
}

Core::Types::Array::const_iterator Core::Types::Array::const_iterator::operator--(int)
{
	const_iterator temp = *this;
	--this->iter;
	return temp;
}

Core::Types::Array::const_iterator& Core::Types::Array::const_iterator::operator--()
{
	--iter;
	return *this;
}

bool Core::Types::Array::const_iterator::operator!=(const const_iterator& other) const
{
	return this->iter != other.iter;
}

bool Core::Types::Array::const_iterator::operator==(const const_iterator& other) const
{
	return this->iter == other.iter;
}



Core::Types::Array::reverse_iterator::reverse_iterator()
	: base_iterator(),
	iter()
{	}

Core::Types::Array::reverse_iterator::reverse_iterator(const raw_reverse_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::reverse_iterator::reverse_iterator(raw_reverse_iterator&& iter) noexcept
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::reverse_iterator::reverse_iterator(const reverse_iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Array::reverse_iterator::reverse_iterator(reverse_iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Array::reverse_iterator& Core::Types::Array::reverse_iterator::operator=(const reverse_iterator& other)
{
	if (this != &other)
	{
		this->iter = other.iter;
	}

	return *this;
}

Core::Types::Array::reverse_iterator& Core::Types::Array::reverse_iterator::operator=(reverse_iterator&& other) noexcept
{
	if (this != &other)
	{
		this->iter = std::move(other.iter);
	}

	return *this;
}

BaseType& Core::Types::Array::reverse_iterator::operator*()
{
	return *(iter->get());
}

BaseType* Core::Types::Array::reverse_iterator::operator->()
{
	return iter->get();
}

const BaseType& Core::Types::Array::reverse_iterator::operator*() const
{
	return *(iter->get());
}

const BaseType* Core::Types::Array::reverse_iterator::operator->() const
{
	return iter->get();
}

Core::Types::Array::reverse_iterator Core::Types::Array::reverse_iterator::operator++(int)
{
	reverse_iterator temp = *this;
	++this->iter;
	return temp;
}

Core::Types::Array::reverse_iterator& Core::Types::Array::reverse_iterator::operator++()
{
	++iter;
	return *this;
}

Core::Types::Array::reverse_iterator Core::Types::Array::reverse_iterator::operator--(int)
{
	reverse_iterator temp = *this;
	--this->iter;
	return temp;
}

Core::Types::Array::reverse_iterator& Core::Types::Array::reverse_iterator::operator--()
{
	--iter;
	return *this;
}

bool Core::Types::Array::reverse_iterator::operator!=(const reverse_iterator& other) const
{
	return this->iter != other.iter;
}

bool Core::Types::Array::reverse_iterator::operator==(const reverse_iterator& other) const
{
	return this->iter == other.iter;
}



Core::Types::Array::const_reverse_iterator::const_reverse_iterator()
	: base_iterator(),
	iter()
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(const raw_reverse_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(raw_reverse_iterator&& iter) noexcept
	: base_iterator(),
	iter(std::move(iter))
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(const raw_const_reverse_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(raw_const_reverse_iterator&& iter) noexcept
	: base_iterator(),
	iter(std::move(iter))
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(const reverse_iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(reverse_iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Array::const_reverse_iterator::const_reverse_iterator(const_reverse_iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Array::const_reverse_iterator& Core::Types::Array::const_reverse_iterator::operator=(const reverse_iterator& other)
{
	this->iter = other.iter;
	return *this;
}

Core::Types::Array::const_reverse_iterator& Core::Types::Array::const_reverse_iterator::operator=(reverse_iterator&& other) noexcept
{
	this->iter = std::move(other.iter);
	return *this;
}

Core::Types::Array::const_reverse_iterator& Core::Types::Array::const_reverse_iterator::operator=(const const_reverse_iterator& other)
{
	if (this != &other)
	{
		this->iter = other.iter;
	}

	return *this;
}

Core::Types::Array::const_reverse_iterator& Core::Types::Array::const_reverse_iterator::operator=(const_reverse_iterator&& other) noexcept
{
	if (this != &other)
	{
		this->iter = std::move(other.iter);
	}

	return *this;
}

const BaseType& Core::Types::Array::const_reverse_iterator::operator*() const
{
	return *(iter->get());
}

const BaseType* Core::Types::Array::const_reverse_iterator::operator->() const
{
	return iter->get();
}

Core::Types::Array::const_reverse_iterator Core::Types::Array::const_reverse_iterator::operator++(int)
{
	const_reverse_iterator temp = *this;
	++this->iter;
	return temp;
}

Core::Types::Array::const_reverse_iterator& Core::Types::Array::const_reverse_iterator::operator++()
{
	++iter;
	return *this;
}

Core::Types::Array::const_reverse_iterator Core::Types::Array::const_reverse_iterator::operator--(int)
{
	const_reverse_iterator temp = *this;
	--this->iter;
	return temp;
}

Core::Types::Array::const_reverse_iterator& Core::Types::Array::const_reverse_iterator::operator--()
{
	--iter;
	return *this;
}

bool Core::Types::Array::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const
{
	return this->iter != other.iter;
}

bool Core::Types::Array::const_reverse_iterator::operator==(const const_reverse_iterator& other) const
{
	return this->iter == other.iter;
}