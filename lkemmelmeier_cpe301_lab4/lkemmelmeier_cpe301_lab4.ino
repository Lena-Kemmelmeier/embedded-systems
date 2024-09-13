/*
 * Name: Lena Kemmelmeier
 * Lab Partner: Emma Cornia
 * Assignment: Lab 4
 * Class: CPE 301.1104
 * Date: 2/28/2024
*/

volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;


void setup() {
  Serial.begin(9600);
  //set pin B.6 to output
  *portDDRB |= 0x01 << 6;
}

bool quit = true;

void loop() {
  unsigned int frequency;
  unsigned char in_char;
  if(Serial.available()) {
    in_char = Serial.read();
    Serial.write(in_char);
    switch(in_char) {
      case 'a': {
        frequency = 440;
        quit = false;
        break;
      }
      case 'b': {
        frequency = 494;
        quit = false;
        break;
      }
      case 'c': {
        frequency = 523;
        quit = false;
        break;
      }
      case 'd': {
        frequency = 578;
        quit = false;
        break;
      }
      case 'e': {
        frequency = 659;
        quit = false;
        break;
      }
      case 'f': {
        frequency = 698;
        quit = false;
        break;
      }
      case 'g': {
        frequency = 784;
        quit = false;
        break;
      }
      case 'q': {
        quit = true;
      }
    }
  }

  if(!quit) {
    *portB |= (0x01 << 6);
    my_delay(frequency);
    *portB &= ~(0x01 << 6);
    my_delay(frequency);
  }
}

void my_delay(unsigned int freq) {
  // calc period
  double period = 1.0/double(freq);
  // 50% duty cycle
  double half_period = period/ 2.0f;
  // clock period def
  double clk_period = 0.0000000625;
  // calc ticks
  unsigned int ticks = half_period / clk_period;
  // stop the timer
  *myTCCR1B &= 0xF8;
  // set the counts
  *myTCNT1 = (unsigned int) (65536 - ticks);
  // start the timer
  * myTCCR1A = 0x0;
  * myTCCR1B |= 0b00000001;
  // wait for overflow
  while((*myTIFR1 & 0x01)==0); // 0b 0000 0000
  // stop the timer
  *myTCCR1B &= 0xF8;   // 0b 0000 0000
  // reset TOV           
  *myTIFR1 |= 0x01;
}
