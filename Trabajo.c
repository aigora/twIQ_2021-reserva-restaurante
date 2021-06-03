//Librerías
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//Constantes definidas
#define MAX 40
#define MAXMESAS 20
#define MAXUSUARIOS 50

//Estructura usuarios
struct usuario{
	char nombre[MAX]; //nombre de usuario
	char pass[MAX];	//contraseña
};

//Estructura mesas
struct mesa
{	int sala; //0=sinAsignar 1=sala 2=terraza
	int libre; //1=libre 2=reservada
	char nombre[MAX]; //nombre de reserva
};

//Funciones
void menu1();
void menu2();
bool existeUsuario(struct usuario r[MAXUSUARIOS], char nombre[MAX], char pass[MAX]);
bool existeNombreUsuario(struct usuario r[MAXUSUARIOS], char nombre[MAX]);
void insertarUsuario(struct usuario r[MAXUSUARIOS], char nombre[MAX], char pass[MAX]);
void mostrarCarta();
void mostrarEstado(struct mesa r[MAXMESAS]);
int numSala(struct mesa r[MAXMESAS]);
int numTerraza(struct mesa r[MAXMESAS]);
void eliminarReserva(struct mesa r[MAXMESAS], char nombre[MAX]);
void guardarEstadoRestaurante(struct mesa r[MAXMESAS]);
void guardarUsuariosRegistrados(struct usuario r[MAXUSUARIOS]);
	
//Programa principal
int main(int argc, char *argv[]) {
	int opcion,opcion2,opcionMesa;
	int i,j;
	bool salir=false,reservada=false;
	bool completo;
	char s[MAX],nombre[MAX], cad[MAX];
	char pass[MAX];
	int sala,libre;
	char car;
	struct mesa restaurante[MAXMESAS];
	struct usuario registrados[MAXUSUARIOS];


	FILE *f = fopen("registros.txt", "r");
	FILE *f2 = fopen("restaurante.txt","r");
	
	if (f==NULL){
		perror ("Error al abrir registros.txt"); 
	}
	if (f2==NULL){
		perror ("Error al abrir restaurante.txt");
	}

	//Inicializar vector usuarios
	for(i=0;i<MAXUSUARIOS;i++){
		strcpy(registrados[i].nombre,"");
		strcpy(registrados[i].pass,"");
	}
	
	//Inicializar vector mesas
	for(i=0;i<MAXMESAS;i++){
		restaurante[i].libre=1; //Inicialmente todas las mesas libres, hasta 10 en terraza y 10 en sala, 1=sala, 2=terraza
		restaurante[i].sala=0;
							  
		strcpy(restaurante[i].nombre,"");
	}
	
	//Leer todos los usuarios registrados y guardarlos en fichero
	i=0;
	while(fscanf(f,"%s",registrados[i].nombre)!=EOF)
	{
       fscanf(f,"%s",registrados[i].pass); 
       i++;
	}

	fclose(f);
	
	//Leer todas las mesas y guardarlas en el fichero
	i=0;
	while(fscanf(f2,"%i",&sala)!=EOF)
	{  
	   restaurante[i].libre=2;
       if(sala==1){
       		restaurante[i].sala=1;
	   }
	   else if(sala==2){
	   		restaurante[i].sala=2;
	   }
	   else{
	   		restaurante[i].sala=0;
	   }
	   
	   fgetc(f2);
	   
       fgets(cad,40,f2);
       strcpy(restaurante[i].nombre,cad);
       i++;
	}
	
	fclose(f2);


	do{
	    system("cls");
		menu1();
		//Leemos opción del usuario
		scanf("%d",&opcion);
		fflush(stdin);
		switch(opcion){
			case 1:completo=false;
				   do{	
					   printf("\nIntroduzca datos para realizar el registro:\n");
					   printf("Nombre de usuario: ");
				       scanf("%s",s);
				  	   fflush(stdin);
				       printf("Password: ");
				       scanf("%s",pass);
				       fflush(stdin);	
				       printf("Ha introducido: %s -- %s\n",s,pass);
				       if(existeNombreUsuario(registrados,s)){
				   	    	printf("Usuario existente. Por favor, introduzca otro nombre:\n"); 
				       }
				       else{
				   	    	completo=true;
				   	    	insertarUsuario(registrados,s,pass);
				   	    	printf("Registro completado\n");
				       }
					}while(!completo);
				   break;
			case 2:printf("\nIntroduzca datos para iniciar sesion:\n");
				   printf("Nombre de usuario: ");
				   scanf("%s",s);
				   fflush(stdin);
				   printf("Password: ");
				   scanf("%s",pass);
				   fflush(stdin);	
				   if(existeUsuario(registrados, s,pass)){
				   		printf("Conectado como: %s\n",s);
				   		do{
				   			system("pause");
				   			system("cls");
							menu2();
							scanf("%d",&opcion2);
							fflush(stdin);
							switch(opcion2){
								case 1: mostrarCarta();
									break;
								case 2: mostrarEstado(restaurante);
									break;
								case 3: printf("Introduzca nombre para la reserva: ");
										fgets(cad, MAX, stdin);
				   						fflush(stdin);
										opcionMesa=0;
										if(numSala(restaurante)<=10 && numTerraza(restaurante)<=10){
											printf("Indique si desea la mesa en sala (1) o en terraza (2): ");
											scanf("%i",&opcionMesa);
											fflush(stdin);
										}
										else{
											if(numTerraza(restaurante)==10 && numSala(restaurante)<=10){
												printf("No hay mesas en terraza, se le asigna mesa en sala\n");
												opcionMesa=1;
											}
											else if(numTerraza(restaurante)<=10 && numSala(restaurante)==10){
												printf("No hay mesas en sala, se le asigna mesa en terraza\n");
												opcionMesa=2;
											}
											else{
												printf("Lamentamos decirle que no hay mesas disponibles\n");
											}
										}
										if(opcionMesa!=0){
											reservada=false;
											for(j=0;j<MAXMESAS;j++){
												if (restaurante[j].libre==1 && !reservada){
													strcpy(restaurante[i].nombre,cad);
													restaurante[i].sala=opcionMesa;
													restaurante[i].libre=2;
													reservada=true;
													printf("Mesa reservada a nombre de %s\n",cad);
												}
											}
										}
									break;
								case 4:printf("Introduzca el nombre de la reserva: ");
									   fgets(cad, MAX, stdin);
									   fflush(stdin);
									   eliminarReserva(restaurante,cad);
									break;
								case 5: guardarEstadoRestaurante(restaurante);
										guardarUsuariosRegistrados(registrados);
										printf("Gracias por confiar en nosotros.\n");
									 	salir=true;
									break;
							}
				   		}while(!salir);
				   }
				   else{
				   		printf("ERROR. Usuario no registrado. Por favor, registrese.\n");
				   }
		}
	
		system("pause");
	}while(!salir);
	return 0;
}

//Funciones

//menú 1
void menu1(){
	printf("¡Bienvenidos al restaurante S & M!\n");
	printf("==================================\n");
	printf("1. Registrarse (usuario y password)\n");
	printf("2. Iniciar sesion\n");
	printf("\nIntroduzca su opcion.. ");
}

//menú 2
void menu2(){
	
	printf("¡Bienvenidos al restaurante S & M!\n");
	printf("==================================\n");
	printf("1. Consultar la carta\n");
	printf("2. Consultar estado del restaurante\n");
	printf("3. Realizar una reserva\n");
	printf("4. Cancelar una reserva\n"); 
	printf("5. Salir del programa\n" );
	printf("\nIntroduzca su opcion.. ");
	
}

//Comprobacion si existe un usuario (nombre de usuario y password)
bool existeUsuario(struct usuario r[MAXUSUARIOS], char nombre[MAX], char pass[MAX]){
	int i;
	bool resultado=false;
	for(i=0;i<MAXUSUARIOS;i++){
		if(strcmp(r[i].nombre,nombre)==0 && strcmp(r[i].pass,pass)==0){
			//El usuario ya existe
			resultado=true;
		}
	}
	return resultado;
}

//Comprobacion si existe un nombre de usuario
bool existeNombreUsuario(struct usuario r[MAXUSUARIOS], char nombre[MAX]){
	int i;
	bool resultado=false;
	for(i=0;i<MAXUSUARIOS;i++){
		if(strcmp(r[i].nombre,nombre)==0){
			//El nombre de usuario ya existe
			resultado=true;
		}
	}
	return resultado;
}

//Nuevo usuario
void insertarUsuario(struct usuario r[MAXUSUARIOS], char nombre[MAX], char pass[MAX]){
	int i=0;
	bool insertado=false;
	while (i<MAXUSUARIOS && !insertado){
		if(strcmp(r[i].nombre,"")==0){
			strcpy(r[i].nombre,nombre);
			strcpy(r[i].pass,pass);
			insertado=true;
		}
		i++;
	} 
}

//Platos disponibles (guardados en carta.txt)
void mostrarCarta(){
	FILE *f = fopen("carta.txt","r");
	char * res;
	char cadena[MAX];
	int j;
	
	if (f==NULL)
	{
		perror ("Error al abrir carta.txt");
	}
	else{
		j=-1;
		do{
			j=j+1;
        	res = fgets(cadena,MAX,f);
        	if(res!=NULL){
				printf(cadena);
			}
        }while (res!=NULL);
       
		fclose(f);
	}
	printf("\n\n");
}

//Mesas ocupadas y mesas libres
void mostrarEstado(struct mesa r[MAXMESAS]){
	int i;
	int cont1=0, cont2=0;
	for(i=0;i<MAXMESAS;i++){
		if(r[i].libre==1){
			cont1=cont1+1;
		}
		else{
			cont2=cont2+1;
		}
	}
	printf("Hay %i mesas libres y %i mesas ocupadas\n",cont1, cont2);
}

//Numero de reservas en sala
int numSala(struct mesa r[MAXMESAS]){
	int i;
	int resultado=0;
	for(i=0;i<MAXMESAS;i++){
		if(r[i].sala==1){
			resultado=resultado+1;
		}
	}
	return resultado;
}

//Número de reservas en terraza
int numTerraza(struct mesa r[MAXMESAS]){
	int i;
	int resultado=0;
	for(i=0;i<MAXMESAS;i++){
		if(r[i].sala==2){
			resultado=resultado+1;
		}
	}
	return resultado;
}

//Elimina la reserva deseada
void eliminarReserva(struct mesa r[MAXMESAS],char nombre[MAX]){
	int i;
	bool eliminado=false;
	for(i=0;i<MAXMESAS;i++){
		if(strcmp(r[i].nombre,nombre)==0){
			strcpy(r[i].nombre,"");
			r[i].sala=0;
			r[i].libre=1;
			eliminado=true;
		}
	}
	if(eliminado){
		printf("Se ha eliminado la reserva\n");
	}
	else{
		printf("No se ha encontrado reserva a ese nombre\n");
	}
}

//Guarda al fichero restaurante.txt el estado de las mesas del mismo
void guardarEstadoRestaurante(struct mesa r[MAXMESAS]){
	int i;
	FILE* f;
    f = fopen("restaurante.txt", "w");
    for(i=0;i<MAXMESAS;i++){
    	if(r[i].sala!=0){
			fprintf(f,"%d %s",r[i].sala, r[i].nombre);
		}
	}
    fclose(f);
    printf("Estado del restaurante guardadado\n");
}

//Guarda al fichero registro.txt todos los usuarios registrados
void guardarUsuariosRegistrados(struct usuario r[MAXUSUARIOS]){
	int i;
	FILE* f;
	f = fopen("registros.txt", "w");
    for(i=0;i<MAXUSUARIOS;i++){
    	
		fprintf(f,"%s %s\n",r[i].nombre, r[i].pass);
	}
	
	fclose(f);
	printf("Registro de usuarios registrados actualizado\n");
}
