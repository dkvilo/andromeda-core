#
# Created by: David Kviloria
# Last modified: Fri, Mar, 26 2021
#

CCX := g++ -std=c++11
COMPILER_FLAGS = -w

AR := ar rvc

DEPS_DIR := deps

BGFX_HEADERS 			:= -I./$(DEPS_DIR)/bgfx/include -I./$(DEPS_DIR)/bx/include \
																				-I./$(DEPS_DIR)/bimg/include \
																				-I./$(DEPS_DIR)/bgfx/3rdparty \
																				-I./$(DEPS_DIR)/bgfx/examples/common

BGFX_LIB					:= $(DEPS_DIR)/bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so $(DEPS_DIR)/bgfx/.build/linux64_gcc/bin/libbgfxRelease.a $(DEPS_DIR)/bgfx/.build/linux64_gcc/bin/libbxRelease.a $(DEPS_DIR)/bgfx/.build/linux64_gcc/bin/libbimgRelease.a 

GLFW_DIR 					:= $(DEPS_DIR)/glfw
GLFW_HEADERS 			:= -I./$(GLFW_DIR)/include/
GLFW_LIB 					:= $(GLFW_DIR)/src/libglfw.so.3.4

ENGINE_DIR 				:= engine
ENGINE_HEADERS 		:= -I$(ENGINE_DIR)/
ENGINE_SOURCE 		:= $(ENGINE_DIR)/source

SANDBOX_BIN				:= app
SANDBOX_DIR 			:= sandbox
SANDBOX_HEADERS 	:= -I$(SANDBOX_DIR)/include
SANDBOX_SOURCE 		:= $(SANDBOX_DIR)/source
SANDBOX_OUTPUT 		:= build/sandbox
SANDBOX_FlAGS			:= $(COMPILER_FLAGS)

LIB_HEADERS				:= libs/

LINKER_FLAGS 			:= $(BGFX_LIB) $(GLFW_LIB) -lGL -lX11 -ldl -lpthread -lrt

clean:
	rm -rf *.a *.o

build:
	cd deps/bgfx && make linux-release64 && cd ../.. && cd $(GLFW_DIR) \
	&& cmake -DBUILD_SHARED_LIBS=ON . && make

app: 
	$(CCX) $(SANDBOX_SOURCE)/app.cpp -o $(SANDBOX_OUTPUT)/$(SANDBOX_BIN) \
	 $(SANDBOX_HEADERS) $(ENGINE_HEADERS) $(BGFX_HEADERS) \
	  $(GLFW_HEADERS) $(SANDBOX_FlAGS) $(LINKER_FLAGS)

run:
	./$(SANDBOX_OUTPUT)/$(SANDBOX_BIN)

.PHONY: engine app build clean
