cmake_minimum_required(VERSION 3.10)
project(XarxaSocial C)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Target)

file(GLOB_RECURSE SOURCES "src/*.c")

add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
add_executable(XarxaSocial ${SOURCES})

target_include_directories(XarxaSocial PUBLIC 
    "src"
    "src/menu"
    "src/menu/list_users"
    "src/menu/new_user"
    "src/menu/operate_user"
    "src/menu/operate_user/ceo_utils"
    "src/menu/operate_user/manage_firends"
    "src/menu/operate_user/manage_posts"
    "src/menu/operate_user/manage_requests"
    "src/network"
    "src/utils"
)

if(WIN32)
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES 
        "${CMAKE_SOURCE_DIR}/Target/XarxaSocial.ilk;${CMAKE_SOURCE_DIR}/Target/XarxaSocial.pdb"
    )
endif()