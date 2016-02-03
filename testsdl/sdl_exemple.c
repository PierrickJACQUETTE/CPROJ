/*
 * Le code ci-dessous donne quelques exemples d'usage de SDL. Sous 
 * ubuntu 14.04, les packages a installer avec leurs  dependances 
 * sont :
 * 
 * libsdl-2-2.0-0
 * libsdl2-dev
 *
 * La compilation se fait via la commande suivante :
 * 
 * gcc -o sdl_exemple sdl_exemple.c `sdl2-config --cflags --libs`
 * 
 * La documentation de SDL se trouve ici :
 *
 * http://wiki.libsdl.org/FrontPage
 *
 *
 * Ce que cette librairie permet de faire :
 * - afficher une fenetre a l'ecran
 * - capturer les mouvements de souris dans les fenetres
 * - capturer les evenements clavier lorsque la fenetre a le focus
 * - dessiner dans la fenetre
 *     une ligne, 
 *     un rectangle rempli, 
 *     une image bitmap stockee dans un fichier externe.
 * Curieusement, on ne peut (apparemment) pas afficher de cercles, ni
 * de texte dans la fenetre (il faut une autre librairie, SDL_ttf, 
 * mais son usage semble loin d'etre simple) - autrement dit, si vous
 * souhaitez afficher des pions, il faudra faire des collages d'images
 * bitmaps.
 * 
 * Remarque : toutes les fonctions de cette librairie renvoient une 
 * valeur singuliere en cas d'erreur. Pour ne pas demesurement 
 * allonger ce code, la detection des erreurs est limitees a quelques
 * etapes-clefs (creation de la fenetre et de son renderer, creation
 * de surface a partir d'une image bitmap - il se peut que le fichier
 * n'existe pas). mais on peut completer ce code en verifiant les
 * valeurs des retours (ou par des assertions sur leurs valeurs). 
 */

#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

enum status {QUIT, CONTINUE}; 
/* etat actuel de la boucle d'evenements, c.f. plus bas. */

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect;
    int width = 320, height = 240;
    enum status status = CONTINUE;


    /* La toute premiere etape est l'initialisation de SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	/* gestion de l'echec de l'initialisation */
        fprintf(stderr,
                "\nImpossible d'initialiser SDL :  %s\n",
                SDL_GetError()
		);
        exit(1);
    }
    atexit(SDL_Quit);
    

    /* La creation d'une fenetre graphique se fait en deux temps. 
     * Dans un premier temps, on cree la fenetre  elle-meme. L'appel 
     * ci-dessous renvoie un point d'acces a la fenetre, ou NULL si 
     * la creation a echouee.
     */
    window = SDL_CreateWindow
	("A window",                 /* titre */
	 SDL_WINDOWPOS_CENTERED,     /* placement en x */
	 SDL_WINDOWPOS_CENTERED,     /* placement en y */
	 320,                         /* largeur */
	 240,                         /* hauteur */
	 0                            /* drapeaux, cf, la doc.  */
	 );
    /* gestion de l'echec de la creation de la fenetre */
    if (window == NULL) {
	fprintf(stderr,
		"\nCreation de la fenetre impossible : %s\n", 
		SDL_GetError()
		);
        exit(1);
    }
    

    /* Dans un second temps, on cree pour la fenetre un "renderer" 
     * (un point d'acces aux pixels de la fenetre a l'ecran) via ce 
     * renderer que l'on pourra dessiner dans la fenetre, y transferer
     * une image, etc.
     */
    renderer = SDL_CreateRenderer(window, -1, 0);
    /* gestion de l'echec de la creation du renderer */
    if (renderer == NULL) {
	fprintf(stderr,
		"\nCreation du renderer impossible : %s\n", 
		SDL_GetError()
		);
        exit(1);
    }


    /* La fenetre et son renderer sont pres. On peut a present, par 
     * exemple :
     */

    /* (1) Effacer le contenu de la fenetre */
    SDL_RenderClear(renderer); 

    /* (2) Choisir une couleur de dessin. Les arguments qui suivent 
     * le renderer sont (entre 0 et 255) : composantes rouge, vert, 
     * bleu, alpha (transparence)
     */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    /* (3) Dessiner une ligne de (0,0) a (320, 240) */
    SDL_RenderDrawLine(renderer, 0, 0, 320, 240);
    

    /* (4) Afficher une image bitmap dans la fenetre. 
     * (4.1) L'image est chargee en memoire dans une "surface"  (une 
     * matrice de pixels hors-ecran).
     */
    surface = SDL_LoadBMP("test.bmp");
    if (surface == NULL) {
	fprintf(stderr,
		"/nImpossible de charger l'image ou de creer\
la surface : %s\n", 
		SDL_GetError()
		);
	exit(1);
    }
    /* (4.2) La surface est transformee en "texture" compatible avec 
     * le renderer - il s'agit encore d'une matrice de pixels hors-
     * ecran, mais manipulable de maniere plus flexible : on peut par
     * exemple la deformer en largeur et/ou hauteur.
     */
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    /* la surface n'a servi qu'a creer une nouvelle texture, et peut 
     * a present etre liberee.
     */
    SDL_FreeSurface(surface);
    /* (4.3) La texture est transferee a l'ecran. 
     * (a) On choisit un rectangle de destination
     * (x, y, largeur, hauteur). La cordonnee (0,0) est le
     * le coin superieur gauche de la fenetre.
     */
    dest_rect = (SDL_Rect) { 0, 0, 100, 100 };
    /* (b) On transmet au renderer la demande d'affichage de la 
     * texture dans son rectangle de destination... 
     */
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    /* (c) puis une demande de transfert effectif du resultat vers les
     * pixels de la fenetre a l'ecran.
     */
    SDL_RenderPresent(renderer);
    /* (d) la texture, a present inutile, est liberee */
    SDL_DestroyTexture(texture);
    /* (PS). Les descriptions (b,c) ne sont qu'une interpretation
     * de la documentation de SDL, et semblent compatibles avec le 
     * mecanisme reellement mis en jeu. Malheureusement, cette 
     * documentation manque d'une description conceptuelle de ce
     * mecanisme.
     */

    /* (5) Dessiner et remplir un rectangle dans la fenetre.
     * (5.1) On cree d'abord une surface de la taille du rectangle.
     * ici, la taille souhaitee est 70 x 50 (largeur x hauteur) 
     */
    surface = SDL_CreateRGBSurface(0, 70, 50, 32, 0, 0, 0, 0);
    if(surface == NULL) {
        fprintf(stderr, "/nImpossible de creer la surface : %s\n", SDL_GetError());
        exit(1);
    }
    /* (5.2) La surface est remplie de la couleur souhaitee.
     * (apres surface -> format : composantes rouge (255), vert (0), 
     * bleu (0)).
     */
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    /* (5.3) La suite d'operations est ensuite la meme que ci-dessus,
     * pour finaliser l'affichage d'une image bitmap a l'ecran.
     * - creation d'une texture, liberation de la surface,
     * - choix d'un rectangle de destination,
     * - transfert, rafraichissement.
     */
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    dest_rect = (SDL_Rect) { 100, 100, 70, 50 };
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);

    /* boucle de capture d'evenements dans la fenetre. la boucle dure 
     * tant que la variable status n'a pas pris la valeur QUIT.
     */
    do {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
	    /* examen du type de l'evenement */
	    switch (e.type) {
		/* fermeture de la fenetre */
	    case SDL_QUIT :
		printf("fermeture de la fenetre.\n"); 
		status = QUIT;
		break;
		/* deplacement de la souris, pointeur dans la fenetre */
	    case SDL_MOUSEMOTION :
		printf("deplacement : %d %d\n", 
		       e.motion.x, 
		       e.motion.y);
		break;
		/* clic de souris, pointeur dans la fenetre */
	    case SDL_MOUSEBUTTONDOWN :
		printf("clic : %d %d, bouton ", 
		       e.button.x, 
		       e.button.y);
		/* avec l'un des boutons : */
		switch (e.button.button) {
		case SDL_BUTTON_LEFT   : printf ("gauche.\n");  break;
		case SDL_BUTTON_MIDDLE : printf ("central.\n"); break;
		case SDL_BUTTON_RIGHT  : printf ("droit.\n"); break;
		default : printf("autre.\n"); break; 
		}
		break;
	    case SDL_KEYDOWN :
		/* touche presse, focus sur la fenetre */
		printf("touche pressee : ");
		/* extraction de la valeur de la touche pressee : 
		 * (1) extraction d'un description la touche 
		 */
		SDL_Keysym ks = e.key.keysym;
		/* (2) affichage du code de la touche. cette valeur 
		 * peut etre comparee a une constante de la forme 
		 * SDLK_a, SDLK_b, ..., SLDK_z (touches a, b, ..., z)
		 * c.f. https://wiki.libsdl.org/SDL_Keycode
		 */
		printf("%d ", ks.sym);
		/* pour les touches 0 ... 9, a... z, le code de
		 * la touche coincide avec son code ascii - sans
		 * tenir compte d'un shift eventuel 
		 */
		if (ks.sym >= 32 && ks.sym <= 127)
		    printf(" soit '%c'\n", (char) ks.sym); 
		else printf("\n");
		break;
	    case SDL_KEYUP :
		/* touche relachee, focus sur la fenetre */
		printf("touche relachee\n");
		break;
		
	    }
        }
    } while (status != QUIT);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
