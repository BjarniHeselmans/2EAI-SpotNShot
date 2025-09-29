## mmWave output processed data over the Data UART COM port: (mss_main.c):

main() => MmwDemo_initTask() => Register a report callback function for the DPM (dpmInitCfg.reportFxn)
dpmInitCfg.reportFxn = MmwDemo_DPC_ObjectDetection_reportFxn() => MmwDemo_handleObjectDetResult() (On reportType == DPM_Report_NOTIFY_DPC_RESULT) => MmwDemo_transmitProcessedOutput()

