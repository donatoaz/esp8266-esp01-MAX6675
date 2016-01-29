# esp8266-esp01-MAX6675
Simple sketch with the connection of a Max6675 to an esp8266 model esp-01

It is important to edit the Max6675 library with the following change on max6675.cpp:

    ...
    #elif defined(ESP8266)
      #include <pgmspace.h>
      #define _delay_ms(ms) delayMicroseconds((ms) * 1000)
    #endif
    //#include <util/delay.h>
    #ifdef __avr__
      #include <util/delay.h>
    #endif
    ...
