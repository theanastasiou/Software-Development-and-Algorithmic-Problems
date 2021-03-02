#include "Hash_Cosine.h"
#define W 1 
using namespace std;


Hash_Cosine::Hash_Cosine(int t,int k,int d){
		this->T=t;
		this->k=k;
		this->d=d;
		//cout << "tc" << this->T << endl;
		//cout<<"A Hash_Cosine Created! "<< endl;
		//rand gia pinaka ri (tha kalw mia sinartisi)
		//rand gia hv+ht twn h + dimiourgia h1...hk (tha kalw mia sinartisi)
		//dimiourgia vector Buckets me Bucket analoga me to L gia Euclidean (tha kalw mia sinartisi)
		for(int i = 0; i < k; ++i){
			//rand gia hv+ht twn h + dimiourgia h1...hk (tha kalw mia sinartisi)
			vector <double> v;
			for(int l=0;l<d;l++){
				double hv = this->Return_Ri();
				v.push_back(hv);
			}
			this->AddFun(new h_Cosine(v));	
	}				
//dimiourgia vector Buckets me Bucket analoga me to L gia Euclidean (tha kalw mia sinartisi)
	for(int q = 0; q < this->T; ++q){
		this->AddBucket(new Bucket(q));
	}
		
			
	}
	
Hash_Cosine::~Hash_Cosine(){
//	Memory+=sizeof(h_fun);
	for(int i=0;i<this->k;i++){
//		Memory+=sizeof(h_fun[i]);
		delete h_fun[i];
		}
	h_fun.erase (h_fun.begin(),h_fun.end());
	
//	Memory+=sizeof(Buckets);
	for(int i=0;i<this->T;i++){
//		Memory+=sizeof(Buckets[i]);
			delete Buckets[i];
			}
	Buckets.erase (Buckets.begin(),Buckets.end());
	
	/*for(unsigned int i=0; i< Checked.size();i++)
			delete Checked[i];
	Checked.erase (Checked.begin(),Checked.end());*/
	
	//cout << Checked.size() <<endl;
//	Memory+=sizeof(Ri);
	Ri.erase (Ri.begin(),Ri.end());
	//cout << "delete Hash cosine" <<endl;
	}

double  Hash_Cosine::Return_Ri(){
    random_device rd; 
    mt19937 gen(rd());
	double sample;
	normal_distribution<double> d(0.0, 1.0);  //mean = 0.0 variance =0.1
	sample = d(gen); 
	return sample;
	}

void Hash_Cosine::AddFun(h_Cosine* fun){
	h_fun.push_back(fun);
	}
	
void  Hash_Cosine::AddBucket(Bucket* bucket){
	Buckets.push_back(bucket); 
	}

	
vector<h_Cosine*>  Hash_Cosine::return_h(){
	return h_fun;
	}
	
void  Hash_Cosine::AddChecked(Item* item){
	Checked.push_back(item); 
}
 
vector<Item*> Hash_Cosine::return_Checked(){
	return Checked;
} 

vector<Bucket*>  Hash_Cosine::return_Buckets(){
	return Buckets;
	}
	


list<Item*>& Hash_Cosine::Search_Cosine(vector<double> myCl){
	//cout << "Search_Cosine" << endl;
	//cout << "--line-- "<< line << endl;
	vector <h_Cosine*> hh;
	vector <double> hhv;
	vector<double> item_d;
	int bucket_bf=0;
	string name="item_idSQ";
	Item *itt = new Item(name);
	for( int l = 0; l <this->k ; l++ ){
		double p=0;
		hh = this->return_h(); // mou epistrefei tis h sinartiseis 
		hhv = hh[l]->get_hv(); // pernw ton vector pinaka me ta hv tis 1is sinartisis
		int h=0;	
		for(unsigned int s=0;s<myCl.size();s++){
			
			itt->AddData(myCl[s]);
			//cout << "li: " << li << " hhv[h++]: " << hhv[h++] <<endl;
			p =  p + (hhv[h++] * myCl[s]);
		}
		
		//cout << "P" << p << endl;
		int bit=-1;
		if (p >= 0 )
			bit = 1;
		else
			bit = 0;
		bucket_bf = bucket_bf + (bit * pow(2,this->k-1-l));
		//cout << "k: " << k << " l : " << l << " bucket:" << bucket_bf << endl ;	

		
	}
	list<Item*>& ItemsInBucket = Buckets[bucket_bf]->return_Items(); 
	return ItemsInBucket;
	//cout <<"BUCKET BFFF: " << bucket_bf << endl;
	//cout << "------------"<< nuum++ <<"-------------"<<  bucket_bf << endl;
	//itt->DisplayVectorContents();
	//Calc_Cosine_distance(bucket_bf,itt->return_item_data(),min_item,min_distance);
	delete itt;
}


double Hash_Cosine::Cosine_distance(vector<double> y,vector<double> x){
	double C_d = 0;
	double aa=0;
	double bb=0;
	for( int l = 0; l < this->d; l++ ){
		C_d = C_d + (y[l]*x[l]);
		aa = aa + pow(y[l],2);
		bb = bb + pow(x[l],2);			
	}
	double aaa = sqrt(aa);
	double bbb = sqrt(bb);
	double cos_ = 0.0;
	cos_ = (double)C_d / (double)(aaa*bbb);
	double new_C_d = 1 - cos_;
	//cout << " CD: " << new_C_d << endl;
	return new_C_d;
}

void Hash_Cosine::Calc_Cosine_distance(int buck ,vector<double> x,string &min_item,double &min_distance){
	//cout<< "Calc_Cosine_distance" <<endl;
	vector < Bucket* > Buckets;
	Buckets = this->return_Buckets();
	vector<Item*> items_Checked = return_Checked();
	vector<double> item_Data;
	//static int qq=0;
	//Buckets[buck]->ShowBucketItems();
	list<Item*> ItemsInBucket;
	ItemsInBucket = Buckets[buck]->return_Items();
	list<Item*>::iterator iter;
	double C_distance;
	//if (ItemsInBucket.size()>0)
	//cout << "BUCKET[" << buck << "]. has " << ItemsInBucket.size() << " items." << endl;
	for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter)
	{		Item* it=*iter;
		//ELEGXOS AN KSANATSEKARA TO IT
		int flag=0;
		for( int f = 0; f < (int)items_Checked.size() ; f++ ){
			if (items_Checked[f]->return_item_id() == it->return_item_id()){
				flag=1;
				//cout << " ======================== " << it->return_item_id() << endl;
				break;
			}
		}	
		if(flag==1) 
			break;
		item_Data = it->return_item_data() ;
		C_distance = this->Cosine_distance(item_Data,x);
		//cout << "/////////////////C_d" << C_distance << endl;
		if (C_distance >=  0.3) //radius
			continue;
		else{
			//ADD IT STON VECTOR 
			AddChecked(it);
			//cout << "/////////////////C_d" << C_distance << " : " <<  it->return_item_id() <<endl;
			//fstream myfile;
			//myfile.open (output_file,  fstream::out | fstream::app);
			//myfile <<  it->return_item_id() <<"\n";
			//myfile.close();
			if(min_distance==-1){
				min_distance = C_distance;
				min_item = it->return_item_id();
			}
			else if(min_distance>C_distance){
					min_distance = C_distance;
					min_item = it->return_item_id();
			}
		}
	}
}
	
//epistrefei ena arithmo (bucket) sto opoio tha anikei to ite
void Hash_Cosine::Cosine_HF(Item* item){
	//cout << "HF " << endl;
	vector <h_Cosine*> hh;
	vector <double> hhv;
	vector<double> item_d;
	int bucket_bf=0;
	for( int l = 0; l <this-> k ; l++ ){
		double p=0;
		hh = this->return_h(); // mou epistrefei tis h sinartiseis 
		hhv = hh[l]->get_hv(); // pernw ton vector pinaka me ta hv tis 1is sinartisis
		int h=0;
		item_d = item->return_item_data(); // pernw ta data tou item
		for( int g = 0; g < this->d; g++){
			p =  p + (hhv[g] * item_d[h++]); // ipologismos essoterikou ginomenou 
			
		}
		//cout << "P" << p << endl;
		int bit=-1;
		if (p >= 0 )
			bit = 1;
		else
			bit = 0;
		bucket_bf = bucket_bf + (bit * pow(2,this->k-1-l));
		//cout << "k: " << k << " l : " << l << " bucket:" << bucket_bf << endl ;	
	}
	vector < Bucket* > Buckets;
	Buckets = this->return_Buckets();
	//cout << "t" << this->T << endl;
	//cout << "BUCKET BD" <<  bucket_bf << endl;
	//add to bucket
	Buckets[bucket_bf]->AddtoBucket(item);
	//Buckets[bucket_bf]->ShowBucketItems();
	}
	
	

