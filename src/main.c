#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h> //Sleep
#else
	#include <unistd.h> //sleep
#endif
#include "../include/andebol.h"

int main() {
    Campeonato camp;   
	
#ifdef _WIN32
		system("cls");
        printf("#--------------------------------------------------#\n");
        printf("|                                                  |\n");    
        printf("|                                                  |\n");
        printf("|                                                  |\n");    
        printf("|                   _____ _____   _____            |\n");
        printf("|            /\\    / ____|  __ \\ / ____|           |\n");
        printf("|           /  \\  | (___ | |__) | (___             |\n");
        printf("|          / /\\ \\  \\___ \\|  _  / \\___ \\            |\n");
        printf("|         / ____ \\ ____) | | \\ \\ ____) |           |\n");
        printf("|        /_/    \\_\\_____/|_|  \\_\\_____/            |\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");    
        printf("|       Andebol Statistics Register Software       |\n");
        printf("|                     V 1.0                        |\n");    
        printf("|                                                  |\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");    
        printf("#--------------------------------------------------#\n");
        Sleep(3000);
	#else
	    system("clear");
        printf("#--------------------------------------------------#\n");
    	printf("|                                                  |\n");
	    printf("|                                                  |\n");
	    printf("|                                                  |\n");
	    printf("|         ▄▄▄▄    ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄    ▄▄▄▄▄▄▄       |\n");
	    printf("|       ▄██▀▀██▄ █████▀▀▀ ███▀▀███▄ █████▀▀▀       |\n");
	    printf("|       ███  ███  ▀████▄  ███▄▄███▀  ▀████▄        |\n");
	    printf("|       ███▀▀███    ▀████ ███▀▀██▄     ▀████       |\n");
    	printf("|       ███  ███ ███████▀ ███  ▀███ ███████▀       |\n");
	    printf("|                                                  |\n");
    	printf("|       Andebol Statistics Register Software       |\n");
	    printf("|                     V 1.0                        |\n");
	    printf("|                                                  |\n");
    	printf("|                                                  |\n");
	    printf("|                                                  |\n");
	    printf("#--------------------------------------------------#\n");
        sleep(3);
    #endif 
    

    ler_ficheiro(&camp);
    menuMI(&camp);
	libertarMemoria(&camp);

    return 0;
}