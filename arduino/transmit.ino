#define LED_PIN 13

char encodedText[21];  // 20 characters max, +1 for null terminator

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);  // start the serial communication
    while (!Serial);     // wait for the serial port to connect

    // Serial.println("Enter the text to be encoded (max 20 characters):");
}

void loop() {
    int index = 0;
    while (true) {
        if (Serial.available() > 0) {
            char ch = Serial.read();
            if (ch == '\n' || ch == '\r' || index >= 20) {
                encodedText[index] = '\0';  // null terminate the string
                break;
            }
            encodedText[index++] = ch;
        }
    }

    int textLength = index;  // now we directly know the length of the entered text
    int asciiValues[20];
    int currentValue;
    int binaryRepresentation[8];

    for (int i = 0; i < textLength; i++) {
        asciiValues[i] = int(encodedText[i]);
    }

    for (int n = 0; n < textLength; n++) {
        currentValue = asciiValues[n];
        int intermediateBin[8];
        int reorderedBin[8];

        for (int z = 0; z < 8; z++) {
            intermediateBin[z] = currentValue % 2;
            currentValue = currentValue / 2;
        }

        for (int j = 7; j >= 0; j--) {
            reorderedBin[7 - j] = intermediateBin[j];
        }

        for (int p = 0; p < 8; p++) {
            if (reorderedBin[p] == 1) {
                binaryRepresentation[p] = HIGH;
            } else {
                binaryRepresentation[p] = LOW;
            }
        }

        binaryRepresentation[0] = HIGH;

        for (int i = 0; i < 8; i++) {
            digitalWrite(LED_PIN, binaryRepresentation[i]);
            delay(25);
        }

        digitalWrite(LED_PIN, LOW);
        delay(50);
    }
}