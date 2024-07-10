/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7 
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_AUTOSAR_4_4_-_R21-11_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file      Tspc_Port_Ip_Cfg.h
*
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Tspc_Port_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define TSPC_PORT_IP_VENDOR_ID_CFG_C                       43
#define TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C        4
#define TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C        7
#define TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C     0
#define TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_C                3
#define TSPC_PORT_IP_SW_MINOR_VERSION_CFG_C                0
#define TSPC_PORT_IP_SW_PATCH_VERSION_CFG_C                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are of the same vendor */
#if (TSPC_PORT_IP_VENDOR_ID_CFG_C != TSPC_PORT_IP_VENDOR_ID_CFG_H)
    #error "Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C    != TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C    != TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C != TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are different"
#endif
/* Check if Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are of the same Software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_C != TSPC_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_SW_MINOR_VERSION_CFG_C != TSPC_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
    (TSPC_PORT_IP_SW_PATCH_VERSION_CFG_C != TSPC_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Tspc_Port_Ip_Cfg.c and Tspc_Port_Ip_Cfg.h are different"
#endif

/*==================================================================================================
                             LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                             LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                            LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                           LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL VARIABLES
==================================================================================================*/

/* clang-format off */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: M7_0}
- pin_list:
  - {pin_num: '172', peripheral: LPUART2, signal: lpuart2_rx, pin_signal: PTA8}
  - {pin_num: '171', peripheral: LPUART2, signal: lpuart2_tx, pin_signal: PTA9, direction: OUTPUT}
  - {pin_num: '102', peripheral: CAN0, signal: can0_rx, pin_signal: PTA6}
  - {pin_num: '100', peripheral: CAN0, signal: can0_tx, pin_signal: PTA7}
  - {pin_num: '97', peripheral: CAN1, signal: can1_rx, pin_signal: PTC9}
  - {pin_num: '98', peripheral: CAN1, signal: can1_tx, pin_signal: PTC8}
  - {pin_num: '88', peripheral: SIUL2, signal: 'gpio, 88', pin_signal: PTC24, direction: OUTPUT, InitValue: state_1}
  - {pin_num: '122', peripheral: SIUL2, signal: 'gpio, 119', pin_signal: PTD23, direction: OUTPUT, InitValue: state_1}
  - {pin_num: '121', peripheral: SIUL2, signal: 'gpio, 98', pin_signal: PTD2, direction: OUTPUT, InitValue: state_1}
  - {pin_num: '86', peripheral: SIUL2, signal: 'gpio, 85', pin_signal: PTC21, direction: OUTPUT, InitValue: state_1}
  - {pin_num: '30', peripheral: LPSPI1, signal: lpspi1_sck, pin_signal: PTA28, direction: OUTPUT}
  - {pin_num: '33', peripheral: LPSPI1, signal: lpspi1_sout, pin_signal: PTA30, direction: INPUT}
  - {pin_num: '6', peripheral: LPSPI1, signal: lpspi1_pcs0, pin_signal: PTA21, direction: OUTPUT}
  - {pin_num: '72', peripheral: LPSPI2, signal: lpspi2_pcs0, pin_signal: PTB25, direction: OUTPUT}
  - {pin_num: '80', peripheral: LPSPI2, signal: lpspi2_sck, pin_signal: PTB29, direction: OUTPUT}
  - {pin_num: '41', peripheral: LPI2C0, signal: lpi2c0_sda, pin_signal: PTD13, direction: INPUT/OUTPUT}
  - {pin_num: '40', peripheral: LPI2C0, signal: lpi2c0_scl, pin_signal: PTD14, direction: INPUT/OUTPUT}
  - {pin_num: '64', peripheral: LPI2C1, signal: lpi2c1_sda, pin_signal: PTD8, direction: INPUT/OUTPUT}
  - {pin_num: '63', peripheral: LPI2C1, signal: lpi2c1_scl, pin_signal: PTD9, direction: INPUT/OUTPUT}
  - {pin_num: '31', peripheral: LPSPI3, signal: lpspi3_pcs0, pin_signal: PTD17, direction: OUTPUT}
  - {pin_num: '7', peripheral: LPSPI3, signal: lpspi3_sck, pin_signal: PTD1, direction: OUTPUT}
  - {pin_num: '8', peripheral: LPSPI3, signal: lpspi3_sout, pin_signal: PTD0, direction: INPUT}
  - {pin_num: '10', peripheral: LPSPI3, signal: lpspi3_sin, pin_signal: PTE10, direction: OUTPUT}
  - {pin_num: '13', peripheral: LPSPI1, signal: lpspi1_pcs1, pin_signal: PTE4, direction: OUTPUT}
  - {pin_num: '84', peripheral: LPSPI2, signal: lpspi2_pcs1, pin_signal: PTC19, direction: OUTPUT}
  - {pin_num: '116', peripheral: eMIOS_0, signal: emios_0_ch_1_g, pin_signal: PTB13, direction: OUTPUT}
  - {pin_num: '114', peripheral: eMIOS_0, signal: emios_0_ch_2_g, pin_signal: PTB14, direction: OUTPUT}
  - {pin_num: '113', peripheral: eMIOS_0, signal: emios_0_ch_3_g, pin_signal: PTB15, direction: OUTPUT}
  - {pin_num: '112', peripheral: eMIOS_0, signal: emios_0_ch_4_g, pin_signal: PTB16, direction: OUTPUT}
  - {pin_num: '110', peripheral: eMIOS_0, signal: emios_0_ch_5_g, pin_signal: PTB17, direction: OUTPUT}
  - {pin_num: '160', peripheral: SIUL2, signal: 'gpio, 11', pin_signal: PTA11, direction: INPUT}
  - {pin_num: '162', peripheral: SIUL2, signal: 'gpio, 129', pin_signal: PTE1, direction: INPUT}
  - {pin_num: '153', peripheral: ADC2, signal: adc2_p3, pin_signal: PTE21}
  - {pin_num: '154', peripheral: ADC2, signal: adc2_p4, pin_signal: PTE22}
  - {pin_num: '156', peripheral: ADC2, signal: adc2_p5, pin_signal: PTE23}
  - {pin_num: '141', peripheral: SIUL2, signal: 'gpio, 70', pin_signal: PTC6, direction: INPUT}
  - {pin_num: '140', peripheral: SIUL2, signal: 'gpio, 71', pin_signal: PTC7, direction: INPUT}
  - {pin_num: '147', peripheral: SIUL2, signal: 'gpio, 130', pin_signal: PTE2, direction: INPUT}
  - {pin_num: '146', peripheral: SIUL2, signal: 'gpio, 134', pin_signal: PTE6, direction: INPUT}
  - {pin_num: '130', peripheral: LPSPI4, signal: lpspi4_sout, pin_signal: PTB9, direction: INPUT}
  - {pin_num: '129', peripheral: LPSPI4, signal: lpspi4_sck, pin_signal: PTB10, direction: OUTPUT}
  - {pin_num: '133', peripheral: LPSPI4, signal: lpspi4_pcs0, pin_signal: PTB8, direction: OUTPUT}
  - {pin_num: '137', peripheral: SIUL2, signal: 'gpio, 0', pin_signal: PTA0, direction: INPUT}
  - {pin_num: '135', peripheral: SIUL2, signal: 'gpio, 1', pin_signal: PTA1, direction: INPUT}
  - {pin_num: '124', peripheral: SIUL2, signal: 'gpio, 2', pin_signal: PTA2, direction: INPUT}
  - {pin_num: '123', peripheral: SIUL2, signal: 'gpio, 3', pin_signal: PTA3, direction: INPUT}
  - {pin_num: '42', peripheral: SIUL2, signal: 'gpio, 50', pin_signal: PTB18, direction: INPUT}
  - {pin_num: '43', peripheral: SIUL2, signal: 'gpio, 51', pin_signal: PTB19, direction: INPUT}
  - {pin_num: '44', peripheral: SIUL2, signal: 'gpio, 52', pin_signal: PTB20, direction: INPUT}
  - {pin_num: '45', peripheral: SIUL2, signal: 'gpio, 53', pin_signal: PTB21, direction: INPUT}
  - {pin_num: '11', peripheral: ADC1, signal: adc1_s19, pin_signal: PTE13}
  - {pin_num: '159', peripheral: SIUL2, signal: 'gpio, 12', pin_signal: PTA12, direction: INPUT}
  - {pin_num: '164', peripheral: SIUL2, signal: 'gpio, 154', pin_signal: PTE26, direction: INPUT}
  - {pin_num: '99', peripheral: CAN3, signal: can3_rx, pin_signal: PTC29}
  - {pin_num: '96', peripheral: CAN3, signal: can3_tx, pin_signal: PTC28}
  - {pin_num: '95', peripheral: SIUL2, signal: 'gpio, 32', pin_signal: PTB0, direction: OUTPUT, InitValue: state_1}
  - {pin_num: '94', peripheral: SIUL2, signal: 'gpio, 33', pin_signal: PTB1, direction: OUTPUT, InitValue: state_1}
  - {pin_num: '109', peripheral: eMIOS_0, signal: emios_0_ch_6_g, pin_signal: PTA17, direction: OUTPUT}
  - {pin_num: '117', peripheral: SIUL2, signal: 'gpio, 44', pin_signal: PTB12, direction: OUTPUT}
  - {pin_num: '163', peripheral: ADC1, signal: adc1_p2, pin_signal: PTE0}
  - {pin_num: '9', peripheral: ADC0, signal: adc0_p6, pin_signal: PTE11}
  - {pin_num: '75', peripheral: LPSPI2, signal: lpspi2_sout, pin_signal: PTB27, direction: INPUT}
  - {pin_num: '32', peripheral: SIUL2, signal: 'gpio, 29', pin_signal: PTA29, direction: INPUT}
  - {pin_num: '76', peripheral: SIUL2, signal: 'gpio, 60', pin_signal: PTB28, direction: INPUT}
  - {pin_num: '126', peripheral: SIUL2, signal: 'gpio, 43', pin_signal: PTB11, direction: INPUT}
  - {pin_num: '104', peripheral: SIUL2, signal: 'gpio, 135', pin_signal: PTE7, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* No registers that support TSPC were configured*/

/*==================================================================================================
                                      LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                           LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
