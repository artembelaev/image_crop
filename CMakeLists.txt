# CMakeList.txt: проект CMake для image_crop; 

cmake_minimum_required (VERSION 3.8)

project ("image_crop")

#set(Boost_NO_SYSTEM_PATHS ON)
#set(BOOST_ROOT $ENV{BOOST_PATH})
#set(BOOST_INCLUDEDIR ${BOOST_ROOT}/boost)

#set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib64-msvc-14.2)
#set(boost_COMPONENTS
#    "chrono" "regex" "thread"
#)

find_package(Boost COMPONENTS ${boost_COMPONENTS} REQUIRED)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    message(STATUS "boost found! " ${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

set(Boost_USE_STATIC_LIBS   ON)

add_executable (image_crop "image_crop.cpp")
