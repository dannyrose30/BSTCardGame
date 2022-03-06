//cards.cpp
//Danny Rose
//Implementation of the classes defined in cards.h

#include "cards.h"
#include <string>

//consturctor makes empty tree
CardBST::CardBST(): root(nullptr) { };

//destructor to delete all CardNodes
CardBST::~CardBST() {
    clear(root); //using recursive helper function passing in root to begin
}

//recursive helper for destructor, uses postOrder algorithm to delete
void CardBST::clear(CardBST::CardNode* n) {
    if(n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

//copy constructor
CardBST::CardBST(const CardBST &bst) {
    this->root = nullptr; //need to assign root to nullptr for insert()
    addPreOrder(bst.root); //copies implicit bst by passing in its root pointer
}

//recursive helper for copy constructor, using PreOrder algorithm to add in same order
void CardBST::addPreOrder(CardBST::CardNode* n) {
    if(n) {         //if it's null then it won't add any nodes
    insert(n->card); //adds root then top node of each subtree (pre-order)
    if(n->left)
        addPreOrder(n->left);
    if(n->right)
        addPreOrder(n->right);
    }
}

bool operator==(const CardBST::Card &c1, const CardBST::Card &c2) { 
            return (c1.suit == c2.suit && c1.value == c2.value); //if both members equal than cards are equal
        }

bool operator<(const CardBST::Card &c1, const CardBST::Card &c2) {
            char suit1 = c1.suit;
            char suit2 = c2.suit;
            int value1, value2;
            if(c1.value == "a" || c1.value == "j" || c1.value == "q" || c1.value == "k") { //c1.value isn't a number
                if(c1.value == "a")
                    value1 = 0;
                else if(c1.value == "j") 
                    value1 = 11;
                else if(c1.value == "q")
                    value1 = 12;
                else    
                    value1 = 13;
            }
            else {              //c1.value is a number
                value1 = stoi(c1.value);
            }

            if(c2.value == "a" || c2.value == "j" || c2.value == "q" || c2.value == "k") { //c2.value isn't a number
                if(c2.value == "a")
                    value2 = 0;
                else if(c2.value == "j") 
                    value2 = 11;
                else if(c2.value == "q")
                    value2 = 12;
                else    
                    value2 = 13;
            }
            else {              //c2.value is a number
                value2 = stoi(c2.value);
            }

            //Case 1: Same suit
            if(suit1 == suit2) {
                if(value1 == value2)
                    return false;
                else 
                    return (value1 < value2);
            }
            //Case 2: Different suit
            else {
                if(suit1 == 'c')                            //if suit1 is clubs
                    return true;                            //always smaller
                else if(suit1 == 'd') {                     //if suit1 is diamonds
                    return (suit2 == 's' || suit2 == 'h');  //if suit2 is spades or heart
                }
                else if(suit1 == 's')                       //if suit1 is spades
                    return (suit2 == 'h');                  //if suit2 is hearts
            }
            return false; //suit 1 is diamonds, suit 2 is different
}

bool operator>(const CardBST::Card &c1, const CardBST::Card &c2) {
    return (!(c1==c2) && !(c1<c2)); //if both equal-to and less-than fail then c1 is greater than c2
}
//insert Card in tree, return true if successful, false if duplicate 
bool CardBST::insert(CardBST::Card c) {
    //first deal with empty tree
    if(!root) {
        root = new CardNode(c);
        return true; //CardNode inserted
    }
    //otherwise use recursive helper
    //pass in root at first, as usual (to iterate through tree)
    return insertHelper(c, root); //will return bool representing success of insert of recursive helper
}

//recursive helper for insert (assumes n is NEVER nullptr because we checked that in insert())
//also returns true if successful, false if not
bool CardBST::insertHelper(CardBST::Card c, CardBST::CardNode* n) {
    if(c == n->card) //each CardNode must be unique
        return false;
    if(c < n->card) { //if card smaller than n's card
        if(n->left)   //if left subtree exists
            return insertHelper(c, n->left); //recursive call
    else {
        n->left = new CardNode(c);         //no left subtree, mamke new Card Node (leaf)
        n->left->parent = n;
        return true;
    }
    }else{          //if card smaller than n's card
        if(n->right) //if right subtree exists
            return insertHelper(c, n->right); //recursive call
        else {
            n->right = new CardNode(c);     //no right subtree, make new CardNode(leaf)
            n->right->parent = n;
            return true;
        }
    }
}

//print CardBST data pre-order
void CardBST::printPreOrder() const {
    printPreOrderHelper(root);
}

//recursive helper for printPreOrder()
void CardBST::printPreOrderHelper(CardBST::CardNode* n) const {
    if(n) {     //not null tree
        cout << n->card.suit << " " << n->card.value << endl;
        printPreOrderHelper(n->left);
        printPreOrderHelper(n->right);
    }
}

//print CardBST data in-order
void CardBST::printInOrder() const {
    printInOrderHelper(root);
}

//recursive helper for printInOrder()
void CardBST::printInOrderHelper(CardBST::CardNode* n) const {
    if(n) { //not a null tree
        printInOrderHelper(n->left);
        cout << n->card.suit << " " << n->card.value << endl;
        printInOrderHelper(n->right);
    }
}

//returns CardNode* to smallest Card or nullptr if none exists
CardBST::CardNode* CardBST::getSmallestCardNode() const {
    CardNode* n = root;
    if(!n) { //empty tree
        return nullptr;
    }
    while(n && n->left) {
        n = n->left;
    }
    return n;
}

//returns smallest Card or Card() if none exists
CardBST::Card CardBST::getSmallestCard() const {
    return ( getSmallestCardNode() ) ? getSmallestCardNode()->card: Card(); 
}

CardBST::CardNode* CardBST::getLargestCardNode() const {
    CardNode* n = root;
    if(!n) { //empty tree
        return nullptr;
    }
    while(n && n->right) {
        n= n->right;
    }
    return n;
}

//returns smallest Card or Card() if none exists
CardBST::Card CardBST::getLargestCard() const {
    return ( getLargestCardNode() ) ? getLargestCardNode()->card: Card(); 
}


//returns CardNode* to node for a given Card or nullptr if none exists
CardBST::CardNode* CardBST::getCardNodeFor(Card c, CardNode* n) const {
    if(!n) { //empty tree
        return nullptr;
    }else if (n->card == c) {
        return n;
    }else if (c < n->card) {
        return getCardNodeFor(c, n->left);
    }else{
        return getCardNodeFor(c, n->right);
    }
}

//returns true if Card is in the BST, false if none
bool CardBST::contains(CardBST::Card c) const {
    return (getCardNodeFor(c, root) != nullptr);
}

//returns a pointer to the CardNode containing the predecessor of the given Card
CardBST::CardNode* CardBST::getPredecessorCardNode(Card c) const {
    //CASE 1: There's a left subtree, return rightmost leaf
    //CASE 2: There's no left subtree, parse through parents until smaller
    //(CASE 3): No parent with larger, return 0

    CardNode* n = getCardNodeFor(c, root);
    if(root==NULL) {
        return NULL;
    }
    if(n->left) { //there is a left subtree--CASE 1
        n = n->left; //go to left child
        while(n->right) { //there is right subtree
            n = n->right; //go to right child until last
        }
        return n; //returns predecessor CASE 1
    }else{      //there might be a parent, find node with value less than key "value"-CASE 2
        while(n->parent) { //while there is a parent
            if(n->parent->card < c) { //if parent Card is less than
            return n->parent; //returns predecessor CASE 2
            }
            n = n->parent; //update n to be be parent, regardless if predecessor
            }
        }
            return n->parent;  //if no predecessor (no left subtree, no smaller parent), n is root, retu    rns null (root's parent) CASE 3
    }

//returns the predecesssor Card of the given value or 0 if there is none
CardBST::Card CardBST::getPredecessor(Card c) const {
    return ( getPredecessorCardNode(c) ) ? getPredecessorCardNode(c)->card: Card();
}

//returns a pointer to the CardNode containing the predecessor of the given Card
CardBST::CardNode* CardBST::getSuccessorCardNode(Card c) const {
    //CASE 1: There's a right subtree, return leftmost leaf
    //CASE 2: There's no right subtree, parse through parents until larger
    //(CASE 3): No parent with larger, return 0
    CardNode* n = getCardNodeFor(c, root);
    if(root==NULL) {
        return NULL;
    }
    if(n->right) { //there is a right subtree
        n = n->right; //go to right child
        while(n->left) { //there is left subtree of main right subtree
            n = n->left; //go to right child until last
        }
            return n; //returns predecessor CASE 1
        }else{      //there might be a parent, find node with value greater than     key "value"
            while(n->parent) { //while there is a parent
                if(n->parent->card > c) { //if parent info is greater than
                return n->parent; //returns predecessor CASE 2
                }
                n = n->parent; //update n to be be parent, regardless if predecessor
            }
        }
            return n->parent;  //if no predecessor, n is root, returns null CASE     3 
    }
//returns the successor Card of the given value or empty Card if there is none
CardBST::Card CardBST::getSuccessor(Card c) const {
    return ( getSuccessorCardNode(c) ) ? getSuccessorCardNode(c)->card: Card();
}

// deletes the CardNode containing the given Card from the tree
// returns true if the Cardnode exists and was deleted, false if the Cardnode does not exist
bool CardBST::remove(Card c){
    //CASE 1: It's a leaf, so just delete the leaf then set the child to null
    //CASE 2: It has one child, so you just replace the node with it's child
    //CASE 3: It has two children, so you replace the node with it's successor
    CardNode* currentNode = getCardNodeFor(c, root); //Start at root
    CardNode* parent = currentNode->parent; //Making a parent node because we'll change it later

    //CASE 1
    if(currentNode->left == nullptr && currentNode->right == nullptr) {
        if(parent == nullptr){ //if root is nullptr
            root = nullptr;
        }
        else if (parent->left == currentNode){ //it's left child
            parent->left = nullptr;
        }else{
            parent->right = nullptr;
        }
        delete currentNode; //everything that points to it is null
        return true; //Node found, deleted
    }
    //CASE 2
    else if(currentNode->left && currentNode->right == nullptr) { //LEFT CHILD
        if(parent == nullptr) { //node is root
            root = currentNode->left; //node is left child of root
        }
        else if(parent->left == currentNode) {  //left child
            parent->left = currentNode->left;
        }else{                                  //right child
            parent->right = currentNode->left;
        }
        currentNode->left->parent = parent;     //make left child's parent point to current Node's parent
        delete currentNode;
        return true;
    }
   else if(currentNode->right && currentNode->left == nullptr) { //RIGHT CHILD
        if(parent == nullptr) { //node is root
            root = currentNode->right; //node is left child of root
        }
        else if(parent->left == currentNode) { //left child
            parent->left = currentNode->right; 
        }else{                                  //right child
            parent->right = currentNode->right;
        }
        currentNode->right->parent = parent;    //make right child's parent point to current Node's parent
        delete currentNode;
        return true;
    } 
    //CASE 3
    else {                                      //two children, use recursion                             
        CardNode* successor = getSuccessorCardNode(c);
        Card tempSuccessorCard = successor->card;
        remove(successor->card);                //recursive call to delete successor node
        currentNode->card = tempSuccessorCard; //copies it
        return true;
    }
    return false; //node not found
}