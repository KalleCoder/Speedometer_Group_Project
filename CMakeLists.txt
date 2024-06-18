cmake_minimum_required(VERSION 3.22)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

#INSTALL FONTS
if(NOT EXISTS "$ENV{HOME}/.local/share/fonts/MaterialIcons.ttf")
    file(COPY "./desktop/client/res/MaterialIcons.ttf" DESTINATION "$ENV{HOME}/.local/share/fonts")
endif()

##############################

# Define the variable that will be used to toggle features
option(TCIP "Enable TCIP" OFF)

# cmake -DTCIP=ON ..
# make

option(CAN "Enable CAN" OFF)
# cmake -DCAN=ON ..
# make

#dont forget 
# cmake -DCAN=OFF .. when you want to remove it

## MAKING THE CLIENT

# Add your source files
set(SOURCES_CLIENT
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/client/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/client/src/canvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/client/src/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/client/src/comservice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/client/src/tcpservice.cpp
)

add_executable(client ${SOURCES_CLIENT})

# Link the Qt6 Widgets library to your application
target_link_libraries(client PUBLIC Qt6::Core Qt6::Widgets)


# Include the header files directory
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/desktop/client/include shared)

# Conditionally add compile definitions for Client
if(CAN)
    target_compile_definitions(client PRIVATE CAN)
endif()

if(TCIP)
    target_compile_definitions(client PRIVATE TCIP)
endif()


#MAKING THE SERVER

# Specify the source files
set(SOURCES_SERVER
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/server/src/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/server/src/comservice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/server/src/tcpservice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/desktop/server/main.cpp
)

# Add the executable
add_executable(server ${SOURCES_SERVER} ${CMAKE_CURRENT_SOURCE_DIR}/desktop/server/include)

# Link the Qt6 Widgets library to your application
target_link_libraries(server PUBLIC Qt6::Core Qt6::Widgets)

# Include the header files directory
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/desktop/server/include shared)

if(CAN)
    target_compile_definitions(server PRIVATE CAN)
endif()

if(TCIP)
    target_compile_definitions(server PRIVATE TCIP)
endif()


