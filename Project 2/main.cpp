#include<iostream>
using namespace std;


struct node {

    int value, priority;
    node *left, *right;

};

node* newNode(int value) {

    node* n=new node;
    n->value=value;
    n->priority=(rand()*rand())%value;
    n->left=NULL;
    n->right=NULL;

    return n;
}

void rotateRight(node* &n)
{
    node* q=n->left;
    n->left=q->right;
    q->right=n;
    n=q;
}

void rotateLeft(node* &n)
{
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

void printT(node* nod)
{
    if(nod==NULL)
    {
        return;
    }

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


bool cautare(node* root, int val) {
    if (root==NULL) return false;
    else if (root->value == val) return true;
    else if(val < root->value) cautare(root->left,val);
    else cautare(root->right,val);
}


int main() {

    node* Treap = NULL;
    insertTr(Treap, 10);
    insertTr(Treap, 20);
    insertTr(Treap, 30);
    insertTr(Treap, 40);
    insertTr(Treap, 50);
    insertTr(Treap, 60);
    insertTr(Treap, 70);
    insertTr(Treap, 80);
    //printT(Treap);

    cout<<cautare(Treap, 69);


    return 0;
}
