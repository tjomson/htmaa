const int sensLeft = 3;
const int sensRight = 2;

const int leftBackward = 10;
const int leftForward = 11;
const int rightForward = 12;
const int rightBackward = 13;

void setup()
{
    pinMode(sensLeft, INPUT);
    pinMode(sensRight, INPUT);

    pinMode(leftForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(rightBackward, OUTPUT);
}

void loop()
{
    int detectedLeft = digitalRead(sensLeft);
    int detectedRight = digitalRead(sensRight);

    if (detectedLeft == detectedRight)
    {
        spinLeftForward();
        spinRightForward();
    }
    else if (detectedLeft == LOW)
    {
        turnLeft();
    }
    else
    {
        turnRight();
    }
}

void spinRightForward()
{
    digitalWrite(rightForward, HIGH);
    digitalWrite(rightBackward, LOW);
}

void spinRightBackward()
{
    digitalWrite(rightForward, LOW);
    digitalWrite(rightBackward, HIGH);
}

void spinLeftBackward()
{
    digitalWrite(leftForward, HIGH);
    digitalWrite(leftBackward, LOW);
}

void spinLeftForward()
{
    digitalWrite(leftForward, LOW);
    digitalWrite(leftBackward, HIGH);
}

void turnRight()
{
    spinLeftForward();
    spinRightBackward();
}

void turnLeft()
{
    spinRightForward();
    spinLeftBackward();
}
