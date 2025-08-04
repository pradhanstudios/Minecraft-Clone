# --- Configuration ---
# Define the C++ compiler to use
CXX = g++

# Define the source files using the wildcard function for flexibility
# This is a robust way to get all .cpp files in the src directory
SRCS = $(wildcard src/*.cpp)

# Define the output executable name
TARGET = MinecraftClone

# Define the build directory
BUILD_DIR = build

# --- Platform-specific settings ---
ifeq ($(OS),Windows_NT)
    # Windows settings (using MinGW/g++)
    # Library paths should be relative to the project root
    LIB_DIR = lib/
    
    # Pre-compiled static library names
    # The '-L' flags tell the linker where to find the libraries
    LIBS = -L$(LIB_DIR)glfw/lib-mingw-w64 -L$(LIB_DIR)glew/lib -lglfw3 -lglew32s -lopengl32 -lglu32 -lgdi32 -pthread

    # Include directories
    # The '-I' flags tell the compiler where to find header files
    INCLUDES = -Iinclude -Iinclude/glfw -Iinclude/glew -Iinclude/glm

    # C++ compiler flags for Windows
    # -D GLEW_STATIC is crucial for linking with glew32s.a
    # -static-libgcc and -static-libstdc++ for a self-contained executable
    CXXFLAGS = -D GLEW_STATIC -static-libgcc -static-libstdc++
    
else
    # Linux settings
    # Assumes libraries are installed system-wide (e.g., via apt)
    # These are common include and library paths for a Linux system
    INCLUDES = -I/usr/include/GLFW -I/usr/include/GL -I/usr/include/glm
    
    # These are the standard linker flags for GLFW and GLEW on Linux
    LIBS = -lglfw -lGLEW -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXcursor -lpthread -ldl -lm
    
    CXXFLAGS =
endif

# --- End of Configuration ---

# The OBJS variable correctly creates a list of object file names
# e.g., src/main.cpp -> build/main.o
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# The main rule to build everything
# It depends on the final executable, which in turn depends on everything else
all: $(BUILD_DIR)/$(TARGET)

# Rule to create the build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Rule to link all object files into the final executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@echo "Linking executable..."
	$(CXX) $(OBJS) $(LIBS) -o $@

# Pattern rule to compile each source file into its corresponding object file
# The '| $(BUILD_DIR)' is a crucial fix that ensures the build directory exists
# before the compiler tries to write to it.
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

# Clean up build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: all clean