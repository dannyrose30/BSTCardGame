//cards.h
//Danny Rose
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
using namespace std;

class CardBST {
    public:

        struct Card { //creates a struct to define a Card as a (public) datatype in each CardNode (defined below)
            char suit;
            string value;
            Card(char s=0, string v=""): suit(s), value(v) {}
            };

        CardBST();                   // constructor
        ~CardBST();                  // destructor   
        CardBST(const CardBST &bst);     //copy constructor
        CardBST& operator=(const CardBST& source); //copy assignment
        bool insert(Card c);     // insert Card; return false if duplicate
        friend bool operator==(const Card &c1, const Card &c2); //overloaded == implemented as a non-member function
        friend bool operator<(const Card &c1, const Card &c2); //overloaded < implemented as non-member function
        friend bool operator>(const Card &c1, const Card &c2); //overloaded > implemented as non-member function

        bool remove(Card c);    // deletes node with given Card from the CardsBST tree 
        void printPreOrder() const; // prints tree data pre-order to cout, 
                                    //using this algorithm because it mimics the order inserted
        void printInOrder() const;  //prints tree data in-order to cout
        bool contains(Card c) const;      //returns true if Card is in the CardBST 
        Card getSmallestCard() const;        //returns the smallest Card
        Card getLargestCard() const;         //returns the largest Card
        Card getPredecessor(Card c) const; //returns predecessor value of given Card, 0 if none
        Card getSuccessor(Card c) const; //returns the successor value of given Card, 0 if none

    private:

        struct CardNode { //creates a struct for each CardNode
            Card card;
            CardNode *left, *right, *parent;
            CardNode(Card c = Card()): card(Card(c.suit, c.value)), left(nullptr), right(nullptr), parent(nullptr) {}
            //constructor--Note: card(c) uses Card's copy constructor, copies values
        };

        //one private instance variable, the pointer to the root CardNode
        CardNode *root;

        //recursive utility functions for public methods above
        CardNode* getCardNodeFor(Card c, CardNode* n) const; //returns node pointer for card values, nullptr if it doesn't exist. 
        void clear(CardNode *n); //clears all CardNodes for destructor
        bool insertHelper(Card c, CardNode* n); 
        void printPreOrderHelper(CardNode* n) const;
        void printInOrderHelper(CardNode* n) const;
        void addPreOrder(CardNode* n); //recursive helper for copy constructor
        CardNode* getSmallestCardNode() const; //recursive helper for getSmallestCard
        CardNode* getLargestCardNode() const;  //recursive helper for getLargestCard
        CardNode* getSuccessorCardNode(Card c) const; //returns pointer to CardNode containing given info
        CardNode* getPredecessorCardNode(Card c) const; //returns pointer to CardNode containing given info
};


#endif
