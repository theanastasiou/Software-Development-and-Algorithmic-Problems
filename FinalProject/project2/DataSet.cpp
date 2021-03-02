#include "DataSet.h"
using namespace std;

Item::Item(string name){
		item_id=name;
		//cout<<"An item Created! "<< endl;
		this->assigned=0;
		this->rev=-1;
		this->cluster_id=0;
		this->distance=0.0;
}
		
Item::~Item(){
		item_data.erase(item_data.begin(),item_data.end());
		//cout<<"An Item just Deleted"<< endl;
	}
	
void Item::AddData(double num){
	   // cout << "......." << endl;
		item_data.push_back(num);
}

vector<double>& Item::return_item_data(){
	return item_data;
	}
	

string Item::return_item_id(){
	return item_id;
	}

int Item::return_assigned(){
	return assigned;
	}

double Item::return_distance(){
	return distance;
	}
	
int Item::return_rev(){
	return rev;
	}
int Item::return_cluster_id(){
	return cluster_id;
	}
void Item::set_assigned(int assigned){
	this->assigned=assigned;
}
void Item::set_rev(int rev){
	this->rev=rev;
}
void Item::set_cluster_id(int id){
	this->cluster_id=id;
}

void Item::set_distance(double distance){
	this->distance=distance;
}
void Item::set_cluster_vector(vector<double> cv){
	this->cluster_vector=cv;
}
vector<double> Item::return_cluster_vector(){
	return cluster_vector;
	}
		
void Item::DisplayVectorContents(){
	cout << "Item_data size: " << item_data.size() << endl;
	cout << "Name" << item_id  << endl;
	
	for( unsigned int i = 0; i < item_data.size(); i++ )
	{
		
		cout << "Element[" << i << "] = " << item_data[i] << endl;
	}
	cout << endl;
}




DataSet::DataSet(){
	//cout<<"A DataSet Created! "<< endl;	
	}
	
void DataSet::AddData_toDataSet(Item *item){
	Items.push_back(item);
	}

int DataSet::Return_size(){
	return Items.size();
	}
	
vector<Item*>& DataSet::return_items(){
	return Items;
	}
		
void  DataSet::DisplayVectorContents_DataSet(){
	for( unsigned int i = 0; i < Items.size(); i++)
		Items[i]->DisplayVectorContents();
	}
	


DataSet::~DataSet(){
	//Memory+=sizeof(Items);
	for( unsigned int i = 0; i < Items.size(); i++ )
		{
			//Memory+=sizeof(Items[i]);
			delete Items[i];
		}
	Items.erase (Items.begin(),Items.end());	
	
	//cout<<"A DataSet just Deleted"<< endl;
	}
	

