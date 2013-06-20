# Copyright (C) 2013 by Glyn Matthews
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

set(CPP-NETLIB_CLIENT_TESTS
  response_test
  client_options_test
  request_options_test
  byte_source_test
  request_test
  )

foreach(test ${CPP-NETLIB_CLIENT_TESTS})
  if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${test}.cpp
      PROPERTIES COMPILE_FLAGS "-Wall")
  endif()

  add_executable(cpp-netlib-http-v2-${test} ${test}.cpp)
  target_link_libraries(cpp-netlib-http-v2-${test}
    cppnetlib-uri
    ${Boost_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    )
  set_target_properties(cpp-netlib-http-v2-${test}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
  add_test(cpp-netlib-http-v2-${test}
    ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-v2-${test})

endforeach(test)
