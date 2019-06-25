#ifndef COMMOM_GLOBAL_ENUM_H
#define COMMOM_GLOBAL_ENUM_H

///////////////////////////////////////////////////������/////////////////////////////////////////////////////////
//�����ǵ���
enum RiskUpDownOperatorType
{
	R_QuotationUpDown = 0x1,        // �ǵ���
};

enum RiskUpDownOrderLimitType
{
	R_OrderOpenEnable = 0x0,        //������
	R_OrderOpenProhibit = 0x1,      //��ֹ����
};

enum RiskUpDownPositionAdjustType
{
	R_PositionNoAdjust = 0x0,       //������
	R_PositionFullClose = 0x1,      //ȫ�����
};

enum RiskModuleType
{
	R_SetMoneyIndex = 0x1,          //�ʽ�ָ������
	R_SetTimingClose = 0x2,         //��ʱǿƽ����
	R_SetOverNightClose = 0x3,      //��ҹǿƽ����
	R_SetTradeProdouctClose = 0x4,  //����Ʒ�ּ���������
};

//�ʽ�ָ��
enum RiskMoneyIndexType
{
	R_PriorityMoneyIndex = 0x1,        // �������ʽ�(<)
	R_InferiorMoneyIndex = 0x2,        // ���Ӻ��ʽ�(<)
	R_RiskDegreeIndex = 0x3,           // �����ն�(>)
	R_TodayLossIndex = 0x4,            // �����տ���(>)
	R_DynamicEquityIndex = 0x5,        // ����̬Ȩ��(>)
	R_InferiorRiskDegreeIndex = 0x6,   // ���Ӻ���ն�(>)
	R_SelfMoneyIndex = 0x7,            // �������ʽ�(<)
};

//������״̬�����������
enum RiskParaChangeType
{
	R_ParaByInOutMoney = 0x1,          // ���˺��ʽ𣨳���𣩱��,������״̬
	R_ParaByUserModuleChange = 0x2,    // ���˺��л����ģ��,������״̬
	R_ParaByModuleSetChange = 0x3,     // ���ģ�����ò������,������״̬
	R_ParaRiskDegreeIndex = 0x4,       // ���ն����ǿƽ�󣬽��ǿƽ״̬
};

//��ؼ�¼----�����������
enum RiskMsgType
{
	R_GlobalUpDown = 0x1,             // �����ǵ���ȫ�ַ��(ϵͳ����)
	R_ProductTiming = 0x2,            // Ʒ�ֶ�ʱǿƽ���(ϵͳ����)
	R_ProductOverNightSys = 0x3,      // Ʒ�ָ�ҹǿƽ���(ϵͳ����)
	R_ProductOverNightUser = 0x4,     // Ʒ�ָ�ҹǿƽ���(�˺ż���)
	R_ProductNumLimitSys = 0x5,       // ����Ʒ�����������Ʒ��(ϵͳ����)
	R_ProductNumLimitUser = 0x6,      // ����Ʒ�����������Ʒ��(�˺ż���)
	R_MoneyIndexSys = 0x7,            // �ʽ�ָ����(ϵͳ����)
	R_MoneyIndexUser = 0x8,           // �ʽ�ָ����(�˺ż���)
};

//�����������
enum RiskTriggerType
{
	R_Warn = 0x1,                  // Ԥ��
	R_Prohibit = 0x2,              // ����
	R_Close = 0x3,                 // ǿƽ
};

///��ش���ƽ�ִ�������
enum RiskTriggerCloseType
{
	RTCT_Normal = 0x0,                //������:(Ĭ��)��ʼ״̬
	RTCT_CommonTrigger = 0x1,		  //��ͨ�ģ���ش����󳷵�/ƽ�ִ�����
	RTCT_MoneyDegreeTrigger = 0x2,    //�������:�ʽ���ն�ָ����ʳ���/ƽ�ִ�����
	RTCT_NightDegreeTrigger = 0x3,    //�������:��ҹǿƽ�Ӻ���նȴ�����ʳ���/ƽ�ִ�����
};

// �˺�����
enum E_ACCOUNT_PROP
{
	EAP_Root = 0x0, 					// ���˺�
	EAP_Trader = 0x1,					// �����˺�
	EAP_Risker = 0x2,					// ����˺�
	EAP_Manager = 0x3,					// �����˺�
	EAP_Agency = 0x4,					// �����˺�
	EAP_Funder = 0x5,					// �ʽ��˺�
};
// �˺�״̬
enum E_ACCOUNT_STATUS
{
	EAS_LOGIN = 0x0,					// ��¼
	EAS_UNLOGIN = 0x1,					// δ��¼
};
// �˺�����
enum E_ACCOUNT_TYPE
{
	EAT_Simulation = 0x0,				// ģ���˺�
	EAT_Real = 0x1,						// ʵ���˺�
	EAT_SimuReal = 0x2,					// ģ���ʵ���˺�
};
//�µ�����
enum OrderStyle
{
	LASTPRICE = 0x0,				    // ���¼�
	BUYONEPRICE = 0x1,				    // ��һ��
	SELLONEPRICE = 0x2,				    // ��һ��
	MARKETPRICE = 0x3,                  // �м�
	LIMITEPRICE = 0x4,                  // �޼�
};
//��������������
enum YunTrrigerStyle
{
	Y_LASTPRICE = 0x0,				   // ���¼�
	Y_BUYONEPRICE = 0x1,			   // ��һ��
	Y_SELLONEPRICE = 0x2,			   // ��һ��
};
//��ƽ����
enum  OffsetType 
{
	OFFSET_OPEN = 0x1,					 // ����
	OFFSET_COVER = 0x2,				     // ƽ��
	OFFSET_COVER_TODAY = 0x3,			 // ƽ��
};
//ί��״̬����
enum  OrderStateType 
{
	ORDER_STATE_FAIL = 0x0,				    // ָ��ʧ��
	ORDER_STATE_ACCEPT = 0x1,				// ������,����������������
	ORDER_STATE_QUEUED = 0x2,				// ���Ŷ�,����������/���׶���/�ύ��������
	ORDER_STATE_SUPPENDING = 0x3,			// �ύ��
	ORDER_STATE_SUPPENDED = 0x4,			// �ѹ���
	ORDER_STATE_FINISHED = 0x5,				// ��ȫ�ɽ�
	ORDER_STATE_PARTFINISHED = 0x6,			// ���ֳɽ�
	ORDER_STATE_DELETEING = 0x7,			// ������
	ORDER_STATE_PARTDELETED = 0x8,			// ���ֳ���
	ORDER_STATE_DELETED = 0x9,				// ��ȫ����
	
};
//��������
enum YunTriggerType
{
	Y_GREATEREQUAL = 0x0,				  //  ���ڵ���
	Y_LESSEREQUAL = 0x1,				  //  С�ڵ���
};
// ʱ������
enum TimeType
{
	T_CurrentDay = 0x0,                         // ������Ч
	T_PromptDay = 0x1,                          // ������Ǯ��Ч
};
//��������������
enum  YunConditonOrderType
{
	Y_GREATEREQUALLASTPRICE = 0x0,           // ���¼� ���ڵ���
	Y_LESSEQUALLASTPRICE = 0x1,              // ���¼� С�ڵ���
	Y_GREATEREQUALBUYONEPRICE = 0x2,         // ��һ�� ���ڵ���
	Y_LESSEQUALBUYONEPRICE = 0x3,            // ��һ�� С�ڵ���
	Y_GREATEREQUALSELLONEPRICE = 0x4,	    //  ��һ�� ���ڵ���
	Y_LESSEQUALSELLONEPRICE = 0x5,		    //  ��һ�� С�ڵ���
};
//��������
enum YunOperatorType
{
	Y_ADDOPERATOR = 0x0,                   // ����
	Y_UPDATEOPERATOR = 0x1,                // �޸�
	Y_DELETEOPERATOR = 0x2,                // ɾ��
};
//����������
enum YunConditionType
{
	Y_PRICE =0X0,                         //�۸�
	Y_TIME  =0X1,                         //ʱ��
	Y_TIMEPRICE =0X2,                     //ʱ��۸�
};

// ������״̬
enum ConditionStateType
{
	CONDITION_STATE_WORKING = 0x0,          // �½�(������)
	CONDITION_STATE_HADTRRIGER = 0x1,       // �Ѵ���
	CONDITION_STATE_FAIL = 0x2,             // ʧ��
	CONDITION_STATE_DELETE = 0x3,           // ɾ��
	CONDITION_STATE_SETTLEDELETE = 0x4,     // ����ɾ��

};
//����Ա����
enum  OperatorTradeType 
{
	OPERATOR_TRADE_PC = 0x0,              // PC�˿ͻ��Է���
	OPERATOR_TRADE_APP = 0x1,             // APP�˿ͻ��Է���
	OPERATOR_TRADE_MC = 0x2,              // ��̨��ض˷���
	OPERATOR_TRADE_RC = 0x3,              // ��̨��ض˷���
	OPERATOR_CONDITION_TC = 0x4,          // ������ģ�鷢��
	OPERATOR_STOP_PROFIT_TC = 0x5,	      // ֹӯֹ��˷���
	OPERATOR_RISK = 0x6,			      // ���ģ�鷢��
	OPERATOR_POSTIONT = 0x7,			  // �����ֲ�
	OPERATOR_ROUTINE_LIST = 0x8,          // ����
	OPERATOR_MODIFY_STATE = 0x9,          // ����״̬
	OPERATOR_AUTO_STOP_PC = 0xA,		  // PC���Զ�ֹӯֹ����
};
// �����ʽ
enum OIMM_Change_Type
{
	OIMM_In_WithCapotal = 0x0,				// �������
	OIMM_Out_Withdrawals = 0x1,				// ��������
};

// ���������ʽ
enum OIMM_MoneyChange_Type
{
	OIMM_Type_Invalid = 0,
	OIMM_Out_PostInferiorFunds,		// ���Ӻ��ʽ�
	OIMM_Out_AllocationFunds,		// �����ʶ��
	OIMM_Out_RedReverse,		    // ���
	OIMM_In_PostInferiorFunds,      // ���Ӻ��ʽ�
	OIMM_In_AllocationFunds,        // �����ʶ��
	OIMM_In_BluePatch,              // ����
};

// �ʽ����״̬
enum E_APPLY_MONEY_STATUS
{
	EAMS_Check_Create = 0x0,				// �������������
	EAMS_Check_Unpass = 0x1,				// ��˾ܾ�
	EAMS_Using = 0x2,						// ͨ�����
};
// �ʽ�䶯��ʽ
enum Money_Change_Type
{
	MC_In_Equipment = 0x1,                  // �������ʽ�
	MC_EquipmentADD = 0x2,                  // �����ʶ��
	MC_Out_RedSub = 0x3,		            // �ʽ���	
	MC_In_BlueAdd = 0x4,		            // �ʽ�����
	MC_Fee_Change = 0x5,                    // ���������
	MC_Colse_Position = 0x6,                // ƽ��ӯ��
	MC_Settle_Profit = 0x7,                 // �������
	
		
};
//�ӿ���������
enum  ApiTypeType 
{
	APIType_TYPE_CTP = 0x0,
	APIType_TYPE_ESUNNY = 0x1,
	APIType_TYPE_IB = 0x2,
	APIType_TYPE_SP = 0x3,
};
// �㼶
enum  LevelType
{
	LType_Institution = 0x1,			// ����
	LType_AgentOne = 0x2,				// һ������
	LType_AgentTwo = 0x3,				// ��������
	LType_AgentThree = 0x4,				// ��������
};
// �����Ѽ��㷽ʽ
enum  FeeCalcType
{
	FCT_Fixed = 0x0,					// �̶�
	FCT_Ratio = 0x1,					// ����
};

//��֤����㷽ʽ
enum  MarginCalcType
{
	MCT_Fixed = 0x0,					// �̶�
	MCT_Ratio = 0x1,					// ����
};
//����ֹ���־
enum FloatLossFlag
{
	FLF_FloatLoss = 0x0,				// ����ֹ��
	FLF_NoFloatLoss = 0x1,				// �޸���ֹ��
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
	OOT_CONDITIONORDERS =14,			// ������
	OOT_STOPPROFITLOSSORDERS = 15,	    // ֹӯֹ��
	OOT_ORDERINFO = 16,                 // �µ�

};

///ϵͳ��������
enum SysSettleType
{
	Sys_SettleDate = 0x0,             //�ս���
	Sys_SettleMonth = 0x1,            //�½���
	Sys_SettleByRange = 0x2,          //��ʱ���
};

///ϵͳģ��id
enum SysMoudle
{
	Sys_ManagerCenter,                 //����ģ��
	Sys_TradeCenter,                   //����ģ��
	Sys_RiskCenter,                    //���ģ��
	Sys_YunCenter,                     //��������ģ��
};
#endif //COMMOM_GLOBAL_ENUM_H
