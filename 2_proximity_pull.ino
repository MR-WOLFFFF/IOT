/*
    An example for Grove - Light&Gesture&Color&Proximity Sensor

    Copyright (c) 2018 seeed technology co., ltd.
    Author      : Jack Shao
    Create Time: June 2018
    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include <Wire.h>

#include "Seeed_TMG3993.h"

TMG3993 tmg3993;

void setup() {
    Serial.begin(9600);
    Serial.println("TMG3993 Proximity Example");

    Wire.begin();

    if (tmg3993.initialize() == false) {
        Serial.println("Device not found. Check wiring.");
        while (1);
    }
    tmg3993.setupRecommendedConfigForProximity();
    tmg3993.enableEngines(ENABLE_PON | ENABLE_PEN | ENABLE_PIEN);
}

void loop() {
    if (tmg3993.getSTATUS() & STATUS_PVALID) {
        uint8_t proximity_raw = tmg3993.getProximityRaw();  //read the Proximity data will clear the status bit
        Serial.print("Proximity Raw: ");
        Serial.println(proximity_raw);
    }
    delay(1);
}
