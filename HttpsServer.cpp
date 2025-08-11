#include "HttpsServer.hpp"

HttpsServer::HttpsServer(int port, uint8_t *cert_pem, uint8_t *key_pem, size_t cert_len, size_t key_len)
{
    this->conf.httpd.server_port = port;

    this->conf = HTTPD_SSL_CONFIG_DEFAULT();
    this->conf.servercert = cert_pem;
    this->conf.servercert_len = cert_len;
    this->conf.prvtkey_pem = key_pem;
    this->conf.prvtkey_len = key_len;
}

void HttpsServer::registerURI(char *uri, httpd_method_t method, esp_err_t (*handler)(httpd_req_t *r))
{
    if(!isRunning()) return; // becose the handle == NULL, please do start() before
    httpd_uri_t _uri = {
        .uri = uri,
        .method = method,
        .handler = handler,
        .user_ctx = NULL
    };
    ESP_ERROR_CHECK(httpd_register_uri_handler(this->server_handle, &_uri));
}

bool HttpsServer::isRunning()
{
    return this->running;
}

void HttpsServer::start()
{
    ESP_ERROR_CHECK(httpd_ssl_start(&(this->server_handle), &(this->conf)));
    this->running = true;
}

void HttpsServer::stop()
{
    ESP_ERROR_CHECK(httpd_ssl_stop(this->server_handle));
    this->running = false;
}