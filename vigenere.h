#ifndef VIGENERE_H
#define VIGENERE_H

#include <QString>

class vigenere
{
public:
    vigenere();
    QString make(QString text);
    bool check(QString text);
private:
    QString encrypt(QString text);
    QString decrypt(QString vigenereText);
};

#endif // VIGENERE_H
