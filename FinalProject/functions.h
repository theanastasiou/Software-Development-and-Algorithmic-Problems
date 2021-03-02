#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>  
#include <cfloat>
#include <limits>
#include "DataSet.h"
#include "Combinations.h"
#include <list>
#include <unordered_map>

void tweets_dataset(std::vector<User*>& Users,std::string t_d,std::unordered_map<std::string,double> mylexicon,std::unordered_map<std::string,int> coins_lexicon);
std::unordered_map<std::string,double> lexicon_dataset(std::string lexicon);
std::unordered_map<int,std::string> bitcoin_dataset(std::string bitcoin, std::unordered_map<std::string,int>& coins_lexicon);
double calculate_totalscore(std::vector<std::string> tweet,std::unordered_map<std::string,double> mylexicon);
double calculate_sentiment(double totalscore);
std::vector<int> find_coins_contained(std::vector<std::string> tweet_data,std::unordered_map<std::string,int> coins_lexicon);
void beforemagicArray(std::vector<User*> Users,int coinssize,std::vector<Feelings*>& feelings,std::vector<Feelings*>& feelings_withInf);
void avgFeelings(std::vector<Feelings*>& feelings);
double euclidean_similarity(std::vector<double> y,std::vector<double> x,int d);
void feelings_to_dataset(std::vector<Feelings*>& feelings,DataSet& set);
std::vector<std::vector<int>> findPnearestLSH(std::vector<Feelings*>& feelings_withInf,int metric,int k,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P);
std::vector<int> calculateRelateCoins(std::vector<Feelings*> feelings_withInf,Feelings& target,std::list<Item*>& P_nearest,std::vector<Feelings*> feelings);
double avgFeelings_V(std::vector<double>& feel);
double cosine_similarity(std::vector<double> y,std::vector<double> x);
void OutPut(int s,double duration,std::string output_file,std::vector<std::vector<int>> Top5,std::vector<User*> Users,std::unordered_map<int,std::string> coinlexicon);
std::vector<std::vector<int>> findPnearestClustering(std::vector<Feelings*>& feelings_withInf,int metric,int k,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P_nearest,std::vector<Cluster*> Clusters,std::vector<User*> Users); //vriskei ta top 5 gia kathe user
std::vector<int> calculateRelateCoins_2(std::vector<Feelings*> feelings_withInf,Feelings& target,std::vector<Item*>& P_nearest,std::vector<Feelings*> feelings);
void Dataset_Project2(int metric,int k,std::string input_file_3,DataSet& set,std::vector<Cluster*>& Clusters);
void magicArrayVirtualUsers(std::vector<Cluster*> Clusters_project2,std::vector<User*> Users,int coinssize,std::vector<Feelings*>& feelings,std::vector<Feelings*>& feelings_withInf);
std::vector<std::vector<int>> findPnearestLSH_2(std::vector<Feelings*>& feelings_Or,std::vector<Feelings*>& feelings_withInf,int metric,int k,int L,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P);
std::vector<int> calculateRelateCoins_B1(std::vector<Feelings*> feelings_withInf,Feelings& target,std::list<Item*>& P_nearest,std::vector<Feelings*> feelings);
std::vector<std::vector<int>> findPnearestClustering_B2(std::vector<Feelings*>& feelings_withInf,int metric,int k,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P_nearest,std::vector<Cluster*> Clusters,std::vector<User*> Users); //vriskei ta top 5 gia kathe user
std::vector<int> calculateRelateCoins_B2(std::vector<Feelings*> feelings_withInf,Feelings& target,std::vector<Item*>& P_nearest,std::vector<Feelings*> feelings);
