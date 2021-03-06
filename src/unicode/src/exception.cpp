//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/unicode/exception.hpp>

// STL headers
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <string>


namespace missio
{
namespace unicode
{

std::string exception::message() const
{
    return std::string(what());
}

char const* input_underflow_error::what() const noexcept
{
    return "input underflow error";
}

invalid_utf32_code_point::invalid_utf32_code_point(std::uint32_t code_point) :
    code_point_(code_point)
{
}

std::uint32_t invalid_utf32_code_point::code_point() const noexcept
{
    return code_point_;
}

char const* invalid_utf32_code_point::what() const noexcept
{
    return "invalid UTF-32 code point";
}

std::string invalid_utf32_code_point::message() const
{
    std::ostringstream os;

    os.imbue(std::locale::classic());

    os << what()
       << ": U+"
       << std::hex
       << std::setw(4)
       << std::setfill('0')
       << std::uppercase
       << code_point_;

    return os.str();
}

invalid_utf16_code_unit::invalid_utf16_code_unit(std::uint16_t code_unit) :
    code_unit_(code_unit)
{
}

std::uint16_t invalid_utf16_code_unit::code_unit() const noexcept
{
    return code_unit_;
}

char const* invalid_utf16_code_unit::what() const noexcept
{
    return "invalid or unexpected UTF-16 code unit";
}

std::string invalid_utf16_code_unit::message() const
{
    std::ostringstream os;

    os.imbue(std::locale::classic());

    os << what()
       << ": 0x"
       << std::hex
       << std::setw(4)
       << std::setfill('0')
       << std::uppercase
       << code_unit_;

    return os.str();
}

std::string invalid_utf8_sequence::sequence() const
{
    return std::string(sequence_, sequence_ + sequence_length_);
}

char const* invalid_utf8_sequence::what() const noexcept
{
    return "invalid UTF-8 sequence";
}

std::string invalid_utf8_sequence::message() const
{
    std::ostringstream os;

    os.imbue(std::locale::classic());

    os << what();

    if(sequence_length_ > 0)
    {
        os << ':'
           << std::hex
           << std::setfill('0')
           << std::uppercase;

        for(std::size_t i = 0; i < sequence_length_; ++i)
        {
            os << " 0x" << std::setw(2) << static_cast<int>(sequence_[i]);
        }
    }

    return os.str();
}

}   // namespace unicode
}   // namespace missio
