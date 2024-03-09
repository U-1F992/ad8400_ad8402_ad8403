#ifdef ARDUINO

#ifndef AD8400_AD8402_AD8403_ARDUINO_H_
#define AD8400_AD8402_AD8403_ARDUINO_H_

#include <ad8400_ad8402_ad8403.h>

#include <Arduino.h>
#include <SPI.h>

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
                return AD8400_AD8402_AD8403_EINVAL;
            }

            digitalWrite(writer->cs_, LOW);
            writer->spi_->transfer(data, size);
            digitalWrite(writer->cs_, HIGH);

            return AD8400_AD8402_AD8403_OK;
        };
        writer_.spi_ = spi;
        writer_.cs_ = cs;

        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403_, (AD8400_AD8402_AD8403SPIWriter *)&writer_, NULL) == AD8400_AD8402_AD8403_OK);
    }

    AD8400_AD8402_AD8403Wrapper(HardwareSPI *spi, pin_size_t cs, pin_size_t shdn)
    {
        writer_.parent.write = [](AD8400_AD8402_AD8403SPIWriter *parent, uint8_t data[], size_t size)
        {
            Writer_ *writer = (Writer_ *)parent;
            if (writer == NULL)
            {
                return AD8400_AD8402_AD8403_EINVAL;
            }

            digitalWrite(writer->cs_, LOW);
            writer->spi_->transfer(data, size);
            digitalWrite(writer->cs_, HIGH);

            return AD8400_AD8402_AD8403_OK;
        };
        writer_.spi_ = spi;
        writer_.cs_ = cs;

        shdn_.parent.set_high = [](AD8400_AD8402_AD8403GPIO *parent)
        {
            GPIO_ *gpio = (GPIO_ *)parent;
            if (gpio == NULL)
            {
                return AD8400_AD8402_AD8403_EINVAL;
            }

            digitalWrite(gpio->pin_, HIGH);

            return AD8400_AD8402_AD8403_OK;
        };
        shdn_.parent.set_low = [](AD8400_AD8402_AD8403GPIO *parent)
        {
            GPIO_ *gpio = (GPIO_ *)parent;
            if (gpio == NULL)
            {
                return AD8400_AD8402_AD8403_EINVAL;
            }

            digitalWrite(gpio->pin_, LOW);

            return AD8400_AD8402_AD8403_OK;
        };
        shdn_.pin_ = shdn;

        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403_, (AD8400_AD8402_AD8403SPIWriter *)&writer_, (AD8400_AD8402_AD8403GPIO *)&shdn_) == AD8400_AD8402_AD8403_OK);
    }

    AD8400_AD8402_AD8403ErrNo setRDAC1(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac1(&ad8400_ad8402_ad8403_, data); }
    AD8400_AD8402_AD8403ErrNo setRDAC2(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac2(&ad8400_ad8402_ad8403_, data); }
    AD8400_AD8402_AD8403ErrNo setRDAC3(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac3(&ad8400_ad8402_ad8403_, data); }
    AD8400_AD8402_AD8403ErrNo setRDAC4(uint8_t data) { return ad8400_ad8402_ad8403_set_rdac4(&ad8400_ad8402_ad8403_, data); }
    AD8400_AD8402_AD8403ErrNo enterShutdownMode() { return ad8400_ad8402_ad8403_enter_shutdown_mode(&ad8400_ad8402_ad8403_); }
    AD8400_AD8402_AD8403ErrNo enterOperationalMode() { return ad8400_ad8402_ad8403_enter_operational_mode(&ad8400_ad8402_ad8403_); }

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

#endif // AD8400_AD8402_AD8403_ARDUINO_H_

#endif // ARDUINO