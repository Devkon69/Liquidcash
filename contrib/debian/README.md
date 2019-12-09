
Debian
====================
This directory contains files used to package liquidcashd/liquidcash-qt
for Debian-based Linux systems. If you compile liquidcashd/liquidcash-qt yourself, there are some useful files here.

## liquidcash: URI support ##


liquidcash-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install liquidcash-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your liquidcash-qt binary to `/usr/bin`
and the `../../share/pixmaps/liquidcash128.png` to `/usr/share/pixmaps`

liquidcash-qt.protocol (KDE)

