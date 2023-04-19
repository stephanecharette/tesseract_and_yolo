# Description

Example C++ code that shows how to use Tesseract or DarkHelp/Darknet/YOLO to read text from images.

The following is a short youtube video showing how this works:

[![Tesseract and Darknet/YOLO video](https://img.youtube.com/vi/_BsLM4e3_oo/0.jpg)](https://www.youtube.com/watch?v=_BsLM4e3_oo)

# Building

First, run this command to install dependencies:

	sudo apt-get install build-essential cmake git libopencv-dev libtesseract-dev tesseract-ocr

Once you [install Darknet and DarkHelp](https://github.com/stephanecharette/DarkHelp#building-darknet-linux), this is how you build the source code in this repo:

	cd
	mkdir src
	cd src
	git clone https://github.com/stephanecharette/tesseract_and_yolo.git
	cd tesseract_and_yolo
	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make -j4
