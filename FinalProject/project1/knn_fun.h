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
#include <list>
#include <math.h>
#include <time.h> 
#include <map>
#include <random>
#include <cmath>
#include <random>
#include "DataSet.h"

double E_knn(DataSet *set,std::string Q_line);
double C_knn(DataSet *set,std::string Q_line);
bool is_number(const std::string& s);
