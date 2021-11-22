# Build GLFW first
cmake -S deps/glfw -B deps/glfw/build -DGLFW_BUILD_EXAMPLES=false -DGLFW_BUILD_TESTS=false
cmake --build deps/glfw/build

# Buid our stuff
cmake -S . -B build
cmake --build build