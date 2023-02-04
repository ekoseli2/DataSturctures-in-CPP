#ifndef SCORESLINKEDLIST_HPP
#define SCORESLINKEDLIST_HPP

#include <string>
#include <iostream>

class GameEntryNode {
public:
    // constructor
    GameEntryNode(const std::string& n = "", int s = 0);
    std::string getName() const;
    int getScore() const;

private:
    int score;
    std::string name;
    GameEntryNode* next;

friend class SinglyLinkedList;
};

class SinglyLinkedList {
public:
    SinglyLinkedList() : head(NULL), totalEntries(0) { };
    ~SinglyLinkedList();
    // is the list empty?
    bool empty() const;
    // get lowest Score number value
    const int& front() const;
    // adds the new top 10 score to the correct location
    void addScore(const std::string& n, const int& s);
    // removes the 10th highest score
    void removeFront();
    // print method
    void print();
    
private:
    // head of the list
    GameEntryNode* head;
    // count of total entries in the list
    int totalEntries;
};

#endif
