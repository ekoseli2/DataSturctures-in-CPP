#include "ScoresLinkedList.hpp"
#include <fstream>

using namespace std;

int main() {
    // Token for score
    int score;
    // Token for name
    string name;
    ifstream entries;
    // Take the fileName to use from user for the entries list
    string fileName;
    while (fileName.empty()) {
        cout << "Enter file name: ";
        char c[255];
        cin.getline(c, 255);
        fileName = string(c);
    }
    entries.open(fileName);
    // Read the User files
    SinglyLinkedList HighScores;

    entries >> name >> score;
    cout << "Player " << name << " |  Score " << score << endl;
    while (!entries.eof()) {
        HighScores.addScore(name, score);
        cout << "Player " << name << " |  Score " << score << endl;
        entries >> name >> score;
        if(entries.eof()) {
            break;
        }
    }
    cout << endl;
    HighScores.print();

    return 0;
}
