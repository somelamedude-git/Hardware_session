void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(2);

  if(val==LOW){
    Serial.println("Object detected");
  }
  else{
    Serial.println("No object");
  }
}
