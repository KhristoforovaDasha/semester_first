#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
int sz = 0;
struct node{
    int val;
    node* par;
};
void print(node* root);
void push(node*& root,int n){
    node* cur = new node;
    cur->val = n;
    cur->par = root;
    root = cur;
    sz++;
    cout <<"ok" <<'\n';
    //print(root);
}
void pop(node*& root){
    if(root != nullptr){
         node* cur = root->par;
         cout << root->val <<'\n';
         delete root;
         root = cur;
         sz--;
    }
    else cout <<"error" <<'\n';
    //print(root);
}
void back(node*& root){
    if(root != nullptr){
        cout << root->val <<'\n';
    }
    else cout <<"error" <<'\n';
}
void clear(node*& root){
    while(root != nullptr){
        node* cnt = root->par;
        delete root;
        root = cnt;
        sz = 0;
    }
    cout <<"ok" <<'\n';
    //print(root);
}
void print(node* root){
    while(root != nullptr){
        cout << root->val <<endl;
        root = root->par;
    }
    cout << "end" <<endl;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s = "";
    node* root = nullptr;
    while(s != "exit"){
        cin >> s;
        if(s == "push"){
            int n;
            cin >> n;
            push(root,n);
        }
        else if(s == "pop"){
             pop(root);
        }
        else if(s == "back"){
              back(root);
        }
        else if(s == "size"){
              cout << sz <<'\n';
        }
        else if(s == "clear"){
              clear(root);
        }
        else{
           cout << "bye";
        }
    }
    return 0;
}
