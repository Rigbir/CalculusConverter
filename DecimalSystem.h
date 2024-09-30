#pragma once
#include <Library.h>

// [0, 1]
QString toBinaryCod(QString workNumber);

// [0..7]
QString toEight(QString workNumber);

//[0..9ABCDEF]
QString  toSixteen(QString workNumber);
