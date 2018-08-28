#include <M5Stack.h>

extern unsigned char logo[];

int dot_width = 10;
int dot_height = 10;
int dash_width = 40;
int dash_height = 20;
int padding = 10;
int dot_time = 250;
int dash_time = dot_time * 3;
int padding_time = dot_time;

String MorseTelephony[] =
{
  "Alfa",
  "Bravo",
  "Charlie",
  "Delta",
  "Echo",
  "Foxtrot",
  "Golf",
  "Hotel",
  "India",
  "Juliett",
  "Kilo",
  "Lima",
  "Mike",
  "November",
  "Oscar",
  "Papa",
  "Quebec",
  "Romeo",
  "Sierra",
  "Tango",
  "Uniform",
  "Victor",
  "Whiskey",
  "Xray",
  "Yankee",
  "Zulu",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "0"
};

String MorsePhonic[] =
{
  "AL-FAH",
  "BRAH-VOH",
  "CHAR-LEE",
  "DELL-TAH",
  "ECK-OH",
  "FOKS-TROT",
  "GOLF",
  "HOH-TEL",
  "IN-DEE-AH",
  "JEW-LEE-ETT",
  "KEY-LOH",
  "LEE-MAH",
  "MIKE",
  "NO-VEM-BER",
  "OSS-CAH",
  "PAH-PAH",
  "KEH-BECK",
  "ROW-ME-OH",
  "SEE-AIR-RAH",
  "TANG-GO",
  "YOU-NEE-FORM",
  "VIK-TAH",
  "WISS-KEY",
  "ECKS-RAY",
  "YANG-KEY",
  "ZOO-LOO",
  "WUN",
  "TOO",
  "TREE",
  "FOW-ER",
  "FIFE",
  "SIX",
  "SEV-EN",
  "AIT",
  "NIN-ER",
  "ZEE-RO"
};

int MorseCodes[] =
{
  0,1,-1,-1,-1, // A
  1,0,0,0,-1, // B
  1,0,1,0,-1, // C
  1,0,0,-1,-1, // D
  0,-1,-1,-1,-1, // E
  0,0,1,0,-1,  //F
  1,1,0,-1,-1, // G
  0,0,0,0,-1,  // H
  0,0,-1,-1,-1,  // I
  0,1,1,1,-1, // J
  1,0,1,-1,-1, // K
  0,1,0,0,-1, // L
  1,1,-1,-1,-1, // M
  1,0,-1,-1,-1,  // N
  1,1,1,-1,-1, // O
  0,1,1,0,-1,  // P
  1,1,0,1,-1,  // Q
  0,1,0,-1,-1, // R
  0,0,0,-1,-1, // S
  1,-1,-1,-1,-1, // T
  0,0,1,-1,-1, // U
  0,0,0,1,-1,  // V
  0,1,1,-1,-1, // W
  1,0,0,1,-1,  // X
  1,0,1,1,-1, // Y
  1,1,0,0,-1, // Z
  0,1,1,1,1, // 1
  0,0,1,1,1, // 2
  0,0,0,1,1, // 3
  0,0,0,0,1, // 4
  0,0,0,0,0, // 5
  1,0,0,0,0, // 6
  1,1,0,0,0, // 7
  1,1,1,0,0, // 8
  1,1,1,1,0, // 9
  1,1,1,1,1 // 0
};

void Play(int i) {
  for (int j = i * 5; j < i * 5 + 5; j++)
  {
    int k = j - i * 5;
    int x = 40 + (k * (dash_width + padding));
    int y = 160;
    delay(padding_time);
    if (MorseCodes[j] == 0)
    {
      M5.Lcd.fillCircle(x + dash_width / 2, y + dot_height, dot_height, 0x0000);
      M5.Speaker.tone(630);
      delay(dot_time);
      M5.Speaker.mute();
    } 
    else if (MorseCodes[j] == 1)
    {
      M5.Lcd.fillRect(x, y, dash_width, dash_height, 0x0000);
      M5.Speaker.tone(630);
      delay(dash_time);
      M5.Speaker.mute();
    }  
    else;
  }
}

void setup() {
  M5.begin();
  M5.Lcd.drawBitmap(0, 0, 320, 240, (uint16_t *)logo);
  while (true)
  {
    if (M5.BtnA.wasPressed())
    {
      break;
    }
    M5.update();
  }
  M5.Lcd.fillScreen(0x0000);
  delay(250);
}

void loop() {
  for (int i = 0; i < sizeof(MorsePhonic) / sizeof(String); i++)
  {
    M5.Lcd.fillScreen(0xffff);
    M5.Lcd.drawRoundRect(40, 40, 64, 64, 10, 0x0000);
    M5.Lcd.setTextColor(0x0000);
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(60, 55);
    M5.Lcd.print(MorseTelephony[i][0]);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(120, 50);
    M5.Lcd.print(MorseTelephony[i]);
    M5.Lcd.setCursor(120, 80);
    M5.Lcd.print(MorsePhonic[i]);
    Play(i);
    while (true)
    {
      int UserMorseCodeTime[5] = {};
      int actual_time = 0;
      for (int j = i * 5; j < i * 5 + 5; j++)
      {
        if (MorseCodes[j] > -1)
        {
          int k = j - i * 5;
          int previous_time = 0;         
          while (true)
          {
            if (M5.BtnB.wasPressed())
            {
              previous_time = millis();
              M5.Speaker.tone(630);
            }
            if (M5.BtnB.wasReleased())
            {
              M5.Speaker.mute();
              UserMorseCodeTime[k] = millis() - previous_time;
              M5.update();
              break;
            }
            if (M5.BtnC.wasReleased())
            {
              Play(i);
            }
            M5.update();
          }
        }
      }
      int r = true;
      for (int j = i * 5; j < i * 5 + 5; j++)
      {
        int k = j - i * 5;
        if (MorseCodes[j] == 0)
          actual_time = dot_time;
        else if (MorseCodes[j] == 1)
          actual_time = dash_time;
        if (UserMorseCodeTime[k] == 0)
          break;
        int abs_ = abs(actual_time - UserMorseCodeTime[k]);
        int x = 50 + k * 50;
        int y = 190;
        M5.Lcd.fillRect(x, y, 305, 30, WHITE);
        M5.Lcd.setCursor(x, y);
        if (abs_ > actual_time / 4)
        {
          r = false;
          M5.Lcd.print(":(");
        }
        else
        {
          M5.Lcd.print(":)");
        }
      }
      if (r)
        break;
    }
  }
}
