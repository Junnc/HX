#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <map>

#include "../common/net/NetBaseDef.h"
#include "../common/net/NetCommandCode.h"

#include "EchoHandle/echoHandle.h"

class CWSHandler{

public:
	static void SetHttpHandle();

public:
	static WS_HANDLE_MAP ms_handles;
};
