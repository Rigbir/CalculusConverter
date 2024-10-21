#pragma once
#include <Library.h>

//BCD -> 2
QString BCDtoBinary(QString number);

//BCD -> 8
QString BCDtoOctal(QString number);

//BCD -> 10
QString BCDtoOrdinary(QString number);

//BCD -> 16
QString BCDtoHexadecimal(QString number);

//BCD -> Grey
QString BCDtoGrey(QString number);
