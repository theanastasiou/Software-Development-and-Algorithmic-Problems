#include <sstream>
#include <iterator>
#include "knn_fun.h"

using namespace std;
	
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
	
double E_knn(DataSet *set,string Q_line){
	vector<Item*> it;

	
	it = set->return_items(); 
	//cout << "OKKKK" << endl;
	istringstream ss( Q_line );
	//cout << Q_line << endl;
	vector<int> it_dataQ ;
	//dimiourgia item
	string::size_type sz;
	size_t pos = 0;
	string token;
	string delimiter = " "; 
	while ((pos = Q_line.find(delimiter)) != string::npos) { //spazw tin grammi(dianisma) se int 
		token = Q_line.substr(0, pos);
		int li= stod(token,&sz);
		//cout << li << endl;
		it_dataQ.push_back(li);
		Q_line.erase(0, pos + delimiter.length());
		//q=it_dataQ.size();
		
	}
	double min_distance=-1;
	//cout << "---------------------------" << set->Return_size() << endl;
	for( int l = 0; l < set->Return_size(); l++ ){ //gia kathe simeio sto dataset
		vector<int> it_data  = it[l]->return_item_data();
		
		//cout << q << endl;
		//cout << "---------------------------" << endl;
		
		double E_d = -1;
		for( int q = 0; q < (int)it_dataQ.size(); q++ ){
			E_d = E_d +  pow(it_data[q]-it_dataQ[q],2);
		}
		double new_E_d = 0;
		new_E_d = sqrt(E_d);
			
		if (new_E_d > 300 ) //radius // an einai megaliteri apo to radius continue allios to vazw sto range ton kontinoterwn
			continue;
		else{
			if(min_distance==-1){
				min_distance = new_E_d;
			}
			else 
				if(min_distance > new_E_d){
					min_distance = new_E_d;
			}
		}
		// p pernei ws orisma tin grammi (diladi to query antikeimeno ) to min item kai to min distance san reference
			
		}
		
	//cout << "---------- " << min_distance << endl;
	fstream myfile;
	myfile.open (output_file,  fstream::out | fstream::app);
	myfile << "distanceTrue: " << min_distance << "\n";
	myfile.close();
	return min_distance;
	}



	
double C_knn(DataSet *set,string Q_line){
	vector<Item*> it;
	it = set->return_items(); 
	//cout << "OKKKK" << endl;
	//pairnei grammi grammi tou query arxeiou
		istringstream ss( Q_line );
		//cout << Q_line << endl;
		vector<int> it_dataQ ;
		string::size_type sz;
		size_t pos = 0;
		string token;
		string delimiter = " "; 
		while ((pos = Q_line.find(delimiter)) != string::npos) { //spazw tin grammi(dianisma) se int 
			token = Q_line.substr(0, pos);
			int li= stod(token,&sz);
			//cout << li << endl;
			it_dataQ.push_back(li);
			Q_line.erase(0, pos + delimiter.length());
			//q=it_dataQ.size();
			//acout << it_dataQ.size() << endl;
			
		}
		//cout << "---------------------------" << set->Return_size() << endl;
		double min_distance=-1;
		for( int l = 0; l < set->Return_size(); l++ ){ //gia kathe simeio sto dataset
			vector<int> it_data  = it[l]->return_item_data();
			
			//cout << it_dataQ.size() << endl;
			//cout << "---------------------------" << endl;
		
			long long int C_d = 0;
			long long int aa=0;
			long long int bb=0;
			for( int l = 0; l < (int)it_dataQ.size(); l++ ){
				C_d = C_d + (it_data[l]*it_dataQ[l]);
				aa = aa + pow(it_dataQ[l],2);
				bb = bb + pow(it_data[l],2);			
			}
			double aaa = sqrt(aa);
			double bbb = sqrt(bb);
			float cos_ = 0.0;
			cos_ = (float)C_d / (float)(aaa*bbb);
			double new_C_d = 1 - cos_;
			//cout << " CD: " << new_C_d << endl;
			if (new_C_d > 0.5) //radius // an einai megaliteri apo to radius continue allios to vazw sto range ton kontinoterwn
				continue;
			else{
				if(min_distance==-1){
					min_distance = new_C_d;
				}
				else 
					if(min_distance > new_C_d){
						min_distance = new_C_d;
				}
			}
			// p pernei ws orisma tin grammi (diladi to query antikeimeno ) to min item kai to min distance san reference
		}
	//cout << "---------- " << min_distance << endl;
	fstream myfile;
	myfile.open (output_file,  fstream::out | fstream::app);
	myfile << "distanceTrue: " << min_distance << "\n";
	myfile.close();
	return min_distance;
}


