#include <iostream>
#include<fstream>
#include <list>
#include <iterator>
#include <map>
#include <vector>


using namespace std;

int main(int argc, char *argv[] )
{
    ifstream inData;
    ifstream cost;
    ofstream outData;
    int number=0;
    inData.open(argv[1]);
    if(!inData){
        cerr << "Error opening input file";
        return -1;
    }
    cost.open(argv[3]);
    if(!cost){
        cerr << "Error opening cost file";
        return -1;
    }
    int cost_array[10001];
    //reading cost and saving
    for(int i=0; i<=10000; i++){
        int num=0;
        int cost_num = 0;
        cost>>num;
        cost>>cost_num;
        cost_array[num] = cost_num;
    }
    outData.open(argv[2]);
    if(!outData){
        cerr << "Error opening output file.";
        return -1;
    }
    inData>>number; // no. of test cases from i/p file
    for (int i=0; i<number; i++){
        int period =0;
        int amt=0;
        int bal=0;
        map<int,int> min_cost; // map to store sum, min_cost;
        map<int, int>::iterator itc;
        inData>>period>>amt>>bal; // input period,amount,balance from i/p file
        vector<int> pairs;
        vector<int> :: iterator itl;
        vector<int> values;
        vector<int> :: iterator it;
        map<int, vector<int> > sum;
        map<int, vector<int> > sum1;
        map<int, vector<int> > :: iterator it1;
        map<int, map<int, vector<int> > > solution;
        map<int, map<int, vector<int> > > :: iterator it2;
        for (int k=1; k<=period; k++){
            //   cout<<"period is:"<<k<<endl;
            if(k==1){
                for(int j=amt; j<=amt+bal && (j<=period*amt); j++){
                    sum[j].push_back(j);
                    min_cost.insert(pair<int, int>(j, cost_array[j]));
                }
                solution.insert( make_pair(k, sum));
            } //k=1
            else if(k!=period && k!=1){
                for(int p= k*amt; (p<=((k*amt)+bal)) && (p<=period*amt) ;p++){
                    int sum_here = p; //current sums
                    it2 =solution.find(k-1);
                    int min_cost_cal = 99999999;
                    for(it1 = it2->second.begin(); it1!=it2->second.end() && (it1->first <= sum_here); ++it1){
                        int prev_sum = it1->first;
                        pairs = it1->second; // put values for sum of k-1
                        int new_el = sum_here - prev_sum;
                        pairs.push_back(new_el);
                        int cost_curr = 0;
                        cost_curr = min_cost[prev_sum] + cost_array[new_el];
                        if (cost_curr < min_cost_cal){
                            min_cost_cal = cost_curr;
                            sum1.erase(sum_here);
                            sum1[sum_here] = pairs;
                            if(min_cost_cal < min_cost[sum_here] || min_cost[sum_here]==0){
                                min_cost.erase(sum_here);
                                min_cost.insert(pair<int, int>(sum_here, min_cost_cal));}
                        } //cost
                        pairs.clear();
                    }//it1
                    //        }//else
                }//p
                solution.insert( make_pair(k, sum1));
                solution.erase(k-1);
                sum1.clear();
            } //if k!=period
            else if(k==period){
                int sum_here = period*amt;
                it2 =solution.find(k-1);
                int min_cost_cal = 99999999;
                for(it1 = it2->second.begin(); it1!=it2->second.end() && (it1->first <= sum_here); ++it1){
                    pairs = it1->second; // put values for sum of k-1
                    int prev_sum = it1->first;
                    int new_el = sum_here - prev_sum;
                    pairs.push_back(new_el);
                    int cost_curr = 0;
                    cost_curr = min_cost[prev_sum] + cost_array[new_el];
                    if (cost_curr < min_cost_cal){
                        min_cost_cal = cost_curr;
                        sum1.erase(sum_here);
                        sum1[sum_here] = pairs;
                        if(min_cost_cal < min_cost[sum_here] || min_cost[sum_here]==0){
                            min_cost.erase(sum_here);
                            min_cost.insert(pair<int, int>(sum_here, min_cost_cal));}
                    } //cost
                    pairs.clear();
                }//it1
                solution.insert(make_pair(k, sum1));
                sum1.clear();
                solution.erase(k-1);
            } //if k= period
        }//k
        
        //printing the optimal solution
        it2 =solution.find(period);
        for(it1 = it2->second.begin(); it1!=it2->second.end(); ++it1){
            for(it = it1->second.begin(); it!=it1->second.end(); ++it){
                cout<<*it<<" ";
            }//it
            cout<<endl;
        }//it1
        
        itc = min_cost.find(period*amt);
        if(i==number){
            outData<<itc->second;
        }else{
            outData<<itc->second<<endl;
        }
        
        
    } //i= 0 to number
    inData.close();
    cost.close();
    outData.close();
    return 0;
}
