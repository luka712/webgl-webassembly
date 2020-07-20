### Build WASM (WINDOWS OS)

- project is set up in such was that it assumes that emscripten sdk (https://emscripten.org/docs/getting_started/downloads.html) is downloaded in 
"C:\emsdk" folder. To set proper paths and build, run *_set_emsdk_and_build.bat* file.

- another way of running files is to go to "C:\emsdk" folder or wherever you have installed it, run emcmdprompt.bat, navigate back to this folder and run _build.bat from withing command line. After navigating back to this folder, instead of running _build.bat file, you can simply type emscripten compiler commands in console... em++ ... 

### WASM build commands (WINDOWS OS)

wasm build commands are located in _build.bat file. Some notable errors: 

- note exported function are *ALWAYS* prefixed with *UNDERSCORE*  <-- This is pain in the *** :) will say undefined exported function
- note every C++ file needs to be *DEFINED* and *ADDED* as source to script <-- if undefined symbol error pops up, most likely missing C++ script
- segmatation fault ( usually happens for non initialized c++ pointer variables. ei Shader* shader never gets called via new Shader())
- there are 2 usefull shell files, one robust, one basic index_shell.html and index_shell_basic.html. Change shell files in _build.bat script to get different index.html output file.

### TYPESCRIPT compilation
- npm install
- npx webpack 

### RUNNING
- Start any desired server, for example http-server(https://www.npmjs.com/package/http-server). If by any chance you do not have it installed, run "npm install http-server" and then simply type "http-server"


### TODO: 
* use smart pointers 
* use vector list
* explore use of inline function