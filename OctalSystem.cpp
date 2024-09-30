#include <OctalSystem.h>

// 8 -> 2
QString eightToBinary(QString number){
    QStringList parts = number.split('.');

    QHash<QChar, QString> map = {
        {'0', "000"}, {'1', "001"}, {'2', "010"}, {'3', "011"},
        {'4', "100"}, {'5', "101"}, {'6', "110"}, {'7', "111"}
    };

    std::stack<QString> sum;
    QString final;

    for (int i = parts[0].length() - 1; i >= 0; --i){
        if (map.contains(parts[0][i]))
            sum.push(map[parts[0][i]]);
    }

    while(!sum.empty()){
        final += sum.top();
        sum.pop();
    }

    if (parts.size() == 2){
        final += ".";

        for (int i = 0; i < parts[1].size(); ++i){
            if (map.contains(parts[1][i]))
                final += map[parts[1][i]];
        }
    }

    final.remove(0, final.indexOf(QChar('1')));
    return final.isEmpty() ? "0" : final;
}

// 8 -> 10
int power(int powerSize){
    return (powerSize == 0) ? 1 : 8 * power(powerSize - 1);
}
QString eightToTen(QString number){
    QStringList parts = number.split('.');
    int sum = 0;
    int x = 0;

    for (int i = parts[0].length() - 1; i >= 0; --i){
        int digit = parts[0][i].toLatin1() - '0';
        sum += digit * power(x);
        ++x;
    }

    QString final = QString::number(sum);

    if (parts.size() == 2){
        double fractionaPart = 0.0;

        for (int i = 0; i < parts[1].size(); ++i){
            int digit = parts[1][i].toLatin1() - '0';
            fractionaPart += digit * pow(8, -(i + 1));
        }

        if (fractionaPart > 0)
            final += QString::number(fractionaPart, 'f', 6).remove(0, 1);
    }

    return final;
}

// 8 -> 16
QString eightToSixteen(QString numbmer){
    QString binary = eightToBinary(numbmer);
    QString hexResult = binaryToSixteen(binary);
    return hexResult;
}

