//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_value_get_hpp
#define _missio_json_detail_value_get_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application header
#include <missio/json/value.hpp>


namespace boost
{

template <typename T>
missio::json::value::result_type_of_get<T> get(missio::json::value const& value)
{
    return value.get<T>();
}

}   // namespace boost

#endif  // _missio_json_detail_value_get_hpp
