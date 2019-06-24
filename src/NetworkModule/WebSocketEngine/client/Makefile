CC=g++
LIBS=-lhpsocket -lpthread -ljsoncpp
CPPS= test.cxx \
      ./WSClientEngine.cpp \
      ./WSClient.cpp
CFLAGS= -std=c++11 -O2

TARGET=wsclient

all:
	$(CC) $(CPPS) $(LIBS) $(OPTI) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
