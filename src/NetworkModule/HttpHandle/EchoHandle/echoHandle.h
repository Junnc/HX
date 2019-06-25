#pragma once
#include <functional>
#include <memory>
#include <map>

#include "common/net/NetCommandCode.h"
#include "common/net/NetBaseDef.h"

class CEchoHttpHandle{
public:
	CEchoHttpHandle()=default;
	~CEchoHttpHandle()=default;
public:
	void registedHttpHandle(HTTP_HANDLE_MAP& handleMap);

public:
	bool Handle(const std::string& content, std::string& response);
	void HandleDetail();
};

typedef std::shared_ptr<CEchoHttpHandle> CEchoHttpHandlePtr;
