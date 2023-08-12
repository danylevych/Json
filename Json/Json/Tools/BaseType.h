#pragma once

#include "JsonTypes.h"
#include <memory>
//#include "../Types/Bollean.h"
//#include "../Types/Int.h"
//#include "../Types/Null.h"
//#include "../Types/String.h"
//#include "../Types/Float.h"
//#include "../Types/Object.h"

namespace Core
{
	namespace Types
	{
		class BaseType
		{
		protected:
			JsonTypes type;

		public:
			BaseType(JsonTypes&& type);
			BaseType(const JsonTypes& type);
		
		public:
			bool IsObject() const;
			bool IsArray() const;
			bool IsString() const;
			bool IsInt() const;
			bool IsFloat() const;
			bool IsBoolean() const;
			bool IsNull() const;

		public:
			template<typename T>
			T& Get() { return *dynamic_cast<T*>(this); }

		public:
			virtual JsonTypes GetType() const = 0;
			virtual ~BaseType() = default;
		
		};
	}
}


