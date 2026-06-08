#!/usr/bin/sh
exec gcc \
-shared \
-nostartfiles \
-std=c23 \
-Wall \
-Wextra \
-O2 \
-fno-plt \
-fpic \
-g0 \
-fuse-ld=bfd \
-Xlinker --build-id=none \
-Xlinker --hash-style=gnu \
-Xlinker -znow \
-Xlinker -zrelro \
-Xlinker -znoexecstack \
-Xlinker -zdefs \
-Xlinker --gc-sections \
-Xlinker --strip-all \
-Xlinker --version-script=version-script.txt \
-Xlinker -hgtk-3-no-portal-cheat.so \
-ogtk-3-no-portal-cheat.so \
gtk-3-no-portal-cheat.c
