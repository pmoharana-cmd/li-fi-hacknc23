#define SOLARPANEL A0
#define MINIMUM_THRESHOLD 100
#define TIMING 29

void setup() {
  pinMode(SOLARPANEL, INPUT);
  Serial.begin(9600);
}

void loop() {
  int incomingData = analogRead(SOLARPANEL);
  int bitstream[8];

  if (incomingData > MINIMUM_THRESHOLD) {
    for (int i = 0; i < 8; i++) {
      if (analogRead(SOLARPANEL) > MINIMUM_THRESHOLD) {
        bitstream[i] = 1;
      }
      else {
        bitstream[i] = 0;
      }
      delay(TIMING);
    }
  
    int k = 0;
    for (int j = 1; j < 8; j++) {
      if (bitstream[j] == 1) {
        k = k + (1<<(7-j));
      }
    }
    char n = k;
    Serial.print(n);
  }
} 