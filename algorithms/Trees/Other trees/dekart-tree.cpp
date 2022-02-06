#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct node{
    int x,y;
    node* left;
    node* right;
    node(int x_ = 0,int y_ = 0,node* left_ = nullptr, node* right_ = nullptr):
            x(x_),y(y_),left(left_),right(right_){};
};
pair<node*,node*> split(node* root,int x){
    if(root == nullptr){
        return {nullptr,nullptr};
    }
    if(root->x < x) {
        pair<node*,node*> cnt = split(root->right,x);
        root->right = cnt.first;
        return {root,cnt.second};
    }
    else{
        pair<node*,node*> cnt = split(root->left,x);
        root->left = cnt.second;
        return {cnt.first,root};
    }
}
node* merge(node* left,node* right){
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    if(right->y > left->y){
        right->left = merge(left,right->left);
        return right;
    }
    else{
        left->right = merge(left->right,right);
        return left;
    }
}
node* insert(node* root,int x){
    pair<node*,node*> cur = split(root,x);
    node* m = new node({x,rand()});
    return merge(merge(cur.first,m),cur.second);
}
int findMax(node* root){
    while(root->right != nullptr) root = root->right;
    return root->x;
}
int findMin(node* root){
    while(root->left != nullptr) root = root->left;
    return root->x;
}
void erase(node*& root,int x){
    if(root->x < x) erase(root->right,x);
    else if(root->x > x) erase(root->left,x);
    else{
        root = merge(root->left,root->right);
    }
}
void out(node*& root) {
    if (root == nullptr) return;
    cout << root->x <<endl;
    out(root->right);
    out(root->left);
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    cin >> tt;
    node* root = nullptr;
    while(tt--){
        string s;
        cin >> s;
        if(s == "GetMin"){
            int cur = findMin(root);
            erase(root,cur);
            cout << cur <<'\n';
        }
        else if(s == "GetMax"){
            int cur = findMax(root);
            erase(root,cur);
            cout << cur <<'\n';
        }
        else{
            int x = 0;
            for(int i = 0; i < s.size(); ++i){
                if(s[i] - '0' >= 0 && s[i] - '0' <= 9) x *= 10, x += (s[i] - '0');
            }
            root = insert(root,x);
        }
        //out(root);
    }
    return 0;
}

