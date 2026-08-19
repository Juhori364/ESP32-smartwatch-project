#include <stdio.h>

#include <stdio.h> 
#include "sdkconfig.h" 
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h" 
#include "esp_log.h" 
#include <driver/gpio.h>

#define BUTTON_PIN 4 

int flag = 0;

void app_main(void)
{
    printf("Debug printti\n");

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);

    int previous_level = 1;

    while (1) {
        int level = gpio_get_level(BUTTON_PIN);

        // Button has just been pressed
        if (previous_level == 1 && level == 0) {
            flag = !flag;
            printf("Flag set to %d\n", flag);
        }

        previous_level = level;

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
