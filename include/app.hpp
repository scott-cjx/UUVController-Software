/**
 * @file app.hpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief
 * @version 0.1
 * @date 10-10-2024
 *
 * @copyright Copyright (c) 2024 Scott CJX
 *
 */

#ifndef _INCLUDE_APP
#define _INCLUDE_APP

#include <Arduino.h>
#include "bot.hpp"
#include "main.hpp"

enum botDepthDir_e
{
    BOT_GO_DOWN,
    BOT_GO_UP
};

enum thrusterDir_e
{
    THRUSTER_GO_BWD,
    THRUSTER_GO_FWD
};

typedef struct _comms_tx_t
{
	thruster_cmd_t thruster_cmds[NUM_THRUSTERS];

    /**
     * @brief bot depth rate of change
     * @ref 
     */
    uint8_t ddx_botDepth;
    botDepthDir_e botDepthCMD;

} comms_tx_t;

typedef struct _cartesian_coords_t
{
    uint8_t x;
    uint8_t y;
    uint8_t z;

} cartesian_coords_t;

typedef struct _imu_rdgs_t
{
    cartesian_coords_t accel;
    cartesian_coords_t compass;
    cartesian_coords_t magnometer;

} imu_rdgs_t;

void loop_10hz();
void loop_100hz();
void loop_2hz();

#endif /* _INCLUDE_APP */
