// Copyright (C) 2013 by Glyn Matthews
// Copyright 2012 Dean Michael Berris <dberris@google.com>.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/protocol/http/response.hpp>

namespace http = network::http;

TEST(response_test, response_constructor) { http::response created; }

TEST(response_test, response_value_semantics) {
  http::response original;
  http::response copy(original);
  http::response assigned;
  assigned = original;
  ASSERT_TRUE(original == assigned);
  assigned.set_source("http://www.google.com/");
  ASSERT_TRUE(original != assigned);
  std::swap(assigned, copy);
  ASSERT_TRUE(assigned == original);
  ASSERT_TRUE(copy != original);
  ASSERT_TRUE(assigned != copy);
  original = copy;
  ASSERT_TRUE(original == copy);
}

struct multimap_inserter {
  void operator()(std::string const& name, std::string const& value) const {
    multimap_.insert(std::make_pair(name, value));
  }
  explicit multimap_inserter(std::multimap<std::string, std::string>& multimap)
      : multimap_(multimap) {}
  std::multimap<std::string, std::string>& multimap_;
};

TEST(response_test, response_setters_and_getters) {
  http::response response;
  response.set_source("http://www.google.com/");
  response.set_destination("127.0.0.1");
  response.append_header("Connection", "close");
  response.append_header("Content-Type", "text/plain");
  response.set_body("Hello, World!");
  response.set_status(200u);
  response.set_status_message("OK");
  response.set_version("HTTP/1.1");
  std::string source, destination, body, status_message, version;
  std::multimap<std::string, std::string> headers, expected_headers;
  expected_headers.insert(std::make_pair("Connection", "close"));
  expected_headers.insert(std::make_pair("Content-Type", "text/plain"));
  boost::uint16_t status;
  response.get_source(source);
  response.get_destination(destination);
  response.get_body(body);
  response.get_status_message(status_message);
  response.get_version(version);
  response.get_headers(multimap_inserter(headers));
  response.get_status(status);
  ASSERT_EQ(source, std::string("http://www.google.com/"));
  ASSERT_EQ(destination, std::string("127.0.0.1"));
  ASSERT_EQ(body, std::string("Hello, World!"));
  ASSERT_EQ(status, 200u);
  ASSERT_EQ(version, std::string("HTTP/1.1"));
  ASSERT_TRUE(expected_headers == headers);
}
