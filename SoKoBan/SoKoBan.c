#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
/*	Name: Pedro Soto
	Author: Pedro Soto
	Date: 09/10/19 11:18
	Description: Proyecto III Parcial SOKOBAN
	Seccion 09 */
int nivel=1;
int a=0;
/*-----------DA LA BIENVENIDA --------------------- */
int Bienvenido();
void mostrar_str();
void reseteo();
void Animacion();
void who();
//Procesan y cargan los mapas para comenzar
void cargar_mapa1();
void cargar_mapa2();
void cargar_mapa3();
void imprime_mapa();
//____Valida las teclas presionadas y mas_________
int procesar_tecla(int *i,int *j,char *key,int *suma,int *Trampa,int kill,int *mov);
int IF_win();
void rellena_tres();
int trancado();
int cuantas_cajas_quedan();
/*------------_FUNCIONES_SECUNDARIAS_------*/
void gotoxy(int x, int y);
void textcolor(int color);
void setCursorVisible(BOOL visible);
void textbgcolor(WORD textcolor, WORD bgcolor);
//----------------------------------------------
int mapas[30][30];
typedef struct{
	int x;
	int y;
}jugador; 
jugador posicion;
/*     Struct Movimiento,nombre, X cvada nivel*/
struct jugador{
	char nombre[10];
	int movimientos;
};
struct jugador nivel1;

struct jugador nivel2;

struct jugador nivel3;
//--------------------
int main(){
	int i=0,j=0,iteraciones,reiniciar=0,level_follow=0,kill=0,desplazado=0,fin=0;
	char key;
	if(a<3){
	system("MODE 120,35");
	Animacion();
	reseteo();
	system("MODE 100,25");
	Bienvenido();
	}

	/*Verifico el Nuvel*/
	system("cls");
	if(nivel==1)cargar_mapa1();
	if(nivel==2)cargar_mapa2();
	if(nivel==3)cargar_mapa3();
	//_________________________
	i =	posicion.x;
	j = posicion.y;
	setCursorVisible(0);
	imprime_mapa();
	//--------------------------
	who();
	while(nivel<4 && reiniciar!=2){
		imprime_mapa();
		while(reiniciar==0 && level_follow==0){
			gotoxy(50,5);
			textcolor(11);	printf("Cajas Por Almacenar: ");	textcolor(15);	printf("%d ",cuantas_cajas_quedan());
			gotoxy(50,8);
			textcolor(11);		printf("Movimientos  "); 	textcolor(15);		printf("%d",desplazado);
			if(desplazado>20){	fin = trancado();	}
			if(fin>4){
			gotoxy(30,20);	textcolor(12);	printf("GAME OVER presione 'z' para regresar");
			}
			
			if( kbhit() ){
				level_follow = IF_win();
				key = getch();//Capturo la Tecla
				reiniciar = procesar_tecla(&i,&j,&key,&iteraciones,&level_follow,kill,&desplazado);//llamo procesar tecla y le paso las coordenadas de donde estoy
				imprime_mapa();
				rellena_tres();
				
			}//fin Kbhit;
		}//fin del bucle infinito;
		if(nivel==1){
			nivel1.movimientos = desplazado;
			desplazado=0;
		}
		if(nivel==2){
			nivel2.movimientos = desplazado;
			desplazado=0;
			strcpy(nivel2.nombre,nivel1.nombre);
		}
		if(nivel==3){
			nivel3.movimientos = desplazado;
			desplazado=0;
			strcpy(nivel3.nombre,nivel2.nombre);
		}
		if(reiniciar>0 && reiniciar<2){
			if(nivel==1)cargar_mapa1();
			if(nivel==2)cargar_mapa2();
			if(nivel==3)cargar_mapa3();
			i =	posicion.x;
			j = posicion.y;
			reiniciar=0;
			desplazado=0;
		}
		if(level_follow>0){
			level_follow=0;
			nivel+=1;
			if(nivel==1)cargar_mapa1();
			if(nivel==2)cargar_mapa2();
			if(nivel==3)cargar_mapa3();
			i =	posicion.x;
			j = posicion.y;
		}
		if(reiniciar==3){
		break;
		Bienvenido();
		a=5;
		return main();
		}
		fin=0;
		system("CLS");
		who();
	}
	if(reiniciar==3){
		
		Bienvenido();
		a=5;
		return main();
	}
	system("cls && f0");
	printf("\n\t\t\tEnhorabuena Has Ganado");
	mostrar_str();
	system("pause>nul");
	return 0;
}
void who(){
	gotoxy(50,3);
	textcolor(11);
	printf("%s",nivel1.nombre);
	gotoxy(60,3);
	textbgcolor(15,3);
	printf("%c",94);
	textbgcolor(15,11);
	gotoxy(61,3);
	printf("%c",94);
	textbgcolor(15,0);

}


int Bienvenido(){

	int tecla=0;
	system("CLS");
	textcolor(15);gotoxy(30,0); printf("Bienvenido a Sokoban");
	textcolor(14);printf("\n\n\n\t\t\t1 > > ");	textcolor(15);	printf("\tJugar");
	textcolor(14);printf("\n\t\t\t2 > > ");				textcolor(15);	printf("\tEstadisticas");
	textcolor(14);printf("\n\t\t\t3 > > ");	textcolor(15);	printf("\tSalir");
	textcolor(14); printf("\n\t< <   "); 
	scanf("%d",&tecla);
	if(tecla==1){
	system("cls");
	printf("\n\t\t\tIngrese Nombre del jugador: \t");
	fflush(stdin);
	fgets(nivel1.nombre,50,stdin);
	system("cls");
	gotoxy(30,2);
	textcolor(11);
	printf(":: CONTROLES ::");
	gotoxy(30,6); textcolor(15); printf("<<");   textcolor(11); printf(" w ");	textcolor(15); printf(">> Para moverse hacia Arriba");
	gotoxy(30,7); textcolor(15); printf("<<");   textcolor(11); printf(" s ");	textcolor(15); printf(">> Para moverse hacia Abajo");
	gotoxy(30,8); textcolor(15); printf("<<");   textcolor(11); printf(" a ");	textcolor(15); printf(">> Para moverse hacia la Izquierda");
	gotoxy(30,9); textcolor(15); printf("<<");   textcolor(11); printf(" d ");	textcolor(15); printf(">> Para moverse hacia la Derecha");
	gotoxy(30,10); textcolor(15); printf("<<");   textcolor(11); printf(" r ");	textcolor(15); printf(">> Para Reiniciar Nivel");
	
	system("pause>nul");
	return 0;
	}
	if(tecla==2){
		system("cls");
		mostrar_str();
		system("pause>nul");
		system("cls");
		Bienvenido();
	}
	if(tecla==3){
		exit(0);
	}
	if(tecla>3){
		Bienvenido();
	}
	if(tecla<0){
		Bienvenido();
	}
	return 0;
}


void imprime_mapa(){
	int i=0,j=0;
	int max_fil,max_col;
	if(nivel==1){max_fil=16; max_col=22;	}
	if(nivel==2){max_fil=15; max_col=21;	}
	if(nivel==3){max_fil=18; max_col=23;	}
	gotoxy(0,0);
	for(i=0;i<max_fil;i++){
		for(j=0;j<max_col;j++){
			if(mapas[i][j]==0){printf("  ");}
			if(mapas[i][j]==1){
				textcolor(8); 
				printf("%c",219);
				textcolor(7); 
				printf("%c",219);}
			if(mapas[i][j]==7){
				//textcolor(6); 
				textbgcolor(15,6);
				printf(">");
				textbgcolor(15,14);
				//textcolor(14); 
				printf("<");
				textbgcolor(15,0);}
			if(mapas[i][j]==9){ 
				textbgcolor(15,3);
				printf("%c",94);
				textbgcolor(15,11);
				//textcolor(14); 
				printf("%c",94);
				textbgcolor(15,0);
			/*textcolor(9);
			printf("%c",219);
			textcolor(11);
			printf("%c",219);*/
			
			}
			if(mapas[i][j]==3){
				textcolor(4); 
				printf("%c", 169);
				textcolor(0); 
				printf(" ");
			}
			if(mapas[i][j]==5){
				textcolor(4);
				printf("%c", 219);
				textcolor(6);
				printf("%c", 219);
			}	
		}
		printf("\n");
	}
}
int procesar_tecla(int *i,int *j,char *key,int *suma,int *Trampa,int kill,int *mov){
	
	if((*key=='w' || *key=='W') && mapas[*i-1][*j]!=1){
				//Dezplazar caja
		if( (mapas[*i-1][*j]==7 && mapas[*i-2][*j]!=7 && mapas[*i-2][*j]!=1 ) && mapas[*i-2][*j]!=3 && mapas[*i-2][*j]!=5){
			*i-=1;
			mapas[*i][*j]=9;
			mapas[*i-1][*j]=7;
			mapas[*i+1][*j]=0;
			*mov+=1;
		}else if(   (mapas[*i-1][*j]==7 && mapas[*i-2][*j]!=7 && mapas[*i-2][*j]!=1 )  && mapas[*i-2][*j]==3&&mapas[*i-1][*j]!=1){
			//se mueve con caja en el deposito
			*i-=1;
			mapas[*i][*j]=9;
			mapas[*i-1][*j]=5;
			mapas[*i+1][*j]=0;
			*mov+=1;
		}else if( (mapas[*i-2][*j]!=1 && mapas[*i-1][*j]!=1 && mapas[*i-1][*j]==5 && mapas[*i-2][*j]!=5) && mapas[*i-2][*j]==3){
				//moverse con caja dentro* del deposito
				*i-=1;
				mapas[*i][*j]=9;
				mapas[*i-1][*j]=5;
				mapas[*i+1][*j]=0;
				*mov+=1;
		}else if(mapas[*i-1][*j]!=1 && mapas[*i-1][*j]!=7 && mapas[*i-1][*j]!=5){
			//Moverse sin caja
			*i-=1;
			mapas[*i][*j]=9;
			mapas[*i+1][*j]=0;
			*mov+=1;
		}
		posicion.x=*i;
		posicion.y=*j;
	}//fin if w
	if((*key=='s' || *key=='S') && mapas[*i+1][*j]!=1){
		
		if(   (mapas[*i+1][*j]==7 && mapas[*i+2][*j]!=7 && mapas[*i+2][*j]!=1 ) && mapas[*i+2][*j]!=3 && mapas[*i+2][*j]!=5){
			//se mueve con caja
			*i+=1;
			mapas[*i][*j]=9;
			mapas[*i+1][*j]=7;
			mapas[*i-1][*j]=0;
			*mov+=1;
		}else if(   (mapas[*i+1][*j]==7 && mapas[*i+2][*j]!=7 && mapas[*i+2][*j]!=1 ) && mapas[*i+2][*j]==3 && mapas[*i+1][*j]!=1){
			//se mueve con caja en el deposito
			*i+=1;
			mapas[*i][*j]=9;
			mapas[*i+1][*j]=5;
			mapas[*i-1][*j]=0;
			*mov+=1;
		}else if( (mapas[*i+2][*j]!=1 && mapas[*i+1][*j]!=1 && mapas[*i+1][*j]==5 && mapas[*i+2][*j]!=5) ){
				//moverse con caja dentro* del deposito
				*i+=1;
				mapas[*i][*j]=9;
				mapas[*i+1][*j]=5;
				mapas[*i-1][*j]=0;
				*mov+=1;
		}else if(mapas[*i+1][*j]!=1 && mapas[*i+1][*j]!=7 && mapas[*i+1][*j]!=5){
			//se mueve sin caja
			*i+=1;
			mapas[*i][*j]=9;
			mapas[*i-1][*j]=0;
			*mov+=1;
		}
	posicion.x=*i;
	posicion.y=*j;
	}//fin if s
	if((*key=='a' || *key=='A') && mapas[*i][*j-1]!=1){
		
		if(   (mapas[*i][*j-1]==7 && mapas[*i][*j-2]!=7 && mapas[*i][*j-2]!=1 ) && mapas[*i][*j-2]!=3 && mapas[*i][*j-2]!=5){
			//se mueve con caja
			*j-=1;
			mapas[*i][*j]=9;
			mapas[*i][*j-1]=7;
			mapas[*i][*j+1]=0;
			*mov+=1;
			
		}else  if( mapas[*i][*j-2]!=5 && mapas[*i][*j-1]!=5 && (mapas[*i][*j-1]==7 && mapas[*i][*j-2]!=7 && mapas[*i][*j-2]!=1 ) && mapas[*i][*j-2]==3 &&  mapas[*i][*j-1]!=1){
			//se mueve con caja en el deposito
			*j-=1;
			mapas[*i][*j]=9;
			mapas[*i][*j-1]=5;
			mapas[*i][*j+1]=0;
			*mov+=1;
			
		}else if( (mapas[*i][*j-2]!=1 && mapas[*i][*j-1]!=1 && mapas[*i][*j-1]==5 && mapas[*i][*j-2]!=5) && mapas[*i][*j-2]==3){
				//moverse con caja dentro* del deposito
				*j-=1;
				mapas[*i][*j]=9;
				mapas[*i][*j-1]=5;
				mapas[*i][*j+1]=0;
				*mov+=1;
		}else if(mapas[*i][*j-1]!=1 && mapas[*i][*j-1]!=7 && mapas[*i][*j-1]!=5){
			//se mueve sin caja
			*j-=1;
			mapas[*i][*j]=9;
			mapas[*i][*j+1]=0;
			*mov+=1;
		}
		posicion.x=*i;
		posicion.y=*j;
		
	}//fin if a
	
	if( (*key=='d' || *key=='D') && mapas[*i][*j+1]!=1){
		
		if(   (mapas[*i][*j+1]==7 && mapas[*i][*j+2]!=7 && mapas[*i][*j+2]!=1 ) && mapas[*i][*j+2]!=3 && mapas[*i][*j+2]!=5){
				//moverse con caja
				*j+=1;
				mapas[*i][*j]=9;
				mapas[*i][*j+1]=7;
				mapas[*i][*j-1]=0;
				*mov+=1;
		}else if(   (mapas[*i][*j+1]==7 && mapas[*i][*j+2]!=7 && mapas[*i][*j+2]!=1 )  && mapas[*i][*j+2]==3 && mapas[*i][*j+1]!=5 &&  mapas[*i][*j+1]!=1 && mapas[*i][*j+2]!=5 ) {
				//moverse con caja en el deposito
				*j+=1;
				mapas[*i][*j]=9;
				mapas[*i][*j+1]=5;
				mapas[*i][*j-1]=0;
				*mov+=1;
		
		}else if( (mapas[*i][*j+2]!=1 && mapas[*i][*j+1]!=1 && mapas[*i][*j+1]==5 && mapas[*i][*j+2]!=5) && mapas[*i][*j+2]==3){
				//moverse con caja dentro* del deposito
				*j+=1;
				mapas[*i][*j]=9;
				mapas[*i][*j+1]=5;
				mapas[*i][*j-1]=0;
				*mov+=1;
				
		}else if(mapas[*i][*j+1]!=1 && mapas[*i][*j+1]!=7 && mapas[*i][*j+1]!=5){//Establecer condicioenes de pare en 3
			//moverse sin caja
			*j+=1;
			mapas[*i][*j]=9;
			mapas[*i][*j-1]=0;
			*mov+=1;
		}
		posicion.x=*i;
		posicion.y=*j;
	}//fin de if 'd'
	if(*key=='r' || *key=='R'){
		return 1;
	}
	if(*key=='*'){
		*Trampa=1;
	}
	if(*key=='z' || *key=='Z'){
		return 3;
	}
	return 0;
}
//--------------------------Verifica los 3------------------
void rellena_tres(){
	int i=0,j=0,max=0;
	if(nivel==1){///
		for(i=9;i<12;i++){
			for(j=18;j<20;j++){
				if(mapas[i][j]==0){
					mapas[i][j]=3;
				}
			}
		}
	}
	if(nivel==2){
		for(i=8;i<11;i++){
			for(j=3;j<7;j++){
				if(mapas[i][j]==0){
					mapas[i][j]=3;
				}
			}
		}
		
	}
	if(nivel==3){
		for(i=3;i<8;i++){
			for(j=16;j<20;j++){
				if(mapas[i][j]==0){
					mapas[i][j]=3;
				}
			}
		}
		
	}
}
/*					COMPRUEBA SI GANA 						*/
int IF_win(){
	int i=0,j=0;
	int max_fil,max_col,contador_cajas=0;
	if(nivel==1){max_fil=16; max_col=22;	}
	if(nivel==2){max_fil=15; max_col=21;	}
	if(nivel==3){max_fil=18; max_col=23;	}
	for(i=0;i<max_fil;i++){
		for(j=0;j<max_col;j++){
			if(mapas[i][j]==5)				
			contador_cajas++;
			}
	}
	if(nivel==1 && contador_cajas==6){return 1;}
	if(nivel==2 && contador_cajas==11){return 1;}
	if(nivel==3 && contador_cajas==20){return 1;}
	return 0;
}

/*resetea los valores de struct jugador*/

void reseteo(){
	char cadena[5] = "x-x-x";
	int num=0;
	nivel1.movimientos=num;
	nivel2.movimientos=num;
	nivel3.movimientos=num;
	strcpy(nivel1.nombre, cadena);
	strcpy(nivel2.nombre, cadena);
	strcpy(nivel3.nombre, cadena);
}
void mostrar_str(){
	gotoxy(0,0);
	system("CLS");
	gotoxy(40,3);
	textcolor(11);
	printf(" |     Estadisticas    |\n\n");
	gotoxy(35,5);
	textcolor(15);
	printf("%i\t%s\n",nivel1.movimientos,nivel1.nombre );
	gotoxy(35,7);
	textcolor(15);
	printf("%i\t%s\n",nivel2.movimientos ,nivel2.nombre );
	gotoxy(35,9);
	textcolor(15);
	printf("%i\t%s\n", nivel3.movimientos, nivel3.nombre);
	gotoxy(0,0);
	textcolor(15);
}

/*_____________________________________________________*/
/*____________Revisa el Numero de cajas que quedan_____*/
/*_____________________________________________________*/
int cuantas_cajas_quedan(){
	int i=0,j=0,cuenta=0,max_fil=0,max_col=0;
	if(nivel==1){max_fil=16; max_col=22;	}
	if(nivel==2){max_fil=15; max_col=21;	}
	if(nivel==3){max_fil=18; max_col=23;	}
	for(i=4;i<max_fil-2;i++){
		for(j=2;j<max_col-2;j++){
			if(mapas[i][j]==7){
				cuenta++;
			}
		}
	}
	return cuenta;	
}
int trancado(){
	int i=0,j=0;
	for(i=0;i<20;i++){
		for(j=0;j<24;j++){
			if((mapas[i][j]==7) && (mapas[i][j-1]==1 && mapas[i+1][j]==1  )){	return 10;}
			if((mapas[i][j]==7) && (mapas[i][j+1]==1 && mapas[i-1][j]==1  )){	return 10;}
			if((mapas[i][j]==7) && (mapas[i][j+1]==1 && mapas[i+1][j]==1  )){	return 10;}
			if((mapas[i][j]==7) && (mapas[i][j-1]==1 && mapas[i-1][j]==1  )){	return 10;}
			//i *1
			if(mapas[i][j]==7 &&  mapas[i+1][j]==7 && mapas[i+1][j-1]==1 &&  mapas[i][j-1]==1 ){	return 10;}
			if(mapas[i][j]==7 &&  mapas[i+1][j]==7 && mapas[i+1][j+1]==1 &&  mapas[i][j+1]==1 ){	return 10;}
			///i *2
			if(mapas[i][j]==7 &&  mapas[i-1][j]==7 && mapas[i-1][j-1]==1 && mapas[i][j-1]==1 ){	return 10;}
			if(mapas[i][j]==7 &&  mapas[i-1][j]==7 && mapas[i-1][j+1]==1 && mapas[i][j+1]==1 ){	return 10;}
			
			//j *1
			if(mapas[i][j]==7 &&  mapas[i][j+1]==7 && mapas[i-1][j+1]==1 &&  mapas[i-1][j]==1 ){	return 10;}
			if(mapas[i][j]==7 &&  mapas[i][j+1]==7 && mapas[i+1][j+1]==1 &&  mapas[i+1][j]==1 ){	return 10;}
			//j *2
			if(mapas[i][j]==7 &&  mapas[i][j-1]==7 && mapas[i-1][j-1]==1 && mapas[i-1][j]==1 ){	return 10;}
			if(mapas[i][j]==7 &&  mapas[i][j-1]==7 && mapas[i-1][j-1]==1 && mapas[i+1][j]==1 ){	return 10;}	
	}
}
return 0;
}
/*-----------------------------FUNCIONES SECUNDARIAS--------------------------------------------------------*/

void textcolor(int color){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &csbi);
	SetConsoleTextAttribute(console, (csbi.wAttributes & 0xf0) | color);
}
void textbgcolor(WORD textcolor, WORD bgcolor){
    WORD color = (bgcolor & 0xF) << 4 | (textcolor & 0xF);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, color);
}
void gotoxy(int x, int y){
    HANDLE hConsole;
    COORD dwPos;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hConsole, dwPos);
}
void setCursorVisible(BOOL visible){
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = visible;
	cursor.dwSize = 20;

	SetConsoleCursorInfo(console, &cursor);
}
/*-------------------------------------------------*/
/*---------------MAPAS || NIVELES------------------*/
/*_________________________________________________*/

void Animacion(){
	int sokoban[9][46] = {
		{0,0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0},
		{0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1,0},
		{0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,0},
		{0,0,1,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,0,1,1,0,0,1,0,1,0,0,1,0},
		{0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,1,0},
		{0,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,0,0,1,0,0,1,0,1,0},
		{0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,0},
		{0,0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

	};
	int caja[10][14] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,2,2,2,2,2,2,2,2},
		{1,1,1,1,1,1,2,2,2,2,2,2,2,2},
		{1,1,1,5,5,5,2,5,5,5,2,2,2,2},
		{1,1,1,1,1,5,2,2,2,5,2,2,2,2},
		{1,1,1,1,1,1,2,2,2,2,2,2,2,2},
		{1,1,1,2,5,5,5,5,2,2,2,2,2,2},
		{1,1,1,1,1,1,2,5,2,2,2,2,2,2},
		{1,1,1,1,1,1,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	setCursorVisible(0);
	int i=0,j=0,h=0,xx=0,yy=0,cc=2,color;
	system("CLS");
	yy=3;xx=20;
	//caja
	yy=10;	xx=10;	h=0;
	int ca=0;	color=14;
	int ax=2,color2=6;
	gotoxy(xx,yy);
	ca=12;
	while(h<4){
		system("CLS");
		if(h<4){
			if(h>1){ca=14;	}
			gotoxy(20,ax);
		for(i=0;i<9;i++){
			for(j=0;j<46;j++){
				if(sokoban[i][j]==1){
				textcolor(ca);
				printf("%c",219);
				}
				if(sokoban[i][j]==0){
				textcolor(0);
				printf(" ");
				}
			}
			gotoxy(20,++ax);
			}
			ax=22;
		}
		if(h==1){	color=1;	color2=3;}
		if(h==2){	color=14;	color2=6;}
		if(h==3){	color=11;	color2=9;}
		////////////////////////////////
		cc+=10;
		gotoxy(xx,yy);
		for(i=0;i<10;i++){
			for(j=0;j<14;j++){
				if(caja[i][j]==5){
				textcolor(15);
				printf("%c",219);
				}
				if(caja[i][j]==2){
				textcolor(color2);
				printf("%c",219);
				}
				if(caja[i][j]==1){
				textcolor(color);
				printf("%c",219);
				}
				if(caja[i][j]==0){
				textcolor(0);
				printf(" ");
				}
			}
			gotoxy(xx,++yy);
		
		}
		///////////////////////////
		Sleep(800);
		yy=10;	xx=10;	xx+=cc;	h++;
	}
	yy+=3;
	system("CLS");
	gotoxy(20,yy);
	for(i=0;i<10;i++){
			for(j=0;j<14;j++){
				if(caja[i][j]==5){
				textcolor(15);
				printf("%c",219);
				}
				if(caja[i][j]==2){
				textcolor(11);
				printf("%c",219);
				}
				if(caja[i][j]==1){
				textcolor(3);
				printf("%c",219);
				}
				if(caja[i][j]==0){
				textcolor(0);
				printf(" ");
				}
				Sleep(3);
			}
			gotoxy(xx,++yy);
		
		}
		//94

	int ch=178;
	h=0;
	cc=14;
	while(h<3){
		yy=3;
		xx=10;
		if(h==1) {
			cc=6;
			ch=178;
		}
		if(h==2){
			cc=14;
			ch=219;
		}
		gotoxy(xx,yy);
		for(i=0;i<9;i++){
			for(j=0;j<46;j++){
				if(sokoban[i][j]==1){
				textcolor(cc);
				printf("%c%c",ch,ch);
				}
				if(sokoban[i][j]==0){
				textcolor(0);
				printf("  ");
				}
				
			}
			gotoxy(xx,++yy);
			Sleep(100);
		}
		h++;
	}
	gotoxy(5,20);
	textbgcolor(0,15);
	printf("CREATE BY PEDRO SOTO");
	Sleep(500);
	gotoxy(5,20);
	textbgcolor(15,0);
	printf("CREATE BY PEDRO SOTO");
	Sleep(600);
	textbgcolor(15,0);
	gotoxy(5,20);
	textbgcolor(0,15);
	printf("CREATE BY PEDRO SOTO");
	textbgcolor(15,0);
	Sleep(2000);
}


void cargar_mapa1(){
	int mapa1[16][22] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,7,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,0,0,7,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,7,0,7,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,0,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,0},
{0,0,1,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,3,3,1,0},
{0,0,1,0,7,0,0,7,0,0,0,0,0,0,0,0,0,0,3,3,1,0},
{0,0,1,1,1,1,1,0,1,1,1,0,1,9,1,1,0,0,3,3,1,0},
{0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
	int i=0,j=0;
	for(i=0;i<16;i++){
		for(j=0;j<22;j++){
			mapas[i][j] = mapa1[i][j];
		}
	}
	posicion.x=11;
	posicion.y=13;
}

void cargar_mapa2(){//15X21
	int mapa2[15][21]={
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 9, 1, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 1, 7, 0, 1, 1, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 0, 0, 7, 1, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 7, 0, 7, 0, 1, 0, 0, 0}, 
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 7, 0, 1, 0, 1, 1, 1, 0}, 
		{0, 0, 1, 3, 3, 3, 3, 0, 0, 1, 1, 0, 7, 0, 0, 7, 0, 0, 1, 0}, 
		{0, 0, 1, 1, 3, 3, 3, 0, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0, 1, 0}, 
		{0, 0, 1, 3, 3, 3, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int i=0,j=0;
	for(i=0;i<30;i++){
		for(j=0;j<30;j++){
			mapas[i][j] = 0;
		}
	}
	for(i=0;i<15;i++){
		for(j=0;j<21;j++){
			mapas[i][j] = mapa2[i][j];
		}
	}
	i =	posicion.x=3;
	j = posicion.y=16;
}

void cargar_mapa3(){
	int mapa3[18][23]={
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,3,3,3,3,1,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,3,3,3,1,0},
		{0,0,1,0,0,0,0,1,0,0,7,0,7,0,0,0,3,3,3,3,1,0},
		{0,0,1,0,7,7,7,1,7,0,0,7,0,1,0,0,3,3,3,3,1,0},
		{0,0,1,0,0,7,0,0,0,0,0,7,0,1,0,0,3,3,3,3,1,0},
		{0,0,1,0,7,7,0,1,7,0,7,0,7,1,1,1,1,1,1,1,1,0},
		{0,0,1,0,0,7,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,7,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,7,7,1,7,7,0,0,9,1,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}	};
		int i=0,j=0;
	for(i=0;i<30;i++){
		for(j=0;j<30;j++){
			mapas[i][j] = 0;
		}
	}
	for(i=0;i<18;i++){
		for(j=0;j<23;j++){
			mapas[i][j] = mapa3[i][j];
		}
	}
	i =	posicion.x=13;
	j = posicion.y=12;
	
}
