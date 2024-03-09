#include <ad8400_ad8402_ad8403.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_init(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403;
        AD8400_AD8402_AD8403SPIWriter *writer;
        AD8400_AD8402_AD8403GPIO *shdn;

        AD8400_AD8402_AD8403ErrNo expected_ret;
        AD8400_AD8402_AD8403SPIWriter *expected_writer;
        AD8400_AD8402_AD8403GPIO *expected_shdn;
    } TestCase;

    AD8400_AD8402_AD8403 ad8400_ad8402_ad8403[8];
    AD8400_AD8402_AD8403SPIWriter writer[8];
    AD8400_AD8402_AD8403GPIO shdn[8];

    TestCase cases[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = NULL, /* */ .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                        {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .writer = NULL, /* */ .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                        {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = &writer[2], .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                        {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[3], .writer = &writer[3], .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_writer = &writer[3], .expected_shdn = NULL},
                        {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = NULL, /* */ .shdn = &shdn[4], /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                        {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[5], .writer = NULL, /* */ .shdn = &shdn[5], /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                        {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = &writer[6], .shdn = &shdn[6], /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                        {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[7], .writer = &writer[7], .shdn = &shdn[7], /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_writer = &writer[7], .expected_shdn = &shdn[7]}};

    TEST_FOR(cases)
    {
        AD8400_AD8402_AD8403ErrNo actual_ret = ad8400_ad8402_ad8403_init(case_.ad8400_ad8402_ad8403, case_.writer, case_.shdn);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        AD8400_AD8402_AD8403SPIWriter *actual_writer = case_.ad8400_ad8402_ad8403->writer;
        if (case_.expected_writer != actual_writer)
        {
            fprintf(stderr, "index: %d, expected_writer: %#x, actual_writer: %#x\n",
                    i, case_.expected_writer, actual_writer);
            cnt++;
        }

        AD8400_AD8402_AD8403GPIO *actual_shdn = case_.ad8400_ad8402_ad8403->shdn;
        if (case_.expected_shdn != actual_shdn)
        {
            fprintf(stderr, "index: %d, expected_shdn: %#x, actual_shdn: %#x\n",
                    i, case_.expected_shdn, actual_shdn);
            cnt++;
        }
    }

    return cnt;
}

int test_set_rdac1(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        AD8400_AD8402_AD8403ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______00'00000000 */ 0x00, 0x00}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______00'10000000 */ 0x00, 0x80}, .expected_size = 2},
                        {.data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______00'11111111 */ 0x00, 0xFF}, .expected_size = 2}};

    TEST_FOR(cases)
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403_null = NULL;
        AD8400_AD8402_AD8403ErrNo actual_ret = ad8400_ad8402_ad8403_set_rdac1(NULL, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_EINVAL, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403;
        TestSPIWriter writer;
        test_spi_writer_init(&writer);
        TestGPIO shdn;
        test_gpio_init(&shdn);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (AD8400_AD8402_AD8403SPIWriter *)&writer, (AD8400_AD8402_AD8403GPIO *)&shdn) == AD8400_AD8402_AD8403_OK);

        actual_ret = ad8400_ad8402_ad8403_set_rdac1(&ad8400_ad8402_ad8403, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int test_set_rdac2(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        AD8400_AD8402_AD8403ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______01'00000000 */ 0x01, 0x00}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______01'10000000 */ 0x01, 0x80}, .expected_size = 2},
                        {.data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______01'11111111 */ 0x01, 0xFF}, .expected_size = 2}};

    TEST_FOR(cases)
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403_null = NULL;
        AD8400_AD8402_AD8403ErrNo actual_ret = ad8400_ad8402_ad8403_set_rdac2(NULL, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_EINVAL, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403;
        TestSPIWriter writer;
        test_spi_writer_init(&writer);
        TestGPIO shdn;
        test_gpio_init(&shdn);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (AD8400_AD8402_AD8403SPIWriter *)&writer, (AD8400_AD8402_AD8403GPIO *)&shdn) == AD8400_AD8402_AD8403_OK);

        actual_ret = ad8400_ad8402_ad8403_set_rdac2(&ad8400_ad8402_ad8403, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int test_set_rdac3(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        AD8400_AD8402_AD8403ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______10'00000000 */ 0x02, 0x00}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______10'10000000 */ 0x02, 0x80}, .expected_size = 2},
                        {.data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______10'11111111 */ 0x02, 0xFF}, .expected_size = 2}};

    TEST_FOR(cases)
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403_null = NULL;
        AD8400_AD8402_AD8403ErrNo actual_ret = ad8400_ad8402_ad8403_set_rdac3(NULL, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_EINVAL, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403;
        TestSPIWriter writer;
        test_spi_writer_init(&writer);
        TestGPIO shdn;
        test_gpio_init(&shdn);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (AD8400_AD8402_AD8403SPIWriter *)&writer, (AD8400_AD8402_AD8403GPIO *)&shdn) == AD8400_AD8402_AD8403_OK);

        actual_ret = ad8400_ad8402_ad8403_set_rdac3(&ad8400_ad8402_ad8403, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int test_set_rdac4(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        uint8_t data;

        AD8400_AD8402_AD8403ErrNo expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } TestCase;

    TestCase cases[] = {{.data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______11'00000000 */ 0x03, 0x00}, .expected_size = 2},
                        {.data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______11'10000000 */ 0x03, 0x80}, .expected_size = 2},
                        {.data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______11'11111111 */ 0x03, 0xFF}, .expected_size = 2}};

    TEST_FOR(cases)
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403_null = NULL;
        AD8400_AD8402_AD8403ErrNo actual_ret = ad8400_ad8402_ad8403_set_rdac4(NULL, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_EINVAL, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403;
        TestSPIWriter writer;
        test_spi_writer_init(&writer);
        TestGPIO shdn;
        test_gpio_init(&shdn);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (AD8400_AD8402_AD8403SPIWriter *)&writer, (AD8400_AD8402_AD8403GPIO *)&shdn) == AD8400_AD8402_AD8403_OK);

        actual_ret = ad8400_ad8402_ad8403_set_rdac4(&ad8400_ad8402_ad8403, case_.data);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        size_t actual_size = writer.last_size;
        TEST_ASSERT_EQUAL_SPI_WRITTEN(case_.expected_data, case_.expected_size, actual_data, actual_size);
    }

    return cnt;
}

int test_enter_shutdown_mode(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        AD8400_AD8402_AD8403ErrNo expected_ret;
        TestGPIOState expected_state;
    } TestCase;

    TestCase cases[] = {{.expected_ret = AD8400_AD8402_AD8403_OK, .expected_state = TEST_GPIO_LOW}};

    TEST_FOR(cases)
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403_null = NULL;
        AD8400_AD8402_AD8403ErrNo actual_ret = ad8400_ad8402_ad8403_enter_shutdown_mode(NULL);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_EINVAL, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403_shdn_null;
        TestSPIWriter writer_shdn_null;
        test_spi_writer_init(&writer_shdn_null);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403_shdn_null, (AD8400_AD8402_AD8403SPIWriter *)&writer_shdn_null, NULL) == AD8400_AD8402_AD8403_OK);
        actual_ret = ad8400_ad8402_ad8403_enter_shutdown_mode(&ad8400_ad8402_ad8403_shdn_null);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_OK, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403;
        TestSPIWriter writer;
        test_spi_writer_init(&writer);
        TestGPIO shdn;
        test_gpio_init(&shdn);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (AD8400_AD8402_AD8403SPIWriter *)&writer, (AD8400_AD8402_AD8403GPIO *)&shdn) == AD8400_AD8402_AD8403_OK);

        actual_ret = ad8400_ad8402_ad8403_enter_shutdown_mode(&ad8400_ad8402_ad8403);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        TestGPIOState actual_state = shdn.state;
        if (case_.expected_state != actual_state)
        {
            fprintf(stderr, "index: %d, expected_state: %s, actual_state: %s\n",
                    0, TEST_GPIO_STATE(case_.expected_state), TEST_GPIO_STATE(actual_state));
            cnt++;
            return cnt;
        }
    }

    return cnt;
}

int test_enter_operational_mode(void)
{
    printf("* %s\n", __func__);
    int cnt = 0;

    typedef struct TestCase
    {
        AD8400_AD8402_AD8403ErrNo expected_ret;
        TestGPIOState expected_state;
    } TestCase;

    TestCase cases[] = {{.expected_ret = AD8400_AD8402_AD8403_OK, .expected_state = TEST_GPIO_HIGH}};

    TEST_FOR(cases)
    {
        AD8400_AD8402_AD8403 *ad8400_ad8402_ad8403_null = NULL;
        AD8400_AD8402_AD8403ErrNo actual_ret = ad8400_ad8402_ad8403_enter_operational_mode(NULL);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_EINVAL, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403_shdn_null;
        TestSPIWriter writer_shdn_null;
        test_spi_writer_init(&writer_shdn_null);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403_shdn_null, (AD8400_AD8402_AD8403SPIWriter *)&writer_shdn_null, NULL) == AD8400_AD8402_AD8403_OK);
        actual_ret = ad8400_ad8402_ad8403_enter_operational_mode(&ad8400_ad8402_ad8403_shdn_null);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(AD8400_AD8402_AD8403_OK, actual_ret);

        AD8400_AD8402_AD8403 ad8400_ad8402_ad8403;
        TestSPIWriter writer;
        test_spi_writer_init(&writer);
        TestGPIO shdn;
        test_gpio_init(&shdn);
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (AD8400_AD8402_AD8403SPIWriter *)&writer, (AD8400_AD8402_AD8403GPIO *)&shdn) == AD8400_AD8402_AD8403_OK);

        actual_ret = ad8400_ad8402_ad8403_enter_operational_mode(&ad8400_ad8402_ad8403);
        TEST_ASSERT_EQUAL_AD8400_AD8402_AD8403_ERROR_RET(case_.expected_ret, actual_ret);
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        TestGPIOState actual_state = shdn.state;
        if (case_.expected_state != actual_state)
        {
            fprintf(stderr, "index: %d, expected_state: %s, actual_state: %s\n",
                    0, TEST_GPIO_STATE(case_.expected_state), TEST_GPIO_STATE(actual_state));
            cnt++;
            return cnt;
        }
    }

    return cnt;
}

int main(void)
{
    int cnt = 0;

    cnt += test_init();
    cnt += test_set_rdac1();
    cnt += test_set_rdac2();
    cnt += test_set_rdac3();
    cnt += test_set_rdac4();
    cnt += test_enter_shutdown_mode();
    cnt += test_enter_operational_mode();

    if (cnt == 0)
    {
        printf("OK\n");
        return 0;
    }
    else
    {
        fprintf(stderr, "%d errors found.\n", cnt);
        return 1;
    }
}