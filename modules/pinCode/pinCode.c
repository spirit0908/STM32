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

#define PINCODE_CODE_LENGTH_MIN     4
#define PINCODE_CODE_LENGTH_MAX     10

/* Numbe of User codes */
#define PINCODE_USER_PIN_NUM        1

#define PINCODE_PIN_MASTER          0
#define PINCODE_PIN_USER            1
#define PINCODE_PIN_ERROR           2
#define PINCODE_PIN_CONTINUE_TRY    3


#define PINCODE_DEFAULT_MASTER_CODE  \
  {                                  \
    {1, 2, 3, 4, 5, 6, 0, 0, 0, 0},  \
    6,                               \
    PINCODE_PIN_MASTER               \
  }

#define PINCODE_DEFAULT_USER_CODE    \
  {                                  \
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  \
    4,                               \
    PINCODE_PIN_USER                 \
  }

/************************************************************************
 * GLOBAL VARIABLES *
 ************************************************************************/
T_pinCode pinCode_secretCode[1+PINCODE_USER_PIN_NUM];

unsigned char pinCode_code[PINCODE_CODE_LENGTH_MAX] = {0};
unsigned char pinCode_digit_pos, pinCode_error, pinCode_timeout, pinCode_lock, pinCode_lastDigit;

T_pinCode_state pinCode_state;

// T_pinCode PinCode_default_masterCode = PINCODE_DEFAULT_MASTER_CODE;
T_pinCode PinCode_default_masterCode = { {1, 2, 3, 4, 5, 6, 0, 0, 0, 0}, 6, PINCODE_PIN_MASTER };
#if (PINCODE_USER_PIN_NUM > 0)
T_pinCode PinCode_default_userCode[PINCODE_USER_PIN_NUM]   = PINCODE_DEFAULT_USER_CODE;
#endif

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
    
  /* Initialize variables */
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
      for(i=0; i<(PINCODE_USER_PIN_NUM+1) ; i++)
      {
        if(pinCode_digit_pos >= pinCode_secretCode[i].len)
        {
          pinCode_state = PINCODE_CHECK_CODE;
        }
      }

      if(pinCode_timeout++ > ( 1*PINCODE_MAIN_PERIOD ) )
      {
        pinCode_state = PINCODE_TIMEOUT;
      }
    }
    break;

    case PINCODE_CHECK_CODE:
    {
      unsigned char codeStatus = pinCode_checkCode(pinCode_digit_pos);

      switch(codeStatus)
      {
        case PINCODE_PIN_MASTER:
          pinCode_state = PINCODE_CODE_OK_MASTER;
          break;

        case PINCODE_PIN_USER:
          pinCode_state = PINCODE_CODE_OK_USER;
          break;

        case PINCODE_PIN_ERROR:
          pinCode_state = PINCODE_CODE_ERROR;
          break;
                
        case PINCODE_PIN_CONTINUE_TRY:
          pinCode_state = PINCODE_WAIT_CODE;
          break;

        default:
          pinCode_state = PINCODE_CODE_ERROR;
        break;
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

    case PINCODE_CODE_OK_MASTER:
    {
      /* code OK, callback call*/
    }
    break;

    case PINCODE_CODE_OK_USER:
    {
      /* code OK, callback call*/
    }
    break;

    case PINCODE_CODE_CHANGE:
    {
      if(pinCode_lastDigit == 0xFF)
      {
        // pinCode_ChangeCode(pinCode_code, pinCode_digit_pos+1);
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

  if(digit < 10)
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
 * Function: PinCode_setCode                                            *
 * input: none                                                          *
 * output: none                                                         *
 * return: status of the function                                       *
 * description: Initializes default master and users code               *
 ************************************************************************/
unsigned char pinCode_SetDefaultCode(void)
{
  unsigned char retVal, i;

  for(i=0; i<PinCode_default_masterCode.len; i++)
    pinCode_secretCode[0].pin[i] = PinCode_default_masterCode.pin[i];
  
  pinCode_secretCode[0].len = PinCode_default_masterCode.len;
  pinCode_secretCode[0].masterUser = PinCode_default_masterCode.masterUser;

#if (PINCODE_USER_PIN_NUM > 0)
  for(i=0; i<PINCODE_USER_PIN_NUM; i++)
  {
    for(int j=0; j<PinCode_default_userCode[i].len; j++)
      pinCode_secretCode[i+1].pin[j] = PinCode_default_userCode[i].pin[j];
    pinCode_secretCode[i+1].len = PinCode_default_userCode[i].len;
    pinCode_secretCode[i+1].masterUser = PinCode_default_userCode[i].masterUser;
  }
#endif

  return retVal;
}

/************************************************************************
 * Function: Function_name                                              *
 * input: none                                                          *
 * output: none                                                         *
 * return: status of the function                                       *
 * description: replaces the current code by the staged code            *
 ************************************************************************/
unsigned char pinCode_ChangeCode(unsigned char *oldCodePtr, unsigned char oldCodeLen, unsigned char * newcodePtr, unsigned char newCodeLen)
{
  unsigned char retVal, found, codeIndex=255;
  int i;
  
  /* check number of digits*/
  
  /* search code */
  for(i=0; i<(PINCODE_USER_PIN_NUM+1) ;i++)
  {
    found = 1;
    for(int j=0; j<oldCodeLen; j++)
    {
      if( pinCode_secretCode[i].pin[j] = oldCodePtr[j] )
      {
        found = 0;
        break;
      }
    }

    if(found ==1 )
    {
      codeIndex = i;
      break;
    }
  }

  if( (newCodeLen >= PINCODE_CODE_LENGTH_MIN) && (newCodeLen <= PINCODE_CODE_LENGTH_MAX) )
  {
    /* Update new pin code*/
    if(codeIndex <= (PINCODE_USER_PIN_NUM+1) )
    {
      for(i=0; i<newCodeLen; i++ )
      {
        pinCode_secretCode[codeIndex].pin[i] = newcodePtr[i];
      }
      pinCode_secretCode[codeIndex].len = newCodeLen;
      retVal = 0;
    }
  }
  else
  {
    /* Incorrect code length */
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
  unsigned char retVal = PINCODE_CODE_ERROR;
  unsigned char retry = 0;
  /*unsigned int i;*/

  /* Compare all codes */
  for(int i=0; i<(PINCODE_USER_PIN_NUM+1); i++)
  {
    if( pinCode_secretCode[i].len == num_digit )
    {
      /* Check number of digits */
      for(int j=0; j<PINCODE_CODE_LENGTH_MAX; j++)
      {
        if( pinCode_code[j] != (pinCode_secretCode[i].pin[j]) )
        {
          if(i == 0)
          {
            retVal = PINCODE_CODE_OK_MASTER;
          }
          else
          {
            retVal = PINCODE_CODE_OK_USER;
          }
          break;
        }
      }
    }
    else if( pinCode_secretCode[i].len < num_digit )
    {
      /* missing digits */
      retry = 1;
    }
    else
    {
      /* wrong code, do nothing */
    }
  }

  if( (retVal == PINCODE_CODE_ERROR) && (retry = 1 ) )
  {
    retVal = PINCODE_PIN_CONTINUE_TRY;
  }

  return retVal;
}
