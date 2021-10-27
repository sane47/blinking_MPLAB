
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <stdio.h>
#include <string.h>

volatile uint16_t val_pulse_count = 0;

char buf[5];
char buf2[] = "\r\n";
char buffer_tmp[500];

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
void EIC_UserHandler(uintptr_t context)
{
    LED_Toggle();
    ++val_pulse_count;
}



int main ( void )
{
    itoa(val_pulse_count,buf,2 );
    
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    EIC_CallbackRegister(EIC_PIN_7,EIC_UserHandler, 0);
    
    
    while ( true ) {
        
      sprintf(buffer_tmp, "Count val : %d\r\n", val_pulse_count);
      SERCOM3_USART_Write(buffer_tmp, sizeof(buffer_tmp));
      for(uint16_t i = 0; i < 100; i++) {
          for(uint16_t j = 0; j < 65535; j++);
      }
      
        /* Maintain state machines of all polled MPLAB Harmony modules. */
//        SYS_Tasks ( );
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


