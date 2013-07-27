// Copyright (C) 2013 by Glyn Matthews
// Copyright 2010 Dean Michael Berris.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/protocol/http/server/request_parser.hpp>
#include <network/tags.hpp>
#include <boost/range.hpp>
#include <boost/logic/tribool.hpp>
#include <string>
#include <iostream>

/** Synopsis
 *
 *  Test for the HTTP Request Incremental Parser
 *  --------------------------------------------
 *
 *  In this test we fully intend to specify how an incremental HTTP request
 *  parser should be used. This follows the HTTP Response Incremental Parser
 *  example, and models the Incremental Parser Concept.
 *
 */

namespace tags = boost::network::tags;
namespace logic = boost::logic;
namespace fusion = boost::fusion;
using namespace boost::network::http;

TEST(request_test, incremental_parser_constructor) {
  request_parser<tags::default_string> p;  // default constructible
}

TEST(request_test, incremental_parser_parse_http_method) {
  request_parser<tags::default_string> p;
  logic::tribool parsed_ok = false;
  typedef request_parser<tags::default_string> request_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  range_type result_range;

  std::string valid_http_method = "GET ";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::method_done, valid_http_method);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(!boost::empty(result_range));
  std::string parsed(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;

  std::string invalid_http_method = "get ";
  p.reset();
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::method_done, invalid_http_method);
  ASSERT_EQ(parsed_ok, false);
  parsed.assign(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;
}

TEST(request_test, incremental_parser_parse_http_uri) {
  request_parser<tags::default_string> p;
  logic::tribool parsed_ok = false;
  typedef request_parser<tags::default_string> request_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  range_type result_range;

  std::string valid_http_request = "GET / HTTP/1.1\r\n";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::uri_done, valid_http_request);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(!boost::empty(result_range));
  std::string parsed(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;

  std::string invalid_http_request = "GET /\t HTTP/1.1\r\n";
  p.reset();
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::uri_done, invalid_http_request);
  ASSERT_EQ(parsed_ok, false);
  parsed.assign(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;
}

TEST(request_test, incremental_parser_parse_http_version) {
  request_parser<tags::default_string> p;
  logic::tribool parsed_ok = false;
  typedef request_parser<tags::default_string> request_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  range_type result_range;

  std::string valid_http_request = "GET / HTTP/1.1\r\n";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::version_done, valid_http_request);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(!boost::empty(result_range));
  std::string parsed(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;

  std::string invalid_http_request = "GET / HTTP 1.1\r\n";
  p.reset();
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::version_done, invalid_http_request);
  ASSERT_EQ(parsed_ok, false);
  parsed.assign(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;
}

TEST(request_test, incremental_parser_parse_http_headers) {
  request_parser<tags::default_string> p;
  logic::tribool parsed_ok = false;
  typedef request_parser<tags::default_string> request_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  range_type result_range;

  std::string valid_http_request =
      "GET / HTTP/1.1\r\nHost: cpp-netlib.org\r\n\r\n";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::headers_done, valid_http_request);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(!boost::empty(result_range));
  std::string parsed(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;

  valid_http_request =
      "GET / HTTP/1.1\r\nHost: cpp-netlib.org\r\nConnection: close\r\n\r\n";
  p.reset();
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(request_parser_type::headers_done, valid_http_request);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(!boost::empty(result_range));
  parsed.assign(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " [state:" << p.state() << "] "
            << std::endl;
}

