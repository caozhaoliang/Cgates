.PHONY:default all 
BINFILE := Cgates

LIBS := z

INCS := ./src ./src/samples/ ./src/common/

LIBPATHS := ./libs

USER_MARCOS := 
test = 0
ifeq ($(test),1)
USER_MARCOS :=$(USER_MARCOS) _TEST_
endif
CFLAGS = -g -Wall #-pg -O2
CC = g++

COMMONSRCS = $(wildcard ./src/*.cpp ./src/samples/*.cpp ./src/common/*.cpp)

COMMONOBJS = $(patsubst %.cpp,%.o,$(COMMONSRCS))

all:$(BINFILE)

$(BINFILE):$(COMMONOBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(addprefix -L,$(LIBPATHS)) $(addprefix -l,$(LIBS))

%.o:%.cpp
	$(CC) $(FLAGS) $(addprefix -D,$(USER_MARCOS)) $(addprefix -I,$(INCS)) -c $< -o $@

clean :
	rm -rf $(COMMONOBJS) $(BINFILE)
