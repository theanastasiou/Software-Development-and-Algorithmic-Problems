#include "notfun.h"
#include <algorithm>
#include <random>
#include <cmath>  
#include <cfloat>
#include <limits>

using namespace std;

void Configuration_file(string file_name,int &k,int &h,int &L,int &Comb,int &M,int &probes){
    string line;
    ifstream out(file_name);
	int fl=0;
	while ( getline( out, line )){
		string id;
		istringstream ss( line );
		size_t pos = 0;
		string token;
		string delimiter = " ";
		int fir=0;
		string::size_type sz;
		fl++;
		while ((pos = line.find(delimiter)) != string::npos) {
			
			if(fir==0){
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				fir=1;
			}
            if(fir==1){
				token = line.substr(0, pos);
			 	//cout << token << endl;
				if(fl==1){
					k = stoi(token,&sz);
				}
				if(fl==2){
					if(token == "<int>")
						h=4;
					else
						h = stoi(token,&sz);
				}
				if(fl==3){
					if(token == "<int>")
						L=5;
					else
						L = stoi(token,&sz);
				}
				if(fl==4){
					if(token == "<int>")
						Comb = 0;
					else
						Comb = stoi(token,&sz);
				}
				if(fl==5){
					if(token == "<int>")
						M = 10;
					else
						M = stoi(token,&sz);
				}
				if(fl==6){
					if(token == "<int>")
						probes = 2;
					else
						probes = stoi(token,&sz);
				}

				line.erase(0, pos + delimiter.length());	
				continue;
			}
			
        }

    }
}


void Random_Selection(int k,DataSet* set,vector<Cluster*>& Clusters){
	int n=set->Return_size();
 	vector<Item*> It = set->return_items();
	vector<int> Uniq;
	for (int i=0;i<k;i++){
		/* generate secret number between +35 and -35: */
		int r = rand() % (n-1);		
		//cout <<"r: " << r << endl;
		vector<int>::iterator it;
		it = find (Uniq.begin(), Uniq.end(), r);
		while (it != Uniq.end()){
			r = rand() % (n-1);
			it = find (Uniq.begin(), Uniq.end(), r);
		}
		Uniq.push_back(r);
		string idd = It[r]->return_item_id();
		Cluster *clu  = new Cluster(r+1);
		clu->AddImag_toCluster(It[r]->return_item_data());
		Clusters.push_back(clu);
		
	//	cout << "random cluster :" << idd << endl;
	
	}
	
}
void Lloyds_Assignment(DataSet* set,vector<Cluster*>& Clusters,int metric){
	int n=set->Return_size();
	//cout << n << endl;
	vector<Item*> It = set->return_items(); //pernw ta items tou set mou 
	//int c=Clusters->Return_size();
	//cout<< "-- " << w_f << " " << n << endl;
	//cout << "sssw" <<It.size() << endl; 
	for(int i=0;i<n;i++){ //gia kathe item sto set psaxnw na dw se pio cluster einai pio konta
		double distance = 0.0;
		double min = DBL_MAX ;
		int val = -1;
		//cout << "ffdddd" << endl;
		vector<double> y = It[i]->return_item_data();  //epistrefei tis sintetagmenes tou item
			for(unsigned int j=0;j<Clusters.size();j++){
				vector<double> x =Clusters[j]->return_i_cluster();
                if(metric == 1)
			    	distance = E_distance(y,x,x.size());
                else
                    distance = C_distance(y,x,x.size());
				//cout << "DISTANCE======== "<<distance << endl;
				if(j==0){
					min = distance;
						val=j;
				}
				if(distance < min){
					min = distance;
					val=j;
				}
			}
	//		cout <<"bval" << val << endl;
			Clusters[val]->AddData_toCluster(It[i]);
	}
}
void Lloyds_Assignment_2(DataSet* set,vector<Cluster*>& Clusters,int metric){
	int n=set->Return_size();
	//cout << n << endl;
	vector<Item*> It = set->return_items(); //pernw ta items tou set mou 
	//int c=Clusters->Return_size();
	//cout<< "-- " << w_f << " " << n << endl;
	//cout << "sssw" <<It.size() << endl; 
	vector<int> clusters_id; 
//	cout <<"CLUSTERS ID:" << endl;
	for(unsigned int j=0;j<Clusters.size();j++){
		clusters_id.push_back(Clusters[j]->return_cluster_id());
//		cout << Clusters[j]->return_cluster_id() << endl;
	}
	for(int i=0;i<n;i++){ //gia kathe item sto set psaxnw na dw se pio cluster einai pio konta
		double distance = 0.0;
		double min = DBL_MAX ;
		int val = -1;
		//cout << "ffdddd" << endl;
		if(It[i]->return_assigned()==0){	
			vector<double> y = It[i]->return_item_data();  //epistrefei tis sintetagmenes tou item
				for(unsigned int j=0;j<Clusters.size();j++){
					vector<double> x =Clusters[j]->return_i_cluster();
					if(metric == 1)
						distance = E_distance(y,x,x.size());
					else
						distance = C_distance(y,x,x.size());
					//cout << "DISTANCE======== "<<distance << endl;
					if(j==0){
						min = distance;
							val=j;
					}
					if(distance < min){
						min = distance;
						val=j;
					}
				}
		//		cout <<"bval" << val << endl;
				Clusters[val]->AddData_toCluster(It[i]);
				It[i]->set_assigned(1);
				It[i]->set_distance(distance);
				It[i]->set_cluster_id(Clusters[val]->return_cluster_id());
				It[i]->set_cluster_vector(Clusters[val]->return_i_cluster());
		}
		else if(It[i]->return_assigned()==1){
			int cl_id = It[i]->return_cluster_id();
		//	cout <<"CLID:" << cl_id << endl;
			vector<int>::iterator itr;
			itr = find (clusters_id.begin(), clusters_id.end(), (int)cl_id);			
			int in = -1;
			if (itr != clusters_id.end()) { 
				in =  std::distance(clusters_id.begin(),itr);
		//		cout << "Element present at index " << in << endl;
			}
			else {
				cout << "Element not found";
			}
			//cout << "IN " << in <<endl;
			Clusters[in]->AddData_toCluster(It[i]);
		}	
	}
}

double E_distance(vector<double> y,vector<double> x,int d){
	double E_d = 0;
	for( int l = 0; l < (int)y.size(); l++ ){
		E_d = E_d +  pow((double)y[l]-x[l],(double)2);
		//cout << " ED: " << E_d << endl;
	}
	double new_E_d = sqrt(E_d);
	//cout << " NEWED: " << new_E_d << endl;
	return new_E_d;
	}

double C_distance(vector<double> y,vector<double> x,int d){
	double C_d = 0;
	double aa=0;
	double bb=0;
	for( int l = 0; l < d; l++ ){
		cout << " koo " << y[l] << "okk "<< x[l] << endl;
		C_d = C_d + (y[l]*x[l]);
		aa = aa + (pow(y[l],2));
		bb = bb + (pow(x[l],2));			
	}
	cout << " C: " << C_d << endl;
	double aaa = sqrt(abs(aa));
	double bbb = sqrt(abs(bb));
	float cos_ = 0.0;
	cos_ = (double)(C_d) / (double)(aaa*bbb);
	double new_C_d = 1 - cos_;
	cout << " CD: " << new_C_d << endl;
	return new_C_d;
	}



void KmeansPlusPlus(int k,DataSet *set,vector<Cluster*>& Clusters,int Method){
	int n=set->Return_size();
	vector<Item*> It = set->return_items();
	vector<int> ClustersA ;
	for (int i=0;i<k;i++){
		//first cluster 
		if(i==0){
			int r = rand() %(n-1);		
		//	cout <<"r: " << r << endl;
			string idd = It[r]->return_item_id();
			//Cluster *clu  = new Cluster(r+1);
			//Clusters.push_back(clu);
			//cout << "random cluster :" << idd << endl;
			ClustersA.push_back(r+1);
		}
		else if(i>0){ //other clusters
			vector<double> dist;
			double d=0;
			double new_d=0;
			//cout << "N: " << n << endl;
			vector<double> y = It[i-1]->return_item_data();
			for(int j=0;j<n ;j++){
				//dd=0;
				//cout << "i-1 : " << i-1 << " j: "<< j << endl;
				vector<double> x = It[j]->return_item_data();
				/*for (unsigned int l=0;l<y.size();l++){
					cout <<"apostasi l: "<< l <<" "<< y[l] << endl;
				}*/
				//cout << y.size() << endl; 
				if (Method == 1){
					d = E_distance(y,x,x.size());
				}
				else if(Method ==2){
					d = C_distance(y,x,x.size());
				}
				
				//cout << "--of " << d << endl;
				new_d += (double)d*(double)d;
				//cout <<" -- D --"<< new_d << endl;
				dist.push_back(new_d);
			}
			double rD = Return_rD(dist[n-1]);
			double closest = findClosest(dist,n,rD) ;
			
			while(Bs(ClustersA, closest,n) == -1){
				rD = Return_rD(dist[n-1]);
				closest = findClosest(dist,n,rD);
			}
			ClustersA.push_back(closest);
			//cout << closest << endl;
			

		}	

	}
	for(unsigned int s=0;s<ClustersA.size();s++){
		Cluster *clu  = new Cluster(ClustersA[s]);
		clu->AddImag_toCluster(It[ClustersA[s]]->return_item_data());
		Clusters.push_back(clu);
	}
	for(unsigned int df=0;df<Clusters.size();df++){
			//cout << "CLU : "<<Clusters[df]->return_cluster_id() << endl;
	}
}


int Bs(vector<int> ClustersA,int closest,int n){
	if (closest == 0 || closest == n-1)
		return -1;
	if (binary_search(ClustersA.begin(), ClustersA.end(), closest)) {
			//	cout << "found  "<<endl;
				return -1;
				
			} else {
			//	cout << "not found!\n";
				return 0;
			}
}

double Return_rD(double max_dist){
	random_device rd;
    mt19937 gen(rd());
    double sample;
    uniform_real_distribution<> dis(0,max_dist);
	sample= dis(gen) ;
	return sample;

}

double findClosest(vector<double> dist, int n, double target) 
{ 
    // Corner cases 
	//cout << "findClosest to :" <<target << endl;
    if (target <= dist[0]) {
		//cout << "target <= " << dist[0] << endl;
        return 0; }
    if (target >= dist[n - 1]) {
		//cout << "target >= " << dist[n-1] << endl;
        return n - 1; 
		}
  
    // Doing binary search 
    int i = 0, j = n, mid = 0; 
    while (i < j) { 
        mid = (i + j) / 2; 
  
        if (dist[mid] == target) {
	//		cout << "dont think so" << dist[mid] <<endl;
            return mid; 
		}
        /* If target is less than array element, 
            then search in left */
        if (target < dist[mid]) { 
  
            // If target is greater than previous 
            // to mid, return closest of two 
	//		cout << "prev" << dist[mid-1] <<endl;
            if (mid > 0 && target > dist[mid - 1]) {
	//			cout << "hallo minimum " <<endl;
				if (target - dist[mid - 1] >= dist[mid] - target) 
					return mid; 
				else
					return mid-1;
               // return getClosest(dist[mid - 2],dist[mid], target); 
			}
  
            /* Repeat for left half */
            j = mid; 
        } 
  
        // If target is greater than mid 
        else { 
	//		cout << "greater than " << dist[mid+1] <<endl;
            if (mid < n - 1 && target < dist[mid + 1]) 
			{
				if (target - dist[mid - 1] >= dist[mid] - target) 
					return mid; 
				else
					return mid-1;	
			}
            // return getClosest(dist[mid],dist[mid + 1], target); 
            // update i 
            i = mid + 1;  
        } 
    } 
  
    // Only single element left after search 
    return mid; 
} 
  
  
double getClosest(double val1, double val2,double target) 
{ 
    if (target - val1 >= val2 - target) 
        return val2; 
    else
        return val1; 
} 


int Kmeans_Update(DataSet* set ,vector<Cluster*>& Clusters,int d,int metric){
	int c_n = Clusters.size();
	int idd=-1;
	int c_items = 0;
	vector<vector<double>> possibleNC; // apothikeusi twn newn cluster
	for(int i=0;i<c_n;i++){
		vector<double> calc; //timi neou cluster
		for (int c=0;c<d;c++){ //arxikopoiisi timwn neou cluster me 0
			double num = 0.0;
			calc.push_back(num);
		}
		vector<Item*>& It = Clusters[i]->return_items(); // epistrofi twn items tou cluster
		c_items= It.size();
		//cout << "itt ||||| " << It.size() << endl;
		for (int j=0;j<c_items;j++){ //gia kathe item 
			vector<double> y = It[j]->return_item_data(); //epistrofi tu vector me tis sintetagmenes tou 
			for(unsigned int h=0;h<y.size();h++){
				calc[h]+=(double)y[h]; // prosthesi kata stili k apothikeusi ston calc
				//cout<< y[h] <<endl;
			} 
		}
		for (unsigned int f=0;f<calc.size();f++){ // diairesi /c_items
			calc[f]=(double)calc[f]/(double)It.size();
		}
		possibleNC.push_back(calc); //apothikeusi sto possibleNC
	
	}		
	//cout <<"POSSIBLESIZEE: " << possibleNC.size() << endl;

//	cout << "temp " <<temp_clu.size() << endl;

	    int count=0;
        for (unsigned int d=0;d<possibleNC.size();d++){
            vector<double> I_t = Clusters[d]->return_i_cluster();
            if(possibleNC[d]==I_t){
                count++;
            }
        }

        if(count==(int)possibleNC.size()){
            return 0;
        }
        else{
			for (unsigned int f=0;f<possibleNC.size();f++){
//				cout << "REPLACE" << endl;
				Cluster *clu  = new Cluster(idd--);
				clu->AddImag_toCluster(possibleNC[f]);
				//vector<double> whatt = Clusters[f]->return_i_cluster();
				//cout << "OLD" << whatt[0] << endl;
				replace(Clusters.begin(), Clusters.end(), Clusters[f], clu);
				//vector<double> wh = Clusters[f]->return_i_cluster();
				//cout << "NEW" << wh[0] << endl;	
			}

			Lloyds_Assignment(set,Clusters,metric);
		}
		//cout << "------- count idiwn ----"<<count << endl;
	return -1;
}



void Silhouette(std::vector<Cluster*> Clusters,int k,string output_file,int metric){
	//cout << k << endl;
    double AVG_silhouette =0.0;
    fstream myfile;
    myfile.open (output_file,  fstream::out | fstream::app);
    myfile << "Silhouette : [" ;
	for (int l=0;l<k;l++){
		vector<Item*>& It = Clusters[l]->return_items(); //ta items tou cluster
		//cout <<"ITSIZE :" <<  It.size() << endl; 
		vector<double> i_cluster = Clusters[l]->return_i_cluster(); //i timi tou cluster
		
		double CL_Silhouette = 0.0;
		//cout << "------||||||||||||| --- 	" << It.size() << endl;
		for (unsigned int it=0;it<It.size();it++){ //gia kathe item sto cluster
			int val=-1;
			//double min=1.0;
            double distance=0.0;
		    double 	B_distance=0.0;
			vector<double> myit = It[it]->return_item_data();
			//2i pio mikri apostasi etsi vrisko tin 1i 	
			//cout << "--- " <<myit.size() << endl;
			vector<double> min_dist;
			for (unsigned int ml=0;ml<It.size();ml++){ 
				vector<double> myitt = It[ml]->return_item_data();
                if(metric==1)
				    distance += E_distance(myit,myitt,myit.size());
                else 
                    distance += C_distance(myit,myitt,myit.size()); 
			}
			//ypologismos olwn twn apostasewn tou antikeimenu apo ta alla clusters kai apothikeusi tous se vector 
			//gia sigkrisi argotera oste n vro ton 2o pio mikro
			//cout << Clusters.size()<< endl;
			for (unsigned int mcl=0;mcl<Clusters.size();mcl++){
				double new_distance=0.0;
				vector<double> ii_cluster = Clusters[mcl]->return_i_cluster();
				//cout << "dddd " << myit.size() << endl;
				//cout << "dddd " << ii_cluster.size() << endl;
				new_distance = E_distance(ii_cluster,myit,myit.size());
				min_dist.push_back(new_distance);
			}
			
			val = print2Smallest(min_dist, min_dist.size()); //epistrefei tin thesi tu 2ou mikroterou
			vector<Item*>& nn_It = Clusters[val]->return_items();  //pernw ta antikeimena tou mikroterou
			for(unsigned int ii=0;ii<nn_It.size();ii++){	
				vector<double> nn_it = nn_It[ii]->return_item_data(); //gia kathe antikeimeno tou mikroterou ipologizw apostasi me to item mou
				//cout << "nn_it: " << nn_it.size() << endl;
                if(metric==1)
			    	B_distance += E_distance(nn_it,myit,myit.size());
                else
                    B_distance += C_distance(nn_it,myit,myit.size());

			}
			B_distance=B_distance/(double)nn_It.size(); 
			//cout << "--------------------" << endl;
			//cout << " Bdistance " << B_distance << endl;
			//cout << " distance " << distance << endl;
			double avg_distance = 0;
			avg_distance = distance/(double)It.size();

			double Silh =0.0;
			if (avg_distance>B_distance){
				Silh = (B_distance/avg_distance ) - (double)1 ;
				}
			else if(avg_distance<B_distance){
				Silh = (double)1 - (avg_distance/B_distance);
				}
			else if(avg_distance==B_distance)
				Silh=0;
			
			//cout << "SILLLLLL------- " <<  Silh << endl;
			CL_Silhouette +=Silh;
		//	cout << "B_DISTANCE: " <<  B_distance << endl;
			min_dist.erase(min_dist.begin(),min_dist.end()); //diagrafi twn apostasewn apo ta cluster g to epomeno item
		}
		//cout <<"distance: "<<  distance << endl;
        double  Cl_silh =0.0;
		if((double)It.size()==0)
			Cl_silh=0;
		else
        	Cl_silh = (double)CL_Silhouette/(double)It.size() ;
        cout << "SILHOUETTE " << Cl_silh << endl;
        myfile << Cl_silh ;
        AVG_silhouette+=Cl_silh;
	}
	/*int kk=Clusters.size();
	for( unsigned int i = 0; i < kk; i++ )
		{
			//Memory+=sizeof(Items[i]);
			delete Clusters[i];
		}
	Clusters.erase (Clusters.begin(),Clusters.end());*/
    myfile << "]\n";
    myfile << " Total Silhouette " << AVG_silhouette/Clusters.size() <<"\n";
	myfile << "\n" ;
    cout << "AVG SILLHOUETTE: " << AVG_silhouette/Clusters.size() << endl;
    myfile.close();
}

int print2Smallest(vector<double> arr, int arr_size) 
{ 
    int i;
	double first, second; 
	
    /* There should be atleast two elements */
    if (arr_size < 2) 
    { 
        printf(" Invalid Input "); 
        return -1; 
    } 
  
    first = second = DBL_MAX; 
	int val=-1;
	int val1=-1;
    for (i = 0; i < arr_size ; i ++) 
    { 
        /* If current element is smaller than first  
           then update both first and second */
		//cout << "First :" << first << endl;
        if (arr[i] < first) 
        { 
            second = first; 
			val=val1;
			//cout <<"second " << second << endl;
            first = arr[i]; 
			val1 = i;
        }

        /* If arr[i] is in between first and second  
           then update second  */
        else if (arr[i] < second && arr[i] != first) {
            second = arr[i]; 
			val = i;
		}
    } 
    if (second == DBL_MAX) {
       // cout << "There is no second smallest element" << endl; 
		return -1;
	}
    else
		return val;
       //cout << "The smallest element is " << first << " and second Smallest element is " << val << " "<<  second << endl;; 
} 

int PAM_Update_Lloyds(DataSet* set ,vector<Cluster*>& Clusters,int d,int metric){
    int c_n = Clusters.size(); //epistrefi twn arithmo twn cluster mou mou
    int c_items=0;
   // cout << "IN" << endl;
    vector<vector<double>> possibleNC; 
    vector<int> possibleNC_id; 
    for(int i=0;i<c_n;i++){
    	vector<Item*>& It = Clusters[i]->return_items(); // epistrofi twn items tou cluster
		c_items= It.size();
		//cout << "itt ||||| " << It.size() << endl;
        vector<double> D_C; //apothikeusi twn distances twn stoixeiwn apo ola ta ypoloipa sto cluster tous
        //outws wste n pernw to mikrotero kai na to orizw san neo kentro.  
        //cout << D_C.size() <<endl;
		for (int j=0;j<c_items;j++){ //gia kathe item 
			vector<double> y = It[j]->return_item_data(); //epistrofi tu vector me tis sintetagmenes tou 
            double DD=0.0;
            for(int d=0;d<c_items;d++){   
                vector<double> x = It[d]->return_item_data();
                if(metric==1){
                    DD += E_distance(y,x,d);
                }
                else
                    DD += C_distance(y,x,x.size());
            }
        DD=DD/c_items;  // dia twn arithmo twn items sto cluster
        //cout << "apostasi tou " << i << " : " <<  DD << endl;
		D_C.push_back(DD);	
		}

       // cout << D_C.size() << " = "<< It.size() << endl;
        int n_S = 0;
        //n_S = print2Smallest(D_C,(int)D_C.size());
		vector<double>::iterator result = min_element(begin(D_C),end(D_C));
    	n_S = distance(begin(D_C),result);
        vector<Item*>& It_t = Clusters[i]->return_items(); // epistrofi twn items tou cluster
        vector<double> temp_d = It_t[n_S]->return_item_data();
        string id = It_t[n_S]->return_item_id();
        int len = id.length();
        string str2 = id.substr (4,len-4);
		int new_id = -1;
		new_id = stoi(str2);
		//cout << "hi" << str2 << endl;
        possibleNC.push_back(temp_d);
		possibleNC_id.push_back(new_id);

      //  cout << "Smallest: " << n_S << endl;
    }

        int count=0;
    	//    int idd=-1;
        for (unsigned int d=0;d<possibleNC.size();d++){
            vector<double> I_t = Clusters[d]->return_i_cluster();
            if(possibleNC[d]==I_t){
                count++;
            }
        }

        if(count==(int)possibleNC.size()){
            return 0;
        }
        else{
			for (unsigned int f=0;f<possibleNC.size();f++){
//				cout << "REPLACE" << endl;
				Cluster *clu  = new Cluster(possibleNC_id[f]);
				clu->AddImag_toCluster(possibleNC[f]);
				//vector<double> whatt = Clusters[f]->return_i_cluster();
				//cout << "OLD" << whatt[0] << endl;
				replace(Clusters.begin(), Clusters.end(), Clusters[f], clu);
				//vector<double> wh = Clusters[f]->return_i_cluster();
				//cout << "NEW" << wh[0] << endl;	
			}

			Lloyds_Assignment(set,Clusters,metric);
		}
	return -1;
}

void OutPuts_K(vector<Cluster*> Clusters,double t,string output_file,int metric,int a,int b,int c,int wtd){
    fstream myfile;

	myfile.open (output_file,  fstream::out | fstream::app);
	myfile << "Algorithm:" << a <<"x" << b << "x" << c <<  "\n";
	myfile << "-------------------------------------------" << endl;
	if(metric==1)
		myfile << "Metric: Euclidean" << "\n";
	if(metric==2)
		myfile << "Metric: Cosine" << "\n";
    for (unsigned int i=0;i<Clusters.size();i++){
		vector<double> v_C = Clusters[i]->return_i_cluster(); //sintetagmenes kentrou
		myfile << "\nCluster: " << i << "\n";
		vector<Item*>& temp_It = Clusters[i]->return_items(); //items sto kentro
		myfile << "Cluster Size: " << Clusters[i]->Return_size() ;
		if(wtd==2){
			myfile << " { ";
			 for (unsigned int s=0;s<temp_It.size();s++){
				myfile <<  temp_It[s]->return_item_id() << ",";
			 }
			 myfile << " } ";
		}
		myfile << "Centroid coordinates: ["; 
		for(unsigned int v=0;v<v_C.size();v++){
			myfile << v_C[v] << "," ;
		}
		myfile << "]\n"; 
	 }
	cout << "Duration time : " << t << endl;
	myfile << "Clustering Time: " <<  t << endl; //duration time

	myfile.close();

}

void OutPuts_P(vector<Cluster*> Clusters,double t,string output_file,int metric,int a,int b,int c,int wtd){
    fstream myfile;
	myfile.open (output_file,  fstream::out | fstream::app);
	myfile << "Algorithm:" << a <<"x" << b << "x" << c <<  "\n";
	if(metric==1)
		myfile << "Metric: Euclidean" << "\n";
	if(metric==2)
		myfile << "Metric: Cosine" << "\n";
    for (unsigned int i=0;i<Clusters.size();i++){
		int cid = Clusters[i]->return_cluster_id(); //id tou kentrou 
		myfile << "\nCluster: " << i << "\n";
		vector<Item*>& temp_It = Clusters[i]->return_items(); //items sto kentro
		myfile << "\nCluster Size: " << Clusters[i]->Return_size();
		myfile << "Centroid id: " << cid;
		if(wtd==2){
			myfile << " { ";
			 for (unsigned int s=0;s<temp_It.size();s++){
				myfile <<  temp_It[s]->return_item_id() << ",";
			 }
			 myfile << " } ";
		}
		myfile << endl;
	 }
	cout << "Duration time : " << t << endl;
	myfile << "Clustering Time: " <<  t << endl; //duration time
	myfile << endl;
	myfile.close();
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
	