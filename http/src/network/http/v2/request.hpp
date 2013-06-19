// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_REQUEST_INC__
#define __NETWORK_HTTP_V2_REQUEST_INC__

#include <cstdint>
#include <memory>
#include <network/uri.hpp>
#include <network/http/v2/byte_source.hpp>

namespace network {
namespace http {
namespace v2 {
  class request {

  public:

    request(uri locator, std::shared_ptr<byte_source> = nullptr)
      : locator_(locator) { }

    // destination
    // source
    // add_header
    // remove_header
    // clear_headers
    // set_body
    // append_body
    // get_body

    // method
    // status
    // status_message
    // uri
    // version

    uri locator_;
    std::shared_ptr<byte_source> source_;

  };
} // namespace v2
} // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_REQUEST_INC__
