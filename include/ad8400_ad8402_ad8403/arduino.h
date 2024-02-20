#ifdef ARDUINO

#ifndef AD8400_AD8402_AD8403_ARDUINO_H_
#define AD8400_AD8402_AD8403_ARDUINO_H_

#include <ad8400_ad8402_ad8403.h>

#include <Arduino.h>
#include <SPI.h>

class AD8400_AD8402_AD8403
{
public:
    AD8400_AD8402_AD8403(HardwareSPI *spi, pin_size_t cs, pin_size_t shdn)
    {
        writer_.parent.write = [](ad8400_ad8402_ad8403_spi_writer_t *parent, uint8_t data[], size_t size)
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

        shdn_.parent.set_high = [](ad8400_ad8402_ad8403_gpio_t *parent)
        {
            GPIO_ *gpio = (GPIO_ *)parent;
            if (gpio == NULL)
            {
                return AD8400_AD8402_AD8403_EINVAL;
            }

            digitalWrite(gpio->pin_, HIGH);

            return AD8400_AD8402_AD8403_OK;
        };
        shdn_.parent.set_low = [](ad8400_ad8402_ad8403_gpio_t *parent)
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

        ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403_, (ad8400_ad8402_ad8403_spi_writer_t *)&writer_, (ad8400_ad8402_ad8403_gpio_t *)&shdn_);
    }

    ad8400_ad8402_ad8403_error_t set(ad8400_ad8402_ad8403_address_t addr, uint8_t data)
    {
        return ad8400_ad8402_ad8403_set(&ad8400_ad8402_ad8403_, addr, data);
    }

    ad8400_ad8402_ad8403_error_t enterShutdownMode()
    {
        return ad8400_ad8402_ad8403_enter_shutdown_mode(&ad8400_ad8402_ad8403_);
    }

    ad8400_ad8402_ad8403_error_t enterOperationalMode()
    {
        return ad8400_ad8402_ad8403_enter_operational_mode(&ad8400_ad8402_ad8403_);
    }

private:
    ad8400_ad8402_ad8403_t ad8400_ad8402_ad8403_;

    struct Writer_
    {
        ad8400_ad8402_ad8403_spi_writer_t parent;
        HardwareSPI *spi_;
        pin_size_t cs_;
    };

    Writer_ writer_;

    struct GPIO_
    {
        ad8400_ad8402_ad8403_gpio_t parent;
        pin_size_t pin_;
    };

    GPIO_ shdn_;
};

#endif // AD8400_AD8402_AD8403_ARDUINO_H_

#endif // ARDUINO