#pragma once
#include "functions.h"
#include "DataSet.h"
#include "Lsh.h"
#include "Combinations.h"
#include "functions.h"

void A1(std::vector<Feelings*>& feelings__withInf,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon);
void A2(std::vector<Feelings*>& feelings__withInf,int d,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon,std::vector<Cluster*>& Clusters);
void B1(std::vector<Feelings*>& feelings_virtualusers,std::vector<Feelings*>& feelings_withInf,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings_virtual,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon);
void B2(std::vector<Feelings*>& feelings_virtualusers,std::vector<Feelings*>& feelings_withInf,int di,int metric,int k ,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings_virtual,int P,std::string output_file,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon,std::vector<Cluster*>& Clusters_virtual);
