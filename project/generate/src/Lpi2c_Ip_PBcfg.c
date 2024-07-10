/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : LPI2C
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 3.0.0
* Build Version : S32K3_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
* Copyright 2020 - 2023 NXP Semiconductors
*
* NXP Confidential. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup LPI2C_DRIVER_CONFIGURATION Lpi2c Driver Configurations
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Lpi2c_Ip_PBcfg.h"
#include "Mcal.h"

#if (STD_ON == LPI2C_IP_DMA_FEATURE_AVAILABLE)
#include "Dma_Ip_Cfg.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPI2C_IP_PBCFG_VENDOR_ID_C                     43
#define LPI2C_IP_PBCFG_MODULE_ID_C                     255
#define LPI2C_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define LPI2C_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define LPI2C_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define LPI2C_IP_PBCFG_SW_MAJOR_VERSION_C              3
#define LPI2C_IP_PBCFG_SW_MINOR_VERSION_C              0
#define LPI2C_IP_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and I2c header file are of the same vendor */
#if (LPI2C_IP_PBCFG_VENDOR_ID_C != LPI2C_IP_PBCFG_VENDOR_ID)
    #error "Lpi2c_Ip_PBcfg.c and Lpi2c_Ip_PBcfg.h have different vendor ids"
#endif
/* Check if current file and I2c header file are of the same Autosar version */
#if ((LPI2C_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C != LPI2C_IP_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (LPI2C_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C != LPI2C_IP_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (LPI2C_IP_PBCFG_AR_RELEASE_REVISION_VERSION_C != LPI2C_IP_PBCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Lpi2c_Ip_PBcfg.c and Lpi2c_Ip_PBcfg.h are different"
#endif
/* Check if current file and I2c header file are of the same Software version */
#if ((LPI2C_IP_PBCFG_SW_MAJOR_VERSION_C != LPI2C_IP_PBCFG_SW_MAJOR_VERSION) || \
     (LPI2C_IP_PBCFG_SW_MINOR_VERSION_C != LPI2C_IP_PBCFG_SW_MINOR_VERSION) || \
     (LPI2C_IP_PBCFG_SW_PATCH_VERSION_C != LPI2C_IP_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lpi2c_Ip_PBcfg.c and Lpi2c_Ip_PBcfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if (STD_ON == LPI2C_IP_DMA_FEATURE_AVAILABLE)
    /* Check if current file and Dma_Ip_Cfg header file are of the same Autosar version */
        #if ((LPI2C_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DMA_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
             (LPI2C_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C != DMA_IP_CFG_AR_RELEASE_MINOR_VERSION))
            #error "AutoSar Version Numbers of Lpi2c_Ip_PBcfg.c and Dma_Ip_Cfg.h are different"
        #endif
    #endif /* LPI2C_IP_DMA_FEATURE_AVAILABLE */
    /* Check if current file and Mcal.h header file are of the same Autosar version */
    #if ((LPI2C_IP_PBCFG_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (LPI2C_IP_PBCFG_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Lpi2c_Ip_PBcfg.c and Mcal.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

#define I2C_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "I2c_MemMap.h"


const Lpi2c_Ip_SlaveConfigType I2c_Lpi2cSlaveChannel0 =
{
    /* Slave Address */
    32U,
    /* 10 bit address */
    FALSE,
    /* Slave listening */
    TRUE,
    /* Operating Mode*/
    LPI2C_STANDARD_MODE,
    /* Transfer type */
    LPI2C_USING_INTERRUPTS,
    /* SDA Glitch Filter */
    0U,
    /* SCL Glitch FIlter */
    0U,
    /* Dma Tx channel */
    0,
    /* Dma Rx channel */
    0,
    /* Slave Callback */
    i2c_slave_callback,
    /* Slave Callback Param */
    0,
    /* Slave State index*/
    0
};

static const Lpi2c_Ip_BaudRateType baudrateParams1 =
{
    LPI2C_MASTER_PRESC_DIV_128, /* Prescaler */
    1U,  /* Clock HI period */
    3U,  /* Clock LO period */
    0U, /* Setup Delay */
    0U,  /* Data Valid */
    1U, /* Clock High HS */
    3U, /* Clock Low HS*/
    2U, /* Setup Delay HS */
    1U /* Data Valid HS */
};

const Lpi2c_Ip_MasterConfigType I2c_Lpi2cMasterChannel1 =
{
    /* Slave address */
    40U,
    /*10-bit address */
    FALSE,
    /* Operating Mode */
    LPI2C_STANDARD_MODE,
    /* Baudrate parameters */
    &baudrateParams1,
    /* Pin Low Timeout */
    0,
    /* Bus Idle Timeout */
    0,
    /* Glitch Filter SDA */
    0,
    /* Glitch Filter SDA */
    0,
    /* Master code */
    0U,
    /* Transfer Type */
    LPI2C_USING_INTERRUPTS,
    /* Dma Tx channel */
    0,
    /* Dma Rx channel */
    0,
    /* Master Callback */
    i2c_master_callback,
    /* I2c Master Callback Parameter */
    1,
    /*  Master State index */
    0
};




#define I2C_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "I2c_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                  LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

