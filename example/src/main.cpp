#include <Arduino.h>
#include <SPI.h>

#include <ad8400_ad8402_ad8403/arduino.h>

static const pin_size_t PIN_SPI_CS = 1;
static const pin_size_t PIN_SPI_SCK = 2;
static const pin_size_t PIN_SPI_TX = 3;
static const pin_size_t PIN_SHDN = 4;

static AD8400_AD8402_AD8403 ad8400_ad8402_ad8403(&SPI, PIN_SPI_CS, PIN_SHDN);

void setup()
{
    pinMode(PIN_SPI_CS, OUTPUT);

    SPI.setCS(PIN_SPI_CS);
    SPI.setSCK(PIN_SPI_SCK);
    SPI.setTX(PIN_SPI_TX);
    SPI.begin();

    pinMode(PIN_SHDN, OUTPUT);
}

void loop()
{
    ad8400_ad8402_ad8403.set(AD8400_AD8402_AD8403_RDAC1, 0);
    delay(500);
    ad8400_ad8402_ad8403.set(AD8400_AD8402_AD8403_RDAC1, 255);
    delay(500);
}