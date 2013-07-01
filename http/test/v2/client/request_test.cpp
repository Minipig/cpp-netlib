// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/v2/client/request.hpp>

TEST(request_test, request_constructor_url) {
  ASSERT_NO_THROW(network::http::v2::request(network::uri("http://www.example.com/")));
}

TEST(request_test, request_constructor_https_url) {
  ASSERT_NO_THROW(network::http::v2::request(network::uri("https://www.example.com/")));
}

//TEST(request_test, request_constructor_invalid_url) {
//  ASSERT_THROW(network::http::v2::invalid_scheme,
//	       network::http::v2::request(network::uri("mailto:john.doe@example.com")));
//}
