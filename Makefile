# compiler
CC=g++

# compiler flags
CFLAGS=-g -Wall -fPIC

# OpenCV Related
PREFIX=/home/OpenCV-2.4.4a
JDKPREFIX=/usr/lib/jvm/java-1.7.0-openjdk-amd64
OCVFLAGS=-I${PREFIX}/include/opencv -I${PREFIX}/include -I${JDKPREFIX}/include -I${JDKPREFIX}/include/linux
OCVLIBS=-L${PREFIX}/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_flann -lopencv_objdetect -lopencv_calib3d -lopencv_ts -lopencv_contrib -lopencv_gpu -lopencv_legacy -lopencv_photo

PROGRAM=libBGInpaint.so.1.0
SOURCES=com_baguo_inpaint_BGInpaintEngine.cpp utils.cpp src/ClsApp.cpp src/ClsProc.cpp src/ClsPicture.cpp src/ClsObject.cpp
OBJECTS=*.o

program: $(OBJECTS)
	$(CC) -shared -Wl,-soname,libBGInpaint.so.1 -o $(PROGRAM) $(OBJECTS) $(OCVLIBS)

$(OBJECTS): $(SOURCES)
	$(CC) -c $(CFLAGS) $(OCVFLAGS) $(SOURCES)

clean:
	rm -f *.o
	rm -f $(PROGRAM)
	rm -f *~
