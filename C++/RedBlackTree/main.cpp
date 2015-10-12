// main.cpp
//

#include "RBTree.h"
#include <iostream>
#include <string>

void outputTree(RBTree*);
void inOrderTrav(rbnode*);
void preOrderTrav(rbnode*);
void postOrderTrav(rbnode*);
string rorb(rbnode*);
int verifyTree(rbnode*);

int main() {
   RBTree* tree = new RBTree();

   bool temp;
   
//   tree->insertgo = false;
   int i = 5000;
   for (int k = 0; k < i; k++) {
      temp = tree->insertion(k);
   }

   temp = tree->deletion(11);
   temp = tree->deletion(14);
   temp = tree->deletion(2);
   temp = tree->deletion(15);
   temp = tree->deletion(6);
   temp = tree->deletion(28);
   temp = tree->deletion(49);
   temp = tree->deletion(7);
   temp = tree->deletion(25);
   temp = tree->deletion(35);
   temp = tree->deletion(45);
   temp = tree->deletion(5);

   outputTree(tree);

   return 0;
}

void outputTree(RBTree* tree) {
   cout << endl;
   inOrderTrav(tree->treeroot);
   cout << endl;
   cout << endl;
   preOrderTrav(tree->treeroot);
   cout << endl;
   cout << endl;
   postOrderTrav(tree->treeroot);
   cout << endl;
}

void inOrderTrav(rbnode* root) {
   if (root) {
      inOrderTrav(root->leftChild);
      cout << root->value << " " << rorb(root) << " - ";
      inOrderTrav(root->rightChild);
   }
}

void preOrderTrav(rbnode* root) {
   if (root) {
      cout << root->value << " " << rorb(root) << " - ";
      preOrderTrav(root->leftChild);
      preOrderTrav(root->rightChild);
   }
}

void postOrderTrav(rbnode* root) {
   if (root) {
      postOrderTrav(root->leftChild);
      postOrderTrav(root->rightChild);
      cout << root->value << " " << rorb(root) << " - ";
   }
}

string rorb(rbnode* root) {

      if (root->type == RED) {
         return "red";
      }
      else {
         return "black";
      }
}

// verifyTree
// this function will traverse the whole tree and 
//int verifyTree(rbnode* root) {
//   rbnode* left;
//   rbnode* right;
//   if (root == nullptr) {
//      return true;
//   }
//   else {
//      left = root->leftChild;
//      right = root->rightChild;
//
//      if (rorb(root)) {
//         if (rorb(left) || rorb(right)) {
//            cout << "red violation" << endl;
//            return false;
//         }
//      }
//   }
//
//   int leftCount = verifyTree(left);
//   int rightCount = verifyTree(right);
//
//   if (left != nullptr && left->value > root->value) {
//      cout << "binary tree error" << endl;
//      return false;
//   }
//   if (right != nullptr && right->value < root->value) {
//      cout << "binar tree error" << endl;
//      return false;
//   }
//
//   if (leftCount != 0 && rightCount != 0 && left != right) {
//      cout << "red black mismatch" << endl;
//      return false;
//   }
//
//   if (leftCount != 0 && rightCount != 0) {
//      if (rorb(root)) {
//         return leftCount;
//      }
//      else {
//         return leftCount + 1;
//      }
//   }
//   else {
//      return true;
//   }
//}