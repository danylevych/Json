#include "Object.h"

#include <sstream>

using namespace Core::Types;


Object::Object()
	: BaseType(Core::JsonTypes::Object),
	values()
{	}

Object::Object(Object&& other) noexcept
	: BaseType(Core::JsonTypes::Object)
{
	this->operator=(std::move(other));

#ifdef ORDER_KEY
	this->orderKey = std::move(other.orderKey);
#endif
}

Object::Object(const std::initializer_list<std::pair<const String, BaseType*>>& list)
	: BaseType(Core::JsonTypes::Object),
	values()
{
	for (const auto& item : list)
	{
		values.insert(std::make_pair(item.first, std::unique_ptr<BaseType>(item.second)));
#ifdef ORDER_KEY
		orderKey.push_back(item.first);
#endif
	}
}

Object& Object::operator=(Object&& other) noexcept
{
	if (this != &other)
	{
		this->values = std::move(other.values);

#ifdef ORDER_KEY
		this->orderKey = std::move(other.orderKey);
#endif
	}
	return *this;
}

ReturnedDataJson Object::operator[](const String& key)
{
#ifdef ORDER_KEY
	if (std::find(orderKey.begin(), orderKey.end(), key) == orderKey.end())
	{
		orderKey.push_back(key);
	}
#endif

	return ReturnedDataJson(values[key]);
}

const ReturnedDataJson Object::operator[](const String& key) const
{
	return ReturnedDataJson(values.at(key));
}

ReturnedDataJson Core::Types::Object::Get(const String& key, BaseType* def)
{
	try
	{
		return ReturnedDataJson(values.at(key));
	}
	catch (const std::out_of_range&)
	{
		return ReturnedDataJson(def);
	}
}

ReturnedDataJson Core::Types::Object::Get(const String& key, BaseType&& def)
{
	try
	{
		return ReturnedDataJson(values.at(key));
	}
	catch (const std::out_of_range&)
	{
		return ReturnedDataJson(def);
	}
}

ReturnedDataJson Core::Types::Object::Get(const String& key, BaseType& def)
{
	try
	{
		return ReturnedDataJson(values.at(key));
	}
	catch (const std::out_of_range&)
	{
		return ReturnedDataJson(def);
	}
}

const ReturnedDataJson Core::Types::Object::Get(const String& key, BaseType&& def) const
{
	try
	{
		return ReturnedDataJson(values.at(key));
	}
	catch (const std::out_of_range&)
	{
		return ReturnedDataJson(def);
	}
}

const ReturnedDataJson Core::Types::Object::Get(const String& key, BaseType& def) const
{
	try
	{
		return ReturnedDataJson(values.at(key));
	}
	catch (const std::out_of_range&)
	{
		return ReturnedDataJson(def);
	}
}

const ReturnedDataJson Core::Types::Object::Get(const String& key, BaseType* def) const
{
	try
	{
		return ReturnedDataJson(values.at(key));
	}
	catch (const std::out_of_range&)
	{
		return ReturnedDataJson(def);
	}
}

Core::Types::Object::operator std::string() const
{
	std::stringstream sout;
	sout << *this;
	return sout.str();
}

std::unordered_map<String, std::unique_ptr<BaseType>>& Object::Value()
{
	return values;
}

const std::unordered_map<String, std::unique_ptr<BaseType>>& Object::Value() const
{
	return values;
}

Core::Types::Object::iterator Core::Types::Object::Insert(const KeyValueT& pair)
{
	values[pair.first].reset(pair.second);

#ifdef ORDER_KEY
	orderKey.push_back(pair.first);
#endif

	return iterator(values.find(pair.first));
}

Core::Types::Object::iterator Core::Types::Object::Insert(KeyValueT&& pair)
{
	values[pair.first].reset(pair.second);

#ifdef ORDER_KEY
	orderKey.push_back(pair.first);
#endif

	return iterator(values.find(pair.first));
}

Core::Types::Object::iterator Core::Types::Object::Insert(KeyValueSmartT&& pair)
{
	values[pair.first] = std::move(pair.second);

#ifdef ORDER_KEY
	orderKey.push_back(pair.first);
#endif

	return iterator(values.find(pair.first));
}

Core::Types::Object::iterator Core::Types::Object::Insert(const KeyValueSmartT& pair)
{
	values[pair.first].reset(pair.second.get());

#ifdef ORDER_KEY
	orderKey.push_back(pair.first);
#endif

	return iterator(values.find(pair.first));
}

void Core::Types::Object::Insert(const std::initializer_list<KeyValueT>& list)
{
	for (auto& item : list)
	{
		values.insert(std::make_pair(item.first, std::unique_ptr<BaseType>(item.second)));

#ifdef ORDER_KEY
		orderKey.push_back(item.first);
#endif
	}
}

void Core::Types::Object::Insert(Object&& insertObj)
{
	for (auto& item : insertObj)
	{
		values.insert(std::make_pair(item.first, std::move(item.second)));

#ifdef ORDER_KEY
		orderKey.push_back(item.first);
#endif
	}
}

bool Core::Types::Object::Erase(const String& key)
{
#ifdef ORDER_KEY
	orderKey.erase(std::find(orderKey.begin(), orderKey.end(), key));
#endif

	return values.erase(key);
}

Core::Types::Object::iterator Core::Types::Object::Erase(const_iterator iter)
{
#ifdef ORDER_KEY
	orderKey.erase(std::find(orderKey.begin(), orderKey.end(), iter->first));
#endif

	return iterator(values.erase(iter.iter));
}

Core::Types::Object::iterator Core::Types::Object::Erase(const_iterator first, const_iterator last)
{
#ifdef ORDER_KEY
	orderKey.erase(std::find(orderKey.begin(), orderKey.end(), first->first), std::find(orderKey.rbegin(), orderKey.rend(), last->first).base());
#endif

	return iterator(values.erase(first.iter, last.iter));
}

std::ostream& Core::Types::operator<<(std::ostream& out, const Object& obj)
{
	out << "{";
#ifdef ORDER_KEY
	for (auto& key : obj.orderKey)
	{
		const Object::BaseSmartPtrT& value = obj.values.at(key);
		std::pair<const String&, const Object::BaseSmartPtrT&> item(key, value);
#else
	for (auto& item : obj.values)
	{
#endif
		out << item.first << ":";

		if (item.second->GetType() == Core::JsonTypes::Object)
		{
			Object* elem = dynamic_cast<Object*>(item.second.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item.second->GetType() == Core::JsonTypes::Array)
		{
			Array* elem = dynamic_cast<Array*>(item.second.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item.second->GetType() == Core::JsonTypes::String)
		{
			String* elem = dynamic_cast<String*>(item.second.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item.second->GetType() == Core::JsonTypes::Int)
		{
			Int* elem = dynamic_cast<Int*>(item.second.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item.second->GetType() == Core::JsonTypes::Float)
		{
			Float* elem = dynamic_cast<Float*>(item.second.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item.second->GetType() == Core::JsonTypes::Boolean)
		{
			Boolean* elem = dynamic_cast<Boolean*>(item.second.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}
		else if (item.second->GetType() == Core::JsonTypes::Null)
		{
			Null* elem = dynamic_cast<Null*>(item.second.get());
			if (elem != nullptr)
			{
				out << *elem;
			}
		}

		if (item.first == (--obj.values.cend())->first)
		{
			continue;
		}
		out << ",";
	}
	out << "}";
	return out;
}


// Iterators

Core::Types::Object::iterator::iterator(const Core::Types::Object::raw_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Object::iterator::iterator(Core::Types::Object::raw_iterator&& iter) noexcept
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Object::iterator::iterator(const Core::Types::Object::iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Object::iterator::iterator(Core::Types::Object::iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Object::iterator& Core::Types::Object::iterator::operator=(const iterator& other)
{
	if (this != &other)
	{
		this->iter = other.iter;
	}

	return *this;
}

Core::Types::Object::iterator& Core::Types::Object::iterator::operator=(iterator&& other) noexcept
{
	if (this != &other)
	{
		this->iter = std::move(other.iter);
	}

	return *this;
}

Core::Types::Object::KeyValueSmartT& Core::Types::Object::iterator::operator*()
{
	return *iter;
}

Core::Types::Object::KeyValueSmartT* Core::Types::Object::iterator::operator->()
{
	return iter.operator->();
}

const Core::Types::Object::KeyValueSmartT& Core::Types::Object::iterator::operator*() const
{
	return *iter;
}

const Core::Types::Object::KeyValueSmartT* Core::Types::Object::iterator::operator->() const
{
	return iter.operator->();
}

Core::Types::Object::iterator Core::Types::Object::iterator::operator++(int)
{
	iterator temp = *this;
	++this->iter;
	return temp;
}

Core::Types::Object::iterator& Core::Types::Object::iterator::operator++()
{
	++iter;
	return *this;
}

Core::Types::Object::iterator Core::Types::Object::iterator::operator--(int)
{
	iterator temp = *this;
	--this->iter;
	return temp;
}

Core::Types::Object::iterator& Core::Types::Object::iterator::operator--()
{
	--iter;
	return *this;
}

bool Core::Types::Object::iterator::operator!=(const iterator& other) const
{
	return this->iter != other.iter;
}

bool Core::Types::Object::iterator::operator==(const iterator& other) const
{
	return this->iter == other.iter;
}



Core::Types::Object::const_iterator::const_iterator(const Core::Types::Object::raw_const_iterator& iter)
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Object::const_iterator::const_iterator(Core::Types::Object::raw_const_iterator&& iter) noexcept
	: base_iterator(),
	iter(iter)
{	}

Core::Types::Object::const_iterator::const_iterator(const Core::Types::Object::iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Object::const_iterator::const_iterator(Core::Types::Object::iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Object::const_iterator::const_iterator(const Core::Types::Object::const_iterator& other)
	: base_iterator(),
	iter(other.iter)
{	}

Core::Types::Object::const_iterator::const_iterator(Core::Types::Object::const_iterator&& other) noexcept
	: base_iterator(),
	iter(std::move(other.iter))
{	}

Core::Types::Object::const_iterator& Core::Types::Object::const_iterator::operator=(const iterator& other)
{
	this->iter = other.iter;

	return *this;
}

Core::Types::Object::const_iterator& Core::Types::Object::const_iterator::operator=(iterator&& other) noexcept
{
	this->iter = other.iter;

	return *this;
}

Core::Types::Object::const_iterator& Core::Types::Object::const_iterator::operator=(const const_iterator& other)
{
	if (this != &other)
	{
		this->iter = other.iter;
	}

	return *this;
}

Core::Types::Object::const_iterator& Core::Types::Object::const_iterator::operator=(const_iterator&& other) noexcept
{
	if (this != &other)
	{
		this->iter = std::move(other.iter);
	}

	return *this;
}

const Core::Types::Object::KeyValueSmartT& Core::Types::Object::const_iterator::operator*() const
{
	return *iter;
}

const Core::Types::Object::KeyValueSmartT* Core::Types::Object::const_iterator::operator->() const
{
	return iter.operator->();
}

Core::Types::Object::const_iterator Core::Types::Object::const_iterator::operator++(int)
{
	iterator temp = *this;
	++this->iter;
	return temp;
}

Core::Types::Object::const_iterator& Core::Types::Object::const_iterator::operator++()
{
	++iter;
	return *this;
}

Core::Types::Object::const_iterator Core::Types::Object::const_iterator::operator--(int)
{
	iterator temp = *this;
	--this->iter;
	return temp;
}

Core::Types::Object::const_iterator& Core::Types::Object::const_iterator::operator--()
{
	--iter;
	return *this;
}

bool Core::Types::Object::const_iterator::operator!=(const const_iterator& other) const
{
	return this->iter != other.iter;
}

bool Core::Types::Object::const_iterator::operator==(const const_iterator& other) const
{
	return this->iter == other.iter;
}