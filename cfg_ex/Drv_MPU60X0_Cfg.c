/*
 * Drv_MPU6000_Cfg.c
 *
 *  Created on: Mar 19, 2025
 *      Author: tmx37
 */

  /******************************************************************************
 * Includes
 *******************************************************************************/

 #include "Drv_MPU60X0_Cfg.h"
 #include "Drv_MPU60X0.h"

 /******************************************************************************
  * Module Preprocessor Constants
  ******************************************************************************/

 /******************************************************************************
  * Module Preprocessor Macros
  ******************************************************************************/

 /******************************************************************************
  * Function Prototypes Private
  ******************************************************************************/

 /******************************************************************************
  * Module Variable Definitions
  ******************************************************************************/
 
  static Drv_MPU60X0_Config_t mConfigData; // Configuration Istance
  static Drv_MPU60X0_Settings_t mSettingsData; // Settings Istance

 /******************************************************************************
  * Function Definitions Private
  ******************************************************************************/

  uint32_t MockWriteRegister(uint32_t I2cInst, uint8_t DevAddr, uint8_t RegNdx, uint8_t *pDataBuffer, uint32_t DataSize);
  uint32_t MockReadRegister(uint32_t I2cInst, uint8_t DevAddr, uint8_t RegNdx, uint8_t *pDataBuffer, uint32_t DataSize);
  uint32_t MockIsDeviceReady(uint32_t I2cInst, uint8_t DevAddr, uint8_t nTrials);
  uint32_t MockMasterTransmit(uint32_t I2cInst, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
  uint32_t MockMasterReceive(uint32_t I2cInst, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
  void MockDelay(uint32_t Delay);


 /******************************************************************************
  * Function Definitions Public
  ******************************************************************************/

  GenUtl_Err_t  Drv_MPU60X0Cfg_Init(void)
  {
    GenUtl_Err_t ErrCode;
    mConfigData.I2CInst = 0;
    mConfigData.pfWriteRegistersI2cCB = MockWriteRegister;
    mConfigData.pfReadRegisterI2cCB = MockReadRegister;
    mConfigData.pfIsDeviceReadyI2cCB = MockIsDeviceReady;
    mConfigData.pfMasterTransmitCB = MockMasterTransmit;
    mConfigData.pfMasterReceiveCB = MockMasterReceive;
    mConfigData.pfDelayCB = MockDelay;

    // Refer to MPU_60X0_REGISTER_MAP documentation to compile those settings 
    mSettingsData.RESET_STARTUP = DRV_MPU60X0_S_PWR_MGMT_1_DEVICE_RESET + DRV_MPU60X0_S_PWR_MGMT_1_SLEEP;
    mSettingsData.PWE_MGMT_1_SETTINGS = DRV_MPU60X0_S_PWR_MGMT_1_TEMP_DIS + DRV_MPU60X0_S_PWR_MGMT_1_CLKSEL_PLL_X_GYRO_REF;
    mSettingsData.DLPF_FSYNC_SETTINGS = DRV_MPU60X0_S_DLPF_CFG_20HZ_8MS + DRV_MPU60X0_S_EXT_SYNC_INPUT_DISABLED;
    mSettingsData.GYRO_SETTINGS = DRV_MPU60X0_S_FS_SEL_250;
    mSettingsData.FS_SEL = DRV_MPU60X0_S_FS_SEL_250;
    mSettingsData.ACCEL_SETTINGS = DRV_MPU60X0_S_AFS_SEL_2G;
    mSettingsData.AFS_SEL = DRV_MPU60X0_S_AFS_SEL_2G;
    mSettingsData.SMPRT_DIVIDER = 0; // Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) 

    ErrCode = Drv_MPU60X0_Init(&mConfigData, &mSettingsData);
    return ErrCode;
  }

  uint32_t MockWriteRegister(uint32_t I2cInst, uint8_t DevAddr, uint8_t RegNdx, uint8_t *pDataBuffer, uint32_t DataSize)
  {
    return OUT_OK;
  }
  uint32_t MockReadRegister(uint32_t I2cInst, uint8_t DevAddr, uint8_t RegNdx, uint8_t *pDataBuffer, uint32_t DataSize)
  {
    return OUT_OK;
  }
  uint32_t MockIsDeviceReady(uint32_t I2cInst, uint8_t DevAddr, uint8_t nTrials)
  {
    return OUT_OK;
  }
  uint32_t MockMasterTransmit(uint32_t I2cInst, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
  {
    return OUT_OK;
  }
  uint32_t MockMasterReceive(uint32_t I2cInst, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
  {
    return OUT_OK;
  }
  void MockDelay(uint32_t Delay)
  {
    (void)Delay;
  }