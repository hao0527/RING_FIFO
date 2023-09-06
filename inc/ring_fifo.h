#ifndef __RING_FIFO_H__
#define __RING_FIFO_H__

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const void *buffer;           // 数据块地址
    const uint16_t capacity;      // 数据最大存放个数
    const uint16_t element_size;  // 单个数据占用的字节数
    const uint16_t cover;         // 是否支持覆盖
    uint16_t head;                // 起始下标
    uint16_t tail;                // 结尾下标
    uint16_t size;                // 数据实际个数
} RING_FIFO;

/**
 * @brief  定义 RING_FIFO 变量
 * @param  Type 存放的数据类型
 * @param  BufName RING_FIFO 变量名称
 * @param  Size 最多可以存放的数据数量
 * @param  Cover 是否支持覆盖 (0 / 1)
 * @retval None
 */
#define ring_define(Type, BufName, Size, Cover)        \
    Type __##BufName##_data[Size];                     \
    RING_FIFO BufName = {                              \
        .buffer = __##BufName##_data,                  \
        .capacity = Size,                              \
        .element_size = sizeof(__##BufName##_data[0]), \
        .cover = Cover,                                \
        .head = 0,                                     \
        .tail = 0,                                     \
        .size = 0,                                     \
    }

/**
 * @brief  定义 RING_FIFO 静态变量
 * @param  Type 存放的数据类型
 * @param  BufName RING_FIFO 变量名称
 * @param  Size 最多可以存放的数据数量
 * @param  Cover 是否支持覆盖 (0 / 1)
 * @retval None
 */
#define ring_define_static(Type, BufName, Size, Cover) \
    static Type __##BufName##_data[Size];              \
    static RING_FIFO BufName = {                       \
        .buffer = __##BufName##_data,                  \
        .capacity = Size,                              \
        .element_size = sizeof(__##BufName##_data[0]), \
        .cover = Cover,                                \
        .head = 0,                                     \
        .tail = 0,                                     \
        .size = 0,                                     \
    }

/**
 * @brief  放入单个数据
 * @param  ring RING_FIFO 变量的地址
 * @param  element 待存入数据的地址
 * @retval 是否成功放入，失败时返回值小于 0（支持覆盖时，参数正确传入则永远返回0）
 */
int8_t ring_push(RING_FIFO *ring, const void *element);

/**
 * @brief  取出单个数据
 * @param  ring RING_FIFO 变量的地址
 * @param  element 取出数据的存放地址
 * @retval 是否成功取出，失败时返回值小于 0
 */
int8_t ring_pop(RING_FIFO *ring, void *element);

/**
 * @brief  放入多个数据
 * @param  ring RING_FIFO 变量的地址
 * @param  elements 待存入数据块的首地址
 * @param  num 待存入数据的个数
 * @retval 成功放入几个（支持覆盖时，参数正确传入则返回值与数据个数相等）
 */
uint16_t ring_push_mult(RING_FIFO *ring, const void *elements, uint16_t num);

/**
 * @brief  取出多个数据
 * @param  ring RING_FIFO 变量的地址
 * @param  elements 取出数据块的存放地址
 * @param  num 待取出数据的个数
 * @retval 成功取出几个
 */
uint16_t ring_pop_mult(RING_FIFO *ring, void *elements, uint16_t num);

/**
 * @brief  重置 RING_FIFO
 * @param  ring RING_FIFO 变量的地址
 * @retval None
 */
void ring_reset(RING_FIFO *ring);

/**
 * @brief  RING_FIFO 是否为空
 * @param  ring RING_FIFO 变量的地址
 * @retval 为空返回 1
 */
int8_t ring_is_empty(RING_FIFO *ring);

/**
 * @brief  RING_FIFO 是否已满
 * @param  ring RING_FIFO 变量的地址
 * @retval 已满返回 1
 */
int8_t ring_is_full(RING_FIFO *ring);

/**
 * @brief  获取 RING_FIFO 内实际数据数量
 * @param  ring RING_FIFO 变量的地址
 * @retval RING_FIFO 内实际数据数量
 */
uint16_t ring_size(RING_FIFO *ring);

/**
 * @brief  打印 RING_FIFO 内部信息
 * @param  ring RING_FIFO 变量的地址
 * @retval None
 */
void print_ring(RING_FIFO *ring);

#ifdef __cplusplus
}
#endif

#endif
