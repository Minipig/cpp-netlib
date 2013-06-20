// Copyright 2012 Dean Michael Berris <dberris@google.com>.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <network/protocol/http/request/request_base.hpp>

namespace http = network::http;

// In this test we make sure that the implementation of the default request
// storage base actually doesn't have bugs and works as advertised. Although we
// don't intend to expose this interface to users, we use the test as a sanity
// check on the internals of the implementation.
struct request_test : http::request_storage_base {
  typedef http::request_storage_base base_type;

  // Expose the protected functions so that we can test them.
  using base_type::append;
  using base_type::read;
  using base_type::flatten;
  using base_type::clear;

  explicit request_test(size_t chunk_size) : base_type(chunk_size) {}

  request_test(request_test const& other) : base_type(other) {}

  ~request_test() {
    // do nothing here.
  }
};

TEST(request_test, request_storage_flow) {
  // Use a few byte chunks just to make it manageable.
  request_test simple(64);
  static char data[] =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus vitae ante sed nunc dapibus convallis in at neque. Vestibulum sed congue nunc. Sed tempus lorem non dui ultrices porttitor porta ligula venenatis. Sed a orci gravida tellus condimentum laoreet. Vivamus pulvinar, tortor eu adipiscing tempus, dolor urna tincidunt enim, id pretium eros ante quis dui. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. In hac habitasse platea dictumst. Maecenas mattis metus.";
  simple.append(data, sizeof(data));
  std::string output;
  size_t bytes_read = simple.read(output, 0, sizeof(data));
  ASSERT_EQ(bytes_read, sizeof(data));
  std::string flattened;
  simple.flatten(flattened);
  ASSERT_EQ(flattened, output);
  ASSERT_EQ(std::string(data, sizeof(data)), output);
  simple.clear();
}

TEST(request_test, request_storage_copy) {
  // Use a few byt chunks just to make it manageable.
  request_test original(64);
  static char quick_brown[] = "The quick brown fox jumps over the lazy dog.";
  original.append(quick_brown, sizeof(quick_brown));
  std::string output;
  request_test copy(original);
  size_t bytes_read = copy.read(output, 0, sizeof(quick_brown));
  ASSERT_EQ(bytes_read, sizeof(quick_brown));
  std::string flattened;
  copy.flatten(flattened);
  ASSERT_EQ(flattened, output);
  ASSERT_EQ(std::string(quick_brown, sizeof(quick_brown)), output);
  copy.clear();
  flattened.clear();
  original.flatten(flattened);
  ASSERT_EQ(flattened, std::string(quick_brown, sizeof(quick_brown)));
}
