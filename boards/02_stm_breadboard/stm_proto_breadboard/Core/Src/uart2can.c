/************************************************************************
 * File Name          : templace_source.c
 * Author             : author
 * Date               : 23/02/2020
 * Description        : source template file
 ***********************************************************************/


/************************************************************************
* INCLUDES *
************************************************************************/

/************************************************************************
* PRIVATE MACROS *
************************************************************************/


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/


/************************************************************************
* PRIVATE PROTOTYPES *
************************************************************************/


/************************************************************************
* FUNCTIONS *
************************************************************************/
unsigned char u2c_mem_cmp(unsigned char* data1, unsigned char* data2, unsigned char len)
{
  unsigned char i;
  for( i=0; i<len; i++)
  {
    if( data1[i] != data2[i] )
	{
	  return 1;
	}
  }
  return 0;
}

#define a2i(a) \
	(a-'0')

/************************************************************************
 * Function: Function_name                                              *
 * input: param - parameter used in the function                        *
 * output: none                                                         *
 * return: none                                                         *
 * description: This function is a template                             *
 ***********************************************************************/
unsigned char Uart2can_Extract(unsigned char * dataBuff, unsigned int * CanId, unsigned char * dlc, unsigned char * data)
{
  /* data: 1234 8 11 22 33 44 55 66 77 88 */
  /* data: 0x1234 8 0x1122334455667788 */
  unsigned char pos=0, i;

  if(u2c_mem_cmp(&dataBuff[0], (unsigned char *)"can_send ", 9) == 0)
  {
     pos += 9;
  }
  else
  {
	  return 1;
  }


  if(u2c_mem_cmp(&dataBuff[pos], (unsigned char *)"0x", 2) == 0)
  {
     pos = pos + 2;
  }

  /* read can id */
  *CanId = 0;
  while(dataBuff[pos] != ' ')
  {
      *CanId = *CanId << 4;
	  *CanId = *CanId + (a2i(dataBuff[pos]) & 0x0F);
	  pos++;
  }

  pos += 1;

  *dlc = a2i(dataBuff[pos++]);
  if(*dlc > 8)
    return 1;

  pos += 1;

  for(i=0; i<*dlc; i++)
  {
	if(u2c_mem_cmp(&dataBuff[pos], (unsigned char*)"0x", 2) == 0)
    {
      pos += 2;
    }
	if(u2c_mem_cmp(&dataBuff[pos], (unsigned char*)" ", 1) == 0)
    {
      pos += 1;
	}
    data[i] = (
    		    ( (a2i(dataBuff[pos]) << 4) & 0xF0) +
				  (a2i(dataBuff[pos+1]) & 0x0F )
			  );
    pos += 2;
  }
  
  return 0;
}


void Uart2can_RxIndication(unsigned char * dataBuff)
{

	unsigned int CanId;
	unsigned char dlc;
	unsigned char CanData[8];

  Uart2can_Extract(dataBuff, &CanId, &dlc, CanData);


  OrderProcess(CanId, CanData, dlc);


//  LightOrderTmt(0, 0x11, 0);
}

