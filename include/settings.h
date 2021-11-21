/* This file contains all the necessary settings for EHAM,
   and can be customized to suit your application.
*/

// Ethernet Settings
#define DHCP 1  // 1 for DHCP, 0 for static IP
#define MAC { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 }  // ethernet MAC address: check your device for a sticker
#define IP { 192, 168, 1, 2 }  // static IP if DHCP not enabled
#define GATEWAY { 192, 168, 1, 1 }  // gateway IP for when not using DHCP

// EHAM settings
#define DEBUG 1  // 1 for serial debugging enabled, 0 for none

// MQTT settings
#define HOSTNAME "hostname"  // server hostname, leave blank to use IP
#define SERVER { 1, 2, 3, 4 }   // server IP address if not using hostname
#define DISCOVERY_PREFIX "homeassistant" // see https://www.home-assistant.io/docs/mqtt/discovery/
#define DISCOVERY_FREQ 0 // discovery message send frequency in minutes. 0 disables

// component settings see https://www.home-assistant.io/docs/mqtt/discovery/
char *components[] = {"binary_sensor",
                      "light",
                      "switch"};
char *node_id[]    = {"0a01",
                      "0a02",
                      "0a03"};
