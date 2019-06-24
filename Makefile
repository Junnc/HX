CXX = g++
CFLAGS = -Wall -O2 -std=c++11
SRCS =
OBJS =
TARGET = newFuture
Modules = ./src/NetworkModule

sub_make = $(MAKE) -C $(1);
sub_clean= $(MAKE) clean -C $(1);

.PHONY: all mm mc clean

all: $(TARGET)

mm:
	@ $(foreach n,  $(Modules), $(call sub_make, $(n)))
mc:
	@ $(foreach n,  $(Modules), $(call sub_clean, $(n)))

$(TARGET): mm
	# $(CXX) $(OBJS) -o $(TARGET)
	
clean: mc
