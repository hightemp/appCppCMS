ADDON_NAME = test
CGI_BIN_PATH = ../../cgi-bin
ADDON_PATH = $(CGI_BIN_PATH)/addons/$(ADDON_NAME)

all:
	mkdir -p $(ADDON_PATH)
	g++-8 -O3 -fPIC -shared -s addon.cpp -o $(ADDON_PATH)/addon.so

clean:
	rm -f *.so