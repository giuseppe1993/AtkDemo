CFLAGS = `pkg-config --cflags glib-2.0 atk atk-bridge-2.0`
LIBS = `pkg-config --libs glib-2.0 atk atk-bridge-2.0` -Wall -g3 -O0 -ggdb3

CC = gcc
SOURCES = $(shell find . -name '*.c')
$(info $$SOURCES is [${SOURCES}])
DEPS = $(patsubst %.c,%.h,$(SOURCES))
OBJ = $(patsubst %.c,%.o,$(SOURCES))

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

demo: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $@.c $^ $(LIBS)

.PHONY:clean

clean:
	rm -rf demo *.o *.a
