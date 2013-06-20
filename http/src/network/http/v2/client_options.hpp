// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CLIENT_OPTIONS_INC__
#define __NETWORK_HTTP_V2_CLIENT_OPTIONS_INC__

#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>

namespace network {
namespace http {
namespace v2 {
  class client_options {

  public:

    // default timeout is 30 seconds
    client_options()
      : follow_redirects_(false)
      , cache_resolved_(false)
      , use_proxy_(false)
      , timeout_(30000) { }

    client_options(client_options const &) = default;
    client_options(client_options &&) = default;

    client_options &operator = (client_options other) {
      other.swap(*this);
      return *this;
    }

    void swap(client_options &other) noexcept {
      std::swap(follow_redirects_, other.follow_redirects_);
      std::swap(cache_resolved_, other.cache_resolved_);
      std::swap(use_proxy_, other.use_proxy_);
      std::swap(timeout_, other.timeout_);
      std::swap(openssl_certificate_paths_, other.openssl_certificate_paths_);
      std::swap(openssl_verify_paths_, other.openssl_verify_paths_);
    }

    client_options &follow_redirects(bool follow_redirects) noexcept {
      follow_redirects_ = follow_redirects;
      return *this;
    }

    bool follow_redirects() const noexcept {
      return follow_redirects_;
    }

    client_options &cache_resolved(bool cache_resolved) noexcept {
      cache_resolved_ = cache_resolved;
      return *this;
    }

    bool cache_resolved() const noexcept {
      return cache_resolved_;
    }

    client_options &use_proxy(bool use_proxy) noexcept {
      use_proxy_ = use_proxy;
      return *this;
    }

    bool use_proxy() const noexcept {
      return use_proxy_;
    }

    client_options &timeout(std::chrono::milliseconds timeout) noexcept {
      timeout_ = timeout;
      return *this;
    }

    std::chrono::milliseconds timeout() const noexcept {
      return timeout_;
    }

    std::vector<std::string> openssl_certificate_paths() const {
      return openssl_certificate_paths_;
    }

    std::vector<std::string> openssl_verify_paths() const {
      return openssl_verify_paths_;
    }

  private:

    bool follow_redirects_;
    bool cache_resolved_;
    bool use_proxy_;
    std::chrono::milliseconds timeout_;
    std::vector<std::string> openssl_certificate_paths_;
    std::vector<std::string> openssl_verify_paths_;

  };
} // namespace v2
} // namespace http
} // namespace network

#endif // __NETWORK_HTTP_V2_CLIENT_OPTIONS_INC__
