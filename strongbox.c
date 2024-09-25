/* TODO
  commenter tout le code
  regler les problèmes possibles en interceptant chacune des erreurs:
    SAVOIR RSA
    -
    --SEE CHAT GPT FOR ERRORS WITH INPUTS, if i input a phraase or even just press enter it should work (either ignore and wait again or just say invalid input) while?
    --physical errors such as arduino being pulled out?
    --mettre le lien de l'outil
    --la liste corrections est elle les reponses ?
    Unexpected Resets or Crashes:
    renommer les inputs de crypter parce qu'ils veulent rien dire
    a vrmt clef et e message, pas l'inverse?

    VOIR SI ON A TOUJOUR BESOIN DES UINTS32 parce que sinon on peut se faire haggrah dessus a la soutenance

    FINIR LES DOCS

  issues: la lettre doit être recupérée en rapport avec la tension mesurée sinon l'agent peut utiliser n'importe quelle lettre.
  mais donc il faudra directement gérer la tension donnée, si elle n'est pas reconnue, faire un print le disant mais cela ne devrait pas être possible
*/


void setup() {
  Serial.begin(9600);
}

/**
 * Cette fonction permet de lancer l'authentification par niveau de securite en fonction de la lettre de l'agent.
 *
 * @param id: lettre de l'agent.
 * @return appel a une fonction de niveau de securite.
 *
 * Exemple d'utilisation :
 * @code
 *   obtenirNiveauSecurite('A');
 * @endcode
 */
String obtenirNiveauSecurite(char id) {
  if ((id >= 'A' && id <= 'P') && (id == 'A' || id == 'F' || id == 'K' || id == 'P')) return niveauSecurite1(id);
  else if ((id >= 'A' && id <= 'P') && (id == 'B' || id == 'G' || id == 'L')) return niveauSecurite2(id);
  else if ((id >= 'A' && id <= 'P') && (id == 'C' || id == 'H' || id == 'M')) return niveauSecurite3(id);
  else if ((id >= 'A' && id <= 'P') && (id == 'D' || id == 'I' || id == 'N')) return niveauSecurite4(id);
  else if ((id >= 'A' && id <= 'P') && (id == 'E' || id == 'J' || id == 'O')) return niveauSecurite5(id);
  Serial.println("Erreur dans l'obtention du niveau de securité");
  return "";
}

/**
 * Cette fonction permet d'obtenir l'index de la lettre d'un agent dans l'alphabet commençant par l'index 0.
 *
 * @param id: lettre de l'agent.
 * @return La valeur retournée est un entier qui représente l'index de la lettre donnée.
 *
 * Exemple d'utilisation :
 * @code
 *   int indexLettreAgent = obtenirIndexLettreAgent('A');
 * @endcode
 */
int obtenirIndexLettreAgent(char id) {
  // si la lettre est entre a et p, on fait une soustraction de caractères, elle se fait direct en ascii donc si l'id est 'A',
  //cela va soustraire leurs codes ascii donnant 0, si on a C, l'ascii de C est 67 donc 67-65 qui donne 2, le bon index de c
  return (id >= 'A' && id <= 'P') ? id - 'A': (Serial.println("Erreur dans l'obtention de l'index de la lettre de l'agent"), -1);
}

/**
 * Permet d'obtenir la fonction qui chiffre le nombre d'étoiles observées par rapport a la lettre de l'agent.
 *
 * @param nombreEtoile: le nombre d'etoiles confondues dans chacunes des lignes affichées.
 * @param id: lettre de l'agent.
 * @return Description de la valeur de retour.
 *
 * Exemple d'utilisation :
 * @code
 *   obtenirFonctionAgent(7, 'A');
 * @endcode
 */
int obtenirFonctionAgent(int nombreEtoile, char id) {
  int functions[] = {(2 * nombreEtoile) + 15,(-3 * nombreEtoile) + 5,(4 * nombreEtoile) - 2,(-nombreEtoile) + 6,(0.5 * nombreEtoile) + 2,(-1.5 * nombreEtoile) + 4,(3 * nombreEtoile) + 1,(1.5 * nombreEtoile) + 2,(-0.75 * nombreEtoile) - 1,(2 * nombreEtoile) + 7,(-4 * nombreEtoile) + 9,(0.25 * nombreEtoile) + 3,(3.5 * nombreEtoile) + 4,(2 * nombreEtoile) + 3,(-2.5 * nombreEtoile) - 2,(-1 * nombreEtoile) - 5};
  int indexLettreAgent = obtenirIndexLettreAgent(id);
  return functions[indexLettreAgent];
}

/**
 * Description brève de la fonction.
 *
 * @param numero: de la question.
 * @return le numéro de la réponse.
 *
 * Exemple d'utilisation :
 * @code
 *  obtenirCorrection(1)
 * @endcode
 */
int obtenirCorrection(int numero) {
  int corrections[] = {1, 3, 3, 2};
  return (numero >= 0 && numero < 4) ? corrections[numero] : 0;
}

/**
 * Permet d'obtenir la clef publique d'un agent grace a sa lettre.
 *
 * @param id: lettre de l'agent.
 * @return renvoie l'entier qui correspond a la clef publique.
 *
 * Exemple d'utilisation :
 * @code
 *   int clefPublique = obtenirClefPublique('A');
 * @endcode
 */
int obtenirClefPublique(char id) {
  int clefsPubliques[] = {601, 619, 631, 641, 647, 653, 661, 673, 691, 701, 733, 739, 751, 797, 809, 811};
  int indexLettreAgent = obtenirIndexLettreAgent(id);
  return clefsPubliques[indexLettreAgent];
}

/**
 * Fonction qui permet de crypter/decrypter un entier.
 *
 * @param a: clef.
 * @param e: message.
 * @param n: paramètre de cryptage (produit de nombres premiers).
 * @return l'entier e crypté/décrypté.
 *
 * Exemple d'utilisation :
 * @code
 *   int entierCrypte = crypter(668,4219,43 * 67);
 * @endcode
 */
int crypter(uint32_t a, uint32_t e, int n) {
  if (n == 0 || a == 0 || e == 0 || n == 1) return 0;
  int r = 1;
  for (int i = 0; i < e; i++) r = (r * (a % n)) % n;
  return r;
}


/** FONCTIONS MA1 --> MA5
 * Description brève de la fonction.
 *
 * @param parametre1: Description du premier paramètre.
 * @param parametre2: Description du deuxième paramètre.
 * @return Description de la valeur de retour.
 *
 * Exemple d'utilisation :
 * @code
 *   int resultat = nomDeLaFonction(1, 2);
 * @endcode
 */
bool MA1(char id) {
  String questions[] = {"Securite principale du coffre-fort?","Nb d'interrupteurs a positionner avant insertion de la carte?","Comment verifier que l'auth carte/interrupteurs?","Quelle est l'etape deux de l'auth?"};
  String reponsesPossibles[] = {"1) Codes 2) Carte 3) Empreinte","1) 2 interrupteurs 2) 3 3) 4","1) Solution electrique 2) Empreinte 3) Mdp vocal","1) Numpad 2) ADN 3) Cle"};
  int nombreReponsesJustes = 0;

  Serial.println("Saisissez la bonne de la reponse :");
  
  for (int num = 0; num <= 3; num++) {
    Serial.println(questions[num]);
    Serial.println(reponsesPossibles[num]);
    while (!Serial.available()) {};
    if (Serial.parseInt() == obtenirCorrection(num)) nombreReponsesJustes += 1;
  }
  
  return nombreReponsesJustes == 4;
}


bool MA2(char id) {
  int codeEntree, entierAleatoire;
  entierAleatoire = random(8999) + 1000;
  Serial.println("Voici votre numero : " + String(entierAleatoire));
  Serial.println("Entrez votre code : ");
  while (!Serial.available()) {};
  codeEntree = Serial.parseInt();
  return codeEntree == entierAleatoire + 125;
}

bool MA3(char id) {
  int nombreEtoile = 0, reponse;
  String lignes[4];
  
  for (int ligne = 0; ligne <= 3; ligne++) {
    String combinaison = "";
    for (int i = 0; i <= 10; i++) {
      int car = random(3);
      if (car == 1) combinaison += "c";
      else if (car == 0) combinaison += "o";
      else combinaison += "*", nombreEtoile++;
    }
    lignes[ligne] = combinaison;
  }

  for (int i = 0; i <= 3; i++) Serial.println(lignes[i]);
  
  Serial.println("Entrez chiffre mystère transformé par votre fonction d'agent :");
  while (!Serial.available()) {};
  reponse = Serial.parseInt();
  return reponse == obtenirFonctionAgent(nombreEtoile, id);
}

bool MA4(char id) {
  String codeUtilisateur[] = {"1010","1011","0001","0111","1101","1110","0000","1000","0100","1001","0010","1100","1111","0101","0110","0011"};

  String codeEntree;
  String codeValide = codeUtilisateur[obtenirIndexLettreAgent(id)];

  Serial.println("Entrez votre code d'agent :");
  while (!Serial.available()) {};
  codeEntree = Serial.readString();
  return codeEntree == codeValide;
}

bool MA5(char id) {
  int n = 43 * 67, entierAleatoire = random(2882), entierCrypte, entierDecrypte;
  int publicKeyLetter = obtenirClefPublique(id);
  entierCrypte = crypter(entierAleatoire, publicKeyLetter, n);
  Serial.print("Code crypte : ");
  Serial.println(entierCrypte);
  Serial.println("Entrer le code decrypte : ");
  while (!Serial.available()) {};
  entierDecrypte = Serial.parseInt();
  return entierAleatoire == entierDecrypte;
}

/** FONCTIONS NIVEAU SECURITE
 * Description brève de la fonction.
 *
 * @param parametre1: Description du premier paramètre.
 * @param parametre2: Description du deuxième paramètre.
 * @return Description de la valeur de retour.
 *
 * Exemple d'utilisation :
 * @code
 *   int resultat = nomDeLaFonction(1, 2);
 * @endcode
 */
String niveauSecurite1(char id) {
  if (MA1(id)) return MA3(id) ? "MA1 ✓ ; MA3 ✓ !" : "MA1 ✓ ; MA3 ✘ !";
  else return "MA1 ✘ !";
}

String niveauSecurite2(char id) {
  if (MA1(id)) return MA4(id) ? "MA1 ✓ ; MA4 ✓ !" : "MA1 ✓ ; MA4 ✘ !";
  else return "MA1 ✘ !";
}

String niveauSecurite3(char id) {
  if (MA2(id)) return MA5(id) ? "MA2 ✓ ; MA5 ✓ !" : "MA2 ✓ ; MA5 ✘ !";
  else return "MA2 ✘ !";
}

String niveauSecurite4(char id) {
  if (MA2(id)) {
    if (MA3(id)) return MA4(id) ? "MA2 ✓ ; MA3 ✓ ; MA4 ✓ !" : "MA2 ✓ ; MA3 ✓ ; MA4 ✘ !";
    else return "MA2 ✓ ; MA3 ✘ !";
  } else return "MA2 ✘ !";
}

/**
 * Description brève de la fonction.
 *
 * @param parametre1: Description du premier paramètre.
 * @param parametre2: Description du deuxième paramètre.
 * @return Description de la valeur de retour.
 *
 * Exemple d'utilisation :
 * @code
 *   int resultat = nomDeLaFonction(1, 2);
 * @endcode
 */
String niveauSecurite5(char id) {
  if (MA1(id)) {
    if (MA2(id)) {
      if (MA3(id)) return MA5(id) ? "MA1 ✓ ; MA2 ✓ ; MA3 ✓ ; MA5 ✓ !" : "MA1 ✓ ; MA2 ✓ ; MA3 ✓ ; MA5 ✘ !";
      else return "MA1 ✓ ; MA2 ✓ ; MA3 ✘ !";
    } else return "MA1 ✓ ; MA2 ✘ !";
  } else return "MA1 ✘ !";
}

char obtenirId() {

  int valeurRecue = analogRead(A0);
  float tension = valeurRecue * (5.0/1023.0)*1000.0;
  float plageTension[] ={1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  for (int t = 0; t <= 16; t++) {
    (tension == plageTension[t]) ? return toChar(t+65);
  }
  Serial.println("obtenirId n'a pas fonctionné");
  return "";
  
}

void loop() {

  char id;
  id=obtenirId();
  obtenirNiveauSecurite(id);
 
}