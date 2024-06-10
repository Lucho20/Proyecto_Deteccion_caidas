#include <Controlador.h>

MPU6050* mpu6050 = new MPU6050();
RedWifi* wifi = new RedWifi();
Email* mail = new Email();
boolean posible_caida;
boolean caso_urgente;
int tiempo;

Controlador::Controlador(){
}

void Controlador::iniciar_programa(){
    wifi->conectar();
    posible_caida = false;
    caso_urgente = false;
    tiempo = 0;
    pinMode(2,OUTPUT);
    mail ->configurar_envio();
    
    //Comienza Calibracion
    digitalWrite(2,HIGH);
    mpu6050->iniciar_sensor();  
    delay(500);
    digitalWrite(2,LOW);
};

void Controlador::detectar_caida(){
    mpu6050->leer_sensor();
    float norma_acelerometro = obtener_norma(mpu6050->acelerometro_x,mpu6050->acelerometro_y,mpu6050->acelerometro_z);
    float norma_giroscopio = obtener_norma(mpu6050->giroscopio_x,mpu6050->giroscopio_y,mpu6050->giroscopio_z);

    if(!posible_caida && norma_acelerometro >= UMBRAL_ACELERACION && norma_giroscopio >= UMBRAL_GIROSCOPIO){
        posible_caida = true;
        tiempo = millis();
        digitalWrite(2,HIGH);
        return;
    }

    int tiempo_auxiliar = calcular_tiempo();

    if(posible_caida && norma_acelerometro <= UMBRAL_RECUPERACION){
        validar_caso_recuperacion(norma_acelerometro, tiempo_auxiliar);  
    } else if(posible_caida && norma_acelerometro > UMBRAL_RECUPERACION && tiempo_auxiliar >= UMBRAL_TIEMPO_URGENTE){
        validar_caso_urgente();
    }  

};

float Controlador::obtener_norma(float valor_x, float valor_y, float valor_z){
    return sqrt(valor_x*valor_x + valor_y*valor_y + valor_z*valor_z);
}

void Controlador::validar_caso_urgente(){
    if(!caso_urgente){
        caso_urgente = true;
        enviar_mail("Aviso Urgente!!! Detección de caída fuerte","Persona caída por más de 10 segundos");
    } 
    delay(10000);
}

void Controlador::validar_caso_recuperacion(float norma_acelerometro, int tiempo_auxiliar){
    if(tiempo_auxiliar >= UMBRAL_TIEMPO_URGENTE){
        caso_urgente = false;
        enviar_mail("Aviso de Recuperación","La persona se reincorporó de una caída urgente");
        limpiar_variables();
    }else if(tiempo_auxiliar >= UMBRAL_TIEMPO_CAIDA && tiempo_auxiliar < UMBRAL_TIEMPO_URGENTE){
        enviar_mail("Notificación de caída leve","La persona tuvo una caída pero ya se reincorporó");
        limpiar_variables();
    } else if(tiempo_auxiliar < UMBRAL_TIEMPO_CAIDA){
        limpiar_variables();
    }
}

void Controlador::limpiar_variables(){
    posible_caida = false;
    tiempo = 0;
    digitalWrite(2,LOW);
}

void Controlador::enviar_mail(String asunto, String mensaje){
    mail ->realizar_envio(asunto,mensaje);
}

int Controlador::calcular_tiempo(){
    if(caso_urgente){
        return UMBRAL_TIEMPO_URGENTE+1;
    } else {
        return millis()-tiempo;
    }
}