#include "Hash_Euclidean.h"
#define W 4
#define M 4294967291
#include <chrono>         // std::chrono::seconds
#include <thread>         // std::this_thread::sleep_for

using namespace std;


Hash_Euclidean::Hash_Euclidean(int t,int kk,int d){
	this->T=t;
	this->k=kk;
	this->d=d;
	//cout<<"A Hash_Euclidean Created! "<< endl;
	//cout <<"t : " <<this->T << endl;
	for(int i = 0; i < k; ++i){
			//rand gia hv+ht twn h + dimiourgia h1...hk (tha kalw mia sinartisi)
			vector <float> v;
			for(int l=0;l<d;l++){
				float hv = this->Return_v();
				v.push_back(hv);
			}
			int ti=this->Return_t();
			this->AddFun(new h(v,ti));
			//rand gia pinaka ri (kalw ReturnRi)
			int r=Return_Ri();
			this->AddtoRi(r);
	}
//dimiourgia vector Buckets me Bucket analoga me to L gia Euclidean (tha kalw mia sinartisi)
	for(int q = 0; q < this->T; ++q){
		this->AddBucket(new Bucket(q));
	}

}



void  Hash_Euclidean::AddChecked(Item* item){
	Checked.push_back(item); 
}

vector<Bucket*>&  Hash_Euclidean::return_Buckets(){
	return Buckets;
	}


Hash_Euclidean::~Hash_Euclidean(){
	//Memory+=sizeof(h_fun);
	for(int i=0;i<this->k;i++){
		//Memory+=sizeof(h_fun[i]);
		delete h_fun[i];
			}
	h_fun.erase (h_fun.begin(),h_fun.end());
	//Memory+=sizeof(Buckets);
	for(int i=0;i<this->T;i++)
	{
		//Memory+=sizeof(Buckets[i]);
		delete Buckets[i];
			}
	Buckets.erase (Buckets.begin(),Buckets.end());
	
	/*for(unsigned int i=0; i< Checked.size();i++)
			delete Checked[i];
	Checked.erase (Checked.begin(),Checked.end());
	*/
	//cout << Checked.size() <<endl;
//	Memory+=sizeof(Ri);
	Ri.erase (Ri.begin(),Ri.end());
//	Memory+=sizeof(g);
	g.erase (g.begin(),g.end());	
	//cout << "Delete Hash_Euclidean" <<endl;
	};

void Hash_Euclidean::AddtoRi(float r){
	Ri.push_back(r);
}

void  Hash_Euclidean::AddBucket(Bucket* bucket){
	Buckets.push_back(bucket);
	}
void Hash_Euclidean::AddFun(h* fun){
	h_fun.push_back(fun);
	}

void Hash_Euclidean::Addgi(double gi){
	g.push_back(gi);
	}

vector<h*>  Hash_Euclidean::return_h(){
	return h_fun;
	}

	//omoiomorfi katanomi apo 0-w (t)
float Hash_Euclidean::Return_t(){
	random_device rd;
    mt19937 gen(rd());
    float sample;
    uniform_real_distribution<> dis(0,W);
	sample= dis(gen) ;
	return sample;

	}


long long int Hash_Euclidean::modulus(long long int pre){
	long long int mod = pre - (floor((long double)pre/(long double)M)*M) ;
	//cout << "mod in modulus" << mod << endl;
	return mod;
	}

int  Hash_Euclidean::Return_Ri(){
	int r;
	/* generate secret number between +35 and -35: */
	r = (rand() % 71) - 35;
	return r;
	}

	//kanoniki katanomi gia v
float  Hash_Euclidean::Return_v(){
    random_device rd;
    mt19937 gen(rd());
	float sample;
	normal_distribution<float> d(0.0, 1.0);  //mean = 0.0 variance =0.1
	sample = d(gen);
	//cout  << sample << endl;
	//ARNITIKES TIMES ELEGXOS + DIAXIRISI
	return sample;
	}

list<Item*>& Hash_Euclidean::Search_Euclidean(vector<double> myCl){
	cout << "Search_Euclidean" << endl;
	vector <h*> hh;
	vector <float> hhv;
	vector<int> item_d;
	vector <float> Ri;
	double p=0;
	long long int  modM=0;
	Ri=this->Ri;
	string name="item_idSQ";
	Item *itt = new Item(name);
	for( int l = 0; l <this-> k ; l++ ){
		hh = this->return_h(); // mou epistrefei tis h sinartiseis
		hhv = hh[l]->get_hv(); // pernw ton vector pinaka me ta hv tis 1is sinartisis
		int h=0;
		for(unsigned int s=0;s<myCl.size();s++){
			itt->AddData(myCl[s]);
			p =  p + (hhv[h++] * myCl[s]); //ipologismos essoterikou ginomenu
		}
		//cout << "PPP" << p << endl;
		float hht = hh[l]->get_ht();  // pernw to ht tis h mou
		double h_p = floor( (p+hht) / W ); // ipologizw to h(p)
		long long int pre = h_p * Ri[l];
		modM = modM + this->modulus(pre); 	
	}
	long long int ModM = this->modulus(modM);
	int bucket = ModM % this->T;
	cout << " BUCKET : " << bucket << endl;
	vector < Bucket* > Buckets = this->return_Buckets(); //epistrofi ton Bucket tou sigkekrimenu pinak
	list<Item*>& ItemsInBucket = Buckets[bucket]->return_Items(); 
	return ItemsInBucket;
	//ASSIGN
	//Calc_Euclidean_distance(bucket,itt->return_item_data(),min_item,min_distance); //kaleite i sinartisi Calc_Euclidean_distance
	// pou pernei san orismata to bucket , to vector me to dianisma tou itt , min_item+min_distance -reference
//	cout << "----- DELETE ITEM --- " << endl;
	delete itt;
	}


//epistrefei ena arithmo (bucket) sto opoio tha anikei to item
void Hash_Euclidean::Euclidean_HF(Item* item){
	//cout << "Euclidean_HF" << endl;
	vector <h*> hh;
	vector <float> hhv;
	vector<double> item_d;
	vector <float> Ri;
	double p=0;
	long long int modM = 0 ;
	Ri=this->Ri;
	for( int l = 0; l <this-> k ; l++ ){
		hh = this->return_h(); // mou epistrefei tis h sinartiseis
		hhv = hh[l]->get_hv(); // pernw ton vector pinaka me ta hv tis 1is sinartisis
		int h=0;
		item_d = item->return_item_data(); // pernw ta data tou item
		for( int g = 0; g < this->d; g++){
			p =  p + (hhv[g] * item_d[h++]); // ipologismos essoterikou ginomeno
			}
		//	cout << "P: " << p << endl;
		float hht = hh[l]->get_ht();  // pernw to ht tis h mou
		//cout <<"hht"<< hht << endl;
		double h_p = floor( (p+hht) / W ); // ipologizw to h(p)
		//	cout << "hp"<< h_p << endl;
		//this_thread::sleep_for(chrono::seconds(3));
		///g ADD TO VECTOR to kathe item exei diaforetiko g afou exei diaforetiko essoteriko ginomeno.
		//this->Addgi(h_p);
		long long int pre = h_p * Ri[l];
		//cout <<"pre" << pre << endl;
		modM = modM + this->modulus(pre); 
		//cout <<"modM " << modM << endl ;
	}
	long long int ModM = this->modulus(modM);
	long long int bucket = ModM % this->T;
	//	cout << "-------------- bucket : " << bucket << endl;
	vector < Bucket* > Buckets = this->return_Buckets();
    Buckets[bucket]->AddtoBucket(item); 	//add to bucket
}
	
double Hash_Euclidean::Euclidean_distance(vector<double> y,vector<double> x,string &min_item,double &min_distance){
	double E_d = 0;
	for( int l = 0; l < (int)y.size(); l++ ){
		E_d = E_d +  pow(y[l]-x[l],2);
	}
	double new_E_d = sqrt(E_d);
	return new_E_d;
	}
	
vector<Item*> Hash_Euclidean::return_Checked(){
	return Checked;
} 

void Hash_Euclidean::Calc_Euclidean_distance(int buck ,vector<double> x,string &min_item,double &min_distance){
	//cout << "Calc_Euclidean_distance: " << buck  <<endl ;
	vector < Bucket* > Buckets = this->return_Buckets(); //epistrofi ton Bucket tou sigkekrimenu pinaka
	vector<double> item_Data;
	vector<Item*> items_Checked = return_Checked();
	list<Item*> ItemsInBucket;
	ItemsInBucket = Buckets[buck]->return_Items(); // epistrofi twn items p exei mesa to bucket me arithmo buck
	list<Item*>::iterator iter;
	double E_distance=0; 
	if (ItemsInBucket.size()>=0){	//otaan den iparxoun antikeimena sto bucket apla to prospernw
		//cout << "BUCKET[" << buck << "]. has " << ItemsInBucket.size() << " items." << endl;
	}
	else
		return ;
	for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
	{	
		Item* it=*iter;
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
		E_distance = this->Euclidean_distance(item_Data,x,min_item,min_distance); //ipologismos tis euklidias apostasis 
		if (E_distance > 0.3 ) //radius // an einai megaliteri apo to radius continue allios to vazw sto range ton kontinoterwn
			continue;
		else{
			cout << "/////////////////E_d" << E_distance << " : " <<  it->return_item_id() <<endl;
			//ofstream myfilee;
			//myfilee.open ("output");
			//cout << "--------------------- R :"<< Radius << endl;
			AddChecked(it);
			fstream myfile;
			//myfile.open (output_file,  fstream::out | fstream::app);
			//myfile <<  it->return_item_id() <<"\n";
			//myfile.close();
			if(min_distance==-1){ 
				min_distance = E_distance; //arxikopoiisi tou min
				min_item = it->return_item_id();
			}
			else if(min_distance>E_distance){ //tsekarw an einai o pio kontinos mou geitonas
				min_distance = E_distance;
				min_item = it->return_item_id();
			}
			
		}
		
	}
	
	}
