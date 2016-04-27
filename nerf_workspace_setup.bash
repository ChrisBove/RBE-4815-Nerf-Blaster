#!/bin/bash
  onlyroot="Do not run this as root."
  
if [ $(whoami) == 'root' ];then
echo -e $COLOR$onlyroot$MONO #"Only root can do this operation."
    #DBG_MSG "exit 5"
    exit 0
fi



sudo rosdep init
rosdep update
source /opt/ros/indigo/setup.bash
sudo apt-get -y install python-rosinstall
echo source /opt/ros/indigo/setup.bash >> ~/.bashrc
mkdir -p ~/nerf_workspace/src
cd ~/nerf_workspace/src
catkin_init_workspace
cd ~/nerf_workspace/
catkin_make
source devel/setup.bash
echo source ~/nerf_workspace/devel/setup.bash >> ~/.bashrc
echo alias nerfhome="'cd ~/nerf_workspace/src/nerf/'" >> ~/.bashrc
echo alias nerfmake="'catkin_make install -DCMAKE_INSTALL_PREFIX:PATH=~/nerf_workspace/install -C ~/nerf_workspace -DCMAKE_BUILD_TYPE=Release'" >> ~/.bashrc
echo alias nerfeclipse="'catkin_make --force-cmake -G\"Eclipse CDT4 - Unix Makefiles\" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8 -C ~/nerf_workspace'" >> ~/.bashrc
. ~/.bashrc
cd ~/nerf_workspace/src
wstool init
wstool set nerf https://github.com/ChrisBove/RBE-4815-Nerf-Blaster --git
. ~/.bashrc
wstool update
. ~/.bashrc
cd ~/nerf_workspace/
catkin_make
. ~/.bashrc
