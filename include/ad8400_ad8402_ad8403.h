#ifndef AD8400_AD8402_AD8403_H
#define AD8400_AD8402_AD8403_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <errno.h>
#ifndef __STDC_LIB_EXT1__
    typedef int errno_t;
#endif
#include <stddef.h>
#include <stdint.h>

    typedef struct AD8400_AD8402_AD8403SPIWriter
    {
        errno_t (*write)(struct AD8400_AD8402_AD8403SPIWriter *writer, uint8_t data[], size_t size);
    } AD8400_AD8402_AD8403SPIWriter;

    typedef struct AD8400_AD8402_AD8403GPIO
    {
        errno_t (*set_high)(struct AD8400_AD8402_AD8403GPIO *gpio);
        errno_t (*set_low)(struct AD8400_AD8402_AD8403GPIO *gpio);
    } AD8400_AD8402_AD8403GPIO;

    typedef struct AD8400_AD8402_AD8403
    {
        AD8400_AD8402_AD8403SPIWriter *writer;
        AD8400_AD8402_AD8403GPIO *shdn;
    } AD8400_AD8402_AD8403;

    errno_t ad8400_ad8402_ad8403_init(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, AD8400_AD8402_AD8403SPIWriter *writer, AD8400_AD8402_AD8403GPIO *shdn);
    errno_t ad8400_ad8402_ad8403_set_rdac1(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    errno_t ad8400_ad8402_ad8403_set_rdac2(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    errno_t ad8400_ad8402_ad8403_set_rdac3(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    errno_t ad8400_ad8402_ad8403_set_rdac4(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403, uint8_t data);
    errno_t ad8400_ad8402_ad8403_enter_shutdown_mode(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403);
    errno_t ad8400_ad8402_ad8403_enter_operational_mode(AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403);

#ifdef __cplusplus
}
#endif

#endif // AD8400_AD8402_AD8403_H