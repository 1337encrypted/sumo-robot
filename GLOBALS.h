#include "BTS7960.h"
// #include "BUZZER.h"

// enum class motorStates : uint8_t {
//   FRONT = 'F',
//   BACK = 'B',
//   LEFT = 'L',
//   RIGHT = 'R',
//   LEFTFRONT = 'G',
//   RIGHTFRONT = 'I',
//   LEFTBACK = 'H',
//   RIGHTBACK = 'J',
//   STOP = 'S',
//   STOPALL = 'D',
//   DISCONNECT = 'Q',
// };
// motorStates motorStatus = motorStates::STOPALL;                        //State variable set to STOP initially


constexpr uint8_t ch1Pin = A0;  // Steering
constexpr uint8_t ch2Pin = A1;  // Throttle

const int throttleMin = 1000;
const int throttleMax = 2000;

const int steeringMin = 1284;
const int steeringMax = 1760;

const int pwmCenter = 1500;

//BTS7960 motor driver 1 pin definitions
const String leftMotorsId = "Left Motors";
constexpr uint8_t R_EN1 = 4;  
constexpr uint8_t L_EN1 = 2;
constexpr uint8_t RPWM1 = 3;           //PWM 490hz
constexpr uint8_t LPWM1 = 5;           //PWM 980hz
constexpr uint8_t R_IS1 = -1;          //Alarm pin
constexpr uint8_t L_IS1 = -1;          //Alarm pin

//BTS7960 motor driver 2 pin definitions
const String rightMotorsId = "Right Motors";
constexpr uint8_t R_EN2 = 8;
constexpr uint8_t L_EN2 = 7;
constexpr uint8_t RPWM2 = 6;            //PWM 490hz
constexpr uint8_t LPWM2 = 9;            //PWM 980hz
constexpr uint8_t R_IS2 = -1;           //Alarm pin
constexpr uint8_t L_IS2 = -1;           //Alarm pin

//Buzzer definition section
// const String buzzId = "Buzzer";
// constexpr uint8_t buzzpin = 11;  //Active buzzer use 100 ohms resistor

// Create objects 
BTS7960 motor1(L_EN1, R_EN1, LPWM1, RPWM1, R_IS1, L_IS1, leftMotorsId);
BTS7960 motor2(L_EN2, R_EN2, LPWM2, RPWM2, R_IS2, L_IS2, rightMotorsId);
// buzzer buzz(buzzpin, buzzId); 