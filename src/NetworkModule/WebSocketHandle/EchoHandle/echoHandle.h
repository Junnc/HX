#pragma once
#include <functional>
#include <memory>
#include <map>

#include "common/net/NetBaseDef.h"
#include "common/net/NetCommandCode.h"

class CEchoWSHandle{
public:
	CEchoWSHandle()=default;
	~CEchoWSHandle()=default;
public:
	void registedHttpHandle(WS_HANDLE_MAP& handleMap);

public:
	bool Handle(const std::string& content, std::string& response);
	void HandleDetail();
};

typedef std::shared_ptr<CEchoWSHandle> CEchoWSHandlePtr;
