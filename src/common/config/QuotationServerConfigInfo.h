#pragma once
#include <string>

class CQuotationServerConfigInfo
{
public:
	int Read(const std::string& filePath);

public:
	std::string ip;
	std::string port;

};