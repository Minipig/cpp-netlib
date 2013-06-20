// Copyright (C) 2013 by Glyn Matthews
// Copyright 2012 Dean Michael Berris <dberris@google.com>.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/protocol/http/request.hpp>
#include <network/protocol/http/message/wrappers.hpp>
#include <network/message/wrappers.hpp>
#include <network/protocol/http/algorithms/linearize.hpp>
#include <network/uri/uri_io.hpp>

namespace http = network::http;
namespace net = network;

TEST(message_test, request_construction) {
  http::request request;
  http::request other(request);
}

TEST(message_test, request_swap) {
  network::uri tmp_uri;
  network::uri request_uri("http://www.google.com/");
  network::uri other_uri("http://www.google.it/");
  http::request request(request_uri);
  http::request other(other_uri);

  request.swap(other);

  request.get_uri(tmp_uri);
  ASSERT_EQ(tmp_uri, other_uri);
  other.get_uri(tmp_uri);
  ASSERT_EQ(tmp_uri, request_uri);
}

TEST(message_test, request_value_semantics) {
  // First let's default construct a request.
  http::request original;
  // Next let's copy the request.
  http::request copy(original);
  // Next let's compare the requests.
  ASSERT_TRUE(original == copy);
  // Next let's assign the original to another request.
  http::request assigned;
  assigned = original;
  // Next we modify the assigned object and make sure it's not the same as the
  // original.
  assigned.set_uri("http://www.google.com/");
  assigned.set_source("127.0.0.1");
  assigned.set_destination("http://www.google.com/");
  assigned.append_header("Connection", "close");
  assigned.set_body("Hello, world!");
  ASSERT_TRUE(original != assigned);
  // Next we swap the assigned and copy.
  std::swap(assigned, copy);
  ASSERT_TRUE(copy != assigned);
  ASSERT_TRUE(copy != original);
  ASSERT_TRUE(original == assigned);
}

TEST(message_test, request_uri) {
  http::request request;
  request.set_uri("http://www.google.com/");
  http::request other(request);
  std::string original, copied;
  request.get_uri(original);
  other.get_uri(copied);
  ASSERT_EQ(std::string("http://www.google.com/"), original);
  ASSERT_EQ(original, copied);

  // Now we test the bare uri instance with accessing using the request
  // convenience wrapper.
  network::uri uri_;
  request.get_uri(uri_);
  std::string host_ = http::host(request);
  ASSERT_EQ(std::string("www.google.com"), host_);
  std::string gotten_host(*uri_.host());
  ASSERT_EQ(gotten_host, host_);
  ASSERT_EQ(std::string("www.google.com"), gotten_host);
}

TEST(message_test, request_url_constructor) {
  http::request request("http://www.google.com/");
  http::request other;
  other.set_uri("http://www.google.com/");
  network::uri original, other_uri;
  request.get_uri(original);
  other.get_uri(other_uri);
  ASSERT_EQ(original, other_uri);

  // Now test the directives..
  network::uri directive_original = http::uri(request);
  ASSERT_EQ(original, directive_original);
}

TEST(message_test, request_basics) {
  http::request request;
  request.set_uri("http://www.google.com/");
  request.set_source("127.0.0.1");
  request.set_destination("destination!");
  request.append_header("X-Referer", "http://cpp-netlib.github.com/");
  request.append_header("Connection", "close");
  request.append_body("The quick brown fox jumps over the lazy dog!");

  network::uri uri_;
  std::string source_, destination_, body_;
  net::headers_wrapper::container_type const& headers_ = headers(request);
  request.get_uri(uri_);
  request.get_source(source_);
  request.get_destination(destination_);
  request.get_body(body_);

  ASSERT_EQ(uri_.string(), std::string("http://www.google.com/"));
  ASSERT_EQ(source_, std::string("127.0.0.1"));
  ASSERT_EQ(destination_, std::string("destination!"));
  ASSERT_EQ(body_, std::string("The quick brown fox jumps over the lazy dog!"));
  ASSERT_TRUE(!boost::empty(headers_));
}

TEST(message_test, linearize_request) {
  http::request request("http://www.boost.org");
  // TODO: Actually specify the expected output.
  linearize(request, "GET", 1, 0, std::ostream_iterator<char>(std::cout));
  linearize(request, "GET", 2, 1, std::ostream_iterator<char>(std::cout));
}
