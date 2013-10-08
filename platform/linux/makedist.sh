# Run this script after building to make a distro-agnostic distributable binary package.

BUILDDIR=$1
DATADIR=$2

mkdir dist
mkdir dist/bin

cp $BUILDDIR/incavead $BUILDDIR/highscore $BUILDDIR/victory $BUILDDIR/printmap dist/bin
cp `ldd dist/bin/incavead | grep -o '\W/[^ ]*'` dist/bin
cp $DATADIR/*.cfg dist

cat << "EOF" > dist/incavead_putty
#!/bin/bash
SCRIPT_PATH=$(dirname $(readlink -f $0))
$SCRIPT_PATH/bin/ld-*.so.2 --library-path $SCRIPT_PATH/bin $SCRIPT_PATH/bin/incavead --singleplayer &
putty telnet://0.0.0.0:20020
EOF

cat << "EOF" > dist/incavead_telnet
#!/bin/bash
SCRIPT_PATH=$(dirname $(readlink -f $0))
$SCRIPT_PATH/bin/ld-*.so.2 --library-path $SCRIPT_PATH/bin $SCRIPT_PATH/bin/incavead --singleplayer &
telnet 0.0.0.0 20020
EOF

chmod +x dist/incavead_putty
chmod +x dist/incavead_telnet

cat << "EOF" > dist/README

To start the game run either 'incavead_putty' or 'incavead_telnet'.

'incavead_putty' launches Putty as a telnet client, while 'incavead_telnet' uses the standard console 'telnet' command.

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

