#pragma once
#include <sstream>
#include <iterator>
#include "Hash_Euclidean.h"
#include "Hash_Cosine.h"

class LSH{
	private:
		int d; //arithmos diastasewn item
		int k; //arithmos h function ana methodo
		int L; //arithmos hashtable ana methodo
		int n; //arithmos twn items
		int method;
		std::vector < Hash_Euclidean* > E;
		std::vector < Hash_Cosine* > C ;

	public:
		LSH(int,int,int,int,int);
		int return_d();
		void Calc_Euclidean(DataSet *set);
		void Calc_Cosine(DataSet *set);
		std::vector<Hash_Euclidean*>& return_E();
		std::vector<Hash_Cosine*>& return_C();
		void AddtoE(Hash_Euclidean *He);
		void AddtoC(Hash_Cosine *Co);
		std::list<Item*>&  Q_Calc_Euclidean(DataSet *set,std::vector<double> myCl);
		std::list<Item*>& Q_Calc_Cosine(DataSet *set,std::vector<double> myCl);
		
		~LSH();
};




