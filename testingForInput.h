#pragma once
#include <Library.h>

inline bool testInput(QString input, const QSet<size_t>& validDigit){
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
            size_t digit = input[i].digitValue();
            if (!validDigit.contains(digit))
                return false;
        }
    }
    return true;
}

inline bool testMinusForTwoSystem(QString input, const QSet<size_t>& validDigit){
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
            if (ch == '-' && i == 0)
                continue;
            else{
                size_t digit = input[i].digitValue();
                if (!validDigit.contains(digit))
                    return false;
            }
        }
    }
    return true;
}

inline bool testBinaryInput(QString input){
    QSet<size_t> binary{0, 1};
    return testInput(input, binary);
}

inline bool testEightInput(QString input){
    QSet<size_t> eight{0, 1, 2, 3, 4, 5, 6, 7};
    //return testMinusForTwoSystem(input, eight);
    return testInput(input, eight);
}

inline bool testOrdinaryInput(QString input){
    QSet<size_t> ordinary{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    return testMinusForTwoSystem(input, ordinary);
    //return testInput(input, ordinary);
}

inline bool testHexadecimalInput(QString input){
    if (input.isEmpty()) return false;

    for (size_t i = 0; i < input.size(); ++i){
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

inline bool testBCDInput(QString input){
    QHash<QString, char> map = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'},
        {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}
    };

    if (input.isEmpty()) return false;
    if (input.size() % 4 != 0) return false;

    QString add;
    for (int i = 0; i < input.size(); ++i){
        add += input[i];
        if (add.size() == 4)
            if (!map.contains(add))
                return false;
        add.clear();
    }
    return true;
}
