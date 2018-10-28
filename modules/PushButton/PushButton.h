/* 
 * File:   PushButton.h
 * Author:
 *
 * Created on 12 fevrier 2017, 21:50
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum
{
    PB_DISABLED,
    PB_IDLE,
    PB_PUSHED,
    PB_SHORT_PUSH,
	PB_LONG_PUSH,
	PB_CONFIG_PUSH
}T_PushButton;

typedef struct
{
//  unsigned char Name[10];
    GPIO_TypeDef* GPIO_Port;
    u16 GPIO_Pin;
    unsigned char (*SP_action)();
    unsigned char (*LP_action)();
    unsigned char (*CP_action)();
    unsigned char curState;
    unsigned char push_cpt;
}PB_Config_T;

#define NULL 0
#define LONG_PUSH_TIME      2 /*sec*/
#define CONFIG_PUSH_TIME    8/*sec*/
#define PB_READ_PERIOD      100 /*ms*/
#define LONG_PUSH_CPT       (LONG_PUSH_TIME*1000/PB_READ_PERIOD)
#define CONFIG_PUSH_CPT     (CONFIG_PUSH_TIME*1000/PB_READ_PERIOD)
#define PB_CONFIG_NB        4


unsigned char PushButton_Mgt(void);

#ifdef  __cplusplus
}
#endif

#endif  /* TASK_H */

