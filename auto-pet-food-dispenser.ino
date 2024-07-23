#include <DS3231.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

DS3231 rtc(A4, A5);
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int hourO, hourT, minO, minT, secO, secT, feedIntv, feedAmt, r[16];
boolean fTime, fInterval, fAmount;
String feedingTime;
char key;


void setup() {
  servo.attach(10);   
  rtc.begin();
  lcd.begin();
  servo.write(55); 
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.blink();
  char key = kpd.getKey();
  String amt;
  if (key == 'A') {
    setFeedTime();
  } else if (key == 'B') {
    setFeedClock();
  } else if (key == 'C') {
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(" Feed  Int  Amt ");
    lcd.setCursor(0, 1);
    feedingTime = String(r[0]) + String(r[1]) + ":" + String(r[2]) + String(r[3]);
    if (feedAmt == 1){
      amt = "Low";
    } else if (feedAmt == 2){
      amt = "Med";
    } else if(feedAmt == 3){
      amt = "High";
    } else {
      amt = "-";
    }
    lcd.print(feedingTime + "   " + feedIntv + "   " + amt + "    ");
    delay(1000);
  } else if (key == 'D') {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Feeding Time  ");
    lcd.setCursor(0,1);
    lcd.print("    Wait!...    ");
    delayAndFeed(1000);
    lcd.clear();
  }
  lcd.print("Time: ");
  String time = "";
  lcd.setCursor(7, 0);
  time = rtc.getTimeStr(); 
  hourT = time.charAt(0) - 48;
  hourO = time.charAt(1) - 48;
  minT = time.charAt(3) - 48;
  minO = time.charAt(4) - 48;
  secT = time.charAt(6) - 48;
  secO = time.charAt(7) - 48;
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  String d = rtc.getDateStr();
  d.replace('.', '/');
  lcd.print(d);

  if (feedIntv == 1) {
    if (hourT == r[0] && hourO == r[1] && minT == r[2] && minO == r[3] && ((secT*10 + secO) < 3)) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Feeding Time  ");
      lcd.setCursor(0,1);
      lcd.print("    Wait!...    ");
      if (feedAmt == 1) delayAndFeed(1000);
      else if (feedAmt == 2) delayAndFeed(2000);
      else if (feedAmt == 3) delayAndFeed(3000);
      lcd.clear();
    }
  } else if (feedIntv == 2) {
    // First feeding time
    if (hourT == r[0] && hourO == r[1] && minT == r[2] && minO == r[3] && ((secT*10 + secO) < 3)) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Feeding Time  ");
      lcd.setCursor(0,1);
      lcd.print("    Wait!...    ");
      if (feedAmt == 1) delayAndFeed(1000);
      else if (feedAmt == 2) delayAndFeed(2000);
      else if (feedAmt == 3) delayAndFeed(3000);
      lcd.clear();
      // Update feeding time for next 8 hours
      int nextFeedHour = (hourT * 10 + hourO + 8) % 24;
      r[0] = nextFeedHour / 10;
      r[1] = nextFeedHour % 10;
    }
    // Second feeding time
    else if (hourT == r[0] && hourO == r[1] && minT == r[2] && minO == r[3] && ((secT*10 + secO) < 3)) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Feeding Time  ");
      lcd.setCursor(0,1);
      lcd.print("    Wait!...    ");
      if (feedAmt == 1) delayAndFeed(1000);
      else if (feedAmt == 2) delayAndFeed(2000);
      else if (feedAmt == 3) delayAndFeed(3000);
      lcd.clear();
      // Update feeding time for next 16 hours
      int nextFeedHour = (hourT * 10 + hourO + 16) % 24;
      r[0] = nextFeedHour / 10;
      r[1] = nextFeedHour % 10;
    }
  } else if (feedIntv == 3) {
    // First feeding time
    if (hourT == r[0] && hourO == r[1] && minT == r[2] && minO == r[3] && ((secT*10 + secO) < 3)) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Feeding Time  ");
      lcd.setCursor(0,1);
      lcd.print("    Wait!...    ");
      if (feedAmt == 1) delayAndFeed(1000);
      else if (feedAmt == 2) delayAndFeed(2000);
      else if (feedAmt == 3) delayAndFeed(3000);
      lcd.clear();
      // Update feeding time for next 4 hours
      int nextFeedHour = (hourT * 10 + hourO + 4) % 24;
      r[0] = nextFeedHour / 10;
      r[1] = nextFeedHour % 10;
    }
    // Second feeding time
    else if (hourT == r[0] && hourO == r[1] && minT == r[2] && minO == r[3] && ((secT*10 + secO) < 3)) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Feeding Time  ");
      lcd.setCursor(0,1);
      lcd.print("    Wait!...    ");
      if (feedAmt == 1) delayAndFeed(1000);
      else if (feedAmt == 2) delayAndFeed(2000);
      else if (feedAmt == 3) delayAndFeed(3000);
      lcd.clear();
      // Update feeding time for next 4 hours
      int nextFeedHour = (hourT * 10 + hourO + 4) % 24;
      r[0] = nextFeedHour / 10;
      r[1] = nextFeedHour % 10;
    }
    // Third feeding time
    else if (hourT == r[0] && hourO == r[1] && minT == r[2] && minO == r[3] && ((secT*10 + secO) < 3)) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  Feeding Time  ");
      lcd.setCursor(0,1);
      lcd.print("    Wait!...    ");
      if (feedAmt == 1) delayAndFeed(1000);
      else if (feedAmt == 2) delayAndFeed(2000);
      else if (feedAmt == 3) delayAndFeed(3000);
      lcd.clear();
      // Update feeding time for next 16 hours
      int nextFeedHour = (hourT * 10 + hourO + 16) % 24;
      r[0] = nextFeedHour / 10;
      r[1] = nextFeedHour % 10;
    }
  }
}

void delayAndFeed(int delayTime) {
  tone(11, 1);
  delay(500);
  noTone(11);
  delay(500);
  servo.write(180);
  delay(delayTime);
  servo.write(50);
}

void setFeedTime() {
  fTime = true;
  fInterval = false;
  fAmount = false;
  int i = 0;
  int j = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Set Feed Time  ");
  lcd.setCursor(0,1);
  lcd.print("     HH:MM      ");
  lcd.setCursor(5,1);

  while (fTime) {
    key = kpd.getKey();
    if (key != NO_KEY) {
      if (key == 'A') continue;
      else if (key == 'B') {
        if (j > 0) {
          j--;
          i--;
          if (j == 2) {
            j--;
            lcd.setCursor(j + 5, 1);
            lcd.print(":");
          }
          lcd.setCursor(j + 5, 1);
          lcd.print("-");
          lcd.setCursor(j + 5, 1);
        }
      } else if (key == 'C') {
        lcd.setCursor(0, 1);
        lcd.print("     HH:MM      ");
        lcd.setCursor(5, 1);
        i = 0;
        j = 0;
      } else if (key == 'D') {
        // Do nothing
      } else if (key == '#') {
        key = 0;
        if (i == 0) {
          lcd.setCursor(0, 1);
          lcd.print("  Enter  Time!  ");
          delay(1000);
          lcd.clear();
          break;
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Set Feed Time  ");
        lcd.setCursor(0, 1);
        lcd.print("   Saving!...   ");
        delay(1000);
        lcd.clear();
        fTime = false;
        fInterval = true;
      } else if (key == '*') {
        key = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Set Feed Time  ");
        lcd.setCursor(0, 1);
        lcd.print("   Exiting...   ");
        delay(1000);
        lcd.clear();
        break;
      } else {
        if (i < 4) {
          if (j == 2) {
            j++;
            lcd.setCursor(j + 5, 1);
            lcd.print(":");
          }
          lcd.setCursor(j + 5, 1);
          lcd.print(key);
          r[i] = key - 48;
          i++;
          j++;
          delay(500);
        }
      }
    }
  }
  while (fInterval) {
    int i = 0;
    int j = 0;
    lcd.setCursor(0,0);
    lcd.print("  Set Interval  ");
    lcd.setCursor(0,1);
    lcd.print(" 1(L) 2(M) 3(H) ");
    lcd.setCursor(14,1);
    key = kpd.getKey();

    if (key != NO_KEY) {
      if (key == '1') {
        lcd.setCursor(0,1);
        lcd.print("  Once a day!   ");
        delay(1000);
        lcd.clear();
        feedIntv = 1;
        fInterval = false;
        fAmount = true;
      } else if (key == '2') {
        lcd.setCursor(0,1);
        lcd.print("  Twice a day!  ");
        delay(1000);
        lcd.clear();
        feedIntv = 2;
        fInterval = false;
        fAmount = true;
      } else if (key == '3') {
        lcd.setCursor(0,1);
        lcd.print(" Thrice a day!  ");
        delay(1000);
        lcd.clear();
        feedIntv = 3;
        fInterval = false;
        fAmount = true;
      } else if (key != '1' || key != '2' || key != '3') {
        key = 0;
        if (i == 0) {
          lcd.setCursor(0, 0);
          lcd.print("Invalid Interval");
          lcd.setCursor(0, 1);
          lcd.print("   Exiting...   ");
          delay(1000);
          lcd.clear();
          break;
        }
      } else {
          lcd.setCursor(j + 15, 1);
          lcd.print(key);
          r[i] = key - 48;
          i++;
          j++;
          delay(500);
        }
      }
    }
  while (fAmount) {
    int i = 0;
    int j = 0;
    lcd.setCursor(0,0);
    lcd.print("   Set Amount   ");
    lcd.setCursor(0,1);
    lcd.print(" 1(L) 2(M) 3(H) ");
    lcd.setCursor(14,1);
    key = kpd.getKey();

    if (key != NO_KEY) {
      if (key == '1') {
        lcd.setCursor(0,1);
        lcd.print("  Onti  lang!   ");
        delay(1000);
        lcd.clear();
        feedAmt = 1;
        break;
      } else if (key == '2') {
        lcd.setCursor(0,1);
        lcd.print("  Saks  lang!   ");
        delay(1000);
        lcd.clear();
        feedAmt = 2;
        break;
      } else if (key == '3') {
        lcd.setCursor(0,1);
        lcd.print("   MARAMI!!!    ");
        delay(1000);
        lcd.clear();
        feedAmt = 3;
        break;
      } else if (key != '1' || key != '2' || key != '3') {
        key = 0;
        if (i == 0) {
          lcd.setCursor(0, 0);
          lcd.print("Invalid Amount");
          lcd.setCursor(0, 1);
          lcd.print("   Exiting...   ");
          delay(1000);
          lcd.clear();
          break;
        }
      } else {
          lcd.setCursor(j + 15, 1);
          lcd.print(key);
          r[i] = key - 48;
          i++;
          j++;
          delay(500);
      }
    }
  }
}

void setFeedClock() {
  int i = 0;
  int j = 0;
  lcd.clear();
  lcd.print(" Set Feed Clock ");
  lcd.setCursor(0, 1);
  lcd.print("HH:MM   DD/MM/YY");
  lcd.setCursor(0, 1);

  while (1) {
    key = kpd.getKey();

    if (key != NO_KEY) {
      if (key == 'A') {
        // Do nothing
      } else if (key == 'B') {
        if (j > 0) {
          if (j == 3 || j == 6 || j == 7 || j == 8 || j == 11 || j == 14) {
            j -= 2;
          } else {
            j--;
          }
          if (j != 6) {
            lcd.setCursor(j, 1);
            lcd.print("-");
            lcd.setCursor(j, 1);
          }
        }
      } else if (key == 'C') {
        lcd.clear();
        lcd.print(" Set Feed Clock ");
        lcd.setCursor(0, 1);
        lcd.print("HH:MM   DD/MM/YY");
        lcd.setCursor(0, 1);
        j = 0;
        i = 0;
      } else if (key == 'D') {
        // Do nothing
      } else if (key == '#') {
        key = 0;
        if (i == 10) {
          int hour = (r[0] * 10) + r[1];
          int minute = (r[2] * 10) + r[3];
          int day = (r[4] * 10) + r[5];
          int month = (r[6] * 10) + r[7];
          int year = (r[8] * 10) + r[9] + 2000;
          rtc.setTime(hour, minute, 0);
          rtc.setDate(day, month, year);
          lcd.clear();
          lcd.print(" Set Feed Clock ");
          lcd.setCursor(0, 1);
          lcd.print("   Saving!...   ");
          delay(1000);
          lcd.clear();
          break;
        } else {
          lcd.setCursor(0, 1);
          lcd.print(" Invalid Input! ");
          delay(1000);
          lcd.setCursor(0, 1);
          lcd.print("HH:MM   DD/MM/YY");
          j = 0;
          i = 0;
        }
      } else if (key == '*') {
        key = 0;
        lcd.clear();
        lcd.print(" Set Feed Clock ");
        lcd.setCursor(0, 1);
        lcd.print("   Exiting...   ");
        delay(1000);
        lcd.clear();
        break;
      } else {
        if ((j == 2 && key > '3') || (j == 5 && r[3] == 5 && key > '5') || (j == 8 && r[5] == 3 && key > '1')) {
          continue;
        }
        if (j != 6) {
          lcd.setCursor(j, 1);
          lcd.print(key);
        }
        if (j == 1) {
          j++;
          lcd.setCursor(j, 1);
          lcd.print(":");
        } else if (j == 4) {
          j+=3;
          lcd.setCursor(j, 1);
          lcd.print(" ");
        } else if ((j == 7) || (j == 9) || (j == 12)) {
          j++;
          lcd.setCursor(j, 1);
          lcd.print("/");
        }
        r[i] = key - 48;
        i++;
        j++;
      }
    }
  }
}