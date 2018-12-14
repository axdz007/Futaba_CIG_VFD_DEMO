/*			FUTABA VFD≤‚ ‘≥Ã–Ú				*/
/*				œÍ«Èº˚Runtime.c				*/

#include "stm32f0xx.h"
#include "Runtime.h"

int main(void)
{
	Runtime_Init();
	while(1)
  {
		Runtime_Running();
  }
 
}




/*#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

  while (1)
  {
		
  }
}
#endif*/
