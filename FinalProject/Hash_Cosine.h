#pragma once
#include "HF_Bucket.h"

class Hash_Cosine{
	private:
		int T;
		int k;
		int d; 
		std::vector <h_Cosine*> h_fun;
		std::vector <double> Ri;
		std::vector < Bucket* > Buckets;
		std::vector <Item*> Checked;
		
	public:
		Hash_Cosine(int t,int k,int d);
		~Hash_Cosine();	
		std::vector<Item*> return_Checked() ;
		void AddChecked(Item* item);
		//dimiourgw to bucket 
		//meta gia na vazw items sto bucket tha prepei na vriskw ston vector to bucket me num== tade
		//kai meta na kanw insert stin lista tou sigkekrimenu bucket	
		void AddBucket(Bucket* bucket);
		std::vector < Bucket* > return_Buckets();
		void AddFun(h_Cosine* fun);
		std::vector<h_Cosine*> return_h() ;
		std::list<Item*>& Search_Cosine(std::vector<double> myCl);
		double Cosine_distance(std::vector<double> y, std::vector<double> x);
		void Calc_Cosine_distance(int buck,std::vector<double> x,std::string &min_item,double &min_distance);
		//kanoniki katanomi gia v 
		double Return_Ri();
		void Cosine_HF(Item* item);
	
};
