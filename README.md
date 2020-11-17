# Welcom to Sisoc (under development)
Sisoc is the **SI**mple **SO**und **C**ontroller

It provides a simple GUI (made with Qt) that interract with a pulseaudio server.

It is heavily inspired from pavucontrol but aims at being easier to use and customizable.

## Build from sources
You need :
- Qt5
- libpulse
- cmake

You can then clone this repository and build with cmake

```
git clone https://github.com/J-Merle/sisoc
cd sisoc 
mkdir -p build
cd build
cmake ..
make
```

## Install
After building the project, you can simply run `make install` as super user.

Sisoc is now installed and you can use it with the `sisoc` command.
