CC=g++
LIBS=-lhpsocket -ljsoncpp -lpthread -llog4cxx -luuid
CPPS=./WSServerEngine.cpp \
     ./WSServer.cpp \
     ../WebSocketHandle/WSHandle.cpp \
     ../WebSocketHandle/EchoHandle/echoHandle.cpp \
     ../Session/Session.cpp \
     ../Session/SessionManager.cpp \
     ../common/utils/utility_fun.cpp \
     test.cxx
CFLAGS= -std=c++11 -O2

TARGET=wsserv

all:
	$(CC) $(CPPS) $(LIBS) $(CFLAGS) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
