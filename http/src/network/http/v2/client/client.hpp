// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_INC__
#define __NETWORK_HTTP_V2_CLIENT_INC__

#include <cstdint>

namespace network {
  namespace http {
    namespace v2 {
      class client {

      public:

	client() { }
	client(client const &) = delete;
	client(client &&) = delete;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_INC__
