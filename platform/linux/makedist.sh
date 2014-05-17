# Run this script after building to make a distro-agnostic distributable binary package.

BUILDDIR=$1
DATADIR=$2

ARCH=$3

if [[ -z $ARCH ]]
then
  ARCH=x86_64
fi

rm -rf incavead*

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
  MODE="tiles"
  CLIENT="tiletel"
fi

case $MODE in 
ascii) ./.incavead_server --singleplayer ;;
unicode) ./.incavead_server --unicode --singleplayer ;;
tiles) ./.incavead_server --tiles --singleplayer ;;
*) echo "Usage: ./incavead {tiletel|telnet} {tiles|unicode|ascii}. See README."; exit 1 ;;
esac

case $CLIENT in
tiletel) cd tiletel; ./tiletel localhost 20020 ;;
telnet) telnet 0.0.0.0 20020; echo -e '\033[0m' ;;
*) echo "Usage: ./incavead {tiletel|telnet} {tiles|unicode|ascii}. See README."; exit 1 ;;
esac
EOF

chmod +x dist/.incavead_server
chmod +x dist/incavead

tar -C dist -xvzf tiletel-$ARCH.tar.gz

cat << "EOF" > dist/README

There are six ways to play the game:

1) ./incavead built-in client ascii
2) ./incavead built-in client unicode
3) ./incavead built-in client tiles
4) ./incavead telnet ascii
5) ./incavead telnet unicode
6) ./incavead telnet tiles

Ask for 'tiletel' if you want the bundled built-in client. (Built with SDL, so it requires X.)
'telnet' for the regular console telnet client.

'ascii' is the simplest pure-ASCII graphics mode, 
'unicode' enables Unicode graphics, and 
'tiles' is the special 'square tiles' Unicode graphics mode.

By default the game will launch the built-in client with square-tile graphics.

(Note: the game does not require Internet access. Everything is purely offline, telnet is used only as a convenient text-mode rendering client.)

If you want to play online with the built-in client, just do 'cd tiletel; ./tiletel'

EOF

mv dist incavead
tar -cvzf incavead-$ARCH.tar.gz incavead

