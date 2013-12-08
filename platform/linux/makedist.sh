# Run this script after building to make a distro-agnostic distributable binary package.

BUILDDIR=$1
DATADIR=$2

mkdir dist
mkdir dist/bin

cp $BUILDDIR/incavead $BUILDDIR/highscore $BUILDDIR/victory $BUILDDIR/printmap dist/bin
cp `ldd dist/bin/incavead | grep -o '\W/[^ ]*'` dist/bin
cp $DATADIR/*.cfg dist

cat << "EOF" > dist/.incavead_server
#!/bin/bash
SCRIPT_PATH=$(dirname $(readlink -f $0))
$SCRIPT_PATH/bin/ld-*.so.2 --library-path $SCRIPT_PATH/bin $SCRIPT_PATH/bin/incavead $* &
until grep -q '00000000:4E34' /proc/net/tcp; do true; done
EOF

cat << "EOF" > dist/incavead
#!/bin/bash

MODE=$2
CLIENT=$1

if [[ -z $@ ]]
then
  MODE="unicode"
  CLIENT="telnet"
fi

case $MODE in 
ascii) ./.incavead_server --singleplayer ;;
unicode) ./.incavead_server --unicode --singleplayer ;;
tiles) ./.incavead_server --tiles --singleplayer ;;
*) echo "Usage: ./incavead {putty|telnet} {tiles|unicode|ascii}. See README."; exit 1 ;;
esac

case $CLIENT in
putty) putty telnet://0.0.0.0:20020 ;;
telnet) telnet 0.0.0.0 20020; echo -e '\033[0m' ;;
*) echo "Usage: ./incavead {putty|telnet} {tiles|unicode|ascii}. See README."; exit 1 ;;
esac
EOF

chmod +x dist/.incavead_server
chmod +x dist/incavead

cat << "EOF" > dist/README

There are six ways to play the game:

1) ./incavead putty ascii
2) ./incavead putty unicode
3) ./incavead putty tiles
4) ./incavead telnet ascii
5) ./incavead telnet unicode
6) ./incavead telnet tiles

Ask for 'putty' if you want the Putty client, 
'telnet' for the regular console telnet client.

'ascii' is the simplest pure-ASCII graphics mode, 
'unicode' enables Unicode graphics, and 
'tiles' is the special 'square tiles' Unicode graphics mode.

By default the game will launch the console telnet client and Unicode graphics.


(Putty is sometimes faster and more configurable as a telnet client, but may require some fiddling with settings.)

Warning: if you want to use Putty, please install it first if you haven't yet. 

For Ubuntu/Debian:

  $ sudo apt-get install putty

For RedHat/Fedora/OpenSUSE:

  $ sudo yum install putty

For Arch:

  $ sudo pacman -S putty


(Note: the game does not require Internet access. Everything is purely offline, telnet/Putty is used only as a convenient text-mode rendering client.)
EOF

mv dist incavead
tar -cvzf incavead.tar.gz incavead

