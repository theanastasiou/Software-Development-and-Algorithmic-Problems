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
#include <math.h>
#include <time.h>
#define ALPHA 15

class Feelings{
	private:
	int User_id;
	std::vector<double> coins_F;
	
	public: 
	Feelings();	
	~Feelings();
	int return_Userid();
	std::vector<double> return_coins_F();
	void setUserid(int User_id);
	void setCoinsF(std::vector<double> coins_F);
};

class Tweet{
	private:
	int tweet_id;  //id tou tweet
	std::vector<std::string> tweet_data; // ta tweets tou kathe use
	double totalscore;	//scores twn tweets,score kathe tweet se antistoixia
	double senti; //ta sentimiters tou kathe tweet ana totalscore
	std::vector<int> coins_contained;

	public: 
	Tweet(int tweet_id);	
	~Tweet();
	int return_tweetid();
	void AddTweetData(std::string data);
	std::vector<std::string> return_tweet_data();
	void  DisplayVectorContents_Tweet();
	void setTotalscore(double totalscore);
	void setSentiment(double sentiment);
	void setCoinsContained(std::vector<int> coins_contained);
	std::vector<int> return_coins_contained();
	double return_totalscore();
	double return_senti();
};

class User{
	private:
	int user_id; 
	int cluster_id; // se poio cluster anoikei o user_id
	std::vector<Tweet*> tweets; //vector me ta tweets tou user
	
	
	public:
	User(int user_id);	
	~User();
	int return_user_id();
	int return_cluster_id();
	std::vector<Tweet*>& return_tweets();
	void AddTweet_toUser(Tweet *tweet); 
	void DisplayUser_Tweets();

};


class Item{
	private:
	std::string item_id;
	std::vector<double> item_data;
	int assigned;
	int rev;
	int cluster_id;
	std::vector<double> cluster_vector;
	double distance;
	int User_id;
	int id;

	
	public:
	Item(std::string name);
		
	~Item();

	void set_id(int id);
	int returnid();
	int return_rev();
	int return_cluster_id();
	int return_User_id();
	void set_assigned(int assigned);
	void set_Userid(int User_id);
	void set_rev(int rev);
	void set_distance(double distance);
	double return_distance();
	void set_cluster_id(int id);
	void set_cluster_vector(std::vector<double> cv);
	std::vector<double> return_cluster_vector();
	int return_assigned();
	void AddData(double num);
	void DisplayVectorContents();
	std::string return_item_id();
	std::vector<double>& return_item_data();
};



class DataSet{
	private:
	std::vector<Item*> Items;
	
	public:		
	DataSet();
	
	void AddData_toDataSet(Item *item);
	int Return_size();
	std::vector<Item*>&  return_items();
	
	void DisplayVectorContents_DataSet();
	~DataSet();
	
};


