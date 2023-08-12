#pragma once
#include "../Tools/BaseType.h"
#include <string>
#include <ostream>
#include <codecvt>


namespace Core
{
    namespace Types
    {   
        /////////////////////////////////////////////////////////
        //                                                     //
        //    Core::Types::String  use the std::wstring for    // 
        //    save all  strings' data from .json. There are    // 
        //    the strings what  is  represent by  ASCII  or    // 
        //    UTF-8, therefor we have used the std::wstring    //
        //                                                     //
        /////////////////////////////////////////////////////////

        class String : public BaseType
        {
        private:
            std::wstring value;
            mutable std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        public:
            String();
            String(const char* value);
            String(std::string&& value);
            String(const std::string& value);
            String(std::wstring&& value);
            String(const std::wstring& value);
            String(String&& other) noexcept;
            String(const String& other);

        public:
            String& operator=(String&& other) noexcept;
            String& operator=(const String& other);

        public:
            operator std::string() const;
            operator std::wstring&();
            operator const std::wstring&() const;

        public:
            std::wstring& Value();
            const std::wstring& Value() const;

            virtual Core::JsonTypes GetType() const { return type; }
        
        private:
            std::string ToString(const std::wstring& str) const;
            std::wstring ToWString(const std::string& str) const;

        public:
            bool operator<(const String& other) const;
            bool operator>(const String& other) const;
            bool operator==(const String& other) const;
            bool operator!=(const String& other) const;

        public:
            friend std::ostream& operator<<(std::ostream& out, const String& str);
        };
    }
}
