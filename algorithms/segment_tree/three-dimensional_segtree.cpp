#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#define int long long
using namespace std;
struct segtree{
    vector <vector<vector<int> > > tree;
    int size;
    int zero = 0;
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree = vector <vector<vector<int> > > (2*size - 1,vector <vector<int>>(2*size - 1,vector <int>(2*size - 1,0)));
    }
    int sum_y(int vz,int vx,int l,int r,int vy,int ly,int ry){
        if(l >= ry || r <= ly) return 0;
        if(l <= ly && ry <= r) return tree[vz][vx][vy];
        int my = (ly + ry)/2;
        return sum_y(vz,vx,l,r,2*vy + 1,ly,my) + sum_y(vz,vx,l,r,2*vy+2,my,ry);
    }
    int sum_x(int vz,int vx,int l,int r,int lx,int rx,int ly,int ry){
       if(l >= rx || r <= lx) return 0;
       if(l <= lx && rx <= r) return sum_y(vz,vx,ly,ry,0,0,size);
       int mx = (lx + rx)/2;
       return sum_x(vz,2*vx + 1,l,r,lx,mx,ly,ry) + sum_x(vz,2*vx + 2,l,r,mx,rx,ly,ry);
    }
    int sum_z(int vz,int l,int r,int lz,int rz,int lx,int rx,int ly,int ry){
        if(l >= rz || r <= lz) return 0;
        if(l <= lz && rz <= r) return sum_x(vz,0,lx,rx,0,size,ly,ry);
        int mz = (lz + rz)/2;
        return sum_z(2*vz + 1,l,r,lz,mz,lx,rx,ly,ry) + sum_z(2*vz + 2,l,r,mz,rz,lx,rx,ly,ry);
    }
    int get(int lz,int rz,int lx,int rx,int ly,int ry){
        return sum_z(0,lz,rz,0,size,lx,rx,ly,ry);
    }
    void update_y(int vz,int lz,int rz,int vx,int lx,int rx,int vy,int ly,int ry,int x,int y,int z,int val){
        if(ry - ly == 1){
            if(rx - lx == 1)
                if(rz - lz == 1) tree[vz][vx][vy] += val;
                else tree[vz][vx][vy] = tree[2*vz + 1][vx][vy] + tree[2*vz + 2][vx][vy];
            else
                if(rz - lz == 1) tree[vz][vx][vy] = tree[vz][2*vx + 1][vy] + tree[vz][2*vx + 2][vy];
                else tree[vz][vx][vy] =  tree[vz * 2 + 1][vx * 2 + 1][vy] + tree[vz * 2 + 2][vx * 2 + 1][vy] +
                                         tree[vz * 2 + 1][vx * 2 + 2][vy] + tree[vz * 2 + 2][vx * 2 + 2][vy];
            return;
        }
        else{
            int my = (ly + ry)/2;
            if(y < my) update_y(vz,lz,rz,vx,lx,rx,2*vy + 1,ly,my,x,y,z,val);
            else update_y(vz,lz,rz,vx,lx,rx,2*vy + 2,my,ry,x,y,z,val);
            tree[vz][vx][vy] = tree[vz][vx][2*vy + 1] + tree[vz][vx][2*vy + 2];
        }
    }
    void update_x(int vz,int lz,int rz,int vx, int lx, int rx, int x, int y,int z, int val){
        if(rx - lx != 1){
            int mx = (lx + rx)/2;
            if(x < mx) update_x(vz,lz,rz,2*vx + 1,lx,mx,x,y,z,val);
            else update_x(vz,lz,rz,2*vx + 2,mx,rx,x,y,z,val);
        }
        update_y(vz,lz,rz,vx,lx,rx,0,0,size,x,y,z,val);
    }
    void update_z(int vz,int lz,int rz,int x,int y,int z,int val){
        if(rz - lz != 1){
            int mz = (lz + rz)/2;
            if(z < mz) update_z(2*vz + 1,lz,mz,x,y,z,val);
            else update_z(2*vz + 2,mz,rz,x,y,z,val);
        }
        update_x(vz,lz,rz,0,0,size,x,y,z,val);
    }
    void update(int x,int y,int z,int val){
        update_z(0,0,size,x,y,z,val);
    }
    //void print() {for(int i = 0; i < 15; ++i) cout << tree[i].mx <<" " << tree[i].mn <<endl;};
};
signed main() {
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
     int n;
     int m;
     cin >> n;
     segtree tree;
     tree.init(n + 1);
     while(true){
         cin >> m;
         if(m == 3) break;
         if(m == 1){
             int x,y,z;
             int k;
             cin >> x >> y >> z >> k;
             tree.update(x,y,z,k);
         }
         else{
             int x1,x2,y1,y2,z1,z2;
             cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
             cout << tree.get(z1,z2 + 1,x1,x2 + 1,y1,y2 + 1)<<'\n';
         }
     }
     return 0;
}
