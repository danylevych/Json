#pragma once
#include "../Tools/BaseType.h"
#include <string>

namespace Core
{
	namespace Types
	{
		class Null : public BaseType
		{
		private:
			std::nullptr_t value;

		public:
			Null();

		public:
			operator std::string() const;
			operator bool() const;

		public:
			const std::nullptr_t& Value() const;

			virtual Core::JsonTypes GetType() const { return type; }

		public:
			friend std::ostream& operator<<(std::ostream& out, const Null& null);
		};

	}
}
