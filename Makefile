TARGET=tree
CXXFLAGS=-v -std=c++11 -stdlib=libc++

$(TARGET): TreeStruct.o
	clang++ $(CXXFLAGS) $(TARGET).cpp TreeStruct.o  -o $(TARGET) 

List.o: TreeStruct.cpp
	clang++ $(CXXFLAGS) -c TreeStruct.cpp -o TreeStruct.o

clean:
	rm *.o