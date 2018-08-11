#!/bin/bash
set -e
pushd tool
make
popd
pushd Db_Restore
make
popd
mkdir -p bin
rm -f bin/Db_Restore.bin
cp Db_Restore/Db_Restore.bin bin/Db_Restore.bin
mkdir -p html_payload
tool/bin2js bin/Db_Restore.bin > html_payload/payload.js
FILESIZE=$(stat -c%s "bin/Db_Restore.bin")
PNAME=$"Db_Restore"
cp exploit.template html_payload/Db_Restore.html
sed -i -f - html_payload/Db_Restore.html << EOF
s/#NAME#/$PNAME/g
s/#BUF#/$FILESIZE/g
s/#PAY#/$(cat html_payload/payload.js)/g
EOF
rm -f Db_Restore/Db_Restore.bin
rm -f html_payload/payload.js
