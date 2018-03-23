/*****LIBRERIAS******/

#include <NewPing.h>

/*****VARIABLES******/

int z;
int eleccion;
boolean a,b; 
char dato;
int d;
int i;
int distancia;

void setup() {
  Serial.begin(9600);

}

void loop() {
  
/*****CONFIGURACION PARA ELEGIR MODO*****/

  dato = Serial.read();
  Serial.println(dato);
  switch (dato) {
    case ('W'):{
      z=1;
      break;
    }
    case ('w'):{
      z=0;
      break;
    }
  }
  
/*****CASO 1 EVITA OBSTACULOS*****/

  if (z==1){
    //Serial.println("Primero");
    //Configuracion del Ultrasonidos
    #define TRIGGER_PIN  5
    #define ECHO_PIN     3 
    #define MAX_DISTANCE 400
    NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
    //distancia=sonar.ping_cm();
    //Serial.println(sonar.ping_cm());
    if((sonar.ping_cm())<20){//Cuando esta ha menos de 20 cm hace un cosa
      //MOTOR-DER
      analogWrite(10,75);
      digitalWrite(7,1);
      digitalWrite(6,0);
      //MOTOR-IZQ
      analogWrite(11,75);
      digitalWrite(8,0);
      digitalWrite(9,1);
    }
    else if ((sonar.ping_cm())<50){//Cuando esta a menos de 50 cm baja la velocidad
      Movimiento(1,0,75,75);
    }
    else if((sonar.ping_cm())>50){//Cuando esta a mas de 50 cm funciona con la velocidad maxima puesta
      Movimiento(1,0,100,100);
    }
  }
  
/*****CASO 0 EL BLUETOOTH*****/  

  if (z==0){
    //Serial.println("cero");
    //Usamos directamente el case porque no hace falta que vuelva a leer dato ya que lo hemos puesto antes
    switch (dato) {
      case ('X'):{ //PULSANDO EL BOTON TRIANGULO AUMENTAMOS LA VELOCIDAD AL MAXIMO
        i=255;
        d=255;
        break;//SE USA PARA SALIR DEL CASE UNA VEZ QUE SE HA EJECUTADO LA SENTENCIA COMPLETA Y QUE NO COINCIDE LA LETRA QUE TIENE DATO CON LA DE ESE CASE
      }
       case ('x'):{  //NO PULSANDO EL BOTON TRIANGULO PONEMOS LA VELOCIDAD A LA MITAD
        i=128;
        d=128;
        break;
      }        
      case ('F'):{  //PARA ALANTE
        Movimiento (1,0,i,d);
        break;
      }
      case ('B'):{  //PARA ATRAS
        Movimiento (0,1,i,d);
        break;
      }
      case ('L'):{  //DERECHA
        Movimiento (1,0,i,0);
        break;
      }
      case ('R'):{  //IZQUIERDA
        Movimiento (1,0,0,d);
        break;
      }
      case ('G'):{  //ALANTE DERECHA
        Movimiento (1,0,i,d-30);
        break;
      }
      case ('I'):{  //ALANTE IZQUIERDA
        Movimiento (1,0,i-30,d);
        break;
      } 
      case ('H'):{  //ATRAS DERECHA
        Movimiento (1,0,i,d-30);
        break;
      }
      case ('J'):{  //ATRAS IZQUIERDA
        Movimiento (1,0,i-30,d);
        break;
      }                     
      case ('S'):{  //STOP
        Movimiento (1,0,0,0);
        break;
      }        
    }
  }
}

/*****FUNCION DE USUARIO*****/

void Movimiento (int a, int b, int i, int d){
  //MOTOR-DER
  analogWrite(10,i);
  digitalWrite(7,a);
  digitalWrite(6,b);
  //MOTOR-IZQ
  analogWrite(11,d);
  digitalWrite(8,a);
  digitalWrite(9,b);
}
