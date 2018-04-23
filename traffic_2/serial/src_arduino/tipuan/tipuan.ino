char c;

void setup() {                
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() <= 0) {}
  
  c = Serial.read();      // interrupt serial
  if (c=='t')
    Serial.print("y");
}
