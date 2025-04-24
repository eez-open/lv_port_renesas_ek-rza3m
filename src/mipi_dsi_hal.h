/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/
#ifndef MIPI_DSI_HAL_H_
#define MIPI_DSI_HAL_H_

#include <r_mipi_dsi.h>
#include "hal_data.h"

extern const mipi_dsi_cfg_t g_mipi_dsi_cfg;

//#define MIPI_DSI_TIMING_80
//#define MIPI_DSI_TIMING_125
//#define MIPI_DSI_TIMING_250
//#define MIPI_DSI_TIMING_360
//#define MIPI_DSI_TIMING_720
//#define MIPI_DSI_TIMING_OVER720

#if defined(MIPI_DSI_TIMING_80)
#define T_INIT          (0x137B9)
#define TCLK_PREPARE    (0x8)
#define THS_PREPARE     (0xD)
#define TCLK_ZERO       (0x21)
#define TCLK_PRE        (0x18)
#define TCLK_POST       (0x5E)
#define TCLK_TRAIL      (0xA)
#define THS_ZERO        (0x17)
#define THS_TRAIL       (0x11)
#define THS_EXIT        (0xD)
#define TLPX            (0x6)
#elif defined(MIPI_DSI_TIMING_125)
#define T_INIT          (0x137B9)
#define TCLK_PREPARE    (0x8)
#define THS_PREPARE     (0xC)
#define TCLK_ZERO       (0x21)
#define TCLK_PRE        (0xF)
#define TCLK_POST       (0x5E)
#define TCLK_TRAIL      (0xA)
#define THS_ZERO        (0x17)
#define THS_TRAIL       (0x11)
#define THS_EXIT        (0xD)
#define TLPX            (0x6)
#elif defined(MIPI_DSI_TIMING_250)
#define T_INIT          (0x137B9)
#define TCLK_PREPARE    (0x8)
#define THS_PREPARE     (0xC)
#define TCLK_ZERO       (0x21)
#define TCLK_PRE        (0xD)
#define TCLK_POST       (0x5E)
#define TCLK_TRAIL      (0xA)
#define THS_ZERO        (0x17)
#define THS_TRAIL       (0x10)
#define THS_EXIT        (0xD)
#define TLPX            (0x6)
#elif defined(MIPI_DSI_TIMING_360)
#define T_INIT          (0x137B9)
#define TCLK_PREPARE    (0x8)
#define THS_PREPARE     (0xA)
#define TCLK_ZERO       (0x21)
#define TCLK_PRE        (0x4)
#define TCLK_POST       (0x23)
#define TCLK_TRAIL      (0x7)
#define THS_ZERO        (0x10)
#define THS_TRAIL       (0x9)
#define THS_EXIT        (0xD)
#define TLPX            (0x6)
#elif defined(MIPI_DSI_TIMING_720)
#define T_INIT          (0x137B9)
#define TCLK_PREPARE    (0x8)
#define THS_PREPARE     (0x9)
#define TCLK_ZERO       (0x21)
#define TCLK_PRE        (0x4)
#define TCLK_POST       (0x23)
#define TCLK_TRAIL      (0x7)
#define THS_ZERO        (0x10)
#define THS_TRAIL       (0x9)
#define THS_EXIT        (0xD)
#define TLPX            (0x6)
#elif defined(MIPI_DSI_TIMING_OVER720)
#define T_INIT          (0x137B9)
#define TCLK_PREPARE    (0x8)
#define THS_PREPARE     (0x9)
#define TCLK_ZERO       (0x21)
#define TCLK_PRE        (0x4)
#define TCLK_POST       (0x23)
#define TCLK_TRAIL      (0x7)
#define THS_ZERO        (0x10)
#define THS_TRAIL       (0x9)
#define THS_EXIT        (0xD)
#define TLPX            (0x6)
#endif

extern const mipi_dsi_instance_t g_mipi_dsi0;



#endif /* MIPI_DSI_HAL_H_ */
