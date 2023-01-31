#include<bits/stdc++.h>
using namespace std;



template<typename Comparable>
class AVL{
  public:
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
      int getHeight() const;
    };
    AvlNode *root{};
    void rotateWithLeftChild(AvlNode *&k2);
    void rotateWithRightChild(AvlNode *&k2);
    void doubleWithLeftChild(AvlNode *&k3);
    void doubleWithRightChild(AvlNode *&k3);
    void insert(const Comparable x);
    void inorder() const;
    void preorder() const;
    void postorder() const;
    private:
      void inorder(AvlNode *root) const;
      void preorder(AvlNode *root) const;
      void postorder(AvlNode *root) const;
      void insert(const Comparable x,AvlNode *&root);
};

template<typename Comparable>
int AVL<Comparable>::AvlNode::getHeight() const{
  return !this ? -1 : this->height;
}

template<typename Comparable>
void AVL<Comparable>::rotateWithLeftChild(AvlNode *&k2){//unbalenced node
  // cout<<"LL rotation \n";
  AvlNode *k1=k2->left;
  k2->left=k1->right;
  k1->right=k2;
  k2->height=max(k2->left->getHeight(),k2->right->getHeight())+1;
  k1->height=max(k1->left->getHeight(),k2->getHeight())+1;
  k2=k1;
}

template<typename Comparable>
void AVL<Comparable>::rotateWithRightChild(AvlNode *&k2){//unbalenced node
  // cout<<"RR rotation \n";
  AvlNode *k1=k2->right;
  k2->right=k1->left;
  k1->left=k2;
  k2->height=max(k2->left->getHeight(),k2->right->getHeight())+1;
  k1->height=max(k1->left->getHeight(),k2->getHeight())+1;
  k2=k1;
}

template<typename Comparable>
void AVL<Comparable>::doubleWithLeftChild(AvlNode *&k3){//unbalenced node [LR]
  // cout<<"LR rotation \n";
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

template<typename Comparable>
void AVL<Comparable>::doubleWithRightChild(AvlNode *&k3){//unbalenced node [RL]
  // cout<<"RL rotation \n";
  rotateWithLeftChild(k3->right);
  rotateWithRightChild(k3);
}
template<typename Comparable>
void  AVL<Comparable>::insert(const Comparable x,AvlNode *&root){
  if(!root){
    root=new AvlNode{x,NULL,NULL};
  }else if(x<root->element){
    insert(x,root->left);
    if(((root->left->getHeight())-(root->right->getHeight()))==2){//rotation required
        if(x<root->left->element){ //LL rotation required
          rotateWithLeftChild(root);
        }else{
          doubleWithLeftChild(root); //LR rotation required
        }
    }
  }else if(x>root->element){
    insert(x,root->right);
    if((root->right->getHeight()-root->left->getHeight())==2){
        if(root->right->element<x){//RR rotation required
          rotateWithRightChild(root);
        }else{
          doubleWithRightChild(root);
        }
    }
  }else{//duplicate element found
   cout<<"Duplicate element found : insertion failed for value :"<<x<<endl; 
  }
  root->height=max(root->left->getHeight(),root->right->getHeight())+1;
}

template<typename Comparable>
void AVL<Comparable>::insert(const Comparable x){
  this->insert(x,root);
}

template<typename Comparable>
void AVL<Comparable>::inorder(AvlNode *root) const{
   if(!root){
    return;
  }
  inorder(root->left);
  cout<<root->element<<" ";
  inorder(root->right);
}
template<typename Comparable>
void AVL<Comparable>::preorder(AvlNode *root) const{
   if(!root){
    return;
  }
  cout<<root->element<<" ";
  preorder(root->left);
  preorder(root->right);
}
template<typename Comparable>
void AVL<Comparable>::postorder(AvlNode *root) const{
   if(!root){
    return;
  }
  postorder(root->left);
  postorder(root->right);
  cout<<root->element<<" ";
}

template<typename Comparable>
void AVL<Comparable>::inorder() const{
  cout<<"InOrder : [ ";
  inorder(root);
  cout<<" ]\n";
}
template<typename Comparable>
void AVL<Comparable>::preorder() const{
  cout<<"PreOrder : [ ";
  preorder(root);
  cout<<" ]\n";
}
template<typename Comparable>
void AVL<Comparable>::postorder() const{
  cout<<"PostOrder : [ ";
  postorder(root);
  cout<<" ]\n";
}

namespace util{
  namespace{
    void border(int wide,char c){
    cout<<string(wide,c);
    }
  }
  void instructions(){
    border(30,'#');cout<<endl;
    cout<<"AVL Tree\n";
    cout<<"1. Insert a value in avl tree :\n";
    cout<<"2. Insert bulk values in avl tree :\n";
    cout<<"3. print inorder of avl tree :\n";
    cout<<"4. print preorder of avl tree :\n";
    cout<<"5. print postorder of avl tree :\n";
    cout<<"6. Exit\n";
    border(30,'#');cout<<endl;  
  }
}
int main(){
  AVL<int> avlTree;
  
  
  bool shouldExit=false;
  do{
    util::instructions();
    int choice=-1;
    cin>>choice;
    shouldExit=false;

    switch(choice){
      case 1:{
        int val;
        cout<<"Enter the value to insert : ";
        cin>>val;
        cout<<endl;
        avlTree.insert(val);
      };break;
      case 2:{
        int count;
        cout<<"Enter the count of values to insert : ";
        cin>>count;
        if(count<=0){
          cout<<"Invalid count 💥\n";
          break;
        }
        cout<<"Please enter space seperated values to insert :";
        while(count-->0){
          int val;
          cin>>val;
          avlTree.insert(val);
        }
      };break;
      case 3:avlTree.inorder();break;
      case 4:avlTree.preorder();break;
      case 5:avlTree.postorder();break;
      case 6:shouldExit=true;break;
      default :{
        cout<<"Invalid choice💥\n";
      };
    }
  }while(!shouldExit);
  
  cout<<"Happy coding🍵\n";
  return 0;
}