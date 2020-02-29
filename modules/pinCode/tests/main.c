#include <stdio.h>


/************************************************
 *
 *
 *************************************************/


/*******************************************************/

extern unsigned int pinCode_secretCode, pinCode_code;
extern unsigned char pinCode_lastDigit, pinCode_digit_pos;
extern unsigned char pinCode_secretLen;

unsigned int assert_error;
unsigned char assert_testName[100];

void assert_init(unsigned char testName[100], unsigned char testCaseNum)
{
  assert_error=0;
  printf("Executing test: %s__%d... \t", testName, testCaseNum);
  for(int i=0; i<100; i++)
  {
    assert_testName[i] = testName[i];
  }
}

void assert_end(void)
{
  if( assert_error == 0)
  {
    printf("- TEST PASSED!\n", assert_testName );
  }
  else
  {
    printf("\n %s - TEST FAILED: %d errors\n", assert_testName, assert_error);
  }
}

void assert(unsigned char expr, unsigned char errorDescr[100])
{
 if(!expr)
 {
   assert_error++;
   printf("\nERROR: %s", errorDescr);
 }
}
/********************************************************/

typedef struct
{
    unsigned char digits[10];
    unsigned int pinCodes[10];
    unsigned char digitNum;
} T_test_readDigit_seq;


unsigned char TEST_pinCode_readDigit(void)
{
	T_test_readDigit_seq test_readDigit_seq[] =
    {
        { {1, 2,  3, 4, 0, 0, 0, 0, 0, 0}, {1, 12, 123, 1234,     0, 0, 0, 0, 0}, 4 },
		{ {0, 0,  0, 0, 0, 0, 0, 0, 0, 0}, {0, 00, 000, 0000,     0, 0, 0, 0, 0}, 4 },
		{ {4, 3,  2, 1, 0, 0, 0, 0, 0, 0}, {4, 43, 432, 4321,     0, 0, 0, 0, 0}, 4 },

		{ {1, 2,  3, 4, 0, 0, 0, 0, 0, 0}, {1,  1,   1,    1,     0, 0, 0, 0, 0}, 1 },
		{ {1, 1,  1, 1, 1, 1, 1, 1, 1, 1}, {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111}, 10 },


        { {0, 0,  0, 0, 0, 0, 0, 0, 0, 0}, {0,  0,   0,    0,     0, 0, 0, 0, 0}, 8 },
        { {9, 9,  9, 9, 9, 0, 0, 0, 0, 0}, {9, 99, 999, 9999, 99999, 0, 0, 0, 0}, 5 },
        { {5, 5, 55, 5, 5, 0, 0, 0, 0, 0}, {5, 55,  55,  555,  5555, 0, 0, 0, 0}, 4 },

		{ {0xA, 0xA, 0xA, 0xA, 0, 0, 0, 0, 0, 0}, {0, 0,  0,  0, 0, 0, 0, 0, 0}, 4 },
    };

	unsigned char TEST_READDIGIT_SEQ_SIZE = (sizeof(test_readDigit_seq)/sizeof(T_test_readDigit_seq));

	for(int i=0; i<TEST_READDIGIT_SEQ_SIZE ;i++)
	{
        assert_init("TEST_pinCode_readDigit", i);

        /* Initialize code variables */
        pinCode_code = 0;
        pinCode_lastDigit = 0;
        pinCode_digit_pos = 0;

        unsigned char f_ret, digit_cpt=0;

        for(int j=0; j<test_readDigit_seq[i].digitNum; j++ )
        {
          /* Call function */
          f_ret = pinCode_readDigit(test_readDigit_seq[i].digits[j]);
          if(f_ret == 0)
          {
        	  digit_cpt++;
              assert(pinCode_lastDigit == test_readDigit_seq[i].digits[j], "wrong last digit\n");
          }
          assert(pinCode_code == test_readDigit_seq[i].pinCodes[j], "wrong pin code\n");
          assert(pinCode_digit_pos == digit_cpt, "wrong digit number\n");
        }

        assert_end();
    }

}

typedef struct
{
    unsigned int code;
    unsigned char codeLen;
    unsigned int secredCode;
    unsigned char secretLen;
    unsigned char retval;
} T_test_changeCode_seq;

unsigned char TEST_pinCode_ChangeCode(void)
{
	T_test_changeCode_seq test_changeCode_seq[] =
    {
        {   1234,  4, 1234, 4, 0 },
		{     00,  2, 1234, 4, 1 },
		{      0, 10, 1234, 4, 1 },
		{   0000,  4, 0000, 4, 0 },
        {  54321, 5, 54321, 5, 0 },
        { 563412, 6, 563412, 6, 0 },
		{ 99999999, 8, 99999999, 8, 0 },
		{ 563412, 5, 99999999, 8, 1 },
    };

	unsigned char TEST_CHANGECODE_SEQ_SIZE = (sizeof(test_changeCode_seq)/sizeof(T_test_changeCode_seq));

    /* Initialize code variables */
    pinCode_secretCode = 1234;
    pinCode_secretLen  = 4;
    pinCode_code = 0;
    pinCode_digit_pos=0;
    pinCode_lastDigit=0;

	for(int i=0; i<TEST_CHANGECODE_SEQ_SIZE ;i++)
	{
        unsigned char f_ret;

		assert_init("pinCode_ChangeCode", i);

		pinCode_code = test_changeCode_seq[i].code;
		pinCode_digit_pos = test_changeCode_seq[i].codeLen;

		/* Call function */
		f_ret = pinCode_ChangeCode();

		assert(pinCode_secretCode == test_changeCode_seq[i].secredCode, "wrong code");
		assert(pinCode_secretLen == test_changeCode_seq[i].secretLen, "wrong codeLen");
		assert(f_ret == test_changeCode_seq[i].retval, "wrong return value");

		assert_end();
    }

}



/********************************************************/
int main(void)
{
  unsigned char digit=0;
  unsigned char ret=1;


  TEST_pinCode_readDigit();

  TEST_pinCode_ChangeCode();

  return 0;

}



