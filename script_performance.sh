#!/bin/bash
#/usr/local/bin/bash

nbFic=0
tmpsMis=0

parcoursRep(){
  repertoire=$1

  droits=`stat -c "%a" $repertoire`
  #droits=`stat -f "%0p" $repertoire`

  chmod u+xr $repertoire
  cd $repertoire

  for fic in `ls`
  do
    if [ -f $fic ]
      then 

      echo "Fichier: $fic"
      let nbFic++

      time1=$(($(date +%s%N)/1000000))
      $(../CPROJ/CPROJ $fic -s)
      time2=$(($(date +%s%N)/1000000))

      time3=$(($time2-$time1))     
      tailleFic=$(ls -lh $fic | cut -d " " -f5)

      echo "Taille_fichier: $tailleFic  Temps_d'execution: $time3 ms" 

      let tmpsMis=$(($tmpsMis+$time3))

    else
      if [ -d $fic ]
        then
        echo "   *"$fic
        parcoursRep $fic
      else
        echo " $fic n'est ni un fic ni un rep, on ne fais rien"
      fi
    fi
  done
  cd ..
  chmod $droits $repertoire
}


if [ $# != 1 ] || [ ! -d $1 ]
	then
	echo "Error: Il faut donner un nom de repertoire en argument."
else
	repertoire_test=$1
	parcoursRep $repertoire_test
	echo "Nombre de fichiers traité: "$nbFic
	echo "Temps d'execution: $tmpsMis ms"
  echo "Temps moyen d'execution: "$(($tmpsMis/$nbFic))" ms"
fi
