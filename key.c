#include "teamplus.h"


int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        int key = _getch();

        if (key == 224)
        {
            key = _getch();

            switch (key)
            {
            case 72: // Up arrow
                return 1; // Return a unique value for the up arrow key
            case 80: // Down arrow
                return 2; // Return a unique value for the down arrow key
            case 75: // Left arrow
                return 3; // Return a unique value for the left arrow key
            case 77: // Right arrow
                return 4; // Return a unique value for the right arrow key
            }
        }
        else if (key == 'z')
        {
            return 5; // Return a unique value for the 'z' key
        }

        return key; // Return the key code for non-arrow keys
    }

    return 0; // Return 0 if no key is pressed
}