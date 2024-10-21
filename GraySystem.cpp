#include <GraySystem.h>

//Grey -> 2
QString grayToBinary(QString number){
    QStringList parts = number.split('.');
    QString final;

    if (!parts[0].isEmpty()){
        final += parts[0][0];
        for (int i = 1; i < parts[0].size(); ++i){
            final += QString::number(final[i - 1].digitValue() ^ parts[0][i].digitValue());
        }
    }

    if (parts.size() == 2 && !parts[1].isEmpty()){
        int prevBit = final.back().digitValue();
        final += '.';

        for (int i = 0; i < parts[1].size(); ++i){
            final += QString::number(prevBit ^ parts[1][i].digitValue());
            prevBit = final.back().digitValue();
        }
    }

    return final.isEmpty() ? "0" : final;
}

//Grey -> 8
QString grayToOctal(QString number){
    QString final = grayToBinary(number);
    return binaryToEight(final);
}

//Grey -> 10
QString grayToOrdinary(QString number){
    QString final = grayToBinary(number);
    return binaryToOrdinary(final);
}

//Grey -> 16
QString grayToSixteen(QString number){
    QString final = grayToBinary(number);
    return binaryToSixteen(final);
}

//Grey -> BCD
QString grayToBCD(QString number){
    QString final = grayToBinary(number);
    return binaryToBCD(final);
}
