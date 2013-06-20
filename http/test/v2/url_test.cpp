// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/v2/url.hpp>

TEST(url_test, url_constructor) {
  network::http::v2::url instance;
  ASSERT_TRUE(instance.empty());
}

