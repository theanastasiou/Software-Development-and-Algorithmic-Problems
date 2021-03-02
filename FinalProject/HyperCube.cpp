#include <iostream>
#include "HyperCube.h"
#include <limits.h>
#include <unistd.h>

#define W 4

using namespace std;

HyperCube::HyperCube(int k,int M,int probes, int n,int d,int method){
	this->n=n; //items
	this->M=M; //posa stoixeia tha psaxnw
	this->k=k; // d' = logn
	this->d=d; // diastasis item
	this->probes=probes; //poses korifes tha psaxnw
	this->T = pow(2,k);
	this->method=method; 
	
	for(int i = 0; i < k; ++i){
			//rand gia hv+ht twn h + dimiourgia h1...hk (tha kalw mia sinartisi)
			
	if (method == 1){
		vector<float> v;
		for(int l=0;l<d;l++){
			float hv = this->Return_v();
			v.push_back(hv);
		}
		int ti=this->Return_t();
		
		this->AddFun(new h(v,ti));
		unordered_map<int,int> hbitmap;
		bitmap.push_back(hbitmap);
	}
	else if (method == 2){
		vector<double> v;
		for(int l=0;l<d;l++){
			float hv = this->Return_v();
			v.push_back(hv);
		}		
		this->AddFunC(new h_Cosine(v));
		
	}

//dimiourgia vector Buckets me Bucket analoga me to L gia Euclidean (tha kalw mia sinartisi)
	for(int q = 0; q < this->T ; ++q){
		this->AddBucket(new Bucket(q));
	}
	
}
}

	//kanoniki katanomi gia v
float  HyperCube::Return_v(){
    random_device rd;
    mt19937 gen(rd());
	float sample;
	normal_distribution<float> d(0.0, 1.0);  //mean = 0.0 variance =0.1
	sample = d(gen);
	//cout  << sample << endl;
	//ARNITIKES TIMES ELEGXOS + DIAXIRISI
	return sample;
	}

vector<Bucket*>&  HyperCube::return_Buckets(){
	return Buckets;
	}
	
vector<char*>&  HyperCube::return_MyNeighbors_char(){
	return MyNeighbors_char;
	}

void HyperCube::AddNeighbor_char(char* str){
	MyNeighbors_char.push_back(str);
	}

void HyperCube::AddBucket(Bucket* bucket){
	Buckets.push_back(bucket);
	}
	
vector<h*>  HyperCube::return_h(){
	return h_fun;
	}

vector<h_Cosine*>  HyperCube::return_hC(){
	return hC_fun;
	}	


void HyperCube::AddFun(h* fun){
	h_fun.push_back(fun);
	}

void HyperCube::AddFunC(h_Cosine* fun){
	hC_fun.push_back(fun);
	}

float HyperCube::Return_t(){
	random_device rd;
    mt19937 gen(rd());
    float sample;
    uniform_real_distribution<> dis(0,W);
	sample= dis(gen) ;
	return sample;

	}

void HyperCube:: Calc_H(DataSet* set){   //pairnei san orisma to dataset p fortosa proigumenos
	//cout << "Calc_Euclidean" << endl;
	vector<int> it_data; 
	vector<Item*> it;
	vector<h*> hh;
	it = set->return_items(); //epistrefei ton vector me ta items 
		for (int i=0; i< this->n; i++){ //gia kathe antikeimeno
			if(this->method==1)
				Hyper_HF(it[i]); //kalei tin sinartisi Euclidean_HF pou tha ipologisei p anoiki kathe item //gia euklidis
			else
			if(this->method==2)
				Hyper_HF_C(it[i]);
		}
}



vector<unordered_map<int,int>>& HyperCube::get_bitmap(){
	return bitmap;
	}

void HyperCube::Hyper_HF(Item* it){
	vector <h*> hh;
	vector <float> hhv;
	vector<double> item_d;
	vector<unordered_map<int,int>>& bitmap= this->get_bitmap();
	double p=0;
	long long int bucket=0;
	//cout << it->return_item_id() << endl;
	//cout << "______" << endl;
	for( int l = 0; l <this-> k ; l++ ){
		hh = this->return_h(); // mou epistrefei tis h sinartiseis
		hhv = hh[l]->get_hv(); // pernw ton vector pinaka me ta hv tis 1is sinartisis	
		int h=0;
		item_d = it->return_item_data(); // pernw ta data tou item
		for( int g = 0; g < this->d; g++){
			p =  p + (hhv[g] * item_d[h++]); // ipologismos essoterikou ginomenou
			}
		float hht = hh[l]->get_ht();  // pernw to ht tis h mou
		double h_p = floor( (p+hht) / W ); // ipologizw to h(p)
		//cout << h_p <<  " for " << l  << endl;
		int ra;
		unordered_map<int,int>::iterator it=bitmap[l].find(h_p);
		//check an iparxei o arithmos stin domi alliws cointos
		if(it == bitmap[l].end()){
			//cout << "new" <<endl;
			ra = rand() % 2;
			bitmap[l][h_p] = ra;
		}
		else
		{
			//cout << "found" << endl;
			ra = it->second;
			}
		bucket = bucket + (ra * pow(2,this->k-1-l));	
		//cout << "rA: " << ra << endl;
		
	}
	//cout << this->T << endl;
	//cout << "bucket : " << bucket << endl;
	vector < Bucket* > Buckets = this->return_Buckets();
    Buckets[bucket]->AddtoBucket(it); 	//add to bucket
	}

void HyperCube::Hyper_HF_C(Item* item){
	vector <h_Cosine*> hh;
	vector <double> hhv;
	vector<double> item_d;
	int bucket_bf=0;
	for( int l = 0; l <this-> k ; l++ ){
		double p=0;
		hh = this->return_hC(); // mou epistrefei tis h sinartiseis 
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
	//cout << "bucket_bf" << bucket_bf << endl;
	//add to bucket
	Buckets[bucket_bf]->AddtoBucket(item);
	//Buckets[bucket_bf]->ShowBucketItems();
	}

void HyperCube::Q_Calc_Cosine(DataSet *set,string Q_file){
	//cout << "Q_Calc_Cosine" << endl;
	
			//  Search_Cosine(Q_line,min_item,min_distance);
					//cout << "l" << l << " buck " << buck  << endl;
//cout<< "lines: "<<  lin++ <<endl;
	//cout<< "lines: "<<  lines <<endl;
}


void HyperCube::Q_Calc_Euclidean(DataSet *set,string Q_file){
		//pairnei san orisma to onoma tou query arxeiou

				//	Cube_Search_Euclidean(Q_line,min_item,min_distance); // kaleite i sinartisi Search_Euclidean 
}

list<Item*> HyperCube::Cube_Search_Euclidean(vector<double> mc){
	//cout << "Search_Euclidean" << endl;
	vector <h*> hh;
	list<Item*> ItemsInBuckets;
	vector <float> hhv;
	vector<double> item_d;
	vector <float> Ri;
	vector<unordered_map<int,int>>& bitmap= this->get_bitmap();
	double p=0;
	long long int bucket=0;
	string name="item_idSQ";
	Item *itt = new Item(name);
	for( int l = 0; l <this-> k ; l++ ){
		hh = this->return_h(); // mou epistrefei tis h sinartiseis
		hhv = hh[l]->get_hv(); // pernw ton vector pinaka me ta hv tis 1is sinartisis
		int h=0;
		string::size_type sz;
		string token;
		for(unsigned int s=0;s<mc.size();s++){
			
			itt->AddData(mc[s]);
			p =  p + (hhv[h++] * mc[s]); //ipologismos essoterikou ginomenu
		}
		//cout << "PPP" << p << endl;
		float hht = hh[l]->get_ht();  // pernw to ht tis h mou
		double h_p = floor( (p+hht) / W ); // ipologizw to h(p)
		int ra;
		unordered_map<int,int>::iterator it=bitmap[l].find(h_p);
		//check an iparxei o arithmos stin domi alliws cointos
		if(it == bitmap[l].end()){
			//cout << "new" <<endl;
			ra = rand() % 2;
			bitmap[l][h_p] = ra;
		}
		else
		{
			//cout << "found" << endl;
			ra = it->second;
			}
		bucket = bucket + (ra * pow(2,this->k-1-l));	
		
			
	}
	//cout << "bucket: " << bucket << endl;
	unsigned long long n_bits=0;
	long long int b = convertDecimalToBinary(bucket,n_bits);
	int pro = this->probes;
	unsigned long long int clas=0;
	//cout << "n_bits" << n_bits << endl;
	//cout << "Probes" << pro << endl;
	
    do{
		//cout << "|||" << pro << "|||" << endl;
		pro-=Combinations(n_bits,n_bits);
	//	cout << "PRO" << endl;
		clas++;
	}while(pro>0);
	//cout << "class"<< clas <<endl;
	char *st = lltoa(b,10);
	string stt(st);
	 // len of string
	size_t len = stt.length();
	if( (int)len < k){
		stt.insert(0,k-len,'0');
		}
	
	vector< Bucket* > Buckets = this->return_Buckets(); //epistrofi ton Bucket tou sigkekrimenu pinak
	list<Item*>& ItemsInBucket = Buckets[bucket]->return_Items(); 
	list<Item*>::iterator iter;
	for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
	{	
		Item* it=*iter;
		ItemsInBuckets.push_back(it);
	}
	cout << ItemsInBucket.size() << endl;
	cout << "must= " << ItemsInBuckets.size() << endl;
	//ItemsInBuckets.push_back(ItemsInBucket);
//	cout << "BUCKET: "<< bucket << " binary: " << stt  << " numberofbits " << n_bits << endl;
	
	std::vector <string> MyNeighbors_char;
	for (size_t i = 0 ; i <= clas ; ++i) {
    	//printf("Computing for distance %d\n", (int)i);
        this->find_neigh(stt, k-1, i , MyNeighbors_char);
	}
	//printf("----------------\n");
	//cout << "Size" << MyNeighbors_char.size() << endl;
	int Max=0;
	//cout << "--  MMM ------ " << M << endl;
	for( int jj=0; jj < this->probes;  jj++){
		if(Max>=M)
			break;
		string::size_type sz;
		//cout<< MyNeighbors_char[jj] <<endl;
		int myneight = stoi( MyNeighbors_char[jj], &sz);
		//printf(" myneight %d\n", myneight);
		int myN = binaryToDecimal(myneight);
//		cout << "ID BUCKET TOU GEITONA" << myN << endl;
		list<Item*>& ItemsInBucketN = Buckets[myN]->return_Items(); 
		cout << "ITEMS IN MY NEIG:" << ItemsInBucketN.size() << endl;
		std::list<Item*>::iterator iterr;
		for(iterr=ItemsInBucketN.begin(); iterr != ItemsInBucketN.end() ; ++iterr) //me iterator diasxizo tin lista me ta items sto bucket mou
		{	
			Item* itt=*iterr;
			ItemsInBuckets.push_back(itt);
		}	
		cout << "ITEMS WITH MY NEI:"<< ItemsInBuckets.size() << endl;
		//ItemsInBuckets.push_back(ItemsInBucketN);
		//Cube_Calc_Euclidean_distance(myN,itt->return_item_data(),min_item,min_distance,Max);
		
	}
	cout << "ITEMS WITH MY NFFEI:"<< ItemsInBuckets.size() << endl;
	return ItemsInBuckets;
	delete itt;
	//cout << "SIIZE " << MyNeighbors_char.size() <<  endl;
	
	
	 //kaleite i sinartisi Calc_Euclidean_distance
	// pou pernei san orismata to bucket , to vector me to dianisma tou itt , min_item+min_distance -reference
//	cout << "----- DELETE ITEM --- " << endl;
}

// Function to convert binary to decimal 
int HyperCube::binaryToDecimal( int n) 
{ 
    int num = n; 
    int dec_value = 0; 
      
    // Initializing base value to 1, i.e 2^0 
    int base = 1; 
      
    int temp = num; 
    while (temp) 
    { 
        int last_digit = temp % 10; 
        temp = temp/10; 
          
        dec_value += last_digit*base; 
          
        base = base*2; 
    } 
      
    return dec_value; 
} 

void HyperCube::find_neigh(string str, int i, int changesLeft, vector<string>& MyNeighbors_char) {
	
	if (changesLeft == 0) {
		MyNeighbors_char.push_back(str); 
  		//cout << str << endl;
		return;
    }
    if (i < 0)
		return;

    /* flip current bit */
    str[i] = str[i] == '0' ? '1' : '0';
    find_neigh(str, i - 1, changesLeft - 1, MyNeighbors_char);
    /* or don't flip it (flip it again to undo) */
    str[i] = str[i] == '0' ? '1' : '0';
    find_neigh(str, i - 1, changesLeft, MyNeighbors_char);
    
    
}

//https://stackoverflow.com/questions/18858115/c-long-long-to-char-conversion-function-in-embedded-system
char* HyperCube::lltoa(long long int val, int base){

    static char buf[64] = {0};

    int i = 62;
    int sign = (val < 0);
    if(sign) val = -val;

    if(val == 0) return "0";

    for(; val && i ; --i, val /= base) {
        buf[i] = "0123456789abcdef"[val % base];
    }

    if(sign) {
        buf[i--] = '-';
    }
    return &buf[i+1];

}
//https://www.programiz.com/cpp-programming/examples/binary-decimal-convert
long long int HyperCube::convertDecimalToBinary(int n,unsigned long long int &n_bits)
{
    long long int binaryNumber = 0;
    int remainder, i = 1;

    while (n!=0)
    {
        remainder = n%2;
       // cout << "Step " << step++ << ": " << n << "/2, Remainder = " << remainder << ", Quotient = " << n/2 << endl;
		n_bits++;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}

//https://stackoverflow.com/questions/1838368/calculating-the-amount-of-combinations
unsigned long long int HyperCube::gcd(unsigned long long int x, unsigned long long int y)
{
    while (y != 0)
    {
        unsigned long long int t = x % y;
        x = y;
        y = t;
    }
    return x;
}

unsigned long long int HyperCube::Combinations(unsigned long long int n, unsigned long long int k)
{
    if (k > n)
        throw std::invalid_argument("invalid argument in choose");
    unsigned long long int r = 1;
    for (unsigned long long  int d = 1; d <= k; ++d, --n)
    {
        unsigned long long int g = gcd(r, d);
        r /= g;
        unsigned long long int t = n / (d / g);
        if (r > std::numeric_limits<unsigned long long int>::max() / t)
           throw std::overflow_error("overflow in choose");
        r *= t;
    }
    return r;
}

long long int HyperCube::modulus(long long int pre){
	long long int mod = pre - (floor((long double)pre/(long double)M)*M) ;
	//cout << "mod in modulus" << mod << endl;
	return mod;
	}
/*
void HyperCube::Cube_Calc_Euclidean_distance(int buck ,vector<double> x,string &min_item,double &min_distance,int &Max){
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
		if(Max<M){
			Max++;
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
			if (E_distance > Radius ) //radius // an einai megaliteri apo to radius continue allios to vazw sto range ton kontinoterwn
				continue;
			else{
				//cout << "/////////////////E_d" << E_distance << " : " <<  it->return_item_id() <<endl;
				//ofstream myfilee;
				//myfilee.open ("output");
				//cout << "--------------------- R :"<< Radius << endl;
				AddChecked(it);
				fstream myfile;
				myfile.open (output_file,  fstream::out | fstream::app);
				myfile <<  it->return_item_id() <<"\n";
				myfile.close();
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
		else{
			//cout << "STOPPED" << endl;
			break;
		}
	}
	
	}
*/
void  HyperCube::AddChecked(Item* item){
	Checked.push_back(item); 
}

double HyperCube::Euclidean_distance(vector<double> y,vector<double> x,string &min_item,double &min_distance){
	double E_d = 0;
	for( int l = 0; l < (int)y.size(); l++ ){
		E_d = E_d +  pow(y[l]-x[l],2);
	}
	double new_E_d = sqrt(E_d);
	return new_E_d;
	}
	
	
vector<Item*> HyperCube::return_Checked(){
	return Checked;
} 


HyperCube::~HyperCube(){
	if(this->method==1){
		for(int i=0;i<k;i++){
			delete h_fun[i];
			}
		h_fun.erase (h_fun.begin(),h_fun.end());
	}
	else if(this->method==2){
		for(int i=0;i<k;i++){
			delete hC_fun[i];
			}
		hC_fun.erase (hC_fun.begin(),hC_fun.end());
	}
		for(int i=0;i<this->T;i++){
			delete Buckets[i];
			}
		Buckets.erase (Buckets.begin(),Buckets.end());
	
		bitmap.erase (bitmap.begin(),bitmap.end());
		Checked.erase (Checked.begin(),Checked.end());
		hhv.erase(hhv.begin(),hhv.end());
		
	//cout<< "Delete LSH"<<endl;
	}


list<Item*> HyperCube::Search_Cosine(std::vector<double> mc){
	//cout << "Search_Cosine" << endl;
	//cout << "--line-- "<< line << endl;
	vector <h_Cosine*> hh;
	vector <double> hhv;
	list<Item*> ItemsInBuckets;
	vector<double> item_d;
	int bucket_bf=0;
	string name="item_idSQ";
	Item *itt = new Item(name);
	for( int l = 0; l <this->k ; l++ ){
		double p=0;
		hh = this->return_hC(); // mou epistrefei tis h sinartiseis 
		hhv = hh[l]->get_hv(); // pernw ton vector pinaka me ta hv tis 1is sinartisis
		int h=0;	

		for(unsigned int s=0;s<mc.size();s++){
			itt->AddData(mc[s]);
			//cout << "li: " << li << " hhv[h++]: " << hhv[h++] <<endl;
			p =  p + (hhv[h++] * mc[s]);
			//cout << "P : " << p << endl;
		}		
			//itt->DisplayVectorContents();
		
		//cout << "P" << p << endl;
		int bit=-1;
		if (p >= 0 )
			bit = 1;
		else
			bit = 0;
		bucket_bf = bucket_bf + (bit * pow(2,this->k-1-l));
		//cout << "k: " << k << " l : " << l << " bucket:" << bucket_bf << endl ;	
		
		
	}
	//cout << "------------"<< nuum++ <<"-------------"<<  bucket_bf << endl;
	//itt->DisplayVectorContents();
	unsigned long long n_bits=0;
	long long int b = convertDecimalToBinary(bucket_bf,n_bits);
	int pro = this->probes;
	unsigned long long int clas=0;
	//cout << "n_bits" << n_bits << endl;
	//cout << "Probes" << pro << endl;
    do{
		//cout << "|||" << pro << "|||" << endl;
		pro-=Combinations(n_bits,n_bits);
	//	cout << "PRO" << endl;
		clas++;
	}while(pro>0);
	//cout << "class"<< clas <<endl;
	char *st = lltoa(b,10);
	string stt(st);
	 // len of string
	size_t len = stt.length();
	if( (int)len < k){
		stt.insert(0,k-len,'0');
		}
	cout << "BUCKET: "<< bucket_bf << " binary: " << stt  << " numberofbits " << n_bits << endl;
	
	vector< Bucket* > Buckets = this->return_Buckets(); //epistrofi ton Bucket tou sigkekrimenu pinak
	list<Item*>& ItemsInBucket = Buckets[bucket_bf]->return_Items(); 
	list<Item*>::iterator iter;
	for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
	{	
		Item* it=*iter;
		ItemsInBuckets.push_back(it);
	}
	cout << ItemsInBucket.size() << endl;
	cout << "must= " << ItemsInBuckets.size() << endl;
	std::vector <string> MyNeighbors_char;
	for (size_t i = 0 ; i <= clas ; ++i) {
    	//printf("Computing for distance %d\n", (int)i);
        this->find_neigh(stt, k-1, i , MyNeighbors_char);
	}
	//printf("----------------\n");
	//cout << "Size" << MyNeighbors_char.size() << endl;
	int Max=0;
	//cout << "--  MMM ------ " << M << endl;
	for( int jj=0; jj < this->probes;  jj++){
		if(Max>=M)
			break;
		string::size_type sz;
		//cout<< MyNeighbors_char[jj] <<endl;
		int myneight = stoi( MyNeighbors_char[jj], &sz);
		//printf(" myneight %d\n", myneight);
		int myN = binaryToDecimal(myneight);
		list<Item*>& ItemsInBucketN = Buckets[myN]->return_Items(); 
		cout << "ITEMS IN MY NEIG:" << ItemsInBucketN.size() << endl;
		std::list<Item*>::iterator iterr;
		for(iterr=ItemsInBucketN.begin(); iterr != ItemsInBucketN.end() ; ++iterr) //me iterator diasxizo tin lista me ta items sto bucket mou
		{	
			Item* itt=*iterr;
			ItemsInBuckets.push_back(itt);
		}	
		cout << "ITEMS WITH MY NEI:"<< ItemsInBuckets.size() << endl;
		//cout << "ID BUCKET TOU GEITONA" << myN << endl;
		//Cube_Calc_Euclidean_distance(myN,itt->return_item_data(),min_item,min_distance,Max);
		//Calc_Cosine_distance(myN,itt->return_item_data(),min_item,min_distance,Max);

	}
	return ItemsInBuckets;
	delete itt;

	
}

/*
void HyperCube::Calc_Cosine_distance(int buck ,vector<double> x,string &min_item,double &min_distance,int &Max){
	//cout<< "Calc_Cosine_distance" <<endl;
	vector < Bucket* > Buckets;
	Buckets = this->return_Buckets();
	vector<Item*> items_Checked = return_Checked();
	vector<int> item_Data;
	//static int qq=0;
	//Buckets[buck]->ShowBucketItems();
	list<Item*> ItemsInBucket;
	ItemsInBucket = Buckets[buck]->return_Items();
	list<Item*>::iterator iter;
	double C_distance;
	//if (ItemsInBucket.size()>0)
	//cout << "BUCKET[" << buck << "]. has " << ItemsInBucket.size() << " items." << endl;
	for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter)
	{	
		if(Max<M){
			Max++;	
		Item* it=*iter;
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
		C_distance = this->Cosine_distance(item_Data,x,min_item,min_distance);
		//cout << "/////////////////C_d" << C_distance << endl;
		if (C_distance >=  Radius) //radius
			continue;
		else{
			//ADD IT STON VECTOR 
			AddChecked(it);
			//cout << "/////////////////C_d" << C_distance << " : " <<  it->return_item_id() <<endl;
			fstream myfile;
			myfile.open (output_file,  fstream::out | fstream::app);
			myfile <<  it->return_item_id() <<"\n";
			myfile.close();
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
		else{
			//cout << "STOPPED" << endl;
			break;
		}
	}
}

*/
double HyperCube::Cosine_distance(vector<double> y,vector<double> x,string &min_item,double &min_distance){
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
	float cos_ = 0.0;
	cos_ = (float)C_d / (float)(aaa*bbb);
	double new_C_d = 1 - cos_;
	//cout << " CD: " << new_C_d << endl;
	return new_C_d;
}
