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
//#include "stm32f10x_lib.h"
//#include "stm32f10x_map.h"
//#include "stm32f10x_gpio.h"
#include "stm32f103xb.h"
    

/************************************************************************
* MACROS *
************************************************************************/
/* Order */
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

/*  */
#define LIGHT_RGB_R                   0x20
#define LIGHT_RGB_G                   0x30
#define LIGHT_RGB_B                   0x40

/* Error values */
#define LIGHT_E_OK                    0x00
#define LIGHT_E_NOK                   0x01
#define LIGHT_E_INVALID_LIGHTID       0x02
#define LIGHT_E_INVALID_ORDER         0x03

/* Light type */
#define LIGHT_TYPE_ACTIVE             0x80
#define LIGHT_TYPE_DIMMABLE           0x40
#define LIGHT_TYPE_TIMER              0x20
#define LIGHT_TYPE_RGB                0x10
#define LIGHT_TYPE_INVERTED           0x08

enum
{
    Light_ID_0 = 0,
    Light_ID_1,
    Light_ID_2,
    // Keep this position
    Light_ID_MAX
};
#define MAX_LIGHT_NUM Light_ID_MAX

#define IS_LIGHT_TYPE_ACTIVE(a)   \
  (a & LIGHT_TYPE_ACTIVE)
#define IS_LIGHT_TYPE_DIMMABLE(a) \
  (a & LIGHT_TYPE_DIMMABLE)
#define IS_LIGHT_TYPE_TIMER(a)    \
  (a & LIGHT_TYPE_TIMER)
#define IS_LIGHT_TYPE_RGB(a)      \
  (a & LIGHT_TYPE_RGB)
#define IS_LIGHT_TYPE_INVERTED(a) \
  (a & LIGHT_TYPE_INVERTED)


/************************************************************************
* STRUCTURES *
************************************************************************/
/*typedef struct
{
    unsigned char active:1;
    unsigned char dimmable:1;
    unsigned char timer:1;
    unsigned char ledStrip:1;
    unsigned char invertedTor:1;
    unsigned char RESERVED:3;
} T_LightStateType;*/

typedef struct
{
    GPIO_TypeDef* GPIO_Port;
    unsigned int GPIO_Pin;
    unsigned char type; //T_LightStateType type;
    /* type of output is:
     * - bit 7: 0: output is inactive / 1: output is active
     * - bit 6: 0: output is not dimmable / 1:output is dimmable
     * - bit 5: 0: timer can not be set / 1: timer can be set
     * - bit 4: 0: ledStrip not used / 1: ledstrip used
     * - bit 3: 0: contact is NO / 1: contact is NC
     * - bit 2-0: NA
     */
    unsigned char brightness_default;   // default brightness value
    unsigned int  timer_default;        // default timer value
} T_LightConfig;


typedef struct
{
    unsigned char state;                // State/Brightness of current output: form 00 (OFF) to FF (MAX).
    unsigned char order;                // State/Brightness of received order: form 00 (OFF) to FF (MAX).
    unsigned char brightness_last;      // last brightness value recorded
    unsigned int  timer_val;            // Current timer value
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
unsigned char LightOrderTmt( unsigned char LightId, unsigned char Order, unsigned int value );
void LightSendStatus(void);
void LightSendOutputStatus(unsigned char i);

unsigned char Light_order_LightOff(unsigned char LightId);
unsigned char Light_order_LightOn(unsigned char LightId);
unsigned char Light_order_LightReverseState(unsigned char LightId);

unsigned char LightOutputReset(unsigned char LightId);
unsigned char LightOutputSet(unsigned char LightId);
unsigned char LightOutputMan(void);
#endif  /* LIGHT_H */
