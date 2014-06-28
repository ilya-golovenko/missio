//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/common.hpp>
#include <missio/logging/factory.hpp>

// STL headers
#include <utility>


namespace missio
{
namespace logging
{

void initialize()
{
    factory::create_dispatcher();
}

void shutdown()
{
    factory::destroy_dispatcher();
}

void start()
{
    factory::get_dispatcher().start();
}

void stop()
{
    factory::get_dispatcher().stop();
}

}   // namespace logging
}   // namespace missio
