#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRtos.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"


void app_main(void)
{
    //配置gpio配置结构体
#if 0
    typedef struct {
    uint64_t pin_bit_mask;          /*!< GPIO pin: set with bit mask, each bit maps to a GPIO掩码形式 */
    gpio_mode_t mode;               /*!< GPIO mode: set input/output mode                     */
    gpio_pullup_t pull_up_en;       /*!< GPIO pull-up                                         */
    gpio_pulldown_t pull_down_en;   /*!< GPIO pull-down                                       */
    gpio_int_type_t intr_type;      /*!< GPIO interrupt type                                  */
#if SOC_GPIO_SUPPORT_PIN_HYS_FILTER
    gpio_hys_ctrl_mode_t hys_ctrl_mode;       /*!< GPIO hysteresis: hysteresis filter on slope input    */
#endif
} gpio_config_t;
#endif 
    gpio_config_t io_config;
    io_config.intr_type = GPIO_INTR_DISABLE;
    io_config.mode = GPIO_MODE_OUTPUT;//设置输出
    io_config.pull_down_en = GPIO_PULLDOWN_DISABLE;//无下拉
    io_config.pull_up_en = GPIO_PULLUP_DISABLE;//无上拉
    io_config.pin_bit_mask = 1ULL<<GPIO_NUM_4;//配置为1号管脚Unsigned Long Long
printf("ssss\n");
#if 0


#endif
    //传入配置管脚函数
    gpio_config(&io_config);

printf("start\n");
    //设置管脚电平实现500毫秒的亮灭
    int i= 0;
    while(1){
        gpio_set_level(GPIO_NUM_4 ,1); //高电平esp_err_t gpio_set_level(gpio_num_t gpio_num管脚数, uint32_t level电平值)
        printf("LED_ON\n");
        vTaskDelay(500/portTICK_PERIOD_MS);//毫秒延时传TickType_t   u32 
        //#define portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
        gpio_set_level(GPIO_NUM_4 ,0);//低电平
        printf("LED_OFF\n");
        vTaskDelay(500/portTICK_PERIOD_MS);//再延时
        
        printf("当前闪烁次数为%d\n" , i);
        i++;
        if(i>=10)break;

    }
}
//小结：注意使用的gpio管脚是否与日志打印冲突，若管脚冲突则程序将会出现为止错误卡死。
//如：使用gpio1时，gpio_config()函数调用卡死

