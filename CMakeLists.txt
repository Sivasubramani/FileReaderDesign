cmake_minimum_required(VERSION 3.0)
project(FileReaderDesign)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)


FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    MESSAGE(Boost library is found)
    set(Boost_INCLUDE_DIR /Users/siva-6452/FileReaderDesign/boost/include/boost)
    set(Boost_LIBRARY_DIR /usr/local/lib/libboost_iostreams.dylib)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

ADD_LIBRARY(Core src/Helper.cpp src/Helper.h
        src/EnumList/EncryptionList.cpp src/EnumList/EncryptionList.h src/EnumList/CompressionList.h src/EnumList/CompressionList.cpp
        src/Common/CommonFiles.cpp src/Common/CommonFiles.h
        src/Handlers/FileHandler.cpp src/Handlers/FileHandler.h
        src/AESCryption/AES.cpp src/AESCryption/AES.h
        src/Logging/AppLog.cpp src/Logging/AppLog.h
        src/Compression/BoostHeaders.h src/Compression/Bzip2Compression.cpp src/Compression/Bzip2Compression.h src/Compression/GzipCompression.cpp src/Compression/GzipCompression.h
        )
add_executable(FileReaderDesign src/main.cpp)

target_link_libraries(FileReaderDesign
        ${Boost_LIBRARY_DIR}
        Core
        )
add_custom_target(FileReaderDesignMake COMMAND make -C ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        CLION_EXE_DIR=${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
enable_testing()
set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)
add_subdirectory(Google_tests/lib)
#target_compile_definitions(gtest
#        PUBLIC
#        GTEST_LANG_CXX20
#        GTEST_HAS_TR1_TUPLE=0
#        )
#
add_executable(tests)
target_sources(tests
        PRIVATE
        Google_tests/AppLogTest.cpp
        Google_tests/HelperTest.cpp
        Google_tests/FileHandlerTest.cpp
        Google_tests/CompressionTest.cpp
        )
set_target_properties(tests PROPERTIES
        COMPILE_FLAGS "${cxx_strict}"
        )

target_link_libraries(tests
        ${Boost_LIBRARY_DIR}
        gtest
        gtest_main
        Core
        )

add_test(tests tests)
