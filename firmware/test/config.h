/*******************
 * Pin definitions *
 *******************/
/* SPI devices */
// SD card
#define SD_SCLK 18
#define SD_MISO 19
#define SD_MOSI 23
#define SD_SS   22

// Common HSPI pins (both cc1101 modules and nrf24)
#define HSPI_SCLK  14
#define HSPI_MISO 12
#define HSPI_MOSI 13

// CC1101 modules
#define CC1101_SS0 5 
#define MOD0_GDO0 2
#define MOD0_GDO2 4

#define CC1101_SS1 27
#define MOD1_GDO0 25
#define MOD1_GDO2 26

// NRF24
#define NRF24_CE 33
#define NRF24_SS 15
//#define NRF24_CS_B 27 // (?) used by cc1101, declared at code but useless

/* Buttons and led */
#define LED 32
#define BUTTON1 34
#define BUTTON2 35

/**********
 * Others *
 **********/
#define SERIAL_BAUDRATE 38400

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3c
