# Run this script after building to make a distro-agnostic distributable binary package.

BUILDDIR=$1
DATADIR=$2

mkdir dist
mkdir dist/bin

cp $BUILDDIR/incavead $BUILDDIR/highscore $BUILDDIR/victory $BUILDDIR/printmap dist/bin
cp `ldd dist/bin/incavead | grep -o '\W/[^ ]*'` dist/bin
cp $DATADIR/*.cfg dist

cat << "EOF" > dist/incavead_server
#!/bin/bash
SCRIPT_PATH=$(dirname $(readlink -f $0))
$SCRIPT_PATH/bin/ld-*.so.2 --library-path $SCRIPT_PATH/bin $SCRIPT_PATH/bin/incavead $*
EOF

cat << "EOF" > dist/incavead
#!/bin/bash

case $2 in 
ascii) ./incavead_server --singleplayer & ;;
unicode) ./incavead_server --unicode --singleplayer & ;;
*) echo "Usage: ./incavead {putty|telnet} {unicode|ascii}. See README."; exit 1 ;;
esac

case $1 in
putty) putty telnet://0.0.0.0:20020 ;;
telnet) telnet 0.0.0.0 20020 ;;
*) echo "Usage: ./incavead {putty|telnet} {unicode|ascii}. See README."; exit 1 ;;
EOF

chmod +x dist/incavead_server
chmod +x dist/incavead

cat << "EOF" > dist/README

There are four ways to play the game:

 1. With Putty client and ASCII graphics:
    
    $ ./incavead putty ascii

 2. With Putty client and Unicode graphics:

    $ ./incavead putty unicode

 3. With the console telnet client and ASCII graphics:

    $ ./incavead telnet ascii

 4. With the console telnet client and Unicode graphics:

    $ ./incavead telnet unicode


(Putty is usually faster and more configurable as a telnet client, but may require some fiddling with settings.)

Warning: if you want to use Putty, please install it first if you haven't yet. 

For Ubuntu/Debian:

  $ sudo apt-get install putty

For RedHat/Fedora/OpenSUSE:

  $ sudo yum install putty

For Arch:

  $ sudo pacman -S putty


(Note: the game does not require Internet access. Everything is purely offline, telnet/Putty is used only as a convenient text-mode rendering client.)
EOF

