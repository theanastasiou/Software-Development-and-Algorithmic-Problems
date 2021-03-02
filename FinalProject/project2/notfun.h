#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Cluster.h"

void Configuration_file(std::string file_name,int &k,int &h,int &L,int &Comb,int &M,int &probes);
void Random_Selection(int k,DataSet *set,std::vector<Cluster*>& Clusters);
void Lloyds_Assignment_2(DataSet* set,std::vector<Cluster*>& Clusters,int metric);
void Lloyds_Assignment(DataSet* set,std::vector<Cluster*>& Clusters,int metric);
double C_distance(std::vector<double> y,std::vector<double> x,int d);
double E_distance(std::vector<double> y,std::vector<double> x,int d);
void KmeansPlusPlus(int k,DataSet *set,std::vector<Cluster*>& Clusters,int Method);
double Return_rD(double max_dist);
bool is_number(const std::string& s);
int Bs(std::vector<int> ClustersA,int closest,int n);
double getClosest(double val1, double val2,double target);
double findClosest(std::vector<double> dist, int n, double target); 
int Kmeans_Update(DataSet* set,std::vector<Cluster*>& Clusters,int d,int metric);
void Silhouette(std::vector<Cluster*> Clusters,int k,std::string output_file,int metric);
int print2Smallest(std::vector<double> arr, int arr_size);
int PAM_Update_Lloyds(DataSet* set ,std::vector<Cluster*>& Clusters,int d,int metric);
void OutPuts_K(std::vector<Cluster*> Clusters,double t,std::string output_file,int metric, int a,int b,int c,int wtd);
void OutPuts_KC(std::vector<Cluster*> Clusters,double t,std::string output_file,int metric,int a,int b,int c);
void OutPuts_P(std::vector<Cluster*> Clusters,double t,std::string output_file,int  metric,int a,int b,int c,int wtd);
void OutPuts_PC(std::vector<Cluster*> Clusters,double t,std::string output_file,int metric,int a,int b,int c);