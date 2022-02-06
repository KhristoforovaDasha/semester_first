#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using ll = long long;
struct node{
    node *left = nullptr,*right = nullptr,*parent = nullptr;
    ll value = 0,sum = 0;
    node(ll value_):value(value_),sum(value){}
};
node* parent(node* vertex){
    return vertex->parent;
}
node* grand(node* vertex){
    return parent(parent(vertex));
}
ll sum(node* vertex){
    if(vertex) return vertex->sum;
    return 0;
}
void set_sum(node* vertex){
    if(vertex) vertex->sum = vertex->value + sum(vertex->right) + sum(vertex->left);
}
void rotate_right(node* vertex){
    node* par = vertex->parent;
    node* left = vertex->left;
    if(par){
        if(par->right == vertex) par->right = left;
        else par->left = left;
    }
    node* tmp = left->right;
    left->right = vertex;
    vertex->parent = left;
    vertex->left = tmp;
    left->parent = par;
    left->parent = par;
    set_sum(vertex);
    set_sum(left);
    if(vertex->left){
        vertex->left->parent = vertex;
    }
}
void rotate_left(node* vertex){
    node* par = vertex->parent;
    node* right = vertex->right;
    if(par){
        if(par->left == vertex) par->left = right;
        else par->right = right;
    }
    node* tmp = right->left;
    right->left = vertex;
    vertex->right = tmp;
    vertex->parent = right;
    right->parent = par;
    set_sum(vertex);
    set_sum(right);
    if(vertex->right){
        vertex->right->parent = vertex;
    }
}
node* splay(node* root){
    while(parent(root)){
        if(root == parent(root)->left){
            if(grand(root) == nullptr)
                rotate_right(parent(root));
            else if(parent(root) == grand(root)->left){
                rotate_right(grand(root));
                rotate_right(parent(root));
            }
            else{
                rotate_right(parent(root));
                rotate_left(parent(root));
            }
        }
        else{
            if(grand(root) == nullptr)
                rotate_left(parent(root));
            else if(parent(root) == grand(root)->right){
                rotate_left(grand(root));
                rotate_left(parent(root));
            }
            else{
                rotate_left(parent(root));
                rotate_right(parent(root));
            }
        }
    }
    return root;
}
std::pair<node*,node*> split(node* root,int key){
    if(root == nullptr) return {nullptr, nullptr};
    if(root->right == nullptr && root->value <= key){
        root = splay(root);
        node* right = root->right;
        node* left = root;
        if(right) right->parent = nullptr;
        left->right = nullptr;
        set_sum(left),set_sum(right);
        return {left,right};
    }
    else if(root->left == nullptr && root->value > key){
        root = splay(root);
        node* left = root->left;
        node* right = root;
        if(left) left->parent = nullptr;
        right->left = nullptr;
        set_sum(left),set_sum(right);
        return {left,right};
    }
    else if(root->value <= key) return split(root->right,key);
    else return split(root->left,key);
}
node* find_max(node* root){
    if(root == nullptr) return root;
    if(root->right == nullptr){
        return splay(root);
    }
    return find_max(root->right);
}
node* merge(node* first,node* second){
    first = find_max(first);
    if(first) {
        first->right = second;
        if(second) {
            second->parent = first;
        }
        set_sum(first);
        return first;
    }
    return second;
}
node* insert(int value,node* root) {
    std::pair<node*,node*> child  = split(root,value);
    node* result = new node(value);
    result->left = child.first;
    if(child.first) child.first->parent = result;
    result->right = child.second;
    if(child.second) child.second->parent = result;
    result->sum += sum(child.first) + sum(child.second);
    return result;
}
std::pair<node*,ll> sum(int l,int r,node* root){
    std::pair<node*,node*> first = split(root,l);
    ll sum1 = 0;
    if(first.second) sum1 += first.second->sum;
    std::pair<node*,node*> second = split(first.second,r);
    ll sum2 = 0;
    if(second.second) sum2 += second.second->sum;
    return {merge(first.first,merge(second.first,second.second)),sum1 - sum2};
}
void print(node* root){
    if(root == nullptr) return;
    print(root->left);
    cout << root->value <<" ";
    print(root->right);
}
bool find(node* root,int value){
    if(root == nullptr) return 0;
    if(root->value == value) return 1;
    if(root->value < value) return find(root->right,value);
    else return find(root->left,value);
}
int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n, mod = 1e9;
    char c, last = '+';
    ll res = 0;
    cin >> n;
    node* root = nullptr;
    while (n--) {
        cin >> c;
        if (c == '+') {
            int x;
            cin >> x;
            if (last == '?') x = (x + res) % mod;
            if (!find(root, x)) {
                root = insert(x, root);
            }
        } else {
            int l, r;
            cin >> l >> r;
            std::pair<node*, ll> ans = sum(l - 1, r, root);
            res = ans.second;
            root = ans.first;
            cout << res << '\n';
        }
        last = c;
    }
    return 0;
}

