CC := g++ -std=c++11

INCLUDE_PATH := -I ../include

LIB_PATH := -L /usr/lib64/mysql -L../lib

LDLIBS := -l mysqlclient -ldbpool

TARGET := ./bin/libUserManager.so

INC_PATH := ../include

OBJS :=  CacheUserAllInfo.o DBOperator.o \
	TableCertificationRegRecord.o TableInstitutionMainidMap.o \
	TableUserFunction.o TableUserIdentifyFunction.o \
	TableUserMoneyInfoFunction.o TableUserRelationShipFuntion.o \
	TableSystemSet.o TableLogRecordFunction.o \
	UserAccountDeal.o UserManageCenter.o \
	UserManagerAPI.o utility_fun.o \
	DigitalVisa.o json_reader.o \
	json_value.o json_writer.o AuthrityControl.o \
	GlobalParamLogRecord.o
 
SRCS :=  CacheUserAllInfo.cpp DBOperator.cpp \
	 TableCertificationRegRecord.cpp TableInstitutionMainidMap.cpp \
	TableUserFunction.cpp TableUserIdentifyFunction.cpp \
	TableUserMoneyInfoFunction.cpp TableUserRelationShipFuntion.cpp \
	TableLogRecordFunction.cpp TableSystemSet.cpp \
	UserAccountDeal.cpp UserManageCenter.cpp \
	UserManagerAPI.cpp utility_fun.cpp \
	DigitalVisa.cpp ./jsoncpp/json_reader.cpp \
	./jsoncpp/json_value.cpp ./jsoncpp/json_writer.cpp AuthrityControl.cpp \
	GlobalParamLogRecord.cpp


all: $(TARGET) subdir

$(TARGET):$(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS)
	rm -f $(OBJS)

$(OBJS): $(SRCS)
	$(CC) -fpic -c $^ $(INCLUDE_PATH) $(LIB_PATH) $(LDLIBS)

subdir:
	cp *.h $(INC_PATH)
	cp $(TARGET) ../lib

clean: 
	rm -f $(TARGET) $(OBJS)
