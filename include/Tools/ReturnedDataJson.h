#pragma once
#include "BaseType.h"

namespace Core
{
	namespace Types
	{
		class ReturnedDataJson
		{
		private:
			 BaseType* ptr;
			 std::unique_ptr<BaseType>* ref;

		public:
			ReturnedDataJson(BaseType& ptr)
				: ptr(&ptr),
				ref(nullptr)
			{	}
			
			ReturnedDataJson(BaseType&& ptr)
				: ptr(&ptr),
				ref(nullptr)
			{	}

			ReturnedDataJson(BaseType* ptr)
				: ptr(ptr),
				ref(nullptr)
			{	}

			ReturnedDataJson(std::unique_ptr<BaseType>& ptr)
				: ptr(nullptr),
				ref(&ptr)
			{	}

			ReturnedDataJson(const std::unique_ptr<BaseType>& ptr)
				: ptr(nullptr),
				ref(const_cast<std::unique_ptr<BaseType>*>(&ptr))
			{	}

		public:
			ReturnedDataJson& operator=(BaseType* ptr)
			{
				if(this->ptr == nullptr)
				{
					this->ref->reset(ptr);
				}
				
				return *this;
			}

		public:
			template <typename T>
			operator T& () { return ptr ? dynamic_cast<T&>(*ptr) : dynamic_cast<T&>(*ref->get()); }

			template <typename T>
			operator const T& () const { return ptr ? dynamic_cast<T&>(*ptr) : dynamic_cast<T&>(*ref->get()); }

			template <typename T>
			T& Get() { return ptr ? dynamic_cast<T&>(*ptr) : dynamic_cast<T&>(*ref->get()); }
			
			template <typename T>
			const T& Get() const { return ptr ? dynamic_cast<T&>(*ptr) : dynamic_cast<T&>(*ref->get()); }
		};
	}
}
