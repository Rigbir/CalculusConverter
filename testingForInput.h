#pragma once
#include <Library.h>

bool testInput(QString input, const QSet<int>& validDigit){
    if (input.isEmpty()) return false;

    bool hasDot = false;

    for (int i = 0; i < input.size(); ++i){
        QChar ch = input[i];

        if (ch == '.'){
            if (hasDot || i == 0 || i == input.size() - 1)
                return false;
            hasDot = true;
        }

        else {
            int digit = input[i].digitValue();
            if (!validDigit.contains(digit))
                return false;
        }
    }
    return true;
}

bool testBinaryInput(QString input){
    QSet<int> binary{0, 1};
    return testInput(input, binary);
}

bool testEightInput(QString input){
    QSet<int> eight{0, 1, 2, 3, 4, 5, 6, 7};
    return testInput(input, eight);
}

bool testOrdinaryInput(QString input){
    QSet<int> ordinary{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    return testInput(input, ordinary);
}

bool testHexadecimalInput(QString input){
    if (input.isEmpty()) return false;

    for (int i = 0; i < input.size(); ++i){
        QChar ch = input[i];
        bool hasDot = false;

        if (ch == '.'){
            if (hasDot || i == 0 || i == input.size() - 1)
                return false;
            hasDot = true;
        }else {
            if (!((ch >= '0' && ch <= '9') ||
                  (ch >= 'A' && ch <= 'F'))){
                return false;
            }
        }
    }
    return true;
}
