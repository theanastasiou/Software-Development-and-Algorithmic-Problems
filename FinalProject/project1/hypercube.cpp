#include "HyperCube.h"

using namespace std;

string output_file;
int M;
double Aproximation;

int main(int argc, char **argv)
{
    srand (time(NULL));
	string ch="";
    int v=0;
    do{
	Aproximation=0;
	int d=0;
	int k;
	M=0;
	int probes=0;
	string input_file ;
	if (v>0)
		input_file=ch;
	else
		input_file= argv[2];
		
	//cout << input_file << endl;
	string Q_file = argv[4] ;
	k = atoi(argv[6]);  //hash functions per table		
	M = atoi(argv[8]); //items
	probes = atoi(argv[10]); //probes
	output_file = argv[12] ;


	DataSet* set= new DataSet();
	string line;
    ifstream out(input_file);
    int i=0;
    cout << "HyperCube" << endl;
	while ( getline( out, line )){
		d=0;
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
				//cout << "--------" << line << endl;
				token = line.substr(0, pos);
				int l= stod(token,&sz);;
				p->AddData(l);
				line.erase(0, pos + delimiter.length());
				d++;
			}
			set->AddData_toDataSet(p);
		
	}
	out.close();
	ofstream ofile(output_file, ios_base::trunc);
	int n=set->Return_size();
	//cout << "N: " << n << endl;
	//dimiourgia hypercube me orismata to 
	
   // double param, result;
   // result = log2(k);
	HyperCube *hyper = new HyperCube(k,M,probes,n,d);
	//cout << "N: " << n << endl;
	hyper->Calc_H(set);
	hyper->Q_Calc_Euclidean(set,Q_file);
	Memory+=sizeof(hyper);
	Memory+=sizeof(set);
	delete hyper;
	delete set;
	
	cout << "Memory Used: " << Memory << endl;
	cout << "Approximation: " << Aproximation << endl;
	v++;
	cout<<"Insert new input file or press n to exit.";
	cin>>ch;
   
	}while(ch != "n");
}
