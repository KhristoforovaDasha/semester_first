#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>;
using std:: vector;
using std:: cout;
using std:: cin;
using std:: pair;
using std:: swap;
using std:: string;
using pairvector = pair<vector<int>,vector<int> >;
pairvector partition(vector <int>&a ,int x){
         vector <int> b,c;
         for(int elem : a){
             if(elem < x) b.push_back(elem);
             if(elem > x) c.push_back(elem);
         }
         return {b,c};
}
int QuickSelect(vector <int>& a,int k){
    if(a.size() == 1) return a[0];
    int x = a[rand()%a.size()];
    pairvector ans = partition(a,x);
    vector <int> b = ans.first;
    vector <int> c = ans.second;
    if(k < b.size()) return QuickSelect(b,k);
    if(k < a.size() - c.size()) return x;
    return QuickSelect(c,k - (a.size() - c.size()));
}
signed main() {
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(0));
    int tt = 1;
   // cin >> tt;
    while(tt--){
        int n,k;
        cin >> n >> k;
        vector <int> a(n);
        for(int& x : a) cin >> x;
        cout << QuickSelect(a,k);
    }
    return 0;
}


