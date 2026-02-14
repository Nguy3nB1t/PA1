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
    return 1; // Bruh, read the instructions
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
  // Bruh, this is basically Go Fish but they're both terrible at it 💀
  while (true) {
    // Alice's turn: find first matching card (iterate forward through her hand)
    // She's going through her cards like "is this it? no... is THIS it?"
    set<Card>::iterator aliceIt = aliceCards.end();
    for (auto it = aliceCards.begin(); it != aliceCards.end(); ++it) {
      if (bobCards.find(*it) != bobCards.end()) {
        aliceIt = it;
        break; // Found it! Finally...
      }
    }
    
    if (aliceIt == aliceCards.end()) {
      break; // No more matches - game over, they gave up
    }
    
    // Alice picks the matching card
    Card aliceMatch = *aliceIt;
    cout << "Alice picked matching card " << aliceMatch.toString() << endl;
    aliceCards.erase(aliceIt);
    bobCards.erase(aliceMatch); // Bob loses that card too, rip
    
    // Bob's turn: find last matching card (iterate backward through his hand)
    // Bob's out here going backwards like "let me check the biggest ones first"
    set<Card>::reverse_iterator bobIt = bobCards.rend();
    for (auto it = bobCards.rbegin(); it != bobCards.rend(); ++it) {
      if (aliceCards.find(*it) != aliceCards.end()) {
        bobIt = it;
        break; // Gotcha!
      }
    }
    
    if (bobIt == bobCards.rend()) {
      break; // No more matches - this buggin? They're done
    }
    
    // Bob picks the matching card
    Card bobMatch = *bobIt;
    cout << "Bob picked matching card " << bobMatch.toString() << endl;
    aliceCards.erase(bobMatch); // Alice loses that one too
    bobCards.erase(bobMatch);
  }
  
  // Print remaining cards - what's left after they've matched everything they could
  cout << endl << "Alice's cards:" << endl;
  for (const Card& card : aliceCards) {
    cout << card.toString() << endl;
  }
  
  cout << endl << "Bob's cards:" << endl;
  for (const Card& card : bobCards) {
    cout << card.toString() << endl;
  }
  // Game over! They're both stuck with unmatched cards now 💀
  
  return 0;
}
