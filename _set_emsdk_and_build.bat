SETLOCAL
SET p=%cd%
CD "C:\emsdk"
CALL ./emsdk activate latest
CALL emsdk_env.bat
CD %p%
CALL _build.bat

