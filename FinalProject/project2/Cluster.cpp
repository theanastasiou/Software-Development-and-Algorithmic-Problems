#include "Cluster.h"
using namespace std;

Cluster::Cluster(int id){
		this->id=id;
		//cout<<"A Cluster Created! "<< endl;
}
		
Cluster::~Cluster(){
	//Memory+=sizeof(items_in_cluster);
	for( unsigned int i = 0; i < items_in_cluster.size(); i++ )
		{
			//Memory+=sizeof(items_in_cluster[i]);
			delete items_in_cluster[i];
		}
	items_in_cluster.erase (items_in_cluster.begin(),items_in_cluster.end());	
	
	//cout<<"A DataSet just Deleted"<< endl;
	}
	
void Cluster::AddImag_toCluster(vector<double> imag_cluster){
	i_cluster=imag_cluster;
}
	
void Cluster::AddData_toCluster(Item *item){
	items_in_cluster.push_back(item);
	}

int Cluster::Return_size(){
	return items_in_cluster.size();
	}


int Cluster::return_cluster_id(){
	return id;
	}
	
vector<Item*>& Cluster::return_items(){
	return items_in_cluster;
	}
		
vector<double> Cluster::return_i_cluster(){
	return i_cluster;
}

void  Cluster::DisplayVectorContents_Cluster(){
	for( unsigned int i = 0; i < items_in_cluster.size(); i++)
		items_in_cluster[i]->DisplayVectorContents();
	}
