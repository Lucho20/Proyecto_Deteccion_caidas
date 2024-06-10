#include <Arduino.h>
#include <MPU6050.h>
#include <RedWifi.h>
#include <Email.h>

#define UMBRAL_ACELERACION 0.75
#define UMBRAL_GIROSCOPIO 92.0
#define UMBRAL_RECUPERACION 0.75
#define UMBRAL_TIEMPO_URGENTE 10000
#define UMBRAL_TIEMPO_CAIDA 1000

class Controlador
{
    public:
    Controlador();
    void iniciar_programa();
    void detectar_caida();

    private:
    float obtener_norma(float valor_x, float valor_y, float valor_z);
    void validar_caso_urgente();
    void validar_caso_recuperacion(float norma_acelerometro, int tiempo);
    void limpiar_variables();
    void enviar_mail(String asunto, String mensaje);
    int calcular_tiempo();
};