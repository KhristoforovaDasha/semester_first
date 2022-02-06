#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector <int> sum(vector <int>& a,vector <int>& b){
    int last = 0;
    vector <int> c(a.size());
    for(int i = 0; i < (int)a.size() - 1; ++i){
        int cnt = a[i] + b[i] + last;
        c[i] = cnt%10;
        last = cnt/10;
    }
    if(last != 0) c[a.size() - 1] = last,c.push_back(a[a.size() - 1]);
    else c[a.size() - 1] = a[a.size() - 1];
    return c;
}
bool compare(vector <int>& a,vector <int>& b){
    for(int i = a.size() - 2; i >= 0; --i){
        if(a[i] < b[i]) return 1;
        else if(a[i] > b[i]) return 0;
    }
    return 0;
}
vector <int> sub(vector <int> a,vector <int> b){
    int last = 0,sza = a.size();
    vector <int> c(a.size());
    bool f = compare(a,b);
    if(a[sza - 1] == -1) c[sza - 1] = (f == 1 ? 1 : -1);
    else c[sza - 1] = (f == 1 ? -1 : 1);
    if(f) swap(a,b);
    for(int i = 0; i < a.size() - 1; ++i){
        int cnt = a[i] - b[i] + last;
        if(last && a[i] == 0) cnt += 10;
        if(cnt >= 0) {
            c[i] = cnt;
            if(a[i]) last = 0;
        }
        else c[i] = 10 + cnt,last = -1;
    }
    return c;
}
vector <int> div(vector <int>& a,bool flag,int s1,int s2){
    int last = 0;
    vector <int> c;
    c.push_back(a[0]);
    for(int i = 1; i < a.size(); ++i){
        c.push_back((last*10 + a[i])/2);
        last = (last*10 + a[i])%2;
    }
    if(last){
        vector <int> a(c.size());
        a[0] = 1;
        reverse(c.begin(),c.end());
        if( !flag && s1 == -1) {
            a[a.size() - 1] = -1;
            if(a[a.size() - 1] == c[a.size() - 1]) c = sum(c,a);
            else c = sub(c,a);
        }
        else if(!flag && s1 == 1){
            a[a.size() - 1] = 1;
            if(a[a.size() - 1] == c[a.size() - 1]) c = sum(c,a);
            else c = sub(c,a);
        }

        reverse(c.begin(),c.end());
    }
    return c;
}
vector <int> mt(string a,string b){
    int sza = a.size(),szb = b.size();
    vector<int> aa(sza - (a[0] == '-')),bb(szb - (b[0] == '-')),c;
    int mx = max(aa.size(),bb.size()),id1 = 0,id2 = 0;
    for(int i = sza - 1; i >= (a[0] == '-'? 1 : 0);--i) aa[id1] = a[i] - '0',id1++;
    for(int i = szb - 1; i >= (b[0] == '-'? 1 : 0);--i) bb[id2] = b[i] - '0',id2++;
    while(aa.size() != mx) aa.push_back(0);
    while(bb.size() != mx) bb.push_back(0);
    if(b[0] == '-') bb.push_back(-1);
    else bb.push_back(1);
    if(a[0] == '-') aa.push_back(-1);
    else aa.push_back(1);
    if(aa[mx] == bb[mx]) c = sum(aa,bb);
    else c = sub(aa,bb);
    reverse(c.begin(),c.end());
    c = div(c,compare(aa,bb),aa[aa.size() - 1],bb[bb.size() - 1]);
    return c;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string a,b;
    bool f = 0;
    cin >> a >> b;
    vector <int> ans = mt(a,b);
    if(ans[0] == -1) cout <<'-';
    for(int i = 1; i < ans.size(); ++i) {
        if(ans[i]) f = 1;
        if(f) cout << ans[i];

    }
    return 0;
}

