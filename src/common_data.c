/* generated common source file - do not edit */
#include "common_data.h"
/* MIPI PHY Macros */
#define MIPI_PHY_CLKSTPT   (161 + 1)
#define MIPI_PHY_CLKBFHT   (52 + 1)
#define MIPI_PHY_CLKKPT    (44 + 1)
#define MIPI_PHY_GOLPBKT   (49 + 3)

#define MIPI_PHY_TINIT     (79801)
#define MIPI_PHY_TCLKPREP  (8)
#define MIPI_PHY_THSPREP   (9)
#define MIPI_PHY_TCLKTRAIL (7)
#define MIPI_PHY_TCLKPOST  (35)
#define MIPI_PHY_TCLKPRE   (4)
#define MIPI_PHY_TCLKZERO  (33)
#define MIPI_PHY_THSEXIT   (13)
#define MIPI_PHY_THSTRAIL  (9)
#define MIPI_PHY_THSZERO   (16)
#define MIPI_PHY_TLPEXIT   (6)

/* MIPI PHY Structures */
const mipi_phy_b_timing_t g_mipi_phy0_timing =
{ .t_init = 0x3FFFF & (uint32_t)MIPI_PHY_TINIT, .t_clk_prep = (uint8_t)MIPI_PHY_TCLKPREP, .t_hs_prep =
          (uint8_t)MIPI_PHY_THSPREP,
  .t_clk_trail = (uint32_t)MIPI_PHY_TCLKTRAIL, .t_clk_post = (uint32_t)MIPI_PHY_TCLKPOST, .t_clk_pre =
          (uint32_t)MIPI_PHY_TCLKPRE,
  .t_clk_zero = (uint32_t)MIPI_PHY_TCLKZERO, .t_hs_exit = (uint32_t)MIPI_PHY_THSEXIT, .t_hs_trail =
          (uint32_t)MIPI_PHY_THSTRAIL,
  .t_hs_zero = (uint32_t)MIPI_PHY_THSZERO, .t_lp_exit = (uint32_t)MIPI_PHY_TLPEXIT, };

mipi_phy_b_ctrl_t g_mipi_phy0_ctrl;
const mipi_phy_b_cfg_t g_mipi_phy0_cfg =
{ .p_timing = &g_mipi_phy0_timing, };
/* Instance structure to use this module. */
const mipi_phy_instance_t g_mipi_phy0 =
{ .p_ctrl = &g_mipi_phy0_ctrl, .p_cfg = &g_mipi_phy0_cfg, .p_api = &g_mipi_phy };
mipi_dsi_b_instance_ctrl_t g_mipi_dsi0_ctrl;

const mipi_dsi_timing_t g_mipi_dsi0_timing =
{ .clock_stop_time = MIPI_PHY_CLKSTPT,
  .clock_beforehand_time = MIPI_PHY_CLKBFHT,
  .clock_keep_time = MIPI_PHY_CLKKPT,
  .go_lp_and_back = MIPI_PHY_GOLPBKT, };

const mipi_dsi_b_extended_cfg_t g_mipi_dsi0_extended_cfg =
        { .dsi_seq0.ipl = (24),
          .dsi_seq0.irq = DSI_INT_SEQ0_IRQn,

          .dsi_seq1.ipl = (24),
          .dsi_seq1.irq = DSI_INT_SEQ1_IRQn,

          .dsi_vin1.ipl = (24),
          .dsi_vin1.irq = DSI_INT_VIN1_IRQn,

          .dsi_rcv.ipl = (24),
          .dsi_rcv.irq = DSI_INT_RCV_IRQn,

          .dsi_ferr.ipl = (24),
          .dsi_ferr.irq = DSI_INT_FERR_IRQn,

          .dsi_ppi.ipl = (24),
          .dsi_ppi.irq = DSI_INT_PPI_IRQn,

          .dsi_rxie = R_MIPI_DSI_RXIER_BTAREQEND_Msk | R_MIPI_DSI_RXIER_LRXHTO_Msk | R_MIPI_DSI_RXIER_TATO_Msk
                  | R_MIPI_DSI_RXIER_RXRESP_Msk | R_MIPI_DSI_RXIER_RXEOTP_Msk | R_MIPI_DSI_RXIER_RXACK_Msk
                  | R_MIPI_DSI_RXIER_MLFERR_Msk | R_MIPI_DSI_RXIER_ECCERR_Msk | R_MIPI_DSI_RXIER_UEXPKTERR_Msk
                  | R_MIPI_DSI_RXIER_WCERR_Msk | R_MIPI_DSI_RXIER_CRCERR_Msk | R_MIPI_DSI_RXIER_IBERR_Msk
                  | R_MIPI_DSI_RXIER_RXOVFERR_Msk | R_MIPI_DSI_RXIER_PRESPTOERR_Msk | R_MIPI_DSI_RXIER_NORETERR_Msk
                  | R_MIPI_DSI_RXIER_MAXRPSZERR_Msk | R_MIPI_DSI_RXIER_ECCERR1B_Msk | R_MIPI_DSI_RXIER_RXAKE_Msk | 0x0,
          .dsi_ferrie = R_MIPI_DSI_FERRIER_HTXTO_Msk | R_MIPI_DSI_FERRIER_LRXHTO_Msk | R_MIPI_DSI_FERRIER_TATO_Msk
                  | R_MIPI_DSI_FERRIER_ERRESC_Msk | R_MIPI_DSI_FERRIER_ERRSYNESC_Msk | R_MIPI_DSI_FERRIER_ERRCTRL_Msk
                  | R_MIPI_DSI_FERRIER_ERRCLP0_Msk | R_MIPI_DSI_FERRIER_ERRCLP1_Msk | 0x0,
          .dsi_plie = 0x0,
          .dsi_vmie = R_MIPI_DSI_VICH1IER_VBUFUDF_Msk | R_MIPI_DSI_VICH1IER_VBUFOVF_Msk | 0x0,
          .dsi_sqch0ie = R_MIPI_DSI_SQCH0IER_AACTFIN_Msk | R_MIPI_DSI_SQCH0IER_ADESFIN_Msk
                  | R_MIPI_DSI_SQCH0IER_TXIBERR_Msk | R_MIPI_DSI_SQCH0IER_RXFATALERR_Msk
                  | R_MIPI_DSI_SQCH0IER_RXFAIL_Msk | R_MIPI_DSI_SQCH0IER_RXPKTDFAIL_Msk
                  | R_MIPI_DSI_SQCH0IER_RXCORERR_Msk | R_MIPI_DSI_SQCH0IER_RXAKE_Msk | 0x0,
          .dsi_sqch1ie = R_MIPI_DSI_SQCH1IER_AACTFIN_Msk | R_MIPI_DSI_SQCH1IER_ADESFIN_Msk
                  | R_MIPI_DSI_SQCH1IER_PKTBIGERR_Msk | R_MIPI_DSI_SQCH1IER_TXIBERR_Msk
                  | R_MIPI_DSI_SQCH1IER_RXFATALERR_Msk | R_MIPI_DSI_SQCH1IER_RXFAIL_Msk
                  | R_MIPI_DSI_SQCH1IER_RXPKTDFAIL_Msk | R_MIPI_DSI_SQCH1IER_RXCORERR_Msk
                  | R_MIPI_DSI_SQCH1IER_RXAKE_Msk | 0x0, };

const mipi_dsi_cfg_t g_mipi_dsi0_cfg =
{ .p_mipi_phy_instance = &g_mipi_phy0,

  .p_timing = &g_mipi_dsi0_timing,

  .sync_pulse = (0),
  .data_type = MIPI_DSI_VIDEO_DATA_24RGB_PIXEL_STREAM,
  .virtual_channel_id = 0,

  .vertical_active_lines = 1280,
  .vertical_sync_lines = 6,
  .vertical_back_porch = (21 - 6),
  .vertical_front_porch = (1317 - 1280 - 21),
  .vertical_sync_polarity = (DISPLAY_SIGNAL_POLARITY_HIACTIVE != DISPLAY_SIGNAL_POLARITY_HIACTIVE),

  .horizontal_active_lines = 720,
  .horizontal_sync_lines = 8,
  .horizontal_back_porch = (56 - 8),
  .horizontal_front_porch = (828 - 720 - 56),
  .horizontal_sync_polarity = (DISPLAY_SIGNAL_POLARITY_HIACTIVE != DISPLAY_SIGNAL_POLARITY_HIACTIVE),

  .video_mode_delay = 216, //FSP_NOT_DEFINED,

  .hsa_no_lp = ((0x0) & R_MIPI_DSI_VICH1SET0R_HSANOLP_Msk),
  .hbp_no_lp = ((0x0) & R_MIPI_DSI_VICH1SET0R_HBPNOLP_Msk),
  .hfp_no_lp = ((0x0) & R_MIPI_DSI_VICH1SET0R_HFPNOLP_Msk),

  .num_lanes = 4,
  .ulps_wakeup_period = 130,
  .continuous_clock = (1),

  .hs_tx_timeout = 0,
  .lp_rx_timeout = 0,
  .turnaround_timeout = 0,
  .bta_timeout = 0,
  .lprw_timeout = (0 << R_MIPI_DSI_PRESPTOLPSETR_PRESPTOLPR_Pos) | 0,
  .hsrw_timeout = (0 << R_MIPI_DSI_PRESPTOHSSETR_PRESPTOHSR_Pos) | 0,

  .max_return_packet_size = 1,
  .ecc_enable = (1),
  .crc_check_mask = (mipi_dsi_vc_t) (0x0),
  .scramble_enable = (0),

  .eotp_enable = (1),

  .p_extend = &g_mipi_dsi0_extended_cfg,
  .p_callback = mipi_dsi0_callback,
  .p_context = NULL, };

/* Instance structure to use this module. */
const mipi_dsi_instance_t g_mipi_dsi0 =
{ .p_ctrl = &g_mipi_dsi0_ctrl, .p_cfg = &g_mipi_dsi0_cfg, .p_api = &g_mipi_dsi };
mmu_instance_ctrl_t g_mmu_ctrl;
const mmu_cfg_t g_mmu_cfg;
/* Instance structure to use this module. */
const mmu_instance_t g_mmu =
{ .p_api = &g_mmu_on_mmu, .p_ctrl = &g_mmu_ctrl, .p_cfg = &g_mmu_cfg, };
/** IOPORT interface configuration for event link **/

ioport_event_group_output_t g_port_group_output_cfg[] =
{
{ .pin_select = (uint8_t) (uintptr_t) NULL, .operation = (ioport_event_output_operation_t) NULL }, };

ioport_event_group_input_t g_port_group_input_cfg[] =
{
{ .event_control = (ioport_event_control_t) NULL,
  .edge_detection = (ioport_event_detection_t) NULL,
  .overwrite_control = (ioport_event_control_t) NULL,
  .pin_select = (uintptr_t) NULL,
  .buffer_init_value = (uintptr_t) NULL }, };

ioport_event_single_t g_single_port_cfg[] =
{
{ .event_control = (ioport_event_control_t) NULL, .direction = (ioport_event_direction_t) NULL, .port_num =
          (uintptr_t) NULL,
  .operation = (ioport_event_output_operation_t) NULL, .edge_detection = (ioport_event_detection_t) NULL }, };

const ioport_extend_cfg_t g_ioport_cfg_extend =
{ .p_port_group_output_cfg = &g_port_group_output_cfg[0],
  .p_port_group_input_cfg = &g_port_group_input_cfg[0],
  .p_single_port_cfg = &g_single_port_cfg[0] };

ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl, .p_cfg = &g_bsp_pin_cfg, };
SemaphoreHandle_t _SemaphoreVsync;
#if 1
StaticSemaphore_t _SemaphoreVsync_memory;
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
EventGroupHandle_t g_i2c_event_group;
#if 1
StaticEventGroup_t g_i2c_event_group_memory;
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
SemaphoreHandle_t g_irq_binary_semaphore;
#if 1
StaticSemaphore_t g_irq_binary_semaphore_memory;
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
SemaphoreHandle_t g_mipi_binary_semaphore;
#if 1
StaticSemaphore_t g_mipi_binary_semaphore_memory;
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
void g_common_init(void)
{
    _SemaphoreVsync =
#if 1
            xSemaphoreCreateBinaryStatic (&_SemaphoreVsync_memory);
#else
                xSemaphoreCreateBinary();
                #endif
    if (NULL == _SemaphoreVsync)
    {
        rtos_startup_err_callback (_SemaphoreVsync, 0);
    }
    g_i2c_event_group =
#if 1
            xEventGroupCreateStatic (&g_i2c_event_group_memory);
#else
                xEventGroupCreate();
                #endif
    if (NULL == g_i2c_event_group)
    {
        rtos_startup_err_callback (g_i2c_event_group, 0);
    }
    g_irq_binary_semaphore =
#if 1
            xSemaphoreCreateBinaryStatic (&g_irq_binary_semaphore_memory);
#else
                xSemaphoreCreateBinary();
                #endif
    if (NULL == g_irq_binary_semaphore)
    {
        rtos_startup_err_callback (g_irq_binary_semaphore, 0);
    }
    g_mipi_binary_semaphore =
#if 1
            xSemaphoreCreateBinaryStatic (&g_mipi_binary_semaphore_memory);
#else
                xSemaphoreCreateBinary();
                #endif
    if (NULL == g_mipi_binary_semaphore)
    {
        rtos_startup_err_callback (g_mipi_binary_semaphore, 0);
    }
}
