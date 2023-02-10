#ifndef KEY_HPP
#define KEY_HPP

#include <iostream>
#include <cstring>

// Keys are randomly generated every time a message is made.
// They are composed of random 26 chars of alphabet letters with
// a length of 26.
class Key {
public: 
    Key() : decryption_key(new(std::nothrow) char[length])
        { SetLetters(); GenerateKey(length-2); }
    Key(const Key &k);
    ~Key() { delete [] decryption_key; }
    Key& operator=(const Key &k);

    char* ShowKey() {return decryption_key;}

private:
    void SetLetters();
    void GenerateKey(int idx);
    void swap(char *a, char *b);
    const size_t length = 27;
    char* decryption_key;

friend class EncryptedMessage;
};

#endif
