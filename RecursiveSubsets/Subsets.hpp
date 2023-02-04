#ifndef SUBSETS_HPP
#define SUBSETS_HPP

#include <vector>
#include <iostream>
#include <fstream>

class Subsets {
public:
    Subsets() : n(0) { };
    Subsets(std::vector<int>& orig);
   ~Subsets() { };
    
    void findSubsets(int index);
    void variations();
    // When the object is created without the powerset defined: Overload
    std::vector<std::vector<int>> variations(std::vector<int>& orig);
    void addSubset();

    void removeElem();
    void addElem(int& elem);

    int getN() const;
    
    void setPowerset(std::vector<int>& orig);
    std::vector<int> getPowerset() const;

    void print();
    
private:
    // Contains the vectors of the result of all sets
    std::vector<std::vector<int>> allSets;
    // vector to be initialized that will be a placeholder for each subset
    std::vector<int> subset;
    // the original set
    std::vector<int> powerSet;
    // number of elements of the original set
    int n;
};

// I read your email :)
namespace Utilities {
    static void print(std::vector<std::vector<int>>& result) {
        std::cout << "Has 2^n subsets : " << std::endl;
        for(int i = 0; i < result.size(); i++) {
            for(int j = 0; j < result[i].size(); j++) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    static std::vector<int> readFileToSet(std::ifstream& file) {
        std::string fileName;
        int num;
        std::vector<int> set;

        while (fileName.empty()) {
            std::cout << "Enter file name: ";
            char c[255];
            std::cin.getline(c, 255);
            fileName = std::string(c);
        }
        try {
            file.open(fileName);
            if (file.fail()) throw fileName;

            file >> num;
            std::cout << "Power set : ";

            while(!file.eof() ) {
                set.push_back(num);
                std::cout << num << " ";
                file >> num;
                if(file.eof() ) {
                    break;
                }
            }

            std::cout << std::endl;

            file.close();

            return set;
        }
        catch(std::string e) {
            std::cout << e << " was not successfully opened."
            << "\n Please check that the file currently exists." 
            << std::endl;
            exit(1);
        }
    }
};

#endif
