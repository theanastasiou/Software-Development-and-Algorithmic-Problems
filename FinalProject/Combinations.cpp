#include "Combinations.h"
using namespace std;
#include <algorithm>

void Combination_1_1_1(int k,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric){
    clock_t start = clock(); //clock start
	//cout<< "comb " << endl;	
    Random_Selection(k,set,Clusters); //random selection (A1) 
	//cout <<"random" << endl;
	Lloyds_Assignment(set,Clusters,metric);
	//cout << "-------------------------" <<endl;
	int cc=0;
	while(Kmeans_Update(set,Clusters,d,metric)!=0){
		cc++;
	//	cout << "cc" <<endl;
		if(cc>20)
			break;
	}
   // cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	//OutPuts_K(Clusters,duration_sec, output_file,metric,1,1,1,wtd);
    //Silhouette(Clusters,k,output_file,metric);
}