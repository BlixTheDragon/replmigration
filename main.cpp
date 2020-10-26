/* * * * * * * * * * * * * * * * * * * * * * * * * 
 * BINARY SEARCH TREE PROJECT                    *
 *                                               *
 * GROUP FIVE                                    *
 * Ryan A, Arianna P, Sarah C, Refati K          *
 *                                               *
 * Models a BST of electric cars, and implements *
 * a recursive in-order tree walk, insertion,    *
 * and deletion algorithms.                      *
 * * * * * * * * * * * * * * * * * * * * * * * * */



#include <iostream>
#include <vector>
#include <string>
using namespace std;




class TreeNode{
public:
  TreeNode* parent;
  TreeNode* childL;
  TreeNode* childR;
  string model;
  int topSpeed;

  TreeNode(string car, int spd, TreeNode* p)
  //Shorthand to input values to members
  :model(car),topSpeed(spd),parent(p)
  {
    //set children to nullptrs by default
    childL = nullptr;
    childR = nullptr;
  }
};
//Globals for use in main() later
TreeNode* evTree;
TreeNode* testNode = new TreeNode("Cybertruck", 110, nullptr);

/* * * * * * * * * * * * * * * * * * *
 * recursiveWalk                     *
 * In-Order Tree Walk Algorithm that *
 * outputs the tree in alphabetical  *
 * order by modelling a jeep falling *
 * through a tree (inside jokes lol) *
 *                                   *
 * Input: TreeNode pointer to the    *
 *        root of a tree             *
 * Output: C-Out output of the tree  *
 *         in the terminal           *
 * * * * * * * * * * * * * * * * * * */
void recursiveWalk(TreeNode* jeep)
{
  if(jeep != nullptr)
  {
    recursiveWalk(jeep->childL);
    cout << jeep->model << "\n";
    recursiveWalk(jeep->childR);
  }
}

/* * * * * * * * * * * * * * * * * * *
 * insertNode                        *
 * Algorithm that walks through the  *
 * tree to input a leaf node.        *
 *                                   *
 * Input: TreeNode pointer to the    *
 *        root of a tree             *
 *        Optional: TreeNode pointer *
 *        to a node to be inserted   *
 * Output: TreeNode pointer to the   *
 *         root of the tree with the *
 *         new node inserted         *
 * * * * * * * * * * * * * * * * * * */

TreeNode* insertNode(TreeNode* tree, TreeNode* bauble = nullptr)
{
  //Create the node to be added
  //The node is referred to as "bauble" because you hang baubles on trees or something
  if (bauble == nullptr)
  {
    string model;
    int topSpeed;
    cout << "\nEnter the car's model name.\n";
    cin >> model;
    cout << "\nEnter the car's top speed.\n";
    cin >> topSpeed;
    bauble = new TreeNode(model, topSpeed, nullptr);
  }
  //The Algorithm™

  //If the tree is empty, insert the node as the root
  if (tree == nullptr)
  {
    tree = bauble;
  }
 
  else
  {
    compare:
    //st1.compare(st2) outputs -1 if st2 is earlier alphabetically than st1, 
    //                          1 if later, 
    //                          0 if they are the same.
    int comparison = bauble->model.compare(tree->model);
    switch(comparison)
    { 
      //If bauble is earlier in the alphabet than tree, 
      //Check Tree's left node for a nullptr
      case -1:
        //If the node's left child is a nullptr,
        //set the node to the child of the node
        if (tree->childL == nullptr)
        {
          tree->childL = bauble;
          bauble->parent = tree;
          cout << "Node successfully inserted as the left child of " << tree->model << "\n";
          break;
        }
        //Otherwise, set the check node nown a level and try again
        else
        {
          tree = tree->childL;
          goto compare;
        }
      //If bauble is later in the alphabet than tree, 
      //Check Tree's right node for a nullptr
      case 1:
        //If the node's left child is a nullptr,
        //set the node to the child of the node
        if (tree->childR == nullptr)
        {
          tree->childR = bauble;
          bauble->parent = tree;
          cout << "Node successfully inserted as the right child of " << tree->model << "\n";
          break;
        }
        //Otherwise, set the check node nown a level and try again
        else
        {
          tree = tree->childR;
          goto compare;
        }
      //If the nodes are the same, do not insert the node.
      case 0:
        cout << "Node already in tree. \n";
        break;

    }
  }
  //iterate back to the root of the modified tree before returning the tree
  while (tree->parent != nullptr)
  {
    tree = tree->parent;
  }
  //Return the modified tree
  return tree;
}

/* * * * * * * * * * * * * * * * * * *
 * deleteNode                        *
 * Algorithm that searches for a     *
 * node specified by the user and    *
 * deletes it, while preserving its  *
 * child nodes.                      *
 *                                   *
 * Input: TreeNode pointer to the    *
 *        root of a tree             *
 * Output: TreeNode pointer to the   *
 *         root of the tree given in *
 *         input, sans the requested *
 *         node                      *
 * * * * * * * * * * * * * * * * * * */

TreeNode* deleteNode(TreeNode* tree)
{
  TreeNode* slated = nullptr;
  
  //Ask for a node to be deleted
  //look for said node
  //set slated to that node
  string check;
  int comparitor;
  cout << "What node do you want to delete? (cAsE sEnSiTiVe, no_spaces)\n";
  cin >> check;

  //Look for the node in the tree with the same name as the string
  navigate1:
  comparitor = check.compare(tree->model);
  switch(comparitor)
  {
    //If the search term is less than the currently observed node
    case -1:
      //If the search ends with no node of the same name
      if (tree->childL == nullptr)
      {
        cout << "Could not find the node you are looking for.\nNo node will be deleted.\n";
        //Iterate back to the top of the tree and exit
        while (tree->parent != nullptr)
        {
          tree = tree->parent;
        }
        return tree;
      }
      //Otherwise descend a level
      else
      {
        tree = tree->childL;
        goto navigate1;
      }
    //If the search term is more than the currently observed node
    case 1:
      //If the search ends with no node of the same name
      if (tree->childR == nullptr)
        {
          cout << "Could not find the node you are looking for.\nNo node will be deleted.\n";
          //Iterate back to the top of the tree and exit
          while (tree->parent != nullptr)
          {
            tree = tree->parent;
          }
          return tree;
        }
      //Otherwise descend a level
      else
      {
        tree = tree->childR;
        goto navigate1;
      }
    //When it finds a node of the same name
    case 0:
      slated = tree;
      break;
  }
  //navigate back to the top of the tree
  while (tree->parent != nullptr)
  {
    tree = tree->parent;
  }
  
  //Save the children!
  TreeNode* orphanL;
  orphanL = slated->childL;
  TreeNode* orphanR;
  orphanR = slated->childR;
  bool orphanLIsNull = false;
  bool orphanRIsNull = false;
  if (orphanL == nullptr) {orphanLIsNull = true;}
  if (orphanR == nullptr) {orphanRIsNull = true;}

  //Decide which node to remove
  tree = slated->parent;
  bool directionIsL;
  if (slated->model.compare(tree->model) == -1)
  {
    directionIsL = true;
  }
  else if (slated->model.compare(tree->model) == 1)
  {
    directionIsL = false;
  }
  //if slated has no children:
  if (orphanLIsNull && orphanRIsNull)
  {
    //Depending on which side slated is on, set nullptrs accordingly
    if (directionIsL)
    {
      tree->childL = nullptr;
    }
    else if (!directionIsL)
    {
      tree->childR = nullptr;
    }
  }
  //If slated has a left child
  else if (!orphanLIsNull && orphanRIsNull)
  {
    //depending on which side slated is on, link left orphan to parent
    if (directionIsL)
    {
      tree->childL = orphanL;
    }
    else if (!directionIsL)
    {
      tree->childR = orphanL;
    }
  }
  //if slated has a right child
  else if (orphanLIsNull && !orphanRIsNull)
  {
    //depending on which side slated is on, link right orphan to parent
    if (directionIsL)
    {
      tree->childL = orphanR;
    }
    else if (!directionIsL)
    {
      tree->childR = orphanR;
    }
  }
  //if slated has two children
  else if (!orphanLIsNull && !orphanRIsNull)
  {
    //nullify the slated node as above
    if (directionIsL)
    {
      tree->childL = nullptr;
    }
    else if (!directionIsL)
    {
      tree->childR = nullptr;
    }
    //Insert the two orphan nodes back into the tree
    while (tree->parent != nullptr)
    {
      tree = tree->parent;
    }
    insertNode(tree,orphanL);
    insertNode(tree,orphanR);
  }
  //navigate back to the top of the tree
  while (tree->parent != nullptr)
  {
    tree = tree->parent;
  }
  return tree;
}  

/* * * * * * * * * * * * * * * * * * *
 * buildTree                         *
 * Method that manually builds the   *
 * tree of electric vehicles         *
 *                                   *
 * Input: None                       *
 * Output: cout success confirmation *
 * * * * * * * * * * * * * * * * * * */

void buildTree()
{
//Alphabetical Order:
//Bolt, e-tron, Ioniq, i3, Kona, LEAF, Model X, Model Y, Model 3, Niro


  TreeNode* node = new TreeNode("Kona", 104, nullptr);
  evTree = node;
  //Root node is Kona

  TreeNode* tempParent = evTree; //Kona
  node = new TreeNode("Ioniq", 102, tempParent);
  tempParent->childL = node;
  //Kona's left branch is Ioniq

  node = new TreeNode("Model_Y", 135, tempParent);
  tempParent->childR = node;
  //Kona's right branch is Model Y

  tempParent = tempParent->childL; //Ioniq
  node = new TreeNode("Bolt", 90, tempParent);
  tempParent->childL = node;
  //Ioniq's left branch is Bolt

  node = new TreeNode("i3", 93, tempParent);
  tempParent->childR = node;
  //Ioniq's right branch is i3

  tempParent = tempParent->childL;//Bolt
  node = new TreeNode("e-tron", 150, tempParent);
  tempParent->childR = node;
  //Bolt's right branch is e-tron

  tempParent = tempParent->parent;//Ioniq
  tempParent = tempParent->parent;//Kona
  tempParent = tempParent->childR;//Model Y
  
  node = new TreeNode("Model_X", 155, tempParent);
  tempParent->childL = node;
  //Model Y's left branch is Model X

  node = new TreeNode("Niro", 104, tempParent);
  tempParent->childR = node;
  //Model Y's right branch is Niro

  tempParent = tempParent->childL;//Model X
  node = new TreeNode("LEAF",90,tempParent);
  tempParent->childL = node;
  //Model X's left branch is LEAF

  tempParent = tempParent->parent;//Model Y
  tempParent = tempParent->childR;//Niro
  node = new TreeNode("Model_3", 145, tempParent);
  tempParent->childL = node;
  //Niro's left branch is Model 3

  cout << "Base tree initialized with 10 nodes.\n";

}

//main

int main()
{
  buildTree();
  cout << "\n";
  recursiveWalk(evTree);
  evTree = insertNode(evTree);
  evTree = insertNode(evTree, testNode);
  cout << "\n";
  recursiveWalk(evTree);
  evTree = deleteNode(evTree);
  cout << "\n";
  recursiveWalk(evTree);
}