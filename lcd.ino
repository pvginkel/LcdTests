#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 128

#define FONT_HEIGHT 10
#define FONT_WIDTH 6

// https://stackoverflow.com/questions/18216019
#define _FONT1(w, h) u8g2_font_##w##x##h##_mn
#define _FONT(w, h) _FONT1(w, h)

#define FONT _FONT(FONT_WIDTH, FONT_HEIGHT)

typedef unsigned long time_t;

char* buffer = new char[20];
int i = 0;
int offset = 0;
time_t lastMillis = 0;

#define FRAME_MS (1000 / 24)

void setup()
{
    u8g2.begin();
}

void loop()
{
    time_t currentMillis = millis();
    if (currentMillis - lastMillis < FRAME_MS) {
        return;
    }
    lastMillis += FRAME_MS;

    u8g2.clearBuffer();

    u8g2.setFont(FONT);

    for (int x = 0, column = 0; x < SCREEN_WIDTH; column++) {
        int textWidth = 0;

        for (int y = -offset, ii = i + column * 3; y < SCREEN_HEIGHT; ii++) {
            u8g2.setCursor(x, y + FONT_HEIGHT);
            auto text = String(ii);
            u8g2.print(text);
            textWidth = text.length();

            y += FONT_HEIGHT + 1;
        }

        x += textWidth * (FONT_WIDTH + 2);
        break;
    }

    if (offset++ >= FONT_HEIGHT) {
        offset = 0;
        i++;
    }

    u8g2.sendBuffer();
}
