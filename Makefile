#
# Created by: David Kviloria
# Last modified: Sun, May, 02 2021
#

CCX := g++ -std=c++17
COMPILER_FLAGS = -w

AR := ar rvc

DEPS_DIR := deps

GLAD_DIR					:= $(DEPS_DIR)/glad
GLAD_HEADERS			:= -I./$(GLAD_DIR)/include
GLAD_LIB					:= $(GLAD_DIR)/libglad.a

GLFW_DIR 					:= $(DEPS_DIR)/glfw
GLFW_HEADERS 			:= -I./$(GLFW_DIR)/include/
GLFW_LIB 					:= $(GLFW_DIR)/src/libglfw.so.3.4

GLM_DIR						:= $(DEPS_DIR)/glm
GLM_HEADERS				:= -I./$(GLM_DIR)

IMGUI_DIR					:= $(DEPS_DIR)/imgui
IMGUI_HEADERS			:= -I./$(IMGUI_DIR)
IMGUI_SRC					:= $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

ENGINE_DIR 				:= engine
ENGINE_HEADERS 		:= -I$(ENGINE_DIR)/
ENGINE_SOURCE 		:= $(ENGINE_DIR)/source

BIN-editor 				:= build-editor
BIN-debug					:= build-debug
BIN-release				:= build-release

SANDBOX_DIR 			:= sandbox
SANDBOX_HEADERS 	:= -I./$(SANDBOX_DIR)/include
SANDBOX_SOURCE 		:= $(SANDBOX_DIR)/source
SANDBOX_OUTPUT 		:= build/sandbox
SANDBOX_FlAGS			:= $(COMPILER_FLAGS)

LIB_HEADERS				:= libs/

LINKER_FLAGS 			:= $(GLAD_LIB) $(GLFW_LIB) -lGL -lX11 -ldl -lpthread -lrt \
	 -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lGLU -lGL

EDITOR_HEADERS 		:= $(IMGUI_HEADERS) 
COMMON_HEADERS		:= $(SANDBOX_HEADERS) $(ENGINE_HEADERS) $(GLAD_HEADERS) \
	$(GLFW_HEADERS) $(GLM_HEADERS) 

clean:
	rm -rf *.a *.o

build:
	cd $(GLFW_DIR) && cmake -DBUILD_SHARED_LIBS=ON . && make \
	&& cd ../.. && cd $(GLAD_DIR) && make build \

editor: 
	$(CCX) $(SANDBOX_SOURCE)/app.cpp $(IMGUI_SRC) -o $(SANDBOX_OUTPUT)/$(BIN-editor) \
	 $(COMMON_HEADERS) $(EDITOR_HEADERS) $(SANDBOX_FlAGS) $(LINKER_FLAGS)

debug:
	$(CCX) -g $(SANDBOX_SOURCE)/app.cpp -o $(SANDBOX_OUTPUT)/$(BIN-debug) \
	 $(COMMON_HEADERS) $(SANDBOX_FlAGS) $(LINKER_FLAGS)

release:
	$(CCX) -Ofast $(SANDBOX_SOURCE)/app.cpp -o $(SANDBOX_OUTPUT)/$(BIN-release) \
	$(COMMON_HEADERS) $(SANDBOX_FlAGS) $(LINKER_FLAGS)

run-editor:
	./$(SANDBOX_OUTPUT)/$(BIN-editor)

run-debug:
	./$(SANDBOX_OUTPUT)/$(BIN-debug)

run-release:
	./$(SANDBOX_OUTPUT)/$(BIN-release)

.PHONY: editor release build clean run-debug debug run-release run-editor
