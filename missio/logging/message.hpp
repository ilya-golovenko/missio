//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_message_hpp
#define _missio_logging_message_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// Application headers
#include <missio/logging/severity.hpp>
#include <missio/logging/location.hpp>
#include <missio/logging/detail/sink_buffer.hpp>
#include <missio/logging/detail/message_id.hpp>
#include <missio/logging/detail/process_id.hpp>
#include <missio/logging/detail/thread_id.hpp>
#include <missio/logging/detail/timestamp.hpp>
#include <missio/format/adapters/pointer.hpp>
#include <missio/format/adapters/boost.hpp>
#include <missio/format/adapters/std.hpp>
#include <missio/format/write.hpp>
#include <missio/format/print.hpp>


namespace missio
{
namespace logging
{

class MISSIO_EXPORT message
{
public:
    template <typename ... Args>
    message(severity severity, location const& location, Args const& ... args);

    template <typename Format, typename ... Args>
    message(Format const& format, severity severity, location const& location, Args const& ... args);

    message(message const&) = delete;
    message& operator=(message const&) = delete;

    message(message&&) = default;
    message& operator=(message&&) = default;

    severity get_severity() const;

    template <typename Sink, typename Format>
    void format(Sink& sink, Format const& format) const;

private:
    severity severity_;
    location location_;
    detail::timestamp timestamp_;
    detail::message_id message_id_;
    detail::process_id process_id_;
    detail::thread_id thread_id_;
    detail::sink_buffer buffer_;
};

template <typename ... Args>
message::message(severity severity, location const& location, Args const& ... args):
    severity_(severity),
    location_(location)
{
    missio::format::write(buffer_, args...);
}

inline severity message::get_severity() const
{
    return severity_;
}

template <typename Sink, typename Format>
void message::format(Sink& sink, Format const& format) const
{
    format::print(
        sink,
        format,
        message_id_.value(),
        timestamp_.value(),
        to_string(severity_),
        process_id_.value(),
        thread_id_.value(),
        location_.component(),
        location_.function(),
        location_.filename(),
        location_.line(),
        buffer_
    );
}

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_message_hpp
