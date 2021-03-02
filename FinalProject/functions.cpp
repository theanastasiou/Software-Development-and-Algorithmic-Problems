#include "functions.h"
#include "Lsh.h"
#include "notfun.h"

using namespace std;

void tweets_dataset(vector<User*>& Users,string t_d,unordered_map<string,double> mylexicon,unordered_map<std::string,int> coins_lexicon){
    string line;
    ifstream out(t_d);
	vector<int> Users_id;
	while ( getline( out, line )){
		string id;
		istringstream ss( line );
		size_t pos = 0;
		string token;
		string delimiter = "\t";
        int fir=0;
		string::size_type sz;
		
		User *user ;
		Tweet *tweet;
		int userid =-1;
		int whereto = -1; 
		//an exw idi vri tweet me userid tade, an ksanavrw tweet me userid=tade apla to vazw ston pinaka me ta
		//tweets tou sigkekrimenu user kai den ksanaftiaxnw allo user
		int flag=-1; //if user exists 
			if (line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);
		while ((pos = line.find(delimiter))!= string::npos) {
			if(fir==0){ //user id
				token = line.substr(0, pos);
				userid = stoi(token,&sz);
				// std::find function call 
				std::vector<int>::iterator it; 
				it = std::find (Users_id.begin(), Users_id.end(), userid); 
				if (it != Users_id.end()) 
				{ 
					whereto = it - Users_id.begin() + 1 ;
					flag=0; //0 if exists
				} 
				else{
					flag=1; //1 if not exists
				}
				line.erase(0, pos + delimiter.length());
				fir=1;
			}
			//pernw tin 2i stili spazontas sto \t
            if(fir==1){ //tweet id
				token = line.substr(0, pos);
				int tweetid = stoi(token,&sz);
				tweet = new Tweet(tweetid);
			 	//cout << "ROK " <<token << endl;
				line.erase(0, pos + delimiter.length()-1);	
                fir=2;
			}
			int firr = 0;
			//cout << "LINE " << line << endl;
			size_t poS = 0;
			string tokeN;
			while ((poS = line.find(delimiter))!= string::npos) {
				if(fir==2){ //string tou tweet tha pernw mia mia leksi mexri enter
					tokeN = line.substr(0, poS);	
					// cout << "TWEET STRING: " << token << endl;
					tweet->AddTweetData(tokeN);
					line.erase(0, poS + delimiter.length());

				}
			}
			token = line.substr(0, pos);
			tweet->AddTweetData(token);
        }
		//pernw tin teleutaia leksi prin to \n , afou spazei se \t i teleytaia leksi menei ektos kai tin pernw etsi.
        


		//calculate totalscore
		//calculate sentimit
		double totalscore = calculate_totalscore(tweet->return_tweet_data(),mylexicon);

		double sentiment = calculate_sentiment(totalscore);
		vector<int> tweet_bitcoin = find_coins_contained(tweet->return_tweet_data(),coins_lexicon);
		//cout << "Sentiment " << sentiment << endl; 

		//cout<< " AFTER CACLULATE" << endl;
		tweet->setTotalscore(totalscore);
		tweet->setSentiment(sentiment);
		tweet->setCoinsContained(tweet_bitcoin);

		if(flag==0){ //if exists
			//cout << "OK" << endl;
			//cout << whereto << endl;
			Users[whereto-1]->AddTweet_toUser(tweet);
		}
		if(flag==1){ //if not exists
			user=new User(userid);
			Users_id.push_back(userid);
			user->AddTweet_toUser(tweet);
			Users.push_back(user);
		}
		
    }

	/*for(unsigned int i=0;i<Users.size();i++)
		Users[i]->DisplayUser_Tweets();*/
		
}

unordered_map<string,double> lexicon_dataset(string lexicon){
	  unordered_map<string,double> mylexicon;
	  string line;
      ifstream out(lexicon);
	  while ( getline( out, line )){
		istringstream ss( line );
		size_t pos = 0;
		string token;
		string delimiter = "\t";
        int fir=0;
		string::size_type sz;
		//int flag=-1; //if user exists 
		while ((pos = line.find(delimiter))!= string::npos) {
			string myword;
			double wordscore=0;
			if(fir==0){ //user id
				token = line.substr(0, pos);
				//cout << "WORD:" << token;
				myword = token;
				line.erase(0, pos + delimiter.length());
				fir=1;
			}
			if (fir==1){
				token = line.substr(0, pos);
				//cout << " word score :" << token << endl;
				wordscore = stod(token,&sz);
				line.erase(0, pos + delimiter.length());
			}
			//cout << " word___ :" << wordscore;
			//cout << "word" << myword << endl;
			mylexicon.insert(make_pair(myword,wordscore)); // move insertion
			//mylexicon.insert(std::make_pair(myword, wordscore));
		}
	}
	/*int wordcounter=0;
	for(auto& p: mylexicon){
        std::cout << " " << p.first << " => " << p.second << '\n';
		wordcounter++;
	}
	cout << wordcounter << endl;*/
	return mylexicon;
}

unordered_map<int,string> bitcoin_dataset(string bitcoin,unordered_map<std::string,int>& coins_lexicon){
	  unordered_map<int,string> coinlexicon;
	  string line;
      ifstream out(bitcoin);
	  int coincounter=0;
	  while ( getline( out, line )){
		istringstream ss( line );
		size_t pos = 0;
		string token;
		string delimiter = "\t";
        int fir=0;
		//string::size_type sz;
		//cout << "line: " << line << endl;
		pos = line.find(delimiter);
		string myfirstname;
		while (pos!= string::npos) {
			
			string name;
			if(fir==0){ //user id
				token = line.substr(0, pos);
				name = token;
				coins_lexicon.insert(make_pair(token,coincounter));
				line.erase(0, pos + delimiter.length());
				pos = line.find(delimiter);
				fir=1;
			}
			if (fir==1){
				token = line.substr(0, pos);
				coins_lexicon.insert(make_pair(token,coincounter));
				line.erase(0, pos + delimiter.length());
				pos = line.find(delimiter);
				fir=2;
			}
			if (fir==2){
				token = line.substr(0, pos);
				coins_lexicon.insert(make_pair(token,coincounter));
				line.erase(0, pos + delimiter.length());
				pos = line.find(delimiter);
				fir=3;
			}
			if (fir==3){
				token = line.substr(0, pos);
				coins_lexicon.insert(make_pair(token,coincounter));
				line.erase(0, pos + delimiter.length());
				pos = line.find(delimiter);
				fir=4;
			}
			if (fir==4){
				token = line.substr(0, pos);
				//cout <<"TOKENN :" << token[0] << endl;
				
				if(token[0]!='@'){
					myfirstname=token;
					coins_lexicon.insert(make_pair(token,coincounter));
				}
				else{
				 	myfirstname=name;}
				line.erase(0, pos + delimiter.length());
				pos = line.find(delimiter);
				fir=5;
				//cout << "----------- " << endl;
				
			}
			if(fir==5){
				token = line.substr(0, pos);
				coins_lexicon.insert(make_pair(token,coincounter));
				line.erase(0, pos + delimiter.length());
				pos = line.find(delimiter);
			}
			//cout << " coinname :" << myfirstname << endl;
			//cout << "word" << myword << endl;
			//mylexicon.insert(make_pair(myword,wordscore)); // move insertion
			//mylexicon.insert(std::make_pair(myword, wordscore));
			//pos = line.find(delimiter);
		}
	
	coinlexicon.insert(make_pair(coincounter,myfirstname));
	coincounter++;
	}
	/*for(auto& p: coinlexicon){
        std::cout << " " << p.first << " => " << p.second << '\n';
	}*/
	
	return coinlexicon;
}


double calculate_totalscore(vector<string> tweet,unordered_map<string,double> mylexicon){
	double totalscore=0;
	for( unsigned int i = 0; i < tweet.size(); i++ )
	{	
		double ra=0;
		//cout << "Element[" << i << "] =" << tweet[i] << "_" << endl;
		unordered_map<string,double>::iterator it=mylexicon.find(tweet[i]);
		//check an iparxei o arithmos stin domi alliws cointos
		if(it == mylexicon.end()){
			//cout << "not found" <<endl;
		}
		else
		{
			//cout << "found" << endl;
			ra = it->second;
			totalscore +=ra;
		}
		
	}
	
	
	//cout << endl;
	return totalscore;
}

double calculate_sentiment(double totalscore){
	double sentiment=0;
	sentiment=totalscore/sqrt(pow(totalscore,2)+ALPHA);
	return sentiment;
}

//psaxnei sta tweets kai vriskei se poia coins anaferontai
//ta coins einai apothikeumena se ena unordered map se antistoixeia me to id tous 
// utos oste na ta vriskw argotera sto allo unordered map pou exw se antistoixeia id-name gia na to ektipono
vector<int> find_coins_contained(vector<string> tweet,unordered_map<std::string,int> coins_lexicon){
	vector<int> coins_contained;
	
	for( unsigned int i = 0; i < tweet.size(); i++ )
	{	
		int ra;
		//cout<< tweet[i] << " " ;
		unordered_map<string,int>::iterator it=coins_lexicon.find(tweet[i]);
		//check an iparxei o arithmos stin domi alliws cointos
		if(it == coins_lexicon.end()){
			//cout << "not found" <<endl;
		}
		else
		{
			//cout << "found" << endl;
			ra = it->second;
			//cout << ra << endl;
			coins_contained.push_back(ra);
		}
	}
	//cout<< endl;

	/*for(unsigned int i=0;i<coins_contained.size();i++){
		cout << coins_contained[i] << endl;
		}*/
	return coins_contained;
}

void beforemagicArray(vector<User*> Users,int coinssize,vector<Feelings*>& feelings,vector<Feelings*>& feelings_withInf){
	cout << "--- " << Users.size();
	double inf = std::numeric_limits<double>::infinity();
	for(unsigned int i=0;i<Users.size();i++){
		Feelings* Feeling = new Feelings();
		Feelings* Feeling_withinf = new Feelings();
		vector<Tweet*> Tweets;
		Tweets = Users[i]->return_tweets();
		int User_id = Users[i]->return_user_id();
		Feeling->setUserid(User_id);
		Feeling_withinf->setUserid(User_id);
		vector<double> coinF;

		for(unsigned int f=0;f<coinssize;f++){
			coinF.push_back(inf);
		}
		for(unsigned int j=0;j<Tweets.size();j++){
			vector<int> coinsintweet = Tweets[j]->return_coins_contained();
			for(unsigned int k=0;k<coinsintweet.size();k++){
				//cout << "for coin" << coinsintweet[k] << " senti = " << Tweets[j]->return_senti() << endl;
				coinF[coinsintweet[k]]= Tweets[j]->return_senti();
			}  
    	}
		int counter_of_coins=0;
		double avg=0;
		for(unsigned int j=0;j<coinF.size();j++){
			if(coinF[j]!=inf){
				avg+=coinF[j];
				counter_of_coins++;
			}
		}
		Feeling_withinf->setCoinsF(coinF);  
		feelings_withInf.push_back(Feeling_withinf);
		if(counter_of_coins==0)
			avg=0;
		else
			avg=avg/counter_of_coins;
		//cout << "avg" << avg <<  endl;
		for(unsigned int d=0;d<coinF.size();d++){
			if(coinF[d]==inf){
				coinF[d]=avg;
				//cout<<"WHY " << coinF[d] <<endl;
			}
		}
		Feeling->setCoinsF(coinF);  
		feelings.push_back(Feeling);
	}

}

void avgFeelings(std::vector<Feelings*>& feelings){
	 for(unsigned int i=0;i<feelings.size();i++){
		int userid = feelings[i]->return_Userid();
        //cout<< "--------------- Feelings of User : " << userid << endl;
        vector<double> feel = feelings[i]->return_coins_F();
		double avg=0;
		int counter=0;
        for(unsigned int j=0;j<feel.size();j++){
			if(feel[j]!=0){
				avg+=feel[j];
				counter++;
			}
            /*string ra;
            //cout<< tweet[i] << " " ;
            unordered_map<int,string>::iterator it=coinlexicon.find(j);
            //check an iparxei o arithmos stin domi alliws cointos
            if(it == coinlexicon.end()){
                //cout << "not found" <<endl;
            }
            else
            {
                ra = it->second;
            }*/
            //cout<< " old " << feel[j];
        }
		//KANONIKOPOIISI THA GINEI META TO HASHING
		//cout << endl;
		for(unsigned int j=0;j<feel.size();j++){
			if(feel[j]!=0){
				feel[j] = (double)(feel[j]-avg) / counter;
				//cout<<"NEW:" << feel[j];
			}
		}
		//cout<< "Avg: " <<avg << "counter " << counter << endl;
    }
}

void feelings_to_dataset(vector<Feelings*>& feelings,DataSet& set){
	for(unsigned int i=0;i<feelings.size();i++){
		int userid = feelings[i]->return_Userid();
        vector<double> feel = feelings[i]->return_coins_F();
		string name="item" + to_string(userid);
		Item *p = new Item(name);
		p->set_Userid(userid);
		for(unsigned int j=0;j<feel.size();j++){
			p->AddData(feel[j]);
		}
		set.AddData_toDataSet(p);
	}
}

vector<vector<int>> findPnearestLSH(vector<Feelings*>& feelings_withInf,int metric,int k,int L,vector<Feelings*>& feelings,DataSet& setOfFeelings,int P){
	int ni=setOfFeelings.Return_size();
    //cout <<" ni " <<  feelings[1]->return_coins_F().size() << endl;
	k=3;
    LSH *lsh = new LSH(feelings[1]->return_coins_F().size(),k,L,ni,metric);
    lsh->Calc_Cosine(&setOfFeelings); //NA PENREI FEELINGS
	

	//cout<< "---" << feelings.size() <<endl;
	//cout << endl;
	//cout<<endl;
	double inf = std::numeric_limits<double>::infinity();
    //avgFeelings(feelings); //KAPOU PREPEI NA GINETE KANONIKOPOIISI 
	vector<vector<int>> Top5;
	for(unsigned int i=0;i<feelings.size();i++){
		list<Item*> P_nearest;
		int counter_zero_user=0;
		int flag=0;
		int userid = feelings[i]->return_Userid();
        vector<double> feel = feelings[i]->return_coins_F();
		for(unsigned int h=0;h<feelings.size();h++){
			if(feel[h]==0)
				counter_zero_user++;
		}
		if(counter_zero_user==feel.size()){ //edo tha prepei na tu protino asxeta coins 
			flag=1;
	//		cout << "AKANTOUNTOUNTOU" <<endl;
		}
		if(flag==0){ // edo tha vrisko tous P kontinoterous k tha efarmozw ton tipo 
			list<Item*> ItemsInBucket = lsh->Q_Calc_Cosine(&setOfFeelings,feel);
			list<Item*>::iterator iter;
			vector<double> distances;
			int IteM=0;
			//cout << "------------------- SIZE OF BUCKET : --------------  " << ItemsInBucket.size() << endl;
			for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
			{	
				Item* it=*iter;
				//cout << "gia to Item " << IteM << endl;
				double distance_fromcluster=0.0;
				vector<double> i_data = it->return_item_data();

				for(unsigned int h=0;h<i_data.size();h++){
					if(i_data[h]==0)
						counter_zero_user++;
				}
				if(counter_zero_user==i_data.size()){ //edo tha prepei na tu protino asxeta coins 
					distances.push_back(inf);
			//		cout << "AKANTOUNTOUNTOU" <<endl;
				}
				else
			/*	cout << "[" << endl;
				for(unsigned int i=0;i<i_data.size();i++){
					cout << i_data[i] << " ";
				}
				cout << "]" <<endl;*/
				//cout << "must be 100 : " <<i_data.size() << endl;
				{
					distance_fromcluster = C_distance(feel,i_data,i_data.size());
					distances.push_back(distance_fromcluster);
				}
				//cout << " DISTANCE FROM USER:" <<  distance_fromcluster << endl;
			}
			int counter_P=0;
			

			//psaxnw na vrw tous P kontinoterous users me vasi to distance tous 
			int n_S=-1;
			while(counter_P<P){
				//cout<< "COUNTER_P" <<counter_P <<endl;
				vector<double>::iterator result = min_element(begin(distances),end(distances));
				n_S = distance(begin(distances),result);
				//cout<<"distance " << distances[n_S] <<endl;
				distances[n_S] = inf;
				auto it = next(ItemsInBucket.begin(),n_S);
				P_nearest.push_back(*it);
				counter_P++;
			}

		}
		//exw tous P kontinoterous kai prepei na mantepso vasi auton ta kena mu nomismata 
	//	cout << "IM IN" << i <<endl;
		
		Top5.push_back(calculateRelateCoins(feelings_withInf,*feelings[i],P_nearest,feelings)); 
	}
	delete lsh;
	return Top5;	
}

vector<int> calculateRelateCoins(vector<Feelings*> feelings_withInf,Feelings& target,list<Item*>& P_nearest,vector<Feelings*> feelings){
	//R(Utarget,ci) = Utarget/avg + (1/d(Ui,Utarget))*R(Ui,ci)+........
	
	double inf = std::numeric_limits<double>::infinity();
	vector<int> Top5ToPrint;

	if(P_nearest.size()!=0){
		int target_id = target.return_Userid();
		int val=-1;
		for(unsigned int p=0;p<feelings_withInf.size();p++){
			if(feelings_withInf[p]->return_Userid()==target_id)
				val=p;
		}
		cout << val <<endl;
		vector<double> target_data = feelings_withInf[val]->return_coins_F();
		vector<double> target_d = target.return_coins_F();
		//int userid = target->return_Userid();
		//double avg = avgFeelings_V(target_data); //avg target
		
		//gia kathe keno coin
		//paw k psaxnw apo kathe p_nearest
		//provlepseis
		double Rating1;
		double Rating;
		//cout<< "tz "<<target_data.size() <<endl;
		vector<double> allcoins;
		for(unsigned int k=0;k<target_data.size();k++)
				allcoins.push_back(-inf);

		for(unsigned int p=0;p<target_data.size();p++){
			Rating1=0.0; //kanonika edw prepei na einai INF gia na min mpleko ta 0 me ta mi arxikopioimena
			//Rating+=avg;
			if(target_data[p]==inf){
				vector<double> target_dat = target_d;
				double avg_sim =0.0;
				list<Item*>::iterator iter;
				for(iter=P_nearest.begin(); iter != P_nearest.end() ; ++iter) //me iterator diasxizo tin lista me tus pio kontinus users mu
				{		
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					vector<double> i_data = it->return_item_data();
					///cout << "Rating " << Rating << endl;
					avg_sim+= cosine_similarity(target_dat,i_data);
					//cout<<"avg_sim" <<avg_sim <<endl;
				}
				if(avg_sim==0)
					Rating1=0;
				else
					Rating1=1/avg_sim;
				//cout << "Rating1 " << Rating1 <<endl;
				double avgtar=0;
				int countertar=0;
				for(unsigned int j=0;j<target_dat.size();j++){
					if(target_data[j]!=inf){
						avgtar+=target_data[j];
						countertar++;
					}
				}

				list<Item*>::iterator iterr;
				Rating=0.0;
				if(countertar==0)
					Rating=0;
				else
					Rating=avgtar/countertar;

				for(iterr=P_nearest.begin(); iterr != P_nearest.end() ; ++iterr) //me iterator diasxizo tin lista me tus pio kontinus users mu
				{	
					Item* it=*iterr;
					//cout << "gia to Item " << IteM << endl;
					vector<double> i_data = it->return_item_data();
					double avg=0;
					int counter=0;
					for(unsigned int j=0;j<i_data.size();j++){
						if(i_data[j]!=0){
							avg+=i_data[j];
							counter++;
						}
					}
					if (counter==0)
						avg=0;
					else
						avg=avg/counter;
					//cout <<"Target: " <<target_dat[p] <<endl;
					Rating+= cosine_similarity(target_dat,i_data)*(target_dat[p]-avg); 
					
				}
			}
			//cout<<"Ratningg : "<<Rating <<endl;
			Rating=Rating*Rating1;
			//cout<< "rating" << Rating << endl;
			//cout <<"RATING FOR COIN: " << p <<" FOR USER  " << target.return_Userid()<< " is: " << Rating << endl;
			allcoins[p]=Rating;

		}
		int top5=0;
		
		
		for(unsigned int d=0;d<allcoins.size();d++){
			while(top5<5){
				int n_S=-1;
				vector<double>::iterator result = max_element(begin(allcoins),end(allcoins));
				n_S = distance(begin(allcoins),result);
				//coin N_S stin thesi allcoins[n_s] 
				//cout<< " TOP " << top5 << " coin " << n_S << " with rating: "  << allcoins[n_S] <<endl;
				Top5ToPrint.push_back(n_S);
				allcoins[n_S] = -inf;
				top5++;
			}
		}
		//cout << "------------------------" <<endl;
	}
	else
	{
		for(int w=0;w<5;w++)
			Top5ToPrint.push_back(w);
	}
	return Top5ToPrint;

}

double cosine_similarity(std::vector<double> y,std::vector<double> x){
	double C_d = 0;
	double aa=0;
	double bb=0;
	for(unsigned int l = 0; l < x.size(); l++ ){
		C_d = C_d + (y[l]*x[l]);
		aa = aa + pow(y[l],2);
		bb = bb + pow(x[l],2);			
	}
	double aaa = sqrt(aa);
	double bbb = sqrt(bb);
	double cos_ = 0.0;
	if(aaa*bbb==0)
		cos_=0;
	else
		cos_ = (double)C_d / (double)(aaa*bbb);
	//cout << "COS:" << cos_ << endl;
	return cos_;
}

double avgFeelings_V(std::vector<double>& feel){
		double avg=0;
		int counter=0;
        for(unsigned int j=0;j<feel.size();j++){
			if(feel[j]!=0){
				avg+=feel[j];
				counter++;
			}
            /*string ra;
            //cout<< tweet[i] << " " ;
            unordered_map<int,string>::iterator it=coinlexicon.find(j);
            //check an iparxei o arithmos stin domi alliws cointos
            if(it == coinlexicon.end()){
                //cout << "not found" <<endl;
            }
            else
            {
                ra = it->second;
            }*/
            //cout<< " old " << feel[j];
        }
		//KANONIKOPOIISI THA GINEI META TO HASHING
		//cout << endl;
		//avg=avg/counter;
		for(unsigned int j=0;j<feel.size();j++){
			if(feel[j]!=0){
				feel[j] = (double)(feel[j]-(avg/counter));
				//cout<<"NEW:" << feel[j];
			}
		}
		return avg;
		//cout<< "Avg: " <<avg << "counter " << counter << endl;
}

void OutPut(int s,double duration,string output_file,std::vector<std::vector<int>> Top5,vector<User*> Users,std::unordered_map<int,std::string> coinlexicon){
	fstream myfile;
	myfile.open (output_file,  fstream::out | fstream::app);
	if(s==1)
		myfile << "Cosine LSH \n";
	else if(s==2)
		myfile << "Clustering \n";

	myfile << "-------------------------------------------" << endl;
	for(unsigned int i=0;i<Top5.size();i++)
    {
        vector<int> feeli = Top5[i];
        myfile << "<User" << Users[i]->return_user_id() << ">";
        myfile << "[" ;    
        for(unsigned int j=0;j<feeli.size();j++){
			string ra;
			//cout<< tweet[i] << " " ;
			unordered_map<int,string>::iterator it=coinlexicon.find(feeli[j]);
			//check an iparxei o arithmos stin domi alliws cointos
			if(it == coinlexicon.end()){
				//cout << "not found" <<endl;
			}
			else
			{
				ra = it->second;
				myfile << ra << " ";
			}
        }
        myfile << "]" << endl;
	}
	myfile << "Execution Time: < " << duration << " >" <<endl;
	myfile.close();

}


vector<std::vector<int>> findPnearestClustering(std::vector<Feelings*>& feelings_withInf,int metric,int k,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P,std::vector<Cluster*> Clusters,std::vector<User*> Users) //vriskei ta top 5 gia kathe user
{
	double inf = std::numeric_limits<double>::infinity();
		vector<vector<int>> Top2;
	for(unsigned int f=0;f<feelings.size();f++){
		vector<Item*> P_nearest;
		vector<Item*> Cluster_Items;
		vector<double> user_data;
		int flag=0;
        for(unsigned int i=0;i<Clusters.size();i++){
			if(Clusters[i]->Return_size() != 0 ){
				Cluster_Items = Clusters[i]->return_items() ;
				for(unsigned int j=0;j<Cluster_Items.size();j++){
					//cout << Cluster_Items[j]->return_User_id() <<endl;
					if( Cluster_Items[j]->return_User_id() == feelings[f]->return_Userid()){
						//vrisko oti o user[f] anikei sto cluster[i] 
						//cout<<  "------------------- Custer " << Clusters[i]->return_cluster_id() << " Size: " << Clusters[i]->Return_size() <<endl;
						user_data = feelings[f]->return_coins_F();
						//kanw break kai pernw to sigkekrimeno cluster oste na vrw tous P kontinoterous se auton ton user
						flag=1;				
					}
					if(flag==1)
						break;
				}
			}
			if(flag==1)
				break;
		}
		vector<double> distances;
		for(unsigned int s=0;s<Cluster_Items.size();s++){
			double distance_fromcluster=0.0;
			vector<double> i_data = Cluster_Items[s]->return_item_data();
			int counter_zero_user=0;
			
			for(unsigned int h=0;h<i_data.size();h++){
				if(i_data[h]==0)
					counter_zero_user++;
			}
			if(counter_zero_user==i_data.size()){ //edo tha prepei na tu protino asxeta coins 
				distances.push_back(inf);
			}
			else
			{
				distance_fromcluster = E_distance(user_data,i_data,i_data.size());
				distances.push_back(distance_fromcluster);
			}
		}

		int counter_P=0;
		//psaxnw na vrw tous P kontinoterous users me vasi to distance tous 
		int n_S=-1;
		while(counter_P<P){
			//cout<< "COUNTER_P" <<counter_P <<endl;
			vector<double>::iterator result = min_element(begin(distances),end(distances));
			n_S = distance(begin(distances),result);
			//cout<<"distance " << n_S <<endl;
			distances[n_S] = inf;
			//cout<<"distance " << distances[n_S] <<endl;
			auto it = next(Cluster_Items.begin(),n_S);
			P_nearest.push_back(*it);
			counter_P++;
		}
		Top2.push_back(calculateRelateCoins_2(feelings_withInf,*feelings[f],P_nearest,feelings)); 
	}
	return Top2;
}



 vector<int> calculateRelateCoins_2(vector<Feelings*> feelings_withInf,Feelings& target,vector<Item*>& P_nearest,vector<Feelings*> feelings){
	//R(Utarget,ci) = Utarget/avg + (1/d(Ui,Utarget))*R(Ui,ci)+........
	
	double inf = std::numeric_limits<double>::infinity();
	vector<int> Top2ToPrint;
	if(P_nearest.size()!=0){
		int target_id = target.return_Userid();
		int val=-1;
		for(unsigned int p=0;p<feelings_withInf.size();p++){
			if(feelings_withInf[p]->return_Userid()==target_id)
				val=p;
		}
		//cout << val <<endl;
		vector<double> target_data = feelings_withInf[val]->return_coins_F();
		vector<double> target_d = target.return_coins_F();
		//int userid = target->return_Userid();
		//double avg = avgFeelings_V(target_data); //avg target
		
		//gia kathe keno coin
		//paw k psaxnw apo kathe p_nearest
		//provlepseis
		double Rating1;
		double Rating;
		//cout<< "tz "<<target_data.size() <<endl;
		vector<double> allcoins;
		for(unsigned int k=0;k<target_data.size();k++)
				allcoins.push_back(-inf);

		for(unsigned int p=0;p<target_data.size();p++){
			Rating1=0.0; //kanonika edw prepei na einai INF gia na min mpleko ta 0 me ta mi arxikopioimena
			//Rating+=avg;
			if(target_data[p]==inf){
				vector<double> target_dat = target_d;
				double avg_sim =0.0;
				for(unsigned int q=0;q<P_nearest.size();q++) //me iterator diasxizo tin lista me tus pio kontinus users mu
				{		
					//cout << "gia to Item " << IteM << endl;
					vector<double> i_data = P_nearest[q]->return_item_data();
					///cout << "Rating " << Rating << endl;
					avg_sim+= cosine_similarity(target_dat,i_data);
					//cout<<"avg_sim" <<avg_sim <<endl;
				}
				if(avg_sim==0)
					Rating1=0;
				else
					Rating1=1/avg_sim;
				//cout << "Rating1 " << Rating1 <<endl;
				double avgtar=0;
				int countertar=0;
				for(unsigned int j=0;j<target_dat.size();j++){
					if(target_data[j]!=inf){
						avgtar+=target_data[j];
						countertar++;
					}
				}

				list<Item*>::iterator iterr;
				Rating=0.0;
				if(countertar==0)
					Rating=0;
				else
					Rating=avgtar/countertar;

				for(unsigned int q=0;q<P_nearest.size();q++) //me iterator diasxizo tin lista me tus pio kontinus users mu
					{
					//cout << "gia to Item " << IteM << endl;
					vector<double> i_data = P_nearest[q]->return_item_data();
					double avg=0;
					int counter=0;
					for(unsigned int j=0;j<i_data.size();j++){
						if(i_data[j]!=0){
							avg+=i_data[j];
							counter++;
						}
					}
					if (counter==0)
						avg=0;
					else
						avg=avg/counter;
					//cout <<"Target: " <<target_dat[p] <<endl;
					Rating+= euclidean_similarity(target_dat,i_data,i_data.size())*(target_dat[p]-avg); 
					
				}
			}
			//cout<<"Ratningg : "<<Rating <<endl;
			Rating=Rating*Rating1;
			//cout<< "rating" << Rating << endl;
			//cout <<"RATING FOR COIN: " << p <<" FOR USER  " << target.return_Userid()<< " is: " << Rating << endl;
			allcoins[p]=Rating;

		}
		int top2=0;
		
		
		for(unsigned int d=0;d<allcoins.size();d++){
			while(top2<2){
				int n_S=-1;
				vector<double>::iterator result = max_element(begin(allcoins),end(allcoins));
				n_S = distance(begin(allcoins),result);
				//coin N_S stin thesi allcoins[n_s] 
				//cout<< " TOP " << top2 << " coin " << n_S << " with rating: "  << allcoins[n_S] <<endl;
				Top2ToPrint.push_back(n_S);
				allcoins[n_S] = -inf;
				top2++;
			}
		}
	}
	else
	{
		for(int w=0;w<5;w++)
			Top2ToPrint.push_back(w);
	}

	//cout << "------------------------" <<endl;
	return Top2ToPrint;

}


double euclidean_similarity(vector<double> y,vector<double> x,int d){
	double E_d = 0;
	double similarity=0.0;
	for( int l = 0; l < (int)y.size(); l++ ){
		E_d = E_d +  pow((double)y[l]-x[l],(double)2);
		//cout << " ED: " << E_d << endl;
	}
	double new_E_d = sqrt(E_d);
	//cout << " NEWED: " << new_E_d << endl;
	similarity = 1/(1+new_E_d);
	return similarity;
	}

void Dataset_Project2(int metric,int k,std::string input_file3,DataSet& set,vector<Cluster*>& Clusters){
    string line;
    ifstream out(input_file3);
  
    int d=0;
    cout << input_file3 << endl;
    while ( getline( out, line )){
        string id;
        istringstream ss( line );
        d=0;
        string::size_type sz;
        size_t pos = 0;
        string token;
        string delimiter = ",";
        int fir=0;
        Item *p ;
        while ((pos = line.find(delimiter)) != string::npos) {
            if(fir==0){
                token = line.substr(0, pos);
                //	cout << "TOKEN" << token << endl;
                int id= stod(token,&sz);
                string name="item" + to_string(id);
                p = new Item(name);
				p->set_id(id);
                line.erase(0, pos + delimiter.length());
                //cout<< "NAME " <<  name << endl;
                fir=1;
            }
            else
                if (fir==1){
                    token = line.substr(0, pos);
                //    cout << "TOKEN" << token << endl;
                    double l= stod(token,&sz);
                    p->AddData(l);
                    line.erase(0, pos + delimiter.length());
                    d++;
                }
        }
        //cout << "Dimensions" << d << endl;
        set.AddData_toDataSet(p);
    } 
    out.close();
    int n=set.Return_size();
    //cout << "N" << n << endl;
    Combination_1_1_1(k,&set,Clusters,d,metric);
    cout<< Clusters.size() << endl;

}


void magicArrayVirtualUsers(std::vector<Cluster*> Clusters_project2,std::vector<User*> Users,int coinssize,std::vector<Feelings*>& feelings,std::vector<Feelings*>& feelings_withInf){
	double inf = std::numeric_limits<double>::infinity();
	for(unsigned int i=0;i<Clusters_project2.size();i++){//gia kathe cluster pernw ta items tou 
		vector<Item*> cluster_items = Clusters_project2[i]->return_items();
		//gia kathe item psaxnw na vrw antistixoia stus users kai ta coins_contained se auto
		Feelings* Feeling = new Feelings();
		Feelings* Feeling_withinf = new Feelings();
		Feeling->setUserid(Clusters_project2[i]->return_cluster_id());
		Feeling_withinf->setUserid(Clusters_project2[i]->return_cluster_id());
		vector<double> coinF;

		for(unsigned int f=0;f<coinssize;f++){
			coinF.push_back(inf);
		}

		for(unsigned int j=0;j<cluster_items.size();j++){
			int item_id = cluster_items[j]->returnid();
			for(unsigned int f=0;f<Users.size();f++){ //psaxnw na vrw to id tou tweet stous users
				vector<Tweet*> usertweets = Users[f]->return_tweets();
				for(unsigned int t=0;t<usertweets.size();t++){
					if(usertweets[t]->return_tweetid()== item_id ){ //an to id tou tweet tu user = item_id tu cluster
					//tote pairnw ta senti k ta coins_contained k simplirono ton pinaka feelings
						vector<int> coinsintweet = usertweets[t]->return_coins_contained();
						double senti = usertweets[t]->return_senti();
						for(unsigned int g=0;g<coinsintweet.size();g++){
							if(coinF[coinsintweet[g]]==inf){
								coinF[coinsintweet[g]]=0;
							}
							coinF[coinsintweet[g]]+=senti;
							//cout << senti << endl;
						}
					}
				}
			}
		}
		
		/*cout <<"Cluster" << Clusters_project2[i]->return_cluster_id() << "[ " ;
		for(unsigned int f=0;f<coinssize;f++){
			cout << coinF[f]  <<" " ;
		}
		cout << " ]" << endl;*/
		int counter_of_coins=0;
		double avg=0;
		for(unsigned int j=0;j<coinF.size();j++){
			if(coinF[j]!=inf){
				avg+=coinF[j];
				counter_of_coins++;
			}
		}
		Feeling_withinf->setCoinsF(coinF);  
		feelings_withInf.push_back(Feeling_withinf);
		if(counter_of_coins==0)
			avg=0;
		else
			avg=avg/counter_of_coins;
		//cout << "avg" << avg <<  endl;
		for(unsigned int d=0;d<coinF.size();d++){
			if(coinF[d]==inf){
				coinF[d]=avg;
				//cout<<"WHY " << coinF[d] <<endl;
			}
		}
		Feeling->setCoinsF(coinF);  
		feelings.push_back(Feeling);
	}
}


vector<vector<int>> findPnearestLSH_2(vector<Feelings*>& feelings_Or,vector<Feelings*>& feelings_withInf,int metric,int k,int L,vector<Feelings*>& feelings,DataSet& setOfFeelings,int P){
	int ni=setOfFeelings.Return_size();
	cout << "setof feelings size" << setOfFeelings.Return_size() << endl;
    //cout <<" ni " <<  feelings[1]->return_coins_F().size() << endl;
	k=1;
    LSH *lsh = new LSH(feelings[1]->return_coins_F().size(),k,L,ni,metric);
    lsh->Calc_Cosine(&setOfFeelings); //NA PENREI FEELINGS
	

	cout<< "---" << feelings.size() <<endl;
	//cout << endl;
	//cout<<endl;
	double inf = std::numeric_limits<double>::infinity();
    //avgFeelings(feelings); //KAPOU PREPEI NA GINETE KANONIKOPOIISI 
	vector<vector<int>> Top5;
	for(unsigned int i=0;i<feelings_Or.size();i++){
		list<Item*> P_nearest;
		int counter_zero_user=0;
		int flag=0;
		int userid = feelings_Or[i]->return_Userid();
        vector<double> feel = feelings_Or[i]->return_coins_F();
		for(unsigned int h=0;h<feelings_Or.size();h++){
			if(feel[h]==0)
				counter_zero_user++;
		}
		if(counter_zero_user==feel.size()){ //edo tha prepei na tu protino asxeta coins 
			flag=1;
	//		cout << "AKANTOUNTOUNTOU" <<endl;
		}
		if(flag==0){ // edo tha vrisko tous P kontinoterous k tha efarmozw ton tipo 
			list<Item*> ItemsInBucket = lsh->Q_Calc_Cosine(&setOfFeelings,feel);
			list<Item*>::iterator iter;
			vector<double> distances;
			int IteM=0;
			//cout << "------------------- SIZE OF BUCKET : --------------  " << ItemsInBucket.size() << endl;
			for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
			{	
				Item* it=*iter;
				//cout << "gia to Item " << IteM << endl;
				double distance_fromcluster=0.0;
				vector<double> i_data = it->return_item_data();
				distance_fromcluster = C_distance(feel,i_data,i_data.size());
				distances.push_back(distance_fromcluster);
				
				//cout << " DISTANCE FROM USER:" <<  distance_fromcluster << endl;
			}
			int counter_P=0;
			

			//psaxnw na vrw tous P kontinoterous users me vasi to distance tous 
			int n_S=-1;

			while(counter_P<P & ItemsInBucket.size()>0 & distances.size()>counter_P ){
				//cout<< "COUNTER_P" <<counter_P <<endl;
				vector<double>::iterator result = min_element(begin(distances),end(distances));
				n_S = distance(begin(distances),result);
				//cout<<"distance " << n_S <<endl;
				distances[n_S] = inf;
				auto it = next(ItemsInBucket.begin(),n_S);
				P_nearest.push_back(*it);
				counter_P++;
			}

		}
		//exw tous P kontinoterous kai prepei na mantepso vasi auton ta kena mu nomismata 
	//	cout << "IM IN" << i <<endl;
		cout<<"Pnearest" << P_nearest.size() << endl;
		Top5.push_back(calculateRelateCoins_B1(feelings_withInf,*feelings_Or[i],P_nearest,feelings)); 
	}
	delete lsh;
	return Top5;	
}


vector<int> calculateRelateCoins_B1(vector<Feelings*> feelings_withInf,Feelings& target,list<Item*>& P_nearest,vector<Feelings*> feelings){
	//R(Utarget,ci) = Utarget/avg + (1/d(Ui,Utarget))*R(Ui,ci)+........
	
	double inf = std::numeric_limits<double>::infinity();
	vector<int> Top5ToPrint;

	if(P_nearest.size()!=0){
		int target_id = target.return_Userid();
		int val=-1;
		for(unsigned int p=0;p<feelings_withInf.size();p++){
			if(feelings_withInf[p]->return_Userid()==target_id)
				val=p;
		}
		cout << val <<endl;
		vector<double> target_data = feelings_withInf[val]->return_coins_F();
		vector<double> target_d = target.return_coins_F();
		//int userid = target->return_Userid();
		//double avg = avgFeelings_V(target_data); //avg target
		
		//gia kathe keno coin
		//paw k psaxnw apo kathe p_nearest
		//provlepseis
		double Rating1;
		double Rating;
		//cout<< "tz "<<target_data.size() <<endl;
		vector<double> allcoins;
		for(unsigned int k=0;k<target_data.size();k++)
				allcoins.push_back(-inf);

		for(unsigned int p=0;p<target_data.size();p++){
			Rating1=0.0; //kanonika edw prepei na einai INF gia na min mpleko ta 0 me ta mi arxikopioimena
			//Rating+=avg;
			if(target_data[p]==inf){
				vector<double> target_dat = target_d;
				double avg_sim =0.0;
				list<Item*>::iterator iter;
				for(iter=P_nearest.begin(); iter != P_nearest.end() ; ++iter) //me iterator diasxizo tin lista me tus pio kontinus users mu
				{		
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					vector<double> i_data = it->return_item_data();
					///cout << "Rating " << Rating << endl;
					avg_sim+= cosine_similarity(target_dat,i_data);
					//cout<<"avg_sim" <<avg_sim <<endl;
				}
				if(avg_sim==0)
					Rating1=0;
				else
					Rating1=1/avg_sim;
				//cout << "Rating1 " << Rating1 <<endl;
				double avgtar=0;
				int countertar=0;
				for(unsigned int j=0;j<target_dat.size();j++){
					if(target_data[j]!=inf){
						avgtar+=target_data[j];
						countertar++;
					}
				}

				list<Item*>::iterator iterr;
				Rating=0.0;
				if(countertar==0)
					Rating=0;
				else
					Rating=avgtar/countertar;

				for(iterr=P_nearest.begin(); iterr != P_nearest.end() ; ++iterr) //me iterator diasxizo tin lista me tus pio kontinus users mu
				{	
					Item* it=*iterr;
					//cout << "gia to Item " << IteM << endl;
					vector<double> i_data = it->return_item_data();
					double avg=0;
					int counter=0;
					for(unsigned int j=0;j<i_data.size();j++){
						if(i_data[j]!=0){
							avg+=i_data[j];
							counter++;
						}
					}
					if (counter==0)
						avg=0;
					else
						avg=avg/counter;
					//cout <<"Target: " <<target_dat[p] <<endl;
					Rating+= cosine_similarity(target_dat,i_data)*(target_dat[p]-avg); 
					
				}
			}
			//cout<<"Ratningg : "<<Rating <<endl;
			Rating=Rating*Rating1;
			//cout<< "rating" << Rating << endl;
			//cout <<"RATING FOR COIN: " << p <<" FOR USER  " << target.return_Userid()<< " is: " << Rating << endl;
			allcoins[p]=Rating;

		}
		int top5=0;
		
		
		for(unsigned int d=0;d<allcoins.size();d++){
			while(top5<5){
				int n_S=-1;
				vector<double>::iterator result = max_element(begin(allcoins),end(allcoins));
				n_S = distance(begin(allcoins),result);
				//coin N_S stin thesi allcoins[n_s] 
				//cout<< " TOP " << top5 << " coin " << n_S << " with rating: "  << allcoins[n_S] <<endl;
				Top5ToPrint.push_back(n_S);
				allcoins[n_S] = -inf;
				top5++;
			}
		}
		//cout << "------------------------" <<endl;
	}
	else
	{
		for(int w=0;w<5;w++)
			Top5ToPrint.push_back(w);
	}
	return Top5ToPrint;

}


vector<std::vector<int>> findPnearestClustering_B2(std::vector<Feelings*>& feelings_withInf,int metric,int k,std::vector<Feelings*>& feelings,DataSet& setOfFeelings,int P,std::vector<Cluster*> Clusters,std::vector<User*> Users) //vriskei ta top 5 gia kathe user
{
	double inf = std::numeric_limits<double>::infinity();
	vector<vector<int>> Top2;
	for(unsigned int f=0;f<feelings.size();f++){
		vector<Item*> P_nearest;
		int flag=0;
		vector<double> distances_fromcluster;
		vector<double> user_data = feelings[f]->return_coins_F();
        for(unsigned int i=0;i<Clusters.size();i++){
			double distance_clu=0.0;
			vector<double> cluster_double = Clusters[i]->return_i_cluster();
			distance_clu = E_distance(user_data,cluster_double,cluster_double.size());
			distances_fromcluster.push_back(distance_clu);
		}
		int iss=-1; // i thesi tu cluster ston vector g n dw se poio cluster einai pio konta to feeling mou
		vector<double>::iterator resultt = min_element(begin(distances_fromcluster),end(distances_fromcluster));
		iss = distance(begin(distances_fromcluster),resultt);

		vector<Item*> Cluster_Items = Clusters[iss]->return_items();
		vector<double> distances;
		for(unsigned int s=0;s<Cluster_Items.size();s++){
			double distance_fromcluster=0.0;
			vector<double> i_data = Cluster_Items[s]->return_item_data();
			int counter_zero_user=0;
			
			for(unsigned int h=0;h<i_data.size();h++){
				if(i_data[h]==0)
					counter_zero_user++;
			}
			if(counter_zero_user==i_data.size()){ //edo tha prepei na tu protino asxeta coins 
				distances.push_back(inf);
			}
			else
			{
				distance_fromcluster = E_distance(user_data,i_data,i_data.size());
				distances.push_back(distance_fromcluster);
			}
		}

		int counter_P=0;
		//psaxnw na vrw tous P kontinoterous users me vasi to distance tous 
		int n_S=-1;
		while(counter_P<P & Cluster_Items.size()>0 & distances.size()>counter_P){
			//cout<< "COUNTER_P" <<counter_P <<endl;
			vector<double>::iterator result = min_element(begin(distances),end(distances));
			n_S = distance(begin(distances),result);
			//cout<<"distance " << n_S <<endl;
			distances[n_S] = inf;
			//cout<<"distance " << distances[n_S] <<endl;
			auto it = next(Cluster_Items.begin(),n_S);
			P_nearest.push_back(*it);
			counter_P++;
		}
		Top2.push_back(calculateRelateCoins_2(feelings_withInf,*feelings[f],P_nearest,feelings)); 
	}
	return Top2;
}
