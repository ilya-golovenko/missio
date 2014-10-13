//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_generate_value_hpp
#define _missio_format_detail_generate_value_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_iterator.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink, typename Policy, typename Value, typename Generator>
void generate_value(sink_iterator<Sink, Policy>& sink_iterator, Value const& value, Generator const& generator)
{
    boost::spirit::karma::generate(sink_iterator, generator, value);
}

template <typename Sink, typename Value, typename Generator>
void generate_value(Sink& sink, Value const& value, Generator const& generator)
{
    sink_iterator<Sink> sink_iterator(sink);

    boost::spirit::karma::generate(sink_iterator, generator, value);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_generate_value_hpp
