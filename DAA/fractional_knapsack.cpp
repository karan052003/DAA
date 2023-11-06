#include <bits/stdc++.h>
using namespace std;

int main(){
    // fractional we take the goods which have more value per weight
    
    // take the total number of input
    int n;
    cout << "Enter total number of elements: ";
    cin >> n;
    
    vector<double> weight(n, 0), price(n, 0);
    for(int i = 0; i < n; i++){
        cout << "Enter weight and prices: ";
        cin >> weight[i] >> price[i]; 
    }
    
    double capacity;
    cout << "Enter the capacity: ";
    cin >> capacity;
    
    // create a fractional priority queue
    priority_queue<pair<double, int>> pq;
    for(int i = 0; i < n; i++){
        pq.push({ price[i] / weight[i], i });
    }
    
    // Calculate the total profit
    double totalProfit = 0;
    double remainingCapacity = capacity;
    
    while(!pq.empty() && remainingCapacity > 0){
        int idx = pq.top().second; pq.pop();
            
        if(remainingCapacity >= weight[idx]){
            remainingCapacity -= weight[idx];
            totalProfit += price[idx];
        }else{
           totalProfit += (price[idx] * (remainingCapacity / weight[idx]));
           remainingCapacity = 0;
        }
    }    
    
    cout << "Total Profit: " << totalProfit << endl;
    
    return 0;
}
