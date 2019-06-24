#include "WSHandle.h"

void CWSHandler::SetHttpHandle(){
	CEchoWSHandle ce;
	ce.registedHttpHandle(ms_handles);
}

WS_HANDLE_MAP CWSHandler::ms_handles;
