#include "Lsh.h"
#include "knn_fun.h"

using namespace std;

double Aproximation;

int main(int argc, char **argv)
{
    srand (time(NULL));
	string ch="";
    int v=0;
    do{
	Memory=0;
	Aproximation=0;
	int d=0;
	int k;
	int L;
	string input_file ;
	if (v>0)
		input_file=ch;
	else
		input_file= argv[2] ;
		
	//cout << input_file << endl;
	string Q_file = argv[4] ;
	if (strcmp(argv[6], "int") == 0)
		k=4;
	else
		k = atoi(argv[6]);  //hash functions per table
		
	if(strcmp(argv[8],"int") == 0)
		L=5;
	else
		L = atoi(argv[8]); //hashtables
		
	output_file = argv[10] ;


	DataSet* set= new DataSet();
	string line;
    ifstream out(input_file);
    int i=0;
    int first=0;
    int method=-1;
	while ( getline( out, line )){
		d=0;
		if(first==0)
		{
			//cout << "OK"<<endl;
			istringstream ss( line );
			size_t pos = 0;
			string token ;
			string delimiter = " ";
			
			if((pos = line.find(delimiter)) != string::npos) {
				token = line.substr(0, pos);
				
				if (token == "euclidean")
					method = 1;
				else if (token == "cosine")
					method = 2;
				else method = 1;
				}
				//cout<< method << endl;
				first=1;
			}
		else if( first==1){
			string id;
			istringstream ss( line );
			string name="item" + to_string(i++);
			Item *p = new Item(name);
			d=0;
			string::size_type sz;
			size_t pos = 0;
			string token;
			string delimiter = " ";
			while ((pos = line.find(delimiter)) != string::npos) {
				token = line.substr(0, pos);
				int l= stod(token,&sz);;
				p->AddData(l);
				line.erase(0, pos + delimiter.length());
				d++;
			}
			set->AddData_toDataSet(p);
		}
	}
	out.close();
	Memory+=sizeof(set);
	ofstream ofile(output_file, ios_base::trunc);
	int n=set->Return_size();
	if (method == 1){
		LSH *lsh = new LSH(d,k,L,n,method);
		lsh->Calc_Euclidean(set);
		lsh->Q_Calc_Euclidean(set,Q_file);
		
		delete lsh;
		}
	
	if(method == 2){
		LSH *lsh = new LSH(d,k,L,n,method);
		lsh->Calc_Cosine(set);
		lsh->Q_Calc_Cosine(set,Q_file);
		
		delete lsh;
	}
	
	delete set;
	cout <<  "Memory Used: " <<  Memory << endl;
	cout << "Aproximation : " << Aproximation << endl;
	v++;
	cout<<"Insert new input file or press n to exit.";
	cin>>ch;
   
	}while(ch != "n");
}
