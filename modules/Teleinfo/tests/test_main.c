#include <stdio.h>
#include "teleinfo.h"

int TEST_teleinfo_Init(void);
int TEST_teleinfo_rawByte_receive(void);
int TEST_Teleinfo_Mgt(void);
int TEST_TIC_check_frame(void);
int TEST_TIC_set_option(void);
int TEST_TIC_get_option(void);
int TEST_Ascii2Int(void);
int TEST_TIC_FillInInfo(void);
int TEST_TIC_getLabelCode(void);
int TEST_TIC_CRC(void);

int TEST_TeleInfo_Integration(void);

typedef struct
{
  unsigned char functionName[40];
  int (*pf)(void);
  unsigned char run;
} T_testFunction;

/* Test configuration (test_cfg.c) */
unsigned char TEST_module[50] = "Teleinfo";
T_testFunction test_list_config[]=
{
  /* Unit tests*/
  {"teleinfo_Init", TEST_teleinfo_Init, 1},
  {"teleinfo_rawByte_receive", TEST_teleinfo_rawByte_receive, 1},
//  {"Teleinfo_Mgt", TEST_Teleinfo_Mgt},
//  {"TIC_check_frame", TEST_TIC_check_frame},
  {"TIC_set_option", TEST_TIC_set_option, 1},
  {"TIC_get_option", TEST_TIC_get_option, 1},
//  {"Ascii2Int", TEST_Ascii2Int},
//  {"TIC_FillInInfo", TEST_TIC_FillInInfo},
  {"TIC_getLabelCode", TEST_TIC_getLabelCode, 1},
  {"TIC_CRC", TEST_TIC_CRC, 1},

  /* Integration tests*/
  {"Integration test: TeleInfo_Integration", TEST_TeleInfo_Integration, 1},
};
#define TEST_LIST_CONFIG_SIZE (sizeof(test_list_config)/sizeof(T_testFunction))

#define TST_ASCII_STX   0x2  // Start of Text
#define TST_ASCII_ETX   0x3  // End of Text
#define TST_ASCII_LF    0xa  // Start of label
#define TST_ASCII_CR    0xd  // End of label
#define TST_ASCII_SP    0x20 // Space

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

unsigned int errorNum;
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

/************************************************
 *
 *   UNIT TESTS
 *
 *************************************************/
extern u8 rawDataTab[];
extern u16 cptRawData;
extern u8 cptTIC_label;
extern T_TIC_INFO TIC_info;
extern T_TIC_FIFO TIC_Fifo;

int TEST_teleinfo_Init(void)
{
  int result=-1;
  TEST_init();

  /* Init */
  teleinfo_Init();

  /* Check TIC_Fifo structure */
  assert(TIC_Fifo.size      == 55, "size fail");
  assert(TIC_Fifo.WriteIdx   == 0, "WriteIdx fail");
  assert(TIC_Fifo.ReadIdx    == 0, "ReadIdx fail");
  assert(TIC_Fifo.NumElem    == 0, "NumElem fail");
  assert(TIC_Fifo.NumMaxElem == 0, "NumMaxElem fail");
  assert(TIC_Fifo.overrun    == 0, "overrun fail");

  return TEST_finish();
}

int TEST_teleinfo_rawByte_receive(void)
{
  int result = TST_RET_N_OK;
  TEST_init();

  int testStr[10];

//  int testVector[]={ /* testChar, cpt | cpt_out, writeIdx, ReadIdx, NumOfElem */
//                   { ASCII_STC, 2, 0, 0, 0, 0},
//                   { }, 
//                 }
//  unsigned char testVectorSize = sizeof(testVector)/sizeof(testVectorType);

  unsigned char testChar;
  /*
   * Start of transmission
   * End of transmission
   * Start of string
   * end of string
   * label
   * value
   * */


  /* Initialize variables */
  teleinfo_Init();

  /* 1. Start of transmission
   * - start a new line, character 0
   * */

  /* Start of transmission */
  testChar=0x02; //ASCII STX

  cptTIC_label = 2;
  teleinfo_rawByte_receive(testChar);

  /* checks */
  assert(cptTIC_label == 2, "STX - wrong cpt");

  TIC_Fifo.WriteIdx == 0;
  TIC_Fifo.ReadIdx == 0;
  TIC_Fifo.NumElem == 0;


  /* End of transmission */
  testChar=TST_ASCII_ETX;

  cptTIC_label = 3;
  teleinfo_rawByte_receive(testChar);

  /* checks */
  assert(cptTIC_label == 3, "ETX - wrong cpt");

  assert(TIC_Fifo.WriteIdx == 0, "fail1");
  assert(TIC_Fifo.ReadIdx == 0, "fail2");
  assert(TIC_Fifo.NumElem == 0, "fail3");


  /* Start of string */
  testChar=TST_ASCII_LF;

  cptTIC_label = 2;
  teleinfo_rawByte_receive(testChar);

  /* checks */
  assert(cptTIC_label == 1, "fail4");

  assert(TIC_Fifo.WriteIdx == 0, "fail5");
  assert(TIC_Fifo.ReadIdx == 0, "fail6");
  assert(TIC_Fifo.NumElem == 0, "fail7");


  /* End of string */
  testChar=ASCII_CR;

  cptTIC_label = 2;
  teleinfo_rawByte_receive(testChar);

  /* checks */
  assert(cptTIC_label == 2, "fail8");

  assert(TIC_Fifo.WriteIdx == 1, "fail9");
  assert(TIC_Fifo.ReadIdx == 0, "fail10");
  assert(TIC_Fifo.NumElem == 1, "fail11");


  /* Label */
  testChar='A';

  cptTIC_label = 2;
  teleinfo_rawByte_receive(testChar);

  /* checks */
  assert(cptTIC_label == 3, "fail8");

  assert(TIC_Fifo.WriteIdx == 1, "fail9");
  assert(TIC_Fifo.ReadIdx == 0, "fail10");
  assert(TIC_Fifo.NumElem == 1, "fail11");

  return TEST_finish();
}

int TEST_Teleinfo_Mgt(void)
{
  int result = TST_RET_N_OK;
  TEST_init();

  return TEST_finish();
}

int TEST_TIC_check_frame(void)
{
  int result = TST_RET_N_OK;
  TEST_init();

  return TEST_finish();
}


int TEST_TIC_set_option(void)
{
  int result = TST_RET_N_OK;
  unsigned char str[30];

  TEST_init();

  /* ADCO */
  assert( TIC_set_option(ADCO, "0101010101010", ADCO_LEN-1) == TST_RET_N_OK, "set option ADCO failed");
  assert( TIC_set_option(ADCO, "0101010101010", ADCO_LEN+1) == TST_RET_N_OK, "set option ADCO failed");
  assert( TIC_set_option(ADCO, "0101010101010", ADCO_LEN)   == TST_RET_OK, "set option ADCO failed");
  assert( tst_cmp(TIC_info.ADCO ,"0101010101010", ADCO_LEN) == TST_RET_OK, "set option ADCO cmp failed");

  /* OPTARIF */
  assert( TIC_set_option(OPTARIF, "0101010101010", OPTARIF_LEN-1) == TST_RET_N_OK, "set option OPTARIF failed");
  assert( TIC_set_option(OPTARIF, "0101010101010", OPTARIF_LEN+1) == TST_RET_N_OK, "set option OPTARIF failed");
  assert( TIC_set_option(OPTARIF, "0101010101010", OPTARIF_LEN)   == TST_RET_OK, "set option OPTARIF failed");
  assert( tst_cmp(TIC_info.OPTARIF ,"0101010101010", OPTARIF_LEN) == TST_RET_OK, "set option OPTARIF cmp failed");

  /* ISOUSC */
  assert( TIC_set_option(ISOUSC, "0101010101010", ISOUSC_LEN-1) == TST_RET_N_OK, "set option ISOUSC failed");
  assert( TIC_set_option(ISOUSC, "0101010101010", ISOUSC_LEN+1) == TST_RET_N_OK, "set option ISOUSC failed");
  assert( TIC_set_option(ISOUSC, "0101010101010", ISOUSC_LEN)   == TST_RET_OK, "set option ISOUSC failed");
  assert( tst_cmp(TIC_info.ISOUSC ,"0101010101010", ISOUSC_LEN) == TST_RET_OK, "set option ISOUSC cmp failed");

  // /* BASE */
  assert( TIC_set_option(BASE, "0101010101010", BASE_LEN-1) == TST_RET_N_OK, "set option BASE failed");
  assert( TIC_set_option(BASE, "0101010101010", BASE_LEN+1) == TST_RET_N_OK, "set option BASE failed");
  assert( TIC_set_option(BASE, "0101010101010", BASE_LEN)   == TST_RET_OK, "set option BASE failed");
  assert( tst_cmp(TIC_info.BASE ,"0101010101010", BASE_LEN) == TST_RET_OK, "set option BASE cmp failed");

  /* HCHC */
  assert( TIC_set_option(HCHC, "0101010101010", HCHC_LEN-1) == TST_RET_N_OK, "set option HCHC failed");
  assert( TIC_set_option(HCHC, "0101010101010", HCHC_LEN+1) == TST_RET_N_OK, "set option HCHC failed");
  assert( TIC_set_option(HCHC, "0101010101010", HCHC_LEN)   == TST_RET_OK, "set option HCHC failed");
  assert( tst_cmp(TIC_info.HCHC ,"0101010101010", HCHC_LEN) == TST_RET_OK, "set option HCHC cmp failed");

  /* HCHP */
  assert( TIC_set_option(HCHP, "0101010101010", HCHP_LEN-1) == TST_RET_N_OK, "set option HCHP failed");
  assert( TIC_set_option(HCHP, "0101010101010", HCHP_LEN+1) == TST_RET_N_OK, "set option HCHP failed");
  assert( TIC_set_option(HCHP, "0101010101010", HCHP_LEN)   == TST_RET_OK, "set option HCHP failed");
  assert( tst_cmp(TIC_info.HCHP ,"0101010101010", HCHP_LEN) == TST_RET_OK, "set option HCHP cmp failed");

  /* EJPHN */
  assert( TIC_set_option(EJPHN, "0101010101010", EJPHN_LEN-1) == TST_RET_N_OK, "set option EJPHN failed");
  assert( TIC_set_option(EJPHN, "0101010101010", EJPHN_LEN+1) == TST_RET_N_OK, "set option EJPHN failed");
  assert( TIC_set_option(EJPHN, "0101010101010", EJPHN_LEN)   == TST_RET_OK, "set option EJPHN failed");
  assert( tst_cmp(TIC_info.EJPHN ,"0101010101010", EJPHN_LEN) == TST_RET_OK, "set option EJPHN cmp failed");

  /* EJPHPM */
  assert( TIC_set_option(EJPHPM, "0101010101010", EJPHPM_LEN-1) == TST_RET_N_OK, "set option EJPHPM failed");
  assert( TIC_set_option(EJPHPM, "0101010101010", EJPHPM_LEN+1) == TST_RET_N_OK, "set option EJPHPM failed");
  assert( TIC_set_option(EJPHPM, "0101010101010", EJPHPM_LEN)   == TST_RET_OK, "set option EJPHPM failed");
  assert( tst_cmp(TIC_info.EJPHPM ,"0101010101010", EJPHPM_LEN) == TST_RET_OK, "set option EJPHPM cmp failed");

  /* BBRHCJB */
  assert( TIC_set_option(BBRHCJB, "0101010101010", BBRHCJB_LEN-1) == TST_RET_N_OK, "set option BBRHCJB failed");
  assert( TIC_set_option(BBRHCJB, "0101010101010", BBRHCJB_LEN+1) == TST_RET_N_OK, "set option BBRHCJB failed");
  assert( TIC_set_option(BBRHCJB, "0101010101010", BBRHCJB_LEN)   == TST_RET_OK, "set option BBRHCJB failed");
  assert( tst_cmp(TIC_info.BBRHCJB ,"0101010101010", BBRHCJB_LEN) == TST_RET_OK, "set option BBRHCJB cmp failed");
  /* BBRHPJB */
  assert( TIC_set_option(BBRHPJB, "0101010101010", BBRHPJB_LEN-1) == TST_RET_N_OK, "set option BBRHPJB failed");
  assert( TIC_set_option(BBRHPJB, "0101010101010", BBRHPJB_LEN+1) == TST_RET_N_OK, "set option BBRHPJB failed");
  assert( TIC_set_option(BBRHPJB, "0101010101010", BBRHPJB_LEN)   == TST_RET_OK, "set option BBRHPJB failed");
  assert( tst_cmp(TIC_info.BBRHPJB ,"0101010101010", BBRHPJB_LEN) == TST_RET_OK, "set option BBRHPJB cmp failed");

  /* BBRHCJW */
  assert( TIC_set_option(BBRHCJW, "0101010101010", BBRHCJW_LEN-1) == TST_RET_N_OK, "set option BBRHCJW failed");
  assert( TIC_set_option(BBRHCJW, "0101010101010", BBRHCJW_LEN+1) == TST_RET_N_OK, "set option BBRHCJW failed");
  assert( TIC_set_option(BBRHCJW, "0101010101010", BBRHCJW_LEN)   == TST_RET_OK, "set option BBRHCJW failed");
  assert( tst_cmp(TIC_info.BBRHCJW ,"0101010101010", BBRHCJW_LEN) == TST_RET_OK, "set option BBRHCJW cmp failed");

  /* BBRHPJW */
  assert( TIC_set_option(BBRHPJW, "0101010101010", BBRHPJW_LEN-1) == TST_RET_N_OK, "set option BBRHPJW failed");
  assert( TIC_set_option(BBRHPJW, "0101010101010", BBRHPJW_LEN+1) == TST_RET_N_OK, "set option BBRHPJW failed");
  assert( TIC_set_option(BBRHPJW, "0101010101010", BBRHPJW_LEN)   == TST_RET_OK, "set option BBRHPJW failed");
  assert( tst_cmp(TIC_info.BBRHPJW ,"0101010101010", BBRHPJW_LEN) == TST_RET_OK, "set option BBRHPJW cmp failed");
  /* BBRHCJR */
  assert( TIC_set_option(BBRHCJR, "0101010101010", BBRHCJR_LEN-1) == TST_RET_N_OK, "set option BBRHCJR failed");
  assert( TIC_set_option(BBRHCJR, "0101010101010", BBRHCJR_LEN+1) == TST_RET_N_OK, "set option BBRHCJR failed");
  assert( TIC_set_option(BBRHCJR, "0101010101010", BBRHCJR_LEN)   == TST_RET_OK, "set option BBRHCJR failed");
  assert( tst_cmp(TIC_info.BBRHCJR ,"0101010101010", BBRHCJR_LEN) == TST_RET_OK, "set option BBRHCJR cmp failed");
  
  /* BBRHPJR */
  assert( TIC_set_option(BBRHPJR, "0101010101010", BBRHPJR_LEN-1) == TST_RET_N_OK, "set option BBRHPJR failed");
  assert( TIC_set_option(BBRHPJR, "0101010101010", BBRHPJR_LEN+1) == TST_RET_N_OK, "set option BBRHPJR failed");
  assert( TIC_set_option(BBRHPJR, "0101010101010", BBRHPJR_LEN)   == TST_RET_OK, "set option BBRHPJR failed");
  assert( tst_cmp(TIC_info.BBRHPJR ,"0101010101010", BBRHPJR_LEN) == TST_RET_OK, "set option BBRHPJR cmp failed");
    
  /* PEJP */
  assert( TIC_set_option(PEJP, "0101010101010", PEJP_LEN-1) == TST_RET_N_OK, "set option PEJP failed");
  assert( TIC_set_option(PEJP, "0101010101010", PEJP_LEN+1) == TST_RET_N_OK, "set option PEJP failed");
  assert( TIC_set_option(PEJP, "0101010101010", PEJP_LEN)   == TST_RET_OK, "set option PEJP failed");
  assert( tst_cmp(TIC_info.PEJP ,"0101010101010", PEJP_LEN) == TST_RET_OK, "set option PEJP cmp failed");
 
  /* PTEC */
  assert( TIC_set_option(PTEC, "0101010101010", PTEC_LEN-1) == TST_RET_N_OK, "set option PTEC failed");
  assert( TIC_set_option(PTEC, "0101010101010", PTEC_LEN+1) == TST_RET_N_OK, "set option PTEC failed");
  assert( TIC_set_option(PTEC, "0101010101010", PTEC_LEN)   == TST_RET_OK, "set option PTEC failed");
  assert( tst_cmp(TIC_info.PTEC ,"0101010101010", PTEC_LEN) == TST_RET_OK, "set option PTEC cmp failed");
 
  /* DEMAIN */
  assert( TIC_set_option(DEMAIN, "0101010101010", DEMAIN_LEN-1) == TST_RET_N_OK, "set option DEMAIN failed");
  assert( TIC_set_option(DEMAIN, "0101010101010", DEMAIN_LEN+1) == TST_RET_N_OK, "set option DEMAIN failed");
  assert( TIC_set_option(DEMAIN, "0101010101010", DEMAIN_LEN)   == TST_RET_OK, "set option DEMAIN failed");
  assert( tst_cmp(TIC_info.DEMAIN ,"0101010101010", DEMAIN_LEN) == TST_RET_OK, "set option DEMAIN cmp failed");

  /* IINST */
  assert( TIC_set_option(IINST, "0101010101010", IINST_LEN-1) == TST_RET_N_OK, "set option IINST failed");
  assert( TIC_set_option(IINST, "0101010101010", IINST_LEN+1) == TST_RET_N_OK, "set option IINST failed");
  assert( TIC_set_option(IINST, "0101010101010", IINST_LEN)   == TST_RET_OK, "set option IINST failed");
  assert( tst_cmp(TIC_info.IINST ,"0101010101010", IINST_LEN) == TST_RET_OK, "set option IINST cmp failed");

  /* ADPS */
  assert( TIC_set_option(ADPS, "0101010101010", ADPS_LEN-1) == TST_RET_N_OK, "set option ADPS failed");
  assert( TIC_set_option(ADPS, "0101010101010", ADPS_LEN+1) == TST_RET_N_OK, "set option ADPS failed");
  assert( TIC_set_option(ADPS, "0101010101010", ADPS_LEN)   == TST_RET_OK, "set option ADPS failed");
  assert( tst_cmp(TIC_info.ADPS ,"0101010101010", ADPS_LEN) == TST_RET_OK, "set option ADPS cmp failed");

  /* IMAX */
  assert( TIC_set_option(IMAX, "0101010101010", IMAX_LEN-1) == TST_RET_N_OK, "set option IMAX failed");
  assert( TIC_set_option(IMAX, "0101010101010", IMAX_LEN+1) == TST_RET_N_OK, "set option IMAX failed");
  assert( TIC_set_option(IMAX, "0101010101010", IMAX_LEN)   == TST_RET_OK, "set option IMAX failed");
  assert( tst_cmp(TIC_info.IMAX ,"0101010101010", IMAX_LEN) == TST_RET_OK, "set option IMAX cmp failed");

  /* PAPP */
  assert( TIC_set_option(PAPP, "0101010101010", PAPP_LEN-1) == TST_RET_N_OK, "set option PAPP failed");
  assert( TIC_set_option(PAPP, "0101010101010", PAPP_LEN+1) == TST_RET_N_OK, "set option PAPP failed");
  assert( TIC_set_option(PAPP, "0101010101010", PAPP_LEN)   == TST_RET_OK, "set option PAPP failed");
  assert( tst_cmp(TIC_info.PAPP ,"0101010101010", PAPP_LEN) == TST_RET_OK, "set option PAPP cmp failed");

  /* HHPHC */
  assert( TIC_set_option(HHPHC, "0101010101010", HHPHC_LEN-1) == TST_RET_N_OK, "set option HHPHC failed");
  assert( TIC_set_option(HHPHC, "0101010101010", HHPHC_LEN+1) == TST_RET_N_OK, "set option HHPHC failed");
  assert( TIC_set_option(HHPHC, "0101010101010", HHPHC_LEN)   == TST_RET_OK, "set option HHPHC failed");
  assert( tst_cmp(TIC_info.HHPHC ,"0101010101010", HHPHC_LEN) == TST_RET_OK, "set option HHPHC cmp failed");
  
  /* MOTDETAT */
  assert( TIC_set_option(MOTDETAT, "0101010101010", MOTDETAT_LEN-1) == TST_RET_N_OK, "set option MOTDETAT failed");
  assert( TIC_set_option(MOTDETAT, "0101010101010", MOTDETAT_LEN+1) == TST_RET_N_OK, "set option MOTDETAT failed");
  assert( TIC_set_option(MOTDETAT, "0101010101010", MOTDETAT_LEN)   == TST_RET_OK, "set option MOTDETAT failed");
  assert( tst_cmp(TIC_info.MOTDETAT ,"0101010101010", MOTDETAT_LEN) == TST_RET_OK, "set option MOTDETAT cmp failed");

  return TEST_finish();
}

int TEST_TIC_get_option(void)
{
  int result=-1;
  unsigned char outStr[30]="test123456test123456test123456";

  TEST_init();

  /* Initialize data */
  tst_set(TIC_info.ADCO,    "0123456789AB\0", 12+1);
  tst_set(TIC_info.OPTARIF, "CDE\0",           4+1);
  tst_set(TIC_info.ISOUSC,  "FG\0",            2+1);
  tst_set(TIC_info.HCHC,    "HIJKLMNOP\0",     9+1);
  tst_set(TIC_info.HCHP,    "QRSTUVWXY\0",     9+1);
  tst_set(TIC_info.PTEC,    "Zabc\0",          4+1);
  tst_set(TIC_info.IINST,   "def\0",           3+1);
  tst_set(TIC_info.ADPS,    "ghi\0",           3+1);
  tst_set(TIC_info.IMAX,    "jkl\0",           3+1);
  tst_set(TIC_info.PAPP,    "mnopq\0",         5+1);
  tst_set(TIC_info.HHPHC,   "rs\0",            1+1);
  tst_set(TIC_info.MOTDETAT,"tuvwxy\0",        6+1);
  
  assert( TIC_get_option(ADCO, &outStr[0], 12+1) == 0, "ADCO get option failed");
  assert( tst_cmp(outStr, "0123456789AB\0", 12+1) == 0, "ADCO get option cmp failed");

  assert( TIC_get_option(OPTARIF, outStr, 4+1) == 0, "OPTARIF get option failed");
  assert( tst_cmp(outStr, "CDE\0", 4+1) == 0, "OPTARIF get option cmp failed");

  assert( TIC_get_option(ISOUSC, outStr, 2+1) == 0, "ISOUSC get option failed");
  assert( tst_cmp(outStr, "FG\0", 2+1) == 0, "ISOUSC get option cmp failed");

  assert( TIC_get_option(HCHC, outStr, 9+1) == 0, "HCHC get option failed");
  assert( tst_cmp(outStr, "HIJKLMNOP\0", 9+1) == 0, "HCHC get option cmp failed");
  
  assert( TIC_get_option(HCHP, outStr, 9+1) == 0, "HCHP get option failed");
  assert( tst_cmp(outStr, "QRSTUVWXY\0", 9+1) == 0, "HCHP get option cmp failed");
  
  assert( TIC_get_option(PTEC, outStr, 4+1) == 0, "PTEC get option failed");
  assert( tst_cmp(outStr, "Zabc\0", 4+1) == 0, "PTEC get option cmp failed");
  
  assert( TIC_get_option(IINST, outStr, 3+1) == 0, "IINST get option failed");
  assert( tst_cmp(outStr, "def\0", 3+1) == 0, "IINST get option cmp failed");
  
  assert( TIC_get_option(ADPS, outStr, 3+1) == 0, "ADPS get option failed");
  assert( tst_cmp(outStr, "ghi\0", 3+1) == 0, "ADPS get option cmp failed");
  
  assert( TIC_get_option(IMAX, outStr, 3+1) == 0, "IMAX get option failed");
  assert( tst_cmp(outStr, "jkl\0", 3+1) == 0, "IMAX get option cmp failed");
  
  assert( TIC_get_option(PAPP, outStr, 5+1) == 0, "PAPP get option failed");
  assert( tst_cmp(outStr, "mnopq\0", 5+1) == 0, "PAPP get option cmp failed");
  
  assert( TIC_get_option(HHPHC, outStr, 1+1) == 0, "HHPHC get option failed");
  assert( tst_cmp(outStr, "rs\0", 1+1) == 0, "HHPHC get option cmp failed");
  
  assert( TIC_get_option(MOTDETAT, outStr, 6+1) == 0, "MOTDETAT get option failed");
  assert( tst_cmp(outStr, "tuvwxy\0", 6+1) == 0, "MOTDETAT get option cmp failed");

  return TEST_finish();
}

int TEST_Ascii2Int(void)
{
  int result=-1;
  TEST_init();

  return TEST_finish();
}

int TEST_TIC_FillInInfo(void)
{
  int result=-1;
  TEST_init();

  return TEST_finish();
}

int TEST_TIC_getLabelCode(void)
{
  int result=-1;
  TEST_init();

  result = TIC_getLabelCode("ADCO");
  assert(result == ADCO, "ADCO failed");

  result = TIC_getLabelCode("IINST");
  assert(result == IINST, "IINST failed");

  result = TIC_getLabelCode("IMAX");
  assert(result == IMAX, "IMAX failed");

  result = TIC_getLabelCode("ISOUSC");
  assert(result == ISOUSC, "ISOUSC failed");

  result = TIC_getLabelCode("OPTARIF");
  assert(result == OPTARIF, "OPTARIF failed");

  result = TIC_getLabelCode("HCHC");
  assert(result == HCHC, "HCHC failed");

  result = TIC_getLabelCode("HCHP");
  assert(result == HCHP, "HCHP failed");

  result = TIC_getLabelCode("HHPHC");
  assert(result == HHPHC, "HHPHC failed");

  result = TIC_getLabelCode("PTEC");
  assert(result == PTEC, "PTEC failed");

  result = TIC_getLabelCode("PAPP");
  assert(result == PAPP, "PAPP failed");

  result = TIC_getLabelCode("MOTDETAT");
  assert(result == MOTDETAT, "MOTDETAT failed");

  result = TIC_getLabelCode("");
  assert(result == INVALID, "INVALID label failed");

  return TEST_finish();
}


typedef struct
{
  unsigned char string[30];
  unsigned char expectedResult;
} T_TIC_CRC;

int TEST_TIC_CRC(void)
{
  int result=0;
  unsigned char ret;
  T_TIC_CRC test_table[]=
  {
    {"test_string", 'V'},
    {"ADCO 030022261629 8\r\n", '8'},
    {"HCHC 035047226 # CR LF", '#'},
    //LF ADCO space 0 30022261629 space 8 CR 
    {"\xa\x41\x44\x43\x4f\x20\x30\x33\x30\x30\x32\x32\x32\x36\x31\x36\x32\x39\x20\x38\xd", '8'},
  };
 
  for(int j=0; j<4; j++)
  {
    ret = TIC_CRC(test_table[j].string);

    if(test_table[j].expectedResult == ret)
    {
        printf("[OK]");
    }
    else
    {
        printf("[--]");
    }

    printf("  expected value: %d, result: %d\n", test_table[j].expectedResult, ret);
 
    if(ret != test_table[j].expectedResult)
      result = 1;
  }
  return result;
}

/************************************************
 *
 *   INTEGRATION TESTS
 *
 *************************************************/

extern unsigned char TIC_FIFO_Buff[55][30];

int TEST_TeleInfo_Integration(void)
{
  int result=0;
  unsigned char ret;

//  unsigned char string[]="ADCO 030022261629 8\r\nHCHC 035047226 #\r\n";
  unsigned char string[209]=
  {
    0x50,0x48,0x43,0x20,0x41,0x20,0x2c,0xd, /* PHC space A space , CR */
    0xa ,0x4d,0x4f,0x54,0x44,0x45,0x54,0x41,0x54,0x20,0x30,0x30,0x30,0x30,0x30,0x30,0x20,0x42,0xd ,0x3 ,/* LF MOTDETAT space 000000 space B CR ETX */
    0x2 ,0xa ,0x41,0x44,0x43,0x4f,0x20,0x30,0x33,0x30,0x30,0x32,0x32,0x32,0x36,0x31,0x36,0x32,0x39,0x20,0x38,0xd ,/* STX LF ADCO space 030022261629 space 8 CR */
    0xa ,0x4f,0x50,0x54,0x41,0x52,0x49,0x46,0x20,0x48,0x43,0x2e,0x2e,0x20,0x3c,0xd , /*LF OPTARIF space HC.. space < CR */
    0xa ,0x49,0x53,0x4f,0x55,0x53,0x43,0x20,0x33,0x30,0x20,0x39,0xd,/* LF ISOUSC space 30 space 9 CR */
    0xa ,0x48,0x43,0x48,0x43,0x20,0x30,0x33,0x35,0x30,0x34,0x37,0x32,0x32,0x36,0x20,0x23,0xd, /* LF HCHC space 035047226 space # CR */
    0xa ,0x48,0x43,0x48,0x50,0x20,0x30,0x32,0x37,0x36,0x36,0x37,0x30,0x31,0x38,0x20,0x38,0xd, /* LF HCHP space 027667018 space 8 CR */
    0xa ,0x50,0x54,0x45,0x43,0x20,0x48,0x50,0x2e,0x2e,0x20,0x20,0xd, /* LF PTEC space HP.. space  space CR */
    0xa ,0x49,0x49,0x4e,0x53,0x54,0x20,0x30,0x30,0x31,0x20,0x58,0xd, /* LF IINST space 001 space X CR */
    0xa ,0x49,0x4d,0x41,0x58,0x20,0x30,0x32,0x35,0x20,0x46,0xd, /* LF IMAX space 025 space F CR */
    0xa ,0x50,0x41,0x50,0x50,0x20,0x30,0x30,0x31,0x33,0x30,0x20,0x25,0xd, /* LF  PAPP  space  00130  space  % CR */
    0xa ,0x48,0x48,0x50,0x48,0x43,0x20,0x41,0x20,0x2c,0xd, /* LF HHPHC space A space , CR */
    0xa ,0x4d,0x4f,0x54,0x44,0x45,0x54,0x41,0x54,0x20,0x30,0x30,0x30,0x30,0x30,0x30,0x20,0x42,0xd ,0x3, /* LF MOTDETAT space 000000 space B CR ETX */
    0x2 ,0xa ,0x41,0x44,0x43,0x4f,0x20,0x30,0x33,0x30,0x30, /*STX LF ADCO space 0300 */
  };

//  "ADCO" 030022261629
//  "HCHC" 035047226


  //init
  teleinfo_Init();
  teleinfo_TIC_reset_values();

//  TIC_Fifo.buff       = &(TIC_FIFO_Buff[0][0]);
  assert(TIC_Fifo.size      == 55, "size fail");
  assert(TIC_Fifo.WriteIdx   == 0, "WriteIdx fail");
  assert(TIC_Fifo.ReadIdx    == 0, "ReadIdx fail");
  assert(TIC_Fifo.NumElem    == 0, "NumElem fail");
  assert(TIC_Fifo.NumMaxElem == 0, "NumMaxElem fail");
  assert(TIC_Fifo.overrun    == 0, "overrun fail");

  /* STEP 1 */
  //empty buffer
  for(int i=0; i<55; i++)
  {
    for(int j=0; j<30;j++)
    {
      TIC_FIFO_Buff[i][j] = 0;
    }
  }
  
  result += tst_cmp(TIC_info.ADCO,    "-------------", 12+1);
  result += tst_cmp(TIC_info.OPTARIF, "-----",          4+1);
  result += tst_cmp(TIC_info.ISOUSC,  "---",            2+1);
  result += tst_cmp(TIC_info.HCHC,    "----------",     9+1);
  result += tst_cmp(TIC_info.HCHP,    "----------",     9+1);
  result += tst_cmp(TIC_info.PTEC,    "----------",     4+1);
  result += tst_cmp(TIC_info.IINST,   "-----",          3+1);
  result += tst_cmp(TIC_info.ADPS,    "-----",          3+1);
  result += tst_cmp(TIC_info.IMAX,    "-----",          3+1);
  result += tst_cmp(TIC_info.PAPP,    "-----",          4+1);
  result += tst_cmp(TIC_info.HHPHC,   "--",             1+1);
  result += tst_cmp(TIC_info.MOTDETAT,"-------",        6+1);

  if(result == 0)
  {
    printf("[OK]  Step1: Index init\n");
  }
  else
  {
    printf("[--]  Step1: Index init\n");
  }


  /* STEP 2 */
  // Receive transmission
  for(int i=0; i<50; i++)
  {
    teleinfo_rawByte_receive(string[i]);
  }

  //check fifo == string

  Teleinfo_Mgt();

  /* at this point, only 2 index are received: */
  result += tst_cmp(TIC_info.ADCO,    "030022261629\0", 12+1); /* STX LF ADCO space 030022261629 space 8 CR */
  result += tst_cmp(TIC_info.OPTARIF, "-----",          4+1);
  result += tst_cmp(TIC_info.ISOUSC,  "---",            2+1);
  result += tst_cmp(TIC_info.HCHC,    "----------",     9+1);
  result += tst_cmp(TIC_info.HCHP,    "----------",     9+1);
  result += tst_cmp(TIC_info.PTEC,    "-----",          4+1);
  result += tst_cmp(TIC_info.IINST,   "----",           3+1);
  result += tst_cmp(TIC_info.ADPS,    "----",           3+1);
  result += tst_cmp(TIC_info.IMAX,    "----",           3+1);
  result += tst_cmp(TIC_info.PAPP,    "-----",          4+1);
  result += tst_cmp(TIC_info.HHPHC,   "--",             1+1);
  result += tst_cmp(TIC_info.MOTDETAT,"000000\0",       6+1); /* LF MOTDETAT space 000000 space B CR ETX */
  if(result == 0)
  {
    printf("[OK]  Step2: first 2 indexes\n");
  }
  else
  {
    printf("[--]  Step2: first 2 indexes\n");
  }
  assert(result == 0, "Step2 failed");
  

  // Receive transmission
  for(int i=79; i<79+18+18; i++)
  {
    teleinfo_rawByte_receive(string[i]);
  }

  //check fifo == string

  Teleinfo_Mgt();

  /* at this point, 2 more index are received: */
  result += tst_cmp(TIC_info.ADCO,    "030022261629\0", 12+1);
  result += tst_cmp(TIC_info.OPTARIF, "-----",           4+1);
  result += tst_cmp(TIC_info.ISOUSC,  "---",             2+1);
  result += tst_cmp(TIC_info.HCHC,    "035047226\0",     9+1); /* LF HCHC space 035047226 space # CR */
  result += tst_cmp(TIC_info.HCHP,    "027667018\0",     9+1); /* LF HCHP space 027667018 space 8 CR */
  result += tst_cmp(TIC_info.PTEC,    "-----",           4+1);
  result += tst_cmp(TIC_info.IINST,   "----",            3+1);
  result += tst_cmp(TIC_info.ADPS,    "----",            3+1);
  result += tst_cmp(TIC_info.IMAX,    "----",            3+1);
  result += tst_cmp(TIC_info.PAPP,    "-----",           4+1);
  result += tst_cmp(TIC_info.HHPHC,   "--",              1+1);
  result += tst_cmp(TIC_info.MOTDETAT,"000000\0",        6+1);
  if(result == 0)
  {
    printf("[OK]  Step3: next 2 indexes\n");
  }
  else
  {
    printf("[--]  Step3: next 2 indexes\n");
  }

  /* STEP4 */
  // Receive transmission
  for(int i=0; i<209; i++)
  {
    teleinfo_rawByte_receive(string[i]);
  }

  Teleinfo_Mgt();

  /* at this point, all indexes are received: */
  result += tst_cmp(TIC_info.ADCO,    "030022261629\0", 12+1); /* STX LF ADCO space 030022261629 space 8 CR */
  result += tst_cmp(TIC_info.OPTARIF, "HC..\0",          4+1); /* LF OPTARIF space HC.. space < CR          */
  result += tst_cmp(TIC_info.ISOUSC,  "30\0",            2+1); /* LF ISOUSC space 30 space 9 CR             */
  result += tst_cmp(TIC_info.HCHC,    "035047226\0",     9+1); /* LF HCHC space 035047226 space # CR        */
  result += tst_cmp(TIC_info.HCHP,    "027667018\0",     9+1); /* LF HCHP space 027667018 space 8 CR        */
  result += tst_cmp(TIC_info.PTEC,    "HP..\0",          4+1); /* LF PTEC space  space  space CR            */
  result += tst_cmp(TIC_info.IINST,   "001\0",           3+1); /* LF IINST space 001 space X CR             */
  result += tst_cmp(TIC_info.ADPS,    "----",            3+1);
  result += tst_cmp(TIC_info.IMAX,    "025\0",           3+1); /* LF IMAX space 025 space F CR              */
  result += tst_cmp(TIC_info.PAPP,    "00130\0",         4+1); /* LF  PAPP  space  00130  space  % CR       */
  result += tst_cmp(TIC_info.HHPHC,   "A\0",             1+1); /* LF HHPHC space A space , CR               */
  result += tst_cmp(TIC_info.MOTDETAT,"000000\0",        6+1); /* LF MOTDETAT space 000000 space B CR ETX   */

  if(result == 0)
  {
    printf("[OK]  Step4: all indexes\n");
  }
  else
  {
    printf("[--]  Step4: all indexes\n");
  }

  return result;
}

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
    printf("End of test test: %s - ", test_list_config[i].functionName);
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

  return 0;
}
