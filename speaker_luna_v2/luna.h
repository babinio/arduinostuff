class luna {
int inputPin; // choose the input pin (for PIR sensor)
int speaker;  // plug the speaker into Arduino pin 3

int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status



public:

    luna(int pin, int speak) {
      this->inputPin = pin;
      this->speaker = speak;
    }
    
    void setup() {
      pinMode(inputPin, INPUT); // declare sensor as input
      pinMode(speaker, OUTPUT);
      Serial.begin(9600);
      calibrate(30);
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


//playtone fuction

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

  //calibrate motion detection

  void    calibrate (int calibrationTime) {
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
      Serial.println(" done");
      Serial.println("SENSOR ACTIVE");
      delay(50);
    }
    
};
