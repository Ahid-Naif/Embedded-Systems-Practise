#include "Blinky.h"

unsigned char *pinb = (unsigned char *)0x23;
unsigned char *ddrb = (unsigned char *)0x24;
unsigned char *portb = (unsigned char *)0x25;
unsigned char *pinc = (unsigned char *)0x26;
unsigned char *ddrc = (unsigned char *)0x27;
unsigned char *portc = (unsigned char *)0x28;
unsigned char *pind = (unsigned char *)0x29;
unsigned char *ddrd = (unsigned char *)0x2A;
unsigned char *portd = (unsigned char *)0x2B;

Blinky::Blinky(char port, int pin, unsigned long ONTime, unsigned long OFFTime)
{
    this->_portName = port;
    this->_pin = pin;
    this->_ONTime = ONTime;
    this->_OFFTime = OFFTime;

    this->initializePorts();
    this->_OFFWait = millis();
    this->_ONWait = millis();
}

void Blinky::Refresh()
{

    if (this->_isON) // if LED is ON
    {
        if ((millis() - this->_ONWait) >= this->_ONTime)
        {
            this->turnOFF();
            this->_isON = 0;
            this->_OFFWait = millis();
        }
    }
    else // else if LED is OFF
    {
        if ((millis() - this->_OFFWait) >= this->_OFFTime)
        {
            this->turnON(); // turn pin ON
            this->_isON = 1;
            this->_ONWait = millis();
        }
    }
}

void Blinky::initializePorts()
{
    switch (this->_portName)
    {
    case 'B':
        *ddrb |= (1 << this->_pin); // determine directions as OUTPUT
        break;
    case 'C':
        *ddrc |= (1 << this->_pin); // determine directions as OUTPUT
        break;
    case 'D':
        *ddrd |= (1 << this->_pin); // determine directions as OUTPUT
        break;
    }
}

void Blinky::turnON()
{
    switch (this->_portName)
    {
    case 'B':
        *portb |= (1 << this->_pin);
        break;
    case 'C':
        *portc |= (1 << this->_pin);
        break;
    case 'D':
        *portd |= (1 << this->_pin);
        break;
    }
}

void Blinky::turnOFF()
{
    switch (this->_portName)
    {
    case 'B':
        *portb &= ~(1 << this->_pin);
        break;
    case 'C':
        *portc &= ~(1 << this->_pin);
        break;
    case 'D':
        *portd &= ~(1 << this->_pin);
        break;
    }
}