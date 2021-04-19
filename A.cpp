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

struct trie
{
    bool isleaf;
    trie *child[26];
    trie() : isleaf(false)
    {
        for(int i = 0; i < 26; ++i)
        {
            child[i] = nullptr;
        }
    }
};

unordered_map<string,bool>rf;
void insert(trie*&head,string s)
{
    if(head == nullptr)
    {
        head = new trie();
    }
    trie*cur = head;
    for(char c : s)
    {
        if(cur->child[c-'a']==nullptr)
        {
            cur->child[c-'a'] = new trie();
        }
        cur = cur->child[c-'a'];
    }
    cur->isleaf = true;
}

void search(trie*head,vector<vector<bool>>vis, vector<string>&ans,vector<vector<char>>&board,int row,int col,string s)
{
    int n = board.size(), m = board[0].size();
    if(head->child[board[row][col]-'a']!=nullptr)
    {
        s.push_back(board[row][col]);
        if(head->child[board[row][col]-'a']->isleaf)
        {
            ans.push_back(s);
        }
        vis[row][col] = 1;
        if(col+1<m&&!vis[row][col+1]) search(head->child[board[row][col]-'a'],vis,ans,board,row,col+1,s);
        if(row+1<n&&!vis[row+1][col]) search(head->child[board[row][col]-'a'],vis,ans,board,row+1,col,s);
        if(col-1>0&&!vis[row][col-1]) search(head->child[board[row][col]-'a'],vis,ans,board,row,col-1,s);
        if(row-1>0&&!vis[row-1][col]) search(head->child[board[row][col]-'a'],vis,ans,board,row-1,col,s);
    }
}

vector<string> findWords(vector<vector<char>>&board,vector<string>&words)
{
    trie *head = nullptr;
    int n = board.size(), m = board[0].size();

    for(string s: words) insert(head,s);
    vector<string>ans;

    trie *cur = head;
    for(int row = 0; row < n; ++row)
    {
        for(int col = 0; col < m; ++col)
        {
            if(cur->child[board[row][col]-'a']!=nullptr)
            {
                vector<vector<bool>>vis(n,vector<bool>(m,false));
                string s = "";
                search(cur,vis,ans,board,row,col,s);
            }
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<char>>board(n,vector<char>(m));
    for(int row = 0; row < n; ++row)
    {
        for(int col = 0; col < m; ++col)
        {
            cin >> board[row][col];
        }
    }

    int k;
    cin >> k;
    vector<string>words(k);
    for(string &s : words)
        cin >> s;

    vector<string> ans = findWords(board,words);

    for(string &s : ans) cout << s << ' ';
}
