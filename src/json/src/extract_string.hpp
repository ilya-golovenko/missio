//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_extract_string_hpp
#define _missio_json_detail_extract_string_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/string.hpp>

// BOOST headers
#include <boost/spirit/include/qi.hpp>

// STL headers
#include <type_traits>
#include <iterator>
#include <utility>
#include <cstdint>
#include <string>


namespace missio
{
namespace json
{
namespace detail
{

template <typename Attribute>
struct assign_to_attribute
{
    static void call(std::string const& str, Attribute& attr)
    {
        boost::spirit::traits::assign_to(str, attr);
    }
};

template <>
struct assign_to_attribute<string>
{
    static void call(std::string&& str, string& attr)
    {
        attr = std::forward<std::string>(str);
    }
};

class extract_string
{
public:
    template <typename Iterator, typename Attribute>
    static bool call(Iterator& first, Iterator const& last, Attribute& attr)
    {
        Iterator i(first);

        if(!skip_char(i, last, '"'))
            return false;

        std::string str;

        for(;;)
        {
            if(skip_char(i, last, '\\'))
            {
                if(!parse_utf16(i, last, str))
                {
                    if(!parse_escape(i, last, str))
                        return false;
                }
            }
            else
            {
                if(skip_char(i, last, '"'))
                    break;

                if(!parse_char(i, last, str))
                    return false;
            }
        }

        assign_to_attribute<Attribute>::call(std::move(str), attr);

        first = i;

        return true;
    }

private:
    template <typename Iterator>
    static bool skip_char(Iterator& first, Iterator const& last, char const ch)
    {
        if(last == first)
            return false;

        if(ch != *first)
            return false;

        ++first;

        return true;
    }

    template <typename Iterator>
    static bool parse_char(Iterator& first, Iterator const& last, std::string& str)
    {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        typedef typename std::make_unsigned<value_type>::type unsigned_type;

        if(last == first)
            return false;

        unsigned_type const ch(*first);

        if(static_cast<unsigned_type>(0x1F) >= ch)
            return false;

        str.push_back(static_cast<char>(ch));

        ++first;

        return true;
    }

    template <typename Iterator>
    static bool parse_escape(Iterator& first, Iterator const& last, std::string& str)
    {
        if(last == first)
            return false;

        switch(*first)
        {
            case '"': str.push_back('"'); break;
            case '/': str.push_back('/'); break;
            case 'b': str.push_back('\b'); break;
            case 'f': str.push_back('\f'); break;
            case 'n': str.push_back('\n'); break;
            case 'r': str.push_back('\r'); break;
            case 't': str.push_back('\t'); break;
            case '\\': str.push_back('\\'); break;

            default:
                return false;
        }

        ++first;

        return true;
    }

    template <typename Iterator>
    static bool parse_utf16(Iterator& first, Iterator const& last, std::string& str)
    {
        Iterator i(first);

        if(!skip_char(i, last, 'u'))
            return false;

        std::uint32_t cp1;

        if(!extract_utf16(i, last, cp1))
            return false;

        if(is_low_surrogate(cp1))
            return false;

        if(is_high_surrogate(cp1))
        {
            if(!skip_char(i, last, '\\'))
                return false;

            if(!skip_char(i, last, 'u'))
                return false;

            std::uint32_t cp2;

            if(!extract_utf16(i, last, cp2))
                return false;

            if(!is_low_surrogate(cp2))
                return false;

            cp1 = make_code_point(cp1, cp2);
        }

        if(!write_code_point(cp1, str))
            return false;

        first = i;

        return true;
    }

    template <typename Iterator>
    static bool extract_utf16(Iterator& first, Iterator const& last, std::uint32_t& cp)
    {
        return boost::spirit::qi::extract_uint<std::uint32_t, 16, 4, 4>::call(first, last, cp);
    }

    static std::uint32_t make_code_point(std::uint32_t const high, std::uint32_t const low)
    {
        return 0x10000u + ((high - 0xD800u) << 10u) + low - 0xDC00u;
    }

    static bool is_high_surrogate(std::uint32_t const cp)
    {
        return 0xD800u <= cp && cp <= 0xDBFFu;
    }

    static bool is_low_surrogate(std::uint32_t const cp)
    {
        return 0xDC00u <= cp && cp <= 0xDFFFu;
    }

    static bool is_code_point_valid(std::uint32_t const cp)
    {
        return cp <= 0x10FFFFu && cp != 0xFFFEu && cp != 0xFFFFu;
    }

    static bool write_code_point(std::uint32_t const cp, std::string& str)
    {
        if(!is_code_point_valid(cp))
             return false;

        if(cp < 0x80u)
        {
            str.push_back(static_cast<char>(cp));
        }
        else if(cp < 0x800u)
        {
            str.push_back(static_cast<char>(0xC0 | ((cp >> 6) & 0x1F)));
            str.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
        }
        else if(cp < 0x10000u)
        {
            str.push_back(static_cast<char>(0xE0 | ((cp >> 12) & 0x0F)));
            str.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
            str.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
        }
        else if(cp < 0x110000u)
        {
            str.push_back(static_cast<char>(0xF0 | ((cp >> 18) & 0x07)));
            str.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
            str.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
            str.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
        }
  
        return true;
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_extract_string_hpp
