#include <bits/stdc++.h>
using namespace std;

void printGrid(const vector<vector<char>> &grid){
    for(auto row: grid){
        for(auto cell: row) cout << cell << " ";
        cout << endl;
    }
}

bool isPossibleToPlace(int row, int col, vector<vector<char>> &grid){
    int n = grid.size();
    
    // check in row 
    for(int c = 0; c < n; c++){
        if(grid[row][c] == 'Q') return false;
    }
    
    // check in col
    for(int r = 0; r < n; r++){
        if(grid[r][col] == 'Q') return false;
    }
    
    
    // check in diagonal up and down
    int i, j;
    
    i = row - 1;
    j = col - 1;
    while (i >= 0 && j >= 0) {
        if (grid[i][j] == 'Q') {
            return false;
        }
        --i;
        --j;
    }
    
    i = row + 1;
    j = col + 1;
    while (i < n && j < n) {
        if (grid[i][j] == 'Q') {
            return false;
        }
        ++i;
        ++j;
    }
    
    
    // check in reverse diagonal
    i = row - 1;
    j = col + 1;
    while (i >= 0 && j < n) {
        if (grid[i][j] == 'Q') {
            return false;
        }
        --i;
        ++j;
    }
    
    i = row + 1;
    j = col - 1;
    while (i < n && j >= 0) {
        if (grid[i][j] == 'Q') {
            return false;
        }
        ++i;
        --j;
    }

    return true;
}

void backtrack(int row, int rowPlaced, vector<vector<char>> &grid){    
    if(row == grid.size()){
        printGrid(grid);
        return;
    }
    
    // check if already placed in this row
    if(row == rowPlaced){
        backtrack(row + 1, rowPlaced, grid);
        return;
    }
    
    // col
    for(int col = 0; col < grid[row].size(); col++){
        if(isPossibleToPlace(row, col, grid)){            
            grid[row][col] = 'Q';
            
            backtrack(row + 1, rowPlaced, grid);
            
            grid[row][col] = '.';
        }
    }
}

int main(){
    int n;
    cout << "Enter the grid size: ";
    cin >> n;
    
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    
    // take row and column to place the queen
    int row, col;
    cout << "Enter row and col to place queen: ";
    cin >> row >> col;
    
    grid[row][col] = 'Q';
    
    // Print the initial grids
    cout << "Initial: " << endl;
    printGrid(grid);
    cout << endl;
    
    // Now backtrack and find the results
    cout << "Result: " << endl;
    backtrack(0, row, grid); 
    
    return 0;
}
