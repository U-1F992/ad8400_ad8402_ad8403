#ifdef ARDUINO

#ifndef AD8400_AD8402_AD8403_ARDUINO_H_
#define AD8400_AD8402_AD8403_ARDUINO_H_

#include <ad8400_ad8402_ad8403.h>

#include <Arduino.h>
#include <Wire.h>

class AD8400_AD8402_AD8403
{
public:
    AD8400_AD8402_AD8403(HardwareI2C *wire)
    {
        writer_.parent.write = [](ad8400_ad8402_ad8403_i2c_writer_t *parent, uint8_t data[], size_t size)
        {
            _Writer *writer = (_Writer *)parent;
            if (writer == NULL)
            {
                return;
            }

            writer->_wire->beginTransmission(AD8400_AD8402_AD8403_SLAVE_ADDRESS);
            for (size_t i = 0; i < size; i++)
            {
                writer->_wire->write(data[i]);
            }
            writer->_wire->endTransmission();
        };
        writer_._wire = wire;

        ad8400_ad8402_ad8403_init(&_ad8400_ad8402_ad8403, (ad8400_ad8402_ad8403_i2c_writer_t *)&writer_);
    }

    ad8400_ad8402_ad8403_error_t set(ad8400_ad8402_ad8403_memory_address_t addr, ad8400_ad8402_ad8403_sign_bit_t sign, uint8_t data)
    {
        return ad8400_ad8402_ad8403_set(&_ad8400_ad8402_ad8403, addr, sign, data);
    }

private:
    ad8400_ad8402_ad8403_t _ad8400_ad8402_ad8403;

    struct _Writer
    {
        ad8400_ad8402_ad8403_i2c_writer_t parent;
        HardwareI2C *_wire;
    };

    _Writer writer_;
};

#endif // AD8400_AD8402_AD8403_ARDUINO_H_

#endif // ARDUINO