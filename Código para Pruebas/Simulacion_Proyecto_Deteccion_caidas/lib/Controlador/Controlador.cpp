#include <Controlador.h>

boolean posible_caida;
boolean caso_urgente;
int tiempo;

Controlador::Controlador(){
}

void Controlador::iniciar_programa(){
    posible_caida = false;
    caso_urgente = false;
    tiempo = 0;
};

String Controlador::detectar_caida(float ax,float ay,float az,float gx,float gy,float gz){
    float norma_acelerometro = obtener_norma(ax,ay,az);
    float norma_giroscopio = obtener_norma(gx,gy,gz);
    String resultado = " ";
    if(!posible_caida && norma_acelerometro >= UMBRAL_ACELERACION && norma_giroscopio >= UMBRAL_GIROSCOPIO){
        posible_caida = true;
        tiempo = millis();
        digitalWrite(2,HIGH);
        return "Posible caída";
    }

    int tiempo_auxiliar = calcular_tiempo();

    if(posible_caida && norma_acelerometro <= UMBRAL_RECUPERACION){
        resultado = validar_caso_recuperacion(norma_acelerometro, tiempo_auxiliar);  
    } else if(posible_caida && norma_acelerometro > UMBRAL_RECUPERACION && tiempo_auxiliar >= UMBRAL_TIEMPO_URGENTE){
        resultado = validar_caso_urgente();
    } else if(posible_caida) {
        resultado = " ";
    } 
    
    return resultado;
};

float Controlador::obtener_norma(float valor_x, float valor_y, float valor_z){
    return sqrt(valor_x*valor_x + valor_y*valor_y + valor_z*valor_z);
}

String Controlador::validar_caso_urgente(){
    if(!caso_urgente){
        caso_urgente = true;
        digitalWrite(2,LOW);
        delay(100);
        digitalWrite(2,HIGH);
        delay(100);
        digitalWrite(2,LOW);
        delay(100);
        digitalWrite(2,HIGH);
        delay(10000);
        return "Envia Email Urgente";
    } else {
        delay(10000);
        return " ";
    }
}

String Controlador::validar_caso_recuperacion(float norma_acelerometro, int tiempo_auxiliar){
    if(tiempo_auxiliar >= UMBRAL_TIEMPO_URGENTE){
        caso_urgente = false;
        digitalWrite(2,LOW);
        delay(100);
        digitalWrite(2,HIGH);
        delay(100);
        digitalWrite(2,LOW);
        delay(100);
        digitalWrite(2,HIGH);
        limpiar_variables();
        return "Aviso Recuperacion";
    }else if(tiempo_auxiliar >= UMBRAL_TIEMPO_CAIDA && tiempo_auxiliar < UMBRAL_TIEMPO_URGENTE){
        digitalWrite(2,LOW);
        delay(100);
        digitalWrite(2,HIGH);
        delay(100);
        digitalWrite(2,LOW);
        delay(100);
        digitalWrite(2,HIGH);
        limpiar_variables();
        return "Envia Email Leve";
    } else if(tiempo_auxiliar < UMBRAL_TIEMPO_CAIDA){
        limpiar_variables();
        return "Falsa detección";
    } else {
        return " ";
    }
}

void Controlador::limpiar_variables(){
    posible_caida = false;
    tiempo = 0;
    digitalWrite(2,LOW);
}

int Controlador::calcular_tiempo(){
    if(caso_urgente){
        return UMBRAL_TIEMPO_URGENTE+1;
    } else {
        return millis()-tiempo;
    }
}