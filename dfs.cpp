#include <bits/stdc++.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define ll long long
#define pb push_back

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
void recurse(vector<vector<int>> list,vector<bool> visited,int node){
    visited[node]= true;
    cout<<node<<" ";
    for(int i: list[node]){
        if(!visited[i]){
            recurse(list,visited,i);
        }
    }
}

void add(vector<vector<int>>& list,int u,int v){
    list[u].pb(v);
    list[v].pb(u);
}
void dfs(vector<vector<int>>& list,int node){
    vector<bool> visited(list.size(),false);
    recurse(list,visited,node);
}
int main(){
    fast_io();
    int v = 5;
    vector<vector<int>> list(v);

    vector<vector<int>> edges = {{1, 2},{1, 0},{2, 0},{2, 3},{2, 4}};

    for(auto &e:edges){
        add(list,e[0],e[1]);
    }
    int starting = 0;
    cout<<"DFS from source "<<starting<<endl;
    dfs(list,starting);

    return 0;
}
