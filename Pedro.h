/*
 * Pedro - A simple library to control the Meccanoid G15
 * @doc http://cdn.meccano.com/open-source/Meccano_SmartModuleProtocols_2015.pdf
 *      I used a L293D to control the wheels
*/

#ifndef PEDRO_H_
#define PEDRO_H_

#include "Arduino.h"
#include "MeccaBrain.h"

class Pedro {
    public:
        enum ComponentType {
            HEAD =           0b00000001,
            RIGHT_SHOULDER = 0b00000010,
            RIGHT_HAND =     0b00000100,
            LEFT_SHOULDER =  0b00001000,
            LEFT_HAND =      0b00010000,
            LEFT_WHEEL =     0b00100000,
            RIGHT_WHEEL =    0b01000000
        };

        /**
         * @brief Initialize the robot
         *
         * @param pinHead pin head
         * @param pinRightShoulder pin right shoulder
         * @param pinRightHand pin right hand
         * @param pinLeftShoulder pin left shoulder
         * @param pinLeftHand pin left hand
         */
        Pedro(
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
        );

        ~Pedro();

        /**
         * @brief Set a component's pin
         *
         * @param pin component's pin
         * @param type type of component
         */
        void setPin(int pin, ComponentType type);

        /**
         * @brief Set the eyes colors
         *
         * @param r
         * @param g
         * @param b
         * @param fadeTime
         */
        void setEyesColor(byte selector, byte r, byte g, byte b, byte fadeTime);

        /**
         * @brief Set the servo color
         *
         */
        void setServoColor(byte selector, int servoNum, byte color);

        /**
         * @brief Set the servo position
         *
         */
        void setServoPosition(byte selector, int servoNum, byte pos);

        /**
         * @brief Get the servo position object
         *
         */
        void getServoPosition(byte selector);

        /**
         * @brief Communicate with the robot
         *
         */
        void communicate(byte selector);

        /**
         * @brief Move the robot
         *
         */
        void move(byte selector, int speed);
    private:
        unsigned char _pins[11];
        MeccaBrain *_controllers[5];
};

#endif /* !PEDRO_H_ */
