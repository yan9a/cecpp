@REM To run the script set VCPKG_ROOT environmental variable for vcpkg root folder

if exist buildw (
rmdir /s /q buildw
)

cmake -B ./buildw -S ./ -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake" -D CMAKE_INSTALL_PREFIX=./target/ &&^
cmake --build ./buildw --config Release &&^
cmake --install ./buildw --config Release &&^
cd buildw/Release &&^
dir &&^
cd ../..
@REM cpack --verbose 

