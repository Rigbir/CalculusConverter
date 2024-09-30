#include <BinarySystem.h>

// 2 -> 8
QString binaryToEight(QString number) {
    QHash<QString, int> map = {
       {"000", 0}, {"001", 1}, {"010", 2}, {"011", 3},
       {"100", 4}, {"101", 5}, {"110", 6}, {"111", 7},
       };

    QStringList parts = number.split('.');
    std::stack<QString> sum;
    QString current;

    for (int i = parts[0].length() - 1; i >= 0; --i) {
        current.prepend(parts[0][i]);

        if (current.size() >= 3) {
            sum.push(QString::number(map[current]));
            current.clear();
        }
    }

    if (!current.isEmpty()) {
        while (current.size() < 3) {
            current.prepend('0');
        }
        sum.push(QString::number(map[current]));
    }

    QString final;
    while (!sum.empty()) {
        final += sum.top();
        sum.pop();
    }

    if (parts.size() == 2){
        QString fractionalPart = parts[1];

        while (fractionalPart.size() % 3 != 0){
            fractionalPart.append('0');
        }

        final += ".";
        for (int i = 0; i < fractionalPart.size(); i += 3){
            QString group = fractionalPart.mid(i, 3);
            final += QString::number(map[group]);
        }
    }

    return final;
}

// 2 -> 10
QString binaryToOrdinary(QString number) {
    QStringList parts = number.split('.');
    int sum = 0;
    int power = 1;

    for (int i = parts[0].length() - 1; i >= 0; --i) {
        if (parts[0][i] == QChar('1'))
            sum += power;
        power *= 2;
    }

    QString final = QString::number(sum);

    if (parts.size() == 2){
        double fractionalPart = 0.0;

        for (int i = 0; i < parts[1].size(); ++i){
            if (parts[1][i] == QChar('1'))
                fractionalPart += pow(2, -(i + 1));
        }

        if (fractionalPart > 0)
            final += "." + QString::number(fractionalPart, 'f',6).remove(0, 2);
    }

    return final;
}

// 2 -> 16
QString binaryToSixteen(QString number) {
    QHash<QString, QChar> map = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'},
    };

    QStringList parts = number.split('.');
    std::stack<QChar> sum;
    QString current;

    QString integerPart = parts[0];

    for (int i = integerPart.length() - 1; i >= 0; --i) {
        current.prepend(integerPart[i]);

        if (current.size() == 4) {
            if (map.contains(current))
                sum.push(map[current]);

            current.clear();
        }
    }

    if (!current.isEmpty()) {
        while (current.size() < 4) {
            current.prepend('0');
        }
        if (map.contains(current))
            sum.push(map[current]);
    }

    QString final;
    while (!sum.empty()) {
        final += sum.top();
        sum.pop();
    }

    while (final.startsWith('0') && final.size() > 1){
        final.remove(0, 1);
    }

    if (parts.size() == 2){
        QString fractionalPart = parts[1];

        while (fractionalPart.size() % 4 != 0){
            fractionalPart.append('0');
        }

        final += ".";
        for (int i = 0; i < fractionalPart.size(); i += 4){
            QString group = fractionalPart.mid(i, 4);
            final += map[group];
        }
    }

    return final.isEmpty() ? "0" : final;
}

