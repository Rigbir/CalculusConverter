#include <DecimalSystem.h>

// [0, 1]
QString toBinaryCod(QString workNumber){
    QStringList parts = workNumber.split('.');

    std::stack<int> stack;
    int number = parts[0].toInt();

    if (number == 0) return "0";

    while (number > 0){
        int first = number % 2;
        stack.push(first);
        number = number / 2;
    }

    QString final;
    while(!stack.empty()){
        int second = stack.top();
        stack.pop();
        final += QString::number(second);
    }

    if (parts.size() == 1)
        return final;

    double fractionalPart = ("0." + parts[1]).toDouble();
    final += ".";
    int precisions = 6;
    while (precisions > 0 && fractionalPart != 0){
        fractionalPart *= 2;
        int bit = static_cast<int>(fractionalPart);
        final += QString::number(bit);
        fractionalPart -= bit;
        --precisions;
    }

    return final;
}

// [0..7]
QString toEight(QString workNumber){
    QStringList parts = workNumber.split('.');

    std::stack<int> stack;
    int number = parts[0].toInt();

    if (number == 0) return "0";

    while (number > 0){
        int first = number % 8;
        stack.push(first);
        number = number / 8;
    }

    QString final;
    while(!stack.empty()){
        int second = stack.top();
        stack.pop();
        final += QString::number(second);
    }

    if (parts.size() == 1)
        return final;

    double fractionalPart = ("0." + parts[1]).toDouble();
    final += ".";
    int precisional = 6;
    while (precisional > 0 && fractionalPart != 0){
        fractionalPart *= 8;
        int bit = static_cast<int>(fractionalPart);
        final += QString::number(bit);
        fractionalPart -= bit;
        --precisional;
    }

    return final;
}

//[0..9ABCDEF]
QString toSixteen(QString workNumber){
    QStringList parts = workNumber.split('.');

    QHash<int, QChar> map = {
        {10, 'A'},
        {11, 'B'},
        {12, 'C'},
        {13, 'D'},
        {14, 'E'},
        {15, 'F'}
    };

    std::stack<QChar> stack;
    int number = parts[0].toInt();

    if (number == 0)
        return "0";

    while (number > 0){
        int first = number % 16;
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

    if (parts.size() == 1)
        return final;

    double fractionalPart = ("0." + parts[1]).toDouble();
    final += ".";
    int precisions = 6;
    while (precisions > 0 && fractionalPart != 0){
        fractionalPart *= 16;
        int bit = static_cast<int>(fractionalPart);
        fractionalPart -= bit;

        if (bit >= 10)
            final += map[bit];
        else
            final += QChar::fromLatin1('0' + bit);

        --precisions;
    }

    return final;
}
