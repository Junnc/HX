#include "HttpHandle.h"

void CHttpHandler::SetHttpHandle(){
	CEchoHttpHandle ce;
	ce.registedHttpHandle(ms_handles);
}

HTTP_HANDLE_MAP CHttpHandler::ms_handles;
