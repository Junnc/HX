#include "TcpHandle.h"
#include "EchoHandle/echoHandle.h"

void CTcpHandler::SetTcpHandle(){
	CEchoTcpHandle ce;
	ce.registedTcpHandle(ms_handles);
}

TCP_HANDLE_MAP CTcpHandler::ms_handles;
