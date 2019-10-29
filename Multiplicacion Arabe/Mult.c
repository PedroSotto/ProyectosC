#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define cls() system("cls");

int cuenta(int vector[], int num);
int cuenta2(int vector2[], int num1);
void textcolor(int color);

int main() {
	int num1, num2, x=0, y=0, i=0, h=0;
	long long int resultado;
	int vector1[10], vector2[10];
	textcolor(3);
	printf("\t\tMultiplicacion Arabe\n\n< ");textcolor(15);
	scanf("%d", &num1);
	textcolor(3);
	printf("< ");
	textcolor(15);
	scanf("%d", &num2);
	x = cuenta(vector1, num1); //llamo a la funcion cuenta con num1
	y = cuenta2(vector2, num2); //llamo a la funcion cuenta con num2
	//Muestro Los datos del vector1 y vector2
	cls();
	printf("\t\tMultiplicacion Arabe\n\n");
	printf("\t> ");
	for(i=x-1;i>=0;i--){
		printf("%d",vector1[i]);
	}
	textcolor(11);printf("\n\tX\n\t");textcolor(15);printf("> ");
	for(i=0;i<y;i++){
		printf("%d",vector2[i]);
	}
	int a=y;//variable usada para comparar con el numero de iteraciones de la var(control)
	x *= 2;	y *= 2;//Duplica la cantidad de digitos decada numero
	int matriz[x][y]; //declaro la matriz de x(cantida de digitos_num1) * y(cantida de digitos_num2)
	for(i=0;i<x;i++){for(h=0;h<y;h++){matriz[i][h] = 0;}}//Reseteo la matriz con 0 para no tener valores basura
	num2=0;
	num1=0;	
	int control=0;//variable de control para el amento de los indices de vector1[]y vector2[]
/*---------------------------RELLENA LA MATRIZ----------------------------------------------*/
	for(i=0;i<x;i++){ 
		for(h=0;h<y;h++){
			if(i%2!=0 && h%2==0){//toma el primer digito de el producto de los vectore(num1,num2)
				matriz[i][h] = (vector1[num1]*vector2[num2])/10;
				h++;
				control++;
				num2++;	
			}else if(i%2==0 && h%2!=0){ //toma el modulo de el producto de la multiplicacion
				matriz[i][h] = (vector1[num1]*vector2[num2])%10;
				h++;
				control++;
				num2++;
			}
			if(control==a && i%2==0){
				control=0;
				num2=0;
			}else if(control==a && i%2!=0){	num1++;	}
		}
	}
	
/*-------------------Muestra y recorre la matriz la matriz LLena------------------------*/
	printf("\n\n\n\n");
	for(i=0;i<x;i++){
		printf("\t");
		for(h=0;h<y;h++){
			if((h%2==0 && matriz[i][h]==0 && i%2==0) ||(h%2!=0 && matriz[i][h]==0 && i%2!=0)){ 
			textcolor(8);	printf("[]");
			}else{
				textcolor(11);
				printf("[%d]",matriz[i][h]);
			}		
			if(h%2!=0){	printf("");	}
		}
		printf("\n\n");
	}
/*<------------------------Hace el rrecorrido para la suma de las diagonales--------->*/
	x=x/2;
	y=y/2;
	int suma[x+y], parametro=0;
	//reseteo var_suma[] para prevenir errores por basura almacenada en la Ram
	for(i=0;i<x+y;i++)suma[i]=0;
/*------------------------------------------------------------------------------------------------------
							RECORRE MATRIZ Y SUMA LAS DIAGONALES
------------------------------------------------------------------------------------------------------*/
	num1=0;							//PART1
	control=(y*2)-1; // 3
		while(num1<y){//0<3 true 1<3 2<3 //2<3 false
			for(i=0,h=control;h<(y*2) && i<x*2;i++,h++){ // 
				suma[parametro] += matriz[i][h];
			}
				control-=2;
				num1++;
				parametro++;
		}//fin while 1
	printf("\n");
/*---------------------Segundos While,s --------------------PART2--*/
		control=1;
		num1 = 0;
		while(num1<x){ // 5
			for(i=control,h=0; i<(x*2) && h<y*2 ;i++,h++){ //I=1 H=0 i<6 o h<6 i++ h++  
				suma[parametro] += matriz[i][h];
			} 
		printf("\n");
		control+=2;
		num1++;
		parametro++;
		}
/*-------------------->Bucle que se encarga de ordenar los datos dentro de suma[]<--------------------*/
	for(i=0;i<=x+y;i++){//0 14
		
			if(suma[i]>9 ){//14>9
			suma[i+1] += suma[i]/10;//10+1=11
			suma[i] = suma[i]%10;
			}	
	}
	num1=x+y-1;
	printf("Resultado:\t");
	resultado=0;
	for(i=num1;i>=0;i--){
		resultado = resultado*10 + suma[i];
	}
	textcolor(27);
	printf("%lld",resultado);
	textcolor(000);
	printf("\n");	
	system("pause>nul");
	return 0;
}

/*<-------------------Funciones Utilizadas-------------------------->*/

/*	Funcion para cortar los numero, guardarlos en vectores
	y contar la cantida de digitos de cada numero, para posteriormente 
	declarar las dimenciones de la Matriz.
*/
int cuenta(int vector[], int num){ 
	int div=1, i=0;
	do{ 
		vector[i] = num%10; 
		num = num/10; 
		i++;
	}while(num);
	return i;
}

int cuenta2(int vector2[], int num1){ 
	int  i=0, result;
	int temp=0;
	temp = num1;
	while(temp>0){
		temp/=10;
		i++;
	}
	result = i;
	i-=1;
	while(num1>0){
		vector2[i]=num1%10,
		num1/=10;
		i--;
	}
	return result;
}
/*
	Funcion Para Proporcionar el color al texto.
*/
void textcolor(int color){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(console, &csbi);
	SetConsoleTextAttribute(console, (csbi.wAttributes & 0xf0) | color);
}
