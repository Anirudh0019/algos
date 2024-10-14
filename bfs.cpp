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

void bfs(vector<vector<int>>& list,int s){
    queue<int> q;
    vector<bool> visited(list.size(),false);

    visited[s] = true;
    q.push(s);
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        cout<<curr<<" ";

        for(int x: list[curr]){
            if(!visited[x]){
                visited[x] = true;
                q.push(x);
            }
        }
    }
}
void add(vector<vector<int>>& list,int u, int v){
    list[u].pb(v);
    list[v].pb(u);
}
int main(){
    fast_io();
    int v;
    cin>>v; // size of graph, end node?
    vector<vector<int>> list(v);

    for(int i=0;i<v;i++){
        int h,j;
        cin>>h>>j;
        add(list,h,j);
    }
    cout<<"BFS starts from 0"<<"\n";
    bfs(list,0);

    return 0;
}




