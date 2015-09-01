OSMESA_PATH=/opt/osmesa_llvmpipe
LDFLAGS+=`PKG_CONFIG_PATH=$(OSMESA_PATH)/lib/pkgconfig/ pkg-config --libs osmesa`
CFLAGS+=`PKG_CONFIG_PATH=$(OSMESA_PATH)/lib/pkgconfig/ pkg-config --cflags osmesa`
all:
	clang -o osmesa_test osmesa_test.cc $(LDFLAGS) $(CFLAGS) -lGLU

run:
	LD_LIBRARY_PATH=$(OSMESA_PATH)/lib ./osmesa_test
