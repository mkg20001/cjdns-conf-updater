cmake_minimum_required(VERSION 3.19)
project(cjdns_conf_updater)

set(CMAKE_CXX_STANDARD 20)

if(MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
            "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DIS_DEBUG")
file(READ "${CMAKE_SOURCE_DIR}/nodes.ipv4.conf" NODES_IPV4)
file(READ "${CMAKE_SOURCE_DIR}/nodes.ipv6.conf" NODES_IPV6)

string(REGEX REPLACE "\n" "\\\\n" NODES_IPV4 "${NODES_IPV4}")
string(REGEX REPLACE "\n" "\\\\n" NODES_IPV6 "${NODES_IPV6}")

string(REGEX REPLACE "\"" "\\\\\"" NODES_IPV4 "${NODES_IPV4}")
string(REGEX REPLACE "\"" "\\\\\"" NODES_IPV6 "${NODES_IPV6}")

configure_file(conf-updater.h.in conf-updater.h)

add_executable(cjdns_conf_updater conf-updater.c conf-updater.rc)
target_include_directories(cjdns_conf_updater PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS cjdns_conf_updater DESTINATION bin)
