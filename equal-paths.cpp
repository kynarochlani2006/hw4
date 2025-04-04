#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int depthOfTree(Node* root){

  if(root == nullptr){
    return 0;
  }

  int leftSide = depthOfTree(root->left);
  int rightSide = depthOfTree(root->right);

  if(leftSide > rightSide){
    return leftSide + 1;
  } else if(leftSide < rightSide){
    return rightSide + 1;
  } else if(leftSide == rightSide){
    return leftSide + 1;
  }
}


bool equalPaths(Node * root)
{

  if(root == nullptr){
    return true;
  }


  if(root->left == nullptr && root->right == nullptr){
    return true;
  }

  if(root->left == nullptr){
    return equalPaths(root->right);
  } else if(root->right == nullptr){
    return equalPaths(root->left);
  }

  int left = depthOfTree(root->left);
  int right = depthOfTree(root->right);

  if(left != right){
    return false;
  }

  return equalPaths(root->left) == true && equalPaths(root->right) == true;

}



