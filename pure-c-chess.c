#include <stdio.h>
#include <stdlib.h>

void printBoard(char board[8][8])
{ //Schachbrett ausgeben
	char colCaption[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
	int rowCaption[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int i, j, k;

	printf("\n  BLACK\n");

	printf("\n    ");

	for (i = 0; i < 8; i++)
	{ //colCaptionbeschriftung (oben)
		printf("    %c   ", colCaption[i]);
	}

	printf("\n\n    %c", 201);
	for (i = 0; i < 63; i++)
	{
		if (i % 8 == 7)
			printf("%c", 203);
		else
			printf("%c", 205);
	}
	printf("%c\n", 187);

	printf("    %c       %c       %c       %c       %c       %c       %c       %c       %c\n    %c", 186, 186, 186, 186, 186, 186, 186, 186, 186, 186);

	for (i = 0; i < 8; i++)
	{ //Elemente des Board-Arrays ausgeben
		for (j = 0; j < 8; j++)
		{
			printf("   %c   ", board[i][j]);
			if (j < 7)
				printf("%c", 186);
			else
				printf("%c   %d", 186, rowCaption[i]); //rowCaptionbeschriftung (rechts)
		}

		printf("\n    %c       %c       %c       %c       %c       %c       %c       %c       %c", 186, 186, 186, 186, 186, 186, 186, 186, 186);
		if (i < 7)
		{
			printf("\n    %c", 204);
			for (k = 0; k < 63; k++)
			{
				if (k % 8 == 7)
					printf("%c", 206);
				else
					printf("%c", 205);
			}
			printf("%c\n", 185);
		}
		else
		{
			printf("\n    %c", 200);
			for (k = 0; k < 63; k++)
			{
				if (k % 8 == 7)
					printf("%c", 202);
				else
					printf("%c", 205);
			}
			printf("%c", 188);
		}
		if (i < 7)
			printf("    %c       %c       %c       %c       %c       %c       %c       %c       %c\n    %c", 186, 186, 186, 186, 186, 186, 186, 186, 186, 186);
	}
	printf("\n    ");
	for (i = 0; i < 8; i++)
	{ //colCaptionbeschriftung (unten)
		printf("    %c   ", colCaption[i]);
	}
	printf("\n\n  WHITE");
	printf("\n        type \"undo\" + Enter to undo the last move \n");
}

void printMenu()
{
	int i;

	printf("\n\n        %c", 201);
	for (i = 0; i < 23; i++)
		printf("%c", 205);
	printf("%c\n", 187);
	printf("        %c                       %c\n", 186, 186);
	printf("        %c         CHESS         %c\n", 186, 186);
	printf("        %c                       %c\n", 186, 186);
	printf("        %c", 204);
	for (i = 0; i < 23; i++)
		printf("%c", 205);
	printf("%c\n", 185);
	printf("        %c                       %c\n", 186, 186);
	printf("        %c         MENU:         %c\n", 186, 186);
	printf("        %c                       %c\n", 186, 186);
	printf("        %c      1 NEW GAME       %c\n", 186, 186);
	printf("        %c      2 LOAD GAME      %c\n", 186, 186);
	printf("        %c      3 EXIT           %c\n", 186, 186);
	printf("        %c                       %c\n", 186, 186);
	printf("        %c                       %c\n", 186, 186);
	printf("        %c", 200);
	for (i = 0; i < 23; i++)
		printf("%c", 205);
	printf("%c\n", 188);
}

int setEmptyBoard(char board[8][8], char emptyField)
{ //Array mit ' ' auff�llen
	int i, j;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			board[i][j] = emptyField;
		}
	}
}

void setPieces(char board[8][8], char white[5], char black[5])
{ //Ausgangspositionen der Figuren
	int i;

	for (i = 0; i < 8; i++)
	{
		//Bauern schwarz und wei�
		board[1][i] = black[0];
		board[6][i] = white[0];
	}
	//schwarz (Kleinbuchstaben)
	board[0][0] = black[3];
	board[0][7] = black[3];
	board[0][1] = black[1];
	board[0][6] = black[1];
	board[0][2] = black[2];
	board[0][5] = black[2];
	board[0][3] = black[4];
	board[0][4] = black[5];
	//wei� (Gro�buchstaben)
	board[7][0] = white[3];
	board[7][7] = white[3];
	board[7][1] = white[1];
	board[7][6] = white[1];
	board[7][2] = white[2];
	board[7][5] = white[2];
	board[7][3] = white[4];
	board[7][4] = white[5];
}

void createNewFile()
{ //leere Datei namens GameState erstellen
	FILE *fp;

	if ((fp = fopen("GameState.txt", "w")) == 0)
	{
		system("cls");
		printf("Error while onpening file! \n");
	}
	else
	{
		fprintf(fp, "");
	}
	fclose(fp);
}

void saveMove(char move[4])
{ //g�ltigen move in die GameState.txt schreiben
	FILE *fp;
	char *pMove = move;

	if ((fp = fopen("GameState.txt", "a")) == 0)
	{
		system("cls");
		printf("Error while onpening file! \n");
	}
	else
	{
		fprintf(fp, "%c%c%c%c\n", *(pMove + 0), *(pMove + 1), *(pMove + 2), *(pMove + 3));
	}
	fclose(fp);
}

int validateMove(char board[8][8], char move[4], char emptyField, int player, int round);

int executeMove(char board[8][8], char move[4], char emptyField, int player, int round)
{ //move wird �berpr�ft. Falls Eingabe korrekt ist, wird 1 zur�ckgegeben. Ansonsten return 0
	int f;
	char(*pBoard)[8] = board;
	char *pMove = move;
	int col1, row1, col2, row2;

	col1 = *(pMove + 0) - 97;
	row1 = *(pMove + 1) - 49;
	//1. Feld z.B. a7 -> aus 'a' wird 0 | aus '7' wird 6

	col2 = *(pMove + 2) - 97;
	row2 = *(pMove + 3) - 49;
	//2. Feld z.B. b5 -> aus 'b' wird 1 | aus '5' wird 4

	if ((col1 <= 7) && (col1 >= 0) && (row1 <= 7) && (row1 >= 0) && (col2 <= 7) && (col2 >= 0) && (row2 <= 7) && (row2 >= 0))
	{ //�berpr�fung, ob sich die eingegebenen Felder auf dem 8x8 Schachbrett befinden
		if (player == 1)
		{ //falls Wei� dran ist
			if ((*(*(pBoard + row1) + col1) >= 65) && (*(*(pBoard + row1) + col1) <= 90) && ((*(*(pBoard + row2) + col2) < 65) || (*(*(pBoard + row2) + col2) > 90)))
			{ //schauen, ob setEmptyBoard des 1. Feldes Gro�buchstabe ist und ob setEmptyBoard des 2. Feldes kein Gro�buchstabe ist

				f = validateMove(board, move, emptyField, player, round);

				//if ((*(*(pBoard + row2) + col2) == 'K') || (*(*(pBoard + row2) + col2) == 'k'))    //pr�fe, ob der K�nig erfolgreich angegriffen wurde
				//return 2;

				if (f == 0)
					return 0;
				else
				{
					*(*(pBoard + row2) + col2) = *(*(pBoard + row1) + col1);
					*(*(pBoard + row1) + col1) = emptyField; // 2. Feld bekommt setEmptyBoard des Ersten und erstes Feld wird leer
				}
				return 1; //move f�r Wei� ist g�ltig, also gib 1 zur�ck
			}
			else
			{
				system("cls");
				printf("Player 1's turn!\n");
				return 0; //Ung�ltig, 0 zur�ckgeben
			}
		}
		else
		{ //falls Schwarz dran ist
			if ((*(*(pBoard + row1) + col1) >= 97) && (*(*(pBoard + row1) + col1) <= 122) && ((*(*(pBoard + row2) + col2) < 97) || (*(*(pBoard + row2) + col2) > 122)))
			{ //schauen, ob setEmptyBoard des 1. Feldes Kleinbuchstabe ist und ob setEmptyBoard des 2. Feldes kein Kleinbuchstabe ist

				f = validateMove(board, move, emptyField, player, round);
				if (f == 0)
					return 0;
				else
				{
					*(*(pBoard + row2) + col2) = *(*(pBoard + row1) + col1);
					*(*(pBoard + row1) + col1) = emptyField; // 2. Feld bekommt setEmptyBoard des Ersten und erstes Feld wird leer
				}
				return 1; //move f�r Schwarz ist g�ltig, also gib 1 zur�ck
			}
			else
			{
				system("cls");
				printf("Player 2's turn!\n");
				return 0; //Ung�ltig, 0 zur�ckgeben
			}
		}
	}
	else
	{
		system("cls");
		printf("Invalid move! Field does not exist\n");
		return 0; //Ung�ltig, 0 zur�ckgeben
	}
}

int loadGame(char board[8][8], char emptyField)
{
	char move[1000];
	int round = 1;
	int line = 0, f;
	int player;
	FILE *fp;

	if ((fp = fopen("GameState.txt", "r")) == 0)
	{
		system("cls");
		printf("Error while opening file! \n");
	}
	else
	{
		while (fgets(move, 1000, fp))
		{ //rowCaptionweise lesen und in move abspeichern
			line++;
			if (line % 2 == 1)
				printf("      Round %d Player 1 (white): %s", round, move);
			else
			{
				printf("      Round %d Spieler 2 (black): %s", round, move);
				round++;
			}
			if (f = executeMove(board, move, emptyField, line % 2, round) == 0)
			{ //falls ung�ltiger move gelesen wird
				if (line % 2 == 1)
					player = 2;
				else
					player = 1;
				printf("      Invalid move!\n", 129);
				return player;
			}
		}
		if (line % 2 == 1) //f�r line = ungerade ist -> wei� | f�r line = gerade -> schwarz
			player = 1;
		else
			player = 2;
		return player;
		fclose(fp);
	}
}

void rotateLeft(char *moveAll, int n)
{ //Vektorrotation aus Praktikum
	int i, h = moveAll[n - 1];

	for (i = 0; i < n - 1; i++)
		moveAll[i] = moveAll[i + 1];
	moveAll[n - 1] = h;
}

int undo(char moveAll[2000], int *p)
{
	int i, j = 0;

	if ((p) <= 0)
		return 0;
	for (i = 0; i < 4; i++)
	{ //die letzten 4 Array-Elemente werden gel�scht
		rotateLeft(moveAll + (*p), (*p));
		(*p)--;
	}

	for (i = 0; i < *p; i++)
		printf("%c", moveAll[i]);

	FILE *fp;

	if ((fp = fopen("GameState.txt", "w")) == 0)
	{ //wieder in Datei geschrieben
		system("cls");
		printf("Error while onpening file! \n");
	}
	else
	{
		for (i = 0; i < (*p) / 4; i++)
		{
			fprintf(fp, "%c%c%c%c\n", *(moveAll + j), *(moveAll + j + 1), *(moveAll + j + 2), *(moveAll + j + 3));
			j = j + 4;
		}
	}
	fclose(fp);
}

int validateMove(char board[8][8], char move[4], char emptyField, int player, int round)
{
	char(*pBoard)[8] = board;
	char *pMove = move;
	int col1, row1, col2, row2;
	int i, d;

	col1 = *(pMove + 0) - 97;
	row1 = *(pMove + 1) - 49;

	col2 = *(pMove + 2) - 97;
	row2 = *(pMove + 3) - 49;

	if (player == 1)
	{ //�berpr�fung der Spielz�ge f�r Wei�
		switch (*(*(pBoard + row1) + col1))
		{		  //welche Figur wird bewegt?
		case 'B': //g�ltige Spielz�ge f�r Bauern
			if ((row1 == 6))
			{																	  //wenn Bauer (wei�) sich auf der Startposition (rowle 7) befindet -> Bauer darf bis zu 2 Felder vorw�rts
				if ((col1 == col2) && ((row2 == row1 - 2) || (row2 == row1 - 1))) //muss collte des 1. Feldes gleich collte des 2. Feldes sein UND rowle 2 muss entweder rowle1-1 oder rowle2-2 sein
					if (row2 == row1 - 2)
					{
						if ((*(*(pBoard + (row1 - 1)) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
					}
					else
						return 1;
				else
				{
					system("cls");
					return 0;
				}
			}
			else
			{ //Bauer darf nur 1 Feld vorw�rts nur beim Attackieren 1 Feld diagonal
				if (*(*(pBoard + row2) + col2) == emptyField)
				{											  //wenn 2. Feld leer ist
					if ((col1 == col2) && (row2 == row1 - 1)) //1 Feld vorw�rts
						return 1;
					else
					{
						system("cls");
						return 0;
					}
				}
				else
				{
					if (((col2 == col1 + 1) || (col2 == col1 - 1)) && (row2 == row1 - 1)) //diagonal vorw�rts, falls 2. Feld gegenerische Figur ist
						return 1;
					else
					{
						system("cls");
						return 0;
					}
				}
			}
			break;
		case 'S': //g�ltige Spielz�ge f�r Springer
			if ((((col2 == col1 + 1) || (col2 == col1 - 1)) && ((row2 == row1 + 2) || (row2 == row1 - 2))) || (((col2 == col1 + 2) || (col2 == col1 - 2)) && ((row2 == row1 + 1) || (row2 == row1 - 1))))
				return 1;
			else
				system("cls");
			return 0;
			break;
		case 'L':
			if ((col2 - col1 == row2 - row1) || (col2 - col1 == row1 - row2) || (col1 - col2 == row2 - row1) || (col1 - col2 == row1 - row2))
			{												  //Differenz der rowCaption- und colCaptionabst�nde muss gleich sein
				if ((col2 - col1 == 1) || (col1 - col2 == 1)) //falls Abstand von rowle und collte 1 betr�gt, ist move g�ltig
					return 1;
				else if ((col2 > col1) && (row2 < row1))
				{ //Bewegung nach rechts oben
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 + i)) != emptyField)
						{ //falls eine Figur dazwischen ist -> ung�ltig
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 > col1) && (row2 > row1))
				{ //Bewegung nach rechts unten
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 + i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 < row1))
				{ //Beweugung nach links oben
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 > row1))
				{ //Bewegung nach links unten
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else
				{
					system("cls");
					return 0;
				}
			}
			else
			{
				system("cls");
				return 0;
			}
			break;
		case 'T':
			if (col2 == col1)
			{
				if (row1 < row2)
				{
					for (i = row1 + 1; i < row2; i++)				 //Bewegung r�ckw�rts
						if ((*(*(pBoard + i) + col2)) == emptyField) //Pr�fe, ob die Felder dazwischen leer sind
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i++) //Bewegung vorw�rts
						if ((*(*(pBoard + i) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else if (row2 == row1)
			{ //Bewegung seitw�rts
				if (col1 < col2)
				{
					for (i = col1 + 1; i < row2; i++) //rechts
						if ((*(*(pBoard + row2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i--) //links
						if ((*(*(pBoard + col2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else
			{
				system("cls");
				return 0;
			}
			break;
		case 'D': //f�r Dame werden die if-Statements von Turm und L�ufer genommen
			if (col2 == col1)
			{
				if (row1 < row2)
				{
					for (i = row1 + 1; i < row2; i++)				 //Bewegung vorw�rts
						if ((*(*(pBoard + i) + col2)) == emptyField) //Pr�fe, ob die Felder dazwischen leer sind
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i++) //Bewegung r�ckw�rts
						if ((*(*(pBoard + i) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else if (row2 == row1)
			{ //Bewegung seitw�rts
				if (col1 < col2)
				{
					for (i = col1 + 1; i < row2; i++) //rechts
						if ((*(*(pBoard + row2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i--) //links
						if ((*(*(pBoard + col2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else if ((col2 - col1 == row2 - row1) || (col2 - col1 == row1 - row2) || (col1 - col2 == row2 - row1) || (col1 - col2 == row1 - row2))
			{
				if ((col2 - col1 == 1) || (col1 - col2 == 1))
					return 1;
				else if ((col2 > col1) && (row2 < row1))
				{
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 + i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 > col1) && (row2 > row1))
				{
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 + i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 < row1))
				{
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 > row1))
				{
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else
				{
					system("cls");
					return 0;
				}
			}
			else
			{
				system("cls");
				return 0;
			}
			break;
		case 'K':
			if ((col2 == col1) && ((row2 == row1 + 1) || (row2 == row1 - 1))) //vorw�rts und r�ckw�rts
				return 1;
			else if ((row2 == row1) && ((col2 == col1 + 1) || (col2 == col1 - 1))) //seitw�rts
				return 1;
			else if (((col2 == col1 + 1) || (col2 == col1 - 1)) && ((row2 == row1 + 1) || (row2 == row1 - 1))) //diagonal
				return 1;
			else
			{
				system("cls");
				return 0;
			}
			break;
		}
	}
	else
	{ //�berpr�fung der Figuren f�r Schwarz
		switch (*(*(pBoard + row1) + col1))
		{
		case 'b':
			if ((row1 == 1))
			{
				if ((col1 == col2) && ((row2 == row1 + 2) || (row2 == row1 + 1)))
				{
					if (row2 == row1 + 2)
					{
						if ((*(*(pBoard + (row1 + 1)) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
					}
					else
						return 1;
				}
				else
				{
					system("cls");
					return 0;
				}
			}
			else
			{
				if (*(*(pBoard + row2) + col2) == emptyField)
				{
					if ((col1 == col2) && (row2 == row1 + 1))
						return 1;
					else
					{
						system("cls");
						return 0;
					}
				}
				else
				{
					if (((col2 == col1 + 1) || (col2 == col1 - 1)) && (row2 == row1 + 1))
						return 1;
					else
					{
						system("cls");
						return 0;
					}
				}
			}
			break;
		case 's':
			if ((((col2 == col1 + 1) || (col2 == col1 - 1)) && ((row2 == row1 + 2) || (row2 == row1 - 2))) || (((col2 == col1 + 2) || (col2 == col1 - 2)) && ((row2 == row1 + 1) || (row2 == row1 - 1))))
				return 1;
			else
			{
				system("cls");
				return 0;
			}
			break;
		case 'l':
			if ((col2 - col1 == row2 - row1) || (col2 - col1 == row1 - row2) || (col1 - col2 == row2 - row1) || (col1 - col2 == row1 - row2))
			{
				if ((col2 - col1 == 1) || (col1 - col2 == 1))
					return 1;
				else if ((col2 > col1) && (row2 < row1))
				{
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 + i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 > col1) && (row2 > row1))
				{
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 + i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 < row1))
				{
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 > row1))
				{
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else
				{
					system("cls");
					return 0;
				}
			}
			else
			{
				system("cls");
				return 0;
			}
			break;
		case 't':
			if (col2 == col1)
			{
				if (row1 < row2)
				{
					for (i = row1 + 1; i < row2; i++)
						if ((*(*(pBoard + i) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i++)
						if ((*(*(pBoard + i) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else if (row2 == row1)
			{
				if (col1 < col2)
				{
					for (i = col1 + 1; i < row2; i++)
						if ((*(*(pBoard + row2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i--)
						if ((*(*(pBoard + col2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else
			{
				system("cls");
				return 0;
			}
			break;
		case 'd':
			if (col2 == col1)
			{
				if (row1 < row2)
				{
					for (i = row1 + 1; i < row2; i++)
						if ((*(*(pBoard + i) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i++)
						if ((*(*(pBoard + i) + col2)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else if (row2 == row1)
			{
				if (col1 < col2)
				{
					for (i = col1 + 1; i < row2; i++)
						if ((*(*(pBoard + row2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
				else
				{
					for (i = row1 - 1; i > row2; i--) //links
						if ((*(*(pBoard + col2) + i)) == emptyField)
							return 1;
						else
						{
							system("cls");
							return 0;
						}
				}
			}
			else if ((col2 - col1 == row2 - row1) || (col2 - col1 == row1 - row2) || (col1 - col2 == row2 - row1) || (col1 - col2 == row1 - row2))
			{
				if ((col2 - col1 == 1) || (col1 - col2 == 1))
					return 1;
				else if ((col2 > col1) && (row2 < row1))
				{
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 + i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 > col1) && (row2 > row1))
				{
					d = col2 - col1;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 + i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 < row1))
				{
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 - i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else if ((col2 < col1) && (row2 > row1))
				{
					d = col1 - col2;
					for (i = 1; i < d; i++)
					{
						if ((*(*(pBoard + row1 + i) + col1 - i)) != emptyField)
						{
							system("cls");
							return 0;
						}
						else
							return 1;
					}
				}
				else
				{
					system("cls");
					return 0;
				}
			}
			else
			{
				system("cls");
				return 0;
			}
			break;
		case 'k':
			if ((col2 == col1) && ((row2 == row1 + 1) || (row2 == row1 - 1)))
				return 1;
			else if ((row2 == row1) && (col2 == col1 + 1) || (col2 == col1 - 1))
				return 1;
			else if (((col2 == col1 + 1) || (col2 == col1 - 1)) && ((row2 == row1 + 1) || (row2 == row1 - 1)))
				return 1;
			else
			{
				system("cls");
				return 0;
			}
			break;
		}
	}
}

int main()
{

	char board[8][8];
	int userInput, i, player, f;
	char white[6] = {'B', 'S', 'L', 'T', 'D', 'K'};
	char black[6] = {'b', 's', 'l', 't', 'd', 'k'};
	char emptyField = ' ';
	char move[4];
	char moveAll[2000];
	int p = 0;
	int round = 1;
	int moveID = 1;

	printMenu();
	printf("            SELECT: ");
	scanf("%d", &userInput);
	switch (userInput)
	{
	case 1:
		createNewFile();
		system("cls");
		setEmptyBoard(board, emptyField);
		setPieces(board, white, black);
		printBoard(board);
		player = 2;
	Play:
		while (1)
		{					 //Spieler abwechseln
			if (player == 2) //Wei� beginnt
				player = 1;
			else if (player == 1)
				player = 2;
			switch (player)
			{
			case 1:
				printf("\n        round %d\n", round);
				printf("     >> next move for Player 1 (white): ");
				if ((scanf("%4s", &move)) == 0)
				{
					system("cls");
					printBoard(board);
					printf("      Invalid move!\n");
					player = 2;
				}
				else
				{
					if ((move[0] == 'u') && (move[1] == 'n') && (move[2] == 'd') && (move[3] == 'o'))
					{
						if (moveID > 1)
						{
							round--;
							undo(moveAll, &p);
							moveID--;
							goto Load; //Sprung zu Spiel laden | Datei neu laden
						}
						else
						{
							system("cls");
							printf("      Can't undo move!\n", 148);
							printBoard(board);
							player = 2;
						}
					}
					else
					{
						f = executeMove(board, move, emptyField, player, round); //f bekommt entweder Wert 0 (ung�ltig), 1 (move ist g�ltig)
						if (f == 0)
						{ //Falls Eingabe falsch war bleibt Wei� am move
							printBoard(board);
							printf("      Invalid move!\n");
							player = 2;
						}
						else
						{
							system("cls"); //move (wei�) speichern, Schwarz ist dran
							printBoard(board);
							for (i = 0; i < 4; i++) //alle Z�ge werden in Array moveAll abgespeichert
								moveAll[p + i] = move[i];
							p = p + 4;
							saveMove(move);
							moveID++;
						}
					}
				}
				break;
			case 2:
				printf("\n        round %d\n", round);
				printf("     >> next move for Player 2 (black): ", 132);
				if ((scanf("%4s", &move)) == 0)
				{
					printBoard(board);
					printf("      Invalid move!\n");
					player = 2;
				}
				else
				{
					if ((move[0] == 'u') && (move[1] == 'n') && (move[2] == 'd') && (move[3] == 'o'))
					{
						undo(moveAll, &p);
						moveID--;
						goto Load;
					}
					else
					{
						f = executeMove(board, move, emptyField, player, round);
						if (f == 0)
						{
							printBoard(board);
							printf("       Invalid move!\n");
							player = 1;
						}
						else
						{
							system("cls");
							printBoard(board);
							for (i = 0; i < 4; i++)
								moveAll[p + i] = move[i];
							p = p + 4;
							saveMove(move);
							round++;
							moveID++;
						}
					}
				}
			}
		}
		break;
	case 2:
	Load:
		system("cls");
		setEmptyBoard(board, emptyField);
		setPieces(board, white, black);
		player = loadGame(board, emptyField);
		printBoard(board);
		goto Play;
	case 3:
		return 0;
		break;
	default:
		system("cls");
		printf("Invalid input!");
		break;
	}
}