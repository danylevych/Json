#include "Json.h"
#include <codecvt>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace Core;


Core::Json::BasePtrT Core::Json::Load(std::fstream& file)
{
	Core::Json::BasePtrT basePtr = nullptr;

	std::wstring jsonStr;
	if (file.is_open())
	{
		std::string jsonStrTemp;
		std::copy_if(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(),
			std::back_inserter<std::string>(jsonStrTemp), [](char ch) {
				static bool isKey = false;
				if (ch == '"')
				{
					isKey = isKey ? false : true;
				}

				if (ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r' || isKey)
				{
					return true;
				}
				return false;
			});

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		jsonStr = converter.from_bytes(jsonStrTemp);
	}
	else
	{
		throw std::exception("Coudnt open the file.");
	}

	if (!jsonStr.empty())
	{
		if (jsonStr[0] == '{')  // Means that file has stored the Core::Object.
		{
			Core::Types::Object* objPtr = new Core::Types::Object{};
			ReadObject(objPtr, jsonStr);
			basePtr = (objPtr);
		}
		else if (jsonStr[0] == '[')  // The file has stored the Core::Array
		{
			Core::Types::Array* arrPtr = new Core::Types::Array{};
			ReadArray(arrPtr, jsonStr);
			basePtr = (arrPtr);
		}
		else
		{
			throw std::exception{ "The format of file maybe incorrect" };
		}
	}

	return basePtr;
}

std::string Core::Json::Dump(const BasePtrT jsonObj, size_t ident)
{
	if (jsonObj == nullptr)
	{
		return std::string();
	}
	
	std::string jsonString;
	
	if (jsonObj->IsArray())
	{
		if (ident == 0)
		{
			return static_cast<std::string>(dynamic_cast<Types::Array&>(*jsonObj));
		}

		return DumpArray(dynamic_cast<Types::Array*>(jsonObj), ident, 1);
	}
	else if (jsonObj->IsObject())
	{
		if (ident == 0)
		{
			return static_cast<std::string>(dynamic_cast<Types::Object&>(*jsonObj));
		}

		return DumpObject(dynamic_cast<Types::Object*>(jsonObj), ident, 1);
	}
	else
	{
		throw std::runtime_error("The jsonObj has incorect structere.\nIn: " + std::string(__func__));
	}
}

void Core::Json::ReadArray(Types::Array* arrPtr, std::wstring& jsonStr)
{
	size_t endIndex = GetCloseBracketIndex(jsonStr, 0, L'[', L']');
	if (endIndex != std::wstring::npos)
	{
		std::wstring arrayPart = jsonStr.substr(1, endIndex + 1);

		for (size_t i = 0; i < arrayPart.size(); i++)
		{
			if (i != arrayPart.size() - 1)
			{
				size_t endIndex;
				if (arrayPart[i] == L'{')
				{
					endIndex = GetCloseBracketIndex(arrayPart, i + 1) + 1;
				}
				else if (arrayPart[i] == L'[')
				{
					endIndex = GetCloseBracketIndex(arrayPart, i + 1, L'[', L']') + 1;
				}
				else
				{
					endIndex = arrayPart.find_first_of(L",]", i);
				}

				std::wstring valueStr = arrayPart.substr(i, endIndex - i);
				i = endIndex;

				if (!valueStr.empty())
				{
					if (valueStr[0] == L'"')
					{
						arrPtr->PushBack(new Core::Types::String(valueStr.substr(1, valueStr.size() - 2)));  // We have 2 "
					}
					else if (valueStr == L"true" || valueStr == L"false")
					{
						arrPtr->PushBack(new Core::Types::Boolean(valueStr == L"true" ? true : false));
					}
					else if (valueStr == L"null")
					{
						arrPtr->PushBack(new Core::Types::Null());
					}
					else if (std::isdigit(valueStr[0]))
					{
						if (valueStr.find('.') != std::wstring::npos)
						{
							arrPtr->PushBack(new Core::Types::Float(std::stod(valueStr)));
						}
						else
						{
							arrPtr->PushBack(new Core::Types::Int(std::stoi(valueStr)));
						}
					}
					else if (valueStr[0] == L'{')
					{
						Core::Types::Object* otherObjPtr = new Core::Types::Object{};
						ReadObject(otherObjPtr, valueStr);
						arrPtr->PushBack(otherObjPtr);
					}
					else if (valueStr[0] == L'[')
					{
						Core::Types::Array* otherArrPtr = new Core::Types::Array{};
						ReadArray(otherArrPtr, valueStr);
						arrPtr->PushBack(otherArrPtr);
					}
				}
			}
		}
	}
}

void Core::Json::ReadObject(Types::Object* objPtr, std::wstring& jsonStr)
{
	size_t endIndex = GetCloseBracketIndex(jsonStr);
	if (endIndex != std::wstring::npos)
	{
		std::wstring objectPart = jsonStr.substr(1, endIndex + 1);

		for (size_t i = 0; i < objectPart.size(); i++)
		{
			if (objectPart[i] == L'"' && i != objectPart.size() - 1)
			{
				Core::Types::String key{ objectPart.substr(i + 1, objectPart.find(L'"', i + 1) - i - 1) };

				size_t startValueIndex = objectPart.find(L':', i) + 1;
				size_t endValueIndex;
				if (objectPart[startValueIndex] == L'{')
				{
					endValueIndex = GetCloseBracketIndex(objectPart, startValueIndex) + 1;
				}
				else if (objectPart[startValueIndex] == L'[')
				{
					endValueIndex = GetCloseBracketIndex(objectPart, startValueIndex, L'[', L']') + 1;
				}
				else
				{
					endValueIndex = objectPart.find_first_of(L",}", startValueIndex - 1);
				}

				std::wstring valueStr = objectPart.substr(startValueIndex, endValueIndex - startValueIndex);

				i = endValueIndex;  // Move to next key value pair.

				if (!valueStr.empty())
				{
					if (valueStr[0] == L'"')
					{
						(*objPtr)[key] = new Core::Types::String(valueStr.substr(1, valueStr.size() - 2));  // We have 2 "
					}
					else if (valueStr == L"true" || valueStr == L"false")
					{
						(*objPtr)[key] = new Core::Types::Boolean(valueStr == L"true" ? true : false);
					}
					else if (valueStr == L"null")
					{
						(*objPtr)[key] = new Core::Types::Null();
					}
					else if (std::isdigit(valueStr[0]))
					{
						if (valueStr.find(L'.') != std::wstring::npos)
						{
							(*objPtr)[key] = new Core::Types::Float(std::stod(valueStr));
						}
						else
						{
							(*objPtr)[key] = new Core::Types::Int(std::stoi(valueStr));
						}
					}
					else if (valueStr[0] == '{')
					{
						Core::Types::Object* otherObjPtr = new Core::Types::Object{};
						ReadObject(otherObjPtr, valueStr);
						(*objPtr)[key] = otherObjPtr;
					}
					else if (valueStr[0] == '[')
					{
						Core::Types::Array* arrPtr = new Core::Types::Array{};
						ReadArray(arrPtr, valueStr);
						(*objPtr)[key] = arrPtr;
					}
				}
			}
		}
	}
}

size_t Core::Json::GetCloseBracketIndex(std::wstring& jsonStr, size_t start, wchar_t open, wchar_t close)
{
	size_t countOfOpen = 1;
	for (size_t i = start + 1; i < jsonStr.size(); i++)
	{
		if (jsonStr[i] == open)
		{
			countOfOpen++;
		}
		else if (jsonStr[i] == close)
		{
			countOfOpen--;
			if (countOfOpen == 0)
			{
				return i;
			}
		}
	}

	return std::wstring::npos;
}

std::string Core::Json::DumpArray(Types::Array* arrPtr, size_t ident, int add, bool firstCall)
{
	if (arrPtr->Empty())
	{
		return "[]";
	}

	std::stringstream result;
	result << "[";
	for (auto& item : *arrPtr)
	{
		result << "\n" + std::string(ident * add, ' ');

		if (item.IsInt())
		{
			Types::Int& value = dynamic_cast<Types::Int&>(item);
			result << value;
		}
		else if(item.IsFloat())
		{
			Types::Float& value = dynamic_cast<Types::Float&>(item);
			result << value;
		}
		else if (item.IsNull())
		{
			Types::Null& value = dynamic_cast<Types::Null&>(item);
			result << value;
		}
		else if (item.IsBoolean())
		{
			Types::Boolean& value = dynamic_cast<Types::Boolean&>(item);
			result << value;
		}
		else if (item.IsString())
		{
			Types::String& value = dynamic_cast<Types::String&>(item);
			result << value;
		}
		else if (item.IsArray())
		{
			result << DumpArray(dynamic_cast<Types::Array*>(&item), ident, add + 1, false);
		}
		else if (item.IsObject())
		{
			result << DumpObject(dynamic_cast<Types::Object*>(&item), ident, add + 1, false);
		}

		if (&item != arrPtr->Back().get())
		{
			result << ",";
		}
		else
		{
			result << "\n";
		}
	}

	if (firstCall)
	{
		result << "]";
	}
	else
	{
		result << std::string(ident * (add - 1), ' ') + "]";
	}

	return result.str();
}


std::string Core::Json::DumpObject(Types::Object* objPtr, size_t ident, int add, bool firstCall)
{
	if (objPtr->Empty())
	{
		return "{}";
	}
	
	std::stringstream result;
	result << "{";

#if ORDER_KEY
	for (auto& key : objPtr->GetKeyOrder())
	{
		auto item = objPtr->Find(key);
#else
	for (auto item = objPtr->begin(), end = objPtr->end(); item != end; ++item)
	{
#endif
		result << "\n" + std::string(ident * add, ' ');

		if (item->second->IsInt())
		{
			Types::Int& value = item;
			result << item->first << ": " << value;
		}
		else if (item->second->IsFloat())
		{
			Types::Float& value = item;
			result << item->first << ": " << value;
		}
		else if (item->second->IsNull())
		{
			Types::Null& value = item;
			result << item->first << ": " << value;
		}
		else if (item->second->IsBoolean())
		{
			Types::Boolean& value = item;
			result << item->first << ": " << value;
		}
		else if (item->second->IsString())
		{
			Types::String& value = item;
			result << item->first << ": " << value;
		}
		else if (item->second->IsArray())
		{
			result << DumpArray(dynamic_cast<Types::Array*>(item->second.get()), ident, add + 1, false);
		}
		else if (item->second->IsObject())
		{
			result << item->first << ": ";
			result << DumpObject(dynamic_cast<Types::Object*>(item->second.get()), ident, add + 1, false);
		}

		if (item != --objPtr->end())
		{
			result << ",";
		}
		else
		{
			result << "\n";
		}
	}

	if (firstCall)
	{
		result << "}";
	}
	else
	{
		result << std::string(ident * (add - 1), ' ') + "}";
	}

	return result.str();
}