// put your setup code here, to run once:
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
#include <Wire.h>
//for the display {
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoNunchuk.h>
//}


//for the ultrasonic sensor {
#define echoPin 2
#define triggerPin  10
//}
ArduinoNunchuk nunchuk = ArduinoNunchuk();
#define LEDpin 46
int pot_set;
int deg;
long duration;
int distance;

int  val1;
int pcode;



//}

Servo servo1;//create servo object to control a servo
Servo servo2;//create servo object to control a servo
Servo servo3;//create servo object to control a servo
Servo servo4;//create servo object to control a servo
Servo servo5;//create servo object to control a servo



//}
void setup() {
  servo1.attach(9);
  servo2.attach(6);
  servo3.attach(5);
  servo4.attach(3);
  servo5.attach(11);
  pinMode(4, INPUT);
  nunchuk.init();
  //for the ultrasonic sensor {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(19200);
  //}
  pinMode(LEDpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nunchuk.update();
  val1 = 1;


  if (nunchuk.zButton == HIGH) {
    if (nunchuk.cButton == HIGH) {
      val1 = 3;
    } else {
      val1 = 1;
    }
  }
  if (val1 == 1)
    if ( nunchuk.zButton == HIGH) {
      pcode = 2;
      if (nunchuk.analogY > 140) {
        servo3.write(servo3.read() - val1);
        servo2.write(servo2.read());
      }
      if (nunchuk.analogY < 110) {
        servo3.write(servo3.read() + val1);
        servo2.write(servo2.read());
      }
      if (nunchuk.analogX < 100) {
        servo5.write(servo5.read() + val1);
      }
      if (nunchuk.analogX > 145) {
        servo5.write(servo5.read() - val1);
      }
    } else {
      pcode = 1;
    }

  if (val1 == 1) {
    if (nunchuk.cButton == HIGH) {
      servo1.write(90);
      servo2.write(90);
      servo3.write(90);
      servo4.write(90);
      servo5.write(25);
      digitalWrite(LEDpin,HIGH);
    }else{
      digitalWrite(LEDpin,LOW);
    }
  }
  //y axis control {
  if (pcode == 1) {

    if (nunchuk.analogY > 145) {
      if (servo2.read() == 145) {

        servo3.write(servo3.read() - val1);
      }
      else {
        servo2.write(servo2.read() + val1);
      }

    }

    if (nunchuk.analogY < 110) {
      if (servo2.read() == 45) {
        servo3.write(servo3.read() + val1);
      }
      else {
        servo2.write(servo2.read() - val1);
      }

    }


    //x or z axis control{

    if (nunchuk.analogX < 100) {
      servo1.write(servo1.read() + val1);
    }
    if (nunchuk.analogX > 145) {
      servo1.write(servo1.read() - val1);
    }
  }
  //debug();

  delay(20);//wait for 0.05second
}

void debug() {

  Serial.print("joyY: ");
  Serial.print(nunchuk.analogY);
  Serial.print("joyX: ");
  Serial.print(nunchuk.analogX);
  Serial.print(" cButtion:");
  Serial.print(nunchuk.cButton);
  Serial.print("servo: ");
  Serial.println(servo2.read());
}
