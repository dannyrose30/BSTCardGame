#include "cards.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

CardBST::Card convertStringToCard(string line) {
  char suit = line[0]; //starts at index 1, returns character at zeroth index
  string value = line.substr(2); //starts at index 2 (after space), returns substring remainder of string (value string)
  CardBST::Card newCard(suit, value);
  return newCard;
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
  
  CardBST aliceBST, bobBST; //alice is cardFile1, bob is CardFile 2
  //Read each file and insert them into a tree 
  while (getline (cardFile1, line) && (line.length() > 0)){
    aliceBST.insert(convertStringToCard(line));
  }
  cardFile1.close();
  while (getline (cardFile2, line) && (line.length() > 0)){
    bobBST.insert(convertStringToCard(line));
  }
  cardFile2.close();

  CardBST::Card aliceGuess = aliceBST.getSmallestCard(); //starting at Alice's smallest card, use this to iterate forward hand
  CardBST::Card bobGuess = bobBST.getLargestCard();      //starting at Bob's largest card, use this to iterate back through hand

  while(!(aliceGuess== CardBST::Card()) && !(bobGuess == CardBST::Card())) {
     
    while(!(aliceGuess == CardBST::Card())) {
      if(bobBST.contains(aliceGuess)) {   //Alice guesses
       cout << "Alice picked matching card " << aliceGuess.suit << " " << aliceGuess.value << endl;
       aliceBST.remove(aliceGuess);
       bobBST.remove(aliceGuess);
       aliceGuess = aliceBST.getSmallestCard();
       bobGuess = bobBST.getLargestCard();
       break;
       }
      else
        aliceGuess = aliceBST.getSuccessor(aliceGuess);
    }
   while(!(bobGuess == CardBST::Card())) {
      if(aliceBST.contains(bobGuess)) {   //Bob guesses
        cout << "Bob picked matching card " << bobGuess.suit << " " << bobGuess.value << endl;
        aliceBST.remove(bobGuess);
        bobBST.remove(bobGuess);
        bobGuess = bobBST.getLargestCard();
        aliceGuess = aliceBST.getSmallestCard();
        break;
      }
      else
        bobGuess = bobBST.getPredecessor(bobGuess);
    }   
  }

  cout << endl << "Alice's cards:" << endl;
  aliceBST.printInOrder();

  cout << endl;

  cout << "Bob's cards:" << endl;
  bobBST.printInOrder();
  
  return 0;
}
