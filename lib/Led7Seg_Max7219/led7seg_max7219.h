#ifndef LED7SEG_MAX7219_H
#define LED7SEG_MAX7219_H

#include <Arduino.h>
#include <SPI.h>

#define SHUTDOWN_MODE_REG_ADDR 0x0C
#define DISPLAYTEST_MODE_REG_ADDR 0x0F
#define INTENSITY_REG_ADDR 0x0A
#define DECODE_MODE_REG_ADDR 0x09
#define SCAN_LIMIT_REG_ADDR 0x0B

const unsigned char LED_TABLE[] PROGMEM = {
  0x7E, // digit 0
  0x30, // digit 1
  0x6D, // digit 2
  0x79, // digit 3
  0x33, // digit 4
  0x5B, // digit 5
  0x5F, // digit 6
  0x70, // digit 7
  0x7F, // digit 8
  0x7B, // digit 9
  0x77, // A
  0x1F, // b
  0x4E, // C
  0x3D, // d
  0x4F, // E
  0x47, // F
  0x37, // H
  0x0E, // L
  0x67, // P
  0x3E, // U
  0x3B, // y
  0x01, // sign -
  0x63, // degree
};

#define MINUS_SIGN 21
#define DEGREE 22
#define HEX_SIGN 16

class Led7seg_Max7219 {
  public:
    Led7seg_Max7219();
    Led7seg_Max7219(unsigned char _din, unsigned char _clk, unsigned char _cs);
    ~Led7seg_Max7219();

    void write(unsigned char _addr, unsigned char _data);
    void begin(unsigned char _qty=8);
    void setBrightness(unsigned char _intensity=5);
    void setDigit(unsigned char _led, unsigned char _value, bool _dp=false);
    void setNumber(long _num, unsigned char _pos=1);
    void setNumberF(float _num, unsigned char _precision=2, unsigned char _pos=1);
    void setNumberH(long _addr, unsigned char _pos=1);
    void clear();

  private:
    unsigned char m_qty=8;
    unsigned char m_din, m_clk, m_cs;
    bool m_spi_mode;
};

#endif