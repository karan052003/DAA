#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    char val;
    int count;
    Node *left, *right;

    Node(char val, int count){
        this->val = val;
        this->count = count;
    }
};

class comp{
public:
    bool operator()(Node *a, Node *b){
        return a->count > b->count;
    }
};

void printCodes(Node *root, string &code){
    if(!root->left && !root->right){
        cout << root->val << ": " << code << endl;
        return;
    }
    
    if(root->left){
        code += "0";
        printCodes(root->left, code);
        code.pop_back();
    }
    
    if(root->right){
        code += "1";
        printCodes(root->right, code);
        code.pop_back();
    }
}

int main(){
    // Take word as input 
    string word = "karan is the best";
    
    // Count the frequency of each character
    unordered_map<char, int> count;    
    for(auto ch: word) count[ch]++;
    
    // Create nodes in tree
    priority_queue<Node *, vector<Node *>, comp> pq;
    for(auto p: count){
        pq.push(new Node(p.first, p.second));
    }
    
    // merge till only one node is remaining
    while(pq.size() > 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        
        Node *node = new Node('#', left->count + right->count);
        node->left = left;
        node->right = right;
        
        pq.push(node);
    }
        
    // Display the root
    Node *node = pq.top(); pq.pop();
    string codes = "";
    printCodes(node, codes);
    
    return 0;
}
