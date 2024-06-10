#include <Arduino.h>
#include <MPU6050.h>
#include <Controlador.h>

MPU6050* mpu6050 = new MPU6050();
Controlador* controlador = new Controlador();

int cantidad_muestras = 0;
long tiempo_acumulado = 0;
int tiempo_auxiliar2 = 0;
int tiempo_controlador = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  delay(5000);
  mpu6050->iniciar_sensor();
  Serial.println("Comienza Calibracion...."); 
  digitalWrite(2,HIGH);
  int tiempo_calibracion = millis();
  mpu6050->calibrar_sensor();
  tiempo_calibracion = millis()-tiempo_calibracion;
  Serial.println("Calibracion Finalizada"); 
  Serial.print("Tiempo total: "); Serial.println(tiempo_calibracion);
  Serial.print("Offset AcX = "); Serial.print(mpu6050->offset_acelerometro_x);
  Serial.print(" | Offset AcY = "); Serial.print(mpu6050->offset_acelerometro_y);
  Serial.print(" | Offset AcZ = "); Serial.println(mpu6050->offset_acelerometro_z);
  Serial.print("Offset GiX = "); Serial.print(mpu6050->offset_giroscopio_x);
  Serial.print(" | Offset GiY = "); Serial.print(mpu6050->offset_giroscopio_y);
  Serial.print(" | Offset GiZ = "); Serial.println(mpu6050->offset_giroscopio_z);
  tiempo_calibracion = millis();
  controlador -> iniciar_programa();
  tiempo_calibracion = millis()-tiempo_calibracion;
  Serial.print("Tiempo configuracion: "); Serial.println(tiempo_calibracion);
  
}

void loop() {
  if (cantidad_muestras == 0){
    Serial.println("Comienza a tomar datos....."); 
    cantidad_muestras++;
    digitalWrite(2,LOW);
    delay(500);
  } else if(cantidad_muestras <= 3000){
    tiempo_auxiliar2 = micros();
    mpu6050->leer_sensor();
    cantidad_muestras++;
    int tiempo_temporal = micros()-tiempo_auxiliar2;
    tiempo_acumulado += tiempo_temporal;
    Serial.print("AcX = "); Serial.print((float)(mpu6050->acelerometro_x));
    Serial.print(" | AcY = "); Serial.print((float)(mpu6050->acelerometro_y));
    Serial.print(" | AcZ = "); Serial.print((float)(mpu6050->acelerometro_z));
    Serial.print(" | GiX = "); Serial.print((float)(mpu6050->giroscopio_x));
    Serial.print(" | GiY = "); Serial.print((float)(mpu6050->giroscopio_y));
    Serial.print(" | GiZ = "); Serial.print((float)(mpu6050->giroscopio_z));
    Serial.print(" | Tiempo: "); Serial.println(tiempo_acumulado);
    tiempo_controlador = micros();
    Serial.println(controlador->detectar_caida(mpu6050->acelerometro_x,mpu6050->acelerometro_y,mpu6050->acelerometro_z,mpu6050->giroscopio_x,mpu6050->giroscopio_y,mpu6050->giroscopio_z));
    tiempo_controlador = micros() - tiempo_controlador;
    //Serial.print("Tiempo controlador: ");Serial.println(tiempo_controlador);
  } else if (cantidad_muestras == 3001){
    Serial.print("Tiempo promedio: "); Serial.println((float)tiempo_acumulado/1000);
    cantidad_muestras++;
  } else {
    cantidad_muestras++;
  }
  delay(50);
}
