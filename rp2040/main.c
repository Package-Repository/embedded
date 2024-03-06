#include <stdlib.h>
#include <stdio.h>
#include <string.h>   
#include <ctype.h>
#include <inttypes.h>

#include "bsp/board.h"
#include "tusb.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "hardware/pwm.h"
#include "hardware/structs/rosc.h"
#include "generic_include.h"
#include "mech_usb_protocol.h"

#define CDC_DATA_CHAN   0
#define CDC_CTRL_CHAN   1
#define LED_PIN         PICO_DEFAULT_LED_PIN

byte_t buffer[64];

static void send_cdc(byte_t chan, byte_t* data, uint16_t len){
    tud_cdc_n_write(chan, data, len);
    tud_cdc_n_write_flush(chan);
}

void MOVE_MOTORS_F(const byte_t* data)
{
    byte_t msg[4] = {'n', 'i', 'c', 'e'};
    gpio_put(LED_PIN, 1);
    send_cdc(CDC_DATA_CHAN, msg, 4);
    (void)data;
}

void setup_light(void)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);
}

void hardware_init(void)
{
    stdio_init_all();
    board_init();
    tud_init(BOARD_TUD_RHPORT);
    setup_light();
}

void usb_mech_init(void)
{
    init_robot_actions();
    set_robot_action(MOTORS, MOTOR_MOVE, &MOVE_MOTORS_F);
}

void usb_mech_task(void)
{
    byte_t init_byte; tud_cdc_read(&init_byte, 1);
    if(init_byte==INIT_BYTE)
    {
        byte_t meta_flags; tud_cdc_read(&meta_flags, 1);
        const byte_t msg_size = GET_MESSAGE_SIZE(meta_flags); 
        tud_cdc_read(&buffer, msg_size);
        HANDLE_MESSAGE(buffer, msg_size);
    }
}

int main()
{
    hardware_init();
    usb_mech_init();
    for (;;)
    {        
        tud_task();
        if (tud_cdc_connected()) 
        {
            if (tud_cdc_available()) 
            {
                usb_mech_task();
            }
        }        
    }
    return 0;
}
