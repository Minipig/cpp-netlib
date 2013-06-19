// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_RESPONSE_INC__
#define __NETWORK_HTTP_V2_RESPONSE_INC__

#include <cstdint>
#include <map>
#include <string>
#include <future>
#include <network/uri.hpp>

namespace network {
namespace http {
namespace v2 {
  class response {

  public:

    typedef std::multimap<std::string, std::string> headers_type;
    typedef headers_type::const_iterator headers_iterator;
    typedef headers_type::const_iterator const_headers_iterator;

    response() { }

    std::uint16_t status() const;
    std::string status_message() const;
    const_headers_iterator headers_begin() const;
    const_headers_iterator end_begin() const;
    std::pair<headers_iterator, headers_iterator> headers() const;
    std::future<std::string> read_body(std::size_t length) const;

    // destination
    // source
    // add_header
    // remove_header
    // set_body
    // append_body
    // get_body

  private:

    struct impl;
    impl *pimpl_;


  };
} // namespace v2
} // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_RESPONSE_INC__
