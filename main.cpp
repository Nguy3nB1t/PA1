// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

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

  CardList aliceCards;
  CardList bobCards;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    istringstream iss(line);
    string suit, rank;
    if (iss >> suit >> rank) {
      Card card(suit, rank);
      aliceCards.add(card);
    }
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    istringstream iss(line);
    string suit, rank;
    if (iss >> suit >> rank) {
      Card card(suit, rank);
      bobCards.add(card);
    }
  }
  cardFile2.close();
  
  // Game loop: Alice and Bob alternate turns
  // Alice finds first matching card (smallest in her hand), Bob finds last matching card (largest in his hand)
  // Same game logic but with our custom BST - no std::set cheating here 😤
  while (true) {
    // Alice's turn: find first matching card (iterate forward through her hand)
    // She's methodical, going through cards one by one like a robot
    vector<Card> aliceCardVec;
    aliceCards.getCards(aliceCardVec);
    
    Card aliceMatch("", "");
    bool aliceFound = false;
    for (const Card& card : aliceCardVec) {
      if (bobCards.contains(card)) {
        aliceMatch = card;
        aliceFound = true;
        break; // Found one! Let's gooo
      }
    }
    
    if (!aliceFound) {
      break; // No more matches - they're both out of luck
    }
    
    // Alice picks the matching card
    cout << "Alice picked matching card " << aliceMatch.toString() << endl;
    aliceCards.remove(aliceMatch);
    bobCards.remove(aliceMatch); // Bob's card collection just got smaller 💀
    
    // Bob's turn: find last matching card (iterate backward through his hand)
    // Bob's doing the reverse strategy - "biggest first, why not?"
    vector<Card> bobCardVec;
    bobCards.getCards(bobCardVec);
    
    Card bobMatch("", "");
    bool bobFound = false;
    // Iterate backward through Bob's cards (from largest to smallest)
    // Going backwards like he's reading a book from the end
    for (int i = bobCardVec.size() - 1; i >= 0; i--) {
      if (aliceCards.contains(bobCardVec[i])) {
        bobMatch = bobCardVec[i];
        bobFound = true;
        break; // Score!
      }
    }
    
    if (!bobFound) {
      break; // No more matches - this is getting boring
    }
    
    // Bob picks the matching card
    cout << "Bob picked matching card " << bobMatch.toString() << endl;
    aliceCards.remove(bobMatch); // Alice loses that one
    bobCards.remove(bobMatch);
  }
  
  // Print remaining cards
  cout << endl << "Alice's cards:" << endl;
  aliceCards.print();
  
  cout << endl << "Bob's cards:" << endl;
  bobCards.print();
  
  return 0;
}
