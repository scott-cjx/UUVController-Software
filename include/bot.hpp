/**
 * @file bot.hpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 10-10-2024
 * 
 * @copyright Copyright (c) 2024 Scott CJX
 * 
 */

#ifndef _INCLUDE_BOT
#define _INCLUDE_BOT

#include <Arduino.h>
#include <Servo.h>

#include "main.hpp"

#define STOP_CMD 1500
#define MAX_FWD_CMD 1900
#define MAX_BWD_CMD 1100

typedef struct _thruster_t
{
	// private
	Servo esc;
	uint16_t pulseWidth;

	// public
	uint16_t pin;
} thruster_t;

typedef struct _pump_t
{
	uint16_t dutyCycle;

	uint16_t pin;
} pump_t;

typedef struct _bot_t
{
	thruster_t thrusters[NUM_THRUSTERS];
	pump_t pumps[NUM_PUMPS];

	bool heightDir;
	uint8_t pumpSpd;
} bot_t;

typedef struct _thruster_cmd_t
{
	uint8_t percentSpeed;
	bool direction;
} thruster_cmd_t;

void _init_pump_struct(pump_t *ppump);
void _init_pump_inst(pump_t *ppump);
void _init_thruster_struct(thruster_t *thruster);
void _init_thruster_inst(thruster_t *thruster);
void init_bot(bot_t *pbot, const uint8_t *thruster_pins, const uint8_t *pump_pins);
void send_pump_cmd(bot_t *pbot, uint8_t whichPump, uint8_t percentSpeed);
void send_thruster_cmd(bot_t *pbot, uint8_t whichThruster, thruster_cmd_t *pthruster_cmd);

#endif /* _INCLUDE_BOT */
