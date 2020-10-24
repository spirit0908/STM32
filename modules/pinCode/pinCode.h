/************************************************************************
 * File Name          : pinCode.h
 * Author             : author
 * Date               : 23/02/2020
 * Description        :
 ***********************************************************************/

#ifndef PINCODE_H_
#define PINCODE_H_


/************************************************************************
* INCLUDES *
************************************************************************/


/************************************************************************
* DEFINES *
************************************************************************/


/************************************************************************
* STRUCTURES *
************************************************************************/
typedef enum
{
	PINCODE_INIT,
	PINCODE_WAIT_CODE,
	PINCODE_CHECK_CODE,
	PINCODE_CODE_OK,
	PINCODE_CODE_ERROR,
	PINCODE_CODE_LOCKED,
	PINCODE_CODE_CHANGE,
	PINCODE_REINIT,
	PINCODE_TIMEOUT
} T_pinCode_state;


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/
void pinCode_init(void);
void pinCode_mainfunction(void);
unsigned char pinCode_readDigit(unsigned char digit);
unsigned char pinCode_ChangeCode(void);
unsigned char pinCode_checkCode(unsigned char num_digit);


#endif /* TEMPLATE_HEADER_H_ */
