#include <HexadecimalSystem.h>

// 16 -> 2
QString sixteenToBinary(QString number){
    QHash<QChar, QString> map = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };

    QStringList parts = number.split('.');
    QString final;

    for (int i = 0; i < parts[0].length(); ++i){
        if (map.contains(parts[0][i]))
            final += map[parts[0][i]];
    }

    final.remove(0, final.indexOf(QChar('1')));

    if (parts.size() == 2){
        final += ".";
        for (int i = 0; i < parts[1].size(); ++i){
            if (map.contains(parts[1][i]))
                final += map[parts[1][i]];
        }
    }

    return final.isEmpty() ? "0" : final;
}

// 16 -> 8
QString sixteenToEight(QString number){
    QString hexToOrdinary = sixteenToTen(number);
    QString eightResult = toEight(hexToOrdinary);
    return eightResult;
}

// 16 -> 10
size_t powerSixteen(size_t powerSize){
    return (powerSize == 0) ? 1 : 16 * powerSixteen(powerSize - 1);
}
QString sixteenToTen(QString number){
    QStringList parts = number.split('.');
    size_t sum = 0;
    size_t x = 0;

    for (int i = parts[0].length() - 1; i >= 0; --i){
        size_t numb = 0;
        if (parts[0][i].isDigit())
            numb = parts[0][i].digitValue();
        else if (parts[0][i] >= 'A' && parts[0][i] <= 'F')
            numb = parts[0][i].unicode() - 'A' + 10;

        sum += numb * powerSixteen(x);
        ++x;
    }

    QString final = QString::number(sum);

    if (parts.size() == 2){
        double fractionalPart = 0.0;

        for (int i = 0; i < parts[1].size(); ++i){
            double numb = 0;
            if (parts[1][i].isDigit())
                numb = parts[1][i].digitValue();
            else if (parts[1][i] >= 'A' && parts[1][i] <= 'F')
                numb = parts[1][i].unicode() - 'A' + 10;

            fractionalPart += numb * pow(16, -(i + 1));
        }

        if (fractionalPart > 0)
            final += QString::number(fractionalPart, 'f', 6).remove(0, 1);
    }

    return final;
}

// 16 -> BCD
QString sixteenToBCD(QString number){
    QString final = sixteenToTen(number);
    return toBCD(final);
}

//16 -> Grey
QString sixteenToGrey(QString number){
    QString final = sixteenToBinary(number);
    return binaryToGrey(final);
}
