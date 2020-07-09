em++^
 src/c_code/main.cpp src/c_code/src/renderer.cpp src/c_code/src/glattribute.cpp src/c_code/src/glindices.cpp  src/c_code/src/shader.cpp^
 src/c_code/src/io/FileManager.cpp^
 -s WASM=1 -s FETCH=1 -s NO_EXIT_RUNTIME=1 -s USE_WEBGL2=1 -s USE_SDL=2^
 -s EXPORTED_FUNCTIONS="['_main', '_clear_color', '_create_shader_material', '_test', '_load_indices_data', '_load_attribute_data', '_geometry_color', '_read_file']"^
 -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"^
 -std=c++17^
 --shell-file shell_files/index_shell.html^
 --preload-file src/shaders/color.shader^
 -o index.html