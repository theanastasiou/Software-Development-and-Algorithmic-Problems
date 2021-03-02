all: lsh cube
CC = g++
CFLAGS = -g -Wall -std=c++0x
OBJECTS = Project.o DataSet.o Lsh.o Hash_Euclidean.o HF_Bucket.o Hash_Cosine.o knn_fun.o
OBJECTS1 = hypercube.o HyperCube.o DataSet.o HF_Bucket.o knn_fun.o
MATH = -lm

cube: $(OBJECTS1)
	$(CC) $(CFLAGS) $(OBJECTS1) -o cube $(MATH)

lsh: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o lsh $(MATH)

Project.o: Project.cpp 
	$(CC) $(CFLAGS) -c Project.cpp

DataSet.o: DataSet.cpp
	$(CC) $(CFLAGS) -c DataSet.cpp

Lsh.o: Lsh.cpp 
	$(CC) $(CFLAGS) -c Lsh.cpp

Hash_Euclidean.o: Hash_Euclidean.cpp
	$(CC) $(CFLAGS) -c Hash_Euclidean.cpp

HF_Bucket.o: HF_Bucket.cpp 
	$(CC) $(CFLAGS) -c HF_Bucket.cpp

Hash_Cosine.o: Hash_Cosine.cpp
	$(CC) $(CFLAGS) -c Hash_Cosine.cpp

knn_fun.o: knn_fun.cpp
	$(CC) $(CFLAGS) -c knn_fun.cpp

hypercube.o: hypercube.cpp
	$(CC) $(CFLAGS) -c hypercube.cpp

HyperCube.o: HyperCube.cpp
	$(CC) $(CFLAGS) -c HyperCube.cpp

C_T.o: C_T.cpp
	$(CC) $(CFLAGS) -c C_T.cpp


.PHONY: clean

clean:
	rm -f lsh $(OBJECTS) 

