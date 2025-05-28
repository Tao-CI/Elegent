/**********外部中断处理函数处理中断****************/
//按键点灯：io口，电平检测（上升or下降），中断处理优先级，中断处理函数
//gpio_config,gpio_set_inte_type,gpio_install_isr_service,gpio_isr_handler_add
#include <stdio.h>
#include "freertos/FreeRtos.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
//定义按键和灯的管脚
#define LED_PIN GPIO_NUM_4
#define BUTTON_PIN GPIO_NUM_5
#define VCC GPIO_NUM_23
int cont = 0;//记录中断次数
//中断回调函数
void static button_isr_handler(void*arg)
{
    gpio_set_level(LED_PIN,!(gpio_get_level(LED_PIN)));//取灯电平的反值，即电平转化

           vTaskDelay(500/portTICK_PERIOD_MS);
           
    cont++;
}
//LED初始化函数
void led_init()
{
    gpio_config_t ledio_config;
    ledio_config.mode = GPIO_MODE_INPUT_OUTPUT;//输入输出模式
    //无上下拉电阻
    ledio_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    ledio_config.pull_up_en = GPIO_PULLUP_DISABLE;
    ledio_config.intr_type = GPIO_INTR_DISABLE;
    ledio_config.pin_bit_mask = 1ULL<<LED_PIN;
    gpio_config(&ledio_config);
}
void VCC_init()
{
    gpio_config_t ledio_config;
    ledio_config.mode = GPIO_MODE_INPUT_OUTPUT;//输入输出模式
    //无上下拉电阻
    ledio_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    ledio_config.pull_up_en = GPIO_PULLUP_DISABLE;
    ledio_config.intr_type = GPIO_INTR_DISABLE;
    ledio_config.pin_bit_mask = 1ULL<<VCC;
    gpio_config(&ledio_config);
}

//按钮初始化函数
void button_init()
{
    gpio_config_t btnio_config;
    btnio_config.mode = GPIO_MODE_INPUT_OUTPUT;//输入输出模式
    //无下拉有上拉电阻
    btnio_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    btnio_config.pull_up_en = GPIO_PULLUP_ENABLE;
    btnio_config.intr_type = GPIO_INTR_NEGEDGE;//下降沿触发(需要上拉)
    btnio_config.pin_bit_mask = 1ULL<<BUTTON_PIN;
    gpio_config(&btnio_config);
    //检测那个管脚如何触发   buttn管脚下降沿触发
    gpio_set_intr_type(BUTTON_PIN,GPIO_INTR_NEGEDGE );
    //中断优先级
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);
    //中断处理函数
    gpio_isr_handler_add(BUTTON_PIN,button_isr_handler, NULL);

}
void app_main(void)
{
     
    printf("start!\n");
    led_init();
    VCC_init();
    button_init();
    while(1){
        gpio_set_level(BUTTON_PIN,!(gpio_get_level(BUTTON_PIN)));//取灯电平的反值，即电平转化
        printf("等待中断。。。当前按钮电平为：%d" , gpio_get_level(BUTTON_PIN));
        ESP_LOGW("中断次数记录:","已经触发%d次" ,cont);
        vTaskDelay(500/portTICK_PERIOD_MS);
            gpio_intr_disable(BUTTON_PIN);
    gpio_uninstall_isr_service();
    }
}
