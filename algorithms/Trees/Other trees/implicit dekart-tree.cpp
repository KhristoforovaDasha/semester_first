#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
using ll = long long;
using std:: string;
using std:: cin;
using std:: cout;
using std:: vector;
using std:: queue;
using std:: pair;
struct node{
    ll y,value,size = 1,sum;
    node* left = nullptr;
    node* right = nullptr;
    node(int prior_,int value_,int cnt_):y(prior_),value(value_),sum(value*value){}
};
int cnt(node* it){
    return it ? it->size : 0;
}
ll sum(node* it){
    return it ? it->sum : 0;
}
void upd_cnt(node*& it){
    if(it) it->size = cnt(it->left) + cnt(it->right) + 1;
    if(it) it->sum = sum(it->left) + sum(it->right) + it->value*it->value;
}
node* merge(node* left,node* right){
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    if(right->y > left->y){
        right->left = merge(left,right->left);
        upd_cnt(right);
        return right;
    }
    else{
        left->right = merge(left->right,right);
        upd_cnt(left);
        return left;
    }
}
void split(node* root,node*& l,node*& r,int key,int add = 0){
    if(root == nullptr){
        r = l = nullptr;
        return;
    }
    int cur_key = add + cnt(root->left);
    if(key <= cur_key){
        split(root->left,l,root->left,key,add);
        r = root;
    }
    else{
        split(root->right,root->right,r,key,add + 1 + cnt(root->left));
        l = root;
    }
    upd_cnt(root);
}
node* insert(node* root,int pos,int value){
    node *l,*r;
    split(root,l,r,pos);
    node* m = new node({rand(),value,pos});
    return merge(merge(l,m),r);
}
int elem;
void add(node*& root,int value,int pos,int ad = 0){
    int cur_key = ad + cnt(root->left);
    if(cur_key < pos) add(root->right,value,pos,ad + cnt(root->left) + 1);
    else if(cur_key > pos)add(root->left,value,pos,ad);
    else{
        root->value += value;
    }
    upd_cnt(root);
}
void erase(node*& root,int pos,int add = 0){
    int cur_key = add + cnt(root->left);
    if(cur_key < pos) erase(root->right,pos,add + cnt(root->left) + 1);
    else if(cur_key > pos) erase(root->left,pos,add);
    else{
        elem = root->value;
        root = merge(root->left,root->right);
    }
    upd_cnt(root);
}
int get(node* root,int pos,int add = 0){
    int cur_key = add + cnt(root->left);
    if(cur_key < pos) return get(root->right,pos,add + cnt(root->left) + 1);
    else if(cur_key > pos) return get(root->left,pos,add);
    else return root->value;
}
int main(){
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    freopen("river.in","r",stdin);
    freopen("river.out","w",stdout);
    srand(time(0));
    int n, p;
    cin >> n >> p;
    vector <int> a(n);
    node* root = nullptr;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        root = insert(root,i,a[i]);
    }
    int k;
    cin >> k;
    cout << root->sum <<'\n';
    while(k--){
        int e,v;
        cin >> e >> v;
        if(e == 1){
            erase(root,v - 1);
            if(v == 1) add(root,elem, v - 1);
            else if(v == cnt(root) + 1) add(root,elem,v - 2);
            else{
                add(root,elem/2,v - 2);
                add(root,(elem + 1)/2,v  - 1);
            }
        }
        else{
            //предприятие разделилось на 2
            int elem = get(root,v - 1);
            root = insert(root,v,(elem + 1)/2);
            add(root,elem/2 - elem,v - 1);
        }
        cout << root->sum << '\n';
    }
    return 0;
}
