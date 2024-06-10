#include <Arduino.h>

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
    String detectar_caida(float ax,float ay,float az,float gx,float gy,float gz);

    private:
    float obtener_norma(float valor_x, float valor_y, float valor_z);
    String validar_caso_urgente();
    String validar_caso_recuperacion(float norma_acelerometro, int tiempo);
    void limpiar_variables();
    int calcular_tiempo();
};