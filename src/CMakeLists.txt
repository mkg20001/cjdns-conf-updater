cmake_minimum_required(VERSION 3.19)
project(cjdns_conf_updater)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DIS_DEBUG")
file(READ "${CMAKE_SOURCE_DIR}/nodes.ipv4.conf" NODES_IPV4)
file(READ "${CMAKE_SOURCE_DIR}/nodes.ipv6.conf" NODES_IPV6)

string(REGEX REPLACE "\n" " \\\\ \n" NODES_IPV4 "${NODES_IPV4}")
string(REGEX REPLACE "\n" " \\\\ \n" NODES_IPV6 "${NODES_IPV6}")

configure_file(conf-updater.h.in conf-updater.h)

add_executable(cjdns_conf_updater conf-updater.c)
target_include_directories(cjdns_conf_updater PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS cjdns_conf_updater DESTINATION bin)
