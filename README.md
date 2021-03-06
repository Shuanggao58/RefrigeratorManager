<h2 align="center">Refrigerator manager - Team 5</h2>  
<div align=center><img width="850" height="850" src="https://github.com/Shuanggao58/RefrigeratorManager/blob/main/fig/RM.jpg"/></div>
<h5 align="center">Shang Dong: 2528225D@student.gla.ac.uk, Shuang Gao: 2572218G@student.gla.ac.uk</h2>
<h5 align="center">Yuxin Qin: 2588583Q@student.gla.ac.uk, Linqing Cai: 2508394C@student.gla.ac.uk</h2>
<h5 align="center">Webpage: https://github.com/Shuanggao58/RefrigeratorManager</h2>
<!-- TABLE OF CONTENTS -->

## Contents

<ol>
    <li><a href="#abstract">Abstract</a></li>
	<li><a href="#aim">Aim</a></li>
	<li><a href="#methods">Methods</a></li>
	<li><a href="#hardware">Hardware</a></li>
	<li><a href="#solftware">Solftware</a></li>
		<ul>
		<li><a href="#environment">Environment configuration and compilation</a></li>
		</ul>
	<li><a href="#test">Test</a></li>
		<ul>
		<li><a href="#unit_test">Unit test</a></li>
		<li><a href="#identification_and_weighing">Identification and weighing</a></li>
		</ul>
	<li><a href="#improvement">Improvement</a></li>
	<li><a href="#license">License</a></li>
	<li><a href="#social_media">Social media</a></li>
</ol>
     
***

## Abstract

In order to meet people's higher and higher requirements for healthy life, the system uses multilayer convolution neural network and edge detection technology to realize the refrigerator fruit management system based on image recognition and weighing, which is conducive to enrich the smart home system and guide people's healthy life.

## Aim

The system is built for fresh foods, especially fruits. 

![image](https://user-images.githubusercontent.com/71794241/113421148-26174400-93fd-11eb-8c38-90412bca3af6.png)

We buy and eat fruits regularly in our daily life. There are 2 questions: 
1. Do you want to know how many calories you have gotten from those lovely fruits? 
2. Do you want a reminder to help you eat them in their optimal period?

Then use our system!

## Methods

Now, let’s see how to implement the system in 4 steps.

First, what can we do by the camera? It will turn on by the signal of weight changing and send several images to the raspberry Pi. There is an agent trained by AI technics to recognize different fruits.

Second, weighting module. We choose HX711 model to get the weight signal and send it to Raspberry Pi. The putting date will be recorded as well.

Third, training and classification module. For the training part, we use a seven-layer convolutional neural network. The first layer is a convolutional layer, the input is a 100×100×3 picture, and 64 convolution kernels with a size of 5×5 and a depth of 3 are used. The second layer is the pooling layer, which reduces the picture size to 50×50. The third and fourth layers are convolutional and pooling at the same time, and finally 25×25×128 picture data is obtained. The fifth and sixth layers are fully connected layers, and use the dropout algorithm with a dropout coefficient of 0.5. The seventh layer is a fully connected output layer. For the classification part, there is two methods, the one is use cpkt model and call it in the python using tensorflow and another is use opencv.dnn to call the pb model, but we should save the model in .pb mode.

Fourth, we fisrt detect the edge of the target and then we classify images according to the pictures cut from the contours. For edge recognition, we use opencv's findcontour function. 
The method of this function comes from "Satoshi Suzuki and others. Topological structural analysis of digitized binary images by border following. Computer Vision, Graphics, and Image Processing, 30(1):32–46, 1985." This algorithm is performed on global pixels Scan one by one and find the relationship between the value of each pixel and the value of surrounding pixels to determine the inner and outer contours. In addition, we also try to use the Laplacian operator to find the boundary with the largest pixel difference by using the Laplacian operator's characteristic of being more sensitive to the derivative gradient.

Now we have all the data we want. It will all processing in the Raspberry Pi and work out the calories by the weight and fruit species. We will also get the expected optimal eating period by current images and fruit species.

## Hardware

The project is centered by Raspberry Pi embedded in the domestic refrigerators. The Raspberry Pi is 3b generation, and it has 256MB memory and 1G swap settings.

![image](https://user-images.githubusercontent.com/71794241/113420739-675b2400-93fc-11eb-8bfb-0d9ca3bd88e5.png)

Two extra devices are needed. One is camera located on the top of the preservation layer. Another is the weight sensor embedded in the bottom of the layer.

![image](https://user-images.githubusercontent.com/71794241/113421316-77273800-93fd-11eb-8910-e737a961e74d.png) ![image](https://user-images.githubusercontent.com/71794241/113421354-84dcbd80-93fd-11eb-93cf-55108f73bfd7.png)

The camera and the weight sensor will work collaboratively. The camera only turns on to catch images of the fruits after the weight sensor feeling weight changes. Then, the images and weight data will send to Raspberry Pi and processing in it.

Finally, we add the system to a wi-fi based LAN to make it participated in the network of smart home. We believe it will show huge energy after version iteration.

![image](https://user-images.githubusercontent.com/71794241/113417215-85715600-93f5-11eb-9e79-2c5fd4d5c2f5.png)

## Solftware

1. Burning Raspberry Pi system
2. Install OpenCV and tensorflow

The system is developed in Linux environment, and main used C++.

### Environment configuration and compilation
1.install opencv(3.5.0)
```
sudo apt -y update
sudo apt -y upgrade

sudo apt-get -y remove x264 libx264-dev

## Install dependencies
sudo apt-get -y install build-essential checkinstall cmake pkg-config yasm
sudo apt-get -y install git gfortran
sudo apt-get -y install libjpeg8-dev libjasper-dev libpng12-dev

sudo apt-get -y install libtiff5-dev

sudo apt-get -y install libtiff-dev

sudo apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev
sudo apt-get -y install libxine2-dev libv4l-dev
cd /usr/include/linux
sudo ln -s -f ../libv4l1-videodev.h videodev.h
cd $cwd

sudo apt-get -y install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
sudo apt-get -y install libgtk2.0-dev libtbb-dev qt5-default
sudo apt-get -y install libatlas-base-dev
sudo apt-get -y install libmp3lame-dev libtheora-dev
sudo apt-get -y install libvorbis-dev libxvidcore-dev libx264-dev
sudo apt-get -y install libopencore-amrnb-dev libopencore-amrwb-dev
sudo apt-get -y install libavresample-dev
sudo apt-get -y install x264 v4l-utils

# Optional dependencies
sudo apt-get -y install libprotobuf-dev protobuf-compiler
sudo apt-get -y install libgoogle-glog-dev libgflags-dev
sudo apt-get -y install libgphoto2-dev libeigen3-dev libhdf5-dev doxygen

sudo apt-get -y install python3-dev python3-pip
sudo -H pip3 install -U pip numpy
sudo apt-get -y install python3-testresources

cd $cwd
# Install virtual environment
python3 -m venv OpenCV-"$cvVersion"-py3
echo "# Virtual Environment Wrapper" >> ~/.bashrc
echo "alias workoncv-$cvVersion=\"source $cwd/OpenCV-$cvVersion-py3/bin/activate\"" >> ~/.bashrc
source "$cwd"/OpenCV-"$cvVersion"-py3/bin/activate

# now install python libraries within this virtual environment
sudo sed -i 's/CONF_SWAPSIZE=100/CONF_SWAPSIZE=1024/g' /etc/dphys-swapfile
sudo /etc/init.d/dphys-swapfile stop
sudo /etc/init.d/dphys-swapfile start
pip install numpy dlib
# quit virtual environment
deactivate

git clone https://github.com/opencv/opencv.git
cd opencv
git checkout $cvVersion
cd ..

git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout $cvVersion
cd ..

cd opencv
mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE \
            -D CMAKE_INSTALL_PREFIX=$cwd/installation/OpenCV-"$cvVersion" \
            -D INSTALL_C_EXAMPLES=ON \
            -D INSTALL_PYTHON_EXAMPLES=ON \
            -D WITH_TBB=ON \
            -D WITH_V4L=ON \
            -D OPENCV_PYTHON3_INSTALL_PATH=$cwd/OpenCV-$cvVersion-py3/lib/python3.5/site-packages \
            -D WITH_QT=ON \
            -D WITH_OPENGL=ON \
            -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
            -D BUILD_EXAMPLES=ON ..
make -j$(nproc)
make install
```
2.install tensorflow(1.14.0)
```
install tensorflow from https://www.tensorflow.org/install/source
install tensorflow lite from https://www.tensorflow.org/lite/guide/build_rpi
```

## Test

### Unit test

### Identification and weighing

![image](https://github.com/Shuanggao58/RefrigeratorManager/blob/main/gif/Orange.gif)

## Improvement

The edge recognition is obviously optimized, as you can see in the figure below.
![image](https://github.com/Shuanggao58/RefrigeratorManager/blob/main/gif/Onion.gif)

## License  
Project is distributed under [GNU General Public License v3.0](https://github.com/Shuanggao58/RefrigeratorManager/blob/main/LICENSE)

## Social media
 Follow our social channels to keep up to date with our branding.
 - [Youtube](https://youtu.be/306hyfkdimc) Initial version
 - [Youtube](https://youtu.be/rlTY5PDiC7U) Final version
