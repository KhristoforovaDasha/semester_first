#include <iostream>
#include <vector>
#include <algorithm>
using ll = long long;
using namespace std;
pair<int,int> getAns(vector<vector<pair<int,int> > >& sparse,vector<int>& log,int l,int r){
    int level = log[r - l + 1];
    if(sparse[level][l].first < sparse[level][r - (1 << level) + 1].first) return sparse[level][l];
    return sparse[level][r - (1 << level) + 1];
}
signed main() {
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
     int n,m,l = 0,len;
     cin >> n >> m;
     len = n;
     while(len) len/= 2,l++;
     vector <int> elem(n);
     for(int& x: elem) cin >> x;
     vector<vector<pair<int,int> > > sparse(l + 1);
     vector<int> log(n + 1);
     sparse[0].resize(n);
     int log_cur = 0;
     for(int i = 1; i < n + 1; ++i){
         if((1 <<(log_cur + 1))<= i) log_cur++;
         log[i] = log_cur;
     }
     for(int i = 0; i < n; ++i) sparse[0][i] = {elem[i],i};
    for(int k = 0; k < l; ++k){
        sparse[k + 1].resize(--n);
        for(int i = 0; i < n; ++i){
            if(sparse[k][i].first < sparse[k][min(n,i + (1 << k))].first)
                sparse[k + 1][i] = sparse[k][i];
            else sparse[k + 1][i] = sparse[k][min(n,i + (1 << k))];
        }
    }
    /*for(int k = 0; k < l + 1; ++k){
        for(int i = 0; i < sparse[k].size(); ++i){
            cout << sparse[k][i].first <<" ";
        }
        cout << endl;
    }*/
     while(m--){
         int l,r;
         cin >> l >> r;
         l--,r--;
         int first = 1e18,second = 1e18;
         int pos = getAns(sparse,log,l,r).second;
         if(l != pos) first = getAns(sparse,log,l,pos - 1).first;
         if(r != pos) second = getAns(sparse,log,pos + 1,r).first;
         cout << min(first,second) <<'\n';
     }
     return 0;
}
