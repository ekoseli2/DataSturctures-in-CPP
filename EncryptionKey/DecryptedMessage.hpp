#ifndef DECRYPTEDMESSAGE_HPP
#define DECRYTPEDMESSAGE_HPP

#include <string>

// decryptedmessage is similar to encrypted message however takes
// the encrypted message string as a param. does not generate a key or
// need to make any calls to the key.
class DecryptedMessage {
public:
    DecryptedMessage() : message(nullptr), m_len(0), plain_text("") {} 
    DecryptedMessage(std::string &m) : message(nullptr), m_len(m.length()), 
        plain_text("") { Decrypt(m); }
    DecryptedMessage(const DecryptedMessage &dm);

    ~DecryptedMessage() { delete [] message; }

    DecryptedMessage& operator=(const DecryptedMessage &dm);
    
    void Decrypt(std::string &m);
    std::string GetDecryptedMessage() { return plain_text; }

private:
    void SetMessage(std::string &m);
    void SetPtext(char* p_text) { plain_text = p_text; }
    char* LongDecrypt(char* d, bool start, size_t i, size_t j, 
        size_t nSlot, size_t c);
    char* ShortDecrypt(char* d, bool start, size_t i, size_t j, 
        size_t nSlot);

    char* message;   
    size_t m_len;
    std::string plain_text;
};

#endif
