CC := g++ -std=c++11
HXBASE = $(shell cd ../..; pwd)
HXSRC = $(HXBASE)/src
HXLIB = $(HXBASE)/lib

INCLUDE_PATH := -I ../mysqlConnectPool/include -I ../common/utils -I ../common/queue \
		-I ../common -I ../common/net
TARGET := libUserManager.so

OBJS :=  CacheUserAllInfo.o DBOperator.o \
	TableCertificationRegRecord.o TableInstitutionMainidMap.o \
	TableUserFunction.o TableUserIdentifyFunction.o \
	TableUserMoneyInfoFunction.o TableUserRelationShipFuntion.o \
	TableSystemSet.o TableLogRecordFunction.o \
	UserAccountDeal.o UserManageCenter.o \
	UserManagerAPI.o \
	DigitalVisa.o \
	AuthrityControl.o \
	GlobalParamLogRecord.o
 
SRCS :=  CacheUserAllInfo.cpp DBOperator.cpp \
	 TableCertificationRegRecord.cpp TableInstitutionMainidMap.cpp \
	TableUserFunction.cpp TableUserIdentifyFunction.cpp \
	TableUserMoneyInfoFunction.cpp TableUserRelationShipFuntion.cpp \
	TableLogRecordFunction.cpp TableSystemSet.cpp \
	UserAccountDeal.cpp UserManageCenter.cpp \
	UserManagerAPI.cpp \
	DigitalVisa.cpp \
	AuthrityControl.cpp \
	GlobalParamLogRecord.cpp


#all: $(TARGET) subdir
all: $(TARGET) 

$(TARGET):$(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS)
	cp $(TARGET) $(HXLIB)

%.o : %.cpp
	$(CC) -fpic -c $< $(INCLUDE_PATH)

clean: 
	rm -f $(TARGET) $(OBJS)
	rm -f $(HXLIB)/$(TARGET)
