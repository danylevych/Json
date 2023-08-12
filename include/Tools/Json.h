#pragma once

//#ifdef USE_ORDERED_KEY
//#define ORDER_KEY
//#endif

#include <memory>
#include <string>
#include <fstream>

#include "BaseType.h"
#include "../Types/Object.h"
#include "../Types/Array.h"


namespace Core 
{
	class Json
	{
	public:
		using BasePtrT = Types::BaseType*;
		using BaseSmartPtrT = std::unique_ptr<Types::BaseType>;
		template<typename T>
		using SmartPtrT = std::unique_ptr<T>;

	public: 
		static BasePtrT Load(std::fstream& file);
		static std::string Dump(const BasePtrT jsonObj, size_t ident = 0);

	private:
		static void ReadArray(Types::Array* arrPtr, std::wstring& jsonStr);
		static void ReadObject(Types::Object* objPtr, std::wstring& jsonStr);
		
		static std::string DumpArray(Types::Array* arrPtr, size_t ident, int add = 0, bool firstCall = true);
		static std::string DumpObject(Types::Object* objPtr, size_t ident, int add = 0, bool firstCall = true);

		static size_t GetCloseBracketIndex(std::wstring& jsonStr, size_t start = 0, wchar_t open = L'{', wchar_t close = L'}');
	};
}