/*
 *  Name: Lena Kemmelmeier 
 *  Lab Partner: Emma Cornia
 *  Assignment: Lab 1
 *  Class: CPE 301 Spring 2024 (Section 1104)
 *  Date: Feb 7th 2024
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello from the Serial monitor!");

  pinMode(3, INPUT); // Input for LSB (button 1)
  pinMode(4, INPUT); // Input for MSB (button 2)

  pinMode(5, OUTPUT); //D0
  pinMode(6, OUTPUT); //D1
  pinMode(7, OUTPUT); //D2
  pinMode(8, OUTPUT); //D3
}

void loop() {
  // put your main code here, to run repeatedly:
  char input1 = digitalRead(3); // input for LSB (button 1)
  char input2 = digitalRead(4); // input for LSB (button 2)

  if(input1 == LOW && input2 == LOW){
    digitalWrite(5,HIGH); //D0 is high
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
  }
  else if(input1 == LOW && input2 == HIGH){
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH); //D1 is high
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
  }
  else if(input1 == HIGH && input2 == LOW){
    digitalWrite(5,LOW);
    digitalWrite(6,LOW); 
    digitalWrite(7,HIGH); //D2 is high
    digitalWrite(8,LOW);
  }
  else{
    digitalWrite(5,LOW);
    digitalWrite(6,LOW); 
    digitalWrite(7,LOW); 
    digitalWrite(8,HIGH); //D3 is high
  }
}
