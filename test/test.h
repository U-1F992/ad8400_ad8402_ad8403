#ifndef TEST_H_
#define TEST_H_

#include <ad8400_ad8402_ad8403.h>

#include <assert.h>
#include <stdbool.h>

#define TEST_AD8400_AD8402_AD8403_ERROR(err) ((err) == AD8400_AD8402_AD8403_EINVAL ? "AD8400_AD8402_AD8403_EINVAL" \
                                                                                   : "AD8400_AD8402_AD8403_OK")

ad8400_ad8402_ad8403_error_t test_null_spi_writer_write(ad8400_ad8402_ad8403_spi_writer_t *writer, uint8_t data[], size_t size)
{
    assert(writer != NULL);
    return AD8400_AD8402_AD8403_OK;
}

#define TEST_SPI_SIZE ((size_t)8)

typedef struct test_spi_writer_t
{
    ad8400_ad8402_ad8403_spi_writer_t parent;
    uint8_t last_data[TEST_SPI_SIZE];
    size_t last_size;
} test_spi_writer_t;

ad8400_ad8402_ad8403_error_t test_spi_writer_write(ad8400_ad8402_ad8403_spi_writer_t *parent, uint8_t data[], size_t size)
{
    assert(parent != NULL);
    assert(size < TEST_SPI_SIZE);
    test_spi_writer_t *writer = (test_spi_writer_t *)parent;
    for (size_t i = 0; i < size; i++)
    {
        writer->last_data[i] = data[i];
    }
    writer->last_size = size;
    return AD8400_AD8402_AD8403_OK;
}

#define test_spi_writer_init(writer) ((writer)->parent.write = test_spi_writer_write, \
                                      (writer)->last_size = 0,                        \
                                      (void)0)

bool test_spi_data_equals(uint8_t arr0[], uint8_t arr1[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr0[i] != arr1[i])
        {
            return false;
        }
    }
    return true;
}

ad8400_ad8402_ad8403_error_t test_null_gpio_set(ad8400_ad8402_ad8403_gpio_t *gpio)
{
    assert(gpio != NULL);
    return AD8400_AD8402_AD8403_OK;
}

typedef enum test_gpio_state_t
{
    TEST_GPIO_HIGH,
    TEST_GPIO_LOW,
} test_gpio_state_t;

#define TEST_GPIO_STATE(state) ((state) == TEST_GPIO_HIGH ? "TEST_GPIO_HIGH" \
                                                          : "TEST_GPIO_LOW")

typedef struct test_gpio_t
{
    ad8400_ad8402_ad8403_gpio_t parent;
    test_gpio_state_t state;
} test_gpio_t;

ad8400_ad8402_ad8403_error_t test_gpio_set_high(ad8400_ad8402_ad8403_gpio_t *gpio)
{
    assert(gpio != NULL);
    ((test_gpio_t *)gpio)->state = TEST_GPIO_HIGH;
    return AD8400_AD8402_AD8403_OK;
}

ad8400_ad8402_ad8403_error_t test_gpio_set_low(ad8400_ad8402_ad8403_gpio_t *gpio)
{
    assert(gpio != NULL);
    ((test_gpio_t *)gpio)->state = TEST_GPIO_LOW;
    return AD8400_AD8402_AD8403_OK;
}

#define test_gpio_init(gpio) ((gpio)->parent.set_high = test_gpio_set_high, \
                              (gpio)->parent.set_low = test_gpio_set_low,   \
                              (void)0)

#endif // TEST_H_