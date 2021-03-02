#include "DataSet.h"

class Cluster{
	private:
    int id;
	std::vector<Item*> items_in_cluster;
	std::vector<double> i_cluster;

	public:
	Cluster(int id);
		
	~Cluster();
	void AddData_toCluster(Item *item);
	void AddImag_toCluster(std::vector<double> imag_cluster);
    int Return_size();
	std::vector<double> return_i_cluster();
    std::vector<Item*>& return_items();
	int return_cluster_id();	
    void  DisplayVectorContents_Cluster();
};
