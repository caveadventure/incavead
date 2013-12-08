# Run this script after cross-platform building to bundle a Windows package.

BUILDDIR=$1
DATADIR=$2
MINGW=/usr/i686-w64-mingw32/


mkdir dist
mkdir dist/bin
cp $BUILDDIR/incavead.exe $BUILDDIR/highscore.exe $BUILDDIR/victory.exe $BUILDDIR/printmap.exe dist/bin

$MINGW/bin/objdump -x dist/bin/incavead.exe | grep 'DLL Name: ' | grep -o ': .*' | grep -o '[^: ]*' | xargs -IX find $MINGW -name X | xargs -IX cp X dist/bin

cp $DATADIR/*.cfg dist

cat << "EOF" > dist/incavead_ascii.bat
@ECHO OFF
start "" /b bin\incavead.exe --singleplayer
start putty -load game telnet://127.0.0.1:20020
EOF

cat << "EOF" > dist/incavead_unicode.bat
@ECHO OFF
start "" /b bin\incavead.exe --unicode --singleplayer
start putty -load game telnet://127.0.0.1:20020
EOF

cat << "EOF" > dist/incavead_tiles.bat
@ECHO OFF
start "" /b bin\incavead.exe --tiles --singleplayer
start putty -load game telnet://127.0.0.1:20020
EOF

cp dist/incavead_unicode.bat dist/incavead.bat

#wget -Pdist 'http://the.earth.li/~sgtatham/putty/latest/x86/puttytel.exe'

# http://jakub.kotrla.net/putty/
cp putty.exe dist
cp putty.conf dist
mkdir -p dist/putty/sessions
cp game.session dist/putty/sessions

cat << "EOF" > dist/README.txt

Run 'incavead_ascii.bat' to launch the game with ASCII graphics.
Run 'incavead_unicode.bat' to launch the game with Unicode graphics.
Run 'incavead_tiles.bat' to launch the game with 'square tiles' graphics.

  P.S. 'incavead.bat' is the same thing as 'incavead_unicode.bat'.

(Note: the game does not require Internet access. Everything is purely offline, Putty is used only as a convenient text-mode rendering client.)
EOF

mv dist incavead
zip -r incavead incavead

