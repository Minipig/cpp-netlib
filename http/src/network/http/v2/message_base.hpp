// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_MESSAGE_BASE_INC__
#define __NETWORK_HTTP_V2_MESSAGE_BASE_INC__

#include <network/config.hpp>
#include <network/uri.hpp>
#include <string>
#include <functional>

namespace network {
  namespace http {
    class message_base {

    public:

      typedef std::string string_type;
      typedef string_type::size_type size_type;

      message_base() NETWORK_DEFAULTED_FUNCTION;

      message_base(const message_base &) NETWORK_DELETED_FUNCTION;

      message_base &operator = (const message_base &) NETWORK_DELETED_FUNCTION;

      virtual ~message_base() NETWORK_NOEXCEPT = 0;

      // Mutators
      virtual void set_destination(string_type destination) = 0;
      virtual void set_source(string_type source) = 0;
      virtual void append_header(string_type name, string_type value) = 0;
      virtual void remove_headers(string_type name) = 0;
      virtual void clear_headers() = 0;
      virtual void set_body(std::string body) = 0;
      virtual void append_body(std::string data) = 0;

      // Accessors
      virtual string_type destination() const = 0;
      virtual string_type source() = 0;
      virtual string_type headers(std::function<void (string_type, string_type)> inserter) const = 0;
      virtual string_type headers(std::function<bool (string_type, string_type)> predicate,
				  std::function<void (string_type, string_type)> inserter) const = 0;
      virtual string_type body() const = 0;
      virtual void body(std::function<void (string_type::const_iterator, size_type)> chunk_reader,
			size_type size) = 0;

    };
  } // namespace v2
} // namespace network


#endif // __NETWORK_HTTP_V2_MESSAGE_BASE_INC__
