#$CC -fPIE -pie hello.c -o hello -landroid

CC = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-gcc 
#CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-g++
CXX = /home/hyeongjun/mytooldir/my-android-ndk-24/bin/aarch64-linux-android-clang++
CFLAGS = 
#CXXFLAGS = -static -std=c++11 -v 
CXXFLAGS = -fPIE -pie 
TARGET = mybinary
OBJECTS = mybinary.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
clean :
	rm *.o mybinary

