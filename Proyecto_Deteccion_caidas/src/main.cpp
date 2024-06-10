#include <Arduino.h>
#include <Controlador.h>

Controlador* controlador = new Controlador();

void setup() {
  Serial.begin(115200);
  delay(2000);
  controlador -> iniciar_programa();
}

void loop() {
  controlador->detectar_caida();
  delay(50);
}
