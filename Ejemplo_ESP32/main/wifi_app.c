#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif_net_stack.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/lwip_napt.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "wifi_app.h"

#define TAG "WIFI_APP"

//Queue que me ayudara a comunicar con el proceso Wi-Fi app
static QueueHandle_t wifi_app_queue; 

//El proceso que ejecuta nuestra aplicación Wi-Fi
static void wifi_task(void * parameters){
    while(1) {

        ESP_LOGI(TAG,"Soy un task corriendo");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void start_wifi_app(){
    ESP_LOGI(TAG, "Starting Wi-Fi app");
    //Inicializar la queue
    wifi_app_queue = xQueueCreate(10, sizeof(wifi_app_message_t));
    //Crear Wi-Fi app task
    xTaskCreate(&wifi_task,"wifi_app_task", WIFI_APP_STACK_SIZE, NULL, WIFI_APP_TASK_PRIORITY, NULL);
}