# Run this script after cross-platform building to bundle a Windows package.

BUILDDIR=$1
DATADIR=$2
MINGW=/usr/i686-w64-mingw32/

rm -rf incavead*

mkdir dist
mkdir dist/bin
cp $BUILDDIR/incavead.exe $BUILDDIR/highscore.exe $BUILDDIR/victory.exe $BUILDDIR/printmap.exe dist/bin

$MINGW/bin/objdump -x dist/bin/incavead.exe | grep 'DLL Name: ' | grep -o ': .*' | grep -o '[^: ]*' | xargs -IX find $MINGW -name X | xargs -IX cp X dist/bin

$MINGW/bin/strip dist/bin/incavead.exe

cp $DATADIR/*.cfg dist

cat << "EOF" > dist/incavead_ascii.bat
@ECHO OFF
start "" /b bin\incavead.exe --singleplayer
cd tiletel
start tiletel localhost 20020
EOF

cat << "EOF" > dist/incavead_unicode.bat
@ECHO OFF
start "" /b bin\incavead.exe --unicode --singleplayer
cd tiletel
start tiletel localhost 20020
EOF

cat << "EOF" > dist/incavead_tiles.bat
@ECHO OFF
start "" /b bin\incavead.exe --tiles --singleplayer
cd tiletel
start tiletel localhost 20020
EOF

cp dist/incavead_tiles.bat dist/incavead.bat

unzip -d dist tiletel.zip

cat << "EOF" > dist/README.txt

Run 'incavead_ascii.bat' to launch the game with ASCII graphics.
Run 'incavead_unicode.bat' to launch the game with Unicode graphics.
Run 'incavead_tiles.bat' to launch the game with 'square tiles' graphics.

  P.S. 'incavead.bat' is the same thing as 'incavead_tiles.bat'.

(Note: the game does not require Internet access. Everything is purely offline, telnet is used only as a convenient text-mode rendering client.)
EOF

mv dist incavead
zip -r incavead incavead

