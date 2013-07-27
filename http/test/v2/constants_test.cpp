// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/v2/constants.hpp>

// methods
TEST(constants_test, get)
{
  ASSERT_EQ("GET", network::http::v2::methods::get());
}

TEST(constants_test, post)
{
  ASSERT_EQ("POST", network::http::v2::methods::post());
}

TEST(constants_test, put)
{
  ASSERT_EQ("PUT", network::http::v2::methods::put());
}

TEST(constants_test, delete_)
{
  ASSERT_EQ("DELETE", network::http::v2::methods::delete_());
}

TEST(constants_test, head)
{
  ASSERT_EQ("HEAD", network::http::v2::methods::head());
}

TEST(constants_test, options)
{
  ASSERT_EQ("OPTIONS", network::http::v2::methods::options());
}

TEST(constants_test, trace)
{
  ASSERT_EQ("TRACE", network::http::v2::methods::trace());
}

TEST(constants_test, connect)
{
  ASSERT_EQ("CONNECT", network::http::v2::methods::connect());
}

TEST(constants_test, merge)
{
  ASSERT_EQ("MERGE", network::http::v2::methods::merge());
}

TEST(constants_test, patch)
{
  ASSERT_EQ("PATCH", network::http::v2::methods::patch());
}
