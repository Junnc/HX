CXX = g++
CFLAGS = -Wall -O2 -std=c++11
SRCS =
OBJS =
TARGET = newFuture
Modules = ./src/common \
	  ./src/mysqlConnectPool \
	  ./src/NetworkModule \
	  ./src/UserManager 

sub_make = $(MAKE) -C $(1) || exit "$$?";
sub_clean= $(MAKE) clean -C $(1);

.PHONY: all mm mc clean

all: $(TARGET)

mm:
	@ $(foreach n,  $(Modules), $(call sub_make, $(n)))
mc:
	@ $(foreach n,  $(Modules), $(call sub_clean, $(n)))

$(TARGET): mm
	# $(CXX) $(OBJS) -o $(TARGET)
	
test:
	# modules test
	#
	
clean: mc
	@ echo -e "\nclean $(TARGET), *.o and *.so SUCCESS."
