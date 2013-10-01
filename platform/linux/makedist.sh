# Run this script after building to make a distro-agnostic distributable binary package.

mkdir dist
mkdir dist/bin
cp ../../build/incavead ../../build/highscore ../../build/victory ../../build/printmap dist/bin
cp `ldd dist/bin/incavead | grep -o '\W/[^ ]*'` dist/bin
cp ../../data/*.cfg dist
cat << "EOF" > dist/incavead
#!/bin/bash
SCRIPT_PATH=$(dirname $(readlink -f $0))
$SCRIPT_PATH/bin/ld-*.so.2 --library-path $SCRIPT_PATH/bin $SCRIPT_PATH/bin/incavead --singleplayer &
puttytel 0.0.0.0 20020
EOF
chmod +x dist/incavead
