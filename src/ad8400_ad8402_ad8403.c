#include <ad8400_ad8402_ad8403.h>
#include "internal.h"

AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_init(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, AD8400_AD8402_AD8403SPIWriter *writer, AD8400_AD8402_AD8403GPIO *shdn)
{
    if (ad8400_ad8402_ad8403 == NULL ||
        writer == NULL)
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }

    ad8400_ad8402_ad8403->writer = writer;
    ad8400_ad8402_ad8403->shdn = shdn;

    return AD8400_AD8402_AD8403_OK;
}

static AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, AD8400_AD8402_AD8403Address addr, uint8_t data)
{
    if (ad8400_ad8402_ad8403 == NULL ||
        (addr != AD8400_AD8402_AD8403_RDAC1 &&
         addr != AD8400_AD8402_AD8403_RDAC2 &&
         addr != AD8400_AD8402_AD8403_RDAC3 &&
         addr != AD8400_AD8402_AD8403_RDAC4))
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }

    return ad8400_ad8402_ad8403->writer->write(ad8400_ad8402_ad8403->writer,
                                               (uint8_t[]){(uint8_t)addr,
                                                           data},
                                               2);
}

AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac1(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data)
{
    return ad8400_ad8402_ad8403_set(ad8400_ad8402_ad8403, AD8400_AD8402_AD8403_RDAC1, data);
}

AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac2(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data)
{
    return ad8400_ad8402_ad8403_set(ad8400_ad8402_ad8403, AD8400_AD8402_AD8403_RDAC2, data);
}

AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac3(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data)
{
    return ad8400_ad8402_ad8403_set(ad8400_ad8402_ad8403, AD8400_AD8402_AD8403_RDAC3, data);
}

AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac4(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data)
{
    return ad8400_ad8402_ad8403_set(ad8400_ad8402_ad8403, AD8400_AD8402_AD8403_RDAC4, data);
}

AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_enter_shutdown_mode(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403)
{
    if (ad8400_ad8402_ad8403 == NULL)
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }
    else if (ad8400_ad8402_ad8403->shdn == NULL)
    {
        return AD8400_AD8402_AD8403_OK;
    }

    return ad8400_ad8402_ad8403->shdn->set_low(ad8400_ad8402_ad8403->shdn);
}

AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_enter_operational_mode(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403)
{
    if (ad8400_ad8402_ad8403 == NULL)
    {
        return AD8400_AD8402_AD8403_EINVAL;
    }
    else if (ad8400_ad8402_ad8403->shdn == NULL)
    {
        return AD8400_AD8402_AD8403_OK;
    }

    return ad8400_ad8402_ad8403->shdn->set_high(ad8400_ad8402_ad8403->shdn);
}