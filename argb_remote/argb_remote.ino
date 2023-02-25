#include <IRremote.hpp>
#include <microLED.h>

#define LED_PIN 2    // пин ленты
#define NUMLEDS 102  // количество светодиодов
#define IR_PIN 3     // пин ИК-приёмника
#define debug false  // включение отладки

microLED<NUMLEDS, LED_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB, CLI_AVER, SAVE_MILLIS> led;

//effects:
void R();
void R_1();
void R_2();
void R_3();
void R_4();

void G();
void G_1();
void G_2();
void G_3();
void G_4();

void B();
void B_1();
void B_2();
void B_3();
void B_4();

void W();
void W_1();
void W_2();
void W_3();
void W_4();

uint8_t DIY1_R = 45, DIY1_G = 30, DIY1_B = 30,
        DIY2_R = 30, DIY2_G = 45, DIY2_B = 30,
        DIY3_R = 30, DIY3_G = 30, DIY3_B = 45,
        DIY4_R = 45, DIY4_G = 45, DIY4_B = 45,
        DIY5_R = 45, DIY5_G = 45, DIY5_B = 30,
        DIY6_R = 30, DIY6_G = 45, DIY6_B = 45;

void DIY1();
void DIY2();
void DIY3();
void DIY4();
void DIY5();
void DIY6();

int speed = 1000;
bool pause = false;

void JUMP3();
void JUMP7();
void FADE3();
void FADE7();
void FLASH();
void AUTO();

int temp_com = 0;
unsigned long time_com = 0;
bool miss_click = false;

uint8_t brightness = 100;
bool off = true;
int last_mode = 0;

void switch_last_mode() {
  switch (last_mode) {
    case 0:
      R();
      break;
    case 1:
      R_1();
      break;
    case 2:
      R_2();
      break;
    case 3:
      R_3();
      break;
    case 4:
      R_4();
      break;
    case 5:
      G();
      break;
    case 6:
      G_1();
      break;
    case 7:
      G_2();
      break;
    case 8:
      G_3();
      break;
    case 9:
      G_4();
      break;
    case 10:
      B();
      break;
    case 11:
      B_1();
      break;
    case 12:
      B_2();
      break;
    case 13:
      B_3();
      break;
    case 14:
      B_4();
      break;
    case 15:
      W();
      break;
    case 16:
      W_1();
      break;
    case 17:
      W_2();
      break;
    case 18:
      W_3();
      break;
    case 19:
      W_4();
      break;
    case 20:
      DIY1();
      break;
    case 21:
      DIY2();
      break;
    case 22:
      DIY3();
      break;
    case 23:
      DIY4();
      break;
    case 24:
      DIY5();
      break;
    case 25:
      DIY6();
      break;
    case 26:
      JUMP3();
      break;
    case 27:
      JUMP7();
      break;
    case 28:
      FADE3();
      break;
    case 29:
      FADE7();
      break;
    case 30:
      FLASH();
      break;
    case 31:
      AUTO();
      break;
  }
}

void setup() {
  for (int i = 0; i <= NUMLEDS; i++) {
    led.set(i, mWheel(map(i, 0, NUMLEDS, 0, 1530)));
    led.setBrightness(map(i, 0, NUMLEDS, 0, brightness));
    led.show();
    delay(10);
  }
  for (int i = 0; i <= NUMLEDS; i++) {
    led.set(i, mBlack);
    led.setBrightness(map(i, 0, NUMLEDS, brightness, 0));
    led.show();
    delay(10);
  }
  led.setBrightness(brightness);
  led.show();
  if (debug) Serial.begin(9600);
  IrReceiver.begin(IR_PIN);
}
void yield() {
  loop();
}
void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.command == temp_com) {
      if (millis() - time_com < 110) {
        miss_click = true;
      }
    }
    time_com = millis();
    temp_com = IrReceiver.decodedIRData.command;
    switch (IrReceiver.decodedIRData.command) {
      case 0x5C:  // BRIHTNESS +
        if (brightness < 170) brightness += 5;
        led.setBrightness(brightness);
        led.show();
        if (debug) Serial.print("BRIHTNESS + ");
        if (debug) Serial.println(brightness);
        break;
      case 0x5D:  // BRIHTNESS -
        if (brightness > 10) brightness -= 5;
        led.setBrightness(brightness);
        led.show();
        if (debug) Serial.print("BRIHTNESS - ");
        if (debug) Serial.println(brightness);
        break;
      case 0x41:  // PAUSE/PLAY
        if (!miss_click) {
          if (last_mode == 26 || last_mode == 27 || last_mode == 28 || last_mode == 29 || last_mode == 30 || last_mode == 31) {
            if (debug) Serial.println("PAUSE/PLAY");
            pause = !pause;
          }
        }
        break;
      case 0x40:  // ON/OFF
        if (!miss_click) {
          if (debug) Serial.println("ON/OFF");
          if (off) {
            off = false;
            switch_last_mode();
          } else {
            led.fill(mBlack);
            led.show();
            off = true;
          }
        }
        break;
      case 0x58:  // R
        if (!miss_click) {
          if (debug) Serial.println("R");
          R();
        }
        break;
      case 0x54:  // R1
        if (!miss_click) {
          if (debug) Serial.println("R1");
          R_1();
        }
        break;
      case 0x50:  // R2
        if (!miss_click) {
          if (debug) Serial.println("R2");
          R_2();
        }
        break;
      case 0x1C:  // R3
        if (!miss_click) {
          if (debug) Serial.println("R3");
          R_3();
          break;
          case 0x18:  // R4
            if (!miss_click) {
              if (debug) Serial.println("R4");
              R_4();
            }
        }
        break;
      case 0x59:  // G
        if (!miss_click) {
          if (debug) Serial.println("G");
          G();
        }
        break;
      case 0x55:  // G1
        if (!miss_click) {
          if (debug) Serial.println("G1");
          G_1();
        }
        break;
      case 0x51:  // G2
        if (!miss_click) {
          if (debug) Serial.println("G2");
          G_2();
        }
        break;
      case 0x1D:  // G3
        if (!miss_click) {
          if (debug) Serial.println("G3");
          G_3();
        }
        break;
      case 0x19:  // G4
        if (!miss_click) {
          if (debug) Serial.println("G4");
          G_4();
        }
        break;
      case 0x45:  // B
        if (!miss_click) {
          if (debug) Serial.println("B");
          B();
        }
        break;
      case 0x49:  // B1
        if (!miss_click) {
          if (debug) Serial.println("B1");
          B_1();
        }
        break;
      case 0x4D:  // B2
        if (!miss_click) {
          if (debug) Serial.println("B2");
          B_2();
        }
        break;
      case 0x1E:  // B3
        if (!miss_click) {
          if (debug) Serial.println("B3");
          B_3();
        }
        break;
      case 0x1A:  // B4
        if (!miss_click) {
          if (debug) Serial.println("B4");
          B_4();
        }
        break;
      case 0x44:  // W
        if (!miss_click) {
          if (debug) Serial.println("W");
          W();
        }
        break;
      case 0x48:  // W1
        if (!miss_click) {
          if (debug) Serial.println("W1");
          W_1();
        }
        break;
      case 0x4C:  // W2
        if (!miss_click) {
          if (debug) Serial.println("W2");
          W_2();
        }
        break;
      case 0x1F:  // W3
        if (!miss_click) {
          if (debug) Serial.println("W3");
          W_3();
        }
        break;
      case 0x1B:  // W4
        if (!miss_click) {
          if (debug) Serial.println("W4");
          W_4();
        }
        break;
      case 0x14:  // R+
        if (debug) Serial.println("R+");
        switch (last_mode) {
          case 20:  // DIY1
            if (DIY1_R < 255) DIY1_R += 15;
            DIY1();
            break;
          case 21:  // DIY2
            if (DIY2_R < 255) DIY2_R += 15;
            DIY2();
            break;
          case 22:  // DIY3
            if (DIY3_R < 255) DIY3_R += 15;
            DIY3();
            break;
          case 23:  // DIY4
            if (DIY4_R < 255) DIY4_R += 15;
            DIY4();
            break;
          case 24:  // DIY5
            if (DIY5_R < 255) DIY5_R += 15;
            DIY5();
            break;
          case 25:  // DIY6
            if (DIY6_R < 255) DIY6_R += 15;
            DIY6();
            break;
        }
        break;
      case 0x10:  // R-
        if (debug) Serial.println("R-");
        switch (last_mode) {
          case 20:  // DIY1
            if (DIY1_R > 0) DIY1_R -= 15;
            DIY1();
            break;
          case 21:  // DIY2
            if (DIY2_R > 0) DIY2_R -= 15;
            DIY2();
            break;
          case 22:  // DIY3
            if (DIY3_R > 0) DIY3_R -= 15;
            DIY3();
            break;
          case 23:  // DIY4
            if (DIY4_R > 0) DIY4_R -= 15;
            DIY4();
            break;
          case 24:  // DIY5
            if (DIY5_R > 0) DIY5_R -= 15;
            DIY5();
            break;
          case 25:  // DIY6
            if (DIY6_R > 0) DIY6_R -= 15;
            DIY6();
            break;
        }
        break;
      case 0x15:  // G+
        if (debug) Serial.println("G+");
        switch (last_mode) {
          case 20:  // DIY1
            if (DIY1_G < 255) DIY1_G += 15;
            DIY1();
            break;
          case 21:  // DIY2
            if (DIY2_G < 255) DIY2_G += 15;
            DIY2();
            break;
          case 22:  // DIY3
            if (DIY3_G < 255) DIY3_G += 15;
            DIY3();
            break;
          case 23:  // DIY4
            if (DIY4_G < 255) DIY4_G += 15;
            DIY4();
            break;
          case 24:  // DIY5
            if (DIY5_G < 255) DIY5_G += 15;
            DIY5();
            break;
          case 25:  // DIY6
            if (DIY6_G < 255) DIY6_G += 15;
            DIY6();
            break;
        }
        break;
      case 0x11:  // G-
        if (debug) Serial.println("G-");
        switch (last_mode) {
          case 20:  // DIY1
            if (DIY1_G > 0) DIY1_G -= 15;
            DIY1();
            break;
          case 21:  // DIY2
            if (DIY2_G > 0) DIY2_G -= 15;
            DIY2();
            break;
          case 22:  // DIY3
            if (DIY3_G > 0) DIY3_G -= 15;
            DIY3();
            break;
          case 23:  // DIY4
            if (DIY4_G > 0) DIY4_G -= 15;
            DIY4();
            break;
          case 24:  // DIY5
            if (DIY5_G > 0) DIY5_G -= 15;
            DIY5();
            break;
          case 25:  // DIY6
            if (DIY6_G > 0) DIY6_G -= 15;
            DIY6();
            break;
        }
        break;
      case 0x16:  // B+
        if (debug) Serial.println("B+");
        switch (last_mode) {
          case 20:  // DIY1
            if (DIY1_B < 255) DIY1_B += 15;
            DIY1();
            break;
          case 21:  // DIY2
            if (DIY2_B < 255) DIY2_B += 15;
            DIY2();
            break;
          case 22:  // DIY3
            if (DIY3_B < 255) DIY3_B += 15;
            DIY3();
            break;
          case 23:  // DIY4
            if (DIY4_B < 255) DIY4_B += 15;
            DIY4();
            break;
          case 24:  // DIY5
            if (DIY5_B < 255) DIY5_B += 15;
            DIY5();
            break;
          case 25:  // DIY6
            if (DIY6_B < 255) DIY6_B += 15;
            DIY6();
            break;
        }
        break;
      case 0x12:  // B-
        if (debug) Serial.println("B-");
        switch (last_mode) {
          case 20:  // DIY1
            if (DIY1_B > 0) DIY1_B -= 15;
            DIY1();
            break;
          case 21:  // DIY2
            if (DIY2_B > 0) DIY2_B -= 15;
            DIY2();
            break;
          case 22:  // DIY3
            if (DIY3_B > 0) DIY3_B -= 15;
            DIY3();
            break;
          case 23:  // DIY4
            if (DIY4_B > 0) DIY4_B -= 15;
            DIY4();
            break;
          case 24:  // DIY5
            if (DIY5_B > 0) DIY5_B -= 15;
            DIY5();
            break;
          case 25:  // DIY6
            if (DIY6_B > 0) DIY6_B -= 15;
            DIY6();
            break;
        }
        break;
      case 0x17:  // QUICK
        if (speed > 25) speed -= 25;
        if (debug) Serial.println("QUICK");
        if (debug) Serial.println(speed);
        break;
      case 0x13:  // SLOW
        if (speed < 5000) speed += 25;
        if (debug) Serial.println("SLOW");
        if (debug) Serial.println(speed);
        break;
      case 0xC:  // DIY1
        if (!miss_click) {
          if (debug) Serial.println("DIY1");
          DIY1();
        }
        break;
      case 0xD:  // DIY2
        if (!miss_click) {
          if (debug) Serial.println("DIY2");
          DIY2();
        }
        break;
      case 0xE:  // DIY3
        if (!miss_click) {
          if (debug) Serial.println("DIY3");
          DIY3();
        }
        break;
      case 0x8:  // DIY4
        if (!miss_click) {
          if (debug) Serial.println("DIY4");
          DIY4();
        }
        break;
      case 0x9:  // DIY5
        if (!miss_click) {
          if (debug) Serial.println("DIY5");
          DIY5();
        }
        break;
      case 0xA:  // DIY6
        if (!miss_click) {
          if (debug) Serial.println("DIY6");
          DIY6();
        }
        break;
      case 0xF:  // AUTO
        if (!miss_click) {
          if (debug) Serial.println("AUTO");
          AUTO();
        }
        break;
      case 0xB:  // FLASH
        if (!miss_click) {
          if (debug) Serial.println("FLASH");
          FLASH();
        }
        break;
      case 0x4:  // JUMP3
        if (!miss_click) {
          if (debug) Serial.println("JUMP3");
          JUMP3();
        }
        break;
      case 0x5:  // JUMP7
        if (!miss_click) {
          if (debug) Serial.println("JUMP7");
          JUMP7();
        }
        break;
      case 0x6:  // FADE3
        if (!miss_click) {
          if (debug) Serial.println("FADE3");
          FADE3();
        }
        break;
      case 0x7:  // FADE7
        if (!miss_click) {
          if (debug) Serial.println("FADE7");
          FADE7();
        }
        break;
      default:
        if (debug) IrReceiver.printIRResultShort(&Serial);
        break;
    }
    IrReceiver.resume();
    miss_click = false;
  }
}

// colors
void R() {
  if (!off) {
    led.fill(mRed);
    led.show();
    last_mode = 0;
  }
}
void R_1() {
  if (!off) {
    led.fill(mHEX(0xD35339));
    led.show();
    last_mode = 1;
  }
}
void R_2() {
  if (!off) {
    led.fill(mHEX(0xD5713F));
    led.show();
    last_mode = 2;
  }
}
void R_3() {
  if (!off) {
    led.fill(mHEX(0xD68A59));
    led.show();
    last_mode = 3;
  }
}
void R_4() {
  if (!off) {
    led.fill(mHEX(0xFFFF00));
    led.show();
    last_mode = 4;
  }
}

void G() {
  if (!off) {
    led.fill(mGreen);
    led.show();
    last_mode = 5;
  }
}
void G_1() {
  if (!off) {
    led.fill(mHEX(0x7BA05B));
    led.show();
    last_mode = 6;
  }
}
void G_2() {
  if (!off) {
    led.fill(mHEX(0x669E85));
    led.show();
    last_mode = 7;
  }
}
void G_3() {
  if (!off) {
    led.fill(mHEX(0x158078));
    led.show();
    last_mode = 8;
  }
}
void G_4() {
  if (!off) {
    led.fill(mHEX(0x1C6B72));
    led.show();
    last_mode = 9;
  }
}

void B() {
  if (!off) {
    led.fill(mBlue);
    led.show();
    last_mode = 10;
  }
}
void B_1() {
  if (!off) {
    led.fill(mHEX(0x2B6CC4));
    led.show();
    last_mode = 11;
  }
}
void B_2() {
  if (!off) {
    led.fill(mHEX(0x9A366B));
    led.show();
    last_mode = 12;
  }
}
void B_3() {
  if (!off) {
    led.fill(mHEX(0xC54B8C));
    led.show();
    last_mode = 13;
  }
}
void B_4() {
  if (!off) {
    led.fill(mHEX(0xD36E70));
    led.show();
    last_mode = 14;
  }
}

void W() {
  if (!off) {
    led.fill(mWhite);
    led.show();
    last_mode = 15;
  }
}
void W_1() {
  if (!off) {
    led.fill(mHEX(0xEBC2AF));
    led.show();
    last_mode = 16;
  }
}
void W_2() {
  if (!off) {
    led.fill(mHEX(0xE6BBC1));
    led.show();
    last_mode = 17;
  }
}
void W_3() {
  if (!off) {
    led.fill(mHEX(0xC7D0CC));
    led.show();
    last_mode = 18;
  }
}
void W_4() {
  if (!off) {
    led.fill(mHEX(0xC1CACA));
    led.show();
    last_mode = 19;
  }
}

void DIY1() {
  if (!off) {
    led.fill(mRGB(DIY1_R, DIY1_G, DIY1_B));
    led.show();
    last_mode = 20;
  }
}
void DIY2() {
  if (!off) {
    led.fill(mRGB(DIY2_R, DIY2_G, DIY2_B));
    led.show();
    last_mode = 21;
  }
}
void DIY3() {
  if (!off) {
    led.fill(mRGB(DIY3_R, DIY3_G, DIY3_B));
    led.show();
    last_mode = 22;
  }
}
void DIY4() {
  if (!off) {
    pause = false;
    last_mode = 29;
    uint8_t hsv = 255;
    while (last_mode == 29) {
      if (!pause) {
        if (!off) {
          led.show();
        }
        hsv--;
        delay(speed / 25);
      }
      if (pause) {
        loop();
      }
    }
  }
  // if (!off) {
  //   led.fill(mRGB(DIY4_R, DIY4_G, DIY4_B));
  //   led.show();
  //   last_mode = 23;
  }
}
void DIY5() {
  if (!off) {
    led.fill(mRGB(DIY5_R, DIY5_G, DIY5_B));
    led.show();
    last_mode = 24;
  }
}
void DIY6() {
  if (!off) {
    led.fill(mRGB(DIY6_R, DIY6_G, DIY6_B));
    led.show();
    last_mode = 25;
  }
}

//dynamic
void JUMP3() {
  if (!off) {
    pause = false;
    last_mode = 26;
    while (last_mode == 26) {
      if (last_mode == 26 && !pause) {
        R();
        last_mode = 26;
        delay(speed);
      }
      if (last_mode == 26 && !pause) {
        G();
        last_mode = 26;
        delay(speed);
      }
      if (last_mode == 26 && !pause) {
        B();
        last_mode = 26;
        delay(speed);
      }
      if (pause) {
        loop();
      }
    }
  }
}
void JUMP7() {
  if (!off) {
    pause = false;
    last_mode = 27;
    while (last_mode == 27 && !pause) {
      if (last_mode == 27 && !pause) {
        R();
        last_mode = 27;
        delay(speed);
      }
      if (last_mode == 27 && !pause) {
        G();
        last_mode = 27;
        delay(speed);
      }
      if (last_mode == 27 && !pause) {
        B();
        last_mode = 27;
        delay(speed);
      }
      if (last_mode == 27 && !pause) {
        R_4();
        last_mode = 27;
        delay(speed);
      }
      if (last_mode == 27 && !pause) {
        B_2();
        last_mode = 27;
        delay(speed);
      }
      if (last_mode == 27 && !pause) {
        G_4();
        last_mode = 27;
        delay(speed);
      }
      if (last_mode == 27 && !pause) {
        W();
        last_mode = 27;
        delay(speed);
      }
      if (pause) {
        loop();
      }
    }
  }
}

void FADE3() {
  if (!off) {
    pause = false;
    last_mode = 28;
    uint8_t hsv = 0;
    while (last_mode == 28) {
      if (!pause) {
        if (!off) {
          led.fill(mWheel8(hsv));
          led.show();
        }
        hsv++;
        delay(speed / 25);
      }
      if (pause) {
        loop();
      }
    }
  }
}
void FADE7() {
  if (!off) {
    pause = false;
    last_mode = 29;
    uint8_t hsv = 255;
    while (last_mode == 29) {
      if (!pause) {
        if (!off) {
          led.fill(mWheel8(hsv));
          led.show();
        }
        hsv--;
        delay(speed / 25);
      }
      if (pause) {
        loop();
      }
    }
  }
}

void FLASH() {
  if (!off) {
    last_mode = 30;
    while (last_mode == 30) {
      if (last_mode == 30) {
        W();
        last_mode = 30;
        delay(speed);
      }
      if (last_mode == 30) {
        led.fill(mBlack);
        led.show();
        last_mode = 30;
        delay(speed);
      }
    }
  }
}
void AUTO() {
  if (!off) {
    pause = false;
    last_mode = 31;
    while (last_mode == 31) {
      if (last_mode == 31 && !pause) {
        R();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        G();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        B();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        R();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        G();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        B();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        R_4();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        B_2();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        G_4();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        W();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        W();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        led.fill(mBlack);
        led.show();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        W();
        last_mode = 31;
        delay(speed);
      }
      if (last_mode == 31 && !pause) {
        led.fill(mBlack);
        led.show();
        last_mode = 31;
        delay(speed);
      }
      for (uint8_t hsv = 0; hsv < 255; hsv++) {
        if (last_mode == 31 && !pause) {
          if (!off) {
            led.fill(mWheel8(hsv));
            led.show();
            last_mode = 31;
          }
          delay(speed / 25);
        }
      }
      for (uint8_t hsv = 255; hsv > 0; hsv--) {
        if (last_mode == 31 && !pause) {
          if (!off) {
            led.fill(mWheel8(hsv));
            led.show();
            last_mode = 31;
          }
          delay(speed / 25);
        }
      }
      if (pause) {
        loop();
      }
    }
  }
}