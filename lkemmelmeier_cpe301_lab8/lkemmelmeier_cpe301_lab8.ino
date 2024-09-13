/*
 * Name: Lena Kemmelmeier
 Partner: Emma Cornia
 * Date: 4/10/2024
 * Assignment: Lab 8
*/

/* UNR CPE 301 Lab - Interrupts
 * Frank Mascarich Fall 2022
 * This lab instructs students to write a program which uses interrupts
 * to generate a square wave on Port B Bit 6 (Digital 12) with a 
 * frequency dependent on a character received over serial.
 */

#define RDA 0x80
#define TBE 0x20

// UART Pointers
volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;
// GPIO Pointers
volatile unsigned char *portB =    (unsigned char *) 0x25;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
// Timer Pointers
volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;


char in_char;
int currentTicks;
bool timer_running = false;
//This array holds the tick values
unsigned int ticks[7]= {18182, 16194, 15296, 13629, 12140, 11461, 10204};
//This array holds the charachters to be entered, index echos the index of the ticks
unsigned char input[7]= {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

//global ticks counter

void setup() 
{                
  // set PB6 to output
  *portDDRB |= 0x40;
  // set PB6 LOW
  *portB &= 0xBF;
  // setup the Timer for Normal Mode, with the TOV interrupt enabled
  setup_timer_regs();
  // Start the UART
  U0Init(9600);
}

void loop() 
{
  // if we recieve a character from serial
  if (kbhit()) 
  {
    // read the character
    in_char = getChar();
    // echo it back
    putChar(in_char);
    // if it's the quit character
    if(in_char == 'q' || in_char == 'Q')
    {
      // set the current ticks to the max value
      currentTicks = 65535;
      // if the timer is running
      if(timer_running)
      {
        // stop the timer
        *myTCCR1B &= 0xF8;
        // set the flag to not running
        timer_running = 0;
        // set PB6 LOW
        *portB &= 0xBF;
      }
    }
    // otherwise we need to look for the char in the array
    else
    {
      // look up the character
      for(int i=0; i < 7; i++)
      {
        // if it's the character we received...
        if(in_char == input[i])
        {
          // set the ticks
          currentTicks = ticks[i];
          // if the timer is not already running, start it
          if(!timer_running)
          {
              // start the timer
              *myTCCR1B |= 0b00000001;
              // set the running flag
              timer_running = 1;
          }
        }
      }
    }
  }
}


// Timer setup function
void setup_timer_regs()
{
  // setup the timer control registers
  *myTCCR1A= 0x00;
  *myTCCR1B= 0X00;
  *myTCCR1C= 0x00;
  
  // reset the TOV flag
  *myTIFR1 |= 0x01;
  
  // enable the TOV interrupt
  *myTIMSK1 |= 0x01;
}


// TIMER OVERFLOW ISR
ISR(TIMER1_OVF_vect)
{
  // Stop the Timer
  *myTCCR1B &= 0xF8;
  // Load the Count
  *myTCNT1 =  (unsigned int) (65535 -  (unsigned long) (currentTicks));
  // Start the Timer
  *myTCCR1B |= 0b00000001;
  // if it's not the STOP amount
  if(currentTicks != 65535)
  {
    // XOR to toggle PB6
    *portB ^= 0x40;
  }
}
/*
 * UART FUNCTIONS
 */
void U0Init(int U0baud)
{
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 // Same as (FCPU / (16 * U0baud)) - 1;
 *myUCSR0A = 0x20;
 *myUCSR0B = 0x18;
 *myUCSR0C = 0x06;
 *myUBRR0  = tbaud;
}
unsigned char kbhit()
{
  return *myUCSR0A & RDA;
}
unsigned char getChar()
{
  return *myUDR0;
}
void putChar(unsigned char U0pdata)
{
  while((*myUCSR0A & TBE)==0);
  *myUDR0 = U0pdata;
}
