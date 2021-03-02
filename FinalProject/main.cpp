#include "Combinations.h"
#include "functions.h"
#include "DataSet.h"
#include "Lsh.h"
#include "rec.h"

using namespace std;

int main(int argc, char **argv)
{
    	
	int metric=2;
    srand(time(NULL));
	int k=10;
    int L=3;
    int P=20;
	string input_file = "tweets_dataset_small.csv"; 
    string output_file = "theodora"; 
    string input_file2 = "vader_lexicon.csv";  
    string input_file3 = "twitter_dataset_small.csv";
    string coin_file = "coins_queries.csv"; 
    //cout << " INPUT FILE : " << input_file << endl;  
    unordered_map<string,double> mylexicon =lexicon_dataset(input_file2); //lexico me lekseis k score
    unordered_map<std::string,int> coins_lexicon; // lekseis p antistixoun sta coins
    unordered_map<int,string> coinlexicon = bitcoin_dataset(coin_file, coins_lexicon); // onoma coin kai id coin
    vector<User*> Users; // users pou exun tweets // pou ta tweets exun coins_contained
    tweets_dataset(Users,input_file,mylexicon,coins_lexicon);   // diavasma input.dat k dimiourgia users me tweets 
    int coinssize = coinlexicon.size();
    ofstream ofile(output_file, ios_base::trunc); //adiasma proigumenou output arxeiou
    /*-------------------------------A--------------------- */
    vector<Feelings*> feelings; // me mesous orous 
    vector<Feelings*> feelings_withInf; // me inf sta kena ratings
    
    beforemagicArray(Users,coinssize,feelings,feelings_withInf); //kataskeui pinaka useri[s1,s2,...,s100]..
    DataSet* setOfFeelings = new DataSet();
    feelings_to_dataset(feelings,*setOfFeelings); //metatropi pinaka useri[s1,s2,...,s100]. se Dataset me items 
    //k=feelings.size()/(P);
    A1(feelings_withInf,1,k,L,feelings,*setOfFeelings,P,output_file,Users,coinlexicon);

    vector<double> feeli = feelings[1]->return_coins_F();
    int d=feeli.size();
    vector<Cluster*> Clusters;
    A2(feelings_withInf,d,2,k ,L, feelings,*setOfFeelings,P,output_file,Users,coinlexicon,Clusters);

    DataSet* set_project2= new DataSet();
    vector<Cluster*> Clusters_project2;
    Dataset_Project2(metric,k,input_file3,*set_project2,Clusters_project2);
  
    vector<Feelings*> feelings_virtualusers; // me mesous orous 
    vector<Feelings*> feelings_withInf_virtualusers; // me inf sta kena ratings

    magicArrayVirtualUsers(Clusters_project2,Users,coinssize,feelings_virtualusers,feelings_withInf_virtualusers); //kataskeui pinaka virtual useri[s1,s2,...,s100]..

    DataSet* setOfFeelings_virtual = new DataSet();
    feelings_to_dataset(feelings_virtualusers,*setOfFeelings_virtual);
    
    B1(feelings_virtualusers,feelings_withInf,metric,k,L,feelings,*setOfFeelings_virtual,P,output_file,Users,coinlexicon);
    vector<double> feelii = feelings_virtualusers[1]->return_coins_F();
    int di=feelii.size();
    vector<Cluster*> Clusters_virtual; 
    //cout <<"di " << di << endl;
    B2(feelings_virtualusers,feelings_withInf,di,metric,k,L,feelings,*setOfFeelings_virtual,P,output_file,Users,coinlexicon,Clusters_virtual);

    /*-----------------------B1-------------------------*/
    /*clock_t start2 = clock(); //clock start
    vector<vector<int>> Top_5 = findPnearestLSH_2(feelings,feelings_withInf,metric,k,L,feelings_virtualusers,*setOfFeelings_virtual,10); //vriskei ta top 5 gia kathe user
    double duration_sec2 = (double)(clock() - start2)/CLOCKS_PER_SEC ;
    OutPut(1,duration_sec2,output_file,Top_5,Users,coinlexicon); //ftiaxnei to output file gia B1
    */
    /*------------------- B2----------------------*/

   /* clock_t start3 = clock(); //clock start
    
    Combination_1_1_1(k,setOfFeelings,Clusters_virtual,di,1); //ergasia 2 clustering me sindiasmo 1_1_1
    cout << Clusters_virtual.size() <<endl;
    vector<vector<int>> Top_2 = findPnearestClustering_B2(feelings_withInf,1,k,feelings,*setOfFeelings_virtual,10,Clusters_virtual,Users); //vriskei ta top 5 gia kathe user
    double duration_sec3 = (double)(clock() - start3)/CLOCKS_PER_SEC;
    OutPut(2,duration_sec3,output_file,Top_2,Users,coinlexicon); //ftiaxnei to output file gia A2
    
    */

    for(int a=0;a<feelings.size();a++){
        delete feelings[a];   
    }
    for(int a=0;a<feelings.size();a++){
        delete feelings_withInf[a];  
    }
    for(int a=0;a<Clusters_virtual.size();a++){
        delete Clusters_virtual[a];
    }
    for(int a=0;a<Clusters_project2.size();a++){
        delete Clusters_project2[a];
    }
    for(int a=0;a<Clusters.size();a++){
        delete Clusters[a];
    }
    for(int a=0;a<feelings_virtualusers.size();a++){
        delete feelings_withInf_virtualusers[a];
    }
    for(int a=0;a<feelings_virtualusers.size();a++){
        delete feelings_virtualusers[a];
    }
    for(int a=0;a<feelings_virtualusers.size();a++){
        delete feelings_virtualusers[a];
    }
    for(int a=0;a<Users.size();a++){
        vector<Tweet*> tweets = Users[a]->return_tweets();
        for(int b=0;b<tweets.size();b++){
            delete tweets[b];
        }
        delete Users[a];
    }
    
}
