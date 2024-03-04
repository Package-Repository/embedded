#include "usb_actions.h"

/* 
 * @brief Packages all robot actions into a jump table
 * The jump table can be edited by calling set_robot_action() to point to desired functions
 * Make sure to use enum values for editing the jump table provided from subtopic headers
 */

/* ********************************************************************************************* */
/* *********************************** Init extern variable ************************************ */

void (*robot_actions[NUM_TOPICS][NUM_SUBTOPICS])(const byte_t* data) = {0}; // From usb_actions.h

/* ********************************************************************************************* */
/* ********************************************************************************************* */


/* ********************************** *********************** ********************************** */
/* **************************** SET ROBOT ACTIONS USING PUBLIC API ***************************** */
/* ********************************** *********************** ********************************** */

void NOP(const byte_t* data) {}
void init_robot_actions(void)
{
    for (int i = 0; i < NUM_TOPICS; i++) {
        for (int j = 0; j < NUM_SUBTOPICS; j++) {
            robot_actions[i][j] = &NOP;
        }
    }
}

void set_robot_action(const byte_t topic, const byte_t subtopic, const void (*action)(const byte_t* data))
{
    robot_actions[topic][subtopic] = action;
}