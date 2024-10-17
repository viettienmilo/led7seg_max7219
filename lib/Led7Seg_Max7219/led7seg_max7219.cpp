#include "led7seg_max7219.h"

Led7seg_Max7219::Led7seg_Max7219(){
    m_spi_mode = true;
}

Led7seg_Max7219::Led7seg_Max7219(unsigned char _din, unsigned char _clk, unsigned char _cs)
    : m_din(_din), m_clk(_clk), m_cs(_cs){
    m_spi_mode = false;
}

Led7seg_Max7219::~Led7seg_Max7219(){}

void Led7seg_Max7219::write(unsigned char _addr, unsigned char _data){
    if(m_spi_mode){
        digitalWrite(SS, LOW);
        SPI.transfer(_addr);
        SPI.transfer(_data);
        digitalWrite(SS, HIGH);
    }
    else{
        digitalWrite(m_cs, LOW);
        shiftOut(m_din, m_clk, MSBFIRST, _addr);
        shiftOut(m_din, m_clk, MSBFIRST, _data);
        digitalWrite(m_cs, HIGH);
    }
}

void Led7seg_Max7219::begin(unsigned char _qty){
    m_qty = _qty;

    if(m_spi_mode){
        pinMode(SS, OUTPUT);
  	    SPI.begin();
  	    SPI.beginTransaction(SPISettings(12000000, MSBFIRST, SPI_MODE0));
    }
    else{
        pinMode(m_din, OUTPUT);
        pinMode(m_clk, OUTPUT);
        pinMode(m_cs, OUTPUT);
    }
	
	write(DISPLAYTEST_MODE_REG_ADDR, 0);
	write(SCAN_LIMIT_REG_ADDR, m_qty-1);
	write(DECODE_MODE_REG_ADDR, 0);
	clear();
	write(SHUTDOWN_MODE_REG_ADDR, 1);
}

void Led7seg_Max7219::setBrightness(unsigned char _intensity){
    if(_intensity <0 || _intensity > 15) return;
    write(INTENSITY_REG_ADDR, _intensity);
}

void Led7seg_Max7219::clear(){
    for(unsigned char led=1; led<9; led++){
        write(led, 0);
    }
}

void Led7seg_Max7219::setDigit(unsigned char _led, unsigned char _digit, bool _dp){
    unsigned char value = pgm_read_byte_near(LED_TABLE + _digit);
    _dp ? write(_led, value ^ (1<<7)) : write(_led, value);
}

void Led7seg_Max7219::setNumber(long _num, unsigned char _pos){
    unsigned char led = _pos;
    long digit = 0;
    bool minus = false;

    if(_num < 0){
        minus = true;
        _num *= -1;
    }

    while(led <= m_qty){
        digit = _num%10;
        setDigit(led, digit);
        _num /= 10;
        if(_num==0 && _num%10==0) break;
        led++;
    }
    if(minus) setDigit(++led, MINUS_SIGN);
}

void Led7seg_Max7219::setNumberH(long _addr, unsigned char _pos){
    unsigned char led = _pos;
    long digit = 0;

    while(led <= m_qty){
        digit = _addr%16;
        setDigit(led, digit);
        _addr /= 16;
        if(_addr==0 && _addr%16==0) break;
        led++;
    }
    if(led&1) setDigit(++led, 0);
    setDigit(++led, HEX_SIGN);
    setDigit(++led, 0);
}

void Led7seg_Max7219::setNumberF(float _num, unsigned char _precision, unsigned char _pos){
    unsigned char led = _pos;
    bool minus = false;

    if(_num < 0){
        minus = true;
        _num *= -1;
    }
    long value = _num*pow(10, _precision);
    long digit = 0;

    while(led <= m_qty){
        digit = value%10;
        (led==_precision+1) ? setDigit(led, digit, true) : setDigit(led, digit);
        value /= 10;
        if(value==0 && value%10==0) break;
        led++;
    }
    if(minus) setDigit(++led, MINUS_SIGN);
}