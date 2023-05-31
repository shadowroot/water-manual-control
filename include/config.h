#define SERIAL_BAUD_RATE 115200

//ESP32C3 - LUATOS
#define PIN_LED1 12
#define PIN_LED2 13

//Arduino UNO
#define LCD_RS_PIN 8
#define LCD_EN_PIN 9
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7
#define BUTTON_PIN A0

//ESP32C3
#define I2C_SCL_PIN GPIO_NUM_5
#define I2C_SDA_PIN GPIO_NUM_4

#define BROKER_ADDR     IPAddress(37, 205, 14, 122)
#define BROKER_PORT     1883
#define BROKER_USERNAME "haas"
#define BROKER_PASSWORD "Zerogeneration0!"

#define WIFI_SSID       "Hells Gate IOT"
#define WIFI_PASSWORD   "HadejHeslo0" 


#define WATER_BOOT_TEXT "Zalevani 0.1"
#define WATER_MODE_AUTO_TEXT "Automaticke"
#define WATER_MODE_MANUAL_TEXT "Rucni"
#define ACTION_WATERRING_ON_TEXT "Spust rucni"
#define ACTION_WATERRING_ON_TEXT "Spust cyklus"
#define ACTION_WATERRING_OFF_TEXT "Zastav zalevani"
#define STATUS_WATERRING_ON_TEXT "Zalevam..."
#define SET_WATERRING_CYCLE_TEXT "Nastav interval"
#define SET_WATERRING_TIME_TEXT "Nastav dobu zalevani"
#define LAST_WATERRING_TEXT "Posledni zalevani"
#define SOIL_MOISTURE_TEXT "Vlhkost pudy"
#define WATERRING_TIME_UNIT_TEXT "s"
#define OK_TEXT "OK!"
#define RIGHT_SYMBOL ">"
#define LEFT_SYMBOL "<"
#define LCD_ROWS 2
#define LCD_COLS 16

#define OPTIMAL_SOIL_MOISTURE_PERCENT 60
