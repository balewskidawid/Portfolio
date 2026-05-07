
#include "LedControl.h"

LedControl::LedControl(int numPixels, Adafruit_NeoPixel& strip) : strip(strip), numDevices(numPixels) {
    strip.begin();
    strip.show();
    rotation = 0;
    color = strip.Color(255, 255, 255);  // Default to white color
}

void LedControl::setRotation(int rot) {
    rotation = rot;
}

void LedControl::clearDisplay(int addr) {
    for (int i = addr * 64; i < (addr + 1) * 64; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}

void LedControl::setIntensity(int intensity) {
    color = strip.Color(intensity, intensity, intensity);
}

coord LedControl::flipHorizontally(coord xy) {
    xy.x = 7 - xy.x;
    return xy;
}

coord LedControl::flipVertically(coord xy) {
    xy.y = 7 - xy.y;
    return xy;
}

coord LedControl::rotate90(coord xy) {
    int tmp = xy.y;
    xy.y = xy.x;
    xy.x = tmp;
    return flipHorizontally(xy);
}

coord LedControl::rotate180(coord xy) {
    return flipHorizontally(flipVertically(xy));
}

coord LedControl::rotate270(coord xy) {
    return rotate180(rotate90(xy));
}
coord LedControl::transform(coord xy) {
    if (rotation == 90) {
        xy = rotate90(xy);
    } else if (rotation == 180) {
        xy = rotate180(xy);
    } else if (rotation == 270) {
        xy = rotate270(xy);
    }
    return xy;
}

void LedControl::setXY(int addr, int x, int y, bool state) {
    coord xy;
    xy.x = x;
    xy.y = y;
    xy = transform(xy);
    setLed(addr, xy.x, xy.y, state);
}

void LedControl::setLed(int addr, int x, int y, bool state) {
    int pixelIndex = addr * 64 + y * 8 + x;
    if (state) {
        strip.setPixelColor(pixelIndex, color);
    } else {
        strip.setPixelColor(pixelIndex, strip.Color(0, 0, 0));
    }
    strip.show();
}

void LedControl::invertXY(int addr, int x, int y) {
    coord xy;
    xy.x = x;
    xy.y = y;
    xy = transform(xy);
    int pixelIndex = addr * 64 + xy.y * 8 + xy.x;
    uint32_t currentColor = strip.getPixelColor(pixelIndex);
    if (currentColor == 0) {
        strip.setPixelColor(pixelIndex, color);
    } else {
        strip.setPixelColor(pixelIndex, strip.Color(0, 0, 0));
    }
    strip.show();
}

bool LedControl::getXY(int addr, int x, int y) {
    coord xy;
    xy.x = x;
    xy.y = y;
    xy = transform(xy);
    int pixelIndex = addr * 64 + xy.y * 8 + xy.x;
    uint32_t currentColor = strip.getPixelColor(pixelIndex);
    return currentColor != 0;
}
