CC=g++ -std=c++11
LIBS=-lhpsocket -lpthread -ljsoncpp
CPPS= test.cxx \
      ./WSClientEngine.cpp \
      ./WSClient.cpp
CFLAGS= -std=c++11 -O2
INCLUDE = -I ../../../

TARGET=wsclient

all:
	$(CC) $(CPPS) $(LIBS) $(INCLUDE) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
