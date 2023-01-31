#include<bits/stdc++.h>
using namespace std;


template<typename Comparable>
class AvlNode{
  public:
    Comparable element;
    AvlNode *left;
    AvlNode *right;
    int height;
    AvlNode(Comparable element,AvlNode *left,AvlNode *right,int h=0){
      this->element = element;
      this->left = left;
      this->right = right;
      this->height = h;
    }
};

template<typename Comparable>
int height(AvlNode<Comparable> *node){
  return node==NULL ? -1 : node->height;
}

template<typename Comparable>
void rotateWithLeftChild(AvlNode<Comparable> *&k2){//unbalenced node
  cout<<"LL rotation \n";
  AvlNode<Comparable> *k1=k2->left;
  k2->left=k1->right;
  k1->right=k2;
  k2->height=max(height(k2->left),height(k2->right))+1;
  k1->height=max(height(k1->left),k2->height)+1;
  k2=k1;
}

template<typename Comparable>
void rotateWithRightChild(AvlNode<Comparable> *&k2){//unbalenced node
  cout<<"RR rotation \n";
  AvlNode<Comparable> *k1=k2->right;
  k2->right=k1->left;
  k1->left=k2;
  k2->height=max(height(k2->left),height(k2->right))+1;
  k1->height=max(height(k1->left),k2->height)+1;
  k2=k1;
}

template<typename Comparable>
void doubleWithLeftChild(AvlNode<Comparable> *&k3){//unbalenced node [LR]
  cout<<"LR rotation \n";
  rotateWithRightChild<Comparable>(k3->left);
  rotateWithLeftChild<Comparable>(k3);
}

template<typename Comparable>
void doubleWithRightChild(AvlNode<Comparable> *&k3){//unbalenced node [RL]
  cout<<"RL rotation \n";
  rotateWithLeftChild<Comparable>(k3->right);
  rotateWithRightChild<Comparable>(k3);
}


template<typename Comparable>
void insert(const Comparable &x,AvlNode<int> *&t){
  if(!t){
    t=new AvlNode<int>{x,NULL,NULL};
  }else if(x<t->element){
    insert(x,t->left);
    if(height(t->left)-height(t->right)==2){//rotation required
        if(x<t->left->element){ //LL rotation required
          rotateWithLeftChild<Comparable>(t);
        }else{
          doubleWithLeftChild<Comparable>(t); //LR rotation required
        }
    }
  }else if(x>t->element){
    insert(x,t->right);
    if(height(t->right)-height(t->left)==2){
        if(t->right->element<x){//RR rotation required
          rotateWithRightChild<Comparable>(t);
        }else{
          doubleWithRightChild<Comparable>(t);
        }
    }
  }else{//duplicate element found
   cout<<"Duplicate element found : insertion failed."; 
  }
  t->height=max(height(t->left),height(t->right))+1;
}

void printAvl(AvlNode<int> *root){
  if(!root){
    return;
  }
  printAvl(root->left);
  cout<<root->element<<" ";
  printAvl(root->right);
}


int main(){
  AvlNode<int> *root=NULL;
  insert(3,root);
  insert(2,root);
  insert(1,root);
  printAvl(root);
  cout<<endl;
  insert(4,root);
  insert(5,root);
  insert(6,root);
  insert(7,root);
  printAvl(root);
  cout<<endl;
  insert(16,root);
  insert(15,root);
  insert(14,root);
  insert(13,root);
  insert(12,root);
  insert(11,root);
  insert(10,root);
  insert(8,root);
  insert(9,root);
  printAvl(root);
  cout<<endl;
  cout<<root->height<<endl;
}