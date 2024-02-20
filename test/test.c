#include <ad8400_ad8402_ad8403.h>
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_init(void)
{
    int cnt = 0;

    typedef struct test_case_t
    {
        ad8400_ad8402_ad8403_t *ad8400_ad8402_ad8403;
        ad8400_ad8402_ad8403_spi_writer_t *writer;
        ad8400_ad8402_ad8403_gpio_t *shdn;

        ad8400_ad8402_ad8403_error_t expected_ret;
        ad8400_ad8402_ad8403_spi_writer_t *expected_writer;
        ad8400_ad8402_ad8403_gpio_t *expected_shdn;
    } test_case_t;

    ad8400_ad8402_ad8403_t ad8400_ad8402_ad8403[8];
    ad8400_ad8402_ad8403_spi_writer_t writer[8];
    ad8400_ad8402_ad8403_gpio_t shdn[8];

    test_case_t cases[] = {{.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = NULL, /* */ .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[1], .writer = NULL, /* */ .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = &writer[2], .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[3], .writer = &writer[3], .shdn = NULL, /*    */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = NULL, /* */ .shdn = &shdn[4], /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[5], .writer = NULL, /* */ .shdn = &shdn[5], /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.ad8400_ad8402_ad8403 = NULL, /*               */ .writer = &writer[6], .shdn = &shdn[6], /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.ad8400_ad8402_ad8403 = &ad8400_ad8402_ad8403[7], .writer = &writer[7], .shdn = &shdn[7], /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_writer = &writer[7], .expected_shdn = &shdn[7]}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    for (size_t i = 0; i < size; i++)
    {
        test_case_t case_ = cases[i];

        ad8400_ad8402_ad8403_error_t actual_ret = ad8400_ad8402_ad8403_init(case_.ad8400_ad8402_ad8403, case_.writer, case_.shdn);
        if (case_.expected_ret != actual_ret)
        {
            fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",
                    i, TEST_AD8400_AD8402_AD8403_ERROR(case_.expected_ret), TEST_AD8400_AD8402_AD8403_ERROR(actual_ret));
            cnt++;
            continue;
        }
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        ad8400_ad8402_ad8403_spi_writer_t *actual_writer = case_.ad8400_ad8402_ad8403->writer_;
        if (case_.expected_writer != actual_writer)
        {
            fprintf(stderr, "index: %d, expected_writer: %#x, actual_writer: %#x\n",
                    i, case_.expected_writer, actual_writer);
            cnt++;
            continue;
        }

        ad8400_ad8402_ad8403_gpio_t *actual_shdn = case_.ad8400_ad8402_ad8403->shdn_;
        if (case_.expected_shdn != actual_shdn)
        {
            fprintf(stderr, "index: %d, expected_shdn: %#x, actual_shdn: %#x\n",
                    i, case_.expected_shdn, actual_shdn);
            cnt++;
            continue;
        }
    }

    return cnt;
}

int test_set(void)
{
    int cnt = 0;

    // Nothing is expected to happen.
    assert(ad8400_ad8402_ad8403_set(NULL, AD8400_AD8402_AD8403_RDAC1, 0) == AD8400_AD8402_AD8403_EINVAL);

    typedef struct test_case_t
    {
        ad8400_ad8402_ad8403_address_t addr;
        uint8_t data;

        ad8400_ad8402_ad8403_error_t expected_ret;
        uint8_t *expected_data;
        size_t expected_size;
    } test_case_t;

    test_case_t cases[] = {{.addr = AD8400_AD8402_AD8403_RDAC1, .data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______00'00000000 */ 0x00, 0x00}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC2, .data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______01'00000000 */ 0x01, 0x00}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC3, .data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______10'00000000 */ 0x02, 0x00}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC4, .data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______11'00000000 */ 0x03, 0x00}, .expected_size = 2},
                           {.addr = 255, /*                  */ .data = 0, /*  */ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.addr = AD8400_AD8402_AD8403_RDAC1, .data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______00'10000000 */ 0x00, 0x80}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC2, .data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______01'10000000 */ 0x01, 0x80}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC3, .data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______10'10000000 */ 0x02, 0x80}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC4, .data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______11'10000000 */ 0x03, 0x80}, .expected_size = 2},
                           {.addr = 255, /*                  */ .data = 128, /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL},
                           {.addr = AD8400_AD8402_AD8403_RDAC1, .data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______00'11111111 */ 0x00, 0xFF}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC2, .data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______01'11111111 */ 0x01, 0xFF}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC3, .data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______10'11111111 */ 0x02, 0xFF}, .expected_size = 2},
                           {.addr = AD8400_AD8402_AD8403_RDAC4, .data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_OK, .expected_data = (uint8_t[]){/* 0b______11'11111111 */ 0x03, 0xFF}, .expected_size = 2},
                           {.addr = 255, /*                  */ .data = 255, /**/ .expected_ret = AD8400_AD8402_AD8403_EINVAL}};
    size_t size = sizeof(cases) / sizeof(test_case_t);

    for (size_t i = 0; i < size; i++)
    {
        test_case_t case_ = cases[i];

        ad8400_ad8402_ad8403_t ad8400_ad8402_ad8403;
        test_spi_writer_t writer;
        test_spi_writer_init(&writer);
        ad8400_ad8402_ad8403_gpio_t shdn;
        shdn.set_high = test_null_gpio_set;
        shdn.set_low = test_null_gpio_set;
        assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (ad8400_ad8402_ad8403_spi_writer_t *)&writer, (ad8400_ad8402_ad8403_gpio_t *)&shdn) == AD8400_AD8402_AD8403_OK);

        ad8400_ad8402_ad8403_error_t actual_ret = ad8400_ad8402_ad8403_set(&ad8400_ad8402_ad8403, case_.addr, case_.data);
        if (case_.expected_ret != actual_ret)
        {
            fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",
                    i, TEST_AD8400_AD8402_AD8403_ERROR(case_.expected_ret), TEST_AD8400_AD8402_AD8403_ERROR(actual_ret));
            cnt++;
            continue;
        }
        if (actual_ret != AD8400_AD8402_AD8403_OK)
        {
            continue;
        }

        size_t actual_size = writer.last_size;
        if (case_.expected_size != actual_size)
        {
            fprintf(stderr, "index: %d, expected_size: %d, actual_size: %d\n",
                    i, case_.expected_size, actual_size);
            cnt++;
            continue;
        }

        uint8_t *actual_data = writer.last_data;
        if (!test_spi_data_equals(case_.expected_data, actual_data, actual_size))
        {
            fprintf(stderr, "index: %d,\n", i);
            for (size_t j = 0; j < actual_size; j++)
            {
                if (case_.expected_data[j] != actual_data[j])
                {
                    fprintf(stderr, "  expected_data[%d]: %d, actual_data[%d]: %d\n",
                            j, case_.expected_data[j], j, actual_data[j]);
                }
            }
            cnt++;
            continue;
        }
    }

    return cnt;
}

int test_enter_shutdown_mode(void)
{
    int cnt = 0;

    // Nothing is expected to happen.
    assert(ad8400_ad8402_ad8403_enter_shutdown_mode(NULL) == AD8400_AD8402_AD8403_EINVAL);

    ad8400_ad8402_ad8403_error_t expected_ret = AD8400_AD8402_AD8403_OK;
    test_gpio_state_t expected_state = TEST_GPIO_LOW;

    ad8400_ad8402_ad8403_t ad8400_ad8402_ad8403;
    ad8400_ad8402_ad8403_spi_writer_t writer;
    writer.write = test_null_spi_writer_write;
    test_gpio_t shdn;
    test_gpio_init(&shdn);
    assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (ad8400_ad8402_ad8403_spi_writer_t *)&writer, (ad8400_ad8402_ad8403_gpio_t *)&shdn) == AD8400_AD8402_AD8403_OK);

    ad8400_ad8402_ad8403_error_t actual_ret = ad8400_ad8402_ad8403_enter_shutdown_mode(&ad8400_ad8402_ad8403);
    if (expected_ret != actual_ret)
    {
        fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",
                0, TEST_AD8400_AD8402_AD8403_ERROR(expected_ret), TEST_AD8400_AD8402_AD8403_ERROR(actual_ret));
        cnt++;
        return cnt;
    }
    if (actual_ret != AD8400_AD8402_AD8403_OK)
    {
        return cnt;
    }

    test_gpio_state_t actual_state = shdn.state;
    if (expected_state != actual_state)
    {
        fprintf(stderr, "index: %d, expected_state: %s, actual_state: %s\n",
                0, TEST_GPIO_STATE(expected_state), TEST_GPIO_STATE(actual_state));
        cnt++;
        return cnt;
    }

    return cnt;
}

int test_enter_operational_mode(void)
{
    int cnt = 0;

    // Nothing is expected to happen.
    assert(ad8400_ad8402_ad8403_enter_operational_mode(NULL) == AD8400_AD8402_AD8403_EINVAL);

    ad8400_ad8402_ad8403_error_t expected_ret = AD8400_AD8402_AD8403_OK;
    test_gpio_state_t expected_state = TEST_GPIO_HIGH;

    ad8400_ad8402_ad8403_t ad8400_ad8402_ad8403;
    ad8400_ad8402_ad8403_spi_writer_t writer;
    writer.write = test_null_spi_writer_write;
    test_gpio_t shdn;
    test_gpio_init(&shdn);
    assert(ad8400_ad8402_ad8403_init(&ad8400_ad8402_ad8403, (ad8400_ad8402_ad8403_spi_writer_t *)&writer, (ad8400_ad8402_ad8403_gpio_t *)&shdn) == AD8400_AD8402_AD8403_OK);

    ad8400_ad8402_ad8403_error_t actual_ret = ad8400_ad8402_ad8403_enter_operational_mode(&ad8400_ad8402_ad8403);
    if (expected_ret != actual_ret)
    {
        fprintf(stderr, "index: %d, expected_ret: %s, actual_ret: %s\n",
                0, TEST_AD8400_AD8402_AD8403_ERROR(expected_ret), TEST_AD8400_AD8402_AD8403_ERROR(actual_ret));
        cnt++;
        return cnt;
    }
    if (actual_ret != AD8400_AD8402_AD8403_OK)
    {
        return cnt;
    }

    test_gpio_state_t actual_state = shdn.state;
    if (expected_state != actual_state)
    {
        fprintf(stderr, "index: %d, expected_state: %s, actual_state: %s\n",
                0, TEST_GPIO_STATE(expected_state), TEST_GPIO_STATE(actual_state));
        cnt++;
        return cnt;
    }

    return cnt;
}

int main(void)
{
    int cnt = 0;

    printf("* test_init\n");
    cnt += test_init();
    printf("* test_set\n");
    cnt += test_set();
    printf("* test_enter_shutdown_mode\n");
    cnt += test_enter_shutdown_mode();
    printf("* test_enter_operational_mode\n");
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