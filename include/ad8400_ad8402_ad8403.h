#ifndef AD8400_AD8402_AD8403_H_
#define AD8400_AD8402_AD8403_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

    typedef int ad8400_ad8402_ad8403_error_t;

#define AD8400_AD8402_AD8403_OK ((int)0)
#define AD8400_AD8402_AD8403_EIO ((int)5)
#define AD8400_AD8402_AD8403_EINVAL ((int)22)

    typedef struct ad8400_ad8402_ad8403_spi_writer_t
    {
        ad8400_ad8402_ad8403_error_t (*write)(struct ad8400_ad8402_ad8403_spi_writer_t *writer, uint8_t data[], size_t size);
    } ad8400_ad8402_ad8403_spi_writer_t;

    typedef struct ad8400_ad8402_ad8403_gpio_t
    {
        ad8400_ad8402_ad8403_error_t (*set_high)(struct ad8400_ad8402_ad8403_gpio_t *gpio);
        ad8400_ad8402_ad8403_error_t (*set_low)(struct ad8400_ad8402_ad8403_gpio_t *gpio);
    } ad8400_ad8402_ad8403_gpio_t;

    typedef struct ad8400_ad8402_ad8403_t
    {
        ad8400_ad8402_ad8403_spi_writer_t *_writer;
        ad8400_ad8402_ad8403_gpio_t *_shdn;
    } ad8400_ad8402_ad8403_t;

    typedef enum ad8400_ad8402_ad8403_address_t
    {
        AD8400_AD8402_AD8403_RDAC1,
        AD8400_AD8402_AD8403_RDAC2,
        AD8400_AD8402_AD8403_RDAC3,
        AD8400_AD8402_AD8403_RDAC4
    } ad8400_ad8402_ad8403_address_t;

    ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_init(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403, ad8400_ad8402_ad8403_spi_writer_t *writer, ad8400_ad8402_ad8403_gpio_t *shdn);
    ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_set(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403, ad8400_ad8402_ad8403_address_t addr, uint8_t data);
    ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_enter_shutdown_mode(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403);
    ad8400_ad8402_ad8403_error_t ad8400_ad8402_ad8403_enter_operational_mode(ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403);

#ifdef __cplusplus
}
#endif

#endif // AD8400_AD8402_AD8403_H_