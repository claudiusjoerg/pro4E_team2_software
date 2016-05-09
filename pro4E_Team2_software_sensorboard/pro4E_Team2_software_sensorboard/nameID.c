/*
 * pro4E_Team2_software_sensorboard.c
 *
 * Created: 09.05.2016 10:41
 * Author : Sarah
 */ 

#include <stdio.h>
#include < stdlib.h>

int giveID()
{
	int name;
	printf("Zur Bennennung Ihres Moduls geben Sie ein Zahl zwischen 1 und 250 ein.\n");//"\n" naechste zeile
	scanf("%n", &name);//"%" Leerschlaege am Anfang ignorieren, in "name" speichern
	printf("\t.Die angeschlossene Sensorplatine trägt nun den Namen %n.\n", name);//"\t." naechste zeile zuerst
	return name;
}