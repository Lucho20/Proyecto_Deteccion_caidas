#include <MPU6050.h>

MPU6050::MPU6050(){
    Wire.begin();
    acelerometro_x = 0, acelerometro_y = 0, acelerometro_z = 0;
    giroscopio_x = 0, giroscopio_y = 0, giroscopio_z = 0; 
}

void MPU6050::iniciar_sensor(){
    Wire.setClock(400000);
    Wire.beginTransmission(DIRECCION_MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(DIRECCION_MPU);
    Wire.write(0x1C);
    Wire.write(0x10);
    Wire.endTransmission();
    Wire.beginTransmission(DIRECCION_MPU);
    Wire.write(0x1B);
    Wire.write(0x08);
    Wire.endTransmission();
}

void MPU6050::leer_sensor(){
    obtener_acelerometro_giroscopio();
}

void MPU6050::obtener_acelerometro_giroscopio(){
    obtener_valores_ejes(DIRECCION_REGISTRO_ACELEROMETRO, &acelerometro_x,&acelerometro_y,&acelerometro_z);
    obtener_valores_ejes(DIRECCION_REGISTRO_GIROSCOPIO, &giroscopio_x,&giroscopio_y,&giroscopio_z);
}

void MPU6050::obtener_valores_ejes(int direccion, float* valor_x, float* valor_y, float* valor_z){
    inicializar_transmision_libreria(direccion);
    *valor_x = (int16_t)(Wire.read()<<8 | Wire.read());
    *valor_y = (int16_t)(Wire.read()<<8 | Wire.read());
    *valor_z = (int16_t)(Wire.read()<<8 | Wire.read());
}

void MPU6050::inicializar_transmision_libreria(int direccion_registro){
    Wire.beginTransmission(DIRECCION_MPU);
    Wire.write(direccion_registro);
    Wire.endTransmission(false);
    Wire.requestFrom(DIRECCION_MPU, 6); 
}

void MPU6050::calibrar_sensor(){
    long offsetAcX = 0,offsetAcY = 0,offsetAcZ = 0,offsetGiX = 0,offsetGiY = 0,offsetGiZ = 0;
    for(int i = 0; i < CANTIDAD_MUESTRAS_CALIBRACION; i++){
        obtener_acelerometro_giroscopio();
        offsetAcX += acelerometro_x;
        offsetAcY += acelerometro_y;
        offsetAcZ += acelerometro_z;
        offsetGiX += giroscopio_x;
        offsetGiY += giroscopio_y;
        offsetGiZ += giroscopio_z; 
        delay(1);
    }
    offset_acelerometro_x = offsetAcX / (float)(CANTIDAD_MUESTRAS_CALIBRACION);
    offset_acelerometro_y = offsetAcY / (float)(CANTIDAD_MUESTRAS_CALIBRACION);
    offset_acelerometro_z = offsetAcZ / (float)(CANTIDAD_MUESTRAS_CALIBRACION);
    offset_giroscopio_x = offsetGiX / (float)(CANTIDAD_MUESTRAS_CALIBRACION);
    offset_giroscopio_y = offsetGiY / (float)(CANTIDAD_MUESTRAS_CALIBRACION);
    offset_giroscopio_z = offsetGiZ / (float)(CANTIDAD_MUESTRAS_CALIBRACION);
}