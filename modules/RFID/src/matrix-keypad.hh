/**
 * \file      matrix-keypad.hh
 * \brief     Class for using a 3x4 or 4x4 matrix keypad
 * \author    Tim IJntema, René de Kluis, Ricardo Bouwman
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <string>
#include <wiringPi.h>

/**
 * \brief Class for using a 3x4 or 4x4 keypad
 *
 * This class can be used to capture input from a 4x4 keypad using wiringPi.
 *
 */
class MatrixKeypad {
private:
    const char noKey = 'h';
    const int asciiZero = 48;
    const int asciiNine = 57;
    const unsigned int maxPinCodeLength = 16;
    const unsigned int checkKeyHeldDelay = 10;
    const int minColSize = 3;
    const int maxColSize = 4;
    const int rowSize = 4;
    const int colSize;

    int activeRow = -1;

    const int *row;
    const int *column;

    // The only difference between the 3x4 and 4x4 keypad is that the 3x4 keypad
    // has no alphabetic characters
    const char keypad[4][4] = {{'1', '2', '3', 'A'},
                         {'4', '5', '6', 'B'},
                         {'7', '8', '9', 'C'},
                         {'*', '0', '#', 'D'}};

public:
    /**
    * \brief Constructor
    *
    * This constructor collects all the pins that are needed for the keypad.
    * It takes the size of the keypad and the pins on which it is attached.
    *
    * \param[in] row Pins that are used as rows for the keypad.
    * \param[in] column Pins that are used as columns for the keypad.
    * \param[in] colSize Amount of columns on the keypad.
    *
    */
    MatrixKeypad(const int *row, const int *column, int colSize = 3);

    /**
    * \brief Obtain separate keys
    *
    * This function obtains the separate keys from the keypad.
    * It waits for a key to be pressed and then returns the pressed key
    * as a character.
    *
    * \return The key that is pressed in the form of a character
    *
    */
    char getKey();

    /**
    * \brief Obtain a string of keys
    * This function will collect keys that are pressed on the keypad.
    * The keys will be collected until the '#' key is pressed.
    *
    * \return The a string containing the pressed keys.
    *
    */
    std::string getString();
};
