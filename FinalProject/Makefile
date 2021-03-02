CC = g++
CFLAGS = -g -Wall -std=c++0x
OBJECTS = main.o functions.o DataSet.o notfun.o Cluster.o Combinations.o Lsh.o Hash_Cosine.o Hash_Euclidean.o HF_Bucket.o HyperCube.o rec.o
MATH = -lm

cluster: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o pro3 $(MATH)

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

functions.o: functions.cpp
	$(CC) $(CFLAGS) -c functions.cpp

DataSet.o: DataSet.cpp
	$(CC) $(CFLAGS) -c DataSet.cpp

notfun.o: notfun.cpp
	$(CC) $(CFLAGS) -c notfun.cpp

Cluster.o: Cluster.cpp
	$(CC) $(CFLAGS) -c Cluster.cpp
	
Combinations.o: Combinations.cpp
	$(CC) $(CFLAGS) -c Combinations.cpp

rec.o: rec.cpp
	$(CC) $(CFLAGS) -c rec.cpp

Lsh.o: Lsh.cpp 
	$(CC) $(CFLAGS) -c Lsh.cpp

Hash_Euclidean.o: Hash_Euclidean.cpp
	$(CC) $(CFLAGS) -c Hash_Euclidean.cpp

Hash_Cosine.o: Hash_Cosine.cpp
	$(CC) $(CFLAGS) -c Hash_Cosine.cpp

HF_Bucket.o: HF_Bucket.cpp 
	$(CC) $(CFLAGS) -c HF_Bucket.cpp

HyperCube.o: HyperCube.cpp
	$(CC) $(CFLAGS) -c HyperCube.cpp

.PHONY: clean

clean:
	rm -f pro3 $(OBJECTS) 

