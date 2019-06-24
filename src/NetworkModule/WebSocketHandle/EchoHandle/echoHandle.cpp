#include "echoHandle.h"

bool CEchoWSHandle::Handle(const std::string& content, std::string& response) {
	response = "ECHO_HELLO_WORLD";
	return true;
}

void CEchoWSHandle::registedHttpHandle(WS_HANDLE_MAP& handleMap) {
	// registed ECHO_TEST
	handleMap[ECHO_TEST] = std::bind(&CEchoWSHandle::Handle, this, _1, _2);
}
