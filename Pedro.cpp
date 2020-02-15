/*
 * Pedro - A simple library to control the Meccanoid G15
 * @doc http://cdn.meccano.com/open-source/Meccano_SmartModuleProtocols_2015.pdf
*/

#include "Pedro.h"

Pedro::Pedro(int pinHead, int pinRightShoulder, int pinRightHand, int pinLeftShoulder, int pinLeftHand)
{
    this->_pins[0] = pinHead;
    this->_pins[1] = pinRightShoulder;
    this->_pins[2] = pinRightHand;
    this->_pins[3] = pinLeftShoulder;
    this->_pins[4] = pinLeftHand;
    for (int i = 0; i < 6; i++)
        this->_controllers[i] = new MeccaBrain(this->_pins[i]);
}

Pedro::~Pedro()
{
    for (int i = 0; i < 6; i++)
        delete(this->_controllers[i]);
}

void Pedro::setPin(int pin, ComponentType type)
{
    unsigned char index = 0;

    while (index >>= 1 != 0)
        index += 1;
    if (index < 0 || index > 5)
        return;
    this->_pins[index] = pin;
}

void Pedro::setEyesColor(byte selector, byte r, byte g, byte b, byte fadeTime)
{
    if (!(selector & Pedro::HEAD))
        return;
    if (this->_pins[0] == -1)
        return;
    this->_controllers[0]->communicate();
    this->_controllers[0]->setLEDColor(r, g, b, fadeTime);
}

void Pedro::setServoColor(byte selector, int servoNum, byte color)
{
    unsigned char index = 0;

    for (byte mask = 00000001; mask > 0; mask <<= 1, index++) {
        if (!(selector & mask) || (selector & Pedro::HEAD))
            continue;
        if (this->_pins[index] == -1)
            continue;
        this->_controllers[index]->communicate();
        this->_controllers[index]->setServoColor(servoNum, color);
    }
}

void Pedro::setServoPosition(byte selector, int servoNum, byte pos)
{
    unsigned char index = 0;

    for (byte mask = 00000001; mask > 0; mask <<= 1, index++) {
        if (!(selector & mask) || (selector & Pedro::HEAD))
            continue;
        if (this->_pins[index] == -1)
            continue;
        this->_controllers[index]->communicate();
        this->_controllers[index]->setServoPosition(servoNum, pos);
    }
}

void Pedro::getServoPosition(byte selector)
{
    unsigned char index = 0;

    for (byte mask = 00000001; mask > 0; mask <<= 1, index++) {
        if (!(selector & mask) || (selector & Pedro::HEAD))
            continue;
        if (this->_pins[index] == -1)
            continue;
        this->_controllers[index]->communicate();
        this->_controllers[index]->getServoPosition(0);
    }
}

void Pedro::communicate(byte selector)
{
    unsigned char index = 0;

    for (byte mask = 00000001; mask > 0; mask <<= 1, index++) {
        if (!(selector & mask) || (selector & Pedro::HEAD))
            continue;
        if (this->_pins[index] == -1)
            continue;
        this->_controllers[index]->communicate();
    }
}