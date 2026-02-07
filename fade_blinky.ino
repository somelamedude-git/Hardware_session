int brightness = 0;
int increment = 5;

void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  analogWrite(10, brightness);
  brightness = brightness + increment;
  if(brightness<=0 || brightness>=255){
    increment= -increment;
  }
  delay(30);
}
