CC = gcc
LD = gcc
CFLAGS = -c -g -Wall $(shell pkg-config --cflags --libs gtk+-3.0)
LDFLAGS = -export-dynamic $(shell pkg-config --libs gtk+-3.0)
GLIB_COMPILE_RESOURCES = $(shell pkg-config --variable=glib_compile_resources gio-2.0)

EXE = namegen
SRCS = main.c signal_handler.c namegen.c resources.c
OBJS = ${SRCS:.c=.o}
resources = $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=. --generate-dependencies resources.xml)

.SUFFIXES:
.SUFFIXES: .o .c

.c.o :
	$(CC) $(CFLAGS) -c $<

all: resources.c resources.h $(EXE)

$(EXE): $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS) : namegen.h resources.c

resources.c: resources.xml $(resources)
	$(GLIB_COMPILE_RESOURCES) resources.xml --target=$@ --sourcedir=. --generate-source

resources.h: resources.c
	$(GLIB_COMPILE_RESOURCES) resources.xml --target=$@ --sourcedir=. --generate-header

clean:
	rm -f namegen *.o *~ resources.c resources.h

install: $(EXE)
	sudo cp -i ./namegen_icon.png /usr/share/icons/.
	sudo cp -i $(EXE) /usr/bin/.
	sudo cp -i ./NameGenerator.desktop /usr/share/applications/.


