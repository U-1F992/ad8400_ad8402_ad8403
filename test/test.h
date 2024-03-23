#ifndef TEST_H
#define TEST_H

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <assert.h>
#include <errno.h>
#ifndef __STDC_LIB_EXT1__
typedef int errno_t;
#endif
#include <stdbool.h>

#define TEST_TEXT_RED "\e[31m"
#define TEST_TEXT_GREEN "\e[32m"
#define TEST_TEXT_RESET "\e[0m"

typedef int (*Test)(void);

#define TEST_RUN(tests)                                                                       \
    int TEST_COUNT = 0;                                                                       \
    for (size_t TEST_INDEX = 0; TEST_INDEX < sizeof((tests)) / sizeof(Test); TEST_INDEX++)    \
    {                                                                                         \
        TEST_COUNT += (tests)[TEST_INDEX]();                                                  \
    }                                                                                         \
    if (TEST_COUNT == 0)                                                                      \
    {                                                                                         \
        printf("%sOK%s\n", TEST_TEXT_GREEN, TEST_TEXT_RESET);                                 \
        return 0;                                                                             \
    }                                                                                         \
    else                                                                                      \
    {                                                                                         \
        fprintf(stderr, "%s%d errors found%s\n", TEST_TEXT_RED, TEST_COUNT, TEST_TEXT_RESET); \
        return 1;                                                                             \
    }

#define TEST_VAR_NAME(var) #var

#define TEST_FOR(cases)         \
    printf("* %s\n", __func__); \
    int TEST_COUNT = 0;         \
    int TEST_STEP = 0;          \
    TestCase *TEST_CASE;        \
    for (size_t TEST_INDEX = 0; TEST_STEP = 0, TEST_CASE = &(cases)[TEST_INDEX], TEST_INDEX < sizeof((cases)) / sizeof(TestCase); TEST_INDEX++)

#define TEST_ERRNO_T(err) ((err) == 0        ? "OK"                  \
                           : (err) == EIO    ? TEST_VAR_NAME(EIO)    \
                           : (err) == EINVAL ? TEST_VAR_NAME(EINVAL) \
                                             : "UNKNOWN")

#define TEST_ASSERT_EQUAL_ERRNO_T(expected, actual)                                                                       \
    if ((expected) != (actual))                                                                                           \
    {                                                                                                                     \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %s, actual: %s%s\n",                                            \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, TEST_ERRNO_T((expected)), TEST_ERRNO_T((actual)), TEST_TEXT_RESET); \
        TEST_COUNT++;                                                                                                     \
        continue;                                                                                                         \
    }                                                                                                                     \
    TEST_STEP++;

#include <ad8400_ad8402_ad8403.h>

#define TEST_SPI_SIZE ((size_t)8)

typedef struct TestSPIWriter
{
    AD8400_AD8402_AD8403SPIWriter parent;
    uint8_t last_data[TEST_SPI_SIZE];
    size_t last_size;
} TestSPIWriter;

errno_t test_spi_writer_write(AD8400_AD8402_AD8403SPIWriter *parent, uint8_t data[], size_t size)
{
    assert(parent != NULL);
    assert(size < TEST_SPI_SIZE);
    TestSPIWriter *writer = (TestSPIWriter *)parent;
    for (size_t i = 0; i < size; i++)
    {
        writer->last_data[i] = data[i];
    }
    writer->last_size = size;
    return 0;
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

#define TEST_ASSERT_EQUAL_SPI_WRITTEN(expected_data, expected_size, actual_data, actual_size)                                                            \
    if ((expected_size) != (actual_size))                                                                                                                \
    {                                                                                                                                                    \
        fprintf(stderr, "%sindex: %d, step: %d, expected_size: %d, actual_size: %d%s\n",                                                                 \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, (expected_size), (actual_size), TEST_TEXT_RESET);                                                  \
        TEST_COUNT++;                                                                                                                                    \
        continue;                                                                                                                                        \
    }                                                                                                                                                    \
    if (!test_spi_data_equals((expected_data), (actual_data), (actual_size)))                                                                            \
    {                                                                                                                                                    \
        fprintf(stderr, "%sindex: %d, step: %d,%s\n",                                                                                                    \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, TEST_TEXT_RESET);                                                                                  \
        for (size_t TEST_SPI_INDEX = 0; TEST_SPI_INDEX < (actual_size); TEST_SPI_INDEX++)                                                                \
        {                                                                                                                                                \
            if ((expected_data)[TEST_SPI_INDEX] != (actual_data)[TEST_SPI_INDEX])                                                                        \
            {                                                                                                                                            \
                fprintf(stderr, "%s  expected_data[%d]: %d, actual_data[%d]: %d%s\n",                                                                    \
                        TEST_TEXT_RED, TEST_SPI_INDEX, (expected_data)[TEST_SPI_INDEX], TEST_SPI_INDEX, (actual_data)[TEST_SPI_INDEX], TEST_TEXT_RESET); \
            }                                                                                                                                            \
        }                                                                                                                                                \
        TEST_COUNT++;                                                                                                                                    \
        continue;                                                                                                                                        \
    }                                                                                                                                                    \
    TEST_STEP++;

typedef enum TestGPIOState
{
    TEST_GPIO_HIGH,
    TEST_GPIO_LOW,
} TestGPIOState;

#define TEST_GPIO_STATE(s) ((s) == TEST_GPIO_HIGH  ? TEST_VAR_NAME(TEST_GPIO_HIGH) \
                            : (s) == TEST_GPIO_LOW ? TEST_VAR_NAME(TEST_GPIO_LOW)  \
                                                   : "UNKNOWN")

#define TEST_ASSERT_EQUAL_TEST_GPIO_STATE(expected, actual)                                                                     \
    if ((expected) != (actual))                                                                                                 \
    {                                                                                                                           \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %s, actual: %s%s\n",                                                  \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, TEST_GPIO_STATE((expected)), TEST_GPIO_STATE((actual)), TEST_TEXT_RESET); \
        TEST_COUNT++;                                                                                                           \
        continue;                                                                                                               \
    }                                                                                                                           \
    TEST_STEP++;

typedef struct TestGPIO
{
    AD8400_AD8402_AD8403GPIO parent;
    TestGPIOState state;
} TestGPIO;

errno_t test_gpio_set_high(AD8400_AD8402_AD8403GPIO *gpio)
{
    assert(gpio != NULL);
    ((TestGPIO *)gpio)->state = TEST_GPIO_HIGH;
    return 0;
}

errno_t test_gpio_set_low(AD8400_AD8402_AD8403GPIO *gpio)
{
    assert(gpio != NULL);
    ((TestGPIO *)gpio)->state = TEST_GPIO_LOW;
    return 0;
}

#define test_gpio_init(gpio) ((gpio)->parent.set_high = test_gpio_set_high, \
                              (gpio)->parent.set_low = test_gpio_set_low,   \
                              (void)0)

#endif // TEST_H