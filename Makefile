# --- Configuration ---
CXX = g++
SRCS = $(wildcard src/*.cpp)
TARGET = MinecraftClone
BUILD_DIR = build

# Set DEBUG to 1 to enable debug symbols (e.g., make DEBUG=1)
ifeq ($(DEBUG),1)
    DEBUG_FLAGS = -g
else
    DEBUG_FLAGS =
endif

# --- Platform-specific settings ---
ifeq ($(OS),Windows_NT)
    # Windows settings (using MinGW/g++)
    LIB_DIR = lib/
    LIBS = -L$(LIB_DIR)glfw/lib-mingw-w64 -L$(LIB_DIR)glew/lib -lglfw3 -lglew32s -lopengl32 -lglu32 -lgdi32 -pthread
    INCLUDES = -Iinclude -Iinclude/glfw -Iinclude/glew -Iinclude/glm
    CXXFLAGS = -D GLEW_STATIC -static-libgcc -static-libstdc++ $(DEBUG_FLAGS)
else
    # Linux settings
    LIBS = -lglfw -lGLEW -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXcursor -lpthread -ldl -lm
    INCLUDES = -I/usr/include/GLFW -I/usr/include/GL -I/usr/include/glm -Iinclude/
    CXXFLAGS = $(DEBUG_FLAGS)
endif
# --- End of Configuration ---

OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))

all: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo "Linking executable..."
	$(CXX) $(OBJS) $(LIBS) -o $@

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	@echo "Cleaning build artifacts..."
	@rm -f $(TARGET)
	@rm -rf $(BUILD_DIR)

.PHONY: all clean
PHONY: all clean
