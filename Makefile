src = $(wildcard *.c src/*.c)
obj = $(patsubst %.c, %.o, $(src))

LIB = -ldl

CC = gcc

CFLAGS = -pipe -Wall -O2 
CFLAGS += -I./ 
CFLAGS += -I./src/

ifeq ($(shell arch), i686)
	CFLAGS += -march=i686
endif

ifneq ($(shell grep -c ^processor /proc/cpuinfo 2>/dev/null), 1)
	CFLAGS += -DCONFIG_SMP
endif

DEMO_MOD_SRC = ./mod_src/demo_mod.c
DEMO_MOD_OBJ = ./mod_src/demo_mod.o
DEMO_MOD_TARGET = ./mod/demo_mod.so

TARGET = clibmain

all:: $(DEMO_MOD_TARGET) $(TARGET)

$(DEMO_MOD_OBJ): $(DEMO_MOD_SRC)
	${CC} -fPIC -c -o  $(DEMO_MOD_OBJ) $(DEMO_MOD_SRC)

${DEMO_MOD_TARGET}: $(DEMO_MOD_OBJ)
	${CC} -shared -o ${DEMO_MOD_TARGET} $(DEMO_MOD_OBJ)

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
	@rm -rf $(DEMO_MOD_OBJ) ${DEMO_MOD_TARGET}
