#include <Arduino.h>
#include <SPI.h>

#include <ad8400_ad8402_ad8403/Arduino.h>

static const pin_size_t PIN_SPI_CS = 6;
static const pin_size_t PIN_SPI_SCK = 2;
static const pin_size_t PIN_SPI_TX = 3;
// static const pin_size_t PIN_SHDN = 4;

static AD8400_AD8402_AD8403Wrapper ad8400_ad8402_ad8403(&SPI, PIN_SPI_CS);

void setup()
{
    Serial.begin();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(PIN_SPI_CS, OUTPUT);
    digitalWrite(PIN_SPI_CS, HIGH);

    // SPI.setCS(PIN_SPI_CS);
    SPI.setSCK(PIN_SPI_SCK);
    SPI.setTX(PIN_SPI_TX);
    SPI.begin();

    // pinMode(PIN_SHDN, OUTPUT);
    // digitalWrite(PIN_SHDN, HIGH);
}

void loop()
{
    digitalWrite(LED_BUILTIN, LOW);
    ad8400_ad8402_ad8403.setRDAC1(0);
    delay(1000);

    digitalWrite(LED_BUILTIN, HIGH);
    ad8400_ad8402_ad8403.setRDAC1(255);
    delay(1000);
}