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
  pinMode(4,OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int input = digitalRead(2);

  if (input == HIGH){
    digitalWrite(4,HIGH);
    Serial.println("Button has been presssed!");
    delay(1000);
  }
  else{
    digitalWrite(4,LOW);
  }

}
