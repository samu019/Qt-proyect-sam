#include "unittests.h"
#include "sha256.h"

#include <qstring.h>

Unit_Tests::Unit_Tests()
{

}

bool Unit_Tests::Test1()
{
    auto sha = new SHA256;
    auto actual = QString::fromStdString(sha->hashString("HELLO"));
    QString expected = "3733cd977ff8eb18b987357e22ced99f46097f31ecb239e878ae63760e83e4d5";
    if (actual == expected)
    {
        return true;
    }
    return false;
}
