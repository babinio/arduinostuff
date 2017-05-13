
int speaker = 3;  // plug the speaker into Arduino pin 2



int inputPin = 4; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status

int thisNote = 3;
int noteDuration ;
int pauseBetweenNotes;

int calibrationTime = 30; //the time we give the sensor to calibrate (10-60 secs according to the datasheet)



void setup() {
  // put your setup code here, to run once:
pinMode(inputPin, INPUT); // declare sensor as input
pinMode(speaker, OUTPUT);

Serial.begin(9600);

 // digitalWrite(inputPin, LOW);

    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);


}

void loop() {
 val = digitalRead(inputPin); // read input value
delay(500);
 Serial.println(val);
  

if (val == HIGH) { 
  
  playTone(600, 460);
  delay(50);


     if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }

    }
  
else {
      
      playTone(0, 0);
      delay(300);    
      if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

}


// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(speaker,HIGH);
        delayMicroseconds(period / 2);
       digitalWrite(speaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
