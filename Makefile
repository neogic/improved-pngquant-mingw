# Makefile for pngquant

/* NWS: download the libpng and zlip binaries (.dll), sources (.h etc) and dev files (.lib etc) from:
     http://gnuwin32.sourceforge.net/packages/libpng.htm
     http://gnuwin32.sourceforge.net/packages/zlib.htm 
   Extract source ZIPs to "libpng"/"zlib" sibling folders. Copy into them the "lib" folder from the respective dev file ZIPs.
*/

CC=gcc

# Change this to point to directory where include/png.h can be found (NWS: this is unneeded for MinGW):
SYSTEMLIBPNG=/usr/X11

# Alternatively, build libpng and zlib in these directories:
CUSTOMLIBPNG = ../libpng
CUSTOMZLIB = ../zlib

CFLAGS = -std=gnu99 -O3 -Wall -I. -I$(CUSTOMLIBPNG) -I$(CUSTOMZLIB) -I$(SYSTEMLIBPNG)/include/ -funroll-loops -fomit-frame-pointer

/* NWS: assume libpng/zlib .lib files will be in "lib" sub-folders */
LDFLAGS = -L$(CUSTOMLIBPNG)/lib/ -L$(CUSTOMZLIB)/lib/ -L$(SYSTEMLIBPNG)/lib/ -L/usr/lib/ -lz -lpng -lm

OBJS = pngquant.o rwpng.o pam.o

all: pngquant

pngquant: $(OBJS)
	/* NWS: output to "bin/pngquanti.exe" */
	$(CC) -o ./bin/pngquanti $(OBJS) $(LDFLAGS)

clean:
	rm -f pngquant $(OBJS)

