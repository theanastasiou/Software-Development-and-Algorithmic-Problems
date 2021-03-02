#pragma once
#include "HF_Bucket.h"

class Hash_Euclidean{
	private:
		int M;
		int T;
		int k;
		int d;
		std::vector <h*> h_fun;
		std::vector <float> Ri;
		std::vector < Bucket* > Buckets;
		std::vector <double> g;
		std::vector <Item*> Checked;

	public:
		Hash_Euclidean(int,int,int);
		~Hash_Euclidean();
		void AddChecked(Item* item);
		void AddtoRi(float r);
		std::vector<Item*> return_Checked() ;
		void Calc_Euclidean_distance(int buck,std::vector<int> x,std::string &min_item,double &min_distance); // opou x to item_data k opou y ta simeia tu item tu query
		//dimiourgw to bucket
		//meta gia na vazw items sto bucket tha prepei na vriskw ston vector to bucket me num== tade
		//kai meta na kanw insert stin lista tou sigkekrimenu bucket
		void AddBucket(Bucket* bucket);
		void Addgi(double gi);
		void AddFun(h* fun);
		std::vector<h*> return_h() ;
		//omoiomorfi katanomi apo 0-w (t)
		float Return_t();
		std::vector < Bucket* >& return_Buckets();
		int Return_Ri();
		void Search_Euclidean(std::string line,std::string &min_item,double &min_distance);
		//kanoniki katanomi gia v
		float Return_v();
		int Euclidean_distance(std::vector<int> y,std::vector<int> x,std::string &min_item,double &min_distance);
		long long int modulus(long long int pre);
		void Euclidean_HF(Item* item);
};
