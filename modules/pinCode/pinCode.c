/************************************************************************
 * File Name          : pinCode.c
 * Author             : author
 * Date               : 28/02/2020
 * Description        :
 ***********************************************************************/


/************************************************************************
 * INCLUDES *
 ************************************************************************/
#include "stm32f10x_lib.h"
#include "stm32f10x_type.h"
#include "pinCode.h"
#include "def.h"

/************************************************************************
 * DEFINES *
 ************************************************************************/
#define PINCODE_MAIN_PERIOD         10
#define PINCODE_TIMEOUT_TIME        5  /* sec */
#define PINCODE_MAXERROR            5
#define PINCODE_ERROR_LOCK_TIME     5  /* min */
#define PINCODE_ERROR_NB_MAX        5

#define PIN_CODE_NUM_DIGIT_MAX      10
/************************************************************************
 * GLOBAL VARIABLES *
 ************************************************************************/
unsigned int pinCode_secretCode[PIN_CODE_NUM_DIGIT_MAX] = {1,2,3,4};
unsigned char  pinCode_secretLen  = 4;

unsigned int pinCode_code[PIN_CODE_NUM_DIGIT_MAX] = {0};
unsigned char pinCode_digit_pos, pinCode_error, pinCode_timeout, pinCode_lock, pinCode_lastDigit;

T_pinCode_state pinCode_state;

/************************************************************************
 * FUNCTIONS                                                            *
 ************************************************************************/


/************************************************************************
 * Function: pinCode_init                                               *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: Initializes pinCode module                              *
 ************************************************************************/
void pinCode_init(void)
{
    unsigned char i;

    /* Set secret pin code */
    for(i=0; i<10; i++)
    {
        pinCode_code[i] = 0;
    }

    pinCode_digit_pos   = 0;
    pinCode_secretLen   = 4;

    /* initialize variables */
    pinCode_error       = 0;
    pinCode_lock        = 0;

    /* Other variables initialization will be done in INIT state */
    pinCode_state = PINCODE_INIT;
}

/************************************************************************
 * Function: Function_name                                              *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: main function                                           *
 ************************************************************************/
void pinCode_mainfunction(void)
{
    unsigned char i;

    switch(pinCode_state)
    {
        case PINCODE_INIT:
        case PINCODE_TIMEOUT:
        {
            for(i=0; i<10; i++)
            {
                pinCode_code[i] = 0;
            }

            pinCode_digit_pos   = 0;
            pinCode_timeout     = 0;
            pinCode_lastDigit   = 0;
            pinCode_state       = PINCODE_WAIT_CODE;
        }
        break;

        case PINCODE_WAIT_CODE:
        {
            if(pinCode_digit_pos >= pinCode_secretLen)
            {
                pinCode_state = PINCODE_CHECK_CODE;
            }

            if(pinCode_timeout++ > ( 1*PINCODE_MAIN_PERIOD ) )
            {
                pinCode_state = PINCODE_TIMEOUT;
            }
        }
        break;

        case PINCODE_CHECK_CODE:
        {
            if( pinCode_checkCode(pinCode_digit_pos) == RET_OK )
            {
                pinCode_state = PINCODE_WAIT_CODE;
            }
            else
            {
                pinCode_state = PINCODE_CODE_ERROR;
            }
        }
        break;

        case PINCODE_CODE_ERROR:
        {
            pinCode_error++;

            if(pinCode_error >= PINCODE_ERROR_NB_MAX)
            {
                pinCode_lock += PINCODE_ERROR_NB_MAX * 60 * PINCODE_MAIN_PERIOD;
                pinCode_state = PINCODE_CODE_LOCKED;
            }
            else
            {
                pinCode_state = PINCODE_REINIT;
            }
        }
        break;

        case PINCODE_CODE_LOCKED:
        {
            pinCode_lock--;
            if(pinCode_lock == 0)
            {
                pinCode_state = PINCODE_REINIT;
            }
        }
        break;

        case PINCODE_CODE_OK:
        {
            /* code OK, callback call*/
        }
        break;

        case PINCODE_CODE_CHANGE:
        {
            if(pinCode_lastDigit == 0xFF)
            {
                pinCode_ChangeCode();
                pinCode_state = PINCODE_REINIT;
            }
        }
        break;

        default:
            pinCode_state = PINCODE_INIT;
        break;
    }
}

/************************************************************************
 * Function: Function_name                                              *
 * input: digit - input digit given on keypad                           *
 * output: none                                                         *
 * return: status of the function                                       *
 * description: Adds one digit to the staged code                       *
 ************************************************************************/
unsigned char pinCode_readDigit(unsigned char digit)
{
    unsigned char retVal;

    if(digit < PIN_CODE_NUM_DIGIT_MAX)
    {
        pinCode_code[pinCode_digit_pos++] = digit;
        pinCode_lastDigit = digit;
        retVal = 0;
    }
    else
    {
        retVal = 1;
    }

    return retVal;
}

/************************************************************************
 * Function: Function_name                                              *
 * input: none                                                          *
 * output: none                                                         *
 * return: status of the function                                       *
 * description: replaces the current code by the staged code            *
 ************************************************************************/
unsigned char pinCode_ChangeCode(void)
{
    unsigned char retVal;

    /* check number of digits*/
    
    if( (pinCode_digit_pos >= 4) && (pinCode_digit_pos <= 8) )
    {
        /* Update new pin code*/
        for(int i=0; i<pinCode_digit_pos ;i++)
        {
            pinCode_secretCode[i] = pinCode_code[i];
        }
        pinCode_secretLen  = pinCode_digit_pos;

        retVal = 0;
    }
    else
    {
        retVal = 1;
    }

    return retVal;
}


/************************************************************************
 * Function: Function_name                                              *
 * input: none                                                          *
 * output: none                                                         *
 * return: status of the function                                       *
 * description: replaces the current code by the staged code            *
 ************************************************************************/
unsigned char pinCode_checkCode(unsigned char num_digit)
{
    unsigned char retVal = RET_NOT_OK;
    /*unsigned int i;*/

    /* Check number of digits*/
    for(int i=0; i<PIN_CODE_NUM_DIGIT_MAX; i++)
    {
        if( pinCode_code[i] != pinCode_secretCode[i] )
        {
            retVal = RET_NOT_OK;
            break;
        }

        if(num_digit >= pinCode_secretLen)
        {
            retVal = RET_OK;
            break;
        }
    }

    return retVal;
}
