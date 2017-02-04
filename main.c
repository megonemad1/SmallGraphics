#include "main.h"
int main()
{
       init_lcd();
       set_frame_rate_hz(61);
       display_string("hello world");
       return 0;
}
