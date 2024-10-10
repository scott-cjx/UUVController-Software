/**
 * @file bot.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief
 * @version 0.1
 * @date 10-10-2024
 *
 * @copyright Copyright (c) 2024 Scott CJX
 *
 */

#include "bot.hpp"

#include <Arduino.h>
#include <Servo.h>

#define _PUMP_STALL_BELOW_THRESHOLD 10

#define PWM_FACTOR 2.55f
#define PUMP_STALL_BASE_THRESHOLD_PWM _PUMP_STALL_BELOW_THRESHOLD *PWM_FACTOR

void _init_pump_struct(pump_t *ppump)
{
	pinMode(ppump->pin, OUTPUT);
	ppump->dutyCycle = 0;
}

void _init_pump_inst(pump_t *ppump)
{
	ppump->dutyCycle = 0;
	analogWrite(ppump->pin, ppump->dutyCycle);
}

void _init_thruster_struct(thruster_t *thruster)
{
	thruster->esc.attach(thruster->pin);
	thruster->pulseWidth = STOP_CMD;
}

void _init_thruster_inst(thruster_t *thruster)
{
	thruster->pulseWidth = STOP_CMD;
	thruster->esc.writeMicroseconds(thruster->pulseWidth);
}

void init_bot(bot_t *pbot, const uint8_t *thruster_pins, const uint8_t *pump_pins)
{
	analogWriteResolution(8);
	analogWriteFrequency(1000);

	for (int i = 0; i < NUM_THRUSTERS; i++)
	{
		pbot->pumps[i].pin = pump_pins[i];
		_init_pump_struct(&pbot->pumps[i]);
		_init_pump_inst(&pbot->pumps[i]);
	}

	for (int i = 0; i < NUM_THRUSTERS; i++)
	{
		pbot->thrusters[i].pin = thruster_pins[i];
		_init_thruster_struct(&pbot->thrusters[i]);
	}

	delay(500);

	for (int i = 0; i < NUM_THRUSTERS; i++)
	{
		_init_thruster_inst(&pbot->thrusters[i]);
	}
	delay(2000);
}

void send_thruster_cmd(bot_t *pbot, uint8_t whichThruster, thruster_cmd_t *pthruster_cmd)
{
	if (whichThruster > NUM_THRUSTERS - 1)
		return;
	if (pthruster_cmd->percentSpeed > 100)
		return;

	if (pthruster_cmd->percentSpeed == 0)
	{
		pbot->thrusters[whichThruster].pulseWidth = STOP_CMD;
	}
	else
	{
		if (!pthruster_cmd->direction)
		{
			pbot->thrusters[whichThruster].pulseWidth = (pthruster_cmd->percentSpeed * (float)((MAX_FWD_CMD - STOP_CMD) / 100)) + STOP_CMD;
		}
		else
		{
			pbot->thrusters[whichThruster].pulseWidth = STOP_CMD - (pthruster_cmd->percentSpeed * (float)((STOP_CMD - MAX_BWD_CMD) / 100));
		}
	}

	pbot->thrusters[whichThruster].esc.writeMicroseconds(pbot->thrusters[whichThruster].pulseWidth);
}

void send_pump_cmd(bot_t *pbot, const uint8_t whichPump, const uint8_t percentSpeed)
{
	if (whichPump > NUM_PUMPS - 1)
		return;
	if (percentSpeed > 100)
		return;

	if (percentSpeed < 2)
	{
		pbot->pumps[whichPump].dutyCycle = 0;
	}
	else
	{

#if PUMP_ALWAYSMAX

		if (percentSpeed > 0)
		{
			pbot->pumps[whichPump].dutyCycle = 255;
		}

#else

		static uint8_t tmpDutyCycle;
		tmpDutyCycle = PUMP_STALL_BASE_THRESHOLD_PWM + PWM_FACTOR * percentSpeed;

		if (tmpDutyCycle > 255)
		{
			tmpDutyCycle = 255;
		}
		pbot->pumps[whichPump].dutyCycle = tmpDutyCycle;

#endif /* PUMP_ALWAYSMAX */
	}

	analogWrite(pbot->pumps[whichPump].pin, pbot->pumps[whichPump].dutyCycle);
}
