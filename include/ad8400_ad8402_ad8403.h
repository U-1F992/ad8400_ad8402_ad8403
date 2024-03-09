#ifndef AD8400_AD8402_AD8403_H_
#define AD8400_AD8402_AD8403_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

    typedef int AD8400_AD8402_AD8403ErrNo;

#define AD8400_AD8402_AD8403_OK /*    */ ((AD8400_AD8402_AD8403ErrNo)0)
#define AD8400_AD8402_AD8403_EIO /*   */ ((AD8400_AD8402_AD8403ErrNo)5)
#define AD8400_AD8402_AD8403_EINVAL /**/ ((AD8400_AD8402_AD8403ErrNo)22)

    typedef struct AD8400_AD8402_AD8403SPIWriter
    {
        AD8400_AD8402_AD8403ErrNo (*write)(struct AD8400_AD8402_AD8403SPIWriter *writer, uint8_t data[], size_t size);
    } AD8400_AD8402_AD8403SPIWriter;

    typedef struct AD8400_AD8402_AD8403GPIO
    {
        AD8400_AD8402_AD8403ErrNo (*set_high)(struct AD8400_AD8402_AD8403GPIO *gpio);
        AD8400_AD8402_AD8403ErrNo (*set_low)(struct AD8400_AD8402_AD8403GPIO *gpio);
    } AD8400_AD8402_AD8403GPIO;

    typedef struct AD8400_AD8402_AD8403
    {
        AD8400_AD8402_AD8403SPIWriter *writer;
        AD8400_AD8402_AD8403GPIO *shdn;
    } AD8400_AD8402_AD8403;

    AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_init(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, AD8400_AD8402_AD8403SPIWriter *writer, AD8400_AD8402_AD8403GPIO *shdn);
    AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac1(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac2(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac3(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_set_rdac4(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_enter_shutdown_mode(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403);
    AD8400_AD8402_AD8403ErrNo ad8400_ad8402_ad8403_enter_operational_mode(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403);

#ifdef __cplusplus
}
#endif

#endif // AD8400_AD8402_AD8403_H_