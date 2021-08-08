#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "lame.h"
#include "lame_test.h"

esp_err_t event_handler(void *ctx, system_event_t *event) {
    return ESP_OK;
}

void setup() {
    nvs_flash_init();

    printf("ESP32 SDK version:%s, RAM left %d\n", esp_get_idf_version(), esp_get_free_heap_size());

    printf("get_lame_version(): %s\n", get_lame_version());

    lameTest();

}

void loop(){

}

