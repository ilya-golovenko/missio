//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Implementation headers
#include "base64.hpp"

// STL headers
#include <iterator>


namespace missio
{
namespace json
{
namespace detail
{

std::string base64::encode(std::vector<std::uint8_t> const& input)
{
    std::string output;

    output.reserve(input.size() * 4 / 3);

    encode(input.begin(), input.end(), std::back_inserter(output));

    return output;
}

std::vector<std::uint8_t> base64::decode(std::string const& input)
{
    std::vector<std::uint8_t> output;

    output.reserve(input.size() * 3 / 4);

    decode(input.begin(), input.end(), std::back_inserter(output));

    return output;
}

char base64::from_6_bit(std::uint8_t ch)
{
    static char const lookup_table[] =
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
    };

    return lookup_table[ch];
}

std::uint8_t base64::to_6_bit(std::uint8_t ch)
{
    static std::uint8_t const nop(255);

    static std::uint8_t const lookup_table[] =
    {
        nop, nop, nop, nop, nop, nop, nop, nop,
        nop, nop, nop, nop, nop, nop, nop, nop,
        nop, nop, nop, nop, nop, nop, nop, nop,
        nop, nop, nop, nop, nop, nop, nop, nop,
        nop, nop, nop, nop, nop, nop, nop, nop,
        nop, nop, nop,  62, nop, nop, nop,  63,
         52,  53,  54,  55,  56,  57,  58,  59,
         60,  61, nop, nop, nop, nop, nop, nop,
        nop,   0,   1,   2,   3,   4,   5,   6,
          7,   8,   9,  10,  11,  12,  13,  14,
         15,  16,  17,  18,  19,  20,  21,  22,
         23,  24,  25, nop, nop, nop, nop, nop,
        nop,  26,  27,  28,  29,  30,  31,  32,
         33,  34,  35,  36,  37,  38,  39,  40,
         41,  42,  43,  44,  45,  46,  47,  48,
         49,  50,  51, nop, nop, nop, nop, nop
    };

    std::uint8_t const value = ch < 128 ? lookup_table[ch] : nop;

    if(nop == value)
        throw exception("invalid BASE-64 character");

    return value;
}

}   // namespace detail
}   // namespace json
}   // namespace missio
