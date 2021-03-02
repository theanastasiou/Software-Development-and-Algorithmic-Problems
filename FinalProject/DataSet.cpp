#include "DataSet.h"
using namespace std;

Feelings:: Feelings(){};
Feelings::~Feelings(){};

int Feelings::return_Userid(){
	return User_id;
}
vector<double> Feelings::return_coins_F(){
	return coins_F;
}

void Feelings::setUserid(int User_id){
	this->User_id = User_id;
}

void Feelings::setCoinsF(vector<double> coins_F){
	this->coins_F = coins_F;
}

User::User(int user_id){
		this->user_id=user_id;
		this->cluster_id=-1;
}

User::~User(){
		//cout<<"A User just Deleted"<< endl;
	}

int User::return_user_id(){
	return user_id;
}
int User::return_cluster_id(){
	return cluster_id;
}

void User::AddTweet_toUser(Tweet *tweet){
	tweets.push_back(tweet);
	}

std::vector<Tweet*>&  User::return_tweets(){
	return tweets;
}

void  User::DisplayUser_Tweets(){
	cout << "------------- USER :"<< user_id << " ---------- " << endl;
	cout << " TWEETS COUNTER : " << tweets.size() << endl;
	for( unsigned int i = 0; i < tweets.size(); i++)
		tweets[i]->DisplayVectorContents_Tweet();
	
	}

void Tweet::setCoinsContained(std::vector<int> coins_contained){
	this->coins_contained = coins_contained; 
}

Tweet::Tweet(int tweet_id){
		this->tweet_id=tweet_id;
}

Tweet::~Tweet(){
		//cout<<"A Tweet just Deleted"<< endl;
	}

std::vector<std::string> Tweet::return_tweet_data(){
	return tweet_data;
};

void Tweet::AddTweetData(std::string data){
	tweet_data.push_back(data);
	}
double Tweet::return_totalscore(){
	return totalscore;
}

int Tweet::return_tweetid(){
	return this->tweet_id;
}

void  Tweet::DisplayVectorContents_Tweet(){
	cout << "-------------------" << endl;
	cout << "Tweet ID: " << tweet_id  << endl;
	
	for( unsigned int i = 0; i < tweet_data.size(); i++ )
	{
		cout << "Element[" << i << "] = " << tweet_data[i] << endl;
	}
	cout << "Coins[" ;
	for( unsigned int i = 0; i < coins_contained.size(); i++ )
	{
		
		cout << coins_contained[i] << " ";
	}
	cout << "]" << endl;
	cout << "Sentiment of Tweet: " << senti << endl;
}

vector<int> Tweet::return_coins_contained(){
	return coins_contained;
}

double Tweet::return_senti(){
	return senti;
}

void Tweet::setTotalscore(double totalscore){
	this->totalscore=totalscore;
}

void Tweet::setSentiment(double sentiment){
	this->senti=sentiment;
}

Item::Item(string name){
		item_id=name;
		//cout<<"An item Created! "<< endl;
		this->assigned=0;
		this->rev=-1;
		this->cluster_id=0;
		this->distance=0.0;
}
		
Item::~Item(){
		item_data.erase(item_data.begin(),item_data.end());
		//cout<<"An Item just Deleted"<< endl;
	}
	
void Item::AddData(double num){
	   // cout << "......." << endl;
		item_data.push_back(num);
}

vector<double>& Item::return_item_data(){
	return item_data;
	}
	

string Item::return_item_id(){
	return item_id;
	}

int Item::return_assigned(){
	return assigned;
	}

double Item::return_distance(){
	return distance;
	}
	
int Item::return_rev(){
	return rev;
	}
int Item::return_cluster_id(){
	return cluster_id;
	}
void Item::set_assigned(int assigned){
	this->assigned=assigned;
}
void Item::set_rev(int rev){
	this->rev=rev;
}
void Item::set_cluster_id(int id){
	this->cluster_id=id;
}

void Item::set_Userid(int User_id){
	this->User_id=User_id;
}

void Item::set_id(int id){
	this->id=id;
}

int Item::returnid(){
	return this->id;
}

int Item::return_User_id(){
	return this->User_id;
}

void Item::set_distance(double distance){
	this->distance=distance;
}
void Item::set_cluster_vector(vector<double> cv){
	this->cluster_vector=cv;
}
vector<double> Item::return_cluster_vector(){
	return cluster_vector;
	}
		
void Item::DisplayVectorContents(){
	cout << "Item_data size: " << item_data.size() << endl;
	cout << "Name" << item_id  << endl;
	
	for( unsigned int i = 0; i < item_data.size(); i++ )
	{
		
		cout << "Element[" << i << "] = " << item_data[i] << endl;
	}
	cout << endl;
}




DataSet::DataSet(){
	//cout<<"A DataSet Created! "<< endl;	
	}
	
void DataSet::AddData_toDataSet(Item *item){
	Items.push_back(item);
	}

int DataSet::Return_size(){
	return Items.size();
	}
	
vector<Item*>& DataSet::return_items(){
	return Items;
	}
		
void  DataSet::DisplayVectorContents_DataSet(){
	for( unsigned int i = 0; i < Items.size(); i++)
		Items[i]->DisplayVectorContents();
	}
	


DataSet::~DataSet(){
	//Memory+=sizeof(Items);
	for( unsigned int i = 0; i < Items.size(); i++ )
		{
			//Memory+=sizeof(Items[i]);
			delete Items[i];
		}
	Items.erase (Items.begin(),Items.end());	
	
	//cout<<"A DataSet just Deleted"<< endl;
	}
	

