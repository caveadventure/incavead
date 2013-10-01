# Run this script after building to make a distro-agnostic distributable binary package.

BUILDDIR=$1
DATADIR=$2

mkdir dist
mkdir dist/bin

cp $BUILDDIR/incavead $BUILDDIR/highscore $BUILDDIR/victory $BUILDDIR/printmap dist/bin
cp `ldd dist/bin/incavead | grep -o '\W/[^ ]*'` dist/bin
cp $DATADIR/*.cfg dist

cat << "EOF" > dist/incavead
#!/bin/bash
SCRIPT_PATH=$(dirname $(readlink -f $0))
$SCRIPT_PATH/bin/ld-*.so.2 --library-path $SCRIPT_PATH/bin $SCRIPT_PATH/bin/incavead --singleplayer &
putty telnet://0.0.0.0:20020
EOF

chmod +x dist/incavead

cat << "EOF" > dist/README

*Warning*!

To run the game you will first need to install Putty (a telnet client).

For Ubuntu/Debian:

  $ sudo apt-get install putty

For RedHat/Fedora/OpenSUSE:

  $ sudo yum install putty

For Arch:

  $ sudo pacman -S putty


(Note: the game does not require Internet access. Everything is purely offline, Putty is used only as a convenient text-mode rendering client.)
EOF

