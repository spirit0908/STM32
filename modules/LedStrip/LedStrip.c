/************************************************************************
 * File Name          : LedStrip.c
 * Author             :
 * Date               : 17/10/2018
 * Description        :
 ***********************************************************************/

/************************************************************************
* INCLUDES *
************************************************************************/
#include "stm32f10x_lib.h"
#include "stm32f10x_map.h"
#include "stm32f10x_gpio.h"
#include "LedStrip.h"

/************************************************************************
* DEFINES *
************************************************************************/
#define PERIOD 1000

typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
} T_LedStrip ;
T_LedStrip LedStrip;

/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
extern int TIM_Pulse_R;
extern int TIM_Pulse_G;
extern int TIM_Pulse_B;

#define INC_PERIOD  10

#define LEDSTRIP_INC_TIME       3 /*s*/
#define LEDSTRIP_MGT_PERIOD     100 /*ms*/
#define LEDSTRIP_CPT_MAX        LEDSTRIP_INC_TIME*1000/LEDSTRIP_MGT_PERIOD

unsigned char LedStripMgt_cpt=0;


/************************************************************************
* FUNCTIONS *
************************************************************************/

/************************************************************************
 * Function: LedStrip_Mgt                                               *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: LedStrip module main function                           *
 ***********************************************************************/
void LedStrip_Mgt(void)
{
    //unsigned char inc;
    //inc = (LedStrip.R*4-TIM_Pulse_R)/(LEDSTRIP_CPT_MAX-LedStripMgt_cpt);


    if( TIM_Pulse_R < (LedStrip.R*4) )
    {
        if( (TIM_Pulse_R+INC_PERIOD) < (LedStrip.R*4))
            TIM_Pulse_R +=INC_PERIOD ;
        else
            TIM_Pulse_R = (LedStrip.R*4);

        //Update TIM3
        TIM3->CCR1 = TIM_Pulse_R;
    }
    else if ( TIM_Pulse_R > (LedStrip.R*4) )
    {
        if( TIM_Pulse_R > INC_PERIOD)
            TIM_Pulse_R -=INC_PERIOD;
        else
            TIM_Pulse_R=0;

        //Update TIM3
        TIM3->CCR1 = TIM_Pulse_R;
    }


    if( TIM_Pulse_G < (LedStrip.G*4) )
    {
        if( (TIM_Pulse_G+INC_PERIOD) < (LedStrip.G*4))
            TIM_Pulse_G +=INC_PERIOD;
        else
            TIM_Pulse_G = (LedStrip.G*4);

        //Update TIM3
        TIM3->CCR2 = TIM_Pulse_G;
    }
    else if( TIM_Pulse_G > (LedStrip.G*4) )
    {
        if( TIM_Pulse_G > INC_PERIOD)
            TIM_Pulse_G -=INC_PERIOD;
        else
            TIM_Pulse_G=0;

        //Update TIM3
        TIM3->CCR2 = TIM_Pulse_G;
    }


    if( TIM_Pulse_B < (LedStrip.B*4) )
    {
        if( (TIM_Pulse_B+INC_PERIOD) < (LedStrip.B*4))
            TIM_Pulse_B +=INC_PERIOD;
        else
            TIM_Pulse_B = (LedStrip.B*4);

        //Update TIM3
        TIM3->CCR3 = TIM_Pulse_B;
    }
    else if( TIM_Pulse_B > (LedStrip.B*4) )
    {
        if( TIM_Pulse_B > INC_PERIOD)
            TIM_Pulse_B -=INC_PERIOD;
        else
            TIM_Pulse_B=0;

        //Update TIM3
        TIM3->CCR3 = TIM_Pulse_B;
    }


    if( LedStripMgt_cpt++ > LEDSTRIP_CPT_MAX )
    {
        LedStripMgt_cpt = 0;
    }
}

