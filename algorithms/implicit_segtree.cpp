#include <iostream>
#include <vector>
#include <algorithm>
using ll = long long;
using namespace std;
int inf = 1e9 + 1;
struct node{
    ll sum;
    node* left = nullptr;
    node* right = nullptr;
    node(ll val): sum(val){};
};
struct segtree{
    node* root = new node(0);
    ll get_sum(node* vert){
        if(vert == nullptr) return 0;
        return vert->sum;
    }
    void add(int val,node*& vertex,int lx,int rx){
        if(rx - lx == 1){
            vertex->sum += val;
            return;
        }
        int m = (lx + rx)/2;
        if(val < m) {
            if(vertex->left == nullptr){
                node* cur = new node(0);
                vertex->left = cur;
            }
            add(val,vertex->left,lx,m);
        }
        else {
            if(vertex->right == nullptr){
                node* cur = new node(0);
                vertex->right = cur;
            }
            add(val,vertex->right,m,rx);
        }
        vertex->sum = get_sum(vertex->right) + get_sum(vertex->left);
    }
    void add(int val){
        add(val,root,0,inf);
    }
    ll get(int l,int r,node* vertex,int lx,int rx){
        if(vertex== nullptr) return 0;
        if(lx >= r || rx <= l) return 0;
        if(l <= lx && rx <= r) return vertex->sum;
        int m = (lx + rx)/2;
        ll s1 = get(l,r,vertex->left,lx,m);
        ll s2 = get(l,r,vertex->right,m,rx);
        return s1 + s2;
    }
    ll get(int l,int r){
        return get(l,r,root,0,inf);
    }
    ~segtree() {delete root;}
};

signed main() {
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
     int q;
     cin >> q;
     segtree tree;
     while(q--){
         char c;
         int x;
         cin >> c >> x;
         if(c == '+'){
            tree.add(x);
         }
         else{
           cout << tree.get(0,x + 1) <<endl;
         }
     }
     return 0;
}
