#include "DataSet.h"
using namespace std;

long long int Memory;


Item::Item(string name){
		item_id=name;
		//cout<<"An item Created! "<< endl;
}
		
Item::~Item(){
		item_data.erase (item_data.begin(),item_data.end());
		//cout<<"An Item just Deleted"<< endl;
	}
	
void Item::AddData(int num){
	   // cout << "......." << endl;
		item_data.push_back(num);
}

vector<int>& Item::return_item_data(){
	return item_data;
	}
	

string Item::return_item_id(){
	return item_id;
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
	Memory+=sizeof(Items);
	for( unsigned int i = 0; i < Items.size(); i++ )
		{
			Memory+=sizeof(Items[i]);
			delete Items[i];
		}
	Items.erase (Items.begin(),Items.end());	
	
	//cout<<"A DataSet just Deleted"<< endl;
	}
	

