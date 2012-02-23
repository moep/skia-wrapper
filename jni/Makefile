RELEASE=Debug
SRC = src
SKIA_SRC = skia_src
TARGET = test
JAVA_HOME ?= /usr/lib/jvm/java-6-sun-1.6.0.26/include

CXX = g++

DEFS = '-DSK_SCALAR_IS_FLOAT' \
       '-DSK_CAN_USE_FLOAT' \
       '-DSK_SAMPLES_FOR_X' \
       '-DSK_BUILD_FOR_UNIX' \
       '-DSK_USE_POSIX_THREADS' 

CFLAGS = -fPIC \
		 -Wall \
         -Wextra \
         -Wno-unused \
         -Wno-unused-parameter \
         -Wno-c++11-extensions \
         

INCS = -I/usr/include/freetype2 \
       -I$(SKIA_SRC)/gyp/config \
       -I$(SKIA_SRC)/include/config \
       -I$(SKIA_SRC)/include/core \
       -I$(SKIA_SRC)/gyp/ext \
       -I$(SKIA_SRC)/include/images \
       -I$(SKIA_SRC)/include/ports \
       -I$(SKIA_SRC)/include/utils

INCS_JNI = -I/usr/lib/jvm/java-6-sun/include \
           -I/usr/lib/jvm/java-6-sun/include/linux

OBJS = $(SKIA_SRC)/out/$(RELEASE)/obj.target/skhello/src/effects/SkEffects_none.o \
       $(SKIA_SRC)/out/$(RELEASE)/obj.target/skhello/src/images/SkImageDecoder_libpng.o

LIBS = -lfreetype \
       -lpthread \
       -lpng \
       -lGL \
       -lGLU \
       -lcore \
       -limages \
       -lports \
       -lutils \
       -lopts \
       -lopts_ssse3

LD_INPUTS = $(OBJS) \
            $(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp/libcore.a \
            $(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp/libimages.a \
            $(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp/libports.a \
            $(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp/libutils.a \
            $(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp/libopts.a \
            $(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp/libopts_ssse3.a

# This target compiles the Skia hello world application 
helloWorld:
	@echo " (CC) test.cpp"
	@(CXX) $(CFLAGS) $(DEFS) -o $(TARGET) $(INCS) -L$(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp  -Wl,--start-group $(LD_INPUTS) -Wl,--end-group  $(LIBS) $(SRC)/helloWorld.cpp

# This target creates a hello world shared library 
testWrapper:
	@echo " (CC) org_mapsforge_playground_JNITestMain"
	@$(CXX) $(CFLAGS) $(DEFS) -o libtest.so  \
	$(INCS_JNI) $(INCS) \
	-L$(SKIA_SRC)/out/$(RELEASE)/obj.target/gyp  -Wl,--start-group $(LD_INPUTS) -Wl,--end-group  $(LIBS) \
	-shared src/org_mapsforge_playground_JNITestMain.cpp

shared:
	@$(CXX) $(CFLAGS) -c src/FooType.cpp -o footype.o 
#	@$(CXX) -fPIC -o libtest.so $(INCS_JNI) -shared footype.o src/org_mapsforge_playground_JNITestMain.cpp
	@$(CXX) -fPIC -o libtest.so $(INCS_JNI) -shared footype.o src/AllInOneWrapper.cpp

all: testWrapper helloWorld

clean:
	@echo "Cleaning up"
	@rm $(TARGET)	
	@rm libtest.so 
	@rm *.png

removeSources:
	@rm -rf $(SKIA_SRC)
