/*
 * Pedro - A simple library to control the Meccanoid G15
 * @doc http://cdn.meccano.com/open-source/Meccano_SmartModuleProtocols_2015.pdf
*/

#include "Pedro.h"

Pedro::Pedro(
    int pinHead,
    int pinRightShoulder,
    int pinRightHand,
    int pinLeftShoulder,
    int pinLeftHand,
    int pinLeftWheel1,
    int pinLeftWheel2,
    int pinLeftWheelEnable,
    int pinRightWheel1,
    int pinRightWheel2,
    int pinRightWheelEnable
) {
    this->_pins[0] = pinHead;
    this->_pins[1] = pinRightShoulder;
    this->_pins[2] = pinRightHand;
    this->_pins[3] = pinLeftShoulder;
    this->_pins[4] = pinLeftHand;
    this->_pins[5] = pinLeftWheel1;
    this->_pins[6] = pinLeftWheel2;
    this->_pins[7] = pinLeftWheelEnable;
    this->_pins[8] = pinRightWheel1;
    this->_pins[9] = pinRightWheel2;
    this->_pins[10] = pinRightWheelEnable;
    for (int i = 0; i < 5; i++)
        this->_controllers[i] = new MeccaBrain(this->_pins[i]);
}

Pedro::~Pedro()
{
    for (int i = 0; i < 5; i++)
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
        if (!(selector & mask))
            continue;
        if ((selector & Pedro::HEAD) || (selector & Pedro::LEFT_WHEEL) || (selector & Pedro::RIGHT_WHEEL))
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
        if (!(selector & mask))
            continue;
        if ((selector & Pedro::HEAD) || (selector & Pedro::LEFT_WHEEL) || (selector & Pedro::RIGHT_WHEEL))
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
        if (!(selector & mask))
            continue;
        if ((selector & Pedro::HEAD) || (selector & Pedro::LEFT_WHEEL) || (selector & Pedro::RIGHT_WHEEL))
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
        if (!(selector & mask))
            continue;
        if ((selector & Pedro::LEFT_WHEEL) || (selector & Pedro::RIGHT_WHEEL))
            continue;
        if (this->_pins[index] == -1)
            continue;
        this->_controllers[index]->communicate();
    }
}

void Pedro::move(byte selector, int speed)
{
    unsigned char index = 0;
    char pin1 = 0;
    char pin2 = 0;
    char pinEnable = 0;

    if (abs(speed) > 255)
        return;
    for (byte mask = 00000001; mask > 0; mask <<= 1, index++) {
        if (!(selector & mask))
            continue;
        if (mask & Pedro::LEFT_WHEEL) {
            pin1 = this->_pins[5];
            pin2 = this->_pins[6];
            pinEnable = this->_pins[7];
        } else if (mask & Pedro::RIGHT_WHEEL) {
            pin1 = this->_pins[8];
            pin2 = this->_pins[9];
            pinEnable = this->_pins[10];
        } else
            continue;
        digitalWrite(pinEnable, abs(speed));
        analogWrite(pin1, !(speed > 0));
        digitalWrite(pin2, (speed > 0));
    }
}
