// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_REQUEST_OPTIONS_INC__
#define __NETWORK_HTTP_V2_REQUEST_OPTIONS_INC__

#include <cstdint>
#include <algorithm>

namespace network {
namespace http {
namespace v2 {
  class request_options {

  public:

    // default timeout is 30 seconds
    constexpr request_options()
      : resolve_timeout_(30000)
      , read_timeout_(30000)
      , total_timeout_(30000) { }

    request_options(request_options const &) = default;
    request_options(request_options &&) = default;

    void swap(request_options &other) noexcept {
      std::swap(resolve_timeout_, other.resolve_timeout_);
      std::swap(read_timeout_, other.read_timeout_);
      std::swap(total_timeout_, other.total_timeout_);
    }

    request_options &resolve_timeout(std::uint64_t resolve_timeout) noexcept {
      resolve_timeout_ = resolve_timeout;
      return *this;
    }

    constexpr std::uint64_t resolve_timeout() const noexcept {
      return resolve_timeout_;
    }

    request_options &read_timeout(std::uint64_t read_timeout) noexcept {
      read_timeout_ = read_timeout;
      return *this;
    }

    constexpr std::uint64_t read_timeout() const noexcept {
      return read_timeout_;
    }

    request_options &total_timeout(std::uint64_t total_timeout) noexcept {
      total_timeout_ = total_timeout;
      return *this;
    }

    constexpr std::uint64_t total_timeout() const noexcept {
      return total_timeout_;
    }

  private:

    std::uint64_t resolve_timeout_;
    std::uint64_t read_timeout_;
    std::uint64_t total_timeout_;

  };
} // namespace v2
} // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_REQUEST_OPTIONS_INC__
