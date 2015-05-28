CC=gcc

CFLAGS   = -Wunused -Wall -fPIC -I. -c -O3 -D REENTRANT

CFLAGS  += -DGTK_DISABLE_DEPRECATED=1 -DGDK_DISABLE_DEPRECATED
CFLAGS  += -DGDK_PIXBUF_DISABLE_DEPRECATED -DG_DISABLE_DEPRECATED
CFLAGS  += -DGTK_MULTIHEAD_SAFE=1 -DGTK_MULTIDEVICE_SAFE=1

CFLAGS  += `pkg-config gtk+-3.0 --cflags`

LDFLAGS  = `pkg-config gtk+-3.0 --libs`
LDFLAGS += `pkg-config gmodule-2.0 --libs`

FILES = main.o session.o


.c.o:
	$(CC) -c $< $(CFLAGS)

all:$(FILES)
	$(CC) -o diffusio $(FILES) $(LDFLAGS)

clean:
	rm -f *.o diffusio *core*

install:
	rm -rf /usr/share/diffusio/
	cp -fp diffusio /usr/bin
	cp -fp src/diffusio.desktop /usr/share/applications
	mkdir -p /usr/share/diffusio
	mkdir -p /usr/share/diffusio/icon
	mkdir -p /usr/share/diffusio/glade
	cp -fp src/diffusio.glade /usr/share/diffusio/glade
	cp -fp res/diffusio-logo_128.png /usr/share/diffusio/icon
	