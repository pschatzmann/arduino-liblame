
/**
 * @file output_mp3.ino
 * @author Phil Schatzmann
 * @brief We just calulate the number of encoded samples per second
 * @version 0.1
 * @date 2021-07-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "MP3EncoderLAME.h"
#include <stdlib.h>  // for rand

using namespace liblame;

void dataCallback(uint8_t *mp3_data, size_t len) {
}

MP3EncoderLAME mp3(dataCallback);
AudioInfo info;
const int size = 10000;
const int time_sec = 10;
int16_t buffer[size];

void speed_test(){
    size_t total = 0;
    // we encode for the indicated number of seconds
    uint64_t end = millis() + (time_sec*1000);
    while(millis()<end){
        mp3.write(buffer, size*sizeof(int16_t));
        total+=size;
    }

    Serial.print("Samples decoded per second: ");
    Serial.println(total / time_sec);
}

void setup() {
    Serial.begin(115200);

    info.channels = 1;
    info.sample_rate = 441000;
    mp3.begin(info);

    // fill buffer with random number
    for (int j=0;j<512;j++){
        buffer[j] = (rand() % 100) - 50;         
    }

    Serial.println("testing...");
}

void loop() {
    speed_test();
}
