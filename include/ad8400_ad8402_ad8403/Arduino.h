#ifdef ARDUINO

#ifndef AD8400_AD8402_AD8403_ARDUINO_H
#define AD8400_AD8402_AD8403_ARDUINO_H

#include <ad8400_ad8402_ad8403.h>

#include <Arduino.h>
#include <SPI.h>

#include <assert.h>

class AD8400_AD8402_AD8403Wrapper
{
public:
    AD8400_AD8402_AD8403Wrapper(HardwareSPI *spi, pin_size_t cs)
    {
        writer_.parent.write = [](AD8400_AD8402_AD8403SPIWriter *parent, uint8_t data[], size_t size)
        {
            Writer_ *writer = (Writer_ *)parent;
            if (writer == NULL)
            {
                return EINVAL;
            }

            digitalWrite(writer->cs_, LOW);
            writer->spi_->transfer(data, size);
            digitalWrite(writer->cs_, HIGH);

            return 0;
        };
        writer_.spi_ = spi;
        writer_.cs_ = cs;

        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403_, (AD8400_AD8402_AD8403SPIWriter *)&writer_, NULL) == 0);
    }

    AD8400_AD8402_AD8403Wrapper(HardwareSPI *spi, pin_size_t cs, pin_size_t shdn)
    {
        writer_.parent.write = [](AD8400_AD8402_AD8403SPIWriter *parent, uint8_t data[], size_t size)
        {
            Writer_ *writer = (Writer_ *)parent;
            if (writer == NULL)
            {
                return EINVAL;
            }

            digitalWrite(writer->cs_, LOW);
            writer->spi_->transfer(data, size);
            digitalWrite(writer->cs_, HIGH);

            return 0;
        };
        writer_.spi_ = spi;
        writer_.cs_ = cs;

        shdn_.parent.set_high = [](AD8400_AD8402_AD8403GPIO *parent)
        {
            GPIO_ *gpio = (GPIO_ *)parent;
            if (gpio == NULL)
            {
                return EINVAL;
            }

            digitalWrite(gpio->pin_, HIGH);

            return 0;
        };
        shdn_.parent.set_low = [](AD8400_AD8402_AD8403GPIO *parent)
        {
            GPIO_ *gpio = (GPIO_ *)parent;
            if (gpio == NULL)
            {
                return EINVAL;
            }

            digitalWrite(gpio->pin_, LOW);

            return 0;
        };
        shdn_.pin_ = shdn;

        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403_, (AD8400_AD8402_AD8403SPIWriter *)&writer_, (AD8400_AD8402_AD8403GPIO *)&shdn_) == 0);
    }

    errno_t setRDAC1(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac1(&ad8400_ad8402_ad8403_, data); }
    errno_t setRDAC2(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac2(&ad8400_ad8402_ad8403_, data); }
    errno_t setRDAC3(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac3(&ad8400_ad8402_ad8403_, data); }
    errno_t setRDAC4(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac4(&ad8400_ad8402_ad8403_, data); }
    errno_t enterShutdownMode() { return ad8400_ad8402_ad8403_enter_shutdown_mode(&ad8400_ad8402_ad8403_); }
    errno_t enterOperationalMode() { return ad8400_ad8402_ad8403_enter_operational_mode(&ad8400_ad8402_ad8403_); }

private:
    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403_;

    struct Writer_
    {
        AD8400_AD8402_AD8403SPIWriter parent;
        HardwareSPI *spi_;
        pin_size_t cs_;
    } writer_;

    struct GPIO_
    {
        AD8400_AD8402_AD8403GPIO parent;
        pin_size_t pin_;
    } shdn_;
};

#endif // AD8400_AD8402_AD8403_ARDUINO_H

#endif // ARDUINO