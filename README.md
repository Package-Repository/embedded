# Embedded Code For Mechatronics

Code for robotic hardware will be placed here

## Current Supported Platforms

    Teensy4.1
    RP2040
    SAM4E

## Using USB Protocol 

    for (;;)
    {
        const int byte = udi_cdc_getc();
        if (byte == INIT_BYTE)
        {
            const byte_t meta_flags = udi_cdc_getc();
            const byte_t msg_size = GET_MESSAGE_SIZE(meta_flags); 
            udi_cdc_read_buf(buffer, msg_size);
            HANDLE_MESSAGE(buffer, msg_size);
        }   
        CLEAR_BUFFER(buffer, USB_PACKET_SIZE_BYTES);
    }