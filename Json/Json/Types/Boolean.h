#pragma once
#include "../Tools/BaseType.h"
#include <ostream>

namespace Core
{
    namespace Types
    {
        class Boolean : public BaseType
        {
        private:
            bool value;

        public:
            Boolean();
            Boolean(bool value);
            Boolean(Boolean&& other) noexcept;
            Boolean(const Boolean& other);

        public:
            Boolean& operator=(Boolean&& other) noexcept;
            Boolean& operator=(const Boolean& other);
            
        public:
            operator bool& ();
            operator const bool& () const;
            operator bool() const;
            operator Boolean() const;

        public:
            virtual Core::JsonTypes GetType() const { return type; }

        public:
            bool& Value();
            const bool& Value() const;

        public:
            friend std::ostream& operator<<(std::ostream& out, const Boolean& boolean);
        };
    }
}

