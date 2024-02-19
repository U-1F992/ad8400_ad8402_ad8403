#include <ad8400_ad8402_ad8403.h>

ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_init(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403, ad8400_ad8402_ad8403_spi_writer_t *writer, ad8400_ad8402_ad8403_gpio_t *shdn)
{
    if (ad8400_ad8402_ad8403 == NULL ||
        writer == NULL ||
        shdn == NULL)
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }

    ad8400_ad8402_ad8403->_writer = writer;
    ad8400_ad8402_ad8403->_shdn = shdn;

    return AD8400_AD8402_AD8403_OK;
}

ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_set(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403, ad8400_ad8402_ad8403_address_t addr, uint8_t data)
{
    if (ad8400_ad8402_ad8403 == NULL ||
        (addr != AD8400_AD8402_AD8403_RDAC1 && addr != AD8400_AD8402_AD8403_RDAC2 && addr != AD8400_AD8402_AD8403_RDAC3 && addr != AD8400_AD8402_AD8403_RDAC4))
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }

    ad8400_ad8402_ad8403->_writer->write(ad8400_ad8402_ad8403->_writer,
                                         (uint8_t[]){(uint8_t)addr,
                                                     data},
                                         2);

    return AD8400_AD8402_AD8403_OK;
}

ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_enter_shutdown_mode(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403)
{
    if (ad8400_ad8402_ad8403 == NULL)
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }

    ad8400_ad8402_ad8403->_shdn->set_low(ad8400_ad8402_ad8403->_shdn);

    return AD8400_AD8402_AD8403_OK;
}

ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_enter_operational_mode(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403)
{
    if (ad8400_ad8402_ad8403 == NULL)
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }

    ad8400_ad8402_ad8403->_shdn->set_high(ad8400_ad8402_ad8403->_shdn);

    return AD8400_AD8402_AD8403_OK;
}