#include "echoHandle.h"

bool CEchoHttpHandle::Handle(const std::string& content, std::string& response) {
	response = "ECHO_HELLO_WORLD";
	return true;
}

void CEchoHttpHandle::registedHttpHandle(HTTP_HANDLE_MAP& handleMap) {
	// registed ECHO_TEST
	handleMap[ECHO_TEST] = std::bind(&CEchoHttpHandle::Handle, this, _1, _2);
}
