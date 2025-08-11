#pragma once
#include "esp_https_server.h"

/**
 * HTTPS server class
 * c++ wrapper for ESP32 (ESP-IDF)
 */

class HttpsServer
{
public:
    HttpsServer(const uint8_t *cert_pem, const uint8_t *key_pem, size_t cert_len, size_t key_len);

    // important! call this function only after server->start()
    void registerURI(char* uri, httpd_method_t method, esp_err_t (*handler)(httpd_req_t *r));
    bool isRunning();
    void start();
    void stop();

private:
    httpd_ssl_config_t conf;
    httpd_handle_t server_handle;
    bool running = false;
};