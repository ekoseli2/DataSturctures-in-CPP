#ifndef ENCRYPTEDMESSAGE_HPP
#define ENCRYTPEDMESSAGE_HPP

#include "Key.hpp"

// encryptedmessage class can take a parameter of type Key and a
// plaintext string to return the encrypted message string.
// It can also alternatively decrypt by taking the encrypted message string
// and returning the plaintext
class EncryptedMessage{
public:
    EncryptedMessage() : plain_text(nullptr), p_text_len(0), 
        message("") {}
    EncryptedMessage(std::string &p_text) : 
        p_text_len(p_text.length()), plain_text(nullptr),
        message("") { Encrypt(p_text); }
    EncryptedMessage(const EncryptedMessage &em);

    ~EncryptedMessage() { delete []plain_text; }

    EncryptedMessage& operator=(const EncryptedMessage &em);

    void Encrypt(std::string &p_text);
    std::string GetEncryptedMessage() { return message; };

private:
    void SetMessage(char* m) { message = m; }
    void SetPtext(std::string &p_text);
    // Function for the encryption process for long messages
    char* LongEncrypt(char* e, bool start, size_t i, size_t j, size_t k, 
        size_t nSlot);
    // Function for encrypting short messages
    char* ShortEncrypt(char* e, bool start, size_t i, size_t j, size_t k,
        size_t nSlot);
    
    char* plain_text;
    std::string message;
    Key e_key;
    size_t p_text_len;
};

#endif
