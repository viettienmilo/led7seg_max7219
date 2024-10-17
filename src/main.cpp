#include <led7seg_max7219.h>

Led7seg_Max7219 led7 = Led7seg_Max7219();

void setup() {
  led7.begin(8);
  led7.setBrightness(5);
}

void loop() {
  led7.clear();
  led7.setNumber(12345678);
  delay(2000);

  led7.clear();
  for(uint8_t i=8; i>0; i--){
    led7.setDigit(i, 18-i);
  }
  delay(2000);

  led7.clear();
  for(uint8_t i=5; i>0; i--){
    led7.setDigit(i, 23-i);
  }
  delay(2000);

  led7.clear();
  led7.setDigit(5, MINUS_SIGN);
  led7.setDigit(6, DEGREE);
  delay(2000);

  led7.clear();
  led7.setNumber(-7654321);
  delay(2000);

  led7.clear();
  led7.setDigit(2, 5, true);
  delay(2000);

  led7.clear();
  led7.setNumberF(-3.1415, 4);
  delay(2000);

  led7.clear();
  for(long i=256; i<512; i++){
    led7.setNumberH(i);
    delay(50);
    led7.clear();
  }
  delay(2000);
}