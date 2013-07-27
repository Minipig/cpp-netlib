// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_URL_INC__
#define __NETWORK_HTTP_V2_URL_INC__

#include <network/uri.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/as_literal.hpp>

namespace network {
  namespace http {
    namespace v2 {
      class scheme_not_http : public std::runtime_error {

      public:

	scheme_not_http() : std::runtime_error("scheme_not_http") {}
	virtual ~scheme_not_http() noexcept {}

      };

      class url {

      public:

	typedef uri::string_type string_type;
	typedef uri::iterator const_iterator;
	typedef uri::const_iterator iterator;
	typedef uri::value_type value_type;
	typedef uri::string_view string_view;

      public:

	url() {	}

	template <class Source>
	url(const Source &source)
	  : uri_(source) {
	  if (auto scheme_ = uri_.scheme()) {
	    if (!boost::equal(boost::as_literal("http"), *scheme_) &&
		!boost::equal(boost::as_literal("https"), *scheme_) &&
		!boost::equal(boost::as_literal("shttp"), *scheme_)) {
	      throw scheme_not_http();
	    }
	  }
	}

	url(const url &other)
	  : uri_(other.uri_) { }

	url(url &&other) noexcept
	: uri_(std::move(other.uri_)) { }

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

	boost::optional<string_view> user_info() const {
	  return uri_.user_info();
	}

	boost::optional<string_view> host() const {
	  return uri_.host();
	}

	boost::optional<string_view> port() const {
	  return uri_.port();
	}

	boost::optional<string_view> path() const {
	  return uri_.path();
	}

	boost::optional<string_view> query() const {
	  return uri_.query();
	}

	boost::optional<string_view> fragment() const {
	  return uri_.fragment();
	}

	boost::optional<string_view> authority() const {
	  return uri_.authority();
	}

	std::string string() const {
	  return uri_.string();
	}

	bool empty() const noexcept {
	  return uri_.empty();
	}

	bool is_absolute() const noexcept {
	  return uri_.is_absolute();
	}

	url normalize(uri_comparison_level level) const {
	  return url(uri_.normalize(level));
	  // if scheme-specific
	  //   normalize query arguments in alphanumeric order
	}

	url make_reference(const url &other, uri_comparison_level level) const {
	  return url(uri_.make_reference(other.uri_, level));
	}

	url resolve(const url &other, uri_comparison_level level) const {
	  return url(uri_.resolve(other.uri_, level));
	}

	int compare(const url &other, uri_comparison_level level) const noexcept {
	  int result = uri_.compare(other.uri_, level);
	  // if result == 0 and scheme-specific
	  //   compare query arguments
	  return result;
	}

	uri to_uri() const {
	  return uri_;
	}

      private:

	uri uri_;

      };
    } // namespace v2
  } // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_URL_INC__
