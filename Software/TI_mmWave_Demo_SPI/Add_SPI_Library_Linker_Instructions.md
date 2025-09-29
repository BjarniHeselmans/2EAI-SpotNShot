# Add library to the linker configuration in Code Composer Studio:

## Add lib path:
- right click mss project -> Properties -> Build -> Tools -> Arm linker -> Add: -i"${COM_TI_MMWAVE_SDK_INSTALL_DIR}/packages/ti/drivers/spi/lib" -> apply -> save and close
- This path can also be added via: 
  right click mss project -> Properties -> Build -> Tools -> Arm linker -> File Search Path -> Add <dir> to library search path -> Add: 
-i"${COM_TI_MMWAVE_SDK_INSTALL_DIR}/packages/ti/drivers/spi/lib" -> apply -> save and close

## Add lib file:
right click mss project -> Properties -> Build -> Tools -> Arm linker -> File Search Path -> Include library file or command file as input -> Added libspi_xwr16xx.aer4f -> save and close
(.lib file location: See above for the file path relative to the SDK installation folder path)

(Source: https://e2e.ti.com/support/tools/code-composer-studio-group/ccs/f/code-composer-studio-forum/578229/ccs-tm4c129enczad-how-to-resolve-linker-errors---unresolved-symbols)