#include<iostream>
#include<fstream>
#include<climits>
using namespace std;
ifstream in("abce.in");
ofstream out("abce.out");


struct node {

    int value, priority;
    node *left, *right;

};

node* newNode(int value) {

    node* n=new node;
    n->value=value;
    n->priority=rand();
    n->left=NULL;
    n->right=NULL;

    return n;
}

node* newNode(int value, int priority) {

    node* n=new node;
    n->value=value;
    n->priority=priority;
    n->left=NULL;
    n->right=NULL;

    return n;
}

node* newNode(int value,node* st, node* dr) {

    node* n=new node;
    n->value=value;
    n->priority=rand();
    n->left=st;
    n->right=dr;

    return n;
}

void rotateRight(node* &n){
    node* q=n->left;
    n->left=q->right;
    q->right=n;
    n=q;
}

void rotateLeft(node* &n){
    node* q=n->right;
    n->right=q->left;
    q->left=n;
    n=q;
}

void insertTr(node* &root, int val) {

    if (root==NULL) {
        root = newNode(val);
        return;
    }
    if (val <= root->value) {
        insertTr(root->left,val);
        if(root->priority  <  root->left->priority)
            rotateRight(root);
    }
    else {
        insertTr(root->right,val);
        if(root->priority  <  root->right->priority)
            rotateLeft(root);
    }
}

void printT(node* nod){
    if(nod==NULL) return;

    else
    {
        if (nod->left!=NULL)
        {
            cout<<nod->value<<"|"<<nod->priority<<"-st->"<<nod->left->value<<"|"<<nod->left->priority<<endl;
            printT(nod->left);
        }

        if (nod->right!=NULL)
        {
            cout<<nod->value<<"|"<<nod->priority<<"-dr->"<<nod->right->value<<"|"<<nod->right->priority<<endl;
            printT(nod->right);
        }
    }
}

bool searchT(node* root, int val) {
    if (root==NULL) return false;
    else if (root->value == val) return true;
    else if(val < root->value) return searchT(root->left,val);
    else return searchT(root->right,val);
}


int searchBefore(node* root, int value) {
    int result = INT_MIN;
    while (root) {
        if (root->value <= value) {
            result = root->value;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return result;
}

int searchAfter(node* root, int value) {
    int result = INT_MAX;
    while (root) {
        if (root->value >= value) {
            result = root->value;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return result;
}

void interval(node* root, int x, int y) {
    if (!root) return;
    if (root->value > x) interval(root->left, x, y);
    if (root->value >= x && root->value <= y) out << root->value << " ";
    if (root->value < y) interval(root->right, x, y);
}

void deleteT(node* &root, int val){
    if(root==NULL) return;

    if(val < root->value) deleteT(root->left,val);
    else if (val > root->value) deleteT(root->right,val);
    else
    {
        if(root->left==NULL && root->right==NULL)
        {
                delete root;
                root=NULL;
        }

        else if(root->left==NULL)
        {
            node* aux=root;
            root=root->right;
            delete aux;
        }

        else if(root->right==NULL)
        {
            node* aux=root;
            root=root->left;
            delete aux;
        }

        else
        {
            if(root->left->priority > root->right->priority)
            {
                rotateRight(root);
                deleteT(root->right,val);
            }

            else
            {
                rotateLeft(root);
                deleteT(root->left,val);
            }
        }

    }
}

void joinTs(node* &main, node* left, node* right,int val){
    main = newNode(val,left,right);
    deleteT(main,val);
}

void split(node* root,node* &left,node* &right, int val)
{
    if(root==NULL){
        left=NULL;
        right=NULL;
    }
    else{
        if(root->value<=val)
        {
            split(root->right,root->right,right,val);
            left=root;
        }
        else
        {
            split(root->left,left,root->left,val);
            right=root;
        }
    }
}

int main() {

int q,i,x,y,choice;

node* Treap=NULL;


in>>q;

for(i=1;i<=q;i++)
{
    in>>choice;
    if(choice==1)
    {
        in>>x;
        insertTr(Treap,x);
    }
    else if(choice==2)
    {
        in>>x;
        deleteT(Treap,x);
    }
    else if(choice==3)
    {
        in>>x;
        out<<searchT(Treap,x)<<endl;
    }
    else if(choice==4)
    {
        in>>x;
        out<<searchBefore(Treap,x)<<endl;
    }
    else if(choice==5)
    {
        in>>x;
        out<<searchAfter(Treap,x)<<endl;

    }
    else if(choice==6)
    {
        in>>x>>y;
        interval(Treap,x,y);
        out<<endl;
    }

}

    return 0;
}
