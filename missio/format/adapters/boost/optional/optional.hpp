//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_boost_optional_optional_hpp
#define _missio_format_adapters_boost_optional_optional_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/optional.hpp>
#include <boost/none.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value>
struct type_adapter<boost::optional<Value>>
{
    template <typename Sink>
    static void format(Sink& sink, boost::optional<Value> const& value)
    {
        if(value)
        {
            write(sink, *value);
        }
        else
        {
            write(sink, "--");
        }
    }
};

template <>
struct type_adapter<boost::none_t>
{
    template <typename Sink>
    static void format(Sink& sink, boost::none_t)
    {
        write(sink, "--");
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_boost_optional_optional_hpp
