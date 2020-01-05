#!/bin/bash

: '
Scrivere uno script cercafile.sh che, per ciascuna lettera che sta tra c e g cerca i
file (o directory) che stanno nella directory /usr/include (non nelle sottodirectory) e
che hanno quella lettera come secondo carattere del nome del file, e che verificano
una delle due seguenti proprietà: la lunghezza del percorso assoluto del file è
minore di 15 OPPURE è maggiore di 21. Di questi file stampa in output il percorso
assoluto. 
'

DIR=/usr/include
echo $DIR
for FILE in `ls ${DIR}/?{c..g}*`; do
    if (( ${#FILE}<18|| ${#FILE}>21 )); then
        echo ${FILE}
    fi
done 
