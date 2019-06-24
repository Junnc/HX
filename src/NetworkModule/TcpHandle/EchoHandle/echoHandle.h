#pragma once
#include <functional>
#include <memory>
#include <map>

#include "../../common/net/NetBaseDef.h"
#include "../../common/net/NetCommandCode.h"

class CEchoTcpHandle{
public:
	CEchoTcpHandle()=default;
	~CEchoTcpHandle()=default;
public:
	void registedTcpHandle(TCP_HANDLE_MAP& handleMap);

public:
	bool Handle(const std::string& content, std::string& response);
	void HandleDetail();
};

typedef std::shared_ptr<CEchoTcpHandle> CEchoHttpHandlePtr;
