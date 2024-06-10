#include <Arduino.h>
#include <Wire.h>

#define DIRECCION_MPU 0x68
#define DIRECCION_UBICACION_LECTURA 0x3B
#define SENSIBILIDAD_ACELEROMETRO 4096.00 // +-8g
#define SENSIBILIDAD_GIROSCOPIO 65.5 // 500 °/s
#define CANTIDAD_MUESTRAS_CALIBRACION 2000
#define DIRECCION_REGISTRO_ACELEROMETRO 0x3B
#define DIRECCION_REGISTRO_GIROSCOPIO 0x43

class MPU6050
{
    public:
    MPU6050();
    float acelerometro_x, acelerometro_y, acelerometro_z;
    float giroscopio_x, giroscopio_y, giroscopio_z;
    float offset_acelerometro_x, offset_acelerometro_y, offset_acelerometro_z;
    float offset_giroscopio_x, offset_giroscopio_y, offset_giroscopio_z; 
    void iniciar_sensor();
    void calibrar_sensor();
    void leer_sensor();

    private:
    void obtener_acelerometro_giroscopio();
    void inicializar_transmision_libreria(int direccion_registro);
    void obtener_valores_ejes(int direccion, float* valor_x, float* valor_y, float* valor_z);
    
};