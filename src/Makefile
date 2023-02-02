CC=gcc
LC = lcov

CFLAGS = -c -Wall -Wextra -Werror -std=c11 # -fsanitize=address -g
AFLAGS = ar rc
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LCOVFLAGS = -c -d . -o

LIBSOURCES = $(wildcard Widget/c_part/parser.c Widget/c_part/render.c Widget/c_part/matrix.c)
TESTSOURSES = $(wildcard tests/*.c)
SOURCES = $(LIBSOURCES) $(TESTSOURSES)
LIBOBJECTS = $(patsubst %.c, %.o, $(LIBSOURCES))
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
EXECUTABLE = test
PROJECT_NAME = Viewer

ifeq ($(shell uname -s),Linux)
OPEN_CMD = xdg-open
OFLAGS =  -lcheck -lsubunit -lm -lrt -lpthread -lgcov -o 
endif
ifeq ($(shell uname -s),Darwin) # MacOS
OPEN_CMD = open
OFLAGS = -lcheck -lm -lpthread -lgcov -o
endif

all: clean gcov_report dvi install run	

install: 
	cd Widget && qmake Widget.pro
	cd Widget && make
	cd Widget && make clean

run:
	cd Widget && open Widget.app

dvi:
	latex ./Documentation/3DViewer.tex
	mv ./3DViewer.dvi ./Documentation
	rm -rf ./3DViewer.aux ./3DViewer.log

dist: install
	tar -cvf 3DViewer.tar Documentation/3DViewer.dvi 
	Applications/Widget.app
	gzip 3DViewer.tar

clang:
	bash style.sh

test: $(OBJECTS)
	$(CC) $(OBJECTS) $(OFLAGS) $@
	./test

gcov_report: test
	$(LC) $(LCOVFLAGS) report.info
	genhtml -o reportdir report.info
	$(OPEN_CMD) ./reportdir/index.html

leakscheck: test
	leaks --atExit -- ./test

.c.o:
	$(CC) $(CFLAGS) $< $(GCOVFLAGS) -o $@

uninstall:
	cd Widget && make uninstall
	cd Widget && make clean
	cd Widget && rm -rf Makefile

clean:
	cd Widget && rm -rf .qm/Widget_ru_RU.qm
	cd Widget && rm -rf qrc_qmake_qmake_qm_files.cpp
	cd Widget && rm -rf moc_predefs.h
	cd Widget && rm -rf moc_mainwindow.cpp moc_glwidget.cpp
	cd Widget && rm -rf ui_mainwindow.h ui_glwidget.h
	cd Widget && rm -rf render.o matrix.o parser.o main.o mainwindow.o glwidget.o dgif_lib.o egif_lib.o gif_err.o gif_hash.o gifalloc.o quantize.o qgifimage.o qrc_qmake_qmake_qm_files.o moc_mainwindow.o moc_glwidget.o
	cd Widget && rm -rf *~ core *.core
	cd tests && rm -rf *.gcno
	cd tests && rm -rf *.o
	cd tests && rm -rf *.gcda
	cd Widget/c_part && rm -rf *.gcno
	cd Widget/c_part && rm -rf *.o
	cd Widget/c_part && rm -rf *.gcda
	rm -rf test
	rm -rf test.out
	rm -rf report.info
	rm -rf reportdir
	rm -rf Widget/.qm 
	rm -rf Widget/.qmake.stash
	cd Widget && rm -rf Widget.app
	cd Widget && rm -rf qmake_qmake_qm_files.qrc

installtex:
	brew install --cask mactex
