#include <iostream>
#include "echoHandle.h"

bool CEchoTcpHandle::Handle(const std::string& content, std::string& response) {
	response = "ECHO_HELLO_WORLD";
	std::cout<< "in echo handle: " << content <<std::endl;
	return true;
}

void CEchoTcpHandle::registedTcpHandle(TCP_HANDLE_MAP& handleMap) {
	// registed ECHO_TEST
	handleMap[ECHO_TEST] = std::bind(&CEchoTcpHandle::Handle, this, _1, _2);
}
