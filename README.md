# VCan Viewer 
is a comprehensive Qt-based application for monitoring and analyzing virtual CAN (vcan) interfaces. It integrates a speed feeder simulation and displays CAN data in real-time.

## Features
- Real-time display of CAN messages from vcan interfaces
- Integrated speed feeder simulation
- Qt-based graphical user interface for data visualization

## Prerequisites
- Linux operating system with vcan support
- Qt6 framework and related modules
- can-utils package
- ncurses library
- Setup and Usage

Clone the repository:
```bash
git clone https://github.com/Ahsanbaloch/VCAN-Viewer
cd vcan-viewer
```
Run the main script:
```bash
./run.sh
```
or 
```bash
sudo bash run.sh
```

## This script performs the following actions:
- Sets up vcan interfaces
- Installs necessary dependencies
- Compiles and runs the speed feeder simulation
- Builds and launches the Qt application

## Script Breakdown
The run_vcan_viewer.sh script:
- Initializes vcan interfaces
- Compiles and runs the speed feeder in a new terminal window
- Installs Qt6 and related dependencies
- Builds the Qt application
- Launches the VCan Viewer application

## Troubleshooting
If you encounter any issues with Qt plugins, the script enables Qt debug output.
Ensure you have the necessary permissions to create and modify vcan interfaces.
Contributing
