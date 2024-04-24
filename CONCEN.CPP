#include <iostream.h> //cout, cin
#include <conio.h>    //getch(), clrscr()
#include <stdlib.h>   //random y randomize
#include <dos.h>      //delay()

void limpiarPreg(char matPreg[10][10], int tam);
void limpiarRes(int matRes[10][10], int tam);
void cargarMat(char matPreg[10][10], int tam);
void mostrarPreg(char matPreg[10][10], int tam, char c);
void mostrarPreg2(char matPreg[10][10], char num, int tam,
		  int posx, int posy);
void mostrarRes(int matRes[10][10], int tam, int dif);
void jugarConcentrece(char matPreg[10][10], int matRes[10][10], int mR[10][10],
		      int tam);
char verificar(char matPreg[10][10], int matRes[10][10], int mR[10][10],
	       int num, int tam);
void mostrarRes(char matPreg[10][10], int tam, int posX, int posY);
void intercambiar(int matRes[10][10], int matPreg[10][10], int posX, int posY);

int matRes[10][10], mR[10][10];  //Matris de respuestas.
char matPreg[10][10];           //Cargados las letras o simbolos
int i, j, tam;
int posX=0, posY=0;    //posiciones que encontramos
int posx[2], posy[2];  //guardamos las posiciones encontradas
int px=0, py=0;        //indicie de los vectores

void main()
{
   int tam;
   do {
	 clrscr();
	 cout<<"Digite el Tama¤o del Tablero: ";
	 cin>>tam;   //Tama¤o de la matris para jugar
	  if( ((tam*tam)%2 == 0) && (tam >= 4) )
	  {
	     clrscr();
	     limpiarPreg(matPreg, tam);//pone en NULL las posiciones de la matris
	     cargarMat(matPreg, tam);//llenamos la matris con los simbolos
	     mostrarPreg(matPreg, tam, NULL);//mostramos la matris
	     delay(tam*700); //pausa.

	     limpiarRes(matRes, tam);//ponemos en cero las posiciones de la matris de los resultados
	     limpiarRes(mR, tam);//ponemos en cero la matris auxiliar
	     jugarConcentrece(matPreg, matRes, mR, tam); //jugamos
	  }
	  else
	     cout<<"\nEl tama¤o debe ser minimo de [ 4 ] y par\n";
	getch();
   }while(tam < 4);
}
//Ponemos en NULL la matris de simbolos
void limpiarPreg(char matPreg[10][10], int tam)
{
   for(i=0; i<tam; i++)
   {
      for(j=0; j<tam; j++)
	 matPreg[i][j] = NULL; //ponemos en NULL
   }
}
//Ponemos en cero matris de respuesta.
void limpiarRes(int matRes[10][10], int tam)
{
   for(i=0; i<tam; i++)
   {
      for(j=0; j<tam; j++)
	 matRes[i][j] = 0; //ponemos en 0
   }
}
//Cargamos la matris con los simbolos.
void cargarMat(char matPreg[10][10], int tam)
{
   int a, b;

   randomize();
    for(a=1; a<=(tam*tam)/2; a++)//n-pares depende el tama¤o.
    {
	for(b=0; b<2; )    //Solo dos veces que son las parejas
	{
	   i = random(tam);  //busca una posicion cualquiera para la fila
	   j = random(tam);  //busca una posicion cualquiera para la columna.

	   if(matPreg[i][j] == NULL)  //Si es diferente de NULL ingresa
	   {
	      matPreg[i][j] = a+64; //65 - A
	      b++; //incrementamos si ingresa.
	   }
	}
    }
}
//mostramos la matris de simbolos
void mostrarPreg(char matPreg[10][10], int tam, char c)
{
   int x=5, y=5;
    for(i=0; i<tam; i++)
    {
       x = 5;
       for(j=0; j<tam; j++)
       {
	  if(matPreg[i][j] != c)
	  {
	     gotoxy(x,y);
	     cout<<matPreg[i][j];   //
	  }
	  x += 5;
       }
       y += 1;
    }
}
//mostramos solo el simbolo de una posicion dada.
void mostrarPreg2(char matPreg[10][10], char num, int tam,
		  int posx, int posy)
{
   int x=5, y=5;
    for(i=0; i<tam; i++)
    {
       x = 5;
       for(j=0; j<tam; j++)
       {
	  if(matPreg[i][j] == num)//si es igual al dato mandado
	  {
	     if( (posx == i) && (posy == j) ) //y si esta el las posiciones dadas
	     {
		gotoxy(x,y);
		cout<<"  ";
		gotoxy(x,y);
		cout<<matPreg[i][j]; //
		i=tam;
		j=tam;
	     }
	  }
	  x += 5;
       }
       y += 1;
    }
}
//mostramos la matris de respuesta
void mostrarRes(int matRes[10][10], int tam, int dif)
{
   int x=5, y=5;
    for(i=0; i<tam; i++)
    {
       x = 5;
       for(j=0; j<tam; j++)
       {
	  if(matRes[i][j] != dif)  //si es diferente de lo que mandamos
				   //cuando no son iguales.
	  {
	     gotoxy(x,y);
	     cout<<matRes[i][j];
	  }
	  else  {     //sino imprime [] para saber que son iguales
	     gotoxy(x,y);
	     cout<<"[]";
	  }
	  x += 5;
       }
       y += 1;
    }
}
//jugamos
void jugarConcentrece(char matPreg[10][10], int matRes[10][10],
		      int mR[10][10],int tam)
{
   char num1, num2;  //donde almacenamos las figuras escogidas
   int n=1, sw=0, jug=0;
   int op; //numero de la matris respuesta
   int jugador=1, jd=1;  //jugadores
   int puntjug1=0, puntjug2=0; //puntaje de los jugadores
   int cent=0;  //controla el fin del juego.

    for(i=0; i<tam; i++)   //Cargan los numeros en la matris 1, 2, 3,...
    {
       for(j=0; j<tam; j++)
       {
	  matRes[i][j] = n; //cargamos
	  n++;
       }
    }
    do {
	 if(sw == 0)   //si es la primera ves
	 {
	    clrscr();
	    mostrarRes(matRes, tam, 0);
	    sw = 1;
	 }
	 gotoxy(10,14); cout<<"\nJUEGO CONCENTRECE ";
	 gotoxy(10,15); cout<<"\nPuntaje del Jugador 1: "<<puntjug1;
	 gotoxy(10,16); cout<<"\nPuntaje del Jugador 2: "<<puntjug2;
	 gotoxy(10,18); cout<<"\nJugador "<<jd;
	 gotoxy(10,19); cout<<"\nEscoja los numeros: (0 para Salir del Juego):";
	 gotoxy(48,20); cout<<"   ";
	 gotoxy(48,20); cin>>op;
	 if(op==0){
	   cout<<"\nFINALIZANDO JUEGO CONCENTRECE ";
	   delay(4000);
	   exit(0);
	 }

	  if(sw == 1)
	  {
	     //ingresamos lo que devuelve verificar.
	     num1 = verificar(matPreg, matRes, mR, op, tam);
	     sw = 2; //pasamos a la 2da jugada
	     jug++;  //incrementamos la jugada
	     //mostramos lo que se a jugado
	     mostrarPreg2(matPreg, num1, tam, posx[0], posy[0]);
	  }
	  else if(sw == 2)
	  {
	     num2 = verificar(matPreg, matRes, mR, op, tam);
	     sw = 1;  //pasamos a la 1ra jugada.
	     jug++;
	     mostrarPreg2(matPreg, num2, tam, posx[1], posy[1]);
	  }

	  if(num1 == num2)   //si son iguales
	  {
	     delay(2000);
	     if(jugador == 1)
	     {
		puntjug1 += 1; //incrementamos el puntaje del Jug 1
	     }
	     else if(jugador == 2)
	     {
		puntjug2 += 1; //incrementamos el puntaje del Jug 2
	     }
	     //eliminamos si son iguales
	     matRes[posx[0]][posy[0]]  = 0;
	     matRes[posx[1]][posy[1]]  = 0;
	     sw=0; //ponemos a mostrar como al principio.
	     jug=0;//limpiamos las jugadas
	     px=0; //limpiamos indices de las posiciones del vector posx
	     py=0; //limpiamos indices de las posciones del vector posy
	  }
	  if(jug > 1)  //Si no son iguales
	  {
	     delay(2000);
	     jug=0;//limpiamos las jugadas
	     //recuperamos lo que tenian esas posiciones
	     intercambiar(mR, matRes, posx[0], posy[0]);
	     intercambiar(mR, matRes, posx[1], posy[1]);
	     sw=0;
	     px=0;
	     py=0;
	     num1=NULL;
	     num2=NULL;
	     //Si se pierde
	     if(jugador == 1) //si es el jugador 1
	     {
		jugador=2; //pasamos al jugador 2
		jd=2;
	     }
	     else
		if(jugador == 2) //si es el jugador 2
		{
		   jugador=1; //pasamos al jugador 1
		   jd=1;
		}
	  }

	 //verificamos si no hay mas jugadas en la matris
	 for(int p=0; p<tam; p++)
	 {
	    for(int q=0; q<tam; q++)
	    {
	       if(matRes[p][q] != 0)
	       {
		  q=tam;
		  p=tam;
		  cent=0;  //si hay jugadas
	       }
	       else
		  cent=1; //si no hay jugadas
	    }
	 }   //
    }while(cent != 1);

    if(puntjug1 > puntjug2)  //si el ganador es el jug 1
    {
       gotoxy(10,22);
       cout<<"El Ganador es el << Jugador 1 >> con un puntaje de: "<<puntjug1;
    }
    if(puntjug2 > puntjug1)//si el ganador es el Jug 2
    {
       gotoxy(10,22);
       cout<<"El Ganador es el << Jugador 2 >> con un puntaje de: "<<puntjug2;
    }
    if(puntjug1 == puntjug2)  //si hay empate
    {
       gotoxy(10,22);
       cout<<"Juego Empatado con puntajes de:"<<puntjug1;
    }
}
//verificamos y buscamos el elemento para saber las posicones de un numero
//dada
char verificar(char matPreg[10][10], int matRes[10][10], int mR[10][10],
	       int num, int tam)
{
   int x, y;
   char aux;
   int posX=0, posY=0;

    for(x=0; x<tam; x++)
    {
       for(y=0; y<tam; y++)
       {
	  if(num == matRes[x][y])
	  {
	     posX = x;
	     posY = y;
	     posx[px] = posX;  //guardamos la posicion X
	     posy[py] = posY;  //guardamos la posicion Y
	     x = tam; //
	     y = tam; // bloqueamos
	     px++;   //
	     py++;   // incrementamos posiciones del vector
	  }
       }
    }
   aux = matPreg[posX][posY]; //almacenamos el elemento que encontrmos en la
			      //posicion que resulto.
   intercambiar(matRes, mR, posX, posY); //copiamos el elemento de la
					 //matris resultado a la matris
					 //auxiliar
   return aux;//retornamos el elemento que encontramos
}
//copiamos.
void intercambiar(int matRes[10][10], int mR[10][10], int posX, int posY)
{
   char aux;
    mR[posX][posY] = matRes[posX][posY];
}

