// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/http/v2/constants.hpp>
#include <unordered_map>

static std::unordered_map<int, std::string> status_message_map() {
  std::unordered_map<int, std::string> status_messages;
  status_messages[100] = "Continue";
  status_messages[101] = "Switching Protocols";
  status_messages[200] = "OK";
  status_messages[201] = "Created";
  status_messages[202] = "Accepted";
  status_messages[203] = "Non-Authoritative Information";
  status_messages[204] = "No Content";
  status_messages[205] = "Reset Content";
  status_messages[206] = "Partial Content";
  status_messages[300] = "Multiple Choices";
  status_messages[301] = "Moved Permanently";
  status_messages[302] = "Found";
  status_messages[303] = "See Other";
  status_messages[304] = "Not Modified";
  status_messages[305] = "Use Proxy";
  status_messages[307] = "Temporary Redirect";
  status_messages[400] = "Bad Request";
  status_messages[401] = "Unauthorized";
  status_messages[402] = "Payment Required";
  status_messages[403] = "Forbidden";
  status_messages[404] = "Not Found";
  status_messages[405] = "Method Not Allowed";
  status_messages[406] = "Not Acceptable";
  status_messages[407] = "Proxy Authentication Required";
  status_messages[408] = "Request Timeout";
  status_messages[409] = "Conflict";
  status_messages[410] = "Gone";
  status_messages[411] = "Length Required";
  status_messages[412] = "Precondition Failed";
  status_messages[413] = "Request Entity Too Large";
  status_messages[414] = "Request Uri Too Long";
  status_messages[415] = "Unsupported Media Type";
  status_messages[416] = "Request Range Not Satisfiable";
  status_messages[417] = "Expectation Failed";
  status_messages[500] = "Internal Error";
  status_messages[501] = "Not Implemented";
  status_messages[502] = "Bad Gateway";
  status_messages[503] = "Service Unavailable";
  status_messages[504] = "Gateway Timeout";
  status_messages[505] = "HTTP Version Not Supported";
}


std::string status_message(int status_code) {
  static const auto status_messages = status_message_map();
  auto it = status_messages.find(status_code);
  if (it != status_messages.end()) {
    return it->second;
  }
  return "Invalid Status Code";
}
