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

static esp_netif_t * esp_netif_ap;

/*
 * Wi-Fi app event handler
 * @param args, aside from event data, that is passed to the handler when it is called
 * @param event_base the base id of the event to register the handler for
 * @param event_id the id of the event to handle
 * @param event_data event data
 */
static void wifi_event_handler(void * args, esp_event_base_t event_base, int32_t event_id, void * event_data){
    if (event_base == WIFI_EVENT) {
        switch (event_id) {
            case WIFI_EVENT_AP_STACONNECTED: 
                ESP_LOGI(TAG, "Intruso detectado en la red!!");
                break;

            case WIFI_EVENT_AP_STADISCONNECTED:
                ESP_LOGI(TAG, "Intruso neutralizado!!");
                break;

            default:
                break;
        }
    }
}

//Funcion que corresponde a 1. Init phase 
static void wifi_init() {
    //Initialize the TCP/IP stack
    ESP_ERROR_CHECK(esp_netif_init());
    //Create system Event task and initialize an application event's callback function
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    //Asociamnos un event handler para gestionar eventos Wi-Fi en nuestro loop
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
            WIFI_EVENT, 
            ESP_EVENT_ANY_ID,
            &wifi_event_handler, //Function callback for when a Wi-Fi event occurs
            NULL,
            NULL
        ));
    //Definir configuracion estandar
    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT(); 
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
    ESP_LOGI(TAG, "Wi-Fi init phase finished");
}

//Funcion que corresponde a 2. Configuration phase
static void wifi_config_ap() {
    esp_netif_ap = esp_netif_create_default_wifi_ap(); 
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_APP_SSID,
            .password = WIFI_APP_PASSWD, 
            .ssid_len = strlen(WIFI_APP_SSID),
            .channel = WIFI_APP_CHANNEL,
            .ssid_hidden = WIFI_APP_AP_HIDDEN,
            .max_connection = WIFI_APP_MAX_CONNECTIONS,
        }
    };

    //Set static IP 
    ESP_ERROR_CHECK(esp_netif_dhcps_stop(esp_netif_ap)); //Stop DHCP service to configure it
    esp_netif_ip_info_t ap_ip_info; 
    memset(&ap_ip_info, 0, sizeof(esp_netif_ip_info_t));
    //Nuestra IP estatica
    ap_ip_info.ip.addr = ipaddr_addr(WIFI_APP_IP_ADDRESS);
    ap_ip_info.netmask.addr = ipaddr_addr(WIFI_APP_AP_NETMASK);
    ap_ip_info.gw.addr = ipaddr_addr(WIFI_APP_IP_ADDRESS);
    if(esp_netif_set_ip_info(esp_netif_ap, &ap_ip_info) != ESP_OK){
        ESP_LOGE(TAG, "Failed to set static IP info");
    }
    //Start DHCP service again
    ESP_ERROR_CHECK(esp_netif_dhcps_start(esp_netif_ap)); 
    //Show access point information
    ESP_LOGI(TAG, "SSID: %s", WIFI_APP_SSID);
    ESP_LOGI(TAG, "IP: %s", WIFI_APP_IP_ADDRESS);
    ESP_LOGI(TAG, "Gateway: %s", WIFI_APP_IP_ADDRESS);
    ESP_LOGI(TAG, "Netmask: %s", WIFI_APP_AP_NETMASK);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_set_bandwidth(ESP_IF_WIFI_AP, WIFI_APP_BANDWIDTH));
    
    ESP_LOGI(TAG, "Wi-Fi app configuration finished.");

    //Start Wi-Fi service (3. Start Phase)
    ESP_ERROR_CHECK(esp_wifi_start());
}

//El proceso que ejecuta nuestra aplicación Wi-Fi
static void wifi_task(void * parameters){
    wifi_init(); 
    wifi_config_ap();
    while(1) {
        vTaskDelay(1);
    }
}

void start_wifi_app(){
    ESP_LOGI(TAG, "Starting Wi-Fi app");
    //Inicializar la queue
    wifi_app_queue = xQueueCreate(10, sizeof(wifi_app_message_t));
    //Crear Wi-Fi app task
    xTaskCreate(&wifi_task,"wifi_app_task", WIFI_APP_STACK_SIZE, NULL, WIFI_APP_TASK_PRIORITY, NULL);
}