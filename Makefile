
APP_FILES = $(wildcard app/*/*.cpp)
APP_DIRS = $(wildcard app/*/) .
CGI_BIN_PATH = cgi-bin
CGI_OUTPUT_FILE_NAME = main.cgi

LIBS = -lstdc++ \
		-ldl \
		-lmysqlcppconn \
		/usr/lib/libcgicc.a \
		lib/segvcatch/lib/libsegvcatch.a

CPP_FLAGS=-Wall -fexceptions -fnon-call-exceptions

all:
	+$(MAKE) CPP_FLAGS="$(CPP_FLAGS) -O2" build

debug: 
	+$(MAKE) CPP_FLAGS="$(CPP_FLAGS) -ggdb" build

prepare:
	$(MAKE) prepare -C lib/.
	$(MAKE) prepare -C addons/*/.

run:
	$(CGI_BIN_PATH)/$(CGI_OUTPUT_FILE_NAME)

test:
	cmake tests/CMakeLists.txt
	$(MAKE) -C tests/.

build:
	$(MAKE) -C lib/*/.
	$(MAKE) CGI_BIN_PATH=../../$(CGI_BIN_PATH) -C addons/*/.
	
	g++-8 \
	$(CPP_FLAGS) \
	-s \
		main.cpp \
		$(APP_FILES) \
	-o $(CGI_BIN_PATH)/$(CGI_OUTPUT_FILE_NAME) \
	$(foreach INCLUDE_DIR, $(APP_DIRS), -I$(INCLUDE_DIR)) \
	$(LIBS)

clean:
	rm -f cgi-bin/*.cgi
	rm -f *.cpp.* *.cpp.*
	$(MAKE) clean -C addons/*/.
	$(MAKE) clean -C lib/*/.
	find tests/. -iwholename '*cmake*' -not -name CMakeLists.txt -delete
	rm -f tests/Makefile
	
.PHONY: all test clean addons/*/.
.DEFAULT_GOAL := all