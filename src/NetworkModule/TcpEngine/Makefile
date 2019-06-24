CC=g++
LIBS= -lhpsocket -lpthread -ljsoncpp -llog4cxx
CFLAGS= -std=c++11 -O2

ALL_CPPS= ./TcpServer.cpp \
	  ./TcpServerEngine.cpp \
	  ../TcpHandle/TcpHandle.cpp \
	  ../TcpHandle/EchoHandle/echoHandle.cpp \
	  ./test.cxx

TARGET=serv

$(TARGET):$(ALL_CPPS)
	$(CC) $(ALL_CPPS) $(LIBS) $(CFLAGS) -o $(TARGET)

clean:
	rm $(TARGET) -f
