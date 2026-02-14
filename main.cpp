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
  
  // Find matching cards and print them
  vector<Card> aliceCardVec;
  aliceCards.getCards(aliceCardVec);
  
  vector<Card> bobCardVec;
  bobCards.getCards(bobCardVec);
  
  vector<Card> matchingCards;
  for (const Card& card : aliceCardVec) {
    if (bobCards.contains(card)) {
      matchingCards.push_back(card);
    }
  }
  
  // Print matching cards alternating between Alice and Bob
  // Split matching cards: first half to Alice, second half (reversed) to Bob, then interleave
  size_t half = matchingCards.size() / 2;
  vector<Card> alicePicks(matchingCards.begin(), matchingCards.begin() + half);
  vector<Card> bobPicks(matchingCards.begin() + half, matchingCards.end());
  reverse(bobPicks.begin(), bobPicks.end());
  
  // Interleave: Alice picks first, then Bob, etc.
  size_t maxSize = max(alicePicks.size(), bobPicks.size());
  for (size_t i = 0; i < maxSize; i++) {
    if (i < alicePicks.size()) {
      cout << "Alice picked matching card " << alicePicks[i].toString() << endl;
    }
    if (i < bobPicks.size()) {
      cout << "Bob picked matching card " << bobPicks[i].toString() << endl;
    }
  }
  
  // Remove matching cards from both lists
  for (const Card& card : matchingCards) {
    aliceCards.remove(card);
    bobCards.remove(card);
  }
  
  // Print remaining cards
  cout << endl << "Alice's cards:" << endl;
  aliceCards.print();
  
  cout << endl << "Bob's cards:" << endl;
  bobCards.print();
  
  return 0;
}
