#pragma once
#include "../Tools/BaseType.h"
#include "../Tools/ReturnedDataJson.h"

#include "Boolean.h"
#include "Int.h"
#include "Null.h"
#include "String.h"
#include "Float.h"
#include "Object.h"

#include <vector>
#include <memory>
#include <ostream>
#include <initializer_list>

namespace Core
{
	namespace Types
	{
		class Array : public BaseType
		{
		public:
			/* Iterators */
			class iterator;
			class const_iterator;
			class reverse_iterator;
			class const_reverse_iterator;

		public:
			using BaseTypePtrT  = Core::Types::BaseType*;
			using BaseSmartPtrT = std::unique_ptr<Core::Types::BaseType>;

		private:
			std::vector<BaseSmartPtrT> values;

		public:
			Array();
			Array(const std::initializer_list<BaseTypePtrT>& list);
			Array(Array&& other) noexcept;
			Array(const Array& other) = delete;

		public:
			Array& operator=(Array&& other) noexcept;
			Array& operator=(const Array& other) = delete;

			Array& operator=(const std::initializer_list<BaseTypePtrT>& list);

			
			ReturnedDataJson operator[](size_t index);
			const ReturnedDataJson operator[](size_t index) const;

		public:
			std::vector<BaseSmartPtrT>& Value();
			const std::vector<BaseSmartPtrT>& Value() const;
			
			virtual Core::JsonTypes GetType() const override { return type; }

		public:
			operator std::string() const;

		public:
			void PushBack(BaseTypePtrT ptr);
			void PushBack(BaseSmartPtrT&& ptr);

			size_t Size() const { return values.size(); }
			void Clear() { values.clear(); }
			bool Empty() const { return values.empty(); }
			const std::vector<BaseSmartPtrT>& Data() const { return values; }
			
			ReturnedDataJson Front() { return ReturnedDataJson(values.front()); }
			const ReturnedDataJson Front() const { return ReturnedDataJson(values.front()); }

			BaseSmartPtrT& Back() { return values.back(); }
			const BaseSmartPtrT& Back() const { return values.back(); }
			void PopBack() { values.pop_back(); }

			void Swap(Array& other) { values.swap(other.values); }
			iterator Insert(const_iterator where, BaseSmartPtrT&& val) { return iterator(values.insert(where.iter, std::move(val))); }
			template <typename ...Arg>
			iterator Emplace(const_iterator where, Arg&&... arg) { return iterator(values.emplace(where.iter, arg)); }

			iterator Erase(const_iterator where) { return iterator(values.erase(where.iter)); }
			iterator Erase(const_iterator first, const_iterator last) { return iterator(values.erase(first.iter, last.iter)); }

		public:
			iterator begin() { return iterator(values.begin()); }
			const_iterator cbegin() const { return const_iterator(values.cbegin()); }

			iterator end() { return iterator(values.end()); }
			const_iterator cend() const { return const_iterator(values.cend()); }


			reverse_iterator rbegin() { return reverse_iterator(values.rbegin()); }
			const_reverse_iterator crbegin() const { return const_reverse_iterator(values.crbegin()); }

			reverse_iterator rend() { return reverse_iterator(values.rend()); }
			const_reverse_iterator crend() const { return const_reverse_iterator(values.crend()); }

		private:
			////////////////////////////////////////////////////////////////////////////////
			//                                                                            //
			//	    ╔═══╗╔══╗╔╗╔╗╔╗      ╔══╗╔════╗╔═══╗╔═══╗╔══╗╔════╗╔══╗╔═══╗╔══╗	  //
			//	    ║╔═╗║║╔╗║║║║║║║      ╚╗╔╝╚═╗╔═╝║╔══╝║╔═╗║║╔╗║╚═╗╔═╝║╔╗║║╔═╗║║╔═╝	  //
			//	    ║╚═╝║║╚╝║║║║║║║       ║║   ║║  ║╚══╗║╚═╝║║╚╝║  ║║  ║║║║║╚═╝║║╚═╗	  //
			//	    ║╔╗╔╝║╔╗║║║║║║║       ║║   ║║  ║╔══╝║╔╗╔╝║╔╗║  ║║  ║║║║║╔╗╔╝╚═╗║	  //
			//	    ║║║║ ║║║║║╚╝╚╝║      ╔╝╚╗  ║║  ║╚══╗║║║║ ║║║║  ║║  ║╚╝║║║║║ ╔═╝║	  //
			//	    ╚╝╚╝ ╚╝╚╝╚═╝╚═╝      ╚══╝  ╚╝  ╚═══╝╚╝╚╝ ╚╝╚╝  ╚╝  ╚══╝╚╝╚╝ ╚══╝	  //
			//                                                                            //
			////////////////////////////////////////////////////////////////////////////////
			//                                                                            //
			//     The raw iterators are the iterators of std::vector<BaseSmartPtrT>.     //
			//     For comfortable work in loops, we had done the wrapper around them.    //
			//     Each clases has the template method Get(), which let doing cast of     //
			//     object to some type, that is in Core::JsonType. And wrappers also      //
			//     have the typecast operator.                                            //
			//                                                                            //
			////////////////////////////////////////////////////////////////////////////////

			using raw_iterator               = std::vector<BaseSmartPtrT>::iterator;
			using raw_const_iterator		 = std::vector<BaseSmartPtrT>::const_iterator;
			using raw_reverse_iterator       = std::vector<BaseSmartPtrT>::reverse_iterator;
			using raw_const_reverse_iterator = std::vector<BaseSmartPtrT>::const_reverse_iterator;


			class base_iterator
			{
			// This class is a main for all wrapper iterators.
			public:
				base_iterator() = default;
				virtual ~base_iterator() = default;

			public:
				virtual const BaseType& operator*() const = 0;
				virtual const BaseType* operator->() const = 0;

			public:
				virtual base_iterator& operator++() = 0;
				virtual base_iterator& operator--() = 0;

			};

		public:
			class iterator : public base_iterator
			{
			private:
				raw_iterator iter;

			public:
				iterator();
				iterator(const raw_iterator& iter);
				iterator(raw_iterator&& iter) noexcept;

				iterator(const iterator& other);
				iterator(iterator&& other) noexcept;

				iterator& operator=(const iterator& other);
				iterator& operator=(iterator&& other) noexcept;

				virtual ~iterator() override = default;

			public:
				BaseType& operator*();
				BaseType* operator->();

				virtual const BaseType& operator*() const override;
				virtual const BaseType* operator->() const override;

			public:
				iterator operator++(int);
				virtual iterator& operator++() override;
				
				iterator operator--(int);
				virtual iterator& operator--() override;
				
			public:
				bool operator!=(const iterator& other) const;
				bool operator==(const iterator& other) const;

			public:
				template<typename T>
				operator T& () { return dynamic_cast<T&>(*iter->get()); }

				template<typename T>
				operator const T& () const { return dynamic_cast<const T&>(*iter->get()); }

			private:
				friend class Array;
				friend class const_iterator;
			};


			class const_iterator : public base_iterator
			{
			private:
				raw_const_iterator iter;

			public:
				const_iterator();

				const_iterator(const raw_iterator& iter);
				const_iterator(raw_iterator&& iter) noexcept;

				const_iterator(const raw_const_iterator& iter);
				const_iterator(raw_const_iterator&& iter) noexcept;
				
				const_iterator(const iterator& other);
				const_iterator(iterator&& other) noexcept;

				const_iterator(const const_iterator& other);
				const_iterator(const_iterator&& other) noexcept;

				const_iterator& operator=(const iterator& other);
				const_iterator& operator=(iterator&& other) noexcept;

				const_iterator& operator=(const const_iterator& other);
				const_iterator& operator=(const_iterator&& other) noexcept;

				virtual ~const_iterator() override = default;

			public:
				virtual const BaseType& operator*() const override;
				virtual const BaseType* operator->() const override;

			public:
				const_iterator operator++(int);
				virtual const_iterator& operator++() override;

				const_iterator operator--(int);
				virtual const_iterator& operator--() override;

			public:
				bool operator!=(const const_iterator& other) const;
				bool operator==(const const_iterator& other) const;

			public:
				template<typename T>
				operator const T& () const { return dynamic_cast<const T&>(*iter->get()); }

			public:
				friend class Array;
			};


			class reverse_iterator : public base_iterator
			{
			private:
				raw_reverse_iterator iter;

			public:
				reverse_iterator();
				reverse_iterator(const raw_reverse_iterator& iter);
				reverse_iterator(raw_reverse_iterator&& iter) noexcept;

				reverse_iterator(const reverse_iterator& other);
				reverse_iterator(reverse_iterator&& other) noexcept;

				reverse_iterator& operator=(const reverse_iterator& other);
				reverse_iterator& operator=(reverse_iterator&& other) noexcept;

				virtual ~reverse_iterator() override = default;

			public:
				BaseType& operator*();
				BaseType* operator->();

				virtual const BaseType& operator*() const override;
				virtual const BaseType* operator->() const override;

			public:
				reverse_iterator operator++(int);
				virtual reverse_iterator& operator++() override;

				reverse_iterator operator--(int);
				virtual reverse_iterator& operator--() override;

			public:
				bool operator!=(const reverse_iterator& other) const;
				bool operator==(const reverse_iterator& other) const;

			public:
				template<typename T>
				operator T& () { return dynamic_cast<T&>(*iter->get()); }

				template<typename T>
				operator const T& () const { return dynamic_cast<const T&>(*iter->get()); }

			private:
				friend class const_reverse_iterator;
			};


			class const_reverse_iterator : public base_iterator
			{
			private:
				raw_const_reverse_iterator iter;

			public:
				const_reverse_iterator();

				const_reverse_iterator(const raw_reverse_iterator& iter);
				const_reverse_iterator(raw_reverse_iterator&& iter) noexcept;

				const_reverse_iterator(const raw_const_reverse_iterator& iter);
				const_reverse_iterator(raw_const_reverse_iterator&& iter) noexcept;

				const_reverse_iterator(const reverse_iterator& other);
				const_reverse_iterator(reverse_iterator&& other) noexcept;

				const_reverse_iterator(const const_reverse_iterator& other);
				const_reverse_iterator(const_reverse_iterator&& other) noexcept;

				const_reverse_iterator& operator=(const reverse_iterator& other);
				const_reverse_iterator& operator=(reverse_iterator&& other) noexcept;

				const_reverse_iterator& operator=(const const_reverse_iterator& other);
				const_reverse_iterator& operator=(const_reverse_iterator&& other) noexcept;

				virtual ~const_reverse_iterator() override = default;

			public:
				virtual const BaseType& operator*() const override;
				virtual const BaseType* operator->() const override;

			public:
				const_reverse_iterator operator++(int);
				virtual const_reverse_iterator& operator++() override;

				const_reverse_iterator operator--(int);
				virtual const_reverse_iterator& operator--() override;

			public:
				bool operator!=(const const_reverse_iterator& other) const;
				bool operator==(const const_reverse_iterator& other) const;

			public:
				template<typename T>
				operator const T& () const { return dynamic_cast<const T&>(*iter->get()); }
			};

		public:
			friend std::ostream& operator<<(std::ostream& out, const Array& array);
		};
	}
}


