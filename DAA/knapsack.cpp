#include <bits/stdc++.h>
using namespace std;

int getMaxPrice(int idx, int capacity, vector<int> &price, vector<int> &weight){
    if(capacity < 0) return -1e9;
    if(idx == price.size()) return 0;
    
    int take = getMaxPrice(idx + 1, capacity - weight[idx], price, weight) + price[idx];
    int leave = getMaxPrice(idx + 1, capacity, price, weight);    
    
    return max(take, leave);
}

int getMaxPriceTabulation(int capacity, vector<int> &price, vector<int> &weight){
    int n = price.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for(int i = n - 1; i >= 0; i--){
        for(int m = 0; m <= capacity; m++){
            int take = 0;
            if(m - weight[i] >= 0) take = dp[i + 1][m - weight[i]] + price[i];
            
            int leave = dp[i + 1][m];
    
            dp[i][m] = max(take, leave);
        }
    }
    
    int result = dp[0][capacity];
    
    cout << "Result: ";
    
    // Backtrack and display the item
    int m = capacity;
    for(int i = 0; i < n; i++){
        // check if it is comming from take or leave
        // if leave then capacity will be same
        if(result == dp[i + 1][m]){
            continue;
        }else{
            cout << i << " ";
        
            m -= weight[i];
            result -= price[i];
        }
    }
    
    cout << endl;
    
    return dp[0][capacity];
}

struct Node{
    int level, profit, weight;
    
    Node(int level, int profit, int weight){
        this->level = level;
        this->profit = profit;
        this->weight = weight;
    }
};

double calculateBound(int idx, int currentProfit, int currentWeight, int capacity, const vector<pair<double, int>> &items, vector<int> &price, vector<int> &weight){
    double boundProfit = currentProfit;
    
    for(int i = idx + 1; i < items.size(); i++){
        int itemPrice = price[items[i].second];
        int itemWeight = weight[items[i].second];
        
        if(itemWeight + currentWeight <= capacity){
            boundProfit += itemPrice;
            currentWeight += itemWeight;            
        }else{
            boundProfit += (itemPrice * ((capacity - currentWeight) / itemWeight));
            currentWeight = capacity;
            break;
        }
    }
    
    return boundProfit;
}

int getMaxPriceBB(int capacity, vector<int> &price, vector<int> &weight){
    int n = price.size();
    
    vector<pair<double, int>> items;
    for(int i = 0; i < n; i++){
        items.push_back({(double)price[i] / weight[i] , i});
    }
    
    // sort the items in descending order
    sort(items.rbegin(), items.rend());
    
    // now we have to do bfs
    queue<Node> q;
    q.push(Node(-1, 0, 0));

    int maxProfit = 0;
    
    while(!q.empty()){
        Node &node = q.front();
        q.pop();
        
        if(node.weight <= capacity){
            maxProfit = max(node.profit, maxProfit);
        }
        
        // check if it is in last level
        if(node.level == n - 1) continue;

        // the idx for which we are dealing        
        int idx = node.level + 1;

        // take
        double takeBound = calculateBound(idx, node.profit + price[idx], node.weight + weight[idx], capacity, items, price, weight);
        if(takeBound > maxProfit){        
            q.push(Node(idx, node.profit + price[idx], node.weight + weight[idx]));
        }
        
        // leave
        double leaveBound = calculateBound(idx, node.profit, node.weight, capacity, items, price, weight);
        if(takeBound > maxProfit){        
            q.push(Node(idx, node.profit, node.weight));
        }
    }
    
    return maxProfit;
}

int main(){
    int n;
    
    cout << "Enter number of items: ";
    cin >> n;
    
    vector<int> price(n, 0), weight(n, 0);
    for(int i = 0; i < n; i++){
        cout << "Enter price and weight: ";
        cin >> price[i] >> weight[i];
    }
    
    int capacity;
    cout << "Enter the Capacity: ";
    cin >> capacity;
    
    // Do using dp and capacity
    int result = getMaxPrice(0, capacity, price, weight);
    int resultTab = getMaxPriceTabulation(capacity, price, weight);
    int resultBB = getMaxPriceBB(capacity, price, weight);
    
    cout << "Result: " << endl;
    cout << result << endl;
    cout << resultTab << endl;
    cout << resultBB << endl;
    
    return 0;
}
