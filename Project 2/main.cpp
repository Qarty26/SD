#include<iostream>
using namespace std;


struct node {

    int value, priority;
    node *left, *right;

};

node* newNode(int value) {

    node* n=new node;
    n->value=value;
    n->priority=(rand()*rand())%(value+100);
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
    n->priority=(rand()*rand())%(value+100);
    n->left=st;
    n->right=dr;

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
    else if(val < root->value) searchT(root->left,val);
    else searchT(root->right,val);
}



void deleteT(node* &root, int val)
{
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


void joinTs(node* &main, node* left, node* right,int val)
{
    main = newNode(val,left,right);
    deleteT(main,val);
}


int main() {

    node* Treap1 = NULL;
    node* Treap2 = NULL;
    node* Treap = NULL;
    for(int i=1;i<=30;i=i+2)
        insertTr(Treap1,i);


    for(int i=2;i<=30;i=i+2)
        insertTr(Treap2,i);


    printT(Treap1);
    cout<<endl;
    printT(Treap2);
    cout<<endl;
    joinTs(Treap,Treap1, Treap2,0);
    printT(Treap);

    return 0;
}
