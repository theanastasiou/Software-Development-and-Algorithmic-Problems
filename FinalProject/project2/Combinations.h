#include "Lsh.h"
#include "notfun.h"
#include "HyperCube.h"

void Combination_1_1_1(int k,DataSet *set,std::vector<Cluster*>z Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_1_1_2(int k,DataSet *set,std::vector<Cluster*> Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_2_1_2(int k,DataSet *set,std::vector<Cluster*> Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_2_1_1(int k,DataSet *set,std::vector<Cluster*> Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_1_2_1(int h,int L,int n,int k,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_1_2_2(int h,int L,int n,int k,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_2_2_2(int h,int L,int n,int k,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_2_2_1(int h,int L,int n,int k,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_1_3_1(int h,int L,int n,int k,int M,int probes,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_2_3_1(int h,int L,int n,int k,int M,int probes,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_2_3_2(int h,int L,int n,int k,int M,int probes,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
void Combination_1_3_2(int h,int L,int n,int k,int M,int probes,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd);
