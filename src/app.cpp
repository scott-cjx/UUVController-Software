/**
 * @file app.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief
 * @version 0.1
 * @date 10-10-2024
 *
 * @copyright Copyright (c) 2024 Scott CJX
 *
 */

#include "app.hpp"

extern bot_t bot;
extern thruster_cmd_t thruster_cmd;

void loop_100hz()
{
	send_thruster_cmd(&bot, 0, &thruster_cmd);
	send_thruster_cmd(&bot, 1, &thruster_cmd);

	if (bot.heightDir == BOT_GO_UP)
	{
		send_pump_cmd(&bot, _PUMP_UP, bot.pumpSpd);
		send_pump_cmd(&bot, _PUMP_DN, 0);
	}
	else
	{
		send_pump_cmd(&bot, _PUMP_UP, 0);
		send_pump_cmd(&bot, _PUMP_DN, bot.pumpSpd);
	}
}

uint64_t tim_counter_10hz;

void loop_10hz()
{
	tim_counter_10hz++;
}

void loop_2hz()
{
	SerialUSB.printf("tim_counter_10hz: %u\n", tim_counter_10hz);
}
