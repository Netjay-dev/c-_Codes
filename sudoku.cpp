#include<bits/stdc++.h>

using namespace std;
const int n = 9;

bool isValid(vector<vector<char>> &board, int row, int col, char c){
    board[row][col] = '.';
    for(int i = 0; i < n; ++i){
        if(board[row][i] == c || board[i][col] == c){
            return false;
        }
    }

    int a = (row / 3) * 3;
    int b = (col / 3) * 3;

    for(int i = a; i < a+3; ++i){
        for(int j = b; j < b+3; ++j){
            cout << i << ' ' << j << endl;
            if(board[i][j] == c){
                return false;
            }
        }
    }
    board[row][col] = c;
    return true;
}

bool isEmpty(vector<vector<char>> &board, int& row, int& col){
    for(int i  = 0; i < n; ++i){
        for(int j  = 0;j < n; ++j){
            if(board[i][j] == '.'){
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>> &board){
    int row = 0, col = 0;
    if(!isEmpty(board, row, col)){
        return;
    }

    for(int i = '1'; i <= '9'; ++i){
        if(isValid(board,row,col,(char)i)){
            solveSudoku(board);       
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    
    vector<vector<char>> inp(n,vector<char>(n));

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cin >> inp[i][j];

    solveSudoku(inp);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << inp[i][j];
        }
        cout << endl;
    }
}
