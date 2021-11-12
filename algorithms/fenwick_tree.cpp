#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
using ll = long long;
using namespace std;
int n;
vector<vector<vector<ll> > > t;
void add(int x,int y,int z,int val){
    for(int i = x; i < n; i = (i|(i + 1))){
        for(int j = y; j < n; j = (j | (j + 1))){
            for(int g = z; g < n; g = (g | (g + 1))){
                t[i][j][g] += val;
            }
        }
    }
}
ll sum(int x,int y,int z){
    ll result = 0;
    for(int i = x; i >= 0; i = (i & (i + 1)) - 1){
        for(int j = y; j >= 0; j = (j & (j + 1)) - 1){
            for(int g = z; g >= 0; g = (g & (g + 1)) - 1){
                result += t[i][j][g];
            }
        }
    }
    return result;
}
ll sum(int x1,int y1,int z1,int x2,int y2,int z2){
   ll first =  sum(x2,y2,z2) - sum(x1 - 1,y2,z2) - sum(x2,y1 - 1,z2) + sum(x1 - 1,y1 - 1,z2);
   ll second = sum(x2,y2,z1 - 1) - sum(x1 - 1,y2,z1 - 1) - sum(x2,y1 - 1,z1 - 1) + sum(x1 - 1,y1 - 1,z1 - 1);
   return first - second;
}
signed main() {
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
     int m;
     cin >> n;
     t = vector<vector<vector<ll> > >(n,vector<vector<ll> > (n,vector<ll> (n,0)));
     while(cin >> m){
         if(m == 3) break;
         if(m == 1){
             int x,y,z,val;
             cin >> x >> y >> z >> val;
             add(x,y,z,val);
         }
         else {
             int x1,x2,y1,y2,z1,z2;
             cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
             cout << sum(x1,y1,z1,x2,y2,z2) <<'\n';
         }
     }
     return 0;
}
