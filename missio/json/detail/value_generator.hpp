//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_value_generator_hpp
#define _missio_json_detail_value_generator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/value_traits.hpp>
#include <missio/json/detail/real_policies.hpp>
#include <missio/json/detail/string_generator.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/std_pair.hpp>


namespace missio
{
namespace json
{
namespace detail
{

namespace karma = boost::spirit::karma;

template <typename Iterator>
struct value_generator : karma::grammar<Iterator, value()>
{
    value_generator() : value_generator::base_type(value_)
    {
        using karma::_1;
        using karma::lit;
        using karma::bool_;

        typedef high_precision_real_policies<real> real_policies;
        karma::real_generator<real, real_policies> real_generator;

        karma::int_generator<integer> int_generator;

        null_       =   lit("null")[_1];

        string_     =   string_generator;

        real_       =   real_generator;

        integer_    =   int_generator;

        boolean_    =   bool_;

        array_      =   '['
                    << -(value_ % ',')
                    <<  ']'
                    ;

        pair_       =   string_
                    <<  ':'
                    <<  value_
                    ;

        object_     =   '{'
                    << -(pair_ % ',')
                    <<  '}'
                    ;

        value_      =   string_
                    |   array_
                    |   object_
                    |   real_
                    |   integer_
                    |   boolean_
                    |   null_
                    ;
    }

    typedef object::value_type pair;

    karma::rule<Iterator, null()> null_;
    karma::rule<Iterator, real()> real_;
    karma::rule<Iterator, string()> string_;
    karma::rule<Iterator, integer()> integer_;
    karma::rule<Iterator, boolean()> boolean_;
    karma::rule<Iterator, array()> array_;
    karma::rule<Iterator, pair()> pair_;
    karma::rule<Iterator, object()> object_;
    karma::rule<Iterator, value()> value_;
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_value_generator_hpp
