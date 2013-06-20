// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __TTP_NETWORK_HTTP_V2_URL_INC__
#define __HTTP_NETWORK_HTTP_V2_URL_INC__

#include <network/uri.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class invalid_scheme : public std::runtime_error {

      public:

	virtual ~invalid_scheme() noexcept {}
	virtual const char *what() const noexcept {
	  return "invalid_scheme";
	}

      };

      class url {

      public:

	typedef uri::string_type string_type;
	typedef uri::iterator const_iterator;
	typedef uri::const_iterator iterator;
	typedef uri::value_type value_type;
	typedef uri::string_view string_view;

      public:

	url() {

	}

	url(const url &other)
	  : uri_(other.uri_) {

	}

	url(url &&other)
	  : uri_(other.uri_) {

	}

	url &operator = (url other) {
	  other.swap(*this);
	  return *this;
	}

	void swap(url &other) noexcept {
	  uri_.swap(other.uri_);
	}

	const_iterator begin() const {
	  return uri_.begin();
	}

	const_iterator end() const {
	  return uri_.end();
	}

	bool empty() const noexcept {
	  return uri_.empty();
	}

	bool is_absolute() const noexcept {
	  return uri_.is_absolute();
	}

      private:

	uri uri_;

      };
    } // namespace v2
  } // namespace http
} // namespace network


#endif // __HTTP_NETWORK_HTTP_V2_URL_INC__
