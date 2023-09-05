TARGET     = hamletViewer.a
GCC        = gcc 
FLAGS      = -g -Wall -Werror -Wextra -fno-stack-protector  -std=c11
WAY_OBJ = ./object_files/
SRC    = $(wildcard 3d_parser_obj.c affine_transformations.c)
OBJ    = $(patsubst %.c, $(WAY_OBJ)%.o, $(SRC))

TEST_FLAGS = $(shell pkg-config --cflags --libs check)
OS:=$(shell uname -s)

LM    = -lm

ifeq ($(OS),Darwin)
	LM = 
endif

all : clean install test

$(TARGET) : $(OBJ) 
	@ar cr  $(TARGET) $(OBJ) 

$(WAY_OBJ)%.o : %.c 
	@$(CC) $(FLAGS) $(LM) -c $< -o $@ 

test:  test_all
	rm -f hamletViewer.a
	./test


install: 
	rm -rf ../build_hamlet_3dviewer
	mkdir ../build_hamlet_3dviewer
	cd ../build_hamlet_3dviewer/ && qmake6 ../src/hamletViewer/ && make -j4 && make clean

uninstall: clean
	rm -f ../build_hamlet_3dviewer/.*.stash  ../build_hamlet_3dviewer/hamlet3Dviewer  ../build_hamlet_3dviewer/Makefile
	rm -rf ../build_hamlet_3dviewer

dist:
	rm -rf ../Archive_hamlet_3D_viewer/
	mkdir ../Archive_hamlet_3D_viewer/
	mkdir ../Archive_hamlet_3D_viewer/src/
	mkdir ../Archive_hamlet_3D_viewer/src/object_files/
	cp  -r 3D_parser_obj.c affine_transformations.c three_d_viewer.h hamletViewer ../Archive_hamlet_3D_viewer/src/
	rm -rf dvi/doxygen
	cp  -r dvi ../Archive_hamlet_3D_viewer/src/
	cp  -r files_model_obj ../Archive_hamlet_3D_viewer/src/
	cp  Makefile  ../Archive_hamlet_3D_viewer/src/
	cp  -r tests  ../Archive_hamlet_3D_viewer/src/
	#cp  -r dvi  ../Archive_hamlet_3D_viewer/src/
	tar cvzf ../Archive_hamlet_3D_viewer.tgz ../Archive_hamlet_3D_viewer
	rm -rf ../Archive_hamlet_3D_viewer/

dist_clean:
	rm -rf ../Archive_hamlet_3D_viewer*
	
	
test_all:  test.o $(TARGET) 
	@$(CC) $(WAY_OBJ)test.o $(TARGET) -o test -L. $(TEST_FLAGS) $(LM)

test.o: test.c
	@($(CC) $(CFLAGS) $(LM) -c test.c -o $(WAY_OBJ)test.o) 

test.c: 
	@rm -f test test.c
	@(checkmk clean_mode=1 tests/include.file tests/*.check > test.c)
	@(clang-format -i -style=google test.c)

gcov_report: clean test.c
	$(CC) -fprofile-arcs -ftest-coverage test.c $(SRC)  -o tests/gcov_report $(TEST_FLAGS) $(LM)
	tests/./gcov_report 
	lcov -t "test" -o tests/test.info -c -d .
	genhtml -o report tests/test.info
	@rm -f *.gcda  *.gcno

open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/index.html
else
	xdg-open report/index.html
endif
	
.dvi:
ifeq ($(OS),Darwin)
	rm -rf dvi/doxygen
	brew install 
	doxygen dvi/configure_doc
	open -a "Google Chrome" dvi/doxygen/html/three__d__viewer_8h.html
	open -a "Google Chrome" dvi/3d_viewer_info.html
else
	sudo apt install doxygen
	doxygen dvi/configure_doc
	xdg-open dvi/3d_viewer_info.html
endif

dvi_install:
ifeq ($(OS),Darwin)
	brew install doxygen
else
	sudo apt install doxygen
endif

clang:
	clang-format -n -style=google *.c *.h

clangI:
	clang-format -i -style=google *.c *.h

leak: test_all
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	CK_FORK=no valgrind --leak-check=full  --show-leak-kinds=all -s --track-origins=yes --log-file=leak.log ./test
endif	

clean:
	rm -f $(WAY_OBJ)*.o $(TARGET) *.out *.gc* test test.c *.a tests/*.info  tests/gcov* *.log   *.tex
	rm -rf report
	rm -rf dvi/doxygen

cppcheck:
	cppcheck --enable=all *.c *.h

download: 
ifeq ($(OS),Darwin)
	open -a "Google Chrome" https://disk.yandex.lt/d/2eS3HXfFbibqng
else
	xdg-open https://disk.yandex.lt/d/2eS3HXfFbibqng
endif

to_run :
ifeq ($(OS),Darwin)
	cd ../build_hamlet_3dviewer/hamletViewer.app/Contents/MacOS/ && chmod 557 hamletViewer &&./hamletViewer
else
	cd ../build_hamlet_3dviewer/ && chmod 557 hamletViewer &&./hamletViewer
endif

rename_file:
	mv -f files_model_obj/cube* files_model_obj/cube.obj
	mv files_model_obj/pyramid* files_model_obj/pyramid.obj
	mv files_model_obj/Empty* files_model_obj/Empty.obj
	mv files_model_obj/hamlet_skull* files_model_obj/hamlet_skull.obj

rename_obj:
	mv -f files_model_obj/cube* files_model_obj/cube
	mv files_model_obj/pyramid* files_model_obj/pyramid
	mv files_model_obj/Empty* files_model_obj/Empty
	mv files_model_obj/hamlet_skull* files_model_obj/hamlet_skull
	
clean_all: clean uninstall dist_clean
	
