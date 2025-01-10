#include<bits/stdc++.h>
#define mp make_pair
#define FOR(i,a) for(int i=0;i<a;i++)
#define ll long long
#define fast_io  std::ios::sync_with_studio(false),cin.tie(NULL),cout.tie(NULL)
using namespace std;
int inf = 1e9+7;
int MOD = 1e9+7;
// wow this is com
int reff = 1;
struct Tree{
    public:
        bool isLocked;
        int id;
        int mask;
        int lockedDescCount;
        int lockedAncestorCount;
        unordered_map<int,int> map;

        volatile int s = 1;
        volatile bool flag;
        Tree* p;
        vector<Tree*> c;
        Tree(){

            isLocked = false;
            id =-1;
            mask = reff++;
            p = NULL;
            lockedDescCount = 0;
            lockedAncestorCount = 0;
            flag = false;
        }
        Tree(Tree* parent){
            isLocked = false;

            id -=1;
            mask = reff++;
            p = parent;
            lockedDescCount = 0;
            lockedAncestorCount = 0;
            flag = false;
        }
        void wait(){
            if(s<=0){
                // do nothing
                for(int i=0;i<10000;){
                    i++;
                }
            }
            s--;
        }
        void signal(){
            s++;
        }
        void lock(bool& flag){
            while(flag){

            }
            flag = true;
        }
        void release(bool& flag){
            flag = false;
        }
        // Node->p this gives me its parent

};
// O(N) no. of nodes 
// O() level = h , (m)^(h-1)
// O(log N base m)
// lockedDescCoutn, lockedAncCount
unordered_set<Tree&> set;

bool locking(Tree* n,int unique_id){
    int size = set.size();
    set.insert(&n);
    if(set.size()==size) return false;
    // logic to remove/dec is missing
    
    n->wait(); // makes it so that any thread having working on n will not be able to do a wait(),
    if((n->isLocked)) return false; 
    cout<<"passsed isLocked"<<endl;
    if(n->lockedDescCount > 0) return false; 
    cout<<"reached post initial check"<<"\n";
    n->signal();


    int ancCount = 0;
    Tree* current =n->p; 
    while(current){
        if(current->isLocked) ancCount++;
        current->map[unique_id]++;
        current=current->p;
    }

    n->lockedAncestorCount  = ancCount;
    cout<<"ancestor count = "<<ancCount<<" \n";
    
    if(n->lockedAncestorCount > 0) return false;
    current =n->p;
    while(current){

        current->lockedDescCount++;    
        current=current->p;
    }
    cout<<"descendent count = "<<n->lockedDescCount<<"\n ";

    n->wait();
    if(n->id==-1){
    n->id = unique_id;
    n->isLocked = true;
    }
    n->signal();
    return true;
}

bool unlocking(Tree* n,int unique_id){
    if( n->isLocked == false || (n->isLocked && unique_id != n->id)) return false;
    // cout<<"passing initial check"<<"\n";
    
    n-> isLocked = false;
    n->id = -1;

    Tree* current = n->p;
    while(current){
      current->lockedDescCount--;
      current->map[unique_id]--;
      if(current->map[unique_id] == 0)current->map.erase(unique_id);
      current = current->p;
    }
    cout<<"unlocked a child"<<"\n";
    return true;
}
/*

any desc locked by same id

*/
//O(N log N)
//O(W)
bool upgrade(Tree* n,int unique_id){
    if(n->isLocked == true) return false;
    Tree* T = n;

    unordered_map<int,int> freqMap = T->map;
    int id;
    for(auto& x:freqMap){
        id = x.first;
    }
    if(freqMap.size()>1) return false; 
    cout<<" passed size check"<<"\n";
    if( freqMap.size() != 0 && id!=unique_id ) return false; //atleast 1 & only 1
    cout<<"passed the check ******************"<<"\n";
    queue<Tree*> q;
    // q.push(T);
    // bool f = false;
    // while(!q.empty()){
    //     Tree* tmp = q.front();
    //     q.pop();
    //     for(auto j: tmp->c){
    //         if(j->isLocked == true && j->id!= unique_id)return false;
    //         if(j->isLocked) f = true;
    //         q.push(j);
    //     }
    // }
   
    // if(!f){
    //     return false;
    // }
    q.push(T);
    while(!q.empty()){ //N* H(N Log N)
        Tree* tmp = q.front();
        q.pop();
        for(auto j: tmp->c){
            if(j->isLocked){
                if(!unlocking(j,unique_id))return false; //H
            }
            q.push(j);
        }
    }
    return locking(n,unique_id); // N
}

void printTree(Tree* n){
    queue<Tree*> q;
    q.push(n);
    while(!q.empty()){
        Tree* tmp = q.front();
        q.pop();
        for(auto j: tmp->c){
            cout<<tmp->mask << " -> " << j->mask <<" ";
        }
    }
}
unordered_map<string,Tree*> stringOfTrees;
int main() {
    int n,m,q;
    cin>>n>>m>>q;

    Tree* t = new Tree();
    string d;
    cin>>d;
    stringOfTrees[d] = t;
    queue<Tree*> queue;
    queue.push(t);
    int k = 1;
    while(!queue.empty()){
        auto tmp = queue.front();
        queue.pop();
        while( k < n && (int)tmp->c.size() < m){
            string s;
            cin>>s;
            Tree* u = new Tree(tmp);
            stringOfTrees[s] = u;
            tmp->c.push_back(u);
            queue.push(u);
            k++;
        }
    }
    
    //Print(t)
    FOR(i,q){
        int query_n,unique_id;
        string name;
        bool ans;
        cin>>query_n>>name>>unique_id;
        if(query_n == 1){ // for locking
            ans = locking(stringOfTrees[name],unique_id);
            cout<<"locked "<<"\n";
        }else if(query_n == 2){
            ans = unlocking(stringOfTrees[name],unique_id);
            cout<<"unlocked "<<"\n";
        }else{
            ans = upgrade(stringOfTrees[name],unique_id);
            cout<<"in upgrade"<<"\n";
        }

        if(ans) cout<<"true"<<"\n";
        else cout<<"false"<<"\n";
    }
    return 0;
}
