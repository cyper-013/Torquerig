#include "motor.h"

#define TB6612_PWMA   9
#define TB6612_PWMB   10
#define TB6612_AIN1  4
#define TB6612_AIN2  5
#define TB6612_BIN1  6
#define TB6612_BIN2  7
#define TB6612_STBY  8

void Motor::begin()
{
    // Timer1 Phase & Frequency Correct PWM on OC1A (D9)
    TCCR1A =
        (1 << COM1A1) |
        (0 << COM1A0) |
        (1 << COM1B1) |
        (0 << COM1B0) |
        (0 << WGM11)  |
        (0 << WGM10);

    TCCR1B =
        (0 << ICNC1) |
        (0 << ICES1) |
        (1 << WGM13) |
        (0 << WGM12) |
        (0 << CS12)  |
        (0 << CS11)  |
        (1 << CS10);

    setBitDepth(DEFAULT_FFB_BITDEPTH);

    OCR1A = 0;
    OCR1B = 0;

//    pinMode(TB6612_PWM, OUTPUT);
//    pinMode(TB6612_AIN1, OUTPUT);
//    pinMode(TB6612_AIN2, OUTPUT);
//    pinMode(TB6612_STBY, OUTPUT);

    pinMode(TB6612_PWMA,OUTPUT);
    pinMode(TB6612_PWMB,OUTPUT);
    
    pinMode(TB6612_AIN1,OUTPUT);
    pinMode(TB6612_AIN2,OUTPUT);
    
    pinMode(TB6612_BIN1,OUTPUT);
    pinMode(TB6612_BIN2,OUTPUT);
    
    pinMode(TB6612_STBY,OUTPUT);

    digitalWriteFast(TB6612_STBY, HIGH);

    digitalWriteFast(TB6612_AIN1, LOW);
    digitalWriteFast(TB6612_AIN2, LOW);
    digitalWriteFast(TB6612_BIN1, LOW);
    digitalWriteFast(TB6612_BIN2, LOW);

#ifdef MOTOR_ENABLE_PIN
    pinMode(MOTOR_ENABLE_PIN, OUTPUT);
    digitalWriteFast(MOTOR_ENABLE_PIN, LOW);
#endif
}


// Force range: -16383 ... +16383
void Motor::setForce(int16_t force)
{
    force = constrain(force, -16383, 16383);

#ifdef MOTOR_ENABLE_PIN
    digitalWriteFast(MOTOR_ENABLE_PIN, force != 0);
#endif

    if (force > 0)
    {
        digitalWriteFast(TB6612_STBY, HIGH);
    
        digitalWriteFast(TB6612_AIN1, HIGH);
        digitalWriteFast(TB6612_AIN2, LOW);
        digitalWriteFast(TB6612_BIN1, HIGH);
        digitalWriteFast(TB6612_BIN2, LOW);
    
        uint16_t pwm = (1 + force) >> bitShift;
        OCR1A = pwm;
        OCR1B = pwm;
    }
    else if (force < 0)
    {
        digitalWriteFast(TB6612_STBY, HIGH);
    
        digitalWriteFast(TB6612_AIN1, LOW);
        digitalWriteFast(TB6612_AIN2, HIGH);
        digitalWriteFast(TB6612_BIN1, LOW);
        digitalWriteFast(TB6612_BIN2, HIGH);
    
        uint16_t pwm = (1 - force) >> bitShift;
        OCR1A = pwm;
        OCR1B = pwm;
    }
    else
    {
        OCR1A = 0;
        OCR1B = 0;
    
        digitalWriteFast(TB6612_AIN1, LOW);
        digitalWriteFast(TB6612_AIN2, LOW);
        digitalWriteFast(TB6612_BIN1, LOW);
        digitalWriteFast(TB6612_BIN2, LOW);
    
        digitalWriteFast(TB6612_STBY, LOW);
    }
}


void Motor::setBitDepth(uint8_t value)
{
    value = constrain(value, 1, 14);

    bitDepth = value;
    bitShift = 14 - bitDepth;

    ICR1 = 1 << bitDepth;
}
