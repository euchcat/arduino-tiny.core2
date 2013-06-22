#define ARDUINO_MAIN 1
#include <Arduino.h>

int main(void)
{
  SP = RAMEND;

  init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

