/************************************************************************
 * File Name          : Light.h
 * Author             :
 * Date               : 12/02/2017
 * Description        : header template file
 ***********************************************************************/

#ifndef LIGHT_H
#define LIGHT_H

/************************************************************************
* INCLUDES *
************************************************************************/
#include "stm32f10x_lib.h"
#include "stm32f10x_map.h"
#include "stm32f10x_gpio.h"
    

/************************************************************************
* DEFINES *
************************************************************************/
#define LIGHT_OFF                     0x10
#define LIGHT_ON                      0x11
#define LIGHT_REVERSE                 0x12
#define LIGHT_ON_SPECIFIED_BRIGHTNESS 0x13
#define LIGHT_ON_DEFAULT_BRIGHTNESS   0x14
#define LIGHT_ON_LAST_BRIGHTNESS      0x15
#define LIGHT_BRIGHTNESS_MORE         0x16
#define LIGHT_BRIGHTNESS_LESS         0x17
#define LIGHT_ON_TIMER                0x18
#define LIGHT_ON_TIMER_ADD_30S        0x19
#define LIGHT_INHIBIT_OUTPUT          0x0A
#define LIGHT_RELEASE_OUTPUT          0x0B
#define LIGHT_INFO_REQUEST            0x0C

#define LIGHT_RGB_R                   0x20
#define LIGHT_RGB_G                   0x30
#define LIGHT_RGB_B                   0x40


/************************************************************************
* STRUCTURES *
************************************************************************/
enum
{
    Light_ID_0 = 0,
    
    // Keep this position
    Light_ID_MAX
};
    
#define MAX_LIGHT_NUM Light_ID_MAX

#define LIGHT_TYPE_ACTIVE   (0x80)
#define LIGHT_TYPE_DIMMABLE (0x40)
#define LIGHT_TYPE_TIMER    (0x20)
#define LIGHT_TYPE_RGB      (0x10)


typedef struct
{
    unsigned char active:1;
    unsigned char dimmable:1;
    unsigned char timer:1;
    unsigned char ledStrip:1;
    unsigned char RESERVED:4;
} T_LightStateType;

typedef struct
{
    GPIO_TypeDef* GPIO_Port;
    u16 GPIO_Pin;
    T_LightStateType type;
    // type of output is:
    // - bit 7: 0: output is inactive / 1: output is active
    // - bit 6: 0: output is not dimmable / 1:output is dimmable
    // - bit 5: 0: timer can not be set / 1: timer can be set
    // - bit 4-0: NA
//    unsigned char brightness_default;   // default brightness value
//    unsigned int  timer_default;        // default timer value
} T_LightConfig;


typedef struct
{
    /* Config */
    unsigned char state;                  // State/Brightness of current output: form 00 (OFF) to FF (MAX).
    unsigned char order;                  // State/Brightness of received order: form 00 (OFF) to FF (MAX).
//    unsigned char brightness_last;      // last brightness value recorded
//    unsigned int  timer_val;            // Current timer value
} T_LightState;




/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
extern T_LightConfig LightConfig[MAX_LIGHT_NUM];
extern T_LightState LightState[MAX_LIGHT_NUM];


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/
void Light_Init(void);
void Light_Init_cfg(void);
unsigned char LightOrderTmt( unsigned char LightId, unsigned char Order, unsigned char *param );
void LightSendStatus(void);
void LightSendOutputStatus(unsigned char i);


#endif  /* LIGHT_H */
