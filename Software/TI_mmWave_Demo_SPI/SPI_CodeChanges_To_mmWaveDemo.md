# SPI lines of code added:

## SPI.c
### Structs:
The documentation of the SPI_init() function states that a persistent instance of the SPI_Config struct needs to exist before calling SPI_init().
The user does not need to do this as a global instance already exist:
- Declaration: extern const SPI_Config SPI_config[];
- Definition: spi_xwr16xx.c => This definition is allowed to be modified by the user.

## mss_main.c:
### Includes:
- #include <ti/drivers/spi/SPI.h> (See Linker instructions in this git folder for instructions on adding a library in Code Composer Studio)
- #include <ti/demo/xwr16xx/mmw/include/mmw_config_with_SPI_niels.h> (Replace the original mmw_config.h SDK file)

### Functions:
MmwDemo_initTask():
- SPI_Params spiParams;

- SPI_init()
- SPI_Params_init()
- Initialize SPI_Params:
	- spiParams.mode = SPI_MASTER;
	- spiParams.u.masterParams.bitRate    = gMmwMssMCB.cfg.platformCfg.spiBitRate;
	- spiParams.u.masterParams.numSlaves  = 1;
	- spiParams.u.masterParams.slaveProf[0].chipSelect = 0;
    	- spiParams.u.masterParams.slaveProf[0].ramBufLen  = MIBSPI_RAM_MAX_ELEM / 2; => TO DO: Check the required ram length for the spot and shoot app
    	- spiParams.dmaEnable = 0; // SPI will be used in blocking/polling mode
    	- // spiParams.dmaHandle = gDmaHandle;
	- // spiParams.u.masterParams.slaveProf[0].dmaCfg.txDmaChanNum = 1U;          
    	- // spiParams.u.masterParams.slaveProf[0].dmaCfg.rxDmaChanNum = 0U;
	- spiParams.frameFormat  = SPI_POL0_PHA0;
    	- spiParams.pinMode      = SPI_PINMODE_4PIN_CS; => Possible to change to 3 pin mode without CS because only one slave will be used
    	- spiParams.shiftFormat  = SPI_MSB_FIRST;
	- spiParams.dataSize     = 8; // SPI Data frame size
    	- spiParams.transferMode = SPI_MODE_BLOCKING; // SPI polling mode: DMA or interrupt based SPI is not needed because no other tasks 
                                                      //                   than the radar data collection/processing and SPI transfer will be done in this application.
- SPI_open()

- SPI Test transfer after initialization is done:
    /* Initialize test data */
    uint8_t radarDataBuffer[10]; 
    uint8_t test_index = 0;
    for(test_index = 0; test_index < 10; ++test_index)
    {
        radarDataBuffer[test_index] = test_index;
    }

    /* Start SPI transaction of test data */
    SPI_Transaction spiTransaction;
    spiTransaction.count = 10;
    spiTransaction.txBuf = radarDataBuffer;
    spiTransaction.rxBuf = NULL;
    spiTransaction.slaveIndex = 0;  
 
    bool ret = SPI_transfer(gMmwMssMCB.spiHandle, &spiTransaction);
    if (ret == false) 
    {
        System_printf("Unsuccessful SPI transfer test!\n");
    }

MmwDemo_platformInit():
- Setup the PINMUX to bring out the MibSpiA:
    - CLK:
    	- Pinmux_Set_OverrideCtrl(SOC_XWR16XX_PINE13_PADAF, PINMUX_OUTEN_RETAIN_HW_CTRL, PINMUX_INPEN_RETAIN_HW_CTRL);
    	- Pinmux_Set_FuncSel(SOC_XWR16XX_PINE13_PADAF, SOC_XWR16XX_PINE13_PADAF_SPIA_CLK);
    - MOSI:
    	- Pinmux_Set_OverrideCtrl(SOC_XWR16XX_PIND13_PADAD, PINMUX_OUTEN_RETAIN_HW_CTRL, PINMUX_INPEN_RETAIN_HW_CTRL);
    	- Pinmux_Set_FuncSel(SOC_XWR16XX_PIND13_PADAD, SOC_XWR16XX_PIND13_PADAD_SPIA_MOSI);
    - MISO:
    	- Pinmux_Set_OverrideCtrl(SOC_XWR16XX_PINE14_PADAE, PINMUX_OUTEN_RETAIN_HW_CTRL, PINMUX_INPEN_RETAIN_HW_CTRL);
    	 - Pinmux_Set_FuncSel(SOC_XWR16XX_PINE14_PADAE, SOC_XWR16XX_PINE14_PADAE_SPIA_MISO);
    - Chip select:
    	- Pinmux_Set_OverrideCtrl(SOC_XWR16XX_PINC13_PADAG, PINMUX_OUTEN_RETAIN_HW_CTRL, PINMUX_INPEN_RETAIN_HW_CTRL);
    	- Pinmux_Set_FuncSel(SOC_XWR16XX_PINC13_PADAG, SOC_XWR16XX_PINC13_PADAG_SPIA_CSN);
    // - Host interrupt: Not needed i think ??
    //	 - Pinmux_Set_OverrideCtrl(SOC_XWR16XX_PINP13_PADAA, PINMUX_OUTEN_RETAIN_HW_CTRL, PINMUX_INPEN_RETAIN_HW_CTRL);
    //	 - Pinmux_Set_FuncSel(SOC_XWR16XX_PINP13_PADAA, SOC_XWR16XX_PINP13_PADAA_SPI_HOST_INTR);

- config->spiBitRate = 1000000; // TO DO: need to check if the bit rate equals the actual frequency (1MHz)

## MmwDemo_handleObjectDetResult():
- MmwDemo_transmitProcessedOutput(gMmwMssMCB.loggingUartHandle, gMmwMssMCB.spiHandle, dpcResults, &currSubFrameStats->outputStats);

MmwDemo_transmitProcessedOutput(): (Declaration arguments)
- SPI_Handle spiHandle

MmwDemo_transmitProcessedOutput(): (Definition)
    /* Send the number of detected objects (stored in the first tlv length variable) over SPI */
    SPI_Transaction spiTransaction;
    spiTransaction.count = 1;
    spiTransaction.txBuf = &(tl[tlvIdx].length); // tl[0].length: Number of detected objects
    spiTransaction.rxBuf = NULL;
    spiTransaction.slaveIndex = 0;  
    
    bool ret = SPI_transfer(gMmwMssMCB.spiHandle, &spiTransaction);
    if (false) 
    {
        System_printf("Unsuccessful SPI transfer test!\n");
    }

## mmw_config.h => mmw_config_with_SPI_niels.h
Created a copy of this header to leave the original SDK header file unchanged: C:\ti\mmwave_sdk_03_06_02_00-LTS\packages\ti\demo\xwr16xx\mmw\include\mmw_config_with_SPI_niels.h

### Structs:
- MmwDemo_platformCfg:
	- uint32_t spiBitRate;

## mmw_mss.h
### Includes:
- #include <ti/drivers/spi/SPI.h> (See Linker instructions in this git folder for instructions on adding a library in Code Composer Studio)
- #include <ti/demo/xwr16xx/mmw/include/mmw_config_with_SPI_niels.h> (Replace the original mmw_config.h SDK file)

### Structs:
- gMmwMssMCB struct:
	- SPI_Handle spiHandle;



## Source:
- SDK mmWave Demo:    C:\ti\mmwave_sdk_03_06_02_00-LTS\packages\ti\demo\xwr16xx\mmw 
- SDK spi driver:     file:///C:/ti/mmwave_sdk_03_06_02_00-LTS/packages/ti/drivers/spi/docs/doxygen/html/index.html
- SDK spi driver API: file:///C:/ti/mmwave_sdk_03_06_02_00-LTS/packages/ti/drivers/spi/docs/doxygen/html/group___s_p_i___d_r_i_v_e_r___e_x_t_e_r_n_a_l___f_u_n_c_t_i_o_n.html#ga9c3dd1748332fd6e31c79a6538a71642
- SDK spi test code:  C:\ti\mmwave_sdk_03_06_02_00-LTS\packages\ti\drivers\spi\test\xwr16xx\main.c



## Dev Notes:
- TO DO: Check if all references to the original SDK mmw_config.h are replaced by a reference to <ti/demo/xwr16xx/mmw/include/mmw_config_with_SPI_niels.h>