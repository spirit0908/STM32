/********************************************************************************
 * File Name          : teleinfo.c
 * Date               : 10/08/2007
 * Description        : Main program body
 *******************************************************************************/
#ifndef TELEINFO_H
#define TELEINFO_H

/************************************************************************
* INCLUDES *
************************************************************************/
#include "stm32f10x_lib.h"

#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_map.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_type.h"

/************************************************************************
* DEFINES *
************************************************************************/
/* TIC characters */
#define ASCII_STX   0x2  //Start of Text
#define ASCII_ETX   0x3  //End of Text
#define ASCII_LF    0xa  //Start of label
#define ASCII_CR    0xd  //End of label
#define ASCII_SP    0x20 //Space

// #define CBEMM       1 /* compteur «Bleu» électronique monophasé multitarif (CBEMM -évolution ICC) */
#define CBEMM_BASE  1
#define CBEMM_HC    1
#define CBEMM_EJP   1
#define CBEMM_TEMPO 1
#define CBETM       1
#define CBETM_SHORT 1
#define C_GAZ_AUTRE 1


/* Label options length*/
/* compteur «Bleu» électronique monophasé multitarif (CBEMM -évolution ICC) */
#define ADCO_LEN        (12+1) /* Adresse du compteur      */
#define OPTARIF_LEN      4+1 /* Option tarifaire choisie      */
#define ISOUSC_LEN       2+1 /* Intensité souscrite     A    */
#if( CBEMM_BASE )
    #define BASE_LEN     9+1 /* Index option Base      Wh  */
#endif
#if( CBEMM_HC )
    /* Index option Heures Creuses */
    #define HCHC_LEN     9+1 /* Heures Creuses                Wh  */
    #define HCHP_LEN     9+1 /* Heures Pleines                Wh  */
#endif
#if( CBEMM_EJP )
    /* Index option EJP */
    #define EJPHN_LEN    9+1 /* Heures Normales               Wh  */
    #define EJPHPM_LEN   9+1 /* Heures de Pointe Mobile       Wh  */
    #define PEJP_LEN     2+1 /* Préavis Début EJP (30 min)    min */
#endif
#if( CBEMM_TEMPO )
    /* Index option Tempo */
    #define BBRHCJB_LEN  9+1 /* Heures Creuses Jours Bleus    Wh  */
    #define BBRHPJB_LEN  9+1 /* Heures Pleines Jours Bleus    Wh  */
    #define BBRHCJW_LEN  9+1 /* Heures Creuses Jours Blancs   Wh  */
    #define BBRHPJW_LEN  9+1 /* Heures Pleines Jours Blancs   Wh  */
    #define BBRHCJR_LEN  9+1 /* Heures Creuses Jours Rouges   Wh  */
    #define BBRHPJR_LEN  9+1 /* Heures Pleines Jours Rouges   Wh  */
    #define DEMAIN_LEN   4+1 /* Couleur du lendemain              */
#endif
    #define PTEC_LEN     4+1 /* Période Tarifaire en cours        */
    #define IINST_LEN    3+1 /* Intensité Instantanée        A    */
    #define ADPS_LEN     3+1 /* Avertissement de Dépassementde Puissance Souscrite 3 A*/
    #define IMAX_LEN     3+1 /* Intensité maximale Appelée   3 A   */
    #define PAPP_LEN     5+1 /* Puissance apparente          5 VA  */
    #define HHPHC_LEN    1+1 /* Horaire Heures Pleines Heures Creuses 1 */
    #define MOTDETAT_LEN 6+1 /* Mot d'état du compteur       6     */
#if( CBETM )
/* compteur «Bleu» électronique triphasé multitarif (CBETM) */
/* Intensité Instantanée pour les 3 phases 1, 2 et 3 */
    #define IINST1_LEN   3+1 /* phase 1      3 */
    #define IINST2_LEN   3+1 /* phase 2      3 */
    #define IINST3_LEN   3+1 /* phase 3      3 */
/* Intensité maximale par phase 1, 2 et 3 */
    #define IMAX1_LEN    3+1 /* phase 1      3 */
    #define IMAX2_LEN    3+1 /* phase 2      3 */
    #define IMAX3_LEN    3+1 /* phase 3      3 */
    #define PMAX_LEN     5+1 /* Puissance maximale triphasée atteinte   5 W */
#endif
#if( CBETM_SHORT )
//trames courtes du compteur «Bleu» électronique triphasé multitarif (CBETM)
/* Avertissement de Dépassement d'intensité de réglage par phase */
    #define ADIR1_LEN    7+1 /* phase 1 */
    #define ADIR2_LEN    7+1 /* phase 2 */
    #define ADIR3_LEN    7+1 /* phase 3 */
#endif
#if( C_GAZ_AUTRE )
    #define GAZ_LEN      7+1 /* Index gaz                    7   dal */
    #define AUTRE_LEN    7+1 /* Index du troisième compteur  7   dal */
#endif


/************************************************************************
* STRUCTURES *
************************************************************************/
typedef struct
{
    /* compteur «Bleu» électronique monophasé multitarif (CBEMM -évolution ICC) */
    unsigned char ADCO[ADCO_LEN];       /* Adresse du compteur         12     */
    unsigned char OPTARIF[OPTARIF_LEN]; /* Option tarifaire choisie     4     */
    unsigned char ISOUSC[ISOUSC_LEN];   /* Intensité souscrite          2 A   */
#if( CBEMM_BASE )
    unsigned char BASE[BASE_LEN]; /* Index option Base            9 Wh  */
#endif
#if( CBEMM_HC )
    /* Index option Heures Creuses */
    unsigned char HCHC[HCHC_LEN]; /* Heures Creuses               9 Wh  */
    unsigned char HCHP[HCHP_LEN]; /* Heures Pleines               9 Wh  */
#endif
#if( CBEMM_EJP )
    /* Index option EJP */
    unsigned char EJPHN[EJPHN_LEN];   /* Heures Normales              9 Wh  */
    unsigned char EJPHPM[EJPHPM_LEN]; /* Heures de Pointe Mobile      9 Wh  */
    unsigned char PEJP[PEJP_LEN];     /* Préavis Début EJP (30 min)   2 min */
#endif
#if( CBEMM_TEMPO )
    /* Index option Tempo */
    unsigned char BBRHCJB[BBRHCJB_LEN]; /* Heures Creuses Jours Bleus   9 Wh  */
    unsigned char BBRHPJB[BBRHPJB_LEN]; /* Heures Pleines Jours Bleus   9 Wh  */
    unsigned char BBRHCJW[BBRHCJW_LEN]; /* Heures Creuses Jours Blancs  9 Wh  */
    unsigned char BBRHPJW[BBRHPJW_LEN]; /* Heures Pleines Jours Blancs  9 Wh  */
    unsigned char BBRHCJR[BBRHCJR_LEN]; /* Heures Creuses Jours Rouges  9 Wh  */
    unsigned char BBRHPJR[BBRHPJR_LEN]; /* Heures Pleines Jours Rouges  9 Wh  */
    unsigned char DEMAIN[DEMAIN_LEN];   /* Couleur du lendemain         4     */
#endif
    unsigned char PTEC[PTEC_LEN];         /* Période Tarifaire en cours   4     */
    unsigned char IINST[IINST_LEN];       /* Intensité Instantanée        3 A   */
    unsigned char ADPS[ADPS_LEN];         /* Avertissement de Dépassementde Puissance Souscrite 3 A*/
    unsigned char IMAX[IMAX_LEN];         /* Intensité maximale Appelée   3 A   */
    unsigned char PAPP[PAPP_LEN];         /* Puissance apparente          5 VA  */
    unsigned char HHPHC[HHPHC_LEN];       /* Horaire Heures Pleines Heures Creuses 1 */
    unsigned char MOTDETAT[MOTDETAT_LEN]; /* Mot d'état du compteur       6     */
#if( CBETM )
/* compteur «Bleu» électronique triphasé multitarif (CBETM) */
/* Intensité Instantanée pour les 3 phases 1, 2 et 3 */
    unsigned char IINST1[IINST1_LEN];  /* phase 1      3 */
    unsigned char IINST2[IINST2_LEN];  /* phase 2      3 */
    unsigned char IINST3[IINST3_LEN];  /* phase 3      3 */
/* Intensité maximale par phase 1, 2 et 3 */
    unsigned char IMAX1[IMAX1_LEN];   /* phase 1      3 */
    unsigned char IMAX2[IMAX2_LEN];   /* phase 2      3 */
    unsigned char IMAX3[IMAX3_LEN];   /* phase 3      3 */
    unsigned char PMAX[PMAX_LEN];   /* Puissance maximale triphasée atteinte   5 W */
#endif
#if( CBETM_SHORT )
//trames courtes du compteur «Bleu» électronique triphasé multitarif (CBETM)
/* Avertissement de Dépassement d'intensité de réglage par phase */
    unsigned char ADIR1[ADIR1_LEN]; /* phase 1 */
    unsigned char ADIR2[ADIR2_LEN]; /* phase 2 */
    unsigned char ADIR3[ADIR3_LEN]; /* phase 3 */
#endif
#if( C_GAZ_AUTRE )
    unsigned char GAZ[GAZ_LEN];   /* Index gaz                    7   dal */
    unsigned char AUTRE[AUTRE_LEN]; /* Index du troisième compteur  7   dal */
#endif
}T_TIC_INFO;


/* typedef struct
{
    unsigned char str[30];
}TIC_label_str; */


typedef struct
{
    // FIFO struct for TIC messages
    unsigned char **buff;       // raw data buffer
    unsigned char size;         // FIFO length
    unsigned char WriteIdx;     // Next position to write an element
    unsigned char ReadIdx;      // Next Element to read
    unsigned char NumElem;      // Total of elements currently in the FIFO
    unsigned char NumMaxElem;   // maximum of Elements saved (used for debug purpose)
    unsigned char overrun;
} T_TIC_FIFO;


enum TIC_LABEL_TYPE
{
/* compteur «Bleu» électronique monophasé multitarif (CBEMM -évolution ICC) */
    ADCO,    /* Adresse du compteur         12     */
    OPTARIF, /* Option tarifaire choisie     4     */
    ISOUSC,  /* Intensité souscrite          2 A   */
#if( CBEMM_BASE )
    BASE,    /* Index option Base            9 Wh  */
#endif
#if( CBEMM_HC )
    /* Index option Heures Creuses */
    HCHC,    /* Heures Creuses               9 Wh  */
    HCHP,    /* Heures Pleines               9 Wh  */
#endif
#if( CBEMM_EJP )
    /* Index option EJP */
    EJPHN,   /* Heures Normales              9 Wh  */
    EJPHPM,  /* Heures de Pointe Mobile      9 Wh  */
    PEJP,    /* Préavis Début EJP (30 min)   2 min */
#endif
#if( CBEMM_TEMPO )
    /* Index option Tempo */
    BBRHCJB, /* Heures Creuses Jours Bleus   9 Wh  */
    BBRHPJB, /* Heures Pleines Jours Bleus   9 Wh  */
    BBRHCJW, /* Heures Creuses Jours Blancs  9 Wh  */
    BBRHPJW, /* Heures Pleines Jours Blancs  9 Wh  */
    BBRHCJR, /* Heures Creuses Jours Rouges  9 Wh  */
    BBRHPJR, /* Heures Pleines Jours Rouges  9 Wh  */
    DEMAIN,  /* Couleur du lendemain         4     */
#endif
    PTEC,    /* Période Tarifaire en cours   4     */
    IINST,   /* Intensité Instantanée        3 A   */
    ADPS,    /* Avertissement de Dépassementde Puissance Souscrite 3 A*/
    IMAX,    /* Intensité maximale Appelée   3 A   */
    PAPP,    /* Puissance apparente          5 VA  */
    HHPHC,   /* Horaire Heures Pleines Heures Creuses 1 */
    MOTDETAT,/* Mot d'état du compteur       6     */
#if( CBETM )
/* compteur «Bleu» électronique triphasé multitarif (CBETM) */
/* Intensité Instantanée pour les 3 phases 1, 2 et 3 */
    IINST1,  /* phase 1      3 */
    IINST2,  /* phase 2      3 */
    IINST3,  /* phase 3      3 */
/* Intensité maximale par phase 1, 2 et 3 */
    IMAX1,   /* phase 1      3 */
    IMAX2,   /* phase 2      3 */
    IMAX3,   /* phase 3      3 */
    PMAX,    /* Puissance maximale triphasée atteinte   5 W */
#endif
#if( CBETM_SHORT )
//trames courtes du compteur «Bleu» électronique triphasé multitarif (CBETM)
/* Avertissement de Dépassement d'intensité de réglage par phase */
    ADIR1, /* phase 1 */
    ADIR2, /* phase 2 */
    ADIR3, /* phase 3 */
#endif
#if( C_GAZ_AUTRE )
    GAZ,   /* Index gaz                    7   dal */
    AUTRE, /* Index du troisième compteur  7   dal */
#endif
    /* Invalid option*/
    INVALID
};


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/
extern T_TIC_INFO TIC_info;


/************************************************************************
* FUNCTIONS PROTOTYPE *
************************************************************************/
void teleinfo_Init(void);
void teleinfo_TIC_reset_values(void);
int teleinfo_rawByte_receive(u8 rawByte);
void Teleinfo_Mgt(void);
unsigned char TIC_check_frame(unsigned char str[30], unsigned char *labelCode, unsigned long int *valueCode);
unsigned char TIC_set_option(unsigned char option, unsigned char *str, unsigned char len);
unsigned char TIC_get_option(unsigned char option, unsigned char *str, unsigned char len);
unsigned long int Ascii2Int(unsigned char *str, unsigned char len);
unsigned char TIC_FillInInfo(unsigned char labelCode, unsigned int val);
unsigned char TIC_getLabelCode(unsigned char str[5]);
unsigned char TIC_CRC(unsigned char *str);
void Teleinfo_USART_Init(USART_TypeDef* USARTx);


#endif /* TELEINFO_H */
