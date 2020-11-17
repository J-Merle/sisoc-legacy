cmake_minimum_required(VERSION 3.17)

project(Sisoc, VERSION 0.1)
set(QT_MINIMUM_VERSION "5.15.1")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets ${QT_MINIMUM_VERSION} REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(
    PULSE REQUIRED
    libpulse>=5.0
    libpulse-mainloop-glib>=0.9.16
)

include_directories(
    ${PULSE_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
)

set(SRCS
  src/sisoc.cpp
  src/mainwindow.cpp
  src/sinkwidget.cpp
  src/sinkinputwidget.cpp
)

add_executable(sisoc ${SRCS})

target_link_libraries(sisoc PRIVATE Qt5::Widgets ${PULSE_LDFLAGS} ${GLIB_LDFLAGS})

install(TARGETS sisoc DESTINATION bin)
