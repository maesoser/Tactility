#include <tactility/error.h>
#include <tactility/log.h>
#include <tactility/module.h>

#include <driver/gpio.h>

constexpr auto* TAG = "tdeck-pro";

// Module enable pins used on T-Deck Pro V1.1. The same pins may be held across deep sleep,
// so release any holds early in boot to let the gpio-hog nodes re-assert their levels.
constexpr gpio_num_t POWER_6609_EN = GPIO_NUM_41;
constexpr gpio_num_t POWER_LORA_EN = GPIO_NUM_46;
constexpr gpio_num_t POWER_GPS_EN = GPIO_NUM_39;
constexpr gpio_num_t POWER_A7682E_PWRKEY = GPIO_NUM_40;

extern "C" {

static error_t start() {
    LOG_I(TAG, "Release deep-sleep GPIO holds");

    gpio_hold_dis(POWER_6609_EN);
    gpio_hold_dis(POWER_LORA_EN);
    gpio_hold_dis(POWER_GPS_EN);
    gpio_hold_dis(POWER_A7682E_PWRKEY);
    gpio_deep_sleep_hold_dis();

    return ERROR_NONE;
}

static error_t stop() {
    return ERROR_NONE;
}

Module lilygo_tdeck_pro_module = {
    .name = "lilygo-tdeck-pro",
    .start = start,
    .stop = stop,
    .drivers = nullptr,
    .symbols = nullptr,
    .internal = nullptr
};

}
