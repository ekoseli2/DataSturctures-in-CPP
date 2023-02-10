#include "EncryptedMessage.hpp"
#include "DecryptedMessage.hpp"

#include <fstream>

void exitProgram(bool command) { // Function to exit program
    if (command == true){
        std::cout << "Exiting Program" << std::endl;
        exit(0);
    }
}
std::string EnterFile() {
    std::string fName;
    std::cout << "Enter file name: \n";
    std::cin >> fName;
    exitProgram(fName=="exit");
    return fName;
}
//combine enterfile and readfile
std::string ReadFile(std::string &fileName) {
    std::ifstream file;
    std::string con;
    file.open(fileName);

    if(file.fail()) {
        std::cout << fileName << " was not successfully opened."
        << " Please check that the file currently exists." 
        << std::endl;
        return "FAIL";
    }
    else {
        std::getline(file, con);
        std::cout << con <<"\nread complete"<<std::endl;
        file.close();
    } 
    return con;
}

void WriteFile(std::string &fileName, EncryptedMessage e_mes) {
// save the encrypted message
    std::fstream file;
    file.open(fileName, std::ios_base::out);
    
    file.write(e_mes.GetEncryptedMessage().data(), 
    e_mes.GetEncryptedMessage().size());

    std::cout << e_mes.GetEncryptedMessage() << std::endl;
    file.close();
}

void WriteFile(std::string &fileName, DecryptedMessage d_mes) {
// save the decrypted Message overload
    std::fstream file;
    file.open(fileName, std::ios_base::out);
    
    file.write(d_mes.GetDecryptedMessage().data(), 
    d_mes.GetDecryptedMessage().size());

    std::cout << d_mes.GetDecryptedMessage() << std::endl;
    file.close();
}

using namespace std;

int main() {


    srand(time(nullptr));
    cout << "-------------------------------------------------\n"
        <<"Protect your files with an encryption key.\n>Decrypt them at " 
        << "any time with this program.\n>'exit' to end program.\n"
        <<"-------------------------------------------------"
        <<endl;
    
    string input, fileName, message;

    while(true) {
        cout<<endl;
        fileName = EnterFile();
        message = ReadFile(fileName);
        if(message=="FAIL") { continue; }
        cout<<"Encrypt or Decrypt the file?\ne/d"<<endl;
        cin >> input;
        cout<<endl;

        if(input=="exit") {
            exitProgram(true);
            break;
        }
        else if(input=="e") {
            // encrypt initialize
            const EncryptedMessage e_message(message);
            WriteFile(fileName, e_message);
            cout << fileName << " encryption complete.\n";
        }

        else if(input=="d") {
            // decrypt initialize
            const DecryptedMessage d_message(message);
            WriteFile(fileName, d_message);
            cout << fileName << " decrytion complete.\n";
        } 
        else{
            cout<<"Please choose a command or 'exit' to terminate program"
                <<"\n";
        } 
    }

    return 0;
}


