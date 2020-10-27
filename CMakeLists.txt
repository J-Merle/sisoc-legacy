cmake_minimum_required(VERSION 3.17)

project(Sisoc, VERSION 0.1)
set(QT_MINIMUM_VERSION "5.15.1")

find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)

add_executable(Sisoc src/main.cpp)

target_link_libraries(Sisoc PRIVATE Qt5::Widgets)
