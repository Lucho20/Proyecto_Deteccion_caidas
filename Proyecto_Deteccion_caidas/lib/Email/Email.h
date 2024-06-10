#include <Arduino.h>
#include <ESP_Mail_Client.h>
#include <Variables.h>

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define MAIL_DESDE "noreply.faders@gmail.com"
#define CONTRASENIA_MAIL_DESDE "dqvvlctsxmmjavij"

class Email
{
    public:
    Email();
    void configurar_envio();
    void realizar_envio(String asunto, String texto);

    private:
};