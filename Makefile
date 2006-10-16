#############################################################################
# Makefile for building: Hausaufgaben
# Generated by qmake (1.07a) (Qt 3.3.5) on: Sun Jan  1 21:23:08 2006
# Project:  Hausaufgaben.pro
# Template: app
# Command: $(QMAKE) -o Makefile Hausaufgaben.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT
CXXFLAGS = -pipe -Wall -W -O2 -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED -DQT_TABLET_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/share/qt3/mkspecs/default -I. -I. -I/usr/include/qt3
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L/usr/share/qt3/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11 -lm -lpthread
AR       = ar cqs
RANLIB   = 
MOC      = /usr/share/qt3/bin/moc
UIC      = /usr/share/qt3/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = hausaufgaben.h \
		TfmFortschritt.h \
		TfmMain.h
SOURCES = hausaufgaben.cpp \
		main.cpp \
		TfmFortschritt.cpp \
		TfmMain.cpp
OBJECTS = hausaufgaben.o \
		main.o \
		TfmFortschritt.o \
		TfmMain.o
FORMS = 
UICDECLS = 
UICIMPLS = 
SRCMOC   = moc_hausaufgaben.cpp \
		moc_TfmFortschritt.cpp \
		moc_TfmMain.cpp
OBJMOC = moc_hausaufgaben.o \
		moc_TfmFortschritt.o \
		moc_TfmMain.o
DIST	   = Hausaufgaben.pro
QMAKE_TARGET = Hausaufgaben
DESTDIR  = 
TARGET   = Hausaufgaben

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: Hausaufgaben.pro  /usr/share/qt3/mkspecs/default/qmake.conf /usr/share/qt3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile Hausaufgaben.pro
qmake: 
	@$(QMAKE) -o Makefile Hausaufgaben.pro

dist: 
	@mkdir -p .tmp/Hausaufgaben && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/Hausaufgaben/ && ( cd `dirname .tmp/Hausaufgaben` && $(TAR) Hausaufgaben.tar Hausaufgaben && $(GZIP) Hausaufgaben.tar ) && $(MOVE) `dirname .tmp/Hausaufgaben`/Hausaufgaben.tar.gz . && $(DEL_FILE) -r .tmp/Hausaufgaben

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:

yaccclean:
lexclean:
clean: mocclean
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

hausaufgaben.o: hausaufgaben.cpp hausaufgaben.h

main.o: main.cpp TfmMain.h \
		hausaufgaben.h \
		TfmFortschritt.h

TfmFortschritt.o: TfmFortschritt.cpp TfmFortschritt.h

TfmMain.o: TfmMain.cpp TfmMain.h \
		hausaufgaben.h \
		TfmFortschritt.h

moc_hausaufgaben.o: moc_hausaufgaben.cpp  hausaufgaben.h 

moc_TfmFortschritt.o: moc_TfmFortschritt.cpp  TfmFortschritt.h 

moc_TfmMain.o: moc_TfmMain.cpp  TfmMain.h hausaufgaben.h \
		TfmFortschritt.h

moc_hausaufgaben.cpp: $(MOC) hausaufgaben.h
	$(MOC) hausaufgaben.h -o moc_hausaufgaben.cpp

moc_TfmFortschritt.cpp: $(MOC) TfmFortschritt.h
	$(MOC) TfmFortschritt.h -o moc_TfmFortschritt.cpp

moc_TfmMain.cpp: $(MOC) TfmMain.h
	$(MOC) TfmMain.h -o moc_TfmMain.cpp

####### Install

install:  

uninstall:  
