char c;
int state=0;

void setup() { 
  pinMode(13,OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() <= 0) {
    if (state==0)
      digitalWrite(13,LOW);
    else if (state==1){
      digitalWrite(13,HIGH);
      while(1){
        Serial.print("b201008292140929z");
        delay(1000);
        Serial.print("b201112084081930z");
        delay(1000);
      }
    }
  }
  
  c = Serial.read();
  if (c=='n')
    state=0;
  else if (c=='t'){
    Serial.print("ax");
    state=1;
  }
}
