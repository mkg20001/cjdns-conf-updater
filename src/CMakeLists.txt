cmake_minimum_required(VERSION 3.19)
project(cjdns_conf_updater)

set(CMAKE_CXX_STANDARD 20)

add_executable(cjdns_conf_updater conf-updater.c conf-updater.h)

install(TARGETS cjdns_conf_updater DESTINATION bin)
