#include<iostream>
#include<vector>
#include<iostream>
#include<string>
#include<bits/stdc++.h>
#define pb push_back
#define mod 1000000007
#define vr vector
#define ll long long
#define fast_io ios::sync_with_stdio(false)
#define all(x) (x).begin(), (x).end()
#define fr(k,n) for(int i = k; i < n; i++) 

using namespace std;
int n,m;
bool vis[12][12];

vector<string>ans;

struct trie
{
    bool isleaf;
    trie *chd[26];
};

trie* create()
{
    trie* node = new trie;
    node->isleaf = false;
    for(int i = 0; i < 26; ++i)
        node->chd[i] = nullptr;
    return node;
}

void insert(trie*&head,string s)
{
    if(head==nullptr)
        head = create();
    trie *cur = head;
    for(char c : s)
    {
        if(cur->chd[c-'a']==nullptr)
            cur->chd[c-'a'] = create();
        cur = cur->chd[c-'a'];
    }
    cur->isleaf = true;
}

void dfs(trie*head,vector<vector<char>>&board, string s, int row, int col)
{
    if(row>n || row < 0 || col > m || col < 0 || vis[row][col] || head->chd[board[row][col]-'a']==nullptr){
        return;
    }
    s.push_back(board[row][col]);
    vis[row][col] = 1;
    if(head->chd[board[row][col]-'a']->isleaf) ans.push_back(s);
    head = head->chd[board[row][col]-'a'];
    dfs(head,board,s,row+1,col);
    dfs(head,board,s,row-1,col);
    dfs(head,board,s,row,col+1);
    dfs(head,board,s,row,col-1);
}
vector<string> findWords(vector<vector<char>>&board,vector<string>&words)
{
    n = board.size();
    m = board[0].size();
    
    trie* head = nullptr;
    for(string &s : words)
    {
        insert(head,s);
    }

    for(int row = 0; row < n; ++row)
    {
        for(int col = 0; col < m; ++col)
        {
            memset(vis,false,sizeof(vis));
            dfs(head,board,"",row,col);
        }
        cout << endl;
    }
    return ans;
}

int main()
{
    fast_io;
    cin.tie(0);

    int a, b;
    cin >> a >> b;
    vector<vector<char>>board(a,vector<char>(b));

    for(int row = 0; row < a; ++row)
    {
        for(int col = 0; col < b; ++col)
        {
            cin >> board[row][col];
        }
    }
    
    int k;
    cin >> k;
    vector<string>words(k);
    for(int i = 0; i < k; ++i)
    {
        cin >> words[i];
    }

    vector<string>ans = findWords(board,words);
    for(auto c : ans) cout << c << ' ';
}

