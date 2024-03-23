#include <ad8400_ad8402_ad8403.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_init(void)
{
    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;
        AD8400_AD8402_AD8403SPIWriter *writer;
        AD8400_AD8402_AD8403GPIO *shdn;

        errno_t expected_err;
        AD8400_AD8402_AD8403SPIWriter *expected_writer;
        AD8400_AD8402_AD8403GPIO *expected_shdn;
    } TestCase;

    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[8];
    AD8400_AD8402_AD8403SPIWriter writer[8];
    AD8400_AD8402_AD8403GPIO shdn[8];

    TestCase TEST_CASES[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = NULL, /* */ .shdn = NULL, /*    */ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .writer = NULL, /* */ .shdn = NULL, /*    */ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = &writer[2], .shdn = NULL, /*    */ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[3], .writer = &writer[3], .shdn = NULL, /*    */ .expected_err = 0, .expected_writer = &writer[3], .expected_shdn = NULL},
                             {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = NULL, /* */ .shdn = &shdn[4], /**/ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[5], .writer = NULL, /* */ .shdn = &shdn[5], /**/ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = &writer[6], .shdn = &shdn[6], /**/ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[7], .writer = &writer[7], .shdn = &shdn[7], /**/ .expected_err = 0, .expected_writer = &writer[7], .expected_shdn = &shdn[7]}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = ad8400_ad8402_ad8403_init(TEST_CASE->ad8400_ad8402_ad8403, TEST_CASE->writer, TEST_CASE->shdn);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
    }

    return TEST_COUNT;
}

int test_set_rdac1(void)
{
    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;
        uint8_t data;

        errno_t expected_err;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestSPIWriter writer[4];
    TestGPIO shdn[4];
    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_spi_writer_init(&writer[i]);
        test_gpio_init(&shdn[i]);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403[i], (AD8400_AD8402_AD8403SPIWriter *)&writer[i], (AD8400_AD8402_AD8403GPIO *)&shdn[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .data = 0, .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .data = 0, /*  */ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______00'00000000 */ 0x00, 0x00}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[2], .data = 128, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______00'10000000 */ 0x00, 0x80}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[3], .data = 255, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______00'11111111 */ 0x00, 0xFF}, .expected_size = 2}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = ad8400_ad8402_ad8403_set_rdac1(TEST_CASE->ad8400_ad8402_ad8403, TEST_CASE->data);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        uint8_t *actual_data = writer[TEST_INDEX].last_data;
        size_t actual_size = writer[TEST_INDEX].last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(TEST_CASE->expected_data, TEST_CASE->expected_size, actual_data, actual_size);
    }

    return TEST_COUNT;
}

int test_set_rdac2(void)
{
    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;
        uint8_t data;

        errno_t expected_err;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestSPIWriter writer[4];
    TestGPIO shdn[4];
    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_spi_writer_init(&writer[i]);
        test_gpio_init(&shdn[i]);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403[i], (AD8400_AD8402_AD8403SPIWriter *)&writer[i], (AD8400_AD8402_AD8403GPIO *)&shdn[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .data = 0, .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .data = 0, /*  */ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______01'00000000 */ 0x01, 0x00}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[2], .data = 128, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______01'10000000 */ 0x01, 0x80}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[3], .data = 255, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______01'11111111 */ 0x01, 0xFF}, .expected_size = 2}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = ad8400_ad8402_ad8403_set_rdac2(TEST_CASE->ad8400_ad8402_ad8403, TEST_CASE->data);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        uint8_t *actual_data = writer[TEST_INDEX].last_data;
        size_t actual_size = writer[TEST_INDEX].last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(TEST_CASE->expected_data, TEST_CASE->expected_size, actual_data, actual_size);
    }

    return TEST_COUNT;
}

int test_set_rdac3(void)
{
    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;
        uint8_t data;

        errno_t expected_err;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestSPIWriter writer[4];
    TestGPIO shdn[4];
    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_spi_writer_init(&writer[i]);
        test_gpio_init(&shdn[i]);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403[i], (AD8400_AD8402_AD8403SPIWriter *)&writer[i], (AD8400_AD8402_AD8403GPIO *)&shdn[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .data = 0, .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .data = 0, /*  */ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______10'00000000 */ 0x02, 0x00}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[2], .data = 128, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______10'10000000 */ 0x02, 0x80}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[3], .data = 255, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______10'11111111 */ 0x02, 0xFF}, .expected_size = 2}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = ad8400_ad8402_ad8403_set_rdac3(TEST_CASE->ad8400_ad8402_ad8403, TEST_CASE->data);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        uint8_t *actual_data = writer[TEST_INDEX].last_data;
        size_t actual_size = writer[TEST_INDEX].last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(TEST_CASE->expected_data, TEST_CASE->expected_size, actual_data, actual_size);
    }

    return TEST_COUNT;
}

int test_set_rdac4(void)
{
    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;
        uint8_t data;

        errno_t expected_err;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestSPIWriter writer[4];
    TestGPIO shdn[4];
    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[4];
    for (size_t i = 0; i < 4; i++)
    {
        test_spi_writer_init(&writer[i]);
        test_gpio_init(&shdn[i]);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403[i], (AD8400_AD8402_AD8403SPIWriter *)&writer[i], (AD8400_AD8402_AD8403GPIO *)&shdn[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .data = 0, .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .data = 0, /*  */ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______11'00000000 */ 0x03, 0x00}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[2], .data = 128, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______11'10000000 */ 0x03, 0x80}, .expected_size = 2},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[3], .data = 255, /**/ .expected_err = 0, .expected_data = (uint8_t[]){/* 0b______11'11111111 */ 0x03, 0xFF}, .expected_size = 2}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = ad8400_ad8402_ad8403_set_rdac4(TEST_CASE->ad8400_ad8402_ad8403, TEST_CASE->data);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        uint8_t *actual_data = writer[TEST_INDEX].last_data;
        size_t actual_size = writer[TEST_INDEX].last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(TEST_CASE->expected_data, TEST_CASE->expected_size, actual_data, actual_size);
    }

    return TEST_COUNT;
}

int test_enter_shutdown_mode(void)
{
    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;

        errno_t expected_err;
        TestGPIOState expected_state;
    } TestCase;

    TestSPIWriter writer[2];
    TestGPIO shdn[2];
    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[2];
    for (size_t i = 0; i < 2; i++)
    {
        test_spi_writer_init(&writer[i]);
        test_gpio_init(&shdn[i]);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403[i], (AD8400_AD8402_AD8403SPIWriter *)&writer[i], (AD8400_AD8402_AD8403GPIO *)&shdn[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .expected_err = 0, .expected_state = TEST_GPIO_LOW}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = ad8400_ad8402_ad8403_enter_shutdown_mode(TEST_CASE->ad8400_ad8402_ad8403);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        TestGPIOState actual_state = shdn[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_state, actual_state);
    }

    return TEST_COUNT;
}

int test_enter_operational_mode(void)
{
    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;

        errno_t expected_err;
        TestGPIOState expected_state;
    } TestCase;

    TestSPIWriter writer[2];
    TestGPIO shdn[2];
    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[2];
    for (size_t i = 0; i < 2; i++)
    {
        test_spi_writer_init(&writer[i]);
        test_gpio_init(&shdn[i]);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403[i], (AD8400_AD8402_AD8403SPIWriter *)&writer[i], (AD8400_AD8402_AD8403GPIO *)&shdn[i]) == 0);
    }

    TestCase TEST_CASES[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .expected_err = EINVAL},
                             {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .expected_err = 0, .expected_state = TEST_GPIO_HIGH}};

    TEST_FOR(TEST_CASES)
    {
        errno_t actual_err = ad8400_ad8402_ad8403_enter_operational_mode(TEST_CASE->ad8400_ad8402_ad8403);
        TEST_ASSERT_EQUAL_ERRNO_T(TEST_CASE->expected_err, actual_err);
        if (actual_err != 0)
        {
            continue;
        }

        TestGPIOState actual_state = shdn[TEST_INDEX].state;
        TEST_ASSERT_EQUAL_TEST_GPIO_STATE(TEST_CASE->expected_state, actual_state);
    }

    return TEST_COUNT;
}

int main(void)
{
    Test tests[] = {test_init,
                    test_set_rdac1,
                    test_set_rdac2,
                    test_set_rdac3,
                    test_set_rdac4,
                    test_enter_shutdown_mode,
                    test_enter_operational_mode};

    TEST_RUN(tests);
}