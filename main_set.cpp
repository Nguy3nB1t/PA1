// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2] << endl;
    return 1;
  }

  set<Card> aliceCards;
  set<Card> bobCards;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    istringstream iss(line);
    string suit, rank;
    if (iss >> suit >> rank) {
      Card card(suit, rank);
      aliceCards.insert(card);
    }
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    istringstream iss(line);
    string suit, rank;
    if (iss >> suit >> rank) {
      Card card(suit, rank);
      bobCards.insert(card);
    }
  }
  cardFile2.close();
  
  // Game loop: Alice and Bob alternate turns
  // Alice finds first matching card (smallest in her hand), Bob finds last matching card (largest in his hand)
  while (true) {
    // Alice's turn: find first matching card (iterate forward through her hand)
    set<Card>::iterator aliceIt = aliceCards.end();
    for (auto it = aliceCards.begin(); it != aliceCards.end(); ++it) {
      if (bobCards.find(*it) != bobCards.end()) {
        aliceIt = it;
        break;
      }
    }
    
    if (aliceIt == aliceCards.end()) {
      break; // No more matches
    }
    
    // Alice picks the matching card
    Card aliceMatch = *aliceIt;
    cout << "Alice picked matching card " << aliceMatch.toString() << endl;
    aliceCards.erase(aliceIt);
    bobCards.erase(aliceMatch);
    
    // Bob's turn: find last matching card (iterate backward through his hand)
    set<Card>::reverse_iterator bobIt = bobCards.rend();
    for (auto it = bobCards.rbegin(); it != bobCards.rend(); ++it) {
      if (aliceCards.find(*it) != aliceCards.end()) {
        bobIt = it;
        break;
      }
    }
    
    if (bobIt == bobCards.rend()) {
      break; // No more matches
    }
    
    // Bob picks the matching card
    Card bobMatch = *bobIt;
    cout << "Bob picked matching card " << bobMatch.toString() << endl;
    aliceCards.erase(bobMatch);
    bobCards.erase(bobMatch);
  }
  
  // Print remaining cards
  cout << endl << "Alice's cards:" << endl;
  for (const Card& card : aliceCards) {
    cout << card.toString() << endl;
  }
  
  cout << endl << "Bob's cards:" << endl;
  for (const Card& card : bobCards) {
    cout << card.toString() << endl;
  }
  
  return 0;
}
