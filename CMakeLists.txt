CMAKE_MINIMUM_REQUIRED (VERSION 3.0)

PROJECT (Tesseract_and_YOLO C CXX)

FIND_PACKAGE (Threads	REQUIRED)
FIND_PACKAGE (OpenCV	REQUIRED)	# sudo apt-get install libopencv-dev
FIND_LIBRARY (Tesseract tesseract)	# sudo apt-get install libtesseract-dev tesseract-ocr-eng
FIND_LIBRARY (DarkHelp	darkhelp)	# https://github.com/stephanecharette/DarkHelp
FIND_LIBRARY (Darknet	darknet)	# https://github.com/AlexeyAB/darknet

INCLUDE_DIRECTORIES (${OpenCV_INCLUDE_DIRS})

ADD_EXECUTABLE (tesseract_and_yolo_1 tesseract_and_yolo_1.cpp)
TARGET_LINK_LIBRARIES (tesseract_and_yolo_1 Threads::Threads ${Tesseract} ${OpenCV_LIBS})

ADD_EXECUTABLE (tesseract_and_yolo_2 tesseract_and_yolo_2.cpp)
TARGET_LINK_LIBRARIES (tesseract_and_yolo_2 Threads::Threads ${DarkHelp} ${Darknet} ${OpenCV_LIBS})

ADD_EXECUTABLE (tesseract_and_yolo_3 tesseract_and_yolo_3.cpp)
TARGET_LINK_LIBRARIES (tesseract_and_yolo_3 Threads::Threads ${DarkHelp} ${Darknet} ${OpenCV_LIBS})
