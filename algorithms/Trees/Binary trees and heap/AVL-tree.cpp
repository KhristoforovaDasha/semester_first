#include <iostream>
#include <vector>
#include <algorithm>
int inf = -1e9 - 1;
using std:: cin;
using std:: cout;
using std:: string;
struct node{
    node* left = nullptr;
    node* right = nullptr;
    int value,min ,max ;
    int height = 1;
    node(int value_): value(value_),min(value),max(value){}
};
int height(node* vertex){
    return vertex ? vertex->height : 0;
}
int max(node* vertex){
    return vertex ? vertex->max : inf;
}
int min(node* vertex){
    return vertex ? vertex->min : -inf;
}
void new_height(node*& vertex){
    vertex->height = std:: max(height(vertex->left),height(vertex->right)) + 1;
}
void check(node*& vertex){
    vertex->height = std:: max(height(vertex->left),height(vertex->right)) + 1;
    vertex->min = std:: min(std:: min(min(vertex->right),min(vertex->left)),vertex->value);
    vertex->max = std:: max(std:: max(max(vertex->right),max(vertex->left)),vertex->value);
}
void update(node*& vertex){
    if(vertex == nullptr) return;
    check(vertex);
    update(vertex->left);
    update(vertex->right);
}
int sub_height(node* vertex){
    return height(vertex->right) - height(vertex->left);
}
void right_bal(node*& vertex){
    node* tmp = vertex->left;
    vertex->left = tmp->right;
    tmp->right = vertex;
    check(vertex);
    check(tmp);
    vertex = tmp;
}
void left_bal(node*& vertex){
    node* tmp = vertex->right;
    vertex->right = tmp->left;
    tmp->left = vertex;
    check(vertex);
    check(tmp);
    vertex = tmp;
}
void balance(node*& vertex){
    check(vertex);
    if(sub_height(vertex) == 2){
        if(sub_height(vertex->right) < 0) right_bal(vertex->right);
        left_bal(vertex);
    }
    else if(sub_height(vertex) == -2){
        if(sub_height(vertex->left) > 0) left_bal(vertex->left);
        right_bal(vertex);
    }
}
void insert(int key,node*& vertex){
    if(vertex == nullptr) {
        vertex = new node(key);
        return;
    }
    if(key < vertex->value) insert(key,vertex->left);
    else insert(key,vertex->right);
    balance(vertex);
}
int findmin(node*& vertex){
    if(vertex->left == nullptr) {
        int result = vertex->value;
        vertex = vertex->right;
        return result;
    }
    int result = findmin(vertex->left);
    if(vertex) balance(vertex);
    return result;
}
void erase(int key,node*& vertex){
    if(vertex == nullptr) return;
    if(key < vertex->value) erase(key,vertex->left);
    else if(key > vertex->value) erase(key,vertex->right);
    else{
        if(vertex->right == nullptr){
            vertex = vertex->left;
            return;
        }
        else vertex->value = findmin(vertex->right);
    }
    if(vertex) balance(vertex);
}
int next(int key,node*& vertex){
    if(vertex == nullptr) return inf;
    if(key < vertex->value){
        if(vertex->left && vertex->left->max > key) {
            return next(key,vertex->left);
        }
        return vertex->value;
    }
    return next(key,vertex->right);
}
int prev(int key,node*& vertex){
    if(vertex == nullptr) return inf;
    if(vertex->value < key){
        if(vertex->right && vertex->right->min < key) return prev(key,vertex->right);
        return vertex->value;
    }
    return prev(key,vertex->left);
}
bool exists(int key,node*& vertex){
    if(vertex == nullptr) return 0;
    if(vertex->value == key) return 1;
    if(key < vertex->value) return exists(key,vertex->left);
    return exists(key,vertex->right);
}
signed main() {
    std::ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    string command = "";
    node* root = nullptr;
    while(cin >> command){
        int value;
        cin >> value;
        if(command == "insert"){
            if(!exists(value,root))insert(value, root);
        } else if(command == "exists"){
            if(exists(value,root)) cout <<"true" <<'\n';
            else cout <<"false" <<'\n';
        } else if(command == "next"){
            int result = next(value,root);
            if(result == inf) cout <<"none" <<'\n';
            else cout << result<<'\n';
        } else if(command == "prev"){
            int result = prev(value,root);
            if(result == inf) cout <<"none" <<'\n';
            else cout << result <<'\n';
        } else if(command == "delete"){
            if(exists(value,root)) erase(value,root);
        }
    }
    return 0;
}
