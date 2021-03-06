//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/format/detail/time_point.hpp>

// STL headers
#include <ctime>


namespace missio
{
namespace format
{
namespace detail
{

static int const days_in_month[12] =
{
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static int const days_in_month_leap_year[12] =
{
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static char const* const month_names[12] =
{
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static bool is_leap_year(std::int32_t year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int get_days_in_year(std::int32_t year)
{
    return is_leap_year(year) ? 366 : 365;
}

static int get_days_in_month(std::int32_t year, std::int32_t month)
{
    return is_leap_year(year) ? days_in_month_leap_year[month] : days_in_month[month];
}

static char const* get_month_name(std::int32_t month)
{
    return month < 12 ? month_names[month] : "";
}

time_point convert_time_point(std::chrono::system_clock::time_point const& value)
{
    std::time_t const time = std::chrono::system_clock::to_time_t(value);

    std::int64_t day_number = time / 86400L;
    std::int64_t time_of_day = time % 86400L;

    time_point result;

    result.hours = time_of_day / 3600L;
    result.minutes = time_of_day % 3600L / 60L;
    result.seconds = time_of_day % 60L;

    auto const fractional_seconds = value - std::chrono::time_point_cast<std::chrono::seconds>(value);
    result.microseconds = std::chrono::duration_cast<std::chrono::microseconds>(fractional_seconds).count();

    for(result.year = 1970;
        day_number >= get_days_in_year(result.year);
        day_number -= get_days_in_year(result.year), ++result.year)
    {
    }

    for(result.month = 1;
        day_number >= get_days_in_month(result.year, result.month - 1);
        day_number -= get_days_in_month(result.year, result.month - 1), ++result.month)
    {
    }

    result.month_name = get_month_name(result.month - 1);

    result.day = day_number + 1;

    return result;
}

}   // namespace detail
}   // namespace format
}   // namespace missio
