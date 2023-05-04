cmake_minimum_required(VERSION 3.0.0)
project(rsa_cryptopp VERSION 0.1.0)

# include(CTest)
# enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} crypto++)
# installing crypto++
# apt-cache pkgnames | grep -i crypto++
# sudo apt install libcrypto++6 libcrypto++-utils libcrypto++-dev libcrypto++6-dbg

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
