# --- Configuration ---
# Define the C++ compiler to use
CXX = g++

# Define the source files using the wildcard function for flexibility
# This is a robust way to get all .cpp files in the src directory
SRCS = $(wildcard src/*.cpp)

# Define the output executable name (will be created in the root directory)
TARGET = MinecraftClone

# Define the build directory for intermediate object files
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
    INCLUDES = -I/usr/include/GLFW -I/usr/include/GL -I/usr/include/glm -Iinclude/
    
    # These are the standard linker flags for GLFW and GLEW on Linux
    LIBS = -lglfw -lGLEW -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXcursor -lpthread -ldl -lm
    
    CXXFLAGS =
endif

# --- End of Configuration ---

# The OBJS variable now creates object files within the build directory
# e.g., src/main.cpp -> build/main.o
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# The main rule to build everything
# It now depends directly on the TARGET executable in the root.
all: $(TARGET)

# Rule to create the build directory if it doesn't exist
# This is a prerequisite for creating object files in that directory.
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Rule to link all object files into the final executable in the root directory
$(TARGET): $(OBJS)
	@echo "Linking executable..."
	$(CXX) $(OBJS) $(LIBS) -o $@

# Pattern rule to compile each source file into its corresponding object file
# The object files are now created in the $(BUILD_DIR) directory.
# The '| $(BUILD_DIR)' ensures the build directory exists before compilation.
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

# Clean up build artifacts
# This rule now removes the executable from the root and the entire build directory.
clean:
	@echo "Cleaning build artifacts..."
	@rm -f $(TARGET) # Remove the executable from the root
	@rm -rf $(BUILD_DIR) # Remove the entire build directory (containing .o files)

.PHONY: all clean
