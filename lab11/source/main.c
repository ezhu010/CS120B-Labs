//--------------------------------------
// LED Matrix Demo SynchSM
// Period: 100 ms
//--------------------------------------
enum Demo_States
{
    shift
};
int Demo_Tick(int state)
{

    // Local Variables
    static unsigned char pattern = 0x80; // LED pattern - 0: LED off; 1: LED on
    static unsigned char row = 0xFE;     // Row(s) displaying pattern.
                                         // 0: display pattern on row
                                         // 1: do NOT display pattern on row
    // Transitions
    switch (state)
    {
    case shift:
        break;
    default:
        state = shift;
        break;
    }
    // Actions
    switch (state)
    {
    case shift:
        if (row == 0xEF && pattern == 0x01)
        { // Reset demo
            pattern = 0x80;
            row = 0xFE;
        }
        else if (pattern == 0x01)
        { // Move LED to start of next row
            pattern = 0x80;
            row = (row << 1) | 0x01;
        }
        else
        { // Shift LED one spot to the right on current row
            pattern >>= 1;
        }
        break;
    default:
        break;
    }
    PORTC = pattern; // Pattern to display
    PORTD = row;     // Row(s) displaying pattern
    return state;
}
