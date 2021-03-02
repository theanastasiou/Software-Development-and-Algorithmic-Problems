#include "HF_Bucket.h"
using namespace std;

h::h(vector<float> v,float t){
	hv=v;
	ht=t;
	//cout<<"A Hash Created with t:" << ht << endl;
	}
float  h::get_ht(){
		return ht;
				}
				
vector<float>& h::get_hv(){
	return hv;
	}
		
void h::Addtohv(float v){
	hv.push_back(v);
	}
	
h::~h(){
		Memory+=sizeof(hv);
		hv.erase (hv.begin(),hv.end());
		//cout<<"A Hash just Deleted"<< endl;
	}
	

h_Cosine::h_Cosine(vector<float> v){
	hv=v;
	}

vector<float>& h_Cosine::get_hv(){
	return hv;
	}
	
	
void h_Cosine::Addtohv(float v){
	hv.push_back(v);
	}
		
h_Cosine::~h_Cosine(){
		Memory+=sizeof(hv);
		hv.erase (hv.begin(),hv.end());
		//cout<<"A Hash just Deleted"<< endl;
	}

Bucket::Bucket(int n){
		this->num=n;
		//cout<<"A Bucket just Created with id: "<< num << endl;
	}
	
int Bucket::get_num(){
	return num;
	}
	
void Bucket::AddtoBucket(Item* item){
	ItemsInBucket.push_back(item);
	}
	
void Bucket::ShowBucketItems(){
	cout << "Name" << get_num() << endl;
	list<Item*>::iterator iter;
	for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter)
	{		Item* it=*iter;
			cout << " ITEM ID : " << it->return_item_id() << endl;
	}
	}
	
list< Item* > Bucket::return_Items(){
	return ItemsInBucket;
	}

Bucket::~Bucket(){
	Memory+=sizeof(ItemsInBucket);
		/*for (auto &item:ItemsInBucket)
			  delete[] item;
		ItemsInBucket.clear();*/
	//cout << "Bucket deleted" << endl;
	}
	
	//sinartisi add to bucket_list 





