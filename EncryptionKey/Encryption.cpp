#include "EncryptedMessage.hpp"
#include "DecryptedMessage.hpp"

constexpr int LENGTH = 26;

Key::Key(const Key &k) : decryption_key(new(std::nothrow) char[length]) {
    for(size_t i = 0; i < length; i++) {
        decryption_key[i] = k.decryption_key[i];
    }
}

Key& Key::operator =(const Key& k) {
    if(&k != this) {
        delete [] decryption_key;
        decryption_key = new(std::nothrow) char[length];
        if (decryption_key != nullptr) {
            for (size_t i = 0; i < length; i++) {
                decryption_key[i] = k.decryption_key[i];
            }
        }
    }
    return *this;
}

void Key::SetLetters() {
    char letters[length] = {'a','b','c','d','e','f','g','h','i','j','k',
    'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\n'};
    for(size_t i = 0; i < length; i++) {
        decryption_key[i] = letters[i];
    }
}

void Key::GenerateKey(int idx) {
    if(idx < 0) {
        return;
    } 
    else {
        unsigned int j = rand() % (length-2);
        swap(&decryption_key[idx], &decryption_key[j]);
        GenerateKey(idx-1);
    }
}

void Key::swap (char *a, char *b) {
        char temp = *a;
        *a = *b;
        *b = temp;
}

EncryptedMessage::EncryptedMessage(const EncryptedMessage &em) 
    : plain_text(new(std::nothrow) char[em.p_text_len+1]), e_key(em.e_key), 
    p_text_len(em.p_text_len), message("") 
{
    if(plain_text != nullptr) {
        for(size_t i = 0; i <= p_text_len; i++) {
            plain_text[i] = em.plain_text[i];
        }
        message = em.message;
    }
    else {
        p_text_len = 0;
    }
}

EncryptedMessage& EncryptedMessage::operator=(const EncryptedMessage &em) {
    if(&em != this) {
        delete [] plain_text;
        message = em.message;
        e_key = em.e_key;
        p_text_len = em.p_text_len;
        plain_text = new(std::nothrow) char[em.p_text_len+1];
        if (plain_text != nullptr) {
            for (size_t i = 0; i <= p_text_len; i++) {
                plain_text[i] = em.plain_text[i];
            }
        }
        else {
            e_key = Key();
            p_text_len = 0;
            message = "";
            plain_text = nullptr;
        }
    }
    return *this;
}

void EncryptedMessage::SetPtext(std::string &p_text) {
    // plain_text is better handled as a char array after converting from a
    // string input. This allows easier management of the exact size of the
    // message and the access locations.
    plain_text = new(std::nothrow) char[p_text_len+1];
    for(size_t i = 0; i <= p_text_len; i++) {
        plain_text[i] = p_text[i]; 
    }
}

void EncryptedMessage::Encrypt(std::string &p_text) {
    if(p_text_len == 0) {
        p_text_len = p_text.length();
    }
    SetPtext(p_text);
    // test for the message length in order to evaluate whether the message
    // is hidden in the key, or the key in the message (length < 26)
    SetMessage( (p_text_len >= 25) ? LongEncrypt(nullptr, true, 0, 0, 0, 0) 
        : ShortEncrypt(nullptr, true, 0, 0, 0, 0) );
}

char* EncryptedMessage::ShortEncrypt(char* e, bool start, 
    size_t idx, size_t idx_D, size_t idx_P, size_t nSlot) {
    // Initializes the recursions so that the message is created once.
    if(start) {
        e = new(std::nothrow) char[LENGTH + p_text_len + 1];
        // head and tail slots are to have the remainder evenly split
        nSlot = 26/(p_text_len+1) + (26%(p_text_len+1))/2;
        start = false;
    } 
    else if(idx >= (p_text_len+LENGTH)) {   
        e[p_text_len+LENGTH] = '\0';
        return e; 
    }
    else {
        size_t temp = idx;
        while(idx < nSlot+temp) {
            e[idx++] = e_key.decryption_key[idx_D++];
        }
        if(!(idx_P>=p_text_len)) {
            e[idx++] = plain_text[idx_P++];
            nSlot = 26/(p_text_len+1);
        } else {
            nSlot = 26/(p_text_len+1) + (26%(p_text_len+1))/2;
        }
    }
    return ShortEncrypt(e, start, idx, idx_D, idx_P, nSlot);
}

char* EncryptedMessage::LongEncrypt(char* e, bool start, size_t idx, 
    size_t idx_D, size_t idx_P, size_t nSlot) {
        if(start) {
        e = new(std::nothrow) char[LENGTH + p_text_len + 1];
        // there are now a total of 27 slots split amongs n ptext values
        nSlot = p_text_len/26 + (p_text_len%26)/2;
        start = false;
    } 
    else if(idx >= (p_text_len+LENGTH)) {   
        e[p_text_len+LENGTH] = '\0';
        return e; }
    else {
        size_t temp = idx;
        while(idx < nSlot+temp) {
            e[idx++] = plain_text[idx_P++];
        }
        if(!(idx_D >= LENGTH)) {
            e[idx++] = e_key.decryption_key[idx_D++];
            nSlot = p_text_len/26;
        } else {
            nSlot = p_text_len/26 + (p_text_len%26)/2;
        }
    }
    return LongEncrypt(e, start, idx, idx_D, idx_P, nSlot);
}

DecryptedMessage::DecryptedMessage(const DecryptedMessage &dm) 
    : message(new(std::nothrow) char[dm.m_len+1]), m_len(dm.m_len), 
    plain_text("") 
{
    if(message != nullptr) {
        for(size_t i = 0; i <= m_len; i++) {
            message[i] = dm.message[i];
        }
        plain_text = dm.plain_text;
    }
    else {
        m_len = 0;
    }
}

DecryptedMessage& DecryptedMessage::operator=(const DecryptedMessage &dm) {
    if(&dm != this) {
        delete [] message;
        plain_text = dm.plain_text;
        m_len = dm.m_len;
        message = new(std::nothrow) char[dm.m_len+1];
        if (message != nullptr) {
            for (size_t i = 0; i <= m_len; i++) {
                message[i] = dm.message[i];
            }
        }
        else {
            m_len = 0;
            plain_text = "";
            message = nullptr;
        }
    }
    return *this;
}

void DecryptedMessage::SetMessage(std::string &m) {
    message = new(std::nothrow) char[m_len+1];
    for(size_t i = 0; i <= m_len; i++) {
        message[i] = m[i]; 
    }
}

void DecryptedMessage::Decrypt(std::string &m) {
    // case where default constructor called, init the length
    if(m_len == 0) {
        m_len = m.length();
    }
    SetMessage(m);
    SetPtext( (m_len < LENGTH*2) ? 
        ShortDecrypt(nullptr, true, 0, 0, 0) : 
        LongDecrypt(nullptr, true, 0, 0, 0, 0) );
}

char* DecryptedMessage::ShortDecrypt(char* d, bool start, size_t idx, 
    size_t idx_P, size_t nSlot) {
    if(start) {
        // allocate an extra pointer for the NULL terminator
        d = new(std::nothrow) char[m_len - LENGTH + 1];
        // head slots only matter in this case
        nSlot = 26/(m_len-LENGTH+1) + (26%(m_len-LENGTH+1))/2;
        start = false;
    }
    else if(m_len-idx <= nSlot + (26%(m_len-LENGTH+1))/2) {   
        d[m_len-LENGTH] = '\0';
        return d; 
    }
    else {
        idx += nSlot;
        d[idx_P++] = message[idx++];
        nSlot = 26/(m_len-LENGTH+1);
    }
    return ShortDecrypt(d, start, idx, idx_P, nSlot);
}

// Try to use tail recursion, maybe easier to fix the errors since it will
// be easier to determine the beginning point of the arrays than the end.
char* DecryptedMessage::LongDecrypt(char* d, bool start, size_t idx, 
    size_t idx_P, size_t nSlot, size_t c) { 
    if(start) {
        // allocate an extra pointer for the NULL terminator
        d = new(std::nothrow) char[m_len - LENGTH + 1];
        // head slots only matter in this case
        nSlot = (m_len-LENGTH+1)/26 + ((m_len-LENGTH+1)%26)/2;
        start = false;
    }
    else if(idx >= m_len) {   
        d[m_len-LENGTH] = '\0';
        return d; 
    }
    else if(c == nSlot) {
        idx++;
        c=0;
        // very complex evaluation to set the slot iterator in last slot
        (idx_P > m_len-LENGTH-(m_len-LENGTH+1)/26-
            ((m_len-LENGTH+1)%26)/2) ? 
            nSlot = ((m_len-LENGTH+1)/26 + ((m_len-LENGTH+1)%26)/2) : 
            nSlot = (m_len-LENGTH+1)/26;
    } 
    else {
        d[idx_P++] = message[idx++];
        c++;
    }
    return LongDecrypt(d, start, idx, idx_P, nSlot, c);
}
