
#include <Servo.h>

Servo servo1; //Servos
Servo servo2;
Servo servo3;
Servo servo4;



int button1Presses = 0; //Button values
boolean button2Pressed = false;
boolean button3Pressed = false;

int pot1Val; //Potansiyometre değerleri
int pot2Val;
int pot3Val;
int pot1Angle;
int pot2Angle;
int pot3Angle;
int pot4Angle = 110;
int ara;
int ara2;
int ara3;

int servo1PosSaves[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; //position saves
int servo2PosSaves[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int servo3PosSaves[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int servo4PosSaves[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

unsigned long previousmillis = 0;
unsigned long currentmillis;
////                                        ////
////////////YAPILANDIRMA AYARLARI///////////////
////                                        ///


//Butonların pin giriş numaraları
const int button1 = 7; //Robot kol eksenlerinin konumlarını kaydeden buton
const int button2 = 4; //Kaydedilen konumları sürekli tekrarlar
const int button3 = 8; //tutucu (kıskaç)servoyu açıp kapamaya yarayan tuş

//Servoların mekanik olarak hareket edebilecekleri açılar
const int servo1min = 0;
const int servo1max = 179;
const int servo2min = 50;
const int servo2max = 150;
const int servo3min = 50;
const int servo3max = 155;
const int servo4min = 60;
const int servo4max = 110;


const int araloop = 12; //Robot kol otomatik hareket ederken her açıdan sonra bekleme süresi(milisaniye) bu değeri azaltarak kolu hızlandırabilirsiniz








void setup() {

  servo1.attach(6);//robot kolun en altındaki servo motor (omuz servosu diyebiliriz)
  servo2.attach(9);//dirsek
  servo3.attach(10);//bilek
  servo4.attach(3);//kıskaç

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pot1Angle = servo1.read();
  pot2Angle = servo2.read();
  pot3Angle = servo3.read();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //pot1Angle=map(analogRead(3),0,1023,servo1min,servo1max);
  currentmillis = millis(); //timer başlar

  if (digitalRead(button3) == HIGH && button3Pressed == false)
  {
    pot4Angle = servo4min;
    button3Pressed = true;
    if (digitalRead(button3) == HIGH)
    {
      while (1)
      {

        if (digitalRead(button3) == LOW)
        {
          break;
        }
      }
    }
    Serial.println("kiskac kapali");
  }

  else if (digitalRead(button3) == HIGH && button3Pressed == true)
  {
    pot4Angle = servo4max;
    button3Pressed = false;
    if (digitalRead(button3) == HIGH)
    {
      while (1)
      {

        if (digitalRead(button3) == LOW)
        {
          break;
        }
      }
    }
    Serial.println("kiskac acik");
  }


  if (button2Pressed == false)
  {

    if (analogRead(1) < 500)//servo 1 hız-delay
    {
      ara = map(analogRead(1), 500, 0, 100, 15);
    }
    else if (analogRead(1) > 500)
    {
      ara = map(analogRead(1), 500, 1023, 100, 15);
    }
    else
    {
      ara = 100;
    }

    /////////////////////////////////////////////////


    if (analogRead(2) < 500) //servo 2 hız-delay
    {
      ara2 = map(analogRead(2), 0, 500, 15, 100);
    }
    else if (analogRead(2) > 500)
    {
      ara2 = map(analogRead(2), 500, 1023, 100, 15);
    }
    else
    {
      ara2 = 100;
    }

    ///////////////////////////////////////////////////////////////////

    if (analogRead(3) < 500) //servo 2 hız-delay
    {
      ara3 = map(analogRead(3), 0, 500, 12, 200);
    }
    else if (analogRead(3) > 500)
    {
      ara3 = map(analogRead(3), 500, 1023, 200, 12);
    }
    else
    {
      ara3 = 100;
    }

    ///////////////////////////////////////////////////////////////////
    if ((analogRead(3) < 400) && (currentmillis - previousmillis >= ara3)) //Servo potansiyometre değerine göre açısı azalır ve potansiyometre değerine göre hız belirlenir
    {
      pot1Angle--;
      if (pot1Angle < servo1min)  
        pot1Angle = servo1min;
      previousmillis = currentmillis;
    }
    else if (analogRead(3) > 600 && (currentmillis - previousmillis >= ara3))//Servo potansiyometre değerine göre açısı artar ve potansiyometre değerine göre hız belirlenir
    {
      pot1Angle++;
      if (pot1Angle > servo1max) 
        pot1Angle = servo1max;
      previousmillis = currentmillis;

    } 
    //////////////////////////////////////////////////////

    if ((analogRead(1) < 350) && (currentmillis - previousmillis >= ara)) //Servo potansiyometre değerine göre açısı azalır ve potansiyometre değerine göre hız belirlenir
    {
      pot2Angle--;


      if (pot2Angle < servo2min)   //Servo açısının değeri 125 den yukarı çıkmaz
        pot2Angle = servo2min;


      previousmillis = currentmillis;


    }
    else if (analogRead(1) > 650 && (currentmillis - previousmillis >= ara))//Servo potansiyometre değerine göre açısı artar ve potansiyometre değerine göre hız belirlenir
    {

      pot2Angle++;


      if (pot2Angle > servo2max) //Servo açısının değeri 50 den aşağı düşmez
        pot2Angle = servo2max;

      previousmillis = currentmillis;

    }

    ////////////////////////////////////////////////////////////////////////////////
    //////////////////////Servo2/////////////////

    if ((analogRead(2) < 350) && (currentmillis - previousmillis >= ara2)) //Servo potansiyometre değerine göre açısı azalır ve potansiyometre değerine göre hız belirlenir
    {
      pot3Angle++;
      if (pot3Angle > servo3max)  //Servo açısının değeri 60 dan aşağı düşmez
        pot3Angle = servo3max;



      previousmillis = currentmillis;

    }
    else if (analogRead(2) > 650 && (currentmillis - previousmillis >= ara2)) //Servo potansiyometre değerine göre açısı artar ve potansiyometre değerine göre hız belirlenir
    {
      previousmillis = currentmillis;
      pot3Angle--;
      if (pot3Angle < servo3min)  //Servo açısının değeri 155 den yukarı çıkmaz
        pot3Angle = servo3min;


      previousmillis = currentmillis;
    }

    //    pot1Val = analogRead(pot1); // This will read the values from the potentimeters and store it...
    //    pot1Angle = map(pot1Val, 0, 1023, 0, 179); // ... and this will map the values from the potentiometers to values the servos can use and store it for later use
    //    pot2Val = analogRead(pot2);
    //    pot2Angle = map(pot2Val, 0, 1023, 155, 60);
    //    pot3Val = analogRead(pot3);
    //    pot3Angle = map(pot3Val, 0, 1023, 50, 140);

    servo1.write(pot1Angle); // These will make the servos move to the mapped angles
    servo2.write(pot2Angle);
    servo3.write(pot3Angle);
    servo4.write(pot4Angle);
  }

  if (digitalRead(button1) == HIGH) { // This will check how many times button1 is pressed and save the positions to an array depending on how many times it is pressed; switch/case works like a if statement
    button1Presses++;

    if (digitalRead(button1) == HIGH)
    {

      while (1)
      {
        if (digitalRead(button1) == LOW)
        { delay(50);
          break;
        }
      }

      switch (button1Presses) {
        case 1:
          Serial.println(" ");
          servo1PosSaves[0] = pot1Angle;
          servo2PosSaves[0] = pot2Angle;
          servo3PosSaves[0] = pot3Angle;
          servo4PosSaves[0] = pot4Angle;


          //digitalWrite(LED1, HIGH);

          Serial.println("Pos 1 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;
        case 2:
          Serial.println(" ");
          servo1PosSaves[1] = pot1Angle;
          servo2PosSaves[1] = pot2Angle;
          servo3PosSaves[1] = pot3Angle;
          servo4PosSaves[1] = pot4Angle;


          //digitalWrite(LED2, HIGH);
          Serial.println("Pos 2 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;
        case 3:
          Serial.println(" ");
          servo1PosSaves[2] = pot1Angle;
          servo2PosSaves[2] = pot2Angle;
          servo3PosSaves[2] = pot3Angle;
          servo4PosSaves[2] = pot4Angle;

          //digitalWrite(LED3, HIGH);
          Serial.println("Pos 3 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;
        case 4:
          Serial.println(" ");
          servo1PosSaves[3] = pot1Angle;
          servo2PosSaves[3] = pot2Angle;
          servo3PosSaves[3] = pot3Angle;
          servo4PosSaves[3] = pot4Angle;



          //digitalWrite(LED4, HIGH);
          Serial.println("Pos 4 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;
        case 5:
          Serial.println(" ");
          servo1PosSaves[4] = pot1Angle;
          servo2PosSaves[4] = pot2Angle;
          servo3PosSaves[4] = pot3Angle;
          servo4PosSaves[4] = pot4Angle;


          //digitalWrite(LED5, HIGH);
          Serial.println("Pos 5 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 6:
          Serial.println(" ");
          servo1PosSaves[5] = pot1Angle;
          servo2PosSaves[5] = pot2Angle;
          servo3PosSaves[5] = pot3Angle;
          servo4PosSaves[5] = pot4Angle;

          Serial.println("Pos 6 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 7:
          Serial.println(" ");
          servo1PosSaves[6] = pot1Angle;
          servo2PosSaves[6] = pot2Angle;
          servo3PosSaves[6] = pot3Angle;
          servo4PosSaves[6] = pot4Angle;


          Serial.println("Pos 7 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 8:
          Serial.println(" ");
          servo1PosSaves[7] = pot1Angle;
          servo2PosSaves[7] = pot2Angle;
          servo3PosSaves[7] = pot3Angle;
          servo4PosSaves[7] = pot4Angle;

          Serial.println("Pos 8 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 9:
          Serial.println(" ");
          servo1PosSaves[8] = pot1Angle;
          servo2PosSaves[8] = pot2Angle;
          servo3PosSaves[8] = pot3Angle;
          servo4PosSaves[8] = pot4Angle;


          Serial.println("Pos 9 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;


        case 10:
          Serial.println(" ");
          servo1PosSaves[9] = pot1Angle;
          servo2PosSaves[9] = pot2Angle;
          servo3PosSaves[9] = pot3Angle;
          servo4PosSaves[9] = pot4Angle;

          Serial.println("Pos 10 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 11:
          Serial.println(" ");
          servo1PosSaves[10] = pot1Angle;
          servo2PosSaves[10] = pot2Angle;
          servo3PosSaves[10] = pot3Angle;
          servo4PosSaves[10] = pot4Angle;

          Serial.println("Pos 11 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;


        case 12:
          Serial.println(" ");
          servo1PosSaves[11] = pot1Angle;
          servo2PosSaves[11] = pot2Angle;
          servo3PosSaves[11] = pot3Angle;
          servo4PosSaves[11] = pot4Angle;

          Serial.println("Pos 12 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;


        case 13:
          Serial.println(" ");
          servo1PosSaves[12] = pot1Angle;
          servo2PosSaves[12] = pot2Angle;
          servo3PosSaves[12] = pot3Angle;
          servo4PosSaves[12] = pot4Angle;

          Serial.println("Pos 13 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 14:
          Serial.println(" ");
          servo1PosSaves[13] = pot1Angle;
          servo2PosSaves[13] = pot2Angle;
          servo3PosSaves[13] = pot3Angle;
          servo4PosSaves[13] = pot4Angle;

          Serial.println("Pos 14 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;
        case 15:
          Serial.println(" ");
          servo1PosSaves[14] = pot1Angle;
          servo2PosSaves[14] = pot2Angle;
          servo3PosSaves[14] = pot3Angle;
          servo4PosSaves[14] = pot4Angle;

          Serial.println("Pos 15 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 16:
          Serial.println(" ");
          servo1PosSaves[15] = pot1Angle;
          servo2PosSaves[15] = pot2Angle;
          servo3PosSaves[15] = pot3Angle;
          servo4PosSaves[15] = pot4Angle;

          Serial.println("Pos 16 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 17:
          Serial.println(" ");
          servo1PosSaves[16] = pot1Angle;
          servo2PosSaves[16] = pot2Angle;
          servo3PosSaves[16] = pot3Angle;
          servo4PosSaves[16] = pot4Angle;

          Serial.println("Pos 17 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 18:
          Serial.println(" ");
          servo1PosSaves[17] = pot1Angle;
          servo2PosSaves[17] = pot2Angle;
          servo3PosSaves[17] = pot3Angle;
          servo4PosSaves[17] = pot4Angle;

          Serial.println("Pos 18 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;


        case 19:
          Serial.println(" ");
          servo1PosSaves[18] = pot1Angle;
          servo2PosSaves[18] = pot2Angle;
          servo3PosSaves[18] = pot3Angle;
          servo4PosSaves[18] = pot4Angle;

          Serial.println("Pos 19 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 20:
          Serial.println(" ");
          servo1PosSaves[19] = pot1Angle;
          servo2PosSaves[19] = pot2Angle;
          servo3PosSaves[19] = pot3Angle;
          servo4PosSaves[19] = pot4Angle;

          Serial.println("Pos 20 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 21:
          Serial.println(" ");
          servo1PosSaves[20] = pot1Angle;
          servo2PosSaves[20] = pot2Angle;
          servo3PosSaves[20] = pot3Angle;
          servo4PosSaves[20] = pot4Angle;

          Serial.println("Pos 21 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 22:
          Serial.println(" ");
          servo1PosSaves[21] = pot1Angle;
          servo2PosSaves[21] = pot2Angle;
          servo3PosSaves[21] = pot3Angle;
          servo4PosSaves[21] = pot4Angle;

          Serial.println("Pos 22 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;


        case 23:
          Serial.println(" ");
          servo1PosSaves[22] = pot1Angle;
          servo2PosSaves[22] = pot2Angle;
          servo3PosSaves[22] = pot3Angle;
          servo4PosSaves[22] = pot4Angle;

          Serial.println("Pos 23 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 24:
          Serial.println(" ");
          servo1PosSaves[23] = pot1Angle;
          servo2PosSaves[23] = pot2Angle;
          servo3PosSaves[23] = pot3Angle;
          servo4PosSaves[23] = pot4Angle;

          Serial.println("Pos 24 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;


        case 25:
          Serial.println(" ");
          servo1PosSaves[24] = pot1Angle;
          servo2PosSaves[24] = pot2Angle;
          servo3PosSaves[24] = pot3Angle;
          servo4PosSaves[24] = pot4Angle;

          Serial.println("Pos 25 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 26:
          Serial.println(" ");
          servo1PosSaves[25] = pot1Angle;
          servo2PosSaves[25] = pot2Angle;
          servo3PosSaves[25] = pot3Angle;
          servo4PosSaves[25] = pot4Angle;

          Serial.println("Pos 26 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;


        case 27:
          Serial.println(" ");
          servo1PosSaves[26] = pot1Angle;
          servo2PosSaves[26] = pot2Angle;
          servo3PosSaves[26] = pot3Angle;
          servo4PosSaves[26] = pot4Angle;

          Serial.println("Pos 27 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 28:
          Serial.println(" ");
          servo1PosSaves[27] = pot1Angle;
          servo2PosSaves[27] = pot2Angle;
          servo3PosSaves[27] = pot3Angle;
          servo4PosSaves[27] = pot4Angle;

          Serial.println("Pos 28 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 29:

          servo1PosSaves[28] = pot1Angle;
          servo2PosSaves[28] = pot2Angle;
          servo3PosSaves[28] = pot3Angle;
          servo4PosSaves[28] = pot4Angle;
          Serial.println(" ");
          Serial.println("Pos 29 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;

        case 30:

          servo1PosSaves[29] = pot1Angle;
          servo2PosSaves[29] = pot2Angle;
          servo3PosSaves[29] = pot3Angle;
          servo4PosSaves[29] = pot4Angle;
          Serial.println(" ");
          Serial.println("Pos 30 Saved");
          Serial.println(servo1PosSaves[button1Presses - 1]);
          Serial.println(servo2PosSaves[button1Presses - 1]);
          Serial.println(servo3PosSaves[button1Presses - 1]);
          Serial.println(servo4PosSaves[button1Presses - 1]);
          break;
      }
    }
  }

  if (digitalRead(button2) == HIGH) { // Pretty self-explnatory here

    button2Pressed = true;
    if (digitalRead(button2) == HIGH)
    {
      while (1)
      {
        if (digitalRead(button2) == LOW)
          break;
      }
    }

  }

  if (button2Pressed) { // if the boolean button2Press is true, then the servos will run though all their saved positions

    for (int i = 0; i < button1Presses; i++) {

      servokontrol(servo1PosSaves[i], servo2PosSaves[i], servo3PosSaves[i], servo4PosSaves[i]);

      delay(100);

      //servo1.write(servo1PosSaves[i]);
      // servo2.write(servo2PosSaves[i]);
      // servo3.write(servo3PosSaves[i]);
      //servo4.write(servo4PosSaves[i]);

      Serial.println(" potentimeter Angles: ");
      Serial.println(servo1PosSaves[i]);
      Serial.println(servo2PosSaves[i]);
      Serial.println(servo3PosSaves[i]);
      Serial.println(servo4PosSaves[i]);

    }

  }



}
void servokontrol(int konum1, int konum2, int konum3, int konum4)
{




  int araloop = 12;
  int aci1 = servo1.read();
  int aci2 = servo2.read();
  int aci3 = servo3.read();
  int aci4 = servo4.read();
  while ((aci1 != konum1) || (aci2 != konum2) || (aci3 != konum3) || (aci4 != konum4))
  {
    currentmillis = millis();

    if ((currentmillis - previousmillis >= araloop))
    {
      if (aci1 > konum1)
      {
        aci1--;
        servo1.write(aci1);

      }
      else if (aci1 < konum1)
      {
        aci1++;
        servo1.write(aci1);
      }


      if (aci2 > konum2)
      {
        aci2--;
        servo2.write(aci2);

      }
      else if (aci2 < konum2)
      {
        aci2++;
        servo2.write(aci2);
      }




      if (aci3 > konum3)
      {
        aci3--;
        servo3.write(aci3);

      }
      else if (aci3 < konum3)
      {
        aci3++;
        servo3.write(aci3);
      }



      if (aci4 > konum4)
      {
        aci4 -= 2;
        servo4.write(aci4);
        if (aci4 >= 110)
          delay(100);
      }
      else if (aci4 < konum4)
      {
        aci4 += 2;
        servo4.write(aci4);
        if (aci4 <= 60)
          delay(100);
      }




      //      //Serial("aci1:");
      //      Serial.println(aci1);
      //      //Serial("aci2:");
      //      Serial.println(aci2);
      //      //Serial("aci3:");
      //      Serial.println(aci3);
      //      //Serial("aci4:");
      //      Serial.println(aci4);
      previousmillis = currentmillis;
    }


  }

}

