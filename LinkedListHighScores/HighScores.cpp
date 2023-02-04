#include "ScoresLinkedList.hpp"

using namespace std;

GameEntryNode::GameEntryNode(const string& n, int s)
    : name(n), score(s), next(NULL) { }
// accessors
string GameEntryNode::getName() const { return name; }

int GameEntryNode::getScore() const { return score; }

bool SinglyLinkedList::empty() const
{ return head == NULL; }

SinglyLinkedList::~SinglyLinkedList() 
{ while(!empty()) removeFront(); } 

const int& SinglyLinkedList::front() const {
    return head->score;
}

void SinglyLinkedList::addScore(const string& n, const int& s) {
    // a new node created to store the new entry values
    GameEntryNode* newEntry = new GameEntryNode(n, s);
    // iterator node pointer
    GameEntryNode* current = new GameEntryNode;
    // This is the entry to the list if it is empty or less than 10 entries
    if( empty() || ( (front() >= newEntry->score) 
        && ( totalEntries < 10 ) ) ) {
        newEntry->next = head;
        head = newEntry;
        totalEntries++;
    } 
    // Most of the work is here. The SLL will now be sorted at each insert
    else if( newEntry->score > head->score ) {
        // Locate the node before point of insertion
        current = head;
        while( (current->next != NULL )
            && (current->next->score < newEntry->score) ) {
            current = current->next;
        }
        // set the new sorted node's next pointer to the next node or NULL
        newEntry->next = current->next;
        // set the new node to sit in between the nodes or nulls
        current->next = newEntry;
        // count the size and test if a node should be removed from front
        totalEntries++;
        if(totalEntries > 10) {
            removeFront();
        }
    }

}

void SinglyLinkedList::removeFront() {
    GameEntryNode* old = head;
    head = old->next;
    delete old;
}

void SinglyLinkedList::print() {
    GameEntryNode* temp = head;
    cout << "Top 10 Scores" << endl;
    while(temp != NULL) {
        cout << temp->name << ": " << temp->score << endl;
        temp = temp->next;
    }
}
