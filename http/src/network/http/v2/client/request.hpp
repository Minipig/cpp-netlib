// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_REQUEST_INC__
#define __NETWORK_HTTP_V2_REQUEST_INC__

#include <cstdint>
#include <memory>
#include <string>
#include <network/http/v2/message_base.hpp>
#include <network/http/v2/url.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class byte_source {

      public:

	typedef message_base::string_type string_type;
	typedef message_base::size_type size_type;

	virtual ~byte_source() {}

	virtual size_type read(string_type &source, size_type length) = 0;

      };

      class string_byte_source : public byte_source {

      public:

	explicit string_byte_source(string_type source);

	virtual ~string_byte_source() {}

	virtual size_type read(string_type &source, size_type length);

      private:

	string_type source_;

      };

      class request {

	typedef byte_source::string_type string_type;

      public:

	request(url locator, std::shared_ptr<byte_source> source = nullptr)
	  : locator_(locator), source_(source) { }

	request(const request &other)
	  : locator_(other.locator_), source_(other.source_) { }

	request(request &&other) noexcept
	: locator_(std::move(other.locator_)), source_(std::move(other.source_)) { }

	request &operator = (request other) {
	  other.swap(*this);
	  return *this;
	}

	void swap(request &other) noexcept {
	  locator_.swap(other.locator_);
	  source_.swap(other.source_);
	}

	void set_destination(string_type destination);
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

	url locator_;
	std::shared_ptr<byte_source> source_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_REQUEST_INC__
