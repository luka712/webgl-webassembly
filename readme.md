### Build WASM (WINDOWS OS)

project is set up in such was that it assumes that emscripten sdk (https://emscripten.org/docs/getting_started/downloads.html) is downloaded in 
"C:\emsdk" folder. To set proper paths and run, run *_set_emsdk_and_run.bat* file. Scripts assumes that node module http-server(https://www.npmjs.com/package/http-server) is globally installed. If not simply run "npm install http-server --save-dev" or install it globally "npm install http-server -g".

### WASM build commands (WINDOWS OS)

wasm build commands are located in _build.bat file. Some notable errors: 

- note exported function are *ALWAYS* prefixed with *UNDERSCORE*  <-- This is pain in the *** :) will say undefined exported function
- note every C++ file needs to be *DEFINED* and *ADDED* as source to script <-- if undefined symbol error pops up, most likely missing C++ script
- there are 2 usefull shell files, one robust, one basic index_shell.html and index_shell_basic.html. Change shell files in _build.bat script to get different index.html output file.

### TYPESCRIPT compilation
- npm install
- npx webpack 

### Manual running ( WINDOWS OS)

- Simply another way of running files is to go to "C:\emsdk" folder or wherever you have installed it, run emcmdprompt.bat, navigate back to this folder and run _build.bat from withing command line. After navigating back to this folder, instead of running _build.bat file, you can simply type emscripten compiler commands in console... em++ ... 
