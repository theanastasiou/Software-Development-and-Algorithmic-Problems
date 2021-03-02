#include "Combinations.h"
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char **argv)
{
	string input_file ;
	//="twitter_dataset_small.csv";
	string output_file;
	//="output";
	string configuration_file ;
	//= "configuration_file";
	int metric;
	string ch="";
    srand(time(NULL));
	int v=0;
	int k=0;
	int h=0;
	int L=0;
	int Comb=0;
	int M=0;
	int probes=0;
	int wtd=0;
	if(argv[9]==NULL)
		wtd=1;
	else if(strcmp(argv[9],"-complete") == 0)
		wtd=2;
    do{
		DataSet* set= new DataSet();
		if (v>0)
			input_file=ch;
		if(v==0)
			input_file= argv[2] ;
		output_file = argv[6] ;
		configuration_file = argv[4];
		//cout << "input file : "<< input_file << endl;
		string line;
		ifstream out(input_file);
		ofstream ofile(output_file, ios_base::trunc);
		fstream myfile;
		myfile.open (output_file,  fstream::out | fstream::app);
		if(strcmp(argv[8],"cosine") == 0){
			metric=2;
			}
		else if(strcmp(argv[8],"euclidean") == 0){
			metric=1;
			}
		int d=0;
		myfile.close();
		cout << input_file << endl;
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
			set->AddData_toDataSet(p);
		}
		
		Configuration_file(configuration_file,k,h,L,Comb,M,probes); //diavazei to configuration file kai anathetei tis times pou prepei  
		cout << "COMBINATION NUMBER : " << Comb << endl;
		cout << "k:" << k << endl;
		cout << "h:" << h << endl;
		cout << "L:" << L << endl;
		cout << "M:" << M << endl;
		cout << "Probes:" << probes << endl;
		
		out.close();
		int n=set->Return_size();
		cout << "N" << n << endl;
		vector<Cluster*> Clusters;
		
		if(Comb==0){
			Combination_1_1_1(k,set, Clusters,d,metric,output_file,wtd);
			Combination_1_1_2(k,set, Clusters,d,metric,output_file,wtd);
			Combination_2_1_1(k,set, Clusters,d,metric,output_file,wtd);
			Combination_2_1_2(k,set, Clusters,d,metric,output_file,wtd);
			Combination_1_2_2(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
			Combination_1_2_1(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
			Combination_2_2_2(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
			Combination_2_2_1(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
			Combination_1_3_1(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
			Combination_2_3_1(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
			Combination_1_3_2(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
			Combination_2_3_2(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
		}
		if(Comb==1)
			Combination_1_1_1(k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==2)
			Combination_1_1_2(k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==3)
			Combination_2_1_1(k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==4)
			Combination_2_1_2(k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==5)
			Combination_1_2_1(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==6)
			Combination_1_2_2(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==7)
			Combination_2_2_1(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==8)
			Combination_2_2_2(h,L,n,k,set, Clusters,d,metric,output_file,wtd);
		if(Comb==9)
			Combination_1_3_1(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
		if(Comb==10)
			Combination_1_3_2(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
		if(Comb==11)
			Combination_2_3_1(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
		if(Comb==12)
			Combination_2_3_2(h,L,n,k,M,probes,set,Clusters,d,metric,output_file,wtd);
		
		cout<< Clusters.size() << endl;
		delete set;
		cout<<"Insert new input file or press n to exit.";
		cin>>ch;
		v++;
   
	}while(ch != "n");
}
