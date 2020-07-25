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

/************************************************************************
* DEFINES *
************************************************************************/
#define PINCODE_MAIN_PERIOD         10
#define PINCODE_TIMEOUT_TIME        5  /* sec */
#define PINCODE_MAXERROR            5
#define PINCODE_ERROR_LOCK_TIME     5  /* min */

/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
unsigned int pinCode_secretCode = 1234;
unsigned char  pinCode_secretLen  = 4;

unsigned int pinCode_code = 0;
unsigned char pinCode_digit_pos, pinCode_error, pinCode_timeout, pinCode_lock, pinCode_lastDigit;

T_pinCode_state pinCode_state;

/************************************************************************
* FUNCTIONS *
************************************************************************/
unsigned char pinCode_ChangeCode(void);



/************************************************************************
 * Function: pinCode_init                                               *
 * input: none                                                          *
 * output: none                                                         *
 * return: none                                                         *
 * description: Initializes pinCode module                              *
 ***********************************************************************/
void pinCode_init(void)
{
    /* Set secret pin code */
    pinCode_secretCode = 1234;
    pinCode_secretLen  = 4;

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
 ***********************************************************************/
void pinCode_mainfunction(void)
{
    unsigned char retVal = 1;

    switch(pinCode_state)
    {
        case PINCODE_INIT:
        case PINCODE_TIMEOUT:
        {
            pinCode_code        = 0;
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
            if(pinCode_code == pinCode_secretCode)
            {
                pinCode_state = PINCODE_WAIT_CODE;
            }
            else
            {
                pinCode_error++;
                pinCode_state = PINCODE_CODE_ERROR;
            }
        }
        break;

        case PINCODE_CODE_ERROR:
        {
            if(pinCode_error > 5)
            {
                pinCode_lock += 5 * 60 * PINCODE_MAIN_PERIOD;
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
 ***********************************************************************/
unsigned char pinCode_readDigit(unsigned char digit)
{
    unsigned char retVal;

    if(digit < 10)
    {
        pinCode_code *= 10;
        pinCode_code += digit;
        pinCode_digit_pos++;
        pinCode_lastDigit = digit;
        retVal =  0;
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
 ***********************************************************************/
unsigned char pinCode_ChangeCode(void)
{
    unsigned char retVal;
    unsigned int pinCode_temp=pinCode_code;

    /* check number of digits*/
    for(int i=0; i<pinCode_digit_pos ;i++)
    {
        pinCode_temp = pinCode_temp/10;
    }

    if( (pinCode_digit_pos >= 4) && (pinCode_digit_pos <= 8) && (pinCode_temp == 0) )
    {
        /* Update new pin code*/
        pinCode_secretCode = pinCode_code;
        pinCode_secretLen  = pinCode_digit_pos;

        retVal = 0;
    }
    else
    {
        retVal = 1;
    }

    return retVal;
}


