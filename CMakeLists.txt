cmake_minimum_required(VERSION 3.16)
project(ControlDemoApp)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

set(BOOST_ROOT E:/GitReps/libs/boost_1_79_0)

find_package(Boost 1.79.0 COMPONENTS) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 


set(MY_INCLUDE_DIR
        ${CMAKE_SOURCE_DIR}/include
)

add_executable (ControlDemoApp 
    main.cpp
    )

target_include_directories(ControlDemoApp PUBLIC 
        ${MY_INCLUDE_DIR}
)
endif()