/* 
 * File:   Task_cfg.h
 * Author: spirit
 *
 * Created on September 30, 2017, 3:20 PM
 */

#ifndef TASK_CFG_H
#define TASK_CFG_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "Task.h"
    
#define TASK_SCHEDULE_MAX 20

/* Timer 0 */
//20ms period
#define TIMER0_PERIOD   0x63BF
#define TIMER0_PRESCAL  0x00
#define TASK_MANAGER_IT_CYCLE 5 /*ms*/
//10ms period
//#define TIMER0_PERIOD   0xB1DF
//#define TIMER0_PRESCAL  0x00
//#define TASK_MANAGER_IT_CYCLE 10 /*ms*/
//5ms period
//#define TIMER0_PERIOD   0xD8EF
//#define TIMER0_PRESCAL  0x00
//#define TASK_MANAGER_IT_CYCLE 5 /*ms*/
//2ms period
//#define TIMER0_PERIOD   0xF05F
//#define TIMER0_PRESCAL  0x00
//#define TASK_MANAGER_IT_CYCLE 2 /*ms*/


/* Timer 1 */
//10ms period
#define TIMER1_PERIOD   0xB1DF
#define TIMER1_PRESCAL  0x00




    
extern T_TASK Task_List[];


typedef enum
{
    TASK_20ms_ID=0u,
    TASK_50ms_ID,
    TASK_100ms_ID,
    TASK_1s_ID,
    Task_CanMsgProcess_ID,
  
    // Keep the next value at the end of this enum
    TASK_TOTAL_NUM
}T_TASK_ID;

typedef enum
{
    PB_DISABLED,
    PB_IDLE,
    PB_PUSHED,
    PB_WAITING_RELEASED
}T_PushButton;

unsigned char Task_20ms(void);
unsigned char Task_50ms(void);
unsigned char Task_100ms(void);
unsigned char Task_1s(void);
unsigned char Task_CanMsgProcess(void);


#ifdef  __cplusplus
}
#endif

#endif  /* TASK_CFG_H */

