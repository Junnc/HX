/*
 * NetBaseDef.h
 * spec net base common define
 */

#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <map>

// common define
using std::placeholders::_1;
using std::placeholders::_2;

// tcp define
using TCP_HANDLE = std::function<void(const std::string&, std::string&)>;
using TCP_HANDLE_MAP = std::map<int, TCP_HANDLE>;

// http define
#define HTTP_NAME "http"

using HTTP_HANDLE = std::function<void(const std::string&, std::string&)>;
using HTTP_HANDLE_MAP = std::map<int, HTTP_HANDLE>;

// websocket define
using WS_HANDLE = std::function<void(const std::string&, std::string&)>;
using WS_HANDLE_MAP = std::map<int, WS_HANDLE>;
