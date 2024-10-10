/**
 * @file main.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief
 * @version 0.1
 * @date 10-10-2024
 *
 * @copyright Copyright (c) 2024 Scott CJX
 *
 */

#include <Arduino.h>
#include <HardwareTimer.h>

#include "main.hpp"
#include "app.hpp"

bot_t bot;
thruster_cmd_t thruster_cmd;

static uint8_t req_spd;

void setup()
{
	init_bot(&bot, thruster_pins, pump_pins);
	delay(2000);

	HardwareTimer *tim_2hz = new HardwareTimer(TIM6);
	HardwareTimer *tim_10hz = new HardwareTimer(TIM7);
	HardwareTimer *tim_100hz = new HardwareTimer(TIM8);

	tim_10hz->setOverflow(10, HERTZ_FORMAT);
	tim_10hz->attachInterrupt(loop_10hz);
	tim_10hz->resume();

	tim_100hz->setOverflow(100, HERTZ_FORMAT);
	tim_100hz->attachInterrupt(loop_100hz);
	tim_100hz->resume();

	tim_2hz->setOverflow(2, HERTZ_FORMAT);
	tim_2hz->attachInterrupt(loop_2hz);
	tim_2hz->resume();

	SerialUSB.begin();
}

void loop()
{
	for (; req_spd < 90; req_spd++)
	{
		thruster_cmd.percentSpeed = req_spd;
		bot.pumpSpd = req_spd;
		delay(100);
	}

	delay(3000);

	for (; req_spd > 0; req_spd--)
	{
		thruster_cmd.percentSpeed = req_spd;
		bot.pumpSpd = req_spd;
		delay(100);
	}

	bot.heightDir = !bot.heightDir;
	thruster_cmd.direction = !thruster_cmd.direction;
	delay(2000);
}