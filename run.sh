#!/bin/bash

echo "running the interface of vcan"
cd VCAN
./vcan.sh

#speed feeder on
cd ../speedo_feeder
apt update &&\
apt install libncurses5-dev libncursesw5-dev ncurses-term dbus-x11 -y
make
gnome-terminal -- bash -c "./speed_feeder; exec bash"
# ./speed_feeder


#running vcan
if [ $? -eq 0 ]; then
	echo "vcan runs successfully..."
else
	echo "failed to run. Exiting..."
	exit 1
fi



# Build Qt application
apt-get update &&  apt-get install \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-serialport-dev \
    qml6-module-qtquick-controls \
    qml6-module-qtquick \
    qml6-module-qtquick-layouts \
    qml6-module-qtquick-window2 \
    qml6-module-qtquick-controls2
	# qt6-base-dev \
    # qt6-declarative-dev \
    # qt6-serialbus-dev \
    # qt6-serialport-dev \
	# x11-apps \
    # qml6-module-qtquick-controls \
    # qml6-module-qtquick \
    # qml6-module-qtqml-workerscript \
    # qml6-module-qtquick-templates \
    # qml6-module-qtquick-layouts \
	# libxcb1 \
    # libxcb-icccm4 \
    # libxcb-image0 \
    # libxcb-keysyms1 \
    # libxcb-randr0 \
    # libxcb-render-util0 \
    # libxcb-shape0 \
    # libxcb-xinerama0 \
    # libxkbcommon-x11-0 \
	# libqt6serialbus6-plugins \
	# qml6-module-qtquick-window2 \
	# qml6-module-qtquick-controls2 \
	# qml6-module-qtquick-layouts

export DISPLAY=${DISPLAY}

cd ../QT/DMC/
echo "Building Qt application"
rm -rf /build/
mkdir -p build/
cd build/
cmake ..
make
if [ $? -eq 0 ]; then
	echo "compiled QT application successfully..."
else
	echo "ompiled QT application failed. Exiting..."
	exit 1
fi

# export XDG_RUNTIME_DIR=/tmp/runtime-$USER
export XDG_RUNTIME_DIR=/tmp/runtime-$USER

mkdir -p $XDG_RUNTIME_DIR
chmod 0700 $XDG_RUNTIME_DIR

# export QT_DEBUG_PLUGINS=1


# export QT_DEBUG_PLUGINS=1
if [ -f "appDMC" ] ; then
	./appDMC
else
	echo "Error: Qt executable not found..."
	exit 1
fi


