#include <RedWifi.h>

RedWifi::RedWifi(){
    _ssid = NOMBRE_RED;
    _password = CONTRASENA_RED;
}

void RedWifi::conectar(){
	WiFi.begin(_ssid, _password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}

}
