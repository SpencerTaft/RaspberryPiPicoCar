:::To build:::

in dev_env environment visual studio code developer console:

setx PICO_SDK_PATH "c:/path/to/pico-sdk"
then close the window

in dev_env environment visual studio code developer console:

cd build
cmake -G "NMake Makefiles" ..
nmake
