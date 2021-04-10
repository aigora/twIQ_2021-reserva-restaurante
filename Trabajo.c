#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NPLAZAS 50

struct usuario {
	char nombre[50];
	char contraseña[50];
}; //registro usuario

struct mesa {
	int estado_actual; // 1 Ocupada 0 Libre
	char tipo; //Terraza o Sala
	char numero[3];
};

int main(){
	char opcion;
	int i;
	struct usuario ;
	
	/*MENU D- Ver disponibilidad del restaurante
	       C- Ver carta
	       R- Hacer una reserva (submenu)
	       B- Borrar una reserva
	       S- Salir del restaurante
	*/
	do {
		printf("Introduzca la opcion:\n");
		fflush(stdin);
		scanf("%d", &opcion);
		
		switch(opcion){ 
		
		     case'D':
			     printf("Aqui se programaria la opcion de la disponibilidad del restaurante.\n");
			     break;
		     case'C':
			     printf("Aqui se programaria la opcion de ver la carta.\n"):
			     break;
		     case'R':
			     printf("Aqui se programaria la opcion de reservar (en terraza o en el comedor de dentro; mesa de 2, 4 o 6).\n");
			     break;
		     case'B':
		         printf("Aqui se programaria la opcion de borrar una reserva.\n");
			     break;
		     case'S':
			     printf("Gracias por confiar en nosotros.\n");
			     return 0;
			     default:
				printf("ERROR.\n");	
			           }
		}
	while (opcion != 'S'){
	}
	
	       
	
	
	
}
