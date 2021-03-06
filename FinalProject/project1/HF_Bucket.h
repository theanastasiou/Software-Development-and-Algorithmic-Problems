#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <stdlib.h>   
#include <sstream>      // std::stringstream
#include <list>
#include <math.h>
#include <time.h> 
#include <map>
#include <random>
#include <cmath>
#include <random>
#include <unordered_map>
#include "DataSet.h"
#include "knn_fun.h"

class h{
	private:
		std::vector<float> hv;
		float ht;
	
	public:
		h(std::vector<float>,float);
		float get_ht();	
		std::vector<float>& get_hv();
		void Addtohv(float);
		~h();
};

class h_Cosine{
	private:
		std::vector<float> hv;
		float ht;
	
	public:
		h_Cosine(std::vector<float>);
		std::vector<float>& get_hv();
		void Addtohv(float);
		~h_Cosine();
};

class Bucket {
	private:
		int num;
		std::list<Item*> ItemsInBucket;
	public:
		void AddtoBucket(Item* item);
		int get_num();
		std::list < Item* > return_Items();
		void ShowBucketItems();
		Bucket(int n);
		~Bucket();
};

