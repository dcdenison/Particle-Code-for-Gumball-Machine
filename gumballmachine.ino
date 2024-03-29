int ledR = D4;
int ledG = D3;
int servoPin = D0;

Servo gumballServo;

void setup()
{
    gumballServo.attach(servoPin);
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(servoPin, OUTPUT);

    Particle.function("knock", knock);

    Particle.function("yes", yes);
    Particle.function("no", no);

    Particle.function("testPasswd", testPasswd);

    //second was knockDetector

    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    gumballServo.attach(servoPin);
    gumballServo.write(220);
    //was 235 most recently
    //was 360
}

void loop()
{
}

int testPasswd(String password)
{
    Particle.publish("passwd", password, PRIVATE);
    if (password == "innovate")
    {
        return knock("knock");
    }
    return -1;
}

int yes(String command)
{
    return knock("knock");
}

int no(String command)
{
    return knock("no");
}

int knock(String command)
{
    //was knockDetector

    if (command == "knock")
    {

        Particle.publish("knock", "knock!", 60, PRIVATE);

        digitalWrite(ledR, LOW);
        digitalWrite(ledG, HIGH);
        gumballServo.attach(servoPin);
        delay(500);
        digitalWrite(ledG, LOW);
        gumballServo.write(50);
        //was 55
        delay(2000);

        gumballServo.write(220);
        //was 235 most recently
        //was 360
        delay(2000);
        gumballServo.detach();
        //was 1, going to try 0

        return 0;
    }
    else if (command == "no")
    {
        Particle.publish("knock", "no!", 60, PRIVATE);

        digitalWrite(ledR, HIGH);
        digitalWrite(ledG, LOW);
        gumballServo.attach(servoPin);
        gumballServo.write(235);
        //was 360
        delay(1000);
        gumballServo.detach();
        return 0;
    }
    else
    {
        return -1;
    }
}
