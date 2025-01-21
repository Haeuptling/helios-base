// -*-c++-*-

/*!
  \file positioning.cpp
  \brief positioning action object Source File.
*/

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *EndCopyright:
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "positioning.h"

#include <rcsc/common/server_param.h>
#include <rcsc/math_util.h>

namespace rcsc {

/*-------------------------------------------------------------------*/
/*!
 * \brief Constructor
 */
Positioning::Positioning( const int unum,
                          const rcsc::Vector2D & target_point,
                          const int duration_step,
                          const char * description )
    : CooperativeAction( CooperativeAction::Move,
                         unum,
                         target_point,
                         duration_step,
                         description )
{
    // Calculate optimal position
    rcsc::Vector2D optimal_position = calculateOptimalPosition(unum);
    setTargetPoint(optimal_position);
}

/*-------------------------------------------------------------------*/
/*!
 * \brief Calculate the optimal position for the player
 */
rcsc::Vector2D Positioning::calculateOptimalPosition(const int unum)
{
    const WorldModel & wm = WorldModel::instance();
    const rcsc::Vector2D ball_pos = wm.ball().pos();
    const rcsc::Vector2D goal_pos = rcsc::Vector2D(ServerParam::i().pitchHalfLength(), 0.0);
    const rcsc::Vector2D self_pos = wm.self().pos();

    // Example logic: Position the player dynamically based on the ball and goal positions
    rcsc::Vector2D optimal_position;

    if (wm.self().unum() == unum) {
        // If the player is close to the ball, move towards the goal
        if (self_pos.dist(ball_pos) < 10.0) {
            optimal_position = (ball_pos + goal_pos) * 0.5;
        }
        // If the player is far from the ball, move to a strategic position
        else {
            optimal_position = ball_pos + rcsc::Vector2D(5.0, 0.0);
        }
    } else {
        // Default positioning logic for other players
        optimal_position = target_point;
    }

    return optimal_position;
}

}