#!/bin/bash
pushd tool
make clean
popd
pushd Db_Restore
make clean
popd
rm -f html_payload/Db_Restore.html
rm -f bin/Db_Restore.bin

