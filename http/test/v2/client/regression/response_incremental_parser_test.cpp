// Copyright (C) 2013 by Glyn Matthews
// Copyright Dean Michael Berris 2010.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/protocol/http/parser/incremental.hpp>
#include <boost/range.hpp>
#include <boost/logic/tribool.hpp>
#include <string>
#include <iostream>

/** Synopsis
 *
 * Test for HTTP Response Incremental Parser
 * -----------------------------------------
 *
 * In this test we fully intend to specify how an incremental
 * HTTP Response parser should be used. This defines the bare
 * minimum implementation for an Incremental Parser concept,
 * and shall follow an interface that puts a premium on simplicity.
 *
 * The motivation for coming up with a re-startable stateful
 * incremental parser comes from the requirement in the asynchronous
 * HTTP client implementation that allows for parsing an HTTP
 * response as the data comes in. By being able to process some
 * parts of the message ahead of others, we are allowed to set
 * the promise values bound to futures that the users of the client
 * would be waiting on.
 *
 * The basic interface that we're looking for is a means of providing:
 *   - a range of input
 *   - a means of resetting the parser's state
 *   - a means of initializing the parser to a given state
 *   - a parse_until function that takes a state as parameter and
 *     a range from which the parser will operate on, returns
 *     a tuple of a boost::logic::tribool and a resulting range
 *
 * One of the possible implementations can use the Boost.MSM library
 * to create the state machine. The test however does not specify what
 * implementation should be used, but rather that the interface and the
 * semantics are according to expectations.
 *
 * Date: September 9, 2010
 * Author: Dean Michael Berris <dberris@google.com>
 */

namespace logic = boost::logic;
namespace fusion = boost::fusion;
using namespace network::http;

TEST(response_test, incremental_parser_constructor) {
  response_parser p;  // default constructible
}

/** In this test we want to be able to parse incrementally a
 *  range passed in as input, and specify to the parser that
 *  it should stop when we reach a certain state. In this case
 *  we want it to parse until it either finds the HTTP version
 *  or there is an error encountered.
 */
TEST(response_test, incremental_parser_parse_http_version) {
  response_parser p;  // default constructible
  logic::tribool parsed_ok = false;
  typedef response_parser response_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  range_type result_range;

  std::string valid_http_version = "HTTP/1.0 ";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_version_done,
                    valid_http_version);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(!boost::empty(result_range));
  std::string parsed(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;
  p.reset();
  valid_http_version = "HTTP/1.1 ";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_version_done,
                    valid_http_version);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(!boost::empty(result_range));
  parsed.assign(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;

  p.reset();
  std::string invalid_http_version = "HTTP 1.0";
  parsed_ok = logic::indeterminate;
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_version_done,
                    invalid_http_version);
  ASSERT_EQ(parsed_ok, false);
  parsed.assign(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;

  p.reset();
  valid_http_version = "HTTP/0.9 ";
  parsed_ok = logic::indeterminate;
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_version_done,
                    valid_http_version);
  ASSERT_EQ(parsed_ok, true);
  parsed.assign(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;
}

/** In this test we then want to check that we can parse a status
 *  string right after the version string. We should expect that
 *  the parser doesn't do any conversions from string to integer
 *  and outsource that part to the user of the parser.
 */
TEST(response_test, incremental_parser_parse_status) {
  typedef response_parser response_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  // We want to create a parser that has been initialized to a specific
  // state. In this case we assume that the parser has already parsed
  // the version part of the HTTP Response.
  response_parser_type p(response_parser_type::http_version_done);

  std::string valid_status = "200 ";
  logic::tribool parsed_ok;
  range_type result_range;
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_status_done, valid_status);
  ASSERT_EQ(parsed_ok, true);
  std::string parsed = std::string(boost::begin(result_range),
                                   boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;

  p.reset(response_parser_type::http_version_done);
  std::string invalid_status = "200x ";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_status_done, invalid_status);
  ASSERT_EQ(parsed_ok, false);
  parsed = std::string(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;
}

/** In this test then we get the rest of the first line of the HTTP
 *  Response, and treat it as the status message.
 */
TEST(response_test, incremental_parser_parse_status_message) {
  typedef response_parser response_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  response_parser_type p(response_parser_type::http_status_done);

  std::string valid_status_message = "OK\r\nServer: Foo";
  logic::tribool parsed_ok;
  range_type result_range;
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_status_message_done,
                    valid_status_message);
  ASSERT_EQ(parsed_ok, true);
  std::string parsed = std::string(boost::begin(result_range),
                                   boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;

  p.reset(response_parser_type::http_status_done);
  valid_status_message = "OK\r\n";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_status_message_done,
                    valid_status_message);
  ASSERT_EQ(parsed_ok, true);
  parsed = std::string(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;

  p.reset(response_parser_type::http_status_done);
  valid_status_message = "Internal Server Error\r\n";
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_status_message_done,
                    valid_status_message);
  ASSERT_EQ(parsed_ok, true);
  parsed = std::string(boost::begin(result_range), boost::end(result_range));
  std::cout << "PARSED: " << parsed << " state=" << p.state() << std::endl;
}

/** This test specifices how one-line-per-header parsing happens incrementally.
 */
TEST(response_test, incremental_parser_parse_header_lines) {
  typedef response_parser response_parser_type;
  typedef boost::iterator_range<std::string::const_iterator> range_type;
  response_parser_type p(response_parser_type::http_status_message_done);

  std::string valid_headers =
      "Server: Foo\r\nContent-Type: application/json\r\n\r\n";
  logic::tribool parsed_ok;
  range_type result_range;
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_header_line_done, valid_headers);
  ASSERT_EQ(parsed_ok, true);
  std::string parsed1 = std::string(boost::begin(result_range),
                                    boost::end(result_range));
  std::cout << "PARSED: " << parsed1 << " state=" << p.state() << std::endl;
  p.reset(response_parser_type::http_status_message_done);
  std::string::const_iterator end = valid_headers.end();
  valid_headers.assign(boost::end(result_range), end);
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_header_line_done, valid_headers);
  ASSERT_EQ(parsed_ok, true);
  std::string parsed2 = std::string(boost::begin(result_range),
                                    boost::end(result_range));
  std::cout << "PARSED: " << parsed2 << " state=" << p.state() << std::endl;
  valid_headers.assign(boost::end(result_range), end);
  p.reset(response_parser_type::http_status_message_done);
  fusion::tie(parsed_ok, result_range) =
      p.parse_until(response_parser_type::http_headers_done, valid_headers);
  ASSERT_EQ(parsed_ok, true);
  ASSERT_TRUE(parsed1 != parsed2);
}

