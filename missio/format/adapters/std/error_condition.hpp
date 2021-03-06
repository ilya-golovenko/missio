//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_adapters_std_error_condition_hpp
#define _missio_format_adapters_std_error_condition_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <system_error>


namespace missio
{
namespace format
{
namespace detail
{

template <>
struct type_adapter<std::error_condition>
{
    template <typename Sink>
    static void format(Sink& sink, std::error_condition const& value)
    {
        write(sink, value.message(), " (", value.category().name(), ':', value.value(), ')');
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_adapters_std_error_condition_hpp
