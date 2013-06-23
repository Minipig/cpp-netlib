// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/http/v2/client_options.hpp>

TEST(client_options_test, default_options_follow_redirects) {
  network::http::v2::client_options opts;
  ASSERT_FALSE(opts.follow_redirects());
}

TEST(client_options_test, default_options_cache_resolved) {
  network::http::v2::client_options opts;
  ASSERT_FALSE(opts.cache_resolved());
}

TEST(client_options_test, default_options_use_proxy) {
  network::http::v2::client_options opts;
  ASSERT_FALSE(opts.use_proxy());
}

TEST(client_options, default_options_openssl_certificate_paths) {
  network::http::v2::client_options opts;
  ASSERT_TRUE(opts.openssl_certificate_paths().empty());
}

TEST(client_options, default_options_openssl_verify_paths) {
  network::http::v2::client_options opts;
  ASSERT_TRUE(opts.openssl_verify_paths().empty());
}

TEST(client_options_test, set_option_follow_redirects) {
  network::http::v2::client_options opts;
  opts.follow_redirects(true);
  ASSERT_TRUE(opts.follow_redirects());
}

TEST(client_options_test, set_option_cache_resolved) {
  network::http::v2::client_options opts;
  opts.cache_resolved(true);
  ASSERT_TRUE(opts.cache_resolved());
}

TEST(client_options_test, set_option_use_proxy) {
  network::http::v2::client_options opts;
  opts.use_proxy(true);
  ASSERT_TRUE(opts.use_proxy());
}

TEST(client_options_test, set_option_openssl_certificate_path) {
  network::http::v2::client_options opts;
  opts.openssl_certificate_path("openssl_certificate");
  ASSERT_EQ(std::vector<std::string>{"openssl_certificate"}, opts.openssl_certificate_paths());
}

TEST(client_options_test, set_option_openssl_verify_path) {
  network::http::v2::client_options opts;
  opts.openssl_verify_path("openssl_verify");
  ASSERT_EQ(std::vector<std::string>{"openssl_verify"}, opts.openssl_verify_paths());
}
