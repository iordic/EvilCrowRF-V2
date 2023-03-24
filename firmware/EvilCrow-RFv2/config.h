#define DEST_FS_USES_SD

#define eepromsize 4096
#define samplesize 2000

#define SD_SCLK 18
#define SD_MISO 19
#define SD_MOSI 23
#define SD_SS   5

#define CC1101_SCK  14
#define CC1101_MISO 12
#define CC1101_MOSI 13
#define CC1101_SS0   15 
#define CC1101_SS1 27
#define GDO0 2

#if defined(ESP8266)
    #define RECEIVE_ATTR ICACHE_RAM_ATTR
#elif defined(ESP32)
    #define RECEIVE_ATTR IRAM_ATTR
#else
    #define RECEIVE_ATTR
#endif
