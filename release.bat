mkdir build
cd build
cmake ..
cmake --build . --config Release --target OpenQuark
cd Release
OpenQuark.exe