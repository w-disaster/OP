#!/bin/bash

: '
Stampare a video le sole righe del file 
/usr/include/ stdio.h che contengono almeno 
un asterisco * Suggerimento1: utilizzare il comando 
grep ma  senza usare l operatore |
Suggerimento2: Guardare il man di 
grep per capire come usare 
grep in modo opportuno
'

grep '*' /usr/include/stdio.h
