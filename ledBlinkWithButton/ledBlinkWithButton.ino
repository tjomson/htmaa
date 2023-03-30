const int buttonPin = 11;
const int ledPin = 9;

int ledBlink = LOW;
int ledState = LOW;
long buttonState = LOW;

long previousMillisBlink = 0;
long previousMillisSwitch = 0;

void setup()
{
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);

    digitalWrite(ledPin, ledState);
}

void loop()
{
    unsigned long currentMillis = millis();
    int currentButtonState = digitalRead(buttonPin);

    if (currentMillis - previousMillisBlink > 500 && ledBlink == HIGH)
    {

        previousMillisBlink = currentMillis;
        ledState = !ledState;

        digitalWrite(ledPin, ledState);
    }

    if (currentMillis - previousMillisSwitch > 50 && buttonState == LOW && currentButtonState == HIGH)
    {

        previousMillisSwitch = currentMillis;
        ledBlink = !ledBlink;

        if (ledBlink == LOW)
        {
            digitalWrite(ledPin, LOW);
        }
    }

    buttonState = currentButtonState;
}
