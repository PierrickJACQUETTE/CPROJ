// une Makefile qui nous dit juste les commande pour compiler pour le moment 

// pour un fichier xml: 
gcc nomFichier.c `xml2-config --cflags --libs`


// pour sdl 

gcc nomFichier.c `sdl2-config --cflags --libs`
