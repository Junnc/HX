#pragma once
#include <string>
#include <memory>
#include <map>
#include <mutex>

#define USERMANAGE_API  __declspec(dllexport)
typedef std::unique_lock<std::mutex>		ReadLock;
typedef std::unique_lock<std::mutex>		WriteLock;

using namespace std;
enum UsersType
{
	USER_SUPER,
	USER_TRADER=1,
	USER_RISK,
	USER_MANAGER,
	USER_INSTITUTION,
	USER_MONEYACC
};

// �㼶
enum  LevelType
{
	LType_Institution = 0x1,			// ����
	LType_AgentOne = 0x2,				// һ������
	LType_AgentTwo = 0x3,				// ��������
	LType_AgentThree = 0x4,				// ��������
};

//������־��ѯ����
enum OperatorLogQuery
{
	OLQ_OneManger = 0x0,				// ����Ĺ���Ա
	OLQ_OneRisker = 0x1,				// ����ķ��Ա
	OLQ_Keyword = 0x2,					// �ؼ���
	OLQ_Agen = 0x3,						// ������
	OLQ_Manager = 0x4,					// ����Ա
	OLQ_Risker = 0x5,					// ���Ա
	OLQ_Child = 0x6,					// ���˺�
	OLQ_MarginTemplet = 0x7,			// ��֤��ģ��
	OLQ_FeeTemplet = 0x8,				// ������ģ��
	OLQ_RiskTemplet = 0x9,				// ���ģ��
	OLQ_OutInMoney = 0xA,				// �����
	OLQ_ExchangeRate = 0xB,				// ����
};

// ������־��������
enum OperatorObjType
{
	OOT_MAIN_ACC = 1,					// ���˻�
	OOT_CHILD_ACC = 2,				    // ���˻�
	OOT_MANAGER_ACC = 3,				// ����Ա
	OOT_RISK_ACC = 4,				    // ���Ա
	OOT_CHILD_AGENT = 5,			    // �¼�����
	OOT_AGETOPENMODULE = 6,             // ������ģ��
	OOT_MARGINMODULE = 7,				// ��֤��ģ��
	OOT_CHILD_FEEMODULE = 8,			// ���˻�������
	OOT_RISKMOUDLE = 9,                 // ���ģ��
	OOT_AGENT_FEEMODULE = 10,			// ����������
	OOT_AUTHRITYMODULE = 11,			// Ȩ��ģ��
	OOT_BUSINESS_VALUE = 12,			// ҵ�����

	OOT_ACCOUNT = 13,					// �˻�	
	OOT_CONDITIONORDERS = 14,			// ������
	OOT_STOPPROFITLOSSORDERS = 15,	    // ֹӯֹ��
	OOT_ORDERINFO = 16,                 // �µ�

};

enum SysMoudle
{
	Sys_ManagerCenter,                 //����ģ��
	Sys_TradeCenter,                   //����ģ��
	Sys_RiskCenter,                    //���ģ��
	Sys_YunCenter,                     //��������ģ��
};

enum BussinessType
{
	BUSSINESS_SROCK,
	BUSSINESS_FUTRUE
};

typedef struct userInfos_
{
	std::string  m_sUserID;

	//�û����� 1=����Ա 2=���Ա 3=����Ա 4=���� 5=�ʽ��˻�
	int		m_nUserType;

	//����������� 1=super 2=һ������ 3=��������...
	int		m_nLevel;		

	std::string  m_sLoginName;
	
	std::string  m_sAccountName;
	
	std::string  m_sPassword;
	
	std::string  m_sPhone;
	
	std::string  m_sPoularizeLink;
	
	std::string  m_sAddress;
	
	//�Ƿ��߼�ɾ�� 0=���� 1=ɾ��
	int		m_nIsLogicDel;		

	int		m_nRegisterDate;
	
	int     m_nRegisterTime;
	
	//���˻�����
	int     m_nMainIDNum;			
	
	//���˻�����
	int		m_nSumIDNum;			
	
	//��̨����1=ctp 2=esunny 3=ib,4=sp 5=sub 6=cms 7=zd
	int		m_nCounterType;		

	//�û��������� 1=��Ʊ��2=�ڻ���3=��Ʊ&&�ڻ�
	int     m_nFinanceType;

	double  m_dTotalMoney;

	double  m_dFutureMoney;

	double  m_dStockMoney;

	userInfos_() :
		m_nUserType(0),
		m_nLevel(0),
		m_nIsLogicDel(0),
		m_nRegisterDate(0),
		m_nRegisterTime(0),
		m_nMainIDNum(0),
		m_nSumIDNum(0),
		m_nCounterType(0),
		m_nFinanceType(0),
		m_dTotalMoney(0.0),
		m_dFutureMoney(0.0),
		m_dStockMoney(0.0)
	{}
}userInfos;

typedef std::shared_ptr<userInfos>  userInfosPtr;

typedef struct userRelationShip_
{
	//�û�ID
	std::string sUserID;

	//����
	std::string sInstitutionID;

	//��������
	std::string sInstitutionName;

	//���Ա
	std::string sMonitorID;

	//����Ա
	std::string sManagerID;

	//���˻�/ʵ���˻�
	std::string sMainID;

	//��֤��ģ��
	std::string sMarginModuleID;

	//������ģ��
	std::string sFeemoduleID;

	//���ģ��
	std::string sRiskModuleID;

	//Ȩ��ģ��
	std::string sAuthrityModuleID;

	//�������ģ��Ȩ��
	std::string sRiskModuleAuthrityID;
}userRelationShip;

typedef std::shared_ptr<userRelationShip> userRelationShipPtr;

//������users��  user_relation_ship���map
typedef std::map<userInfosPtr, userRelationShipPtr>		UserAndRelationShipMap;  

typedef struct userIdentify_
{
	std::string m_sUserID;
	
	std::string m_sIDCard;
	
	std::string m_sBankName;
	
	std::string m_sBranchBank;

	std::string m_sBankCardNo;
	//��ʵ����
	std::string m_sSurName;

	//�Ƿ�ʵ����֤ 0=δ��֤  1=��֤
	int	   m_nIsDentify;	

	userIdentify_() :
		m_nIsDentify(0) {}
}userIdentify;

typedef std::shared_ptr<userIdentify> userIdentifyPtr;

typedef struct userMoneyInfo_
{
	// �˻�Ψһ��ʶ
	std::string m_sUserID;

	// �û���֤��
	double m_dUserDeposit;

	// ���ö��
	double m_dEquipment;

	// ��̬Ȩ��
	double m_dPreBalance;

	// ��ǰ�ʽ����
	double m_dCurrentTotal;

	// ����ƽ��ӯ��
	double m_dTodayCloseProfit;

	// ����������
	double m_dTodayFee;

	// �������
	double m_dTodayInMoney;

	// ���ճ���
	double m_dTodayOutMoney;

	// ��ʷӯ���ܺ�
	double m_dHistoryProfit;

	// ��ʷ�������ܺ�
	double m_dHistoryFee;

	// ��ʷ�����ܺ�
	double m_dHistoryOutMoney;

	// ��ʷ����ܺ�
	double m_dHistoryInMoney;

	// ί�б�֤�𣬶��ᱣ֤�� �ڲ�������
	double m_dFrozenMargin;

	// �ֱֲ�֤��ռ�ñ�֤�� �ڲ�������
	double m_dHoleMargin;

	// ����ӯ�� ���ڲ�������
	double m_dFloatGainLoss;

	// ����ӯ�� ���ڲ�������
	double m_dSettleGainLoss;

	// ��̬Ȩ�� ���ڲ�������
	double m_dDynamic;

	// �����ʽ� ���ڲ�������
	double m_dSelfMoney;

	// �����ʽ� ���ڲ�������
	double m_dAvailableMoney;

	// ���ն� ���ڲ�������
	double m_dRiskDegree;

	// �����ʽ�
	double m_dFrozenOutMoney;

	userMoneyInfo_()
		: m_dUserDeposit(0.0)
		, m_dEquipment(0.0)
		, m_dPreBalance(0.0)
		, m_dCurrentTotal(0.0)
		, m_dTodayCloseProfit(0.0)
		, m_dTodayFee(0.0)
		, m_dTodayInMoney(0.0)
		, m_dTodayOutMoney(0.0)
		, m_dHistoryProfit(0.0)
		, m_dHistoryFee(0.0)
		, m_dHistoryOutMoney(0.0)
		, m_dHistoryInMoney(0.0)
		, m_dFrozenMargin(0.0)
		, m_dHoleMargin(0.0)
		, m_dFloatGainLoss(0.0)
		, m_dSettleGainLoss(0.0)
		, m_dDynamic(0.0)
		, m_dSelfMoney(0.0)
		, m_dAvailableMoney(0.0)
		, m_dRiskDegree(0.0)
		, m_sUserID("")
		, m_dFrozenOutMoney(0.0)
	{}
}userMoneyInfo;

typedef std::shared_ptr<userMoneyInfo> userMoneyInfoPtr;


typedef struct certificationRegisterRecordInfo_ 
{
	int m_id;

	std::string m_sUserId;

	std::string m_sLoginName;

	std::string m_sAccountName;

	std::string m_sSurName;

	std::string m_sIDCard;

	std::string m_sPostTime;
	
	std::string m_sApprovalTime;

	std::string m_sApprovalID;

	int m_nIsApproval;

	std::string m_sApprovalReason;

}certificationRegisterRecordInfo;

typedef std::shared_ptr<certificationRegisterRecordInfo> certificationRegRecordInfoPtr;

typedef struct InstitutionMainidMap_
{
	// ����
	std::string m_id;

	//	�������id
	std::string m_institutionID;

	// ���˻�
	std::string m_mainID;

}InstitutionMainidMap;

typedef std::shared_ptr<InstitutionMainidMap> InstitutionMainidMapPtr;

typedef struct SystemSet_
{
	// ����
	std::string m_sKey;

	//	
	std::string m_sValue;

	// 
	std::string m_sNote;

}SystemSet;

typedef std::shared_ptr<SystemSet> SystemSetPtr;

typedef struct LogRecords_
{
	// ����
	int m_logID;

	// �������˻����
	std::string m_userID;

	// �������˻�����
	std::string m_userName;

	// ���������˻����
	std::string m_operatorID;

	// ���������˻�����
	std::string m_operatorName;

	// ��������
	int m_createDate;

	// ����ʱ��
	int m_createTime;

	// 
	std::string m_newContent;

	std::string m_oldContent;

	int m_sysModule;

	std::string m_mac;

	std::string m_ip;

	std::string m_sysModuleName;

	// ������������
	int m_type;

	LogRecords_()
		: m_logID(0)
		, m_sysModule(0)
		, m_type(0)
		, m_createDate(0)
		, m_createTime(0)
	{}

}LogRecords;

typedef std::shared_ptr<LogRecords> LogRecordsPtr;