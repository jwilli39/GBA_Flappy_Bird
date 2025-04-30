// flappy_utils.c
// Utility functions for displaying text and adding delay in the Flappy Bird game

#include "gba.h"
#include "flappy_utils.h"

/**
 * @brief Sets text on the screen at a given location.
 * @param str The string to be displayed.
 * @param row The row (vertical position) on the screen.
 * @param col The column (horizontal position) on the screen.
 */
void set_text(char *str, int row, int col)
{
    // Calculate index in the text map
    int index = row * 32 + col;

    // The first 32 characters are non-printable (control codes)
    int missing = 32;

    // Pointer to screen block 24 (text rendering area)
    volatile unsigned short *ptr = screen_block(24);

    // Loop through and place each character
    while (*str)
    {
        ptr[index] = *str - missing;
        index++;
        str++;
    }
}

/**
 * @brief Delays the execution for a specified amount of time.
 * @param amount The duration of the delay (scaled by 10).
 */
void delay(unsigned int amount)
{
    // Loop-based delay
    for (int i = 0; i < amount * 10; i++) 
    {
    }
}
