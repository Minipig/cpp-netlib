// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/v2/url.hpp>

namespace http = network::http::v2;

TEST(url_test, url_constructor) {
  http::url instance;
  ASSERT_TRUE(instance.empty());
}

TEST(url_test, construct_url_from_char_array) {
  ASSERT_NO_THROW(http::url("http://www.example.com/"));
}

TEST(url_test, construct_https_url_from_char_array) {
  ASSERT_NO_THROW(http::url("https://www.example.com/"));
}

TEST(url_test, construct_shttp_url_from_char_array) {
  ASSERT_NO_THROW(http::url("shttp://www.example.com/"));
}
