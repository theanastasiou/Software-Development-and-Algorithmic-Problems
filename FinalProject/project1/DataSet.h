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

extern std::string output_file;
extern float Radius;
extern long long int Memory;
extern double Aproximation;

class Item{
	private:
	std::string item_id;
	std::vector<int> item_data;
	
	public:
	Item(std::string name);
		
	~Item();
	
	void AddData(int num);
	void DisplayVectorContents();
	std::string return_item_id();
	std::vector<int>& return_item_data();
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


