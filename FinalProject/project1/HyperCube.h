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
#include "HF_Bucket.h"
#include "knn_fun.h"



class HyperCube{
	private:
		int k; 
		int M; //arithmos h function ana methodo
		int probes; //arithmos hashtable ana methodo
		int n; //arithmos twn items
		int d; //arithmos diastasewn twn simeiwn
		int T;
		std::vector <h*> h_fun;
		std::vector < Bucket* > Buckets;
		std::vector <std::unordered_map<int,int>> bitmap;
		std::vector <Item*> Checked;
		std::vector <char*> MyNeighbors_char;
		std::vector <float> hhv;
		
	public:
	
		HyperCube(int,int,int,int,int);
		void Calc_H(DataSet* set);
		void Hyper_HF(Item* it);
		float Return_v();
		int binaryToDecimal(int n);
		void find_neigh(std::string str, int i, int changesLeft,std::vector<std::string>& MyNeighbors_char);
		char* lltoa(long long int val, int base);
		unsigned long long int gcd(unsigned long long int x, unsigned long long int y);
		long long int convertDecimalToBinary(int n,unsigned long long int &n_bits);
		unsigned long long int Combinations(unsigned long long int n, unsigned long long  int k);
		void  AddChecked(Item* item);	
		std::vector<char*>&  return_MyNeighbors_char();
		void AddNeighbor_char(char* str);
		std::vector<Item*> return_Checked();
		int Euclidean_distance(std::vector<int> y,std::vector<int> x,std::string &min_item,double &min_distance);
		long long int modulus(long long int pre);
		std::vector<std::unordered_map<int,int>>& get_bitmap();
		std::vector<h*> return_h(); 
		void Q_Calc_Euclidean(DataSet *set,std::string Q_file);
		void Cube_Search_Euclidean(std::string line,std::string &min_item,double &min_distance);
		void Cube_Calc_Euclidean_distance(int buck ,std::vector<int> x,std::string &min_item,double &min_distance,int &Max);
		std::vector<Bucket*>&  return_Buckets();
		void AddBucket(Bucket* bucket);
		void AddFun(h* fun);
		float Return_t();
		~HyperCube();
};

