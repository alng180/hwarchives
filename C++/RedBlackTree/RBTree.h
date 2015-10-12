// RBTree.h
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

#ifndef RBTree_H
#define RBTree_H
using namespace std;

// emum to describe the color of the node, either red or black
enum color { RED, BLACK };

// rbnode
// a single node of the RBTree. Contains the color of the node,
// the integer value stored, and pointers to its two children
struct rbnode {
   color type;
   int value;
   rbnode* leftChild;
   rbnode* rightChild;
};

// see .cpp file for more detailed comments describing the below methods/members
class RBTree {
public:
   RBTree();
   ~RBTree();
   bool insertion(int value);    // add a value from tree
   bool deletion(int value);     // remove a value from tree
   bool lookup(rbnode* root, int value);  // function to search for value
   rbnode* treeroot;             // root node for the whole tree
private:
   bool treeCheck;               // flag to check if tree needs to be fixed

   // functions related to insertion
   rbnode* insertNode(rbnode* node, int value);
   rbnode* insertCheck(rbnode* node);
   rbnode* createNode(int value);

   // functions related to deletion
   rbnode* removeNode(rbnode* target, int value);
   rbnode* deletionCheck(rbnode* target, bool leftpath);

   // functions used in both deletion and insertion
   bool isRed(rbnode* node);
   rbnode* leftRot(rbnode* root);
   rbnode* rightRot(rbnode* root);


   void deleteTree(rbnode* node);
};

#endif