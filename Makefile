-include config.mk

TARGET    = ddraw.dll
LDFLAGS   = -Wl,--enable-stdcall-fixup -s -static -shared
CFLAGS    = -Iinc -O2 -march=i486 -Wall
LIBS      = -lgdi32 -lwinmm -lpsapi -ldbghelp -lole32

CC        = i686-w64-mingw32-gcc
WINDRES  ?= i686-w64-mingw32-windres

ifdef DEBUG
	CFLAGS   += -D _DEBUG -D _DEBUG_X
endif

.PHONY: clean all
all: $(TARGET)

$(TARGET): $(wildcard src/*.c) $(wildcard src/*/*.c)
	$(WINDRES) -J rc res.rc res.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ exports.def res.o $(LIBS)

clean:
	$(RM) $(TARGET) res.o
