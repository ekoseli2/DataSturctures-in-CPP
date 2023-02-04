#include "Subsets.hpp"

using namespace std;

Subsets::Subsets(vector<int>& orig) {
    setPowerset(orig);
    variations();
}

// Accessors and Mutators to class level variables
int Subsets::getN() const{
    return n;
}

void Subsets::setPowerset(vector<int>& orig) {
    for(int i : orig) {
        powerSet.push_back(i);
    }
    n = orig.size();
}

vector<int> Subsets::getPowerset() const{
    return powerSet;
}

void Subsets::addSubset() {
    allSets.push_back(subset);
}

void Subsets::removeElem() {
    subset.pop_back();
}

void Subsets::addElem(int& elem) {
    subset.push_back(elem);
}

void Subsets::variations() {
    int index = 0;
    findSubsets(index);
}

// Create an overloaded version of this method to accomodate for the 
// case where the Subset constructor had no parameters and can be called

vector<vector<int>> Subsets::variations(vector<int>& orig) {
    // this integer will be used to track the iteration index of the orig
    // vector. The index will be stored by recursive instance
    setPowerset(orig);
    int index = 0;
    findSubsets(index);

    return allSets;
}

void Subsets::findSubsets(int index) {
    // This is where the recursions occur
    addSubset();
    // The index does the magic here by iterating each version of the
    // subset that is possible before moving to the next index.
    for(int i = index; i < getN(); i++) {
        // adding the set at i to the subset variable
        addElem(getPowerset()[i]);
        // move onto next element and add this subset too: recursive call
        findSubsets(i + 1);
        // At the end of the recursive call, removes powerSet[i] to create
        // recursive pattern
        removeElem();
    }

    return;
}

void Subsets::print() {
    cout << "Has 2^n subsets : " << endl;
    for(int i = 0; i < allSets.size(); i++) {
        for(int j = 0; j < allSets[i].size(); j++) {
            cout << allSets[i][j] << " ";
        }
        cout << endl;
    }
}
