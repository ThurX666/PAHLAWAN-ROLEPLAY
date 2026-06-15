cd build

mkdir windows
cd windows
del windows.zip

copy ..\Release\sscanf.dll amxsscanf.dll
copy ..\..\LICENSE LICENSE
copy ..\..\pawn.json pawn.json
copy ..\..\README.md README.md

mkdir components
copy ..\Release\sscanf.dll components\sscanf.dll

mkdir plugins
copy ..\Release\sscanf.dll plugins\sscanf.dll

mkdir pawno
cd pawno
mkdir include
copy ..\..\..\sscanf2.inc include\sscanf2.inc
cd ..

mkdir qawno
cd qawno
mkdir include
copy ..\..\..\sscanf2.inc include\sscanf2.inc
cd ..

7z.exe a -tzip windows.zip *
cd ..

mkdir linux
cd linux
del linux.tar.gz

copy ..\Release\libsscanf.so amxsscanf.so
copy ..\..\LICENSE LICENSE
copy ..\..\pawn.json pawn.json
copy ..\..\README.md README.md

mkdir components
copy ..\Release\libsscanf.so components\sscanf.so

mkdir plugins
copy ..\Release\libsscanf.so plugins\sscanf.so

mkdir pawno
cd pawno
mkdir include
copy ..\..\..\sscanf2.inc include\sscanf2.inc
cd ..

mkdir qawno
cd qawno
mkdir include
copy ..\..\..\sscanf2.inc include\sscanf2.inc
cd ..

7z.exe a -ttar -so -an * | 7z.exe a -si linux.tar.gz *
cd ..

cd ..
copy build\windows\windows.zip .
copy build\linux\linux.tar.gz .