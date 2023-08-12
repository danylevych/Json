#pragma once
#include "../Tools/BaseType.h"

namespace Core
{
    namespace Types
    {
        class Float : public BaseType
        {
        private:
            double value;

        public:
            Float();
            Float(double value);
            Float(Float&& other) noexcept;
            Float(const Float& other);

        public:
            Float& operator=(Float&& other) noexcept;
            Float& operator=(const Float& other);

        public:
            operator double&();
            operator const double&() const;
            operator double() const;
            operator Float() const;

            virtual Core::JsonTypes GetType() const { return type; }

        public:
            double& Value();
            const double& Value() const;
        };
    }
}
