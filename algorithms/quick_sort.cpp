#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using std:: vector;
using std:: cout;
using std:: cin;
using std:: pair;
using std:: swap;
using std:: string;
using std:: min;
using pairvector = pair<vector<int>,vector<int> >;
pairvector partition(vector <int>&a ,int x){
    vector <int> b,c;
    for(int elem : a){
        if(elem < x) b.push_back(elem);
        if(elem > x) c.push_back(elem);
    }
    return make_pair(b,c);
}
int QuickSelect(vector <int>& a,int k){
    size_t n = a.size();
    if(n == 1) return a[0];
    vector <int> d;
    for(size_t i = 0; i < n; i += 5){
        vector <int> cnt;
        for(size_t j = i; j < min(i + 5,n); ++j) cnt.push_back(a[j]);
        sort(cnt.begin(),cnt.end());
        d.push_back(cnt[cnt.size()/2]);
    }
    //for(int m : d) cout << m <<" ";
    int x = QuickSelect(d,n/10);
    pairvector ans = partition(a,x);
    if(k < ans.first.size()) return QuickSelect(ans.first,k);
    if(k < a.size() - ans.second.size()) return x;
    return QuickSelect(ans.second,k - (a.size() - ans.second.size()));
}

void qsort(vector<int>& a){
    if(a.size() <= 1) return;
    int x = QuickSelect(a,(a.size()-1)/2);
    vector <int> b,c,d;
    for(size_t i = 0;i < a.size(); ++i){
        if(a[i] < x) b.push_back(a[i]);
        else if(a[i] > x) c.push_back(a[i]);
        else d.push_back(a[i]);
    }
    qsort(b);
    qsort(c);
    a.clear();
    for(int elem : b) a.push_back(elem);
    for(int elem : d) a.push_back(elem);
    for(int elem : c) a.push_back(elem);
}
signed main() {
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    srand(time(0));
    while(tt--){
        int n;
        cin >> n ;
        vector <int> a(n);
        for(int& x : a) cin >> x;
        qsort(a);
        for(int x : a) cout << x <<" ";
    }
    return 0;
}
