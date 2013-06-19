// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_BYTE_SOURCE_INC__
#define __NETWORK_HTTP_V2_BYTE_SOURCE_INC__

#include <cstdint>
#include <memory>

namespace network {
namespace http {
namespace v2 {
  class byte_source {

  public:

    virtual ~byte_source() {}

    virtual std::size_t read(std::string &source, std::size_t length) = 0;

  };

  class string_byte_source : public byte_source {

    explicit string_byte_source(std::string source);

    virtual ~string_byte_source() {}

    virtual std::size_t read(std::string &source, std::size_t length);

    std::string source_;

  };
} // namespace v2
} // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_BYTE_SOURCE_INC__
