#pragma once
#include <string>

class CHttpServerConfigInfo
{
public:
	// ��ȡ�ļ���Ϣ
	int Read(const std::string& filePath);

public:
	std::string ip;
	int port;

};