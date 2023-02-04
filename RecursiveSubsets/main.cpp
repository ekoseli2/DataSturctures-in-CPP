#include "Subsets.hpp"

using namespace std;

int main() {

    // utilities methods in the header to facilitate the main file
    // First read the files of sets into a vector for program and print
    ifstream file;

    vector<int> set;
    set = Utilities::readFileToSet(file);
    
    Subsets test1 = Subsets(set);

    Subsets test_2;

    vector<vector<int>> test2 = test_2.variations(set);

    // I have removed the print class member function cll from the 
    // driver code to simplify the terminal output, but either print
    // method could be used based on initialization approach.
  
    // Print result
    Utilities::print(test2);
  
    return 0;
}
