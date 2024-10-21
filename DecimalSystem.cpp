#include <DecimalSystem.h>

QString isNegative(QString final){
    while (final.size() < 8){
        final.insert(0, "0");
    }

    for (int i = 0; i < final.size(); ++i){
        final[i] = (final[i] == '0') ? '1' : '0';
    }

    bool one = true;
    for (int i = final.size() - 1; i >= 0 && one; --i){
        if (final[i] == '0'){
            final[i] = '1';
            one = false;
        }else if (final[i] == '1'){
            final[i] = '0';
        }
    }
    return final;
}

// [0, 1]
QString toBinaryCod(QString workNumber){
    QStringList parts = workNumber.split('.');
    std::stack<int> stack;

    int number = parts[0].toInt();
    int startNumber = number;

    if (number < 0)
        number = -number;

    while (number > 0){
        int first = number % 2;
        stack.push(first);
        number /= 2;
    }

    QString final;
    while(!stack.empty()){
        int second = stack.top();
        stack.pop();
        final += QString::number(second);
    }

    if (startNumber < 0){
        final = isNegative(final);
    }

    if (parts.size() > 1){
        double fractionalPart = ("0." + parts[1]).toDouble();
        final += ".";
        size_t precisions = 6;

        while (precisions > 0 && fractionalPart != 0){
            fractionalPart *= 2;
            int bit = static_cast<int>(fractionalPart);
            final += QString::number(bit);
            fractionalPart -= bit;
            --precisions;
        }
    }

    return final;
}

// [0..7]
QString toEight(QString workNumber){
    QStringList parts = workNumber.split('.');
    std::stack<size_t> stack;

    int number = parts[0].toInt();
    int startNumber = number;

    if (number == 0) return "0";

    if (number < 0){
        number = -number;
    }

    while (number > 0){
        size_t first = number % 8;
        stack.push(first);
        number /= 8;
    }

    QString final;
    while(!stack.empty()){
        size_t second = stack.top();
        stack.pop();
        final += QString::number(second);
    }

    if (startNumber < 0){
        final.insert(0, '-');
    }

    if (parts.size() > 1){
        double fractionalPart = ("0." + parts[1]).toDouble();
        final += ".";
        size_t precisional = 6;

        while (precisional > 0 && fractionalPart != 0){
            fractionalPart *= 8;
            size_t bit = static_cast<size_t>(fractionalPart);
            final += QString::number(bit);
            fractionalPart -= bit;
            --precisional;
        }
    }

    return final;
}

//[0..9ABCDEF]
QString toSixteen(QString workNumber){
    QStringList parts = workNumber.split('.');

    QHash<size_t, QChar> map = {
        {10, 'A'},
        {11, 'B'},
        {12, 'C'},
        {13, 'D'},
        {14, 'E'},
        {15, 'F'}
    };

    std::stack<QChar> stack;
    int number = parts[0].toInt();
    int startNumber = number;

    if (number == 0)
        return "0";

    if (number < 0)
        number = -number;

    while (number > 0){
        size_t first = number % 16;
        if (first >= 10)
            stack.push(map[first]);
        else
            stack.push(QChar::fromLatin1('0' + first));
        number = number / 16;
    }

    QString final;
    while (!stack.empty()){
        final += stack.top();
        stack.pop();
    }

    if (startNumber < 0){
        final.insert(0, '-');
    }

    if (parts.size() > 1){
        double fractionalPart = ("0." + parts[1]).toDouble();
        final += ".";
        size_t precisions = 6;

        while (precisions > 0 && fractionalPart != 0){
            fractionalPart *= 16;
            size_t bit = static_cast<size_t>(fractionalPart);
            fractionalPart -= bit;

            if (bit >= 10)
                final += map[bit];
            else
                final += QChar::fromLatin1('0' + bit);

            --precisions;
        }
    }

    return final;
}

//[0,1]
QString toBCD(QString workNumber){
    QHash<size_t, std::string> map = {
        {0, "0000"}, {1, "0001"}, {2, "0010"}, {3, "0011"}, {4, "0100"},
        {5, "0101"}, {6, "0110"}, {7, "0111"}, {8, "1000"}, {9, "1001"}
    };

    size_t number = workNumber.toInt();

    std::stack<size_t> sum;
    while (number > 0){
        size_t first = number % 10;
        sum.push(first);
        number /= 10;
    }

    QString final;
    while (!sum.empty()){
        final += map[sum.top()];
        final += "|";
        sum.pop();
    }

    return final;
}

//Grey
QString toGrey(QString workNumber){
    QString final = toBinaryCod(workNumber);
    return binaryToGrey(final);
}
