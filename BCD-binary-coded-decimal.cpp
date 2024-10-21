#include <BCD-binary-coded-decimal.h>

//BCD -> 2
QString BCDtoBinary(QString number){
    QString final = BCDtoOrdinary(number);
    return toBinaryCod(final);
}

//BCD -> 8
QString BCDtoOctal(QString number){
    QString final = BCDtoOrdinary(number);
    return toEight(final);
}

//BCD -> 10
QString BCDtoOrdinary(QString number){
    QHash<QString, char> map = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'}, {"0100", '4'},
        {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}
    };

    QString final;
    QString add;

    for (int i = 0; i < number.size(); ++i){
        add += number[i];
        if (add.size() == 4){
            final += map[add];
            add = "";
        }
    }

    return final;
}

//BCD -> 16
QString BCDtoHexadecimal(QString number){
    QString final = BCDtoOrdinary(number);
    return toSixteen(final);
}

//BCD -> Grey
QString BCDtoGrey(QString number){
    QString final = BCDtoBinary(number);
    return toGrey(final);
}
