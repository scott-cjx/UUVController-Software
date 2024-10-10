/**
 * @file main.hpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 10-10-2024
 * 
 * @copyright Copyright (c) 2024 Scott CJX
 * 
 */

#ifndef _INCLUDE_MAIN
#define _INCLUDE_MAIN

#define NUM_THRUSTERS 2
#define NUM_PUMPS 2

const uint8_t thruster_pins[NUM_THRUSTERS] = {PB0, PB1};
const uint8_t pump_pins[NUM_THRUSTERS] = {PA8, PC9};

#define PUMP_ALWAYSMAX 0
#define _PUMP_UP 0
#define _PUMP_DN 1

#define _THRUSTER_L 0
#define _THRUSTER_R 1

#endif /* _INCLUDE_MAIN */
