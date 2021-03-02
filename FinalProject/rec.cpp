#include "rec.h"

using namespace std;

void A1(std::vector<Feelings*>& feelings_withInf,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon){
    clock_t start = clock(); //clock start
    vector<vector<int>> Top5 = findPnearestLSH(feelings_withInf,metric,k,L,feelings,setOfFeelings,P); //vriskei ta top 5 gia kathe user
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;
    OutPut(1,duration_sec,output_file,Top5,Users,coinlexicon); 
    //ftiaxnei to output file gia A1
}

void A2(std::vector<Feelings*>& feelings_withInf,int d,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon,std::vector<Cluster*>& Clusters){
    clock_t start1 = clock(); //clock start
    Combination_1_1_1(k,&setOfFeelings,Clusters,d,metric); //ergasia 2 clustering me sindiasmo 1_1_1
    vector<vector<int>> Top2 = findPnearestClustering(feelings_withInf,1,k,feelings,setOfFeelings,P,Clusters,Users); //vriskei ta top 5 gia kathe user
    double duration_sec1 = (double)(clock() - start1)/CLOCKS_PER_SEC ;
    OutPut(2,duration_sec1,output_file,Top2,Users,coinlexicon); //ftiaxnei to output file gia A2*/
}

void B1(std::vector<Feelings*>& feelings_virtualusers,std::vector<Feelings*>& feelings_withInf,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings_virtual,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon){
    clock_t start2 = clock(); //clock start
    vector<vector<int>> Top_5 = findPnearestLSH_2(feelings,feelings_withInf,metric,k,L,feelings_virtualusers,setOfFeelings_virtual,P); //vriskei ta top 5 gia kathe user
    double duration_sec2 = (double)(clock() - start2)/CLOCKS_PER_SEC ;
    OutPut(1,duration_sec2,output_file,Top_5,Users,coinlexicon); //ftiaxnei to output file gia B1
}

void B2(std::vector<Feelings*>& feelings_virtualusers,std::vector<Feelings*>& feelings_withInf,int di,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings_virtual,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon,std::vector<Cluster*>& Clusters_virtual){
    clock_t start3 = clock(); //clock start
    Combination_1_1_1(k,&setOfFeelings_virtual,Clusters_virtual,di,1); //ergasia 2 clustering me sindiasmo 1_1_1
    vector<vector<int>> Top_2 = findPnearestClustering_B2(feelings_withInf,1,k,feelings,setOfFeelings_virtual,P,Clusters_virtual,Users); //vriskei ta top 5 gia kathe user
    double duration_sec3 = (double)(clock() - start3)/CLOCKS_PER_SEC;
    OutPut(2,duration_sec3,output_file,Top_2,Users,coinlexicon); //ftiaxnei to output file gia A2
}