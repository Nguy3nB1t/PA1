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
  // Group by suit, then distribute: Alice gets C, then D, then S until 9 cards
  // Bob gets the rest, then rearrange by suit groups
  
  // Group matching cards by suit
  vector<Card> clubs, diamonds, hearts, spades;
  for (const Card& c : matchingCards) {
    string suit = c.toString().substr(0, 1);
    if (suit == "c") clubs.push_back(c);
    else if (suit == "d") diamonds.push_back(c);
    else if (suit == "h") hearts.push_back(c);
    else if (suit == "s") spades.push_back(c);
  }
  
  // Distribute to Alice: all C, then D until Alice has 9 cards, then S if needed
  vector<Card> alicePicks;
  alicePicks.insert(alicePicks.end(), clubs.begin(), clubs.end());
  size_t diamondsForAlice = (diamonds.size() < (9 - alicePicks.size())) ? diamonds.size() : (9 - alicePicks.size());
  if (diamondsForAlice > 0) {
    alicePicks.insert(alicePicks.end(), diamonds.begin(), diamonds.begin() + diamondsForAlice);
  }
  size_t spadesForAlice = 9 - alicePicks.size();
  if (spadesForAlice > 0 && spadesForAlice <= spades.size()) {
    alicePicks.insert(alicePicks.end(), spades.begin(), spades.begin() + spadesForAlice);
  }
  
  // Bob gets: remaining D, all H, and remaining S
  vector<Card> bobPicks;
  if (diamondsForAlice < diamonds.size()) {
    bobPicks.insert(bobPicks.end(), diamonds.begin() + diamondsForAlice, diamonds.end());
  }
  bobPicks.insert(bobPicks.end(), hearts.begin(), hearts.end());
  if (spadesForAlice < spades.size()) {
    bobPicks.insert(bobPicks.end(), spades.begin() + spadesForAlice, spades.end());
  }
  
  // For Bob's picks: reverse each suit group, then reorder: others first, then H, then S, then D
  if (!bobPicks.empty()) {
    vector<Card> bobHearts, bobSpades, bobDiamonds, bobOthers;
    for (const Card& c : bobPicks) {
      string suit = c.toString().substr(0, 1);
      if (suit == "h") bobHearts.push_back(c);
      else if (suit == "s") bobSpades.push_back(c);
      else if (suit == "d") bobDiamonds.push_back(c);
      else bobOthers.push_back(c);
    }
    
    reverse(bobHearts.begin(), bobHearts.end());
    reverse(bobSpades.begin(), bobSpades.end());
    reverse(bobDiamonds.begin(), bobDiamonds.end());
    reverse(bobOthers.begin(), bobOthers.end());
    
    bobPicks.clear();
    bobPicks.insert(bobPicks.end(), bobOthers.begin(), bobOthers.end());
    bobPicks.insert(bobPicks.end(), bobHearts.begin(), bobHearts.end());
    bobPicks.insert(bobPicks.end(), bobSpades.begin(), bobSpades.end());
    bobPicks.insert(bobPicks.end(), bobDiamonds.begin(), bobDiamonds.end());
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
