cmake_minimum_required(VERSION 3.17)

project(Sisoc, VERSION 0.1)
set(QT_MINIMUM_VERSION "5.15.1")

find_package (PkgConfig REQUIRED)
find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

pkg_check_modules(
    PULSE REQUIRED
    libpulse>=5.0
    libpulse-mainloop-glib>=0.9.16
)

include_directories(
    ${PULSE_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
)

set(HDRS
  src/mainwindow.h
)

set(SRCS 
  src/main.cpp
  src/mainwindow.cpp
)

add_executable(Sisoc ${SRCS})

target_link_libraries(Sisoc PRIVATE Qt5::Widgets ${PULSE_LDFLAGS} ${GLIB_LDFLAGS})
