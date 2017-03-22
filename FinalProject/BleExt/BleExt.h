// BleExt.h - Library for Bluetooth Communication

#ifndef BleExt_h
#define BleExt_h

// COMMON SETTINGS
// ----------------------------------------------------------------------------------------------
// These settings are used in both SW UART, HW UART and SPI mode
// ----------------------------------------------------------------------------------------------
#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output
#define BLE_READPACKET_TIMEOUT         50    // Timeout in ms waiting to read a response
#define NO_INPUT                       0     // Default value when receiving no input

// SOFTWARE UART SETTINGS
// ----------------------------------------------------------------------------------------------
// The following macros declare the pins that will be used for 'SW' serial.
// ----------------------------------------------------------------------------------------------

#define BLUEFRUIT_SWUART_RXD_PIN      10    // Required for software serial!
#define BLUEFRUIT_SWUART_TXD_PIN      9  // Required for software serial!
#define BLUEFRUIT_UART_CTS_PIN        8   // Required for software serial!
#define BLUEFRUIT_UART_RTS_PIN        -1   // Optional, set to -1 if unused
#define BLUEFRUIT_UART_MODE_PIN       -1    // Set to -1 if unused

#define NO_BUTTON                     0     // Returned when no button is pressed

// Sets up the Bluetooth device, should only ever be called once.
bool bleSetup(void) ;

// Gets the input from the Bluetooth device
bool bleGetInput(void);

#endif
