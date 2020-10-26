#include <stdio.h>
#include <pinCode.h>


typedef struct
{
  unsigned char functionName[40];
  int (*pf)(void);
  unsigned char run;
} T_testFunction;


/* Test function prototype (test_main.h) */
int TEST_pinCode_init(void);
int TEST_pinCode_readDigit(void);
int TEST_pinCode_ChangeCode(void);

/* Test configuration (test_cfg.c) */
unsigned char TEST_module[50] = "pinCode";

T_testFunction test_list_config[]=
{
  /* Unit tests*/
  {"pinCode_init", TEST_pinCode_init, 1},
  {"pinCode_readDigit", TEST_pinCode_readDigit, 1},
  {"pinCode_ChangeCode", TEST_pinCode_ChangeCode, 1}

  /* Integration tests */
/*  {"Integration test: TeleInfo_Integration", TEST_TeleInfo_Integration}, */
};


/* Test variables declaration (test_cfg.h) */
extern unsigned int pinCode_secretCode[];
extern unsigned int pinCode_code[];
extern unsigned char pinCode_error, pinCode_lock, pinCode_state;

extern unsigned char pinCode_lastDigit, pinCode_digit_pos;
extern unsigned char pinCode_secretLen;


#define TEST_LIST_CONFIG_SIZE ((unsigned int)(sizeof(test_list_config)/sizeof(T_testFunction)))

/* Test (test.h)*/
#define TST_RET_OK    0
#define TST_RET_N_OK  1
unsigned int errorNum;

/* Test (test.c)*/
int testStringFill(int *strPtr, int *string)
{
  unsigned char strSize = sizeof(string);
  unsigned char i;

  for(i=0; i<strSize; i++)
  {
    strPtr[i] = string[i];
  }
  return 0;
}

void assert(int check, char *str)
{
  if(check == 0)
  {
    printf("  Error: %s\n", str);
    errorNum++;
  }
}

void assert_cmp(unsigned int val1, unsigned int val2, char *str)
{
  if(val1 != val2)
  {
    printf("  Error: %s (%d!=%d)\n", str, val1, val2);
    errorNum++;
  }
}

void TEST_init(void)
{
  errorNum=0;
}

unsigned int TEST_finish(void)
{
  return errorNum;
}

unsigned char tst_cmp(unsigned char *a, unsigned char *b, unsigned char len)
{
  for(unsigned char i=0; i<len; i++)
  {
    if(*a++ != *b++)
    {
      assert(0, "cmp fail\n");
      return TST_RET_N_OK;
    }
  }
  return TST_RET_OK;
}

unsigned char tst_set(unsigned char *a, unsigned char *b, unsigned char len)
{
  for(unsigned char i=0; i<len; i++)
  {
    *a = *b;
    a++;
    b++;
  }
  return TST_RET_OK;
}


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
    printf("%s- TEST PASSED!\n", assert_testName );
  }
  else
  {
    printf("\n %s - TEST FAILED: %d errors\n", assert_testName, assert_error);
  }
}

/********************************************************/

typedef struct
{
    unsigned char digits[10];
    unsigned long pinCodes[10];
    unsigned char digitNum;
} T_test_readDigit_seq;


int TEST_pinCode_init(void)
{
  /*int result=-1;*/
  int i;
  TEST_init();

  /* Init */
  pinCode_init();


  /* Set secret pin code */
  for(i=0; i<10; i++)
  {
    assert(pinCode_code[i] == 0, "Invalid init secret");
  }
  
  assert(pinCode_secretLen == 4, "Invalid secretLen");
  
  /* initialize variables */
  assert(pinCode_error == 0, "Invalid init value error");
  assert(pinCode_lock  == 0, "Invalid init value lock");


  /* Other variables initialization will be done in INIT state */
  assert(pinCode_state == PINCODE_INIT, "Invalid init pin state");
  
  return TEST_finish();
}



int TEST_pinCode_readDigit(void)
{
  T_test_readDigit_seq test_readDigit_seq[] =
  {
    { {1, 2,  3, 4, 0, 0, 0, 0, 0, 0}, {1, 12, 123, 1234,     0, 0, 0, 0, 0}, 4 },
    { {0, 0,  0, 0, 0, 0, 0, 0, 0, 0}, {0, 00, 000, 0000,     0, 0, 0, 0, 0}, 4 },
    { {4, 3,  2, 1, 0, 0, 0, 0, 0, 0}, {4, 43, 432, 4321,     0, 0, 0, 0, 0}, 4 },

    { {1, 2,  3, 4, 0, 0, 0, 0, 0, 0}, {1,  1,   1,    1,     0, 0, 0, 0, 0}, 1 },
    { {1, 1,  1, 1, 1, 1, 1, 1, 1, 1}, {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111}, 10 },
    { {9, 9,  9, 9, 9, 9, 9, 9, 9, 9}, {9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, 9999999999}, 10 },
    { {0, 0,  0, 0, 0, 0, 0, 0, 0, 0}, {0,  0,   0,    0,     0,      0,       0,        0,         0,          0}, 10 },
    
    { {0, 0,  0, 0, 0, 0, 0, 0, 0, 0}, {0,  0,   0,    0,     0, 0, 0, 0, 0}, 8 },
    { {9, 9,  9, 9, 9, 0, 0, 0, 0, 0}, {9, 99, 999, 9999, 99999, 0, 0, 0, 0}, 5 },
    { {5, 5, 55, 5, 5, 0, 0, 0, 0, 0}, {5, 55,  55,  555,  5555, 0, 0, 0, 0}, 4 },

    { {0xA, 0xA, 0xA, 0xA, 0, 0, 0, 0, 0, 0}, {0, 0,  0,  0, 0, 0, 0, 0, 0}, 4 },
    
  };

  unsigned char TEST_READDIGIT_SEQ_SIZE = (sizeof(test_readDigit_seq)/sizeof(T_test_readDigit_seq));
  unsigned long tmpCode;

  /*int result=-1;*/
  /*int i;*/
  unsigned char f_ret, digit_cpt=0;


  TEST_init();



  for(int i=0; i<TEST_READDIGIT_SEQ_SIZE ;i++)
  {
    digit_cpt=0;

    //assert_init("TEST_pinCode_readDigit", i);
    //printf("sequence: %i\n", i);
    /* Initialize code variables */
    pinCode_init();

    for(int j=0; j<test_readDigit_seq[i].digitNum; j++ )
    {
      /* Call function */
      f_ret = pinCode_readDigit(test_readDigit_seq[i].digits[j]);
      //printf("return=%i\n", f_ret);

      if(f_ret == 0)
      {
        digit_cpt++;
        assert(pinCode_lastDigit == test_readDigit_seq[i].digits[j], "wrong last digit\n");
      }
 
      tmpCode=0;
      for(int k=0; k<digit_cpt; k++)
      {
        tmpCode *= 10;
        tmpCode += pinCode_code[k];
        //printf("pinCode=%i\n", tmpCode);
      }
      assert(tmpCode == test_readDigit_seq[i].pinCodes[j], "wrong pin code\n");

      //printf("pinCode_digit_pos=%i %i\n", pinCode_digit_pos, digit_cpt);
      assert(pinCode_digit_pos == digit_cpt, "wrong digit number\n");
    }

    //assert_end();
  }

  return TEST_finish();
}



typedef struct
{
    unsigned long newCode;
    unsigned char newCodeLen;
    unsigned long secretCode;
    unsigned char secretLen;
    unsigned char retval;
} T_test_changeCode_seq;

int TEST_pinCode_ChangeCode(void)
{
  T_test_changeCode_seq test_changeCode_seq[] =
  {
    {     1234,  4, 1234,     4, 0 },
    {       00,  2, 1234,     4, 1 },
    {        0, 10, 1234,     4, 1 },
    {     0000,  4, 0000,     4, 0 },
    {    54321,  5, 54321,    5, 0 },
    {   563412,  6, 563412,   6, 0 },
    { 99999999,  8, 99999999, 8, 0 },
    { 9999999999,  10, 9999999999, 8, 0 },
    { 1029384756,  10, 1029384756, 8, 0 },
    { 11111111111, 11, 1029384756, 8, 0 },
  };

  unsigned char TEST_CHANGECODE_SEQ_SIZE = (sizeof(test_changeCode_seq)/sizeof(T_test_changeCode_seq));
  unsigned long tmp_code;
  /*int result=-1;*/

  TEST_init();

  /* Initialize code variables */
  pinCode_init();

  for(int i=0; i<TEST_CHANGECODE_SEQ_SIZE ;i++)
  {
    unsigned char f_ret;
    unsigned char local_newCodeLen = test_changeCode_seq[i].newCodeLen;
    unsigned char pinPos;

    for(int j=0; j<local_newCodeLen; j++)
    {
      pinPos = local_newCodeLen-j-1;
      pinCode_code[pinPos] = (test_changeCode_seq[i].newCode)%10;
      test_changeCode_seq[i].newCode /= 10;
      printf("  pinCode_code[%d]: %d", pinPos, pinCode_code[pinPos]);
    }
    pinCode_digit_pos = test_changeCode_seq[i].newCodeLen;

    /* Call function */
    f_ret = pinCode_ChangeCode();

    /* check new secretCode */
    tmp_code=0;
    for(int j=0; j<test_changeCode_seq[i].secretLen; j++)
    {
      tmp_code *= 10;
      tmp_code += pinCode_secretCode[j];
    }
    printf("  tmp_code=%li (%i)\n", tmp_code, test_changeCode_seq[i].secretCode);
    assert(tmp_code == test_changeCode_seq[i].secretCode, "wrong code");
    assert(pinCode_secretLen == test_changeCode_seq[i].secretLen, "wrong codeLen");
    assert(f_ret == test_changeCode_seq[i].retval, "wrong return value");
  }

  return TEST_finish();
}



/********************************************************/







/************************************************
 *
 *   MAIN TESTS
 *
 *************************************************/
int main(void)
{
  int ret[TEST_LIST_CONFIG_SIZE];
  unsigned int test_passed=0, test_failed=0, test_notrun=0;
  
  printf("Module: %s\n", TEST_module);
  printf("Test sequence begin\n");
  printf("-------------------\n");

  for(unsigned int i=0; i<TEST_LIST_CONFIG_SIZE; i++)
  {
    printf("Executing test: %s\n", test_list_config[i].functionName);
    if(test_list_config[i].run)
    {
      ret[i] = (test_list_config[i].pf)();
    }
    else 
    {
      ret[i] = -1;
    }
    printf("End of test: %s - ", test_list_config[i].functionName);
    if(ret[i] == 0)
    {
      printf("PASSED\n");
    }
    else if(ret[i] == 1)
    {
      printf("FAILED\n");
    }
    else
    {
      printf("NOT EXECUTED\n");
    }
  }
  printf("-------------------\n");
  printf("Test sequence end  \n\n");

  printf("------Sum Up-------\n");
  for(unsigned int i=0; i<TEST_LIST_CONFIG_SIZE; i++)
  {
    if(ret[i] == 0)
    {
      test_passed++;
      printf("[v] TEST %s: passed\n", test_list_config[i].functionName);
    }
    else if(ret[i] > 1)
    {
      test_failed++;
      printf("[x] TEST %s: failed\n", test_list_config[i].functionName);
    }
    else
    {
      test_notrun++;
      printf("[u] TEST %s: not executed\n", test_list_config[i].functionName);
    }
    
  }
  printf("%d failed - %d passed - %d unexecuted - total: %d tests\n", test_failed, test_passed, test_notrun, test_passed+test_failed+test_notrun);
  printf("-------------------\n");

  return test_failed;
}
