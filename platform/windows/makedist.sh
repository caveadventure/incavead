# Run this script after cross-platform building to bundle a Windows package.

BUILDDIR=$1
DATADIR=$2
MINGW=/usr/i686-w64-mingw32/


mkdir dist
mkdir dist/bin
cp $BUILDDIR/incavead.exe $BUILDDIR/highscore.exe $BUILDDIR/victory.exe $BUILDDIR/printmap.exe dist/bin

$MINGW/bin/objdump -x dist/bin/incavead.exe | grep 'DLL Name: ' | grep -o ': .*' | grep -o '[^: ]*' | xargs -IX find $MINGW -name X | xargs -IX cp X dist/bin

cp $DATADIR/*.cfg dist

cat << "EOF" > dist/incavead.bat
@ECHO OFF
start "" /b bin\incavead.exe --singleplayer
start putty -load game telnet://127.0.0.1:20020
EOF

#wget -Pdist 'http://the.earth.li/~sgtatham/putty/latest/x86/puttytel.exe'

# http://jakub.kotrla.net/putty/
cp putty.exe dist
cp putty.conf dist
mkdir -p dist/putty/sessions
cp game.session dist/putty/sessions

cat << "EOF" > dist/README.txt

Run 'incavead.bat' to launch the game.

(Note: the game does not require Internet access. Everything is purely offline, Putty is used only as a convenient text-mode rendering client.)
EOF


