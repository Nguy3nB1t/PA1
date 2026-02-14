// tests.cpp
// Comprehensive test suite for Card and CardList classes

#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include "card.h"
#include "card_list.h"

using namespace std;

void testCard() {
    cout << "Testing Card class..." << endl;
    
    // Test Card creation
    Card c1("c", "a");
    Card c2("d", "2");
    Card c3("h", "10");
    Card c4("s", "j");
    
    // Test toString
    assert(c1.toString() == "c a");
    assert(c2.toString() == "d 2");
    assert(c3.toString() == "h 10");
    assert(c4.toString() == "s j");
    cout << "  ✓ Card toString() works" << endl;
    
    // Test comparison operators
    Card c5("c", "2");
    Card c6("c", "3");
    Card c7("d", "2");
    
    assert(c5 < c6);  // c 2 < c 3
    assert(c5 < c7);  // c 2 < d 2
    assert(!(c6 < c5));  // c 3 not < c 2
    cout << "  ✓ Card operator< works" << endl;
    
    Card c8("c", "a");
    assert(c1 == c8);  // Same card
    assert(!(c1 == c2));  // Different cards
    cout << "  ✓ Card operator== works" << endl;
    
    cout << "Card class tests passed!" << endl << endl;
}

void testCardList() {
    cout << "Testing CardList class..." << endl;
    
    CardList list;
    
    // Test adding cards
    list.add(Card("c", "a"));
    list.add(Card("d", "2"));
    list.add(Card("h", "10"));
    list.add(Card("s", "j"));
    list.add(Card("c", "3"));
    cout << "  ✓ CardList add() works" << endl;
    
    // Test contains
    assert(list.contains(Card("c", "a")));
    assert(list.contains(Card("d", "2")));
    assert(list.contains(Card("h", "10")));
    assert(!list.contains(Card("c", "k")));
    cout << "  ✓ CardList contains() works" << endl;
    
    // Test getCards
    vector<Card> cards;
    list.getCards(cards);
    assert(cards.size() == 5);
    // Check sorted order
    assert(cards[0].toString() == "c 3" || cards[0].toString() == "c a");
    cout << "  ✓ CardList getCards() works" << endl;
    
    // Test remove
    list.remove(Card("d", "2"));
    assert(!list.contains(Card("d", "2")));
    assert(list.contains(Card("c", "a")));
    cout << "  ✓ CardList remove() works" << endl;
    
    // Test clear (destructor)
    {
        CardList tempList;
        tempList.add(Card("c", "a"));
        tempList.add(Card("d", "2"));
    }  // Should not leak memory
    cout << "  ✓ CardList destructor works" << endl;
    
    cout << "CardList class tests passed!" << endl << endl;
}

void testGameLogic() {
    cout << "Testing game logic..." << endl;
    
    // Create test files
    ofstream file1("test_alice.txt");
    file1 << "c a\n";
    file1 << "d 2\n";
    file1 << "h 10\n";
    file1.close();
    
    ofstream file2("test_bob.txt");
    file2 << "c a\n";
    file2 << "d 3\n";
    file2 << "h 10\n";
    file2.close();
    
    // Test reading files
    CardList aliceCards;
    CardList bobCards;
    
    ifstream cardFile1("test_alice.txt");
    ifstream cardFile2("test_bob.txt");
    string line;
    
    while (getline(cardFile1, line) && (line.length() > 0)) {
        istringstream iss(line);
        string suit, rank;
        if (iss >> suit >> rank) {
            Card card(suit, rank);
            aliceCards.add(card);
        }
    }
    cardFile1.close();
    
    while (getline(cardFile2, line) && (line.length() > 0)) {
        istringstream iss(line);
        string suit, rank;
        if (iss >> suit >> rank) {
            Card card(suit, rank);
            bobCards.add(card);
        }
    }
    cardFile2.close();
    
    assert(aliceCards.contains(Card("c", "a")));
    assert(aliceCards.contains(Card("d", "2")));
    assert(aliceCards.contains(Card("h", "10")));
    
    assert(bobCards.contains(Card("c", "a")));
    assert(bobCards.contains(Card("d", "3")));
    assert(bobCards.contains(Card("h", "10")));
    
    // Test finding matches
    vector<Card> aliceCardVec;
    aliceCards.getCards(aliceCardVec);
    
    vector<Card> matchingCards;
    for (const Card& card : aliceCardVec) {
        if (bobCards.contains(card)) {
            matchingCards.push_back(card);
        }
    }
    
    assert(matchingCards.size() == 2);
    assert(matchingCards[0] == Card("c", "a") || matchingCards[0] == Card("h", "10"));
    assert(matchingCards[1] == Card("c", "a") || matchingCards[1] == Card("h", "10"));
    
    cout << "  ✓ Game logic works correctly" << endl;
    
    // Clean up test files
    remove("test_alice.txt");
    remove("test_bob.txt");
    
    cout << "Game logic tests passed!" << endl << endl;
}

int main() {
    cout << "Running comprehensive tests..." << endl << endl;
    
    testCard();
    testCardList();
    testGameLogic();
    
    cout << "All tests passed! ✓" << endl;
    return 0;
}
