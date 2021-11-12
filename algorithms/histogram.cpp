#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stack>
#define int long long
using namespace std;
void func(vector <int>& a,vector <int>& ans,int l,int r,int d){
    stack <int> st;
    int i = l;
    while(i != r){
        while(!st.empty() && a[st.top()] >= a[i]) st.pop();
        if(!st.empty()){
            ans[i] = st.top();
        }
        else ans[i] = l - d;
        st.push(i);
        i += d;
    }
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,ans = 0;
    cin >> n;
    vector <int> a(n),ans1(n),ans2(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    func(a,ans1,0,n,1);
    func(a,ans2,n - 1, -1,-1);
    for(int i = 0; i < n; ++i){
        ans = max(ans,(ans2[i] - ans1[i] - 1)*a[i]);
    }
    cout << ans;
    return 0;
}

