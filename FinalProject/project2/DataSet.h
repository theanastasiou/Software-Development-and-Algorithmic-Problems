#pragma once 
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <stdlib.h>   
#include <sstream>      // std::stringstream
#include <math.h>
#include <time.h>


class Item{
	private:
	std::string item_id;
	std::vector<double> item_data;
	int assigned;
	int rev;
	int cluster_id;
	std::vector<double> cluster_vector;
	double distance;

	
	public:
	Item(std::string name);
		
	~Item();
	int return_rev();
	int return_cluster_id();
	void set_assigned(int assigned);
	void set_rev(int rev);
	void set_distance(double distance);
	double return_distance();
	void set_cluster_id(int id);
	void set_cluster_vector(std::vector<double> cv);
	std::vector<double> return_cluster_vector();
	int return_assigned();
	void AddData(double num);
	void DisplayVectorContents();
	std::string return_item_id();
	std::vector<double>& return_item_data();
};



class DataSet{
	private:
	std::vector<Item*> Items;
	
	public:		
	DataSet();
	
	void AddData_toDataSet(Item *item);
	int Return_size();
	std::vector<Item*>&  return_items();
	
	void DisplayVectorContents_DataSet();
	~DataSet();
	
};


