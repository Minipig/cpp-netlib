// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef __NETWORK_HTTP_V2_CONSTANTS_INC__
#define __NETWORK_HTTP_V2_CONSTANTS_INC__

#include <string>

namespace network {
  namespace http {
    namespace v2 {
      // methods
      inline
      constexpr const char *get() {
	return "GET";
      }

      inline
      constexpr const char *post() {
	return "POST";
      }

      inline
      constexpr const char *put() {
	return "PUT";
      }

      inline
      constexpr const char *delete_() {
	return "DELETE";
      }

      inline
      constexpr const char *head() {
	return "HEAD";
      }

      inline
      constexpr const char *options() {
	return "OPTIONS";
      }

      inline
      constexpr const char *trace() {
	return "TRACE";
      }

      inline
      constexpr const char *connect() {
	return "CONNECT";
      }

      inline
      constexpr const char *merge() {
	return "MERGE";
      }

      inline
      constexpr const char *patch() {
	return "PATCH";
      }

      // status codes
      // informational
      inline
      constexpr int continue_() {
	return 100;
      }

      inline
      constexpr int switch_protocols() {
	return 101;
      }

      // successful
      inline
      constexpr int ok() {
	return 200;
      }

      inline
      constexpr int created() {
	return 201;
      }

      inline
      constexpr int accepted() {
	return 202;
      }

      inline
      constexpr int non_auth_info() {
	return 203;
      }

      inline
      constexpr int no_content() {
	return 204;
      }

      inline
      constexpr int reset_content() {
	return 205;
      }

      inline
      constexpr int partial_content() {
	return 206;
      }

      // redirection
      inline
      constexpr int multiple_choices() {
	return 300;
      }

      inline
      constexpr int moved_permanently() {
	return 301;
      }

      inline
      constexpr int found() {
	return 302;
      }

      inline
      constexpr int see_other() {
	return 303;
      }

      inline
      constexpr int not_modified() {
	return 304;
      }

      inline
      constexpr int use_proxy() {
	return 305;
      }

      inline
      constexpr int temporary_redirect() {
	return 307;
      }

      // client error
      inline
      constexpr int bad_request() {
	return 400;
      }

      inline
      constexpr int unauthorized() {
	return 401;
      }

      inline
      constexpr int payment_required() {
	return 402;
      }

      inline
      constexpr int forbidden() {
	return 403;
      }

      inline
      constexpr int not_found() {
	return 404;
      }

      inline
      constexpr int method_not_allowed() {
	return 405;
      }

      inline
      constexpr int not_acceptable() {
	return 406;
      }

      inline
      constexpr int proxy_auth_required() {
	return 407;
      }

      inline
      constexpr int request_timeout() {
	return 408;
      }

      inline
      constexpr int conflict() {
	return 409;
      }

      inline
      constexpr int gone() {
	return 410;
      }

      inline
      constexpr int length_required() {
	return 411;
      }

      inline
      constexpr int precondition_failed() {
	return 412;
      }

      inline
      constexpr int request_entity_too_large() {
	return 413;
      }

      inline
      constexpr int request_uri_too_large() {
	return 414;
      }

      inline
      constexpr int unsupported_media_type() {
	return 415;
      }

      inline
      constexpr int range_not_satisfiable() {
	return 416;
      }

      inline
      constexpr int expectation_failed() {
	return 417;
      }

      // server error
      inline
      constexpr int internal_error() {
	return 500;
      }

      inline
      constexpr int not_implemented() {
	return 501;
      }

      inline
      constexpr int bad_gateway() {
	return 502;
      }

      inline
      constexpr int service_unavailable() {
	return 503;
      }

      inline
      constexpr int gateway_timeout() {
	return 504;
      }

      inline
      constexpr int http_version_not_supported() {
	return 505;
      }

      std::string status_message(int status_code);
    } // namespace v2
  } // namespace http
} // namespace network


#endif // __NETWORK_HTTP_V2_CONSTANTS_INC__
