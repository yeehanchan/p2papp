#############################################################################
# Makefile for building: p2papp
# Generated by qmake (2.01a) (Qt 4.8.6) on: Tue Apr 11 03:51:54 2017
# Project:  p2papp.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -o Makefile p2papp.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cc \
		netsocket.cc \
		client.cc \
		chatdialog.cc \
		p2pmanager.cc moc_netsocket.cpp \
		moc_client.cpp \
		moc_chatdialog.cpp \
		moc_p2pmanager.cpp
OBJECTS       = main.o \
		netsocket.o \
		client.o \
		chatdialog.o \
		p2pmanager.o \
		moc_netsocket.o \
		moc_client.o \
		moc_chatdialog.o \
		moc_p2pmanager.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		p2papp.pro
QMAKE_TARGET  = p2papp
DESTDIR       = 
TARGET        = p2papp

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_chatdialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: p2papp.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtNetwork.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile p2papp.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtNetwork.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile p2papp.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/p2papp1.0.0 || $(MKDIR) .tmp/p2papp1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/p2papp1.0.0/ && $(COPY_FILE) --parents netsocket.hh client.hh chatdialog.hh p2pmanager.hh .tmp/p2papp1.0.0/ && $(COPY_FILE) --parents main.cc netsocket.cc client.cc chatdialog.cc p2pmanager.cc .tmp/p2papp1.0.0/ && $(COPY_FILE) --parents chatdialog.ui .tmp/p2papp1.0.0/ && (cd `dirname .tmp/p2papp1.0.0` && $(TAR) p2papp1.0.0.tar p2papp1.0.0 && $(COMPRESS) p2papp1.0.0.tar) && $(MOVE) `dirname .tmp/p2papp1.0.0`/p2papp1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/p2papp1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_netsocket.cpp moc_client.cpp moc_chatdialog.cpp moc_p2pmanager.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_netsocket.cpp moc_client.cpp moc_chatdialog.cpp moc_p2pmanager.cpp
moc_netsocket.cpp: netsocket.hh
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) netsocket.hh -o moc_netsocket.cpp

moc_client.cpp: client.hh
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) client.hh -o moc_client.cpp

moc_chatdialog.cpp: ui_chatdialog.h \
		client.hh \
		p2pmanager.hh \
		netsocket.hh \
		chatdialog.hh
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) chatdialog.hh -o moc_chatdialog.cpp

moc_p2pmanager.cpp: netsocket.hh \
		p2pmanager.hh
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) p2pmanager.hh -o moc_p2pmanager.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_chatdialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_chatdialog.h
ui_chatdialog.h: chatdialog.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic chatdialog.ui -o ui_chatdialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cc chatdialog.hh \
		ui_chatdialog.h \
		client.hh \
		p2pmanager.hh \
		netsocket.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cc

netsocket.o: netsocket.cc netsocket.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o netsocket.o netsocket.cc

client.o: client.cc client.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o client.o client.cc

chatdialog.o: chatdialog.cc chatdialog.hh \
		ui_chatdialog.h \
		client.hh \
		p2pmanager.hh \
		netsocket.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o chatdialog.o chatdialog.cc

p2pmanager.o: p2pmanager.cc client.hh \
		p2pmanager.hh \
		netsocket.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o p2pmanager.o p2pmanager.cc

moc_netsocket.o: moc_netsocket.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_netsocket.o moc_netsocket.cpp

moc_client.o: moc_client.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_client.o moc_client.cpp

moc_chatdialog.o: moc_chatdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_chatdialog.o moc_chatdialog.cpp

moc_p2pmanager.o: moc_p2pmanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_p2pmanager.o moc_p2pmanager.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

