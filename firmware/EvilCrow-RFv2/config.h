#define DEST_FS_USES_SD

#define eepromsize 4096
#define samplesize 2000

#if defined(ESP8266)
    #define RECEIVE_ATTR ICACHE_RAM_ATTR
#elif defined(ESP32)
    #define RECEIVE_ATTR IRAM_ATTR
#else
    #define RECEIVE_ATTR
#endif

/* I/O */

// SPI devices
#define SD_SCLK 18
#define SD_MISO 19
#define SD_MOSI 23
#define SD_SS   5

#define CC1101_SCK  14
#define CC1101_MISO 12
#define CC1101_MOSI 13
#define CC1101_SS0   15 
#define CC1101_SS1 27
#define MOD0_GDO0 2
#define MOD1_GDO0 25

// Buttons and led
#define LED 32
#define BUTTON1 34
#define BUTTON2 35