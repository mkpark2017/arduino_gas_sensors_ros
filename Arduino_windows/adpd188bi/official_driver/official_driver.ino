#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "AdpdDrv.h"


/* Macros -------------------------------------------------------------------*/

#define debug(M, ...)  {_SBZ[0] = 0; \
                        snprintf(_SBZ, BUF_SIZE, "" M "", ##__VA_ARGS__); \
                        Serial.print(_SBZ);}

/* Private define ---------------------------------------------------------- */

uint32_t gnAdpdTimeCurVal = 0;

uint8_t gnAdpdDataReady = 0;



/* Private variables --------------------------------------------------------*/

#define BUF_SIZE (256)

char _SBZ[BUF_SIZE]; // used by 'debug'



uint32_t dcfg_org_188[] = {

  0x00120014,

  0x00150330,

  0x00183FFF,

  0x00193FFF,

  0x001A1F00,

  0x001B1F00,

  0x001E3FFF,

  0x001F3FFF,

  0x00201F00,

  0x00211F00,

  0x00340000,

  0x00060000,

  0x001130A0,

  0x00140555,

  0x00221030,

  0x00233036,

  0x00241030,

  0x0025630C,

  0x00300220,

  0x0031020f,

  0x00350220,

  0x0036020f,

  0x00391af8,

  0x003B1af8,

    0x003C7006,  

  0x00421C35,

  0x0043ADA5,

  0x00441C34,

  0x0045ADA5,

  0x004E7040,

  0x00540AA0,

  0x003F0320,

  0x00580000,

  0x00590808,

  0x005A0010,

  0xFFFFFFFF,

};



/* Private function prototypes ----------------------------------------------*/

void HW_Global_Init(void);

void LoadDefaultConfig(uint32_t *cfg);

void VerifyDefaultConfig(uint32_t *cfg);

void AdpdDriverBringUp(uint8_t nSlotA, uint8_t nSlotB);

void AdpdFifoCallBack(void);



void SystemClock_Config();

void HAL_Init();

void GPIO_Init();

void UART_Init();

void SPI_Init();

void I2C_Init();

void TIM_Init();

void ADP_init();

void MCU_HAL_Delay(uint32_t);

uint32_t MCU_HAL_GetTick();



uint16_t AdpdRxBufferInsertData(uint32_t tcv);



/* Private function prototypes --------------------------------------------- */



uint16_t AppReadAdpdDataBuffer(ADPDData_t *rxData, uint32_t *time);



/**

  *  @brief    Callback function.

  *  @param    None

  *  @retval   None

*/

void AdpdFifoCallBack(void)

{

  /* Read the timestamp when the interrupt comes */

  gnAdpdTimeCurVal = MCU_HAL_GetTick();

  /* Set gnAdpdDataReady to 1 to indicate that the data and timestamp is ready */

  gnAdpdDataReady = 1;

}



/**

                                 * Flow diagram of the code *



                                 ----------------------------

                                 | Hardware initializations |

                                 ----------------------------

                                             |

                                             |

                                 ----------------------------

                                 |  Data ready callback     |

                                 ----------------------------

                                             |

                                             |

                                 ----------------------------

                                 |Soft reset the ADPD device|

                                 |Initialize the ADPD driver|

                                 ----------------------------

                                             |

                                             |

                                 ----------------------------

                                 | Load the default config  |

                                 | and verify it            |

                                 ----------------------------

                                             |

                                             |

                                 ----------------------------

                                 | Write standard value of  |

                                 | clock registers          |

                                 ----------------------------

                                             |

                                             |

                                 ----------------------------

                             --->|     Driver bring up      |

                             |   ----------------------------

                             |               |

                             |               |

                             |---------------|





*/



/**

  *  @brief    Main program.

  *  @param    None

  *  @retval   None

*/

void setup(){

  /* Hardware initializations */

  HW_Global_Init();



  debug("Start\r\n");



  /* Register data ready callback */

  AdpdDrvDataReadyCallback(AdpdFifoCallBack);



  /* Soft reset the ADPD device */

  AdpdDrvSoftReset();



  /* Initialize the ADPD driver*/

  AdpdDrvOpenDriver();



  /* Load default configuration parameters */

  LoadDefaultConfig(dcfg_org_188);

  /* Read default configuration parameters from the device registers and verify */

  VerifyDefaultConfig(dcfg_org_188);



  /* Write standard value of clock registers */

  AdpdDrvRegWrite(0x004B, 0x2695);

  AdpdDrvRegWrite(0x004D, 0x4272);

  /* Driver bring up with 16-bits output data and 8 channel mode */

  AdpdDriverBringUp(ADPDDrv_4CH_16, ADPDDrv_4CH_16);

}



/**

  *  @brief    Hardware Initialization.

  *  @param    None

  *  @retval   None

*/

void HW_Global_Init()

{



  /* HAL initializations such as enabling system tick and low level hardware initialization.*/

  HAL_Init();

  /* Configure the system clock to 26 Mhz */

  SystemClock_Config();

  /* Initialize the GPIO. Should be called before I2C_Init() */

  GPIO_Init();

  /* Initialize the UART */

  UART_Init();

  /* Initialize the I2C. Should be called after GPIO_Init() */

  I2C_Init();



  SPI_Init();

  /* Configure the voltage regulators in proper mode */

  ADP_init();

}



/**

  *  @brief    Load ADPD default configuration

  *  @param    uint32_t *cfg

  *  @retval   None

*/

void LoadDefaultConfig(uint32_t *cfg)

{

  uint8_t regAddr, i;

  uint16_t regData;

  if (cfg == 0) {

    return;

  }

  /* Clear the FIFO */

  AdpdDrvRegWrite(0x10, 0);

  AdpdDrvRegWrite(0x5F, 1);

  AdpdDrvRegWrite(0x00, 0x80FF);

  AdpdDrvRegWrite(0x5F, 0);

  i = 0;

  while (1) {

    /* Read the address and data from the config */

    regAddr = (uint8_t)(cfg[i] >> 16);

    regData = (uint16_t)(cfg[i]);

    i++;

    if (regAddr == 0xFF) {

      break;

    }

    /* Load the data into the ADPD registers */

    if (AdpdDrvRegWrite(regAddr, regData) != ADPDDrv_SUCCESS) {

      break;

    }

  }

}



/**

  *  @brief    Read default configuration parameters to verify

  *  @param    uint32_t *cfg

  *  @retval   None

*/

void VerifyDefaultConfig(uint32_t *cfg)

{

  uint16_t def_val;

  uint8_t  i;

  uint8_t  regAddr;

  uint16_t regData;

  if (cfg == 0) {

    return;

  }

  i = 0;

  /* Read the address and data from the config */

  regAddr = (uint8_t)(cfg[0] >> 16);

  def_val = (uint16_t)(cfg[0]);

  /* Read the data from the ADPD registers and verify */

  while (regAddr != 0xFF) {

    if (AdpdDrvRegRead(regAddr, &regData) != ADPDDrv_SUCCESS) {

      debug("DCFG: Read Error reg(%0.2x)\n", regAddr);

      return;

    } else if (regData != def_val) {

      debug("DCFG: Read mismatch reg(%0.2x) (%0.2x != %0.2x)\n",

            regAddr, def_val, regData);

      return;

    }

    i++;

    regAddr = (uint8_t)(cfg[i] >> 16);

    def_val = (uint16_t)(cfg[i]);

  }

}



/**

  *  @brief  ADPD Driver bring up.

  *  @param  uint8_t nSlotA

  *  @param  uint8_t nSlotB

  *  @retval None

*/

void AdpdDriverBringUp(uint8_t nSlotA, uint8_t nSlotB)

{

  uint32_t LoopCnt;

  uint16_t nRetValue = 0;

  uint16_t nAdpdFifoLevelSize = 0, nAdpdDataSetSize;

  uint8_t value[16] = {0};

    uint8_t nLoopLim;



  /* Set the slot modes for slot A and slot B */

  AdpdDrvSetSlot(nSlotA, nSlotB);

        /* Set the device operation to sample mode. The data can be collected now */

  AdpdDrvSetOperationMode(ADPDDrv_MODE_SAMPLE);

        nLoopLim = nAdpdDataSetSize = 16;

  while (1) {

    /* Check if the data is ready */

    if(gnAdpdDataReady)  {

      gnAdpdDataReady = 0;

      /* Read the size of the data available in the FIFO */

      AdpdDrvGetParameter(ADPD_FIFOLEVEL, &nAdpdFifoLevelSize);

      /* Read the data from the FIFO and print them */

      while (nAdpdFifoLevelSize >= nAdpdDataSetSize) {

        nRetValue = AdpdDrvReadFifoData(&value[0], nAdpdDataSetSize);

        if (nRetValue == ADPDDrv_SUCCESS) {

          for (LoopCnt = 0; LoopCnt < nLoopLim; LoopCnt += 2)

            /* Byte swapping is needed to print ADPD data in proper format */

            debug("%u ", (value[LoopCnt] << 8) | value[LoopCnt + 1]);

          debug("%u\r\n", gnAdpdTimeCurVal);

          nAdpdFifoLevelSize = nAdpdFifoLevelSize - nAdpdDataSetSize;

        }

      }

    }

  }

}



void loop() {
  // put your main code here, to run repeatedly:

}
