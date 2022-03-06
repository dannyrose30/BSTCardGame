//test_cardbst.cpp

#include "cards.h"

#include <iostream>
#include <cassert>
using namespace std;

#include <string> 
#include <cctype> 
#include <typeinfo>

int main() {


    cout << "Testing overloaded operators for Card struct:" << endl;
    CardBST::Card c1('d', "k");
    CardBST::Card c2('d', "q");
    CardBST::Card c3('d', "k");
    cout << (c1>c2) << endl; //should print 1
    cout << (c1<c2) << endl; //should print 0
    cout << (c1==c3) << endl << endl; //should print 1


    CardBST cardbst1, cardbst2; //cardbst1 has values, cardbst2 is empty
    cardbst1.insert(CardBST::Card('h', "10"));
    cardbst1.insert(CardBST::Card('c', "k"));
    cardbst1.insert(CardBST::Card('s', "3"));
    cardbst1.insert(CardBST::Card('c', "a"));
    cardbst1.insert(CardBST::Card('h', "j"));
    cardbst1.insert(CardBST::Card('d', "3"));

    cout << "CardBST class function tests:" << endl << endl; 
    cout << "Testing a CardBST with values..." << endl << endl;
    //insert (first time) and print preorder test
    cout << "pre-order:" << endl;
    cardbst1.printPreOrder();
    cout << endl;

    //print inorder test
    cout << "in-order:" << endl;
    cardbst1.printInOrder();
    cout << endl;

    cout << "copyConstructor test:" << endl; 
    CardBST cardbst3{cardbst1};
    cardbst3.printPreOrder(); //should print same preorder as cardbst1
    cout << endl;

    cout << "copyAssignment test:" << endl;
    CardBST cardbst4 = cardbst3;
    cardbst4.printPreOrder(); //should print same preorder as cardbst
    cout << endl;

    cout << "contains test:" << endl;
    assert(cardbst1.contains(CardBST::Card('h', "j")) == true); //using assert to check
    cout << "Contains h j: " << cardbst1.contains(CardBST::Card('h', "j")) << endl;
    assert(cardbst1.contains(CardBST::Card('s', "a")) == false);
    cout << "Contains s a: " << cardbst1.contains(CardBST::Card('s', "a")) << endl;
    cout << "PASSED CONTAINS TEST" << endl << endl;

    cout << "getSmallestCard test:" << endl;
    assert(cardbst1.getSmallestCard() == CardBST::Card('c', "a"));
    cout << "Smallest card is: " << cardbst1.getSmallestCard().suit << " " << cardbst1.getSmallestCard().value << endl;
    cout << "PASSED SMALLEST CARD TEST" << endl << endl;

    cout << "getLargestCard test:" << endl;
    assert(cardbst1.getLargestCard() == CardBST::Card('h', "j"));
    cout << "Largest card is: " << cardbst1.getLargestCard().suit << " " << cardbst1.getLargestCard().value << endl;
    cout << "PASSED LARGEST CARD TEST" << endl << endl;

    cout << "getPredecessor test:" << endl;
    assert(cardbst1.getPredecessor(CardBST::Card('d', "3")) == CardBST::Card('c', "k"));
    cout << "Predecessor of d 3 is: " << cardbst1.getPredecessor(CardBST::Card('d', "3")).suit << " ";
    cout << cardbst1.getPredecessor(CardBST::Card('d', "3")).value << endl;
    assert(cardbst1.getPredecessor(CardBST::Card('h', "j")) == CardBST::Card('h', "10"));
    cout << "Predecessor of h j is: " << cardbst1.getPredecessor(CardBST::Card('h', "j")).suit << " ";
    cout << cardbst1.getPredecessor(CardBST::Card('h', "j")).value << endl;
    assert(cardbst1.getPredecessor(CardBST::Card('h', "10")) == CardBST::Card('s', "3"));
    cout << "Predecessor of h 10 is: " << cardbst1.getPredecessor(CardBST::Card('h', "10")).suit << " ";
    cout << cardbst1.getPredecessor(CardBST::Card('h', "10")).value << endl;
    assert(cardbst1.getPredecessor(CardBST::Card('c', "a")) == CardBST::Card());
    cout << "Predecessor of c a is: " << cardbst1.getPredecessor(CardBST::Card('c', "a")).suit << " ";
    cout << cardbst1.getPredecessor(CardBST::Card('c', "a")).value << endl;
    cout << "PASSED PREDECESSOR TEST" << endl << endl;

    cout << "getSuccessor test:" << endl;
    assert(cardbst1.getSuccessor(CardBST::Card('c', "a")) == CardBST::Card('c', "k"));
    cout << "Successor of c a is: " << cardbst1.getSuccessor(CardBST::Card('c', "a")).suit << " ";
    cout << cardbst1.getSuccessor(CardBST::Card('c', "a")).value << endl;
    assert(cardbst1.getSuccessor(CardBST::Card('h', "j")) == CardBST::Card());
    cout << "Successor of h j is: " << cardbst1.getSuccessor(CardBST::Card('h', "j")).suit << " ";
    cout << cardbst1.getSuccessor(CardBST::Card('h', "j")).value << endl;
    cout << "PASSED SUCCESSOR TEST" << endl << endl;

    cout << "remove test:" << endl;
    cout << "Current CardBST:" << endl;
    cardbst1.printPreOrder();
    cout << endl << "Removing h j..." << endl;
    assert(cardbst1.remove(CardBST::Card('h', "j")));
    cardbst1.printPreOrder();
    /*cout << endl << "Removing h 10..." << endl;
    assert(cardbst1.remove(CardBST::Card('h', "10")));
    cardbst1.printPreOrder();*/
    cout << endl << "Removing c k..." << endl;
    assert(cardbst1.remove(CardBST::Card('c', "k")));
    cardbst1.printPreOrder(); 

    cout << endl << "getPredecessor test part 2:" << endl;
    assert(cardbst1.getPredecessor(CardBST::Card('c', "a")) == CardBST::Card());
    cout << "Predecessor of c a is: " << cardbst1.getPredecessor(CardBST::Card('c', "a")).suit << " ";
    cout << cardbst1.getPredecessor(CardBST::Card('c', "a")).value << endl;
    

    cout << endl << "getSuccessor test part 2:" << endl;
    assert(cardbst1.getSuccessor(CardBST::Card('h', "10")) == CardBST::Card());
    cout << "Successor of h 10 is: " << cardbst1.getSuccessor(CardBST::Card('h', "10")).suit << " ";
    cout << cardbst1.getSuccessor(CardBST::Card('h', "10")).value << endl;
    assert(cardbst1.getSuccessor(CardBST::Card('s', "3")) == CardBST::Card('h', "10"));
    cout << "Successor of s 3 is: " << cardbst1.getSuccessor(CardBST::Card('s', "3")).suit << " ";
    cout << cardbst1.getSuccessor(CardBST::Card('s', "3")).value << endl;

    cout << endl << "Testing an empty CardBST..." << endl << endl;
    //insert (first time) and print preorder test
    cout << "pre-order:" << endl;
    cardbst2.printPreOrder();
    cout << endl;

    //print inorder test
    cout << "in-order:" << endl;
    cardbst2.printInOrder();
    cout << endl;

    cout << "copyConstructor test:" << endl; 
    CardBST cardbst5{cardbst2};
    cardbst5.printPreOrder(); //should print same preorder as cardbst1
    cout << endl;

    cout << "copyAssignment test:" << endl;
    CardBST cardbst6 = cardbst2;
    cardbst6.printPreOrder(); //should print same preorder as cardbst
    cout << endl;

    cout << "contains test:" << endl;
    assert(cardbst2.contains(CardBST::Card('h', "j")) == false); //using assert to check
    cout << "Contains h j: " << cardbst2.contains(CardBST::Card('h', "j")) << endl;
    cout << "PASSED CONTAINS TEST" << endl << endl;

    cout << "getSmallestCard test:" << endl;
    assert(cardbst2.getSmallestCard() == CardBST::Card());
    cout << "Smallest card is: " << cardbst2.getSmallestCard().suit << " " << cardbst2.getSmallestCard().value << endl;
    cout << "PASSED SMALLEST CARD TEST" << endl << endl;

    cout << "getLargestCard test:" << endl;
    assert(cardbst2.getLargestCard() == CardBST::Card());
    cout << "Largest card is: " << cardbst2.getLargestCard().suit << " " << cardbst2.getLargestCard().value << endl;
    cout << "PASSED LARGEST CARD TEST" << endl << endl;

    cout << "getPredecessor test:" << endl;
    assert(cardbst2.getPredecessor(CardBST::Card('d', "3")) == CardBST::Card());
    cout << "Predecessor of d 3 is: " << cardbst2.getPredecessor(CardBST::Card('d', "3")).suit << " ";
    cout << cardbst2.getPredecessor(CardBST::Card('d', "3")).value << endl;
    cout << "PASSED PREDECESSOR TEST" << endl << endl;

    cout << "getSuccessor test:" << endl;
    assert(cardbst2.getSuccessor(CardBST::Card('c', "a")) == CardBST::Card());
    cout << "Successor of c a is: " << cardbst2.getSuccessor(CardBST::Card('c', "a")).suit << " ";
    cout << cardbst2.getSuccessor(CardBST::Card('c', "a")).value << endl;
    cout << "PASSED SUCCESSOR TEST" << endl << endl;

    return 0;
}
