#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using ll = long long;
using namespace std;
struct node{
    int x1,y1,y2,type;
};
struct segtree {
    int size;
    struct segment{
        int min,count,add;
    };
    vector <segment> tree;
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size - 1,{0,0,0});
    }
    void build(vector<int>& a,int x,int lx,int rx){
        if(rx - lx == 1){
            if(lx < a.size()) tree[x] = {0,a[lx],0};
            return;
        }
        int m = (lx + rx)/2;
        build(a,2*x + 1,lx,m);
        build(a,2*x + 2,m,rx);
        tree[x].count = tree[2*x + 1].count + tree[2*x + 2].count;
    }
    void build(vector <int>& a){
        init(a.size());
        build(a,0,0,size);
    }
    void propagate(int x,int lx,int rx){
        if(tree[x].add == 0 || rx - lx == 1) return;
        tree[2*x + 1].min += tree[x].add;
        tree[2*x + 2].min += tree[x].add;
        tree[2*x + 1].add += tree[x].add;
        tree[2*x + 2].add += tree[x].add;
        tree[x].add = 0;
    }
    void add(int l,int r,int val,int x,int lx,int rx){
        propagate(x,lx,rx);
        if(r <= lx || rx <= l) return;
        if(l <= lx && rx <= r){
            tree[x].min += val;
            tree[x].add += val;
            return;
        }
        int m = (lx + rx)/2;
        add(l,r,val,2*x + 1,lx,m);
        add(l,r,val,2*x + 2,m,rx);
        if(tree[2*x + 1].min < tree[2*x + 2].min){
            tree[x].min = tree[2*x + 1].min;
            tree[x].count = tree[2*x + 1].count;
        }
        else if(tree[2*x + 2].min < tree[2*x + 1].min){
            tree[x].min = tree[2*x + 2].min;
            tree[x].count = tree[2*x + 2].count;
        }
        else{
            tree[x].min = tree[2*x + 2].min;
            tree[x].count = tree[2*x + 2].count + tree[2*x + 1].count;
        }
    }
    void add(int l,int r,int val){
        add(l,r,val,0,0,size);
    }
    segment combain(segment first,segment second){
        if(first.min < second.min) return first;
        else if(second.min < first.min) return second;
        else {
            return {first.min,first.count + second.count,0};
        }
    }
    segment get(int l,int r,int x,int lx,int rx){
           propagate(x,lx,rx);
           if(rx <= l || r <= lx) return {INT_MAX,0,0};
           if(l <= lx && rx <= r) return tree[x];
           int m = (lx + rx)/2;
           segment m1 = get(l,r,2*x + 1,lx,m);
           segment m2 = get(l,r,2*x + 2,m,rx);
           return combain(m1,m2);
    }
    segment get(int l,int r){
        return get(l,r,0,0,size);
    }
};
bool comp(node a,node b){
    if(a.x1 == b.x1) return a.type < b.type;
    return a.x1 < b.x1;
}
bool comp1(pair<int,int> a,pair<int,int> b){
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}
int main() {
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
     int n;
     cin >> n;
     if(n == 0) {
         cout << 0;
         return 0;
     }
     vector<node> elem;
     vector <pair<int,int> > point;
     for(int i = 0; i < n; ++i){
         int x1,x2,y1,y2;
         cin >> x1 >> y1 >> x2 >> y2;
         elem.push_back({x1,y1,y2,1});
         elem.push_back({x2 ,y1,y2,-1});
         point.push_back({y1,1});
         point.push_back({y2,-1});
     }
     sort(elem.begin(),elem.end(),comp);
     sort(point.begin(),point.end(),comp1);
     int cur = 0;
     map <int,int> mp;
     for(int i = 0; i < point.size(); ++i){
         if(i && point[i].first!= point[i - 1].first) {
             cur++;
         }
         mp[point[i].first] = cur;
     }
     vector <int> tree_elem;
     for(int i = 1;i < point.size(); ++i){
         if(point[i].first != point[i - 1].first) tree_elem.push_back(point[i].first - point[i-1].first);
     }
      segtree tree;
     tree.build(tree_elem);
     ll ans = 0,len = point[point.size() - 1].first - point[0].first;
     for(int i = 0; i < elem.size(); ++i){
         segtree:: segment res = tree.get(0,tree.tree.size());
         if(i) {
             ans += 1ll*(elem[i].x1 - elem[i - 1].x1)*len;
             if(res.min == 0) {
                 ans -= 1ll*(elem[i].x1 - elem[i - 1].x1)*res.count;
             }
         }
         tree.add(mp[elem[i].y1],mp[elem[i].y2] ,elem[i].type);
     }
     cout << ans <<'\n';
     return 0;
}
