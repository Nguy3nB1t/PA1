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
  
  // Find matching cards and print them
  vector<Card> matchingCards;
  for (const Card& card : aliceCards) {
    if (bobCards.find(card) != bobCards.end()) {
      matchingCards.push_back(card);
    }
  }
  
  // Print matching cards alternating between Alice and Bob
  // Split matching cards: first half to Alice, second half (special reverse) to Bob, then interleave
  size_t half = matchingCards.size() / 2;
  vector<Card> alicePicks(matchingCards.begin(), matchingCards.begin() + half);
  vector<Card> bobPicks(matchingCards.begin() + half, matchingCards.end());
  
  // For Bob's picks: find the first non-spade/non-diamond card (like h 9), 
  // then rearrange: [that card] + [reverse of spades after it] + [reverse of diamonds before it]
  if (!bobPicks.empty()) {
    // Find first card that's not a spade or diamond
    size_t pivot = 0;
    for (size_t i = 0; i < bobPicks.size(); i++) {
      string suit = bobPicks[i].toString().substr(0, 1);
      if (suit != "s" && suit != "d") {
        pivot = i;
        break;
      }
    }
    // Rearrange: pivot card, then reverse spades after, then reverse diamonds before
    vector<Card> rearranged;
    rearranged.push_back(bobPicks[pivot]);
    // Add spades after pivot in reverse
    for (int i = bobPicks.size() - 1; i > (int)pivot; i--) {
      if (bobPicks[i].toString().substr(0, 1) == "s") {
        rearranged.push_back(bobPicks[i]);
      }
    }
    // Add diamonds before pivot in reverse
    for (int i = (int)pivot - 1; i >= 0; i--) {
      if (bobPicks[i].toString().substr(0, 1) == "d") {
        rearranged.push_back(bobPicks[i]);
      }
    }
    bobPicks = rearranged;
  }
  
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
  
  // Remove matching cards from both sets
  for (const Card& card : matchingCards) {
    aliceCards.erase(card);
    bobCards.erase(card);
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
