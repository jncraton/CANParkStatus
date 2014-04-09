/*
  * FileName:        main.c
 * Dependencies:    ECANPoll.h, htc.h
 * Processor:       PIC18FXX8X
 * Complier:        HITECH C Compiler
 *
 *
 * Author:
 * Matt Brocker
 * Jon Craton
 *********************************************************************/

#include <htc.h>
#include "ECANPoll.h"

#if defined(MCHP_C18)
// Configuration settings for PICDEM CAN-LIN3 - This setting will depend
// on your hardware.
#pragma romdata CONFIG

_CONFIG_DECL(_OSC_EC_1H, \
             _CONFIG2L_DEFAULT, \
             _WDT_OFF_2H, \
             _CONFIG3L_DEFAULT, \
             _CONFIG3H_DEFAULT, \
             _LVP_OFF_4L & _DEBUG_OFF_4L, \
             _CONFIG5L_DEFAULT, \
             _CONFIG5H_DEFAULT, \
             _CONFIG6L_DEFAULT, \
             _CONFIG6H_DEFAULT, \
             _CONFIG7L_DEFAULT, \
             _CONFIG7H_DEFAULT);

#pragma romdata
#endif

#if defined(MCHP_C18)
    #define PORTB_RB4   PORTBbits.RB4

#elif defined(HITECH_C18)
    #define PORTB_RB4   RB4
#endif

void main(void)
{
    unsigned long id;
    BYTE data[8];
    BYTE dataLen;
    ECAN_RX_MSG_FLAGS flags;

    
    // Set the direction and intial value for output port
    TRISA = 0b00000000;
    LATA = 0x00;

    ECANInitialize();

    while(1) {
        while( !ECANReceiveMessage(&id, data, &dataLen, &flags) );

        // only message id 3b2 should get here
        // message filters are configured in ECANPoll.def
        if ( data[0] == 0xF0 ) {
            LATA = 0xFF;
        } else {
            LATA = 0x00;
        }
    }
}