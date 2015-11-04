#src = $(wildcard *.c core/*.c)
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

#LIB = -ldl

CC = gcc

CFLAGS = -pipe -Wall -O2 
CFLAGS += -I./ 

ifeq ($(shell arch), i686)
	CFLAGS += -march=i686
endif

ifneq ($(shell grep -c ^processor /proc/cpuinfo 2>/dev/null), 1)
	CFLAGS += -DCONFIG_SMP
endif

TARGET = clibmain

all:: $(TARGET)

${TARGET}:$(obj)
	${CC} -o $@ ${CFLAGS} $^ $(LIB)

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

install:
	@rm -rf ./bin/$(TARGET)
	@cp -f $(TARGET) ./bin

clean:
	@rm -rf ./bin/$(TARGET)
	@rm -rf $(obj) $(TARGET)
