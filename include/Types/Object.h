#pragma once

#include "../Tools/BaseType.h"
#include "../Tools/ReturnedDataJson.h"


#include "Bollean.h"
#include "Int.h"
#include "Null.h"
#include "String.h"
#include "Array.h"


#include <memory>
#include <ostream>
#include <unordered_map>
#include <initializer_list>


// Overloding the hash function for the std::unordered_map
namespace std
{
    template <>
    struct hash<Core::Types::String> 
    {
        size_t operator()(const Core::Types::String& Keyval) const noexcept
        {
            return hash<std::wstring>()(Keyval.Value());
        }
    };
}


namespace Core
{
    namespace Types
    {
        class Object : public BaseType
        {
        public: 
            class iterator;
            class const_iterator;

        public:
            using BaseTypePtrT   = Core::Types::BaseType*;
            using BaseSmartPtrT  = std::unique_ptr<Core::Types::BaseType>;
            using KeyValueT      = std::pair<const String, Core::Types::BaseType*>;
            using KeyValueSmartT = std::pair<const String, std::unique_ptr<Core::Types::BaseType>>;

        private:
            std::unordered_map<String, BaseSmartPtrT> values;

#ifdef ORDER_KEY
            std::vector<String> orderKey;
#endif

        public:
            Object();
            Object(Object&& other) noexcept;
            Object(const Object& other) = delete;
            Object(const std::initializer_list<KeyValueT>& list);

            virtual ~Object() = default;

        public:
            Object& operator=(Object&& other) noexcept;
            Object& operator=(const Object& other) = delete;

            ReturnedDataJson operator[](const String& key);
            const ReturnedDataJson operator[](const String& key) const;

        public:
            ReturnedDataJson Get(const String& key, BaseType* def = nullptr);
            ReturnedDataJson Get(const String& key, BaseType&& def);
            ReturnedDataJson Get(const String& key, BaseType& def);

            const ReturnedDataJson Get(const String& key, BaseType& def) const;
            const ReturnedDataJson Get(const String& key, BaseType&& def) const;
            const ReturnedDataJson Get(const String& key, BaseType* def = nullptr) const;

        public:
            std::unordered_map<String, std::unique_ptr<BaseType>>& Value();
            const std::unordered_map<String, std::unique_ptr<BaseType>>& Value() const;
            
            operator std::string() const;
            virtual Core::JsonTypes GetType() const override { return type; }
        
        public:
#ifdef ORDER_KEY
            const std::vector<String>& GetKeyOrder() const { return orderKey; }
#endif

            size_t Size() const { return values.size(); }
            bool Empty() const { return values.empty(); }
            void Clear() { values.clear(); }

            iterator Find(const String& key) { return iterator(values.find(key)); }
            const_iterator Find(const String& key) const { return const_iterator(values.find(key)); }

            iterator Insert(const KeyValueT& pair);
            iterator Insert(KeyValueT&& pair);
            iterator Insert(KeyValueSmartT&& pair);
            iterator Insert(const KeyValueSmartT& pair);
            void Insert(const std::initializer_list<KeyValueT>& list);
            void Insert(Object&& insertObj);

            template<typename ...Arg>
            std::pair<iterator, bool> Emplace(Arg&&... args)
            {
                auto tempPair = values.emplace(args...);
                return std::pair<iterator, bool>(iterator(tempPair.first), tempPair.second);
            }

            bool Erase(const String& key);
            iterator Erase(const_iterator iter);
            iterator Erase(const_iterator first, const_iterator last);

        public:
            iterator begin() { return iterator(values.begin()); }
            const_iterator cbegin() const { return const_iterator(values.cbegin()); }

            iterator end() { return iterator(values.end()); }
            const_iterator cend() const { return const_iterator(values.cend()); }

        private:
            using raw_iterator       = std::unordered_map<String, BaseSmartPtrT>::iterator;
            using raw_const_iterator = std::unordered_map<String, BaseSmartPtrT>::const_iterator;


            class base_iterator
            {
                // This class is a main for all wrapper iterators.
            public:
                base_iterator() = default;
                virtual ~base_iterator() = default;

            public:
                virtual const KeyValueSmartT& operator*() const = 0;
                virtual const KeyValueSmartT* operator->() const = 0;

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
                iterator() = default;
                iterator(const raw_iterator& iter);
                iterator(raw_iterator&& iter) noexcept;

                iterator(const iterator& other);
                iterator(iterator&& other) noexcept;

                virtual ~iterator() override = default;
            
            public:
                iterator& operator=(const iterator& iter);
                iterator& operator=(iterator&& iter) noexcept;
            
            public:
                KeyValueSmartT& operator*();
                KeyValueSmartT* operator->();

                virtual const KeyValueSmartT& operator*() const override;
                virtual const KeyValueSmartT* operator->() const override;

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
                operator T& () { return dynamic_cast<T&>(*iter->second.get()); }

                template<typename T>
                operator const T& () const { return dynamic_cast<const T&>(*iter->second.get()); }

            private:
                friend class Object;
                friend class const_iterator;
            };


            class const_iterator : public base_iterator
            {
            private:
                raw_const_iterator iter;

            public:
                const_iterator() = default;
                const_iterator(const raw_const_iterator& iter);
                const_iterator(raw_const_iterator&& iter) noexcept;

                const_iterator(const iterator& iter);
                const_iterator(iterator&& iter) noexcept;

                const_iterator(const const_iterator& other);
                const_iterator(const_iterator&& other) noexcept;

                virtual ~const_iterator() override = default;

            public:
                const_iterator& operator=(const iterator& iter);
                const_iterator& operator=(iterator&& iter) noexcept;

                const_iterator& operator=(const const_iterator& iter);
                const_iterator& operator=(const_iterator&& iter) noexcept;

            public:
                virtual const KeyValueSmartT& operator*() const override;
                virtual const KeyValueSmartT* operator->() const override;

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
                operator const T& () const { return dynamic_cast<const T&>(*iter->second.get()); }

            private:
                friend class Object;
            };

        public:
            friend std::ostream& operator<<(std::ostream& out, const Object& obj);
        };
    }
}
