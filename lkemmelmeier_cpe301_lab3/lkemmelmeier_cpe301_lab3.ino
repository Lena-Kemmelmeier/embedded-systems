/*
 *  Name: Lena Kemmelmeier 
 *  Lab Partner: Emma Cornia
 *  Assignment: Lab 3
 *  Class: CPE 301 Spring 2024 (Section 1104)
 *  Date: Feb 28th 2024
 */

// Define Port K Register Pointers
volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_k  = (unsigned char*) 0x107; 
volatile unsigned char* pin_k  = (unsigned char*) 0x106; 

// Define Port D Register Pointers
volatile unsigned char* port_d = (unsigned char*) 0x2B; 
volatile unsigned char* ddr_d  = (unsigned char*) 0x2A; 
volatile unsigned char* pin_d  = (unsigned char*) 0x29; 

// Define Port E Register Pointers
volatile unsigned char* port_e = (unsigned char*) 0x2E; 
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
volatile unsigned char* pin_e  = (unsigned char*) 0x2C; 



void setup() 
{
  // Initialize the Serial Port
  Serial.begin(9600);

  //set PK2 to INPUT
  *ddr_k &= ~(0x01 << 2);// clear bit 2

  // set PD0 to OUTPUT
  *ddr_d |= 0x01; // set bit 0 to 1

  // set PE3 to OUTPUT
  *ddr_e |= (0x01 << 3); // set bit 3 to 1

}

void loop() 
{
  if(*pin_k & (0x01 << 2)){
    *pin_d |= (0x01); // PD0 high
    *pin_e &= ~(0x01 << 3); // clear PE3
    Serial.println("button pressed!");
  }
  else{
    *pin_d &= ~(0x01);// clear PD0
    *pin_e |= (0x01 << 3); // PE3 high
    Serial.println("button not pressed!");
  }

}
