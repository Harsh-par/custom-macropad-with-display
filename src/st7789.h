#ifndef ST7789_H 
#define ST7789_H 

#include "pico/stdlib.h"

#include "hardware/spi.h"

typedef struct{
    spi_inst_t *spi;

    uint32_t spi_clk;
    uint16_t width;
    uint16_t height;
    
    uint8_t pin_blk;
    uint8_t pin_cs;
    uint8_t pin_dc;
    uint8_t pin_rst;
    uint8_t pin_scl;
    uint8_t pin_sda;
} st7789_t;

void st7789_init(st7789_t *display);

void st7789_set_window(st7789_t *display, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void st7789_draw_pixel(st7789_t *display, uint16_t x, uint16_t y, uint16_t color);
void st7789_fill_screen(st7789_t *display, uint16_t color);

void st7789_draw_rectangle(st7789_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void st7789_draw_rectangle_filled(st7789_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

void st7789_draw_circle(st7789_t *display, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color);
void st7789_draw_circle_filled(st7789_t *display, uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color);

void st7789_draw_bitmap(st7789_t *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *bitmap);

void st7789_draw_hline(st7789_t *display, uint16_t x, uint16_t y, uint16_t length, uint16_t color);
void st7789_draw_vline(st7789_t *display, uint16_t x, uint16_t y, uint16_t length, uint16_t color);

void st7789_draw_gradient(st7789_t *display, uint16_t gradient_color_start, uint16_t gradient_color_end);

#endif 
