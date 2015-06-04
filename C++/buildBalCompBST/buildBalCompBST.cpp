// CSS 502 - HW1
//
// Build a Balanced and Complete BST given
// the # of elements to store in the BST

#include <iostream>
using namespace std;

struct TreeNode{
   int value;
   TreeNode* leftChild;
   TreeNode* rightChild;
};

int calculateRoot(int);
TreeNode* constructNode(int[], int, int);
TreeNode* buildBalancedBST(int[], int);
void inOrderTrav(TreeNode*);
void preOrderTrav(TreeNode*);
void postOrderTrav(TreeNode*);
int calcMaxPowerTwo(int);

int main(){
   int tryint;
   cout << "Enter # of Elements:";
   cin >> tryint;
   cout << endl;
   cout << "Number of Elements:" << tryint << endl;
   int root = calculateRoot(tryint);
   cout << "Root:" << root << endl;

   int arr[100];
   for (int i = 0; i < tryint; i++) {
      arr[i] = i + 1;
   }

   TreeNode* rootx = buildBalancedBST(arr, tryint);
   cout << endl;
   inOrderTrav(rootx);
   cout << endl;
   preOrderTrav(rootx);
   cout << endl;
   postOrderTrav(rootx);
   cout << endl;
	return 0;
}

int calculateRoot(int n) {
   int x = n;
   int k = 0;

   while (x > 1) {
      x /= 2;
      k++;
   }

   cout << "k = " << k << endl;
   x = 1;
   for (int i = 0; i < k; i++) {
      x *= 2;
   }

   cout << "x = " << x << endl;

   if (n >= (x + (x/2))) {
      return x;
   }
   else {
      return n - ((x/2) - 1);
   }
}

// buildBalancedBST
// function that given a sorted array of integers and the number of integers 
// in that array, this function will build a complete (full if possible) 
// binary search tree using the integers provided in the array.
//
// Precondition: pre-sorted array of integers and number of integers in the
//    array is passed in as parameters
// Postcondition: a complete BST is created using the integers in the passed
//    in array
// Returns: pointer to the root node of the complete BST created
TreeNode* buildBalancedBST(int values[], int numValues) {
   // if number of values in array is negative or zero
   if (numValues <= 0) {
      return nullptr;      // empty tree
   }

   return constructNode(values, 0, numValues - 1);
}

// constructNode
// helper recursive function that will construct a single node of a 
// complete BST given an presorted array. The node to be constructed
// will store the "middle" integer value such that the resulting subtree
// will be complete as well.
//
// Precondition: whole presorted array of integers and the start/end
//    points of the section of the array that this instance of 
//    constructNode will deal with
// Postcondition: will either create a TreeNode containing a single int
//    value and pointers to any children TreeNodes or return a nullptr if
//    base case is reached
// Returns: pointer to the node created or a nullptr
TreeNode* constructNode(int values[], int start, int end) {
   // calculate size of section of array to be operated on
   int num = end - start;

   // if size is negative (base case)
   if (num < 0) {
      return nullptr;            // no node will be created/base case
   }

   int midpoint = 0;
   int k = 0;
   int x = num + 1;

   // determine largest power of two (2^k) that is still
   // smaller than num
   while (x > 1) {
      k++;
      x /= 2;
   }

   // calculate 2^k as t
   int t = 1;
   for (int i = 0; i < k; i++) {
      t *= 2;
   }

   // left subtree is perfect/complete
   // midpoint is at t (or # of ints in perfect left subtree + 1)
   if (end >= (t + (t / 2) - 1)) {
      midpoint = t + start - 1;
   }
   // right subtree is perfect
   // midpoint is at size of section - # of ints in perfect right subtree
   else {
      midpoint = (end - (t / 2) + 1);
   }

   // create node and store "middle" integer value
   TreeNode* node = new TreeNode;
   node->value = values[midpoint];

   // start recursive calls for this node's children
   node->leftChild = constructNode(values, start, midpoint - 1);
   node->rightChild = constructNode(values, midpoint + 1, end);
   return node;                // backtrack 
}

void inOrderTrav(TreeNode* root) {
   if (root) {
      inOrderTrav(root->leftChild);
      cout << root->value << " ";
      inOrderTrav(root->rightChild);
   }
}

void preOrderTrav(TreeNode* root) {
   if (root) {
      cout << root->value << " ";
      preOrderTrav(root->leftChild);
      preOrderTrav(root->rightChild);
   }
}

void postOrderTrav(TreeNode* root) {
   if (root) {
      postOrderTrav(root->leftChild);
      postOrderTrav(root->rightChild);
      cout << root->value << " ";
   }
}