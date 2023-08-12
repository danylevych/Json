#pragma once
#include "../Tools/BaseType.h"
#include <iostream>

namespace Core
{
    namespace Types
    {
        class Int : public BaseType
        {
        private:
            int value;

        public:
            Int();
            Int(int value);
            Int(Int&& other) noexcept;
            Int(const Int& other);

        public:
            Int& operator=(Int&& other) noexcept;
            Int& operator=(const Int& other);

        public:
            operator int&();
            operator const int&() const;
            operator int() const;
            operator Int() const;
        
        public:
            virtual Core::JsonTypes GetType() const { return type; }

        public:
            int& Value();
            const int& Value() const;
        };
    }
}


