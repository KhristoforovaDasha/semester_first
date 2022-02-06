#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>;
using ll = long long;
using std:: vector;
using std:: cout;
using std:: cin;
using std:: pair;
using std:: swap;
using std:: string;
void siftup(vector<pair<ll,int> >& a,vector<int>& q,int v){
    while(v != 0){
        if(a[v].first < a[(v - 1)/2].first){
            swap(a[v],a[(v - 1)/2]);
            swap(q[a[v].second],q[a[(v - 1)/2].second]);
            v = (v - 1)/2;
        }
        else break;
    }
}
void siftdown(vector<pair<ll,int> >& a,vector<int>& q,int v){
    while(2*v + 1  < a.size()){
        int u = 2*v + 1;
        if(2*v + 2 < a.size() && a[2*v + 2].first < a[2*v + 1].first) u = 2*v + 2;
        if(a[u].first < a[v].first){
            swap(a[u],a[v]);
            swap(q[a[u].second],q[a[v].second]);
            v = u;
        }
        else break;
    }
}
void insert(vector <pair<ll,int> >&a,vector<int>& q,int x,int id){
    a.push_back({x,id});
    q[id] = a.size() - 1;
    siftup(a,q,a.size() - 1);
}
void decreaseKey(vector<pair<ll,int> >& a,vector<int>& q,int i,int delta){
       a[i].first -= delta;
       siftup(a,q,i);
}
void extractmin(vector<pair<ll,int> >& a,vector<int>& q){
    a[0] = a[a.size() -1];
    q[a[a.size() -1].second] = 0;
    a.pop_back();
    siftdown(a,q,0);
}
signed main() {
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector <pair<ll,int> > a;
    int tt = 1,id = 0;
     cin >> tt;
    vector <int> q(tt,-1);
    while(tt--){
       string command;
       cin >> command;
       if(command == "insert"){
             int x;
             cin >> x;
             insert(a,q,x,id);
       }
       else if(command == "decreaseKey"){
            int i,delta;
            cin >> i >> delta;
            i--;
            decreaseKey(a,q,q[i],delta);
       }
       else if(command == "getMin"){
           cout << a[0].first <<'\n';
       }
       else{
           extractmin(a,q);
       }
       //for(int i : q) cout << i <<" ";
      // cout << endl;
       id++;
    }
    return 0;
}

