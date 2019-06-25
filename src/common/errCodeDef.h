/*
* Date  :
* Desc  : ȫ�ִ����붨��,ϵͳ�����д�����Ӧ�ڴ˶���
* Desc  : ����Ӧ�ð����ܽ��з��࣬ÿһ�����Ӧ����255��(��00-FF)
*/
#ifndef ERR_CODE_DEF_H_
#define ERR_CODE_DEF_H_
#define RISK_MSG_LEN   256

// û�д���
#define ERR_NOERROR								0x0000

/***********************�����ݿ�ģ����ش��� [0x10100-0x101FF]**************/
#define ERR_DB					                0x10100
// ��ʼ���������Ӵ���
#define ERR_DB_INITCONNFAIL					    ERR_DB + 0x1
// �������ݿ����Ӵ���
#define ERR_DB_CREATECONNFAIL					ERR_DB + 0x2
// �������ݿ������ַ�������
#define ERR_DB_SETCHASETFAIL					ERR_DB + 0x3
// ���ݿ����Ӵ���
#define ERR_DB_CONNFAIL							ERR_DB + 0x4
// �������ݿ�ʧ��
#define ERR_DB_OPERATOR							ERR_DB + 0x5

/***********************������ģ�鷢����ش��� [0x10200-0x102FF]*************/
#define ERR_NET							        0x10200
// ��������ʧ��
#define ERR_NET_FAIL							ERR_NET + 0x1
// �������ӱ��ر�
#define ERR_NET_CLOSE							ERR_NET + 0x2

/***********************�ۺ�Լ��Ʒ����ش��� [0x10300-0x103FF] *************/
#define ERR_CP							        0x10300
// ��Լ������
#define ERR_CP_CONTRACT_NOTEXIST			    ERR_CP + 0x1
// ��Լ�Ѵ���
#define ERR_CP_CONTRACT_ALREADYEXIST			ERR_CP + 0x2
// ��Լ���ڹ���״̬
#define ERR_CP_CONTRACT_NOTRADETIME			    ERR_CP + 0x3
// ��Լ����򳬹���󽻸��գ���ֹ�µ�
#define ERR_CP_CONTRACT_DEADLINE			    ERR_CP + 0x4
// Ʒ����Ϣ����
#define ERR_PRODUCT_INFO			            ERR_CP + 0x5
// Ʒ�ֲ�����
#define ERR_PRODUCT_NOTEXIST			        ERR_CP + 0x6
// Ʒ���Ѵ��� 
#define ERR_PRODUCT_ALREADYEXIST			    ERR_CP + 0x7
// Ʒ���������׵ĺ�Լ������
#define ERR_FORCE_CLOSETIME_FORBID_ORDER        ERR_CP + 0x8
// �������տɽ���Ʒ����
#define ERR_PRODUCT_NUM_LIMIT                   ERR_CP + 0x9
// Ʒ�ֵ��ο�����������
#define ERR_PRODUCT_SINGLE_OPEN_LIMIT           ERR_CP + 0xA
// Ʒ�ֵ��տ�����������
#define ERR_PRODUCT_OPEN_LIMIT                  ERR_CP + 0xB
// Ʒ���ֲܳ���������
#define ERR_PRODUCT_POSITION_LIMIT              ERR_CP + 0xC
// Ʒ�־��ֲ���������
#define ERR_PRODUCT_NET_POSITION_LIMIT          ERR_CP + 0xD
// ��Ʒ�ֵ���ǿƽʱ�䣬��ֹ����
#define ERR_PRODUCT_FORCE_TRADE_TIME            ERR_CP + 0xE
// ��Ʒ���޽���Ȩ��
#define ERR_PRODUCT_CANNOT_TRADE				ERR_CP + 0xF
// ��Ʒ�ֲ��ڽ���ʱ����
#define ERR_PRODUCT_NOTIME_TRADED				ERR_CP + 0x10
// ��Ʒ���ڽ��������ڽڼ��������У��޽���Ȩ��
#define ERR_PRODUCT_HOLIDAY_LIMIT				ERR_CP + 0x11
// �ú�Լ�޽���Ȩ��
#define ERR_CONTRACT_CANNOT_TRADE				ERR_CP + 0x12

/***********************��������ش���  [0x10400-0x104FF]*******************/
#define ERR_QUOT 						        0x10400

/***********************���˺���Ȩ�޵���ش��� [0x10500-0x105FF]************/
#define ERR_USER								0x10500
// ��Ȩ��
#define ERR_USER_NOPERMISSION                   ERR_USER + 0x1
// ������
#define ERR_USER_NOEXIST                        ERR_USER + 0x2
// û�е�¼����
#define ERR_NO_LOGIN_PASSWORD                   ERR_USER + 0x3
// �˻����Ѵ���
#define ERR_ACCOUNT_ALREADY_EXIST               ERR_USER + 0x4
// δ��¼
#define ERR_UN_LOGIN                            ERR_USER + 0x5
// �˺���������
#define ERR_ACCOUNT_TYPE                        ERR_USER + 0x6
// �˻�������Ϊ����
#define ERR_ACCOUNT_CHINESE                     ERR_USER + 0x7
// �����¼�����
#define ERR_CHILDAGENT_EXIST					ERR_USER + 0x8
// �������˻�
#define ERR_CHILDAACC_EXIST						ERR_USER + 0x9
// �󶨴�����
#define ERR_BINDAGENT                           ERR_USER + 0x10
// ���������
#define ERR_OLDPASSWROD                         ERR_USER + 0x11
// �����������Ѵ����ȼ�
#define ERR_AGENTADD_MAXLEVEL                   ERR_USER + 0x12
// �˻������������
#define ERR_LOGINNAME_PWD                       ERR_USER + 0x13
// ���˻����ڳֲ�
#define ERR_CHILDPOSITION_EXIST                 ERR_USER + 0x14
// ���˻�����δ��Ч��ί��
#define ERR_CHILDORDER_EXIST                    ERR_USER + 0x15
// ���˻����ڰ󶨵����˻�
#define ERR_MAINIDTOCHILDACC_EXIST              ERR_USER + 0x16
// ���˻�����ģ�����Ѱ����˺�
#define ERR_FEEMODULE_BIND_CHILDACC             ERR_USER + 0x17
// ������˻��Ѵ����ֵ
#define ERR_ADDCHILDACC_MAX                     ERR_USER + 0x18
// ������˻��Ѵ����ֵ
#define ERR_ADDMAINACC_MAX                      ERR_USER + 0x19
// ģ���ѱ�ʹ��
#define ERR_MARGINMODULE_USED                   ERR_USER + 0x20
// ���������˻�������
#define ERR_INS_NOCHILDACC                      ERR_USER + 0x21
// �˻�����
#define ERR_ACC_ONLINE                          ERR_USER + 0x22
// ģ��������ֵ����
#define ERR_MODULEVALUE_OVER                    ERR_USER + 0x23
// ���˻����ڳֲ�
#define ERR_CHILDACC_POSITION_EXIST             ERR_USER + 0x24
// ���˻��㼶ID��Ч
#define ERR_CHILDACC_LEVEL_ID_NO_VAILD          ERR_USER + 0x25
// �������������������Ч���˻�ID
#define ERR_PARA_USER_ID_NO_VAILD               ERR_USER + 0x26
// md5У��ʧ��
#define ERR_MD5CHECK_FAIL				        ERR_USER + 0x27
// ������ģ�岻����
#define ERR_AGENTMODULE_NO_EXIST                ERR_USER + 0x28
// �ѵ�¼
#define ERR_ALREADY_LOGIN                       ERR_USER + 0x29
// �ֻ������˻������ǰ󶨹�ϵ                   
#define ERR_TELNO_LOGINNAME_NOTBIND             ERR_USER + 0x30

/***********************���ʽ���ش��� [0x10600-0x106FF]*********************/
#define ERR_MONEY								0x10600
// ��ȡ�˻��ʽ���Ϣ����ʧ��
#define ERR_MONEY_QRY_FAIL                      ERR_MONEY + 0x1
// �Ӻ��ʽ���
#define ERR_POSTINFFUND_LESS                    ERR_MONEY + 0x2
// ���ö�Ȳ���
#define ERR_ALLOCATIONFUND_LESS                 ERR_MONEY + 0x3
// �ʽ���
#define ERR_LEFTMONEY_LESS                      ERR_MONEY + 0x4
// �Զ���˲���������
#define AUTO_APPROVAL_VAL_NOEXIST               ERR_MONEY + 0x5
// ϵͳ�����
#define NOT_AUTO_APPROVAL                       ERR_MONEY + 0x6
// ��𶩵�������
#define INMONEY_ORDER_NOT_EXIST                 ERR_MONEY + 0x7
// �Ѿ����
#define INMONEY_ORDER_APPROVALED                ERR_MONEY + 0x8
// δ֧���ɹ�
#define NOT_PAY_SUCCESS                         ERR_MONEY + 0x9
// �ʽ�Ϊ����
#define MONEY_IS_MINUS                         ERR_MONEY + 0x10

/***********************�߽���ģ����ش��� [0x10700-0x107FF]***************/
#define ERR_TRADE							  0x10700
// �˺��µ���ί�в�������
#define ERR_TRADE_ORDER_ARGERROR              ERR_TRADE + 0x1
// �˺ŵ�ί�в�����
#define ERR_TRADE_ORDER_NOEXIST               ERR_TRADE + 0x2
// ��ƽ��������
#define  ERR_TRADE_VOLUME_NOT_ENOUGH		  ERR_TRADE + 0x3
// ��ȡ������������
#define  ERR_TRADE_NOT_LASTPRICE			  ERR_TRADE + 0x4
// ��ȡ��������
#define  ERR_TRADE_NOT_EXCHANGE_RATE		  ERR_TRADE + 0X5
// �����ʽ���
#define  ERR_TRADE_NOT_ENOUGH_MONEY			  ERR_TRADE + 0X6
// δָ���ʽ��˺�
#define  ERR_TRADE_NOT_MAIN_ACCOUNT			  ERR_TRADE + 0X7
// ���͵�ʵ��ʧ��
#define  ERR_TRADE_SEND_EXCHANGE_ERR		  ERR_TRADE + 0x8
// ����ί�б�Ų�����
#define  ERR_TRADE_ORDER_DONOT_EXIST		  ERR_TRADE + 0x9
// ί��״̬���ɳ�
#define  ERR_TRADE_CANNOT_BE_CANCELED		  ERR_TRADE + 0x10
// ƽָ���ֲִ���
#define  ERR_TRADE_CLOSE_POSITION			  ERR_TRADE + 0x11

/***********************����ģ����ش��� [0x10800-0x108FF] **************/
#define ERR_RISK									  0x10800
//�Ѵﵽ�����ǵ���,�����֣���λ������
#define ERR_RISK_UPDOWN_OPEN						  ERR_RISK + 0x1
//�Ѵﵽ�����ǵ���,��ֹ����
#define ERR_RISK_UPDOWN_LIMIT						  ERR_RISK + 0x2
//�Ѵﵽ�����ǵ���,��ֹ���֣���ղ�λ
#define ERR_RISK_UPDOWN_CLOSE_LIMIT					  ERR_RISK + 0x3
//�Ѵﵽ�����ǵ���,��ֹ���򿪲֣���λ������
#define ERR_RISK_UPDOWN_OPP_LIMIT					  ERR_RISK + 0x4
//�Ѵﵽ�����ǵ���,��ֹ���򿪲֣���ղ�λ
#define ERR_RISK_UPDOWN_OPP_CLOSE_LIMIT				  ERR_RISK + 0x5
//�Ѵﵽ������������,��������
#define ERR_RISK_SINGLE_VALUE_LIMIT					  ERR_RISK + 0x6
//�Ѵﵽ�ֲܳ���������,��������
#define ERR_RISK_TOTAL_VALUE_LIMIT					  ERR_RISK + 0x7
//�Ѵﵽ���ֲ���������,��������
#define ERR_RISK_NET_VALUE_LIMIT					  ERR_RISK + 0x8
//Ʒ�ֶ�ʱǿƽ�Ѵ���
#define ERR_RISK_GLOBAL_PRODUCT_TRIGGER				  ERR_RISK + 0x9
//Ʒ�ֶ�ʱǿƽȫ�ַ���ѽ��
#define ERR_RISK_GLOBAL_PRODUCT_RELIEVE				  ERR_RISK + 0xA
//Ʒ�ָ�ҹǿƽ�Ѵ���
#define ERR_RISK_OVER_NIGHT_PRODUCT_TRIGGER			  ERR_RISK + 0xB
//Ʒ�ָ�ҹǿƽȫ�ַ���ѽ��
#define ERR_RISK_OVER_NIGHT_PRODUCT_RELIEVE			  ERR_RISK + 0xC
//�Ѵﵽ�˺�Ʒ�ֵ����µ���������
#define ERR_RISK_POSITION_SINGLE_VALUE_LIMIT          ERR_RISK + 0xD
//�ѽ���˺�Ʒ�ֵ����µ���������
#define ERR_RISK_POSITION_SINGLE_VALUE_TRIGGER        ERR_RISK + 0xE
//�Ѵﵽ�˺�Ʒ�־��ֲ���������
#define ERR_RISK_NET_POSITION_VALUE_LIMIT		      ERR_RISK + 0xF
//�ѽ���˺�Ʒ�־��ֲ���������
#define ERR_RISK_NET_PRODUCT_POSITION_TRIGGER	      ERR_RISK + 0x10
//�Ѵﵽ�˺�Ʒ���ֲܳ���������
#define ERR_RISK_TOTAL_POSITION_LIMIT                 ERR_RISK + 0x11
//�ѽ���˺�Ʒ���ֲܳ���������
#define ERR_RISK_TOTAL_POSITION_TRIGGER               ERR_RISK + 0x12
//[�ʽ���ָ��][�������ʽ�]��ؾ������Ѵ���
#define ERR_RISK_MONEY_PRIORITY_WARNING				  ERR_RISK + 0x13
//[�ʽ���ָ��][�������ʽ�]��ؾ������ѽ��
#define ERR_RISK_MONEY_PRIORITY_WARNING_RELIEVE		  ERR_RISK + 0x14
//[�ʽ���ָ��][�������ʽ�]��ؽ������Ѵ���
#define ERR_RISK_MONEY_PRIORITY_FORBID				  ERR_RISK + 0x15
//[�ʽ���ָ��][�������ʽ�]��ؽ������ѽ��
#define ERR_RISK_MONEY_PRIORITY_FORBID_RELIEVE		  ERR_RISK + 0x16
//[�ʽ���ָ��][�������ʽ�]���ǿƽ���Ѵ���
#define ERR_RISK_MONEY_PRIORITY_CLOSE				  ERR_RISK + 0x17
//[�ʽ���ָ��][�������ʽ�]���ǿƽ���ѽ��
#define ERR_RISK_MONEY_PRIORITY_CLOSE_RELIEVE		  ERR_RISK + 0x18
//[�ʽ���ָ��][���Ӻ��ʽ�]��ؾ������Ѵ���
#define ERR_RISK_MONEY_INFERIOR_WARNING				  ERR_RISK + 0x19
//[�ʽ���ָ��][���Ӻ��ʽ�]��ؾ������ѽ��
#define ERR_RISK_MONEY_INFERIOR_WARNING_RELIEVE		  ERR_RISK + 0x1A
//[�ʽ���ָ��][���Ӻ��ʽ�]��ؽ������Ѵ���
#define ERR_RISK_MONEY_INFERIOR_FORBID				  ERR_RISK + 0x1B
//[�ʽ���ָ��][���Ӻ��ʽ�]��ؽ������ѽ��
#define ERR_RISK_MONEY_INFERIOR_FORBID_RELIEVE		  ERR_RISK + 0x1C
//[�ʽ���ָ��][���Ӻ��ʽ�]���ǿƽ���Ѵ���
#define ERR_RISK_MONEY_INFERIOR_CLOSE				  ERR_RISK + 0x1D
//[�ʽ���ָ��][���Ӻ��ʽ�]���ǿƽ���ѽ��
#define ERR_RISK_MONEY_INFERIOR_CLOSE_RELIEVE		  ERR_RISK + 0x1E
//[�ʽ���ָ��][�����ն�]��ؾ������Ѵ���
#define ERR_RISK_MONEY_DEGREE_WARNING				  ERR_RISK + 0x1F
//[�ʽ���ָ��][�����ն�]��ؾ������ѽ��
#define ERR_RISK_MONEY_DEGREE_WARNING_RELIEVE		  ERR_RISK + 0x20
//[�ʽ���ָ��][�����ն�]��ؽ������Ѵ���
#define ERR_RISK_MONEY_DEGREE_FORBID				  ERR_RISK + 0x21
//[�ʽ���ָ��][�����ն�]��ؽ������ѽ��
#define ERR_RISK_MONEY_DEGREE_FORBID_RELIEVE		  ERR_RISK + 0x22
//[�ʽ���ָ��][�����ն�]���ǿƽ���Ѵ���
#define ERR_RISK_MONEY_DEGREE_CLOSE					  ERR_RISK + 0x23
//[�ʽ���ָ��][�����ն�]���ǿƽ���ѽ��
#define ERR_RISK_MONEY_DEGREE_CLOSE_RELIEVE		      ERR_RISK + 0x24
//[�ʽ���ָ��][�����տ���]��ؾ������Ѵ���
#define ERR_RISK_MONEY_LOSS_WARNING				      ERR_RISK + 0x25
//[�ʽ���ָ��][�����տ���]��ؾ������ѽ��
#define ERR_RISK_MONEY_LOSS_WARNING_RELIEVE		      ERR_RISK + 0x26
//[�ʽ���ָ��][�����տ���]��ؽ������Ѵ���
#define ERR_RISK_MONEY_LOSS_FORBID				      ERR_RISK + 0x27
//[�ʽ���ָ��][�����տ���]��ؽ������ѽ��
#define ERR_RISK_MONEY_LOSS_FORBID_RELIEVE		      ERR_RISK + 0x28
//[�ʽ���ָ��][�����տ���]���ǿƽ���Ѵ���
#define ERR_RISK_MONEY_LOSS_CLOSE					  ERR_RISK + 0x29
//[�ʽ���ָ��][�����տ���]���ǿƽ���ѽ��
#define ERR_RISK_MONEY_LOSS_CLOSE_RELIEVE		      ERR_RISK + 0x2A
//[�ʽ���ָ��][����̬Ȩ��]��ؾ������Ѵ���
#define ERR_RISK_MONEY_DYNAMIC_WARNING				  ERR_RISK + 0x2B
//[�ʽ���ָ��][����̬Ȩ��]��ؾ������ѽ��
#define ERR_RISK_MONEY_DYNAMIC_WARNING_RELIEVE		  ERR_RISK + 0x2C
//[�ʽ���ָ��][����̬Ȩ��]��ؽ������Ѵ���
#define ERR_RISK_MONEY_DYNAMIC_FORBID				  ERR_RISK + 0x2D
//[�ʽ���ָ��][����̬Ȩ��]��ؽ������ѽ��
#define ERR_RISK_MONEY_DYNAMIC_FORBID_RELIEVE		  ERR_RISK + 0x2E
//[�ʽ���ָ��][����̬Ȩ��]���ǿƽ���Ѵ���
#define ERR_RISK_MONEY_DYNAMIC_CLOSE				  ERR_RISK + 0x2F
//[�ʽ���ָ��][����̬Ȩ��]���ǿƽ���ѽ��
#define ERR_RISK_MONEY_DYNAMIC_CLOSE_RELIEVE		  ERR_RISK + 0x30
//����������󣬻���IDΪ�ջ򲻴���
#define ERR_RISK_INSTRUMENT_ID_NOEXIT	              ERR_RISK + 0x31
//���ģ�������Ѵ���,�����´������ģ��
#define ERR_RISK_MOUDLE_NAME_REPEAT	                  ERR_RISK + 0x32
//���ģ��ID�Ѵ���,�����´������ģ��
#define ERR_RISK_MOUDLE_ID_REPEAT	                  ERR_RISK + 0x33
//���ģ��������󣬸÷��ģ��ID������
#define ERR_RISK_MOUDLE_ID_NOEXIT	                  ERR_RISK + 0x34
//���ģ�����Ѱ����˺ţ��޷�ɾ����
#define ERR_RISK_MOUDLE_ID_BIND_EXIT	              ERR_RISK + 0x35
//�´����ķ���ʽ�ָ�������Ѵ���,���������ͬ���͵ķ���ʽ�ָ��
#define ERR_RISK_MONEY_INDEX_REPEAT	                  ERR_RISK + 0x36
//����ʽ�ָ��������󣬸÷��ģ��ķ���ʽ�ָ�����Ͳ�����
#define ERR_RISK_MONEY_INDEX_NOEXIT	                  ERR_RISK + 0x37
//�ʽ�ָ�꾯���߷��ֵ����С��0
#define ERR_RISK_MONEY_INDEX_WARN_ZERO	              ERR_RISK + 0x38
//�ʽ�ָ������߷��ֵ����С��0
#define ERR_RISK_MONEY_INDEX_FORBID_ZERO	          ERR_RISK + 0x39
//�ʽ�ָ��ǿƽ�߷��ֵ����С��0
#define ERR_RISK_MONEY_INDEX_CLOSE_ZERO	              ERR_RISK + 0x3A
//�����������,�÷��ģ���¸�Ʒ���Ѵ���,�����ظ���Ӹ�Ʒ��
#define ERR_RISK_PRODUCT_CODE_REPEAT	              ERR_RISK + 0x3B
//�����������,�÷��ģ���¸�Ʒ�ֲ�����
#define ERR_RISK_PRODUCT_CODE_NOEXIT	              ERR_RISK + 0x3C
//�����������, ��������µ���������С��0
#define ERR_RISK_OPEN_SINGLE_VOLUME_ZERO	          ERR_RISK + 0x3D
//�����������, ����ֲܳ���������С��0
#define ERR_RISK_TOTAL_VOLUME_ZERO	                  ERR_RISK + 0x3E
//�����������, ��󾻳ֲ���������С��0
#define ERR_RISK_NET_VOLUME_ZERO	                  ERR_RISK + 0x3F
//�����������, �ǵ�������ֵ����ȷ
#define ERR_RISK_NO_UPDOWN_TYPE	                      ERR_RISK + 0x40
//�����������, ����Ȩ�ޡ���λ���������ò�����,�����ڴ����
#define ERR_RISK_UPDOWN_LIMIT_TYPE_ONE                ERR_RISK + 0x41
//�����������, �ǵ���ֵ����С��0
#define ERR_RISK_UPDOWN_NUM_ZERO                      ERR_RISK + 0x42
//�����������, ǿƽʱ���ʱ��ֵ��Ч
#define ERR_RISK_PRODUCT_TIME_NULL                    ERR_RISK + 0x43
//Ʒ�ֶ�ʱǿƽʱ��һ��ʱ���������ʱ�䲻����ͬ
#define ERR_RISK_PRODUCT_TIME_SAME                    ERR_RISK + 0x44
//�����������,Ʒ�ָ�ҹǿƽ���ն�ָ��ֵ����С��0
#define ERR_RISK_PRODUCT_NIGHT_TIME_ZERO              ERR_RISK + 0x45
//ϵͳ�ڲ���������,δ��ȡ�����ģ���ptr
#define ERR_RISK_CENTER_NULL_PTR					  ERR_RISK + 0x46
//ϵͳ�����̨δ���˻����÷��ģ��
#define ERR_RISK_MOUDLE_NOEXIT_BY_USER			      ERR_RISK + 0x47
//[�ʽ���ָ��][�������ʽ�(�������)]���ǿƽ�Ѵ���
#define ERR_BASE_RISK_SELF_MONEY_CLOSE				  ERR_RISK + 0x48

/***********************����������ģ����ش��� [0x10900-0x109FF] **************/
#define ERR_YUN								          0x10900
//��������Ϣ������
#define ERR_CONDITION_NOEXIST						ERR_YUN +  0x1
//��������Ϣ�Ѵ���
#define ERR_CONDITION_ALREADYEXIST					ERR_YUN +  0x2
//ֹӯֹ����Ϣ������
#define ERR_STOP_PROFIT_NOEXIST						ERR_YUN +  0x3
//ֹӯֹ����Ϣ�Ѵ���
#define ERR_STOP_PROFIT_ALREADYEXIST				ERR_YUN +  0x4

#endif ///ERR_CODE_DEF_H_