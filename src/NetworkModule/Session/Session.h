#pragma once
#include <memory>
#include <vector>

#include <hpsocket/HPSocket.h>

class Session : public std::enable_shared_from_this<Session>
{
public:
	//explicit Session(boost::asio::ip::tcp::socket socket);
	Session(): m_isOnline(false)
		  , m_userType(-1)
		  , m_level(-1)
		  , m_source(0)
		  , m_sender(nullptr)
		  , m_connID(0)
	{}

	~Session()=default;
	
public:
	// sesison init
	int Init(const std::string& ip, unsigned short port);

	// send ws response
	void Write(const std::string& content);

	// 设置是否在线
	inline void SetIsOnline(bool isOnline)
	{
		m_isOnline = isOnline;
	}

	inline bool IsOnline()
	{
		return m_isOnline;
	}

	inline std::string SessionID()
	{
		return m_sessionID;
	}

	inline void SetUserID(const std::string& userID)
	{
		m_userID = userID;
	}

	inline void SetUserType(int userType)
	{
		m_userType = userType;
	}

	inline void SetUserLevel(int level)
	{
		m_level = level;
	}

	inline int GetUserType()
	{
		return m_userType;
	}

	inline int GetUserLevel()
	{
		return m_level;
	}

	inline void SetSource(int source)
	{
		m_source = source;
	}
	inline int GetSource()
	{
		return m_source;
	}
	inline std::string GetUserID()
	{
		return m_userID;
	}

	inline std::string GetParentID()
	{
		return m_parentID;
	}

	inline void SetParentID(const std::string& parentID)
	{
		m_parentID = parentID;
	}

	inline void SetUserName(const std::string& userName)
	{
		m_accountName = userName;
	}

	inline std::string GetUserName()
	{
		return m_accountName;
	}

	inline std::string GetIp()
	{
		return m_ip;
	}

	inline void SetLoginName(const std::string& loginName)
	{
		m_loginName = loginName;
	}

	inline std::string GetLoginName()
	{
		return m_loginName;
	}

	inline void SetLoginTime(const std::string& loginTime)
	{
		m_loginTime = loginTime;
	}

	inline std::string GetLoginTime()
	{
		return m_loginTime;
	}

	inline void SetRegisterTime(const std::string& registerTime)
	{
		m_registerTime = registerTime;
	}

	inline std::string GetRegisterTime()
	{
		return m_registerTime;
	}
	inline void SetMac(const std::string& mac)
	{
		m_mac = mac;
	}

	inline std::string GetMac()
	{
		return m_mac;
	}

	inline void SetWSSender(IHttpServer* pServ, CONNID dwConnID) {
		m_sender = pServ;
		m_connID = dwConnID;
	}
private:
	// ip
	std::string m_ip;

	// 账户名
	std::string m_accountName;

	// 登录名
	std::string m_loginName;

	// 回话id : ip+port
	std::string m_sessionID;

	// 注册时间
	std::string m_registerTime;

	// 登录时间
	std::string m_loginTime;

	// 是否在线
	bool m_isOnline;

	// 账户id
	std::string m_userID;

	// 父账户id
	std::string m_parentID;

	// 账户类型
	int m_userType;

	// 账户等级
	int m_level;

	// 来源
	int m_source;

	// mac地址
	std::string  m_mac;

	// websocket sender
	IHttpServer* m_sender;
	CONNID m_connID;

};

typedef std::shared_ptr<Session> SessionPtr;
