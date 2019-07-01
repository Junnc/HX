CXX = g++
CFLAGS = -Wall -O2 -std=c++11 -Wl,-rpath=./lib
SRCS = 
OBJS =

INCLUDE = -I ./src/common
HXLIBPATH = -L ./lib -L /usr/lib64/mysql/
LIBS = $(wildcard lib/*.so)
HXLIBS = $(patsubst lib/lib%.so, -l%, $(LIBS))
DEPLIBS = -lhpsocket -ljsoncpp -lpthread -llog4cxx -lmysqlclient

TARGET = hx_serv
Modules = ./src/common \
	  ./src/mysqlConnectPool \
	  ./src/NetworkModule \
	  ./src/UserManager \
	  ./src/NewFuture

sub_make = $(MAKE) -C $(1) || exit "$$?";
sub_clean= $(MAKE) clean -C $(1);

.PHONY: all mm mc clean

all: $(TARGET)

mm:
	@ $(foreach n,  $(Modules), $(call sub_make, $(n)))
mc:
	@ $(foreach n,  $(Modules), $(call sub_clean, $(n)))

$(TARGET): src/hx.cpp mm
	 $(CXX) $(CFLAGS) $(INCLUDE) $< -o $(TARGET) $(HXLIBPATH) $(HXLIBS) $(DEPLIBS) 
	
test:
	# modules test
	#
	
clean: mc
	rm -f $(TARGET)
	@ echo -e "\nclean $(TARGET), *.o and *.so SUCCESS."
