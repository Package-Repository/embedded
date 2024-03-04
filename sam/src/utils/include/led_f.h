#ifndef LED_F_H
#define LED_F_H

#include "asf.h"

#define LED0_PIO    		   PIOD
#define LED0_PIN    		   PIO_PD22
#define SET_LIGHT_ON()         LED0_PIO->PIO_CODR = LED0_PIN
#define SET_LIGHT_OFF()        LED0_PIO->PIO_SODR = LED0_PIN
#define TOGGLE_LIGHT() \
                               do { \
                                    if (light_on) \
                                        SET_LIGHT_OFF(); \
                                    else \
                                        SET_LIGHT_ON(); \
                                    light_on = !light_on; \
                                } while (0)


#endif