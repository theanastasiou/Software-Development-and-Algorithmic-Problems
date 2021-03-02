#include "Combinations.h"
using namespace std;
#include <algorithm>

void Combination_2_1_1(int k,DataSet *set,std::vector<Cluster*> Clusters,int d,int metric,string output_file,int wtd){
    clock_t start = clock(); //clock start
    KmeansPlusPlus(k,set,Clusters,metric); //kmeans++ (A2)

	
	Lloyds_Assignment(set,Clusters,metric);


	//cout << "-------------------------" <<endl;
	int cc=0;

	while(Kmeans_Update(set,Clusters,d,metric)!=0){
		cc++;
		if(cc>30)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,2,1,1,wtd);
	Silhouette(Clusters,k,output_file,metric);
}

void Combination_2_1_2(int k,DataSet *set,std::vector<Cluster*> Clusters,int d,int metric,string output_file,int wtd){
    clock_t start = clock(); //clock start
    KmeansPlusPlus(k,set,Clusters,metric); //kmeans++ (A2)


	Lloyds_Assignment(set,Clusters,metric);


	//cout << "-------------------------" <<endl;
	int cc=0;
	while(PAM_Update_Lloyds(set,Clusters,d,metric)!=0){
		cc++;
		if(cc>20)
			break;
	}

    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_P(Clusters,duration_sec, output_file,metric,2,1,2,wtd);
    Silhouette(Clusters,k,output_file,metric);
}

void Combination_1_1_1(int k,DataSet *set,std::vector<Cluster*>& Clusters,int d,int metric,string output_file,int wtd){
    clock_t start = clock(); //clock start
    Random_Selection(k,set,Clusters); //random selection (A1) 




	Lloyds_Assignment(set,Clusters,metric);

		

	//cout << "-------------------------" <<endl;
	int cc=0;

	while(Kmeans_Update(set,Clusters,d,metric)!=0){
		cc++;
		if(cc>40)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	//OutPuts_K(Clusters,duration_sec, output_file,metric,1,1,1,wtd);
    //Silhouette(Clusters,k,output_file,metric);
}

void Combination_1_1_2(int k,DataSet *set,std::vector<Cluster*> Clusters,int d,int metric,string output_file,int wtd){
    clock_t start = clock(); //clock start
    Random_Selection(k,set,Clusters); //random selection (A1) 

	
	Lloyds_Assignment(set,Clusters,metric);


	//cout << "-------------------------" <<endl;
	int cc=0;

	while(PAM_Update_Lloyds(set,Clusters,d,metric)!=0){
		cc++;
		if(cc>20)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	//OutPuts_P(Clusters,duration_sec, output_file,metric,1,1,2,wtd);
    //Silhouette(Clusters,k,output_file,metric);
}

void Combination_1_2_1(int h,int L,int n,int k,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd){
	cout << "IN COMBINATION" << endl;
	clock_t start = clock(); //clock start
	Random_Selection(k,set,Clusters); //random selection (A1) 
	
	if (metric == 1){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Euclidean(set);
		int revision=0;
	//	cout << "CLUSTERS" << Clusters.size() << endl;
		double Radius=0.3;
		int Items_assign=0;
		int Items_in_Buckets=0;
		int flag=0;
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				
				list<Item*>& ItemsInBucket = lsh->Q_Calc_Euclidean(set,mc);
				//ASSIGN 
				list<Item*>::iterator iter;
				int IteM=0;
	//			cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				Items_in_Buckets+= ItemsInBucket.size();
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = E_distance(mc,i_data,i_data.size());
					if(distance_fromcluster< Radius){
						//	cout << "IN range must assign " << endl
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							Items_assign++;
							
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							
							continue;
							}

					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
				flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while(Items_assign!=Items_in_Buckets) ;
	//	cout <<"items in rad -------------------------------- " << flag << endl;
		if(flag==1){
			Lloyds_Assignment_2(set,Clusters,1);
		}
	delete lsh;
	}
	
	if(metric == 2){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Cosine(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		do{
			int items_in_Rad=0;
	//		cout << "RANDOM " << endl;
			for(unsigned int i=0;i<Clusters.size();i++){
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				
				list<Item*> ItemsInBucket = lsh->Q_Calc_Cosine(set,mc);
				list<Item*>::iterator iter;
				int IteM=0;
	//			cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;	
		}while (Items_assign!=Items_in_Buckets);
		//cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete lsh;
	}
//	cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
				cout << Clusters[hf]->Return_size() << endl;
			}
//			cout << "Cc " << cc << endl;
	while(Kmeans_Update(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>20)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,1,2,1,wtd);
	Silhouette(Clusters,k,output_file,metric);

}

void Combination_1_2_2(int h,int L,int n,int k,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd){
	cout << "IN COMBINATION" << endl;
	clock_t start = clock(); //clock start
	Random_Selection(k,set,Clusters); //random selection (A1) 
	
	if (metric == 1){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Euclidean(set);
		int revision=0;
//		cout << "CLUSTERS" << Clusters.size() << endl;
		double Radius=0.3;
		int Items_assign=0;
		int Items_in_Buckets=0;
		int flag=0;
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
//				cout << "ss" << mc.size() << endl;
				
				list<Item*>& ItemsInBucket = lsh->Q_Calc_Euclidean(set,mc);
				//ASSIGN 
				list<Item*>::iterator iter;
				int IteM=0;
			//	cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				Items_in_Buckets+= ItemsInBucket.size();
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = E_distance(mc,i_data,i_data.size());
					if(distance_fromcluster< Radius){
						//	cout << "IN range must assign " << endl
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							Items_assign++;
							
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							
							continue;
							}

					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
				flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while(Items_assign!=Items_in_Buckets) ;
		//cout <<"items in rad -------------------------------- " << flag << endl;
		if(flag==1){
			Lloyds_Assignment_2(set,Clusters,1);
		}
	delete lsh;
	}
	
	if(metric == 2){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Cosine(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		do{
			int items_in_Rad=0;
		//	cout << "RANDOM " << endl;
			for(unsigned int i=0;i<Clusters.size();i++){
				vector<double> mc = Clusters[i]->return_i_cluster();
		//		cout << "ss" << mc.size() << endl;
				
				list<Item*> ItemsInBucket = lsh->Q_Calc_Cosine(set,mc);
				list<Item*>::iterator iter;
				int IteM=0;
		//		cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
		//		cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;	
		}while (Items_assign!=Items_in_Buckets);
		//cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete lsh;
	}
	//cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
//				cout << Clusters[hf]->Return_size() << endl;
			}
//			cout << "Cc " << cc << endl;
	while(PAM_Update_Lloyds(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>20)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,1,2,2,wtd);
	Silhouette(Clusters,k,output_file,metric);

}

void Combination_2_2_1(int h,int L,int n,int k,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd){
	cout << "IN COMBINATION" << endl;
	clock_t start = clock(); //clock start
	KmeansPlusPlus(k,set,Clusters,metric); //random selection (A1) 
	
	if (metric == 1){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Euclidean(set);
		int revision=0;
		//cout << "CLUSTERS" << Clusters.size() << endl;
		double Radius=0.3;
		int Items_assign=0;
		int Items_in_Buckets=0;
		int flag=0;
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
				//cout << "ss" << mc.size() << endl;
				
				list<Item*>& ItemsInBucket = lsh->Q_Calc_Euclidean(set,mc);
				//ASSIGN 
				list<Item*>::iterator iter;
				int IteM=0;
				//cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				Items_in_Buckets+= ItemsInBucket.size();
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = E_distance(mc,i_data,i_data.size());
					if(distance_fromcluster< Radius){
						//	cout << "IN range must assign " << endl
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							Items_assign++;
							
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							
							continue;
							}

					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
				flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while(Items_assign!=Items_in_Buckets) ;
		//cout <<"items in rad -------------------------------- " << flag << endl;
		if(flag==1){
			Lloyds_Assignment_2(set,Clusters,1);
		}
	delete lsh;
	}
	
	if(metric == 2){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Cosine(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		do{
			int items_in_Rad=0;
		//	cout << "RANDOM " << endl;
			for(unsigned int i=0;i<Clusters.size();i++){
				vector<double> mc = Clusters[i]->return_i_cluster();
		//		cout << "ss" << mc.size() << endl;
				
				list<Item*> ItemsInBucket = lsh->Q_Calc_Cosine(set,mc);
				list<Item*>::iterator iter;
				int IteM=0;
		//		cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
		//		cout<< "flag" << flag << endl;
			//	flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;	
		}while (Items_assign!=Items_in_Buckets);
		//cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete lsh;
	}
	//cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
	//			cout << Clusters[hf]->Return_size() << endl;
			}
	//		cout << "Cc " << cc << endl;
	while(Kmeans_Update(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>30)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,2,2,1,wtd);
	Silhouette(Clusters,k,output_file,metric);

}
void Combination_2_2_2(int h,int L,int n,int k,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd){
	cout << "IN COMBINATION" << endl;
	clock_t start = clock(); //clock start
	KmeansPlusPlus(k,set,Clusters,metric); //random selection (A1) 
	
	if (metric == 1){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Euclidean(set);
		int revision=0;
	//	cout << "CLUSTERS" << Clusters.size() << endl;
		double Radius=0.3;
		int Items_assign=0;
		int Items_in_Buckets=0;
		int flag=0;
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				
				list<Item*>& ItemsInBucket = lsh->Q_Calc_Euclidean(set,mc);
				//ASSIGN 
				list<Item*>::iterator iter;
				int IteM=0;
	//			cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				Items_in_Buckets+= ItemsInBucket.size();
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = E_distance(mc,i_data,i_data.size());
					if(distance_fromcluster< Radius){
						//	cout << "IN range must assign " << endl
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							Items_assign++;
							
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							
							continue;
							}

					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
				flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while(Items_assign!=Items_in_Buckets) ;
	//	cout <<"items in rad -------------------------------- " << flag << endl;
		if(flag==1){
			Lloyds_Assignment_2(set,Clusters,1);
		}
	delete lsh;
	}
	
	if(metric == 2){
		LSH *lsh = new LSH(d,h,L,n,metric);
		lsh->Calc_Cosine(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		do{
			int items_in_Rad=0;
	//		cout << "RANDOM " << endl;
			for(unsigned int i=0;i<Clusters.size();i++){
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				
				list<Item*> ItemsInBucket = lsh->Q_Calc_Cosine(set,mc);
				list<Item*>::iterator iter;
				int IteM=0;
	//			cout << "SIZE OF BUCKET : " << ItemsInBucket.size() << endl;
				for(iter=ItemsInBucket.begin(); iter != ItemsInBucket.end() ; ++iter) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*iter;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
				IteM++;	
				}
				
				//Items_In_Bucket_Assign(int bucket,Clusters,)
				//cout <<"BB" << bucket << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;	
		}while (Items_assign!=Items_in_Buckets);
	//	cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete lsh;
	}
	//cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
	//			cout << Clusters[hf]->Return_size() << endl;
			}
	//		cout << "Cc " << cc << endl;
	while(PAM_Update_Lloyds(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>20)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,2,2,2,wtd);
	Silhouette(Clusters,k,output_file,metric);

}

void Combination_1_3_1(int h,int L,int n,int k,int M,int probes,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd)
{
	clock_t start = clock(); //clock start
	HyperCube *hyper = new HyperCube(k,M,probes,n,d,metric);
	Random_Selection(k,set,Clusters); //random selection (A1) 
	//cout << "CLUSTERS" << Clusters.size() << endl;
	if (metric == 1){
		hyper->Calc_H(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Cube_Search_Euclidean(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
				int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
	//			cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
			//	flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
	}while (Items_assign!=Items_in_Buckets);
	//cout << flag << endl;
	Lloyds_Assignment_2(set,Clusters,1);
	
	delete hyper;	
	}

	if(metric == 2){
		
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Search_Cosine(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
				//int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
	//			cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while (Items_assign!=Items_in_Buckets);
	//	cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete hyper;	
		//hyper->Q_Calc_Cosine(set,Q_file);
	}
	//cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
	//			cout << Clusters[hf]->Return_size() << endl;
			}
	//		cout << "Cc " << cc << endl;
	while(Kmeans_Update(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>40)
			break;
	}
    //cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,1,3,1,wtd);
	Silhouette(Clusters,k,output_file,metric);

	//delete hyper;
}


void Combination_1_3_2(int h,int L,int n,int k,int M,int probes,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd)
{
	clock_t start = clock(); //clock start
	HyperCube *hyper = new HyperCube(k,M,probes,n,d,metric);
	Random_Selection(k,set,Clusters); //random selection (A1) 
	//cout << "CLUSTERS" << Clusters.size() << endl;
	if (metric == 1){
		hyper->Calc_H(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Cube_Search_Euclidean(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
				//int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
	//			cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
	}while (Items_assign!=Items_in_Buckets);
	//cout << flag << endl;
	Lloyds_Assignment_2(set,Clusters,1);
	
	delete hyper;	
	}

	if(metric == 2){
		
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Search_Cosine(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
				//int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
	//			cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while (Items_assign!=Items_in_Buckets);
	//	cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete hyper;	
		//hyper->Q_Calc_Cosine(set,Q_file);
	}
	//cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
	//			cout << Clusters[hf]->Return_size() << endl;
			}
	//		cout << "Cc " << cc << endl;
	while(PAM_Update_Lloyds(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>40)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,1,2,2,wtd);
	Silhouette(Clusters,k,output_file,metric);

	//delete hyper;
}


void Combination_2_3_1(int h,int L,int n,int k,int M,int probes,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd)
{
	clock_t start = clock(); //clock start
	HyperCube *hyper = new HyperCube(k,M,probes,n,d,metric);
	KmeansPlusPlus(k,set,Clusters,metric); //random selection (A1) 
	//cout << "CLUSTERS" << Clusters.size() << endl;
	if (metric == 1){
		hyper->Calc_H(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Cube_Search_Euclidean(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
			//	int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
	//			cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
	}while (Items_assign!=Items_in_Buckets);
	//cout << flag << endl;
	Lloyds_Assignment_2(set,Clusters,1);
	
	delete hyper;	
	}

	if(metric == 2){
		
		int revision=0;
		double Radius=0.3;
	//	int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Search_Cosine(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
				//int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
	//			cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while (Items_assign!=Items_in_Buckets);
	//	cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete hyper;	
		//hyper->Q_Calc_Cosine(set,Q_file);
	}
	//cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
	//			cout << Clusters[hf]->Return_size() << endl;
			}
	//		cout << "Cc " << cc << endl;
	while(Kmeans_Update(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>40)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,2,3,1,wtd);
	Silhouette(Clusters,k,output_file,metric);

	//delete hyper;
}


void Combination_2_3_2(int h,int L,int n,int k,int M,int probes,DataSet *set,vector<Cluster*>& Clusters,int d,int metric,std::string output_file,int wtd)
{
	clock_t start = clock(); //clock start
	HyperCube *hyper = new HyperCube(k,M,probes,n,d,metric);
	KmeansPlusPlus(k,set,Clusters,metric); //random selection (A1) 
	//cout << "CLUSTERS" << Clusters.size() << endl;
	if (metric == 1){
		hyper->Calc_H(set);
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
	//			cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Cube_Search_Euclidean(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
				//int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
	//			cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
	//			cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
	}while (Items_assign!=Items_in_Buckets);
//	cout << flag << endl;
	Lloyds_Assignment_2(set,Clusters,1);
	
	delete hyper;	
	}

	if(metric == 2){
		
		int revision=0;
		double Radius=0.3;
		//int flag=0;
		int Items_assign=0;
		int Items_in_Buckets=0;
		//HyperCube *hyper = new HyperCube(k,M,probes,n,d,method);
		//cout << "N: " << n << endl;
		//hyper->Q_Calc_Euclidean(set,Q_file);
		do{
			int items_in_Rad=0;
			for(unsigned int i=0;i<Clusters.size();i++){
				
				vector<double> mc = Clusters[i]->return_i_cluster();
//				cout << "ss" << mc.size() << endl;
				list<Item*> myIt = hyper->Search_Cosine(mc);
				//cout << "FINALL: " << myIt.size() << endl;
				std::list<Item*>::iterator ite;
				//int itemsin=0;
				for(ite=myIt.begin(); ite != myIt.end() ; ++ite) //me iterator diasxizo tin lista me ta items sto bucket mou
				{	
					Item* it=*ite;
					//cout << "gia to Item " << IteM << endl;
					double distance_fromcluster=0.0;
					vector<double> i_data = it->return_item_data();
					//cout << "must be 202 : " <<i_data.size() << endl;
					distance_fromcluster = C_distance(mc,i_data,i_data.size());
					if(distance_fromcluster < Radius){
						//cout << "IN range must assign " << endl;
						if(it->return_assigned()==0){ //assigned=0 simainei oti den einai assigned se kapoio cluster
							it->set_assigned(1);
							it->set_rev(revision);
							it->set_distance(distance_fromcluster);
							it->set_cluster_id(Clusters[i]->return_cluster_id());
							it->set_cluster_vector(Clusters[i]->return_i_cluster());
							//cout << "OL" << endl;
						}
						else if((it->return_assigned()==1) && (revision==it->return_rev())){
							//scout << "FF" << endl;
							double prev_dist = it->return_distance();
							double new_dist=0.0;
							new_dist=E_distance(mc,i_data,i_data.size());
							if(new_dist<prev_dist){
								//PREPEI NA GINETE DELETE P TO PROIGUMENO CLUSTER;****************
								//--------------------------------------------
								it->set_assigned(1);
								it->set_rev(revision);
								it->set_distance(distance_fromcluster);
								it->set_cluster_id(Clusters[i]->return_cluster_id());
								it->set_cluster_vector(Clusters[i]->return_i_cluster());
							}
						}
						else if (revision > it->return_rev()){
							continue;
						}
					}
					if(distance_fromcluster> Radius){
						//	cout<< "out of range must continue to next item" << endl;
						items_in_Rad++;
						continue;
					
					}
				
					
				}	
//				cout << "ITEMS:"<< itemsin << endl;
				
			}
			if(items_in_Rad==0){
//				cout<< "flag" << flag << endl;
				//flag=1;
				break;
			}
			revision++;
			Radius=2*Radius;
		}while (Items_assign!=Items_in_Buckets);
//		cout << flag << endl;
		Lloyds_Assignment_2(set,Clusters,1);
		
		delete hyper;	
		//hyper->Q_Calc_Cosine(set,Q_file);
	}
//	cout << "------------OTINANAI-------------" <<endl;
	int cc=0;
	for(unsigned int hf=0;hf<Clusters.size();hf++){
//				cout << Clusters[hf]->Return_size() << endl;
			}
//			cout << "Cc " << cc << endl;
	while(PAM_Update_Lloyds(set,Clusters,d,metric)!=0){
		cc++;
		cout << cc << endl;
		if(cc>40)
			break;
	}
    cout << "Cc " << cc << endl;
    double duration_sec = (double)(clock() - start)/CLOCKS_PER_SEC ;		
	OutPuts_K(Clusters,duration_sec, output_file,metric,2,3,2,wtd);
	Silhouette(Clusters,k,output_file,metric);
	//delete hyper;
}