#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
using ll = long long;
using namespace std;
struct segtree{
    vector <vector<int> > tree;
    int size;
    int zero = 0;
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree = vector <vector<int> > (2*size - 1,vector <int>(2*size - 1,0));
    }
    int sum_y(int vx,int l,int r,int vy,int ly,int ry){
        if(l >= ry || r <= ly) return 0;
        if(l <= ly && ry <= r) return tree[vx][vy];
        int my = (ly + ry)/2;
        return sum_y(vx,l,r,2*vy + 1,ly,my) + sum_y(vx,l,r,2*vy+2,my,ry);
    }
    int sum_x(int vx,int l,int r,int lx,int rx,int ly,int ry){
       if(l >= rx || r <= lx) return 0;
       if(l <= lx && rx <= r) return sum_y(vx,ly,ry,0,0,size);
       int mx = (lx + rx)/2;
       return sum_x(2*vx + 1,l,r,lx,mx,ly,ry) + sum_x(2*vx + 2,l,r,mx,rx,ly,ry);
    }
    int get(int lx,int rx,int ly,int ry){
        return sum_x(0,lx,rx,0,size,ly,ry);
    }
    void update_y(int vx,int lx,int rx,int vy,int ly,int ry,int x,int y,int val){
        if(ry - ly == 1){
            if(rx - lx == 1) tree[vx][vy] += val;
            else tree[vx][vy] = tree[2*vx + 1][vy] + tree[2*vx + 2][vy];
        }
        else{
            int my = (ly + ry)/2;
            if(y < my) update_y(vx,lx,rx,2*vy + 1,ly,my,x,y,val);
            else update_y(vx,lx,rx,2*vy + 2,my,ry,x,y,val);
            tree[vx][vy] = tree[vx][2*vy + 1] + tree[vx][2*vy + 2];
        }
    }
    void update_x(int vx, int lx, int rx, int x, int y, int val){
        if(rx - lx != 1){
            int mx = (lx + rx)/2;
            if(x < mx) update_x(2*vx + 1,lx,mx,x,y,val);
            else update_x(2*vx + 2,mx,rx,x,y,val);
        }
        update_y(vx,lx,rx,0,0,size,x,y,val);
    }
    void update(int x,int y,int val){
        update_x(0,0,size,x,y,val);
    }
    //void print() {for(int i = 0; i < 15; ++i) cout << tree[i].mx <<" " << tree[i].mn <<endl;};
};
signed main() {
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
     short int n;
     int m;
     cin >> n;
     vector <segtree> tree(n);
     for(int i = 0; i < n; ++i) {
         tree[i].init(n);
     }
     while(true){
         cin >> m;
         if(m == 3) break;
         if(m == 1){
             short int x,y,z,k;
             cin >> x >> y >> z >> k;
             tree[z].update(x,y,k);
         }
         else{
             short int x1,x2,y1,y2,z1,z2;
             ll ans = 0;
             cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
             for(short int z = z1; z <= z2; ++z){
                ans += tree[z].get(x1,x2 + 1,y1,y2 + 1);
             }
             cout << ans <<'\n';
         }
     }
     return 0;
}
