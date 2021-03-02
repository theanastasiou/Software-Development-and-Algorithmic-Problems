#include <iostream>
#include <math.h>
#include "Lsh.h"

using namespace std;
string output_file;
float Radius;

LSH::LSH(int D,int k,int L,int n,int m){
	//cout<<"LSH Created! "<< endl;
	this->method=m;
	this->n=n;
	this->d=D;
	this->k=k;
	this->L=L;
	int te=0;
	te=n/8;
	//cout << "te" << te << endl;
	int tc=0;
	tc = pow(2,k);
	//cout << "TC" << tc << endl;
	if (method == 1){
		for(int i=0;i<L;i++){
			Hash_Euclidean *HE = new Hash_Euclidean(te,k,d);
			this->AddtoE(HE);
		}
	}
	else if (method == 2){
		for(int i=0;i<L;i++){
			Hash_Cosine *CO = new Hash_Cosine(tc,k,d);
			this->AddtoC(CO);
		}
	}

}

int	LSH:: return_d(){
	return d;
	}

list<Item*>& LSH::Q_Calc_Cosine(DataSet *set,vector<double> myCl)
{
	//cout << "Q_Calc_Cosine" << endl;
	vector <Hash_Cosine*> h_funn;
	h_funn = this->return_C();
	for( int l = 0; l < this->L; l++ ){
		list<Item*>& ItemsInBucket = h_funn[l]->Search_Cosine(myCl);
		//cout << "l" << l << " buck " << buck  << endl;
		return ItemsInBucket;
	}
				
	//cout<< "lines: "<<  lines <<endl;
}

list<Item*>&  LSH::Q_Calc_Euclidean(DataSet *set,vector<double> myCl){
	//pairnei san orisma to onoma tou query arxeiou
	cout << "Q_Calc_Euclidean "<< endl;
	vector <Hash_Euclidean*> h_funn; //epistrefei tus pinakes H_E
	h_funn = this->return_E();
	cout << "ok" << this->L << endl;
	for( int l = 0; l < this->L; l++ ){ //gia kathe pinaka
		list<Item*>& ItemsInBucket = h_funn[l]->Search_Euclidean(myCl); // kaleite i sinartisi Search_Euclidean 
	//	cout << "BUCKET" << bucket << endl;
		return ItemsInBucket;
		// p pernei ws orisma tin grammi (diladi to query antikeimeno ) to min item kai to min distance san reference
	}
						
}

void LSH:: Calc_Euclidean(DataSet* set){   //pairnei san orisma to dataset p fortosa proigumenos
	cout << "Calc_Euclidean" << endl;
	vector <Hash_Euclidean*> h_funn = this->return_E(); //pairnw olous tus hash_pinakes
	vector<int> it_data; 
	vector<Item*> it;
	vector<h*> hh;
	it = set->return_items(); //epistrefei ton vector me ta items 
	cout << "SET SIZE " << set->Return_size() << endl;
		for( int l = 0; l < this->L; l++ ){ //gia kathe pinaka
			for (int i=0; i< this->n; i++){ //gia kathe antikeimeno
				h_funn[l]->Euclidean_HF(it[i]); //kalei tin sinartisi Euclidean_HF pou tha ipologisei p anoiki kathe item
			}
		}
}

void LSH:: Calc_Cosine(DataSet* set){
	vector <Hash_Cosine*> h_funn = this->return_C();
	vector<int> it_data;
	vector<Item*> it;
	vector<h*> hh;
	it = set->return_items();
		for( int l = 0; l < this->L; l++ ){
			for (int i=0; i< this->n; i++){
				h_funn[l]->Cosine_HF(it[i]);
				//cout << " i: " << i << " p: " << p << endl;
				}
			}
}

vector<Hash_Euclidean*>&	LSH::return_E() {

	return E;
	}

vector<Hash_Cosine*>&	LSH::return_C() {
	return C; // 'v' is converted to r-value and return value is move constructed.
	}
void LSH::AddtoE(Hash_Euclidean *He){
		E.push_back(He);
	}

void LSH::AddtoC(Hash_Cosine *Co){
		C.push_back(Co);
	}

LSH::~LSH(){
	
	if (this->method == 1){
		//Memory+=sizeof(E);
		for(int i=0;i<L;i++){
		//	Memory+=sizeof(E[i]);
			delete E[i];}
		E.erase (E.begin(),E.end());
	}
	else if (this->method == 2){
		//Memory+=sizeof(C);
		for(int i=0;i<L;i++){
		//	Memory+=sizeof(C);
			delete C[i];}
		C.erase (C.begin(),C.end());
	}
	
	//cout<< "Delete LSH"<<endl; 
	}




