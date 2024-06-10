#include <Email.h>

Session_Config configuracion;
SMTP_Message mensaje;

Email::Email(){
}

void Email::configurar_envio(){
    configuracion.server.host_name = SMTP_HOST;
    configuracion.server.port = SMTP_PORT;
    configuracion.login.email = MAIL_DESDE;
    configuracion.login.password = CONTRASENIA_MAIL_DESDE;
    configuracion.login.user_domain = "";
    configuracion.time.ntp_server = F("pool.ntp.org,time.nist.gov");
    configuracion.time.gmt_offset = 0;
    configuracion.time.day_light_offset = 0;
    configuracion.time.timezone_env_string = "<-03>3"; //Codigo de Argentina

    mensaje.sender.name = F("Faders");
    mensaje.sender.email = MAIL_DESDE;

    mensaje.addRecipient(F("Familiar"), MAIL_PARA);
    mensaje.text.transfer_encoding = "base64"; 
    mensaje.text.charSet = F("utf-8"); 
    mensaje.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;
};

void Email::realizar_envio(String asunto, String texto){
    mensaje.subject = asunto;
    mensaje.text.content = texto; 
    SMTPSession smtp;
    smtp.debug(1);
    //Se conecta al servidor SMTP
    if (!smtp.connect(&configuracion)) {
        MailClient.printf("Connection error, Status Code: %d, Error Code: %d, Reason: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
        return;
    }

    if (!smtp.isLoggedIn()) {
        Serial.println("Not yet logged in.");
    }

     // Envía el email y cierra la sesión    
    if (!MailClient.sendMail(&smtp, &mensaje))
        MailClient.printf("Error, Status Code: %d, Error Code: %d, Reason: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());

    smtp.sendingResult.clear();
};