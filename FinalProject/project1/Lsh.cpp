#include <iostream>
#include "Lsh.h"
#include "Hash_Euclidean.h"
#include <math.h>

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

void LSH::Q_Calc_Cosine(DataSet *set,string Q_file){
	//cout << "Q_Calc_Cosine" << endl;
	vector <Hash_Cosine*> h_funn;
	h_funn = this->return_C();
	string Q_line;
    ifstream Q_out(Q_file);
    int lines=0;
    int first=0;
	while ( getline( Q_out, Q_line )){
		istringstream ss( Q_line );
			string::size_type sz;
			size_t pos = 0;
			string token ;
			string delimiter = " ";
			if (first==0){
				if((pos = Q_line.find(delimiter)) != string::npos) {
					token = Q_line.substr(0, pos);
					//cout << "== " << token << endl;
					if (token != "Radius")
						Radius=0;
					else
					{
						Q_line.erase(0, pos + delimiter.length());
						pos=0;
						string token1 ;
						if((pos = Q_line.find(delimiter)) != string::npos) {
							token1 = Q_line.substr(0, pos);
						//	cout << "== =  " << token << endl;
							Radius  = stof(token1);
							//cout<< Radius << endl;
							Q_line.erase(0, pos + delimiter.length());
						}
					}
					Q_line.erase(0, pos + delimiter.length());
				}
				first=1;
				continue;
			}
		if(first==1){
			//cout << Q_line << endl;
			//cout<< Radius << endl;
			fstream myfile;
			myfile.open (output_file,  fstream::out | fstream::app);
			string min_item=""; //arxikopoiei to onoma tou min item
			double min_distance = -1; //arxikopoiei to min distance
			myfile << "Query: Item" << lines++ << "\n";
			myfile << "R-near Neighbors \n";
			myfile.close();
			clock_t CStart = clock();
			for( int l = 0; l < this->L; l++ ){
					h_funn[l]->Search_Cosine(Q_line,min_item,min_distance);
					//cout << "l" << l << " buck " << buck  << endl;
				}
			
			
			myfile.open (output_file, fstream::out | fstream::app);
			myfile << "Nearest Neighbor: " << min_item <<"\n";
			myfile << "distanceLSH: "<< min_distance <<"\n";
			//cout << "//////// "<< num++ << " /////////MINIMUM : " << min_distance << ": Item : " << min_item <<endl;
			myfile.close();
			double time_LSH = (double)(clock() - CStart)/CLOCKS_PER_SEC ;
			clock_t nnStart = clock();
			double minTrue = C_knn(set,Q_line);	
			double time_T = (double)(clock() - nnStart)/CLOCKS_PER_SEC ;
			myfile.open (output_file, fstream::out | fstream::app);
			
			double Aproximation_New =  min_distance / minTrue ;
			if(Aproximation < Aproximation_New)
				Aproximation=Aproximation_New;
			myfile << "tLSH: " << time_LSH <<"\n";
			myfile << "tTrue: " << time_T <<"\n";
			myfile << " ----------------- \n";
			
			myfile.close();
		

		}//cout<< "lines: "<<  lin++ <<endl;
	}
	//cout<< "lines: "<<  lines <<endl;
}

void LSH::Q_Calc_Euclidean(DataSet *set,string Q_file){
	//pairnei san orisma to onoma tou query arxeiou
	//cout << " Q_Calc_Euclidean "<< endl;
		vector <Hash_Euclidean*> h_funn; //epistrefei tus pinakes H_E
		h_funn = this->return_E();
		string Q_line;
		ifstream Q_out(Q_file);
		int lines=0;
		int first=0;
		
		while ( getline( Q_out, Q_line )){ //pairnei grammi grammi tou query arxeiou
			istringstream ss( Q_line );
			string::size_type sz;
			size_t pos = 0;
			string token ;
			string delimiter = " ";
			if (first==0){
				if((pos = Q_line.find(delimiter)) != string::npos) {
					token = Q_line.substr(0, pos);
					//cout << "== " << token << endl;
					if (token != "Radius")
						Radius=0;
					else
					{
						Q_line.erase(0, pos + delimiter.length());
						pos=0;
						string token1 ;
						if((pos = Q_line.find(delimiter)) != string::npos) {
							token1 = Q_line.substr(0, pos);
							//cout << "== =  " << token << endl;
							if(is_number(token1)!=0)
								Radius  = stoi(token1);
						
						}
					}
					Q_line.erase(0, pos + delimiter.length());
				}
				first=1;
			}
			else if( first==1){
				//cout<< Radius << endl;
				//lines++; //metritis grammwn
				fstream myfile;
				myfile.open (output_file,  fstream::out | fstream::app);
				string min_item=""; //arxikopoiei to onoma tou min item
				double min_distance = -1; //arxikopoiei to min distance
				myfile << "Query: Item" << lines++ << "\n";
				myfile << "R-near Neighbors \n";
				myfile.close();
				clock_t EStart = clock();	
				for( int l = 0; l < this->L; l++ ){ //gia kathe pinaka
					h_funn[l]->Search_Euclidean(Q_line,min_item,min_distance); // kaleite i sinartisi Search_Euclidean 
					// p pernei ws orisma tin grammi (diladi to query antikeimeno ) to min item kai to min distance san reference
				}
					
			
				myfile.open (output_file, fstream::out | fstream::app);
				myfile << "Nearest Neighbor: " << min_item << "\n";
				myfile << "distanceLSH: "<< min_distance <<"\n";
				//cout << "//////// "<< num++ << " /////////MINIMUM : " << min_distance << ": Item : " << min_item <<endl;
				
				myfile.close();
				double time_LSH = (double)(clock() - EStart)/CLOCKS_PER_SEC ;
				clock_t nnStart = clock();
				double minTrue = E_knn(set,Q_line);	
				double time_T = (double)(clock() - nnStart)/CLOCKS_PER_SEC ;
				double Aproximation_New =  min_distance / minTrue ;
				if(Aproximation < Aproximation_New)
					Aproximation=Aproximation_New;
				myfile.open (output_file, fstream::out | fstream::app);
				myfile << "tLSH: " << time_LSH <<"\n";
				myfile << "tTrue: " << time_T <<"\n";
				myfile << " ----------------- \n";
				myfile.close();
		}
	}
		
}

void LSH:: Calc_Euclidean(DataSet* set){   //pairnei san orisma to dataset p fortosa proigumenos
	//cout << "Calc_Euclidean" << endl;
	vector <Hash_Euclidean*> h_funn = this->return_E(); //pairnw olous tus hash_pinakes
	vector<int> it_data; 
	vector<Item*> it;
	vector<h*> hh;
	it = set->return_items(); //epistrefei ton vector me ta items 
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
		Memory+=sizeof(E);
		for(int i=0;i<L;i++){
			Memory+=sizeof(E[i]);
			delete E[i];}
		E.erase (E.begin(),E.end());
	}
	else if (this->method == 2){
		Memory+=sizeof(C);
		for(int i=0;i<L;i++){
			Memory+=sizeof(C);
			delete C[i];}
		C.erase (C.begin(),C.end());
	}
	
	//cout<< "Delete LSH"<<endl; 
	}




