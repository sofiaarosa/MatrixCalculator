	#include <stdio.h>
	#include <math.h>
	#include <windows.h>
	#include <conio.h>
	#include "conio_functions.h" /*substitution of conio.c*/
	#include <stdlib.h>
	#include <locale.h>
	#include <time.h>

	#define downArrow 80
	#define upArrow 72
	#define leftArrow 75
	#define rightArrow 77

	#define esc 27
	#define enter 13
	#define f1 59

	#define screenColumns 90
	#define horizontalCenter 45
	#define screenRows 40
	#define verticalCenter 20

	#define maxSize 10

	//function headers
	int menuSelection(int, int);
	int reprocessing();
	int mainMenu(int matrix[maxSize][maxSize]);
	void menuExecute(int matrix[maxSize][maxSize], int);
	int isSquare();
	
	int isSimetric(int matrix[maxSize][maxSize]);
	int isMagic(int matrix[maxSize][maxSize]);
	int isLatin(int matrix[maxSize][maxSize]);
	int isPermutation(int matrix[maxSize][maxSize]);
	
	
	int selectRow(int matrix[maxSize][maxSize]);
	int selectColumn(int matrix[maxSize][maxSize]);
	void swapRows(int matrix[maxSize][maxSize]);
	void swapColumns(int matrix[maxSize][maxSize]);
	void swapDiagonals(int matrix[maxSize][maxSize]);
	
	int fillMatrix(int matrix[maxSize][maxSize]);
	void readMatrix(int matrix[maxSize][maxSize]);
	void generateMatrix(int matrix[maxSize][maxSize]);
	
	void printHeader();
	void showMatrix(int matrix[maxSize][maxSize], char *);
	void showHighlightedRow(int matrix[maxSize][maxSize], int);
	void showHighlightedColumn(int matrix[maxSize][maxSize], int);
	void showGuidance(char message[100]);
	

	//global variables - only set in main function
	int rows, columns;

	int main() {
		system("mode con:cols=90 lines=40");
		SetConsoleTitle("Calculadora Trigonometrica");
		setlocale(LC_CTYPE, "Portuguese");
		srand(time(NULL));
		cursor(1);

	    int matrix[maxSize][maxSize];
		int out = 0, choice = 0;

		do{
		    printHeader();

		    do{
		    	gotoxy(1,5); printf("N?mero de colunas da matriz:");
		    	gotoxy(30,5); scanf(" %d", &columns);
		    	if(columns <= 0 || columns > maxSize){
		    		gotoxy(1,3);
		    		textcolor(4);
		    		printf("O n?mero de colunas deve ser maior que 0 e menor que 10");
		    		textcolor(0);
		    		gotoxy(30,5);printf("     ");
				}
			}while(columns <= 0 || columns > maxSize);
			gotoxy(1,3);printf("                                                                        ");
			do{
		    	gotoxy(1,6); printf("N?mero de linhas da Matriz:");
		    	gotoxy(30,6); scanf(" %d", &rows);
		    	if(rows <= 0 || rows > maxSize){
		    		gotoxy(1,3);
		    		textcolor(4);
		    		printf("O n?mero de linhas deve ser maior que 1 e menor que 10");
					textcolor(0);
					gotoxy(30,6);printf("     ");
				}
			}while(rows <= 0 || rows > maxSize);
		    gotoxy(1,3);printf("                                                                        ");

		    choice = fillMatrix(matrix);
		    while(choice >= 0){
		    	choice = mainMenu(matrix);
		    	menuExecute(matrix, choice);
			}

			out = reprocessing();
		}while(out != 2 && out != -1);

	    return 0;
	}

	void printHeader(){
		textbackground(15);
		textcolor(0);

	    system("cls");
	    int i;
	    for(i=0;i<screenColumns;i++){
		    gotoxy(i,1);
	    	textbackground(14);printf(" ");
	    }

	    gotoxy(horizontalCenter - 6,1); printf("MATRIZES EM C");
	    textbackground(15);
	}
	
	void showGuidance(char message[100]){
		gotoxy(3, 10 + rows*2); textcolor(4);
		printf("%s", message);
		textcolor(0);
	}

	void swapRows(int matrix[maxSize][maxSize]){
		int row1 = 0, row2= 0;
		int i, x, y, aux;
		do{
			showMatrix(matrix, "Selecione duas linhas distintas (esc para voltar): ");
			row1 = selectRow(matrix);
			if(row1 == -1) break;
			row2 = selectRow(matrix);
			if(row2 == -1) break;
		}while(row1==row2);

		if(row1 != -1 && row2 != -1)
			for(i=0;i<columns;i++){
				x = matrix[row1][i];
				y = matrix[row2][i];
				matrix[row2][i] = x;
				matrix[row1][i] = y;
			}
	}

	void swapColumns(int matrix[maxSize][maxSize]){
		int col1 = 0, col2= 0;
		do{
			showMatrix(matrix, "Selecione duas colunas distintas: ");
			col1 = selectColumn(matrix);
			if(col1 == -1) break;
			col2 = selectColumn(matrix);
			if(col2 == -1) break;
		}while(col1==col2);

		int i, x, y, aux;
		if(col1 != -1 && col2 != -1)
			for(i=0;i<rows;i++){
				x = matrix[i][col1];
				y = matrix[i][col2];
				matrix[i][col2] = x;
				matrix[i][col1] = y;
			}
	}

	void swapDiagonals(int matrix[maxSize][maxSize]){
		int x, y, i, j;
		for(i=0, j=rows-1;i<rows;i++, j--){
			x = matrix[i][i];
			y = matrix[i][j];
			matrix[i][i] = y;
			matrix[i][j] = x;
		}
	}

	void menuExecute(int matrix[maxSize][maxSize], int choice){
		int result;
		switch(choice){
			case 1:
				swapRows(matrix);
				break;
			case 2:
				swapColumns(matrix);
				break;
			case 3:
				swapDiagonals(matrix);
				break;
			case 4:
				result = isSimetric(matrix);
				
				showMatrix(matrix, "A matriz: ");
				gotoxy(3, 10 + rows*2);
				if(result)printf("? sim?trica");
				else printf("N?o ? sim?trica");
				gotoxy(3, 11 + rows*2);
				textcolor(4);
				printf("Pressione qualquer tecla para continuar");
				textcolor(0);
				getch();
				
				break;
			case 5:
				result =  isMagic(matrix);
				
				showMatrix(matrix, "A matriz: ");
				gotoxy(3, 10 + rows*2);
				if(result)printf("? quadrado m?gico");
				else printf("N?o ? quadrado m?gico");
				gotoxy(3, 11 + rows*2);
				textcolor(4);
				printf("Pressione qualquer tecla para continuar");
				textcolor(0);
				getch();
				
				break;
			case 6:
				result = isLatin(matrix);
				
				showMatrix(matrix, "A matriz: ");
				gotoxy(3, 10 + rows*2);
				if(result)printf("? quadrado latino");
				else printf("N?o ? quadrado latino");
				gotoxy(3, 11 + rows*2);
				textcolor(4);
				printf("Pressione qualquer tecla para continuar");
				textcolor(0);
				getch();
				
				break;
			case 7:
				result = isPermutation(matrix);
				
				showMatrix(matrix, "A matriz: ");
				gotoxy(3, 10 + rows*2);
				if(result)printf("? matriz de permuta??o");
				else printf("N?o ? matriz de permuta??o");
				gotoxy(3, 11 + rows*2);
				textcolor(4);
				printf("Pressione qualquer tecla para continuar");
				textcolor(0);
				getch();
				
				break;
		}
	}

	void showMatrix(int matrix[maxSize][maxSize], char * message){
		printHeader();
		int i, j, x, y;
		gotoxy(3, 3); printf("%s", message);
		for(i=0, y=5;i<rows;i++){
			for(j=0,x=horizontalCenter-(columns*3);j<columns;j++){
				gotoxy(x,y);
				printf("%d", matrix[i][j]);
				x+=5;
			}
			y+=2;
		}
	}

	void showHighlightedRow(int matrix[maxSize][maxSize], int row){
		int i, j, x, y;
		for(i=0, y=5;i<rows;i++){
			if(i==row) textcolor(4);
			else textcolor(0);

			for(j=0,x=horizontalCenter-columns*3;j<columns;j++){
				gotoxy(x,y);
				printf("%d", matrix[i][j]);
				x+=5;
			}
			y+=2;
		}
	}

	void showHighlightedColumn(int matrix[maxSize][maxSize], int column){
		int i, j, x, y;
		for(i=0, y=5;i<rows;i++){
			for(j=0,x=horizontalCenter-columns*3;j<columns;j++){
				if(j==column)textcolor(4);
				else textcolor(0);

				gotoxy(x,y);
				printf("%d", matrix[i][j]);
				x+=5;
			}
			y+=2;
		}
	}

	int selectRow(int matrix[maxSize][maxSize]){
		showGuidance("Utilize as setas (cima/baixo) e enter para selecionar");
		int x1=horizontalCenter-(columns*3)-4, x2=horizontalCenter+(columns*2);
		int aux = 5, choice = 0, count = 0; char Cursor;

		textcolor(4);
		gotoxy(x1, aux);printf(">");
		gotoxy(x2, aux);printf("<");
		textcolor(0);

		cursor(0);
		while (!choice) {
	        Cursor = getch();
	        gotoxy(x1,aux); printf("  ");
	        gotoxy(x2,aux); printf("  ");

	        switch(Cursor){
	        	case upArrow:
	        		if(aux == 5) {
	        			aux = 3+rows*2;
						count = rows-1;
					}
	                else {
	                	aux -=2;
	                	count--;
					}
	                break;
	            case downArrow:
	            	if(aux == 3+rows*2) {
	            		aux = 5;
	            		count = 0;
					}
	                else {
	                	aux+=2;
	                	count++;
					}
	                break;
	            case enter:
	            	choice = 1;
	            	break;
	            case esc:
	            	return -1;
			}

	        textcolor(4);
			gotoxy(x1, aux);printf(">");
			gotoxy(x2, aux);printf("<");
			textcolor(0);
	    }
	    cursor(1);

	    choice = count;

	    textcolor(4);
		gotoxy(x1, aux);printf(" ");
		gotoxy(x2, aux);printf(" ");
		textcolor(0);

		showHighlightedRow(matrix, choice);

	    return choice;
	}

	int selectColumn(int matrix[maxSize][maxSize]){
		showGuidance("Utilize as setas (direita/esquerda) e enter para selecionar");
		int y1=5, y2=3+columns*2;
		int aux = horizontalCenter-(columns*3), choice = 0, count = 0; char Cursor;

		textcolor(4);
		gotoxy(aux, 4);printf("v");
		gotoxy(aux, 5+rows*2-1);printf("^");
		textcolor(0);

		cursor(0);
		while (!choice) {
	        Cursor = getch();
	        textcolor(4);
			gotoxy(aux, 4);printf(" ");
			gotoxy(aux, 5+rows*2-1);printf(" ");
			textcolor(0);

	        switch(Cursor){
	        	case leftArrow:
	        		if(aux == horizontalCenter-(columns*3)) {
	        			aux = horizontalCenter+(columns*2)-5;
						count = columns-1;
					}
	                else {
	                	aux -=5;
	                	count--;
					}
	                break;
	            case rightArrow:
	            	if(aux == horizontalCenter+(columns*2)-5) {
	            		aux = horizontalCenter-(columns*3);
	            		count = 0;
					}
	                else {
	                	aux+=5;
	                	count++;
					}
	                break;
	            case enter:
	            	choice = 1;
	            	break;
	            case esc:
	            	return -1;
			}

	        textcolor(4);
			gotoxy(aux, 4);printf("v");
			gotoxy(aux, 5+rows*2-1);printf("^");
			textcolor(0);
	    }
	    choice = count;

	    textcolor(4);
		gotoxy(aux, 4);printf(" ");
		gotoxy(aux, 5+rows*2-1);printf(" ");
		textcolor(0);

	    showHighlightedColumn(matrix, choice);

	    cursor(1);
	    return choice;
	}

	void readMatrix(int matrix[maxSize][maxSize]){
		printHeader();
		gotoxy(1,3); printf("Digite a Matriz:");
		int i, j;
		int x=horizontalCenter-(columns*3), y=5; //gotoxy

		int digits = 0, num, lastDigit = 0;
		for(i=0, y=5;i<rows;i++){
			for(j=0,x=horizontalCenter-(columns*3);j<columns;j++){
				gotoxy(x,y);
				scanf(" %d", &matrix[i][j]);
				num = matrix[i][j];
	//			while(num > 1) {
	//				num = num / 10;
	//				digits++;
	//			}
				x+=5;
			}

			y+=2;
		}
	}

	void generateMatrix(int matrix[maxSize][maxSize]){
		int i, j;
		for(i=0;i<rows;i++)
			for(j=0;j<columns;j++)
				matrix[i][j]=rand()%10;
	}

	int fillMatrix(int matrix[maxSize][maxSize]){
		printHeader();
		gotoxy(3,3);printf("Modo de preenchimento da matriz: ");
		gotoxy(3,5);printf("Entrada pelo teclado");
	    gotoxy(3,6);printf("Gerada aleatoriamente");
	    switch(menuSelection(5,6)){
	    	case 1:
	    		readMatrix(matrix);
	    		break;
	    	case 2:
	    		generateMatrix(matrix);
	    		break;
	    	case -1:
	    		return -1;
		}
		return 0;
	}

	int menuSelection(int rowMin, int rowMax){
		cursor(0); textcolor(0);
	    int choice = 0;
	    int aux = rowMin;
	    char Cursor;

	    gotoxy(0,aux); printf(" >");
	    while (!choice) {
	        Cursor = getch();
	        gotoxy(0,aux); printf("  ");

	        switch(Cursor){
	        	case upArrow:
	        		if(aux == rowMin) aux = rowMax;
	                    else aux --;
	                    break;
	            case downArrow:
	            	if(aux == rowMax) aux = rowMin;
	                    else aux++;
	                    break;
	            case enter:
	            	choice = aux-rowMin+1;
	            	break;
	            case esc:
	            	choice = -1;
	            	break;
			}

	        gotoxy(0,aux); printf(" >");
	    }

	    cursor(1);
	    return choice;
	}

	int isSquare(){
		if(columns == rows)return 1; //yes, is square
		else return 0; //no, isn't square
	}

	int isSimetric(int matrix[maxSize][maxSize]) {
		int flag = 0, r, c;
		for (r = 0; r < rows; r++) {
			for (c = 0; c < columns; c++) {
				if (matrix[r][c] != matrix[c][r]) {
					flag++;
					break;
				}
			}
			if (flag > 0) break;
		}

		if(flag>0) return 0;
		else return 1;
	}

	int isMagic(int matrix[maxSize][maxSize]) {
		int sum = 0, sum2 = 0, lastSum, aux, i, j, k, flag = 0;
		for (i = 0; i < rows; i++) {
			for (j = 0, sum = 0; j < columns; j++) {
				sum += matrix[i][j];
			}
			if (i > 0 && lastSum != sum) {
				flag++;
				break;
			}
			lastSum = sum;
		}
		for (i = 0; i < rows; i++) {
			for (j = 0, sum = 0; j < columns; j++) {
				sum += matrix[j][i];
			}
			if (i > 0 && lastSum != sum) {
				flag++;
				break;
			}
			lastSum = sum;
		}
		for (i = 0, j = rows - 1, sum  = 0, sum2 = 0; i < rows; i++, j--) {
			sum += matrix[i][i];
			sum2 +=	matrix[i][j];
		}
		if (sum != sum2) {
			flag++;
		}

		if(flag > 0) return 0;
		else return 1;
	}

	int isLatin(int matrix[maxSize][maxSize]) {
		int vet[maxSize], i, k, j, flag = 0;

		for (i = 0; i < rows; i++) {
	        vet[i] = 0;
	        for (j = 0; j < rows; j++) {
	            vet[i] += matrix[i][j];
	            for (k = 0; k < rows; k++)
	                if (matrix[i][j] == matrix[i][k] && j != k) flag++;
	        }
	    }

	    for (i = 0; i < rows - 1; i++)
	        if (vet[i] != vet[i + 1]) flag++;


	    for (j = 0; j < rows; j++) {
	        vet[j] = 0;
	        for (i = 0; i < rows; i++) {
	            vet[j] += matrix[i][j];
	            for (k = 0; k < rows; k++)
	                if (matrix[i][j] == matrix[k][j] && i != k) flag++;
	        }
	    }

		for (i = 0; i < rows - 1; i++) {
		    if (vet[i] != vet[i + 1]) flag++;
		}

		if(flag > 0)return 0;
		else return 1;
	}

	int isPermutation(int matrix[maxSize][maxSize]) {
		int flag = 0, i, j;
		int sumCol[maxSize], sum;

		for(i = 0; i < rows; i++)
			sumCol[i] = 0;

		for(i = 0; i < rows && !flag; i++){
		    sum = 0;
		    for(j = 0; j < rows && !flag; j++){
		    	if (matrix[i][j] != 1 && matrix[i][j] != 0)
					flag++;
		   		else {
					sumCol[j] += matrix[i][j];
					sum += matrix[i][j];
				}
		    }

		if(sum != 1)
		    flag++;
		}

		for(i = 0; i < rows && !flag; i++)
		    if(sumCol[i] != 1)
		    	flag++;

		if(flag > 0)return 0;
		else return 1;
	}

	int mainMenu(int matrix[maxSize][maxSize]){
		printHeader();
		showMatrix(matrix, "Matriz obtida: ");
		int x = 5 + rows * 2; int y;
		gotoxy(3,++x); printf("Selecione a opera??o a ser realizada com a matriz (pressione ESC para sair): ");
	    gotoxy(3,++x); printf("Trocar linhas");
	    gotoxy(3,++x); printf("Trocar colunas");
	    y = x;
		if(!isSquare())textcolor(8);
	    gotoxy(3,++x); printf("Trocar diagonais");
	    gotoxy(3,++x); printf("Verificar se ? sim?trica");
	    gotoxy(3,++x); printf("Verificar se ? quadrado m?gico");
	    gotoxy(3,++x); printf("Verificar se ? quadrado latino");
	    gotoxy(3,++x); printf("Verificar se ? matriz de permuta??o");

	    if(!isSquare())
			return menuSelection(rows*2+7, y);
		else
			return menuSelection(rows*2+7, x);
	}

	int reprocessing(){
		printHeader();
		gotoxy(3,3);printf("Deseja recome?ar?");
		gotoxy(3,5);printf("Sim");
	    gotoxy(3,6);printf("N?o");
	    return menuSelection(5,6);
	}
