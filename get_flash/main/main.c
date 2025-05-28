#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRtos.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_flash.h"//5.25之后替换成这个了，要不就是esp_spi_flash.h   spi_flash_get_chip_size()
const char *sw = "软件";
const char *hw = "硬件";

void app_main(void)
{
    //日志打印
    ESP_LOGE(sw, "IDF 版本号 %s", esp_get_idf_version()); // 日志打印cpu型号


    //硬件信息获取
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
//     typedef struct {
//     esp_chip_model_t model;  //!< chip model, one of esp_chip_model_t
//     uint32_t features;       //!< bit mask of CHIP_FEATURE_x feature flags
//     uint16_t revision;       //!< chip revision number (in format MXX; where M - wafer major version, XX - wafer minor version)
//     uint8_t cores;           //!< number of CPU cores
// } esp_chip_info_t;
    ESP_LOGE(sw, "esp类型枚举值 %d", chip_info.model); //可以通过switch语句进行对应打印 
    ESP_LOGE(sw, "特性  %d", (unsigned int)chip_info.features); //转化成二进制就能知道对应的一些硬件的有无对对应的硬件&可以打印出是否有
    ESP_LOGE(sw, "IDF 版本号 %d", chip_info.revision);
    ESP_LOGE(sw, "IDF 核心数 %d", chip_info.cores);   
    //获取flash 的大小
    esp_flash_t *default_flash = esp_flash_default_chip;
    uint32_t chip_size;
    esp_flash_get_physical_size(default_flash, &chip_size);
    ESP_LOGE(hw, "flash:%.2fMB", (float)chip_size / 1024 / 1024);//size得到的是字节数，转化为MB

}
