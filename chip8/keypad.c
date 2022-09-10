#include "keypad.h"
#include "driver.h"

bool KeyPadPressed(keyTypeE keyType)
{
    bool pressed = false;
    uint16 keyState = GetKeyStateHW();
    if(keyType <= KEY_F)
    {
        if(((keyState >> keyType) & 0x1) == 0x1)
            pressed = true;
    }

    return pressed;
}


bool UpdatedQuitState()
{  
    return IsQuitHW();
}