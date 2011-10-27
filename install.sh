#! /bin/bash

echo "install.sh : Installe qt"
sudo apt-get update || exit 0
sudo apt-get install libqt4-dev g++ || exit 0

echo "install.sh : Compile Qflex"
qmake || exit 0
make || exit 0

echo "install.sh : Installe Qflex"
sudo make install || exit 0


