#ifndef TEST_H_
#define TEST_H_

#include <ad8400_ad8402_ad8403.h>

#include <assert.h>
#include <stdbool.h>

#define TEST_FOR(cases) \
    TestCase case_;     \
    for (size_t i = 0; case_ = (cases)[i], i < sizeof((cases)) / sizeof(TestCase); i++)

#define TEST_AD8400_AD8402_AD8403_ERROR(e) ((e) == AD8400_AD8402_AD8403_OK       ? "AD8400_AD8402_AD8403_OK"     \
                                            : (e) == AD8400_AD8402_AD8403_EIO    ? "AD8400_AD8402_AD8403_EIO"    \
                                            : (e) == AD8400_AD8402_AD8403_EINVAL ? "AD8400_AD8402_AD8403_EINVAL" \
                                                                                 : "")

#define TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(expected_ret, actual_ret)                                  \
    if ((expected_ret) != (actual_ret))                                                                             \
    {                                                                                                               \
        fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",                                            \
                i, TEST_AD8400_AD8402_AD8403_ERROR((expected_ret)), TEST_AD8400_AD8402_AD8403_ERROR((actual_ret))); \
        cnt++;                                                                                                      \
        continue;                                                                                                   \
    }

#define TEST_SPI_SIZE ((size_t)8)

typedef struct TestSPIWriter
{
    AD8400_AD8402_AD8403SPIWriter parent;
    uint8_t last_data[TEST_SPI_SIZE];
    size_t last_size;
} TestSPIWriter;

AD8400_AD8402_AD8403ErrNo test_spi_writer_write(AD8400_AD8402_AD8403SPIWriter *parent, uint8_t data[], size_t size)
{
    assert(parent != NULL);
    assert(size < TEST_SPI_SIZE);
    TestSPIWriter *writer = (TestSPIWriter *)parent;
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

#define TEST_ASSERT_EQUAL_SPI_WRITTEN(expected_data, expected_size, actual_data, actual_size) \
    if ((expected_size) != (actual_size))                                                     \
    {                                                                                         \
        fprintf(stderr, "index: %d, expected_size: %d, actual_size: %d\n",                    \
                i, (expected_size), (actual_size));                                           \
        cnt++;                                                                                \
        continue;                                                                             \
    }                                                                                         \
    if (!test_spi_data_equals((expected_data), (actual_data), (actual_size)))                 \
    {                                                                                         \
        fprintf(stderr, "index: %d,\n", i);                                                   \
        for (size_t j = 0; j < (actual_size); j++)                                            \
        {                                                                                     \
            if ((expected_data)[j] != (actual_data)[j])                                       \
            {                                                                                 \
                fprintf(stderr, "  expected_data[%d]: %d, actual_data[%d]: %d\n",             \
                        j, (expected_data)[j], j, (actual_data)[j]);                          \
            }                                                                                 \
        }                                                                                     \
        cnt++;                                                                                \
        continue;                                                                             \
    }

typedef enum TestGPIOState
{
    TEST_GPIO_HIGH,
    TEST_GPIO_LOW,
} TestGPIOState;

#define TEST_GPIO_STATE(state) ((state) == TEST_GPIO_HIGH ? "TEST_GPIO_HIGH" \
                                                          : "TEST_GPIO_LOW")

typedef struct TestGPIO
{
    AD8400_AD8402_AD8403GPIO parent;
    TestGPIOState state;
} TestGPIO;

AD8400_AD8402_AD8403ErrNo test_gpio_set_high(AD8400_AD8402_AD8403GPIO *gpio)
{
    assert(gpio != NULL);
    ((TestGPIO *)gpio)->state = TEST_GPIO_HIGH;
    return AD8400_AD8402_AD8403_OK;
}

AD8400_AD8402_AD8403ErrNo test_gpio_set_low(AD8400_AD8402_AD8403GPIO *gpio)
{
    assert(gpio != NULL);
    ((TestGPIO *)gpio)->state = TEST_GPIO_LOW;
    return AD8400_AD8402_AD8403_OK;
}

#define test_gpio_init(gpio) ((gpio)->parent.set_high = test_gpio_set_high, \
                              (gpio)->parent.set_low = test_gpio_set_low,   \
                              (void)0)

#endif // TEST_H_