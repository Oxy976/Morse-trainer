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
  "А",
  "Б",
  "В",
  "Г",
  "Д",
  "Е",
  "Ж",
  "З",
  "И",
  "Й",
  "К",
  "Л",
  "М",
  "Н",
  "О",
  "П",
  "Р",
  "С",
  "Т",
  "У",
  "Ф",
  "Х",
  "Ц",
  "Ч",
  "Ш",
  "Щ",
  "Ъ",
  "Ы",
  "Ь",
  "Э",
  "Ю",
  "Я",
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
  "ай-даа",
  "беей-ба-ра-бан",
  "цыы-па-цыы-па",
  "доо-ми-ки",
  "есть",
  "фи-ли-моон-чик",
  "гаа-раа-жи",
  "хи-ми-чи-те",
  "и-ди",
  "йош-каа-раа-лаа",
  "каак-же-таак",
  "ли-моон-чи-ки",
  "маа-маа",
  "наа-те",
  "оо-коо-лоо",
  "пи-лаа-поо-ёт",
  "щуу-каа-жи-вааа",
  "ре-бяяяя-та",
  "сам-та-кой",
  "таам",
  "у-бе-гуу",
  "я-бук-ва-жее",
  "вол-чаа-таа",
  "тоо-мяг-кий-знаак",
  "ыы-не-наа-доо",
  "заа-каа-ти-киO",
  "чее-лоо-вее-чик",
  "шаа-раа-ваа-рыы",
  "твёёр-дыый-не-мяяг-киий",
  "э-ле-роо-ни-ки",
  "ю-ли-ааа-наа",
  "я-маал-я-маал",
  "од-наа-гоо-лоо-ваа",
  "две-не-хоо-роо-шоо",
  "три-те-бе-маа-лоо",
  "че-ты-ре-ча-сааа",
  "пя-ти-ле-ти-е",
  "шееесть-пе-ре-да-ю",
  "сеемь-сеемь-хо-ро-шо",
  "во-семь-маль-чи-ков",
  "дее-вяя-тоо-гоо-жди",
  "саа-мыый-длиин-ныый-нооль"
};

int MorseCodes[] =
{
  0,1,-1,-1,-1, // а
  1,0,0,0,-1, // б
  1,0,1,0,-1, // ц
  1,0,0,-1,-1, // д
  0,-1,-1,-1,-1, // е
  0,0,1,0,-1,  // ф
  1,1,0,-1,-1, // г
  0,0,0,0,-1,  // х
  0,0,-1,-1,-1,  // и
  0,1,1,1,-1, // й
  1,0,1,-1,-1, // к
  0,1,0,0,-1, // л
  1,1,-1,-1,-1, // м
  1,0,-1,-1,-1,  // н
  1,1,1,-1,-1, // о
  0,1,1,0,-1,  // п
  1,1,0,1,-1,  // щ
  0,1,0,-1,-1, // р
  0,0,0,-1,-1, // с
  1,-1,-1,-1,-1, // т
  0,0,1,-1,-1, // у
  0,0,0,1,-1,  // ж
  0,1,1,-1,-1, // в
  1,0,0,1,-1,  // ь
  1,0,1,1,-1, // ы
  1,1,0,0,-1, // з
  1,1,1,0,-1, // ч
  1,1,1,1,-1, // ш
  1,1,0,1,1, // ъ
  0,0,1,0,0, // э
  0,0,1,1,-1, // ю
  0,1,0,1,-1, // я
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
    M5.Lcd.print(utf8rus(MorseTelephony[i])[0]);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(120, 50);
    M5.Lcd.print(utf8rus(MorseTelephony[i]));
    M5.Lcd.setCursor(120, 80);
    M5.Lcd.print(utf8rus(MorsePhonic[i]));
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


/* Recode russian fonts from UTF-8 to Windows-1251 */

String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
