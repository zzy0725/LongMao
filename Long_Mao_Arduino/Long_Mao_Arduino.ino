void setup()
{
  Serial.begin(9600);
  pinMode(9, OUTPUT);//LED(B)
  pinMode(10, OUTPUT);//LED(G)
  pinMode(11, OUTPUT);//LED(R)
  pinMode(13, OUTPUT); //LEDred
  pinMode(5, OUTPUT);//L9110(B1)
  pinMode(6, OUTPUT);//L9110(B2)
  pinMode(3, OUTPUT);//BIG LED
  pinMode(2, OUTPUT);//BY8301(4)
  pinMode(4, OUTPUT);//BY8301(5)
  pinMode(7, OUTPUT);//BY8301(6)
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  Serial.println("READY TO GO");
}

void loop()
{
  SCAN();
}

void SCAN()
{
  int w = analogRead(1);
  int x = analogRead(2);
  int y = analogRead(3);
  int z = analogRead(4);
  if (w < 300 && x < 300 && y < 300 && z < 300)//0000（异常状态自动复位@）
  {
    Serial.println("0000(error state)");
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
  if (w < 300 && x < 300 && y < 300 && z > 300)//0001（十分钟后闹钟@）
  {
    Serial.println("0001");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    for (int t = 600; t >= 0; t--)
      delay(1000);
    digitalWrite(2, LOW);
    delay(200);
    digitalWrite(2, HIGH);
  }
  if (w < 300 && x < 300 && y > 300 && z < 300)//0010（晚上好灯@）
  {
    Serial.println("0010");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    analogWrite(11, 0);
    analogWrite(10, 0);
    analogWrite(9, 0);
    digitalWrite(4, HIGH);
    for (int r = 0; r <= 100; r++)
    {
      analogWrite(11, r);
      delay(1);
    }
    digitalWrite(4, LOW);
    for (int g = 0; g <= 50; g++)
    {
      analogWrite(10, g);
      delay(10);
    }
    for (int b = 0; b <= 2; b++)
    {
      analogWrite(9, b);
      delay(15);
    }
    delay(2000);
    for (int r = 100; r <= 210; r++)
    {
      analogWrite(11, r);
      delay(15);
    }
    delay(4000);
    for (int r = 210; r >= 0; r--)
    {
      analogWrite(11, r);
      delay(10);
    }
    for (int g = 30; g >= 0; g--)
    {
      analogWrite(10, g);
      delay(28);
    }
    for (int b = 2; b >= 0; b--)
    {
      analogWrite(9, b);
      delay(100);
    }
  }
  if (w < 300 && x < 300 && y > 300 && z > 300)//0011（我爱你灯@）
  {
    Serial.println("0011");
    LED_XINTIAO();
  }
  if (w < 300 && x > 300 && y < 300 && z < 300)//0100（音乐灯光秀@@）
  {
    Serial.println("0100");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
    delay(200);
    digitalWrite(4, HIGH);
    delay(6000);
  }
  if (w < 300 && x > 300 && y < 300 && z > 300)//0101（打开灯@）
  {
    Serial.println("0101");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    for (int l = 0; l <= 230; l++)
    {
      analogWrite(3, l);
      delay(5);
    }
    delay(1000);
  }
  if (w < 300 && x > 300 && y > 300 && z < 300)//0110（关灯@）
  {
    Serial.println("0110");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_white_FADEOUT();
    for (int l = 200; l >= 0; l--)
    {
      analogWrite(3, l);
      delay(5);
    }
    delay(1000);
  }
  if (w < 300 && x > 300 && y > 300 && z > 300)//0111（亮度加@）
  {
    Serial.println("0111");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_white_FADEIN();
    delay(1000);
  }
  if (w > 300 && x < 300 && y < 300 && z < 300)//1000（亮度减@）
  {
    Serial.println("1000");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_white_FADEOUT();
    delay(1000);
  }
  if (w > 300 && x < 300 && y < 300 && z > 300)//1001（彩色灯@）
  {
    Serial.println("1001");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    for (int x = 3; x >= 0; x--)
    {
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 240; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 1; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 1; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 240);
      analogWrite(10, 1);
      analogWrite(9, 1);
      for (int r = 240; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 1; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 1; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 30; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 200; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 10; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 30);
      analogWrite(10, 200);
      analogWrite(9, 10);
      for (int r = 30; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 200; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 10; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 220; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 30; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 200; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 220);
      analogWrite(10, 30);
      analogWrite(9, 200);
      for (int r = 220; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 30; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 200; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 220; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 40; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 5; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 220);
      analogWrite(10, 40);
      analogWrite(9, 5);
      for (int r = 220; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 40; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 5; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 30; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 90; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 200; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 30);
      analogWrite(10, 90);
      analogWrite(9, 200);
      for (int r = 30; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 90; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 200; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 220; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 15; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 15; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 220);
      analogWrite(10, 15);
      analogWrite(9, 15);
      for (int r = 220; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 15; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 15; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 220; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 70; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 1; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 220);
      analogWrite(10, 70);
      analogWrite(9, 1);
      for (int r = 220; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 70; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 1; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      for (int r = 0; r < 240; r++)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 0; g < 130; g++)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 0; b < 70; b++)
      {
        analogWrite(9, b);
        delay(1);
      }
      analogWrite(11, 240);
      analogWrite(10, 130);
      analogWrite(9, 70);
      for (int r = 240; r >= 0; r--)
      {
        analogWrite(11, r);
        delay(1);
      }
      for (int g = 130; g >= 0; g--)
      {
        analogWrite(10, g);
        delay(1);
      }
      for (int b = 70; b >= 0; b--)
      {
        analogWrite(9, b);
        delay(1);
      }
    }
  }
  if (w > 300 && x < 300 && y > 300 && z < 300)//1010（橙色灯@）
  {
    Serial.println("1010");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_orange_FADEIN();
    delay(1000);
  }
  if (w > 300 && x < 300 && y > 300 && z > 300)//1011（绿色灯@）
  {
    Serial.println("1011");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_green_FADEIN();
    delay(1000);
  }
  if (w > 300 && x > 300 && y < 300 && z < 300)//1100（蓝色灯@）
  {
    Serial.println("1100");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_blue_FADEIN();
    delay(1000);
  }
  if (w > 300 && x > 300 && y < 300 && z > 300)//1101（粉色灯@）
  {
    Serial.println("1101");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_pink_FADEIN();
    delay(1000);
  }
  if (w > 300 && x > 300 && y > 300 && z < 300)//1110（紫色灯@）
  {
    Serial.println("1110");
    digitalWrite(7, LOW);
    delay(200);
    digitalWrite(7, HIGH);
    LED_purple_FADEIN();
    delay(1000);
  }
  if (w > 300 && x > 300 && y > 300 && z > 300)//1111（空状态@）
  {
    Serial.println("1111(normal state)");
  }
  delay(300);
}

void LED_red_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 240; r++)
  {
    analogWrite(11, r);
    delay(2);
  }
  for (int g = 0; g < 1; g++)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 0; b < 1; b++)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_orange_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 220; r++)
  {
    analogWrite(11, r);
    delay(2);
  }
  for (int g = 0; g < 40; g++)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 0; b < 5; b++)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_green_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 30; r++)
  {
    analogWrite(11, r);
    delay(10);
  }
  for (int g = 0; g < 200; g++)
  {
    analogWrite(10, g);
    delay(2);
  }
  for (int b = 0; b < 10; b++)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_blue_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 30; r++)
  {
    analogWrite(11, r);
    delay(10);
  }
  for (int g = 0; g < 90; g++)
  {
    analogWrite(10, g);
    delay(4);
  }
  for (int b = 0; b < 200; b++)
  {
    analogWrite(9, b);
    delay(2);
  }
}

void LED_purple_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 220; r++)
  {
    analogWrite(11, r);
    delay(2);
  }
  for (int g = 0; g < 30; g++)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 0; b < 200; b++)
  {
    analogWrite(9, b);
    delay(5);
  }
}

void LED_pink_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 220; r++)
  {
    analogWrite(11, r);
    delay(2);
  }
  for (int g = 0; g < 15; g++)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 0; b < 15; b++)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_yellow_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 220; r++)
  {
    analogWrite(11, r);
    delay(1);
  }
  for (int g = 0; g < 70; g++)
  {
    analogWrite(10, g);
    delay(5);
  }
  for (int b = 0; b < 1; b++)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_white_FADEIN()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r < 240; r++)
  {
    analogWrite(11, r);
    delay(1);
  }
  for (int g = 0; g < 130; g++)
  {
    analogWrite(10, g);
    delay(5);
  }
  for (int b = 0; b < 70; b++)
  {
    analogWrite(9, b);
    delay(5);
  }
}

void LED_red_FADEOUT()
{
  analogWrite(11, 240);
  analogWrite(10, 1);
  analogWrite(9, 1);
  for (int r = 240; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(2);
  }
  for (int g = 1; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 1; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_orange_FADEOUT()
{
  analogWrite(11, 220);
  analogWrite(10, 40);
  analogWrite(9, 5);
  for (int r = 220; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(2);
  }
  for (int g = 40; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 5; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_green_FADEOUT()
{
  analogWrite(11, 30);
  analogWrite(10, 200);
  analogWrite(9, 10);
  for (int r = 30; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(10);
  }
  for (int g = 200; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(2);
  }
  for (int b = 10; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_blue_FADEOUT()
{
  analogWrite(11, 30);
  analogWrite(10, 90);
  analogWrite(9, 200);
  for (int r = 30; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(10);
  }
  for (int g = 90; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(4);
  }
  for (int b = 200; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(2);
  }
}

void LED_purple_FADEOUT()
{
  analogWrite(11, 220);
  analogWrite(10, 30);
  analogWrite(9, 200);
  for (int r = 220; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(5);
  }
  for (int g = 30; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 200; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(2);
  }
}

void LED_pink_FADEOUT()
{
  analogWrite(11, 220);
  analogWrite(10, 15);
  analogWrite(9, 15);
  for (int r = 220; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(2);
  }
  for (int g = 15; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(10);
  }
  for (int b = 15; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_yellow_FADEOUT()
{
  analogWrite(11, 220);
  analogWrite(10, 70);
  analogWrite(9, 1);
  for (int r = 220; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(1);
  }
  for (int g = 70; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(5);
  }
  for (int b = 1; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(10);
  }
}

void LED_white_FADEOUT()
{
  analogWrite(11, 240);
  analogWrite(10, 130);
  analogWrite(9, 70);
  for (int r = 240; r >= 0; r--)
  {
    analogWrite(11, r);
    delay(1);
  }
  for (int g = 130; g >= 0; g--)
  {
    analogWrite(10, g);
    delay(5);
  }
  for (int b = 70; b >= 0; b--)
  {
    analogWrite(9, b);
    delay(5);
  }
}

void LED_NORMAL()
{
  analogWrite(11, 0);
  analogWrite(10, 0);
  analogWrite(9, 0);
  for (int r = 0; r <= 47; r++)
  {
    analogWrite(11, r);
    delay(1);
  }
  for (int g = 0; g <= 242; g++)
  {
    analogWrite(10, g);
    delay(1);
  }
  for (int b = 0; b <= 124; b++)
  {
    analogWrite(9, b);
    delay(1);
  }
  for (int r = 47; r <= 140; r++)
  {
    analogWrite(11, r);
    delay(1);
  }
  for (int g = 242; g >= 21; g--)
  {
    analogWrite(10, g);
    delay(1);
  }
  for (int b = 124; b >= 54; b--)
  {
    analogWrite(9, b);
    delay(1);
  }
  for (int r = 140; r <= 240; r++)
  {
    analogWrite(11, r);
    delay(1);
  }
  for (int g = 21; g <= 130; g++)
  {
    analogWrite(10, g);
    delay(1);
  }
  for (int b = 54; b <= 70; b++)
  {
    analogWrite(9, b);
    delay(1);
  }
}

void LED_XINTIAO()
{
  analogWrite(11, 0);
  delay(500);
  for (int c = 0; c < 2; c++)
  {
    for (int b = 0; b < 2; b++)
    {
      for (int a = 0; a < 200; a++)
      {
        analogWrite(11, a);
        delayMicroseconds(650);
      }
      for (int a = 200; a > 10; a--)
      {
        analogWrite(11, a);
        delayMicroseconds(650);
      }
    }
    delay(500);
  }
  analogWrite(11, 0);
}
