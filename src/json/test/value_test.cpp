//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/json.hpp>

// BOOST headers
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(json_value_test_suite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    missio::json::value value1;

    BOOST_CHECK_EQUAL(value1.variant().which(), 0);

    missio::json::null null;
    missio::json::value value2(null);

    BOOST_CHECK_EQUAL(value2.variant().which(), 0);

    missio::json::real real(0.0);
    missio::json::value value3(real);

    BOOST_CHECK_EQUAL(value3.variant().which(), 1);

    missio::json::integer integer(0);
    missio::json::value value4(integer);

    BOOST_CHECK_EQUAL(value4.variant().which(), 2);

    missio::json::boolean boolean(false);
    missio::json::value value5(boolean);

    BOOST_CHECK_EQUAL(value5.variant().which(), 3);

    missio::json::string string;
    missio::json::value value6(string);

    BOOST_CHECK_EQUAL(value6.variant().which(), 4);

    missio::json::array array;
    missio::json::value value7(array);

    BOOST_CHECK_EQUAL(value7.variant().which(), 5);

    missio::json::object object;
    missio::json::value value8(object);

    BOOST_CHECK_EQUAL(value8.variant().which(), 6);
}

BOOST_AUTO_TEST_CASE(construct_with_compatible_types_test)
{
    missio::json::value value1(float(0.0));
    BOOST_CHECK_EQUAL(value1.variant().which(), 1);

    missio::json::value value2(short(0));
    BOOST_CHECK_EQUAL(value2.variant().which(), 2);

    missio::json::value value3(std::string(""));
    BOOST_CHECK_EQUAL(value3.variant().which(), 4);

    missio::json::value value4(std::wstring(L""));
    BOOST_CHECK_EQUAL(value4.variant().which(), 4);
}

BOOST_AUTO_TEST_CASE(assignment_changes_type_test)
{
    missio::json::value value;

    value = missio::json::real(0.0);
    BOOST_CHECK_EQUAL(value.variant().which(), 1);

    value = missio::json::integer(0);
    BOOST_CHECK_EQUAL(value.variant().which(), 2);

    value = missio::json::boolean(false);
    BOOST_CHECK_EQUAL(value.variant().which(), 3);

    value = missio::json::string("");
    BOOST_CHECK_EQUAL(value.variant().which(), 4);

    value = missio::json::array();
    BOOST_CHECK_EQUAL(value.variant().which(), 5);

    value = missio::json::object();
    BOOST_CHECK_EQUAL(value.variant().which(), 6);

    value = missio::json::null();
    BOOST_CHECK_EQUAL(value.variant().which(), 0);
}

BOOST_AUTO_TEST_CASE(non_const_get_changes_type_test)
{
    missio::json::value value;

    value.get<missio::json::real>();
    BOOST_CHECK_EQUAL(value.variant().which(), 1);

    value.get<missio::json::integer>();
    BOOST_CHECK_EQUAL(value.variant().which(), 2);

    value.get<missio::json::boolean>();
    BOOST_CHECK_EQUAL(value.variant().which(), 3);

    value.get<missio::json::string>();
    BOOST_CHECK_EQUAL(value.variant().which(), 4);

    value.get<missio::json::array>();
    BOOST_CHECK_EQUAL(value.variant().which(), 5);

    value.get<missio::json::object>();
    BOOST_CHECK_EQUAL(value.variant().which(), 6);

    value.get<missio::json::null>();
    BOOST_CHECK_EQUAL(value.variant().which(), 0);
}

BOOST_AUTO_TEST_CASE(index_operator_changes_type_test)
{
    missio::json::value value;

    value[0] = missio::json::null_value;
    BOOST_CHECK_EQUAL(value.variant().which(), 5);

    value["key"] = missio::json::null_value;
    BOOST_CHECK_EQUAL(value.variant().which(), 6);
}

BOOST_AUTO_TEST_CASE(comparison_operators_test)
{
    missio::json::value value1;
    missio::json::value value2;

    BOOST_CHECK_LE(value1, value2);
    BOOST_CHECK_GE(value1, value2);
    BOOST_CHECK_EQUAL(value1, value2);

    value1 = missio::json::integer(1);

    BOOST_CHECK_GE(value1, value2);
    BOOST_CHECK_GT(value1, value2);
    BOOST_CHECK_NE(value1, value2);

    value2 = missio::json::integer(2);

    BOOST_CHECK_LE(value1, value2);
    BOOST_CHECK_LT(value1, value2);
    BOOST_CHECK_NE(value1, value2);
}

BOOST_AUTO_TEST_CASE(null_value_test)
{
    missio::json::value value;  // null is default

    BOOST_CHECK(value.is<missio::json::null>());

    BOOST_CHECK_EQUAL(value.get<missio::json::null>(), missio::json::null_value);
    BOOST_CHECK_EQUAL(value.as<missio::json::null>(), missio::json::null_value);

    // test invalid conversions

    BOOST_CHECK(!value.is<int>());
    BOOST_CHECK(!value.is<bool>());
    BOOST_CHECK(!value.is<double>());
    BOOST_CHECK(!value.is<missio::json::array>());
    BOOST_CHECK(!value.is<missio::json::object>());
    BOOST_CHECK(!value.is<missio::json::string>());

    BOOST_CHECK_THROW(value.as<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(integer_value_test)
{
    missio::json::value value = 42;

    BOOST_CHECK(value.is<char>());
    BOOST_CHECK(value.is<short>());
    BOOST_CHECK(value.is<int>());
    BOOST_CHECK(value.is<long>());
    BOOST_CHECK(value.is<double>());    // convertible
    BOOST_CHECK(value.is<bool>());      // convertible

    BOOST_CHECK_EQUAL(value.get<missio::json::integer>(), 42);

    BOOST_CHECK_EQUAL(value.as<char>(), 42);
    BOOST_CHECK_EQUAL(value.as<short>(), 42);
    BOOST_CHECK_EQUAL(value.as<int>(), 42);
    BOOST_CHECK_EQUAL(value.as<long>(), 42);
    BOOST_CHECK_CLOSE(value.as<double>(), 42.0, 0.000001);
    BOOST_CHECK_EQUAL(value.as<bool>(), true);

    // test invalid conversions

    BOOST_CHECK(!value.is<missio::json::null>());
    BOOST_CHECK(!value.is<missio::json::array>());
    BOOST_CHECK(!value.is<missio::json::object>());
    BOOST_CHECK(!value.is<missio::json::string>());

    BOOST_CHECK_THROW(value.as<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::string>(), missio::json::exception);
}

// should be defined in global scope due to GCC error
enum numbers
{
    zero,
    one,
    two,
    three
};

BOOST_AUTO_TEST_CASE(enum_value_test)
{
    missio::json::value value = two;

    BOOST_CHECK(value.is<char>());
    BOOST_CHECK(value.is<short>());
    BOOST_CHECK(value.is<int>());
    BOOST_CHECK(value.is<long>());
    BOOST_CHECK(value.is<double>());    // convertible
    BOOST_CHECK(value.is<bool>());      // convertible

    BOOST_CHECK_EQUAL(value.get<missio::json::integer>(), 2);

    BOOST_CHECK(value.as<numbers>() == two);
    BOOST_CHECK_EQUAL(value.as<char>(), 2);
    BOOST_CHECK_EQUAL(value.as<short>(), 2);
    BOOST_CHECK_EQUAL(value.as<int>(), 2);
    BOOST_CHECK_EQUAL(value.as<long>(), 2);
    BOOST_CHECK_CLOSE(value.as<double>(), 2.0, 0.000001);
    BOOST_CHECK_EQUAL(value.as<bool>(), true);

    // test invalid conversions

    BOOST_CHECK(!value.is<missio::json::null>());
    BOOST_CHECK(!value.is<missio::json::array>());
    BOOST_CHECK(!value.is<missio::json::object>());
    BOOST_CHECK(!value.is<missio::json::string>());

    BOOST_CHECK_THROW(value.as<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(real_value_test)
{
    missio::json::value value = 3.141592;

    BOOST_CHECK(value.is<float>());
    BOOST_CHECK(value.is<double>());
    BOOST_CHECK(value.is<int>());       // convertible
    BOOST_CHECK(value.is<bool>());      // convertible

    BOOST_CHECK_CLOSE(value.get<missio::json::real>(), 3.141592, 0.000001);

    BOOST_CHECK_CLOSE(value.as<float>(), 3.141592, 0.000001);
    BOOST_CHECK_CLOSE(value.as<double>(), 3.141592, 0.000001);
    BOOST_CHECK_EQUAL(value.as<int>(), 3);
    BOOST_CHECK_EQUAL(value.as<bool>(), true);

    // test invalid conversions

    BOOST_CHECK(!value.is<missio::json::null>());
    BOOST_CHECK(!value.is<missio::json::array>());
    BOOST_CHECK(!value.is<missio::json::object>());
    BOOST_CHECK(!value.is<missio::json::string>());

    BOOST_CHECK_THROW(value.as<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(boolean_value_test)
{
    missio::json::value value = true;

    BOOST_CHECK(value.is<bool>());
    BOOST_CHECK(value.is<int>());       // convertible
    BOOST_CHECK(value.is<double>());    // convertible

    BOOST_CHECK_EQUAL(value.get<missio::json::boolean>(), true);

    BOOST_CHECK_EQUAL(value.as<bool>(), true);
    BOOST_CHECK_EQUAL(value.as<int>(), 1);
    BOOST_CHECK_CLOSE(value.as<double>(), 1.0, 0.000001);

    // test invalid conversions

    BOOST_CHECK(!value.is<missio::json::null>());
    BOOST_CHECK(!value.is<missio::json::array>());
    BOOST_CHECK(!value.is<missio::json::object>());
    BOOST_CHECK(!value.is<missio::json::string>());

    BOOST_CHECK_THROW(value.as<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(string_value_test)
{
    missio::json::value value = missio::json::string("string");

    BOOST_CHECK(value.is<missio::json::string>());
    BOOST_CHECK(value.is<std::string>());
    BOOST_CHECK(value.is<std::wstring>());

    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "string");

    BOOST_CHECK_EQUAL(value.as<missio::json::string>(), "string");
    BOOST_CHECK_EQUAL(value.as<std::string>(), "string");
    BOOST_CHECK(value.as<std::wstring>() == L"string");

    // test invalid conversions

    BOOST_CHECK(!value.is<int>());
    BOOST_CHECK(!value.is<bool>());
    BOOST_CHECK(!value.is<double>());
    BOOST_CHECK(!value.is<missio::json::null>());
    BOOST_CHECK(!value.is<missio::json::array>());
    BOOST_CHECK(!value.is<missio::json::object>());

    BOOST_CHECK_THROW(value.as<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::object>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(literal_value_test)
{
    missio::json::value value = "ascii";

    BOOST_CHECK(value.is<missio::json::string>());
    BOOST_CHECK(value.is<std::string>());
    BOOST_CHECK(value.is<std::wstring>());

    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "ascii");

    BOOST_CHECK_EQUAL(value.as<missio::json::string>(), "ascii");
    BOOST_CHECK_EQUAL(value.as<std::string>(), "ascii");
    BOOST_CHECK(value.as<std::wstring>() == L"ascii");
}

BOOST_AUTO_TEST_CASE(wide_literal_value_test)
{
    missio::json::value value = L"wide";

    BOOST_CHECK(value.is<missio::json::string>());
    BOOST_CHECK(value.is<std::string>());
    BOOST_CHECK(value.is<std::wstring>());

    BOOST_CHECK_EQUAL(value.get<missio::json::string>(), "wide");

    BOOST_CHECK_EQUAL(value.as<missio::json::string>(), "wide");
    BOOST_CHECK_EQUAL(value.as<std::string>(), "wide");
    BOOST_CHECK(value.as<std::wstring>() == L"wide");
}

BOOST_AUTO_TEST_CASE(array_value_test)
{
    missio::json::value value = missio::json::array();

    BOOST_CHECK(value.is<missio::json::array>());

    BOOST_CHECK_EQUAL(value.get<missio::json::array>(), missio::json::array());
    BOOST_CHECK_EQUAL(value.as<missio::json::array>(), missio::json::array());

    // test invalid conversions

    BOOST_CHECK_THROW(value.as<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::object>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_CASE(object_value_test)
{
    missio::json::value value = missio::json::object();

    BOOST_CHECK(value.is<missio::json::object>());

    BOOST_CHECK_EQUAL(value.get<missio::json::object>(), missio::json::object());
    BOOST_CHECK_EQUAL(value.as<missio::json::object>(), missio::json::object());

    // test invalid conversions

    BOOST_CHECK_THROW(value.as<int>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<bool>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<double>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::null>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::array>(), missio::json::exception);
    BOOST_CHECK_THROW(value.as<missio::json::string>(), missio::json::exception);
}

BOOST_AUTO_TEST_SUITE_END()
