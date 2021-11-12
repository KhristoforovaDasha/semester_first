#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>;
using ll = unsigned long long;
using std:: vector;
using std:: cout;
using std:: cin;
using std:: pair;
using std:: swap;
using std:: string;
void lsd_sort(vector<ll>& a){
    int n = a.size();
    ll d1 = 10,d2 = 1;
    vector <ll> ans(n);
    for(int i = 0; i < 19; ++i){
        vector <int> dig(10);
        for(int j = 1; j < n; ++j){
             dig[(a[j]%d1)/d2]++;
        }
        for(int j = 1; j < 10; ++j) dig[j] += dig[j - 1];
        for(int j = n - 1; j >= 1; --j) ans[dig[(a[j]%d1)/d2]--] = a[j];
        a = ans;
        d1 *= 10,d2 *=10;
    }
    for(int i = 1; i < n ; ++i) cout << ans[i] <<" ";
}
signed main() {
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
       int n;
       cin >> n;
       vector<ll> a(n + 1);
       for(int i = 1; i < n + 1; ++i) cin >> a[i];
       lsd_sort(a);
    }
    return 0;
}

