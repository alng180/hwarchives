// RBTree.cpp
// 
// RBTree is a class that represents/implements a red black tree. It will take
// in integers and then store them in the binary search tree. These integers 
// can be removed from the tree and looked up at will. This tree
// follows the standard rules for red black trees:
//    1. No two consecutive reds (i.e. red node can't have red parent)
//    2. The number of black nodes in between the two possible paths in each
//          tree/subtree are equal
// Also, for this tree, I decided to follow the rule that the tree's root node
// will always be black as well. This tree does not accept duplicates and will
// not perform an insertion if the integer is already contained in the tree.

#include "RBTree.h"

// Constructor
RBTree::RBTree() {
   treeroot = nullptr;
   treeCheck = false;
}

// Destructor
RBTree::~RBTree() {
   deleteTree(treeroot);
   treeroot = nullptr;
}

// deleteTree
// function that will delete an entire subtree with root at node. Only
//    used for the destructor. 
// @param - node - the root of the subtree to be deleted
// @postcondition - whole subtree will be completely deleted
void RBTree::deleteTree(rbnode* node) {
   if (node == nullptr) {
   }
   else {
      deleteTree(node->leftChild);
      deleteTree(node->rightChild);
      delete node;
   }
}

// lookup
// this function will determine if the value is contained in the subtree which
// has the passed in node as its root.
// @param - root - the root node of the subtree that value is to be searched in
// @param - value - the integer to be searched for
// @returns - true if value exists in the root's subtree, false if not
bool RBTree::lookup(rbnode* root, int value) {
   if (root == nullptr) {           // base case
      return false;
   }
   else if (root->value == value) {
      return true;
   }
   else {
      if (root->value < value) {
         return lookup(root->rightChild, value);
      }
      else {
         return lookup(root->leftChild, value);
      }
   }
}

// insertion
// inserts an integer into the red black tree. Will not insert duplicate
// integer values
// @param - values - the integer to be inserted into the R-B tree
// @precondition - the tree is a legal red black tree
// @postcondition - the tree will remain a legal red black tree after insertion
// @return - true if insertion is successful, false if insertion is not
//    successful (i.e. attempting to insert duplicates)
bool RBTree::insertion(int value) {
   // tree is not empty
   if (treeroot) {
      // check if value is in tree
      bool temp = lookup(treeroot, value);
      if (temp) {
         return false;
      }

      treeroot = insertNode(treeroot, value);
      treeroot->type = BLACK;             // root node must always be black
      return true;
   }
   // tree is empty
   else {
      treeroot = createNode(value);
      treeroot->type = BLACK;
      return true;
   }
}

// insertNode
// helper function for the insertion function that will recursively search
//    for a proper spot to insert value into the tree. 
// @param - node - current node being acted upon
// @param - value - integer to be inserted into the red black tree
// @precondition - node's subtree is a legal red black tree
// @postcondition - node's subtree will remain a legal red black tree after
//    insertion of value
// @return - returns the root of this subtree
rbnode* RBTree::insertNode(rbnode* node, int value) {
   // value is less, go left
   if (node->value > value) {
      if (node->leftChild == nullptr) {
         rbnode* newnode = createNode(value);
         node->leftChild = newnode;
      }
      else {
         node->leftChild = insertNode(node->leftChild, value);
      }
   }
   // value is greater, go right
   else {
      if (node->rightChild == nullptr) {
         rbnode* newnode = createNode(value);
         node->rightChild = newnode;

      }
      else{
         node->rightChild = insertNode(node->rightChild, value);
      }
   }

   node = insertCheck(node);           // check tree if legal

   return node;
}

// insertCheck
// this function will check to see if the subtree with node as its root is a 
//    legal red black tree or not after insertion. If it isn't, then it will
//    perform color swaps and rotations until is it.
// @param - node - the root of the subtree to be checked/fixed
// @postcondition - subtree with root at node is now a legal red black tree
// @return - returns the root of the checked/legal red black tree
rbnode* RBTree::insertCheck(rbnode* node) {
   if (isRed(node->leftChild)) {
      // two child red nodes 
      if (isRed(node->rightChild)) {
         node->type = RED;
         node->leftChild->type = BLACK;
         node->rightChild->type = BLACK;
      }
      // string of three nodes
      else {
         // left leaning ("straight line")
         if (isRed(node->leftChild->leftChild)) {
            node = rightRot(node);
         }
         // "crooked line", do double rotation
         else if (isRed(node->leftChild->rightChild)) {
            node->leftChild = leftRot(node->leftChild);
            node = rightRot(node);
         }
      }
   }
   else if (isRed(node->rightChild)) {    //redundant remove?
      // two child red nodes
      if (isRed(node->leftChild)) {
         node->type = RED;
         node->leftChild->type = BLACK;
         node->rightChild->type = BLACK;
      }
      // string of three nodes
      else {
         // right leaning/"straight line"
         if (isRed(node->rightChild->rightChild)) {
            node = leftRot(node);
         }
         // "crooked line", do double rotation
         else if (isRed(node->rightChild->leftChild)) {
            node->rightChild = rightRot(node->rightChild);
            node = leftRot(node);
         }
      }
   }

   return node;
}

// leftRot
// performs a left rotation around node root. Will shift root to become
//    the left child of root's current right child. Will also shift 
//    around the children of these two nodes to maintain binary tree structure
// @param - root - the node to be rotated around
// @postcondition - root's right child should now be rotated to root's
//    previous location and root is now the left child of that node
// @return - returns the new root of this subtree (should be the right
//    child of root)
rbnode* RBTree::leftRot(rbnode* root) {
   rbnode* temp = root->rightChild;

   root->rightChild = temp->leftChild;
   temp->leftChild = root;

   root->type = RED;
   temp->type = BLACK;

   return temp;
}

// rightRot
// performs a right rotation around node root. Will shift root to become
//    the right child of root's current left child. Will also shift 
//    around the children of these two nodes to maintain binary tree structure
// @param - root - the node to be rotated around
// @postcondition - root's left child should now be rotated to root's
//    previous location and root is now the right child of that node
// @return - returns the new root of this subtree (should be the left
//    child of root)
rbnode* RBTree::rightRot(rbnode* root) {
   rbnode* temp = root->leftChild;

   root->leftChild = temp->rightChild;
   temp->rightChild = root;

   root->type = RED;
   temp->type = BLACK;

   return temp;
}

// createNode
// creates new rbnode containing the passed in integer value
// @param - value - the integer that the new node will store
// @postcondition - new node will be a red leaf node
// @return - the newly created node
rbnode* RBTree::createNode(int value) {
   rbnode* newnode = new rbnode;

   newnode->leftChild = nullptr;
   newnode->rightChild = nullptr;
   newnode->type = RED;
   newnode->value = value;

   return newnode;
}

// deletion
// if it exists in the tree, this function will delete the node storing
//    the passed in integer.
// @param - value - the integer desired to be removed from the tree
// @precondition - assumes tree is a legal red black tree
// @postcondition - will remain a legal red black tree after deletion
// @return - returns true if integer is removed from tree, false if integer
//    was not removed as it is not contained in the tree
bool RBTree::deletion(int value) {
   // tree is not empty
   if (treeroot) {
      // search if value exists in tree
      bool temp = lookup(treeroot, value);
      if (!temp) {
         return false;
      }
      else {
         treeCheck = true;             // reset flag to see if check needed
         treeroot = removeNode(treeroot, value);

         if (treeroot) {
            treeroot->type = BLACK;    // always set root to black
         }

         return true;
      }
   }
   // tree is empty
   else {
      return false;
   }
}

// removeNode
// helper function for the deletion function that will recursively search
//    the tree for the value to delete
// @param - node - current node being acted upon
// @param - value - integer to be deleted from the red black tree
// @precondition - node's subtree is a legal red black tree
// @postcondition - node's subtree will remain a legal red black tree after
//    deletion
// @return - returns the root of this subtree
rbnode* RBTree::removeNode(rbnode* target, int value) {
   //if (target == nullptr) {
   //   treeCheck = false;
   //}
   //else {
      rbnode* temp = nullptr;

      // value is found
      if (target->value == value) {
         // target node contains one or no children
         if (target->leftChild == nullptr || target->rightChild == nullptr) {
            // left child only
            if (target->leftChild != nullptr) {
               temp = target->leftChild;
            }
            // right child only
            else if (target->rightChild != nullptr) {
               temp = target->rightChild;
            }

            // check if removing red node (or can trivalize to it)
            if (isRed(target)) {
               treeCheck = false;
            }
            else if (isRed(temp)) {
               temp->type = BLACK;
               treeCheck = false;
            }

            delete target;
            target = nullptr;

            return temp;
         }
         // target node contains two children
         else {
            // find the left most child in right subtree (next value/int in order)
            temp = target->rightChild;

            while (temp->leftChild != nullptr) {
               temp = temp->leftChild;
            }

            // copy left most child value to target node (will remove later)
            target->value = temp->value;
            value = temp->value;
         }
      }
   //}

   // continue down tree
   bool left;
   if (value >= target->value) {
      target->rightChild = removeNode(target->rightChild, value);
      left = false;
   }
   else {
      target->leftChild = removeNode(target->leftChild, value);
      left = true;
   }

   // perform check on tree if necessary
   if (treeCheck) {
      target = deletionCheck(target, left);
   }

   return target;
}

// deletionCheck
// this function will check to see if the subtree with node as its root is a 
//    legal red black tree or not after deletion. If it isn't, then it will
//    perform color swaps and rotations until is it.
// @param - node - the root of the subtree to be checked/fixed
// @postcondition - subtree with root at node is now a legal red black tree
// @return - returns the root of the checked/legal red black tree
rbnode* RBTree::deletionCheck(rbnode* target, bool left) {
   rbnode* root = target;
   rbnode* sibling;
   
   // determine "sibling" node
   if (left) {
      sibling = target->rightChild;
   }
   else {
      sibling = target->leftChild;
   }
   
   // convert red sibling case to black sibling case
   if (isRed(sibling)) {
      if (left) {
         target = leftRot(target);
      }
      else {
         target = rightRot(target);
      }

      // point to new "sibling" node after the rotation
      if (left) {
         sibling = target->rightChild;
      }
      else {
         sibling = target->leftChild;
      }

   }

   if (sibling != nullptr) {
      // if sibling is a red node with two black children, swap colors between root and sibling
      if (!isRed(sibling->leftChild) && !isRed(sibling->rightChild)) {
         if (isRed(root)) {
            treeCheck = false;                     // case is trivial (recolor only)
         }
         root->type = BLACK;
         sibling->type = RED;
      }
      // sibling contains red children
      else {
         // save parent (root) information
         bool rootNotMoved = false;
         if (target == root) {
            rootNotMoved = true;
         }
         color rootColor = root->type;

         //
         if (left) {
            // right (b) right (r) case
            if (isRed(sibling->rightChild)) {
               root = leftRot(root);
            }
            // right (b) left (r) case
            else {
               root->rightChild = rightRot(root->rightChild);
               root = leftRot(root);
            }
         }
         else {
            // left (b) left (r) case
            if (isRed(sibling->leftChild)) {
               root = rightRot(root);
            }
            // left (b) right (r) case
            else {
               root->leftChild = leftRot(root->leftChild);
               root = rightRot(root);
            }
         }

         // restore parent coloring
         root->type = rootColor;
         root->leftChild->type = BLACK;
         root->rightChild->type = BLACK;

         // place (old) root/parent in its new proper location in tree
         if (rootNotMoved) {
            target = root;
         }
         else {
            if (left) {
               target->leftChild = root;
            }
            else {
               target->rightChild = root;
            }
         }

         treeCheck = false;
      }
   }

   return target;
}

// isRed
// function that checks if a node is a red node or not
// @param - node - node to be checked
// @return - true if node is a red node, false if node is black or null
bool RBTree::isRed(rbnode* node) {
   // in RB Trees, paths may terminate in black "null nodes"
   if (node == nullptr) {
      return false;           
   }
   else {
      if (node->type == RED) {
         return true;
      }
      else {
         return false;
      }
   }
}