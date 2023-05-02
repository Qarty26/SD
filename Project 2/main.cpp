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

node* newNode(int value, int priority) {

    node* n=new node;
    n->value=value;
    n->priority=priority;
    n->left=NULL;
    n->right=NULL;

    return n;
}

node* newNode(int value, int priority,node* st, node* dr) {

    node* n=new node;
    n->value=value;
    n->priority=priority;
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




int main() {

    node* Treap = NULL;
    for(int i=1;i<=30;i++)
        insertTr(Treap,i);

    printT(Treap);

    cout<<endl<<endl;

    for(int i=1;i<=30;i=i+2)
        deleteT(Treap,i); ///sterge valorile impare

    printT(Treap);

    return 0;
}
