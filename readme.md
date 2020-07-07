* Run emsdk ( this is for Windows OS)

go to folder "C:\emsdk"   // or wherever you have download emscripten sdk https://emscripten.org/docs/getting_started/downloads.html
start "emcmdprompt.bat" which opens command prompt with emscripten paths correctly set 
then navigate to project folder and emscripten shoud be ready to compile 


* Compile 

// note exported function are ALWAYS prefixed with UNDERSCORE  <-- This is pain in the *** :) will say undefined exported function
// note every C functions needs to be defined <-- if undefined symbol pops up, most likely missing C++ script

// there are 2 usefull shell files, one robust, one basic index_shell.html and index_shell_basic.html

em++ src/c_code/main.cpp src/c_code/src/renderer.cpp src/c_code/src/glattribute.cpp src/c_code/src/glindices.cpp  src/c_code/src/shader.cpp -s WASM=1 -o index.html -std=c++17 --shell-file index_shell.html -s NO_EXIT_RUNTIME=1 -s USE_WEBGL2=1 -s USE_SDL=2 -s EXPORTED_FUNCTIONS="['_main', '_clear_color', '_create_shader_material', '_test', '_load_indices_data', '_load_attribute_data', '_geometry_color']" -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"

// for js 
npm install
npx webpack 

* Run 
emrun {file}
or http-server  whatever you use for server usually 