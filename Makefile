-include config.mk

TARGET    = ddraw.dll
LDFLAGS   = -Wl,--enable-stdcall-fixup -s -static -shared
CFLAGS    = -Iinc -O2 -march=i486 -Wall -std=c99
LIBS      = -lgdi32 -lwinmm -ldbghelp -lole32

COMMIT   := $(shell git describe --match=NeVeRmAtCh --always --dirty || echo UNKNOWN)
BRANCH   := $(shell git rev-parse --abbrev-ref HEAD || echo UNKNOWN)

CMDTEST  := $(shell echo \"\")
ifeq ($(CMDTEST),\"\")
	# Windows
	CMDTEST  := $(shell echo "\#")
	ifeq ($(CMDTEST),"\#")
    	# gmake
		ECOMMIT  := $(shell echo \#define GIT_COMMIT "$(COMMIT)" > inc/git.h)
		EBRANCH  := $(shell echo \#define GIT_BRANCH "$(BRANCH)" >> inc/git.h)
	else
		ECOMMIT  := $(shell echo #define GIT_COMMIT "$(COMMIT)" > inc/git.h)
		EBRANCH  := $(shell echo #define GIT_BRANCH "$(BRANCH)" >> inc/git.h)
	endif
else
	# Either *nix or Windows with BusyBox (e.g. w64devkit)
	ECOMMIT  := $(shell echo \#define GIT_COMMIT \"$(COMMIT)\" > inc/git.h)
	EBRANCH  := $(shell echo \#define GIT_BRANCH \"$(BRANCH)\" >> inc/git.h)
endif

CC        = i686-w64-mingw32-gcc
WINDRES  ?= i686-w64-mingw32-windres

ifdef DEBUG
	CFLAGS   += -D _DEBUG -D _DEBUG_X
endif

SRCS     := $(wildcard src/*.c) $(wildcard src/*/*.c) res.rc
OBJS     := $(addsuffix .o, $(basename $(SRCS)))

.PHONY: clean all
all: $(TARGET)

%.o: %.rc
	$(WINDRES) -J rc $< $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ exports.def $(LIBS)

clean:
	$(RM) $(TARGET) $(OBJS) || del $(TARGET) $(subst /,\\,$(OBJS))
