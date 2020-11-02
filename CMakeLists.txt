cmake_minimum_required(VERSION 3.17)

project(Sisoc, VERSION 0.1)
set(QT_MINIMUM_VERSION "5.15.1")

find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)

set(SRCS 
  src/main.cpp
  src/mainwindow.cpp
)

add_executable(Sisoc ${SRCS})

target_link_libraries(Sisoc PRIVATE Qt5::Widgets ${PULSE_LDFLAGS})

