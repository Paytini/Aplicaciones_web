
//Constantes para la configuracion del punto de acceso 
#define WIFI_APP_SSID "CSI_EJEMPLO_AP"
#define WIFI_APP_PASSWD "root1234"
#define WIFI_APP_IP_ADDRESS "192.168.1.1"
#define WIFI_APP_AP_NETMASK "255.255.255.0"
#define WIFI_APP_AP_HIDDEN 0 //1 - Hide SSID, 0 - Show SSID 
#define WIFI_APP_CHANNEL 1
#define WIFI_APP_MAX_CONNECTIONS 5
#define WIFI_APP_BEACON_INTERVAL 100
#define WIFI_APP_BANDWIDTH WIFI_BW_HT20
#define WIFI_APP_MAX_RETRIES 10

//Constantes para FreeRTOS task
#define WIFI_APP_STACK_SIZE 2048
#define WIFI_APP_TASK_PRIORITY 5 //6 is top priority, for tasks related to interruptions
#define WIFI_APP_CORE_ID 0 

typedef struct wifi_app_message {
    
}wifi_app_message_t;

void start_wifi_app(); 