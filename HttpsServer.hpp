#pragma once
#include <string>
#include "esp_https_server.h"

/**
 * HTTPS server class
 * c++ wraper for ESP32 (ESP-IDF)
 */

class HttpsServer
{
public:
    HttpsServer(int port, uint8_t *cert_pem, uint8_t *key_pem, size_t cert_len, size_t key_len);

    // important! call this function only after server->start()
    void registerURI(std::string uri, httpd_method_t method, esp_err_t (*handler)(httpd_req_t *r));
    bool isRunning();
    void start();
    void stop();

private:
    httpd_ssl_config_t conf;
    httpd_handle_t server_handle;
    bool running = false;
};