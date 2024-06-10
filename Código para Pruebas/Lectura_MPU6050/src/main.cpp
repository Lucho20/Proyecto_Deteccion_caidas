#include <Arduino.h>
#include <MPU6050.h>

MPU6050* mpu6050 = new MPU6050();

int cantidad_muestras = 0;
long tiempo_acumulado = 0;
int tiempo_auxiliar = 0;

void setup() {
  Serial.begin(115200);
  delay(5000);
  mpu6050->iniciar_sensor();
  int tiempo_calibracion = millis();
  mpu6050->calibrar_sensor();
  tiempo_calibracion = millis()-tiempo_calibracion;
  Serial.println("Offset MPU6050"); 
  Serial.print("Tiempo total: "); Serial.println(tiempo_calibracion);
  Serial.print("Offset AcX = "); Serial.print(mpu6050->offset_acelerometro_x);
  Serial.print(" | Offset AcY = "); Serial.print(mpu6050->offset_acelerometro_y);
  Serial.print(" | Offset AcZ = "); Serial.println(mpu6050->offset_acelerometro_z);
  Serial.print("Offset GiX = "); Serial.print(mpu6050->offset_giroscopio_x);
  Serial.print(" | Offset GiY = "); Serial.print(mpu6050->offset_giroscopio_y);
  Serial.print(" | Offset GiZ = "); Serial.println(mpu6050->offset_giroscopio_z);
}

void loop() {
  if (cantidad_muestras == 0){
    Serial.println("Resultados MPU6050"); 
    cantidad_muestras++;
  } else if(cantidad_muestras <= 2000){
    tiempo_auxiliar = micros();
    mpu6050->leer_sensor();
    int tiempo_temporal = micros()-tiempo_auxiliar;
    tiempo_acumulado += tiempo_temporal;
    cantidad_muestras++;
    Serial.print("AcX = "); Serial.print((float)(mpu6050->acelerometro_x));
    Serial.print(" | AcY = "); Serial.print((float)(mpu6050->acelerometro_y));
    Serial.print(" | AcZ = "); Serial.print((float)(mpu6050->acelerometro_z));
    Serial.print(" | GiX = "); Serial.print((float)(mpu6050->giroscopio_x));
    Serial.print(" | GiY = "); Serial.print((float)(mpu6050->giroscopio_y));
    Serial.print(" | GiZ = "); Serial.print((float)(mpu6050->giroscopio_z));
    Serial.print(" | Tiempo: "); Serial.println(tiempo_acumulado);
  } else if (cantidad_muestras == 2001){
    Serial.print("Tiempo promedio: "); Serial.println((float)tiempo_acumulado/2000);
    cantidad_muestras++;
  } else {
    cantidad_muestras++;
  }
  delay(1);
}
