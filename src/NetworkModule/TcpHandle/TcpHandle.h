#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <map>

#include "../common/net/NetBaseDef.h"
#include "../common/net/NetCommandCode.h"
#include "EchoHandle/echoHandle.h"

class CTcpHandler{

public:
	static void SetTcpHandle();

public:
	static TCP_HANDLE_MAP ms_handles;
};
