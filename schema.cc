// Implementatie van klasse Schema

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include "standaard.h"
#include "schema.h"
using namespace std;

//*************************************************************************

Schema::Schema()
{
// TODO: implementeer zo nodig deze constructor
this->nrSpelers = 0; // TODO: value
this->nrRondes = 0; // TODO: value.
}  // default constructor

//*************************************************************************

Schema::Schema (int nwNrSpelers)
{
  int schema[MaxGrootteSchema];
  for (int i = 0; i < MaxGrootteSchema; i++) {
    schema[i] = 0;
  }
  //Controle op aantal spelers
  if (nwNrSpelers % 4 == 2 || nwNrSpelers % 4 == 3)
  {
    cout << "Dit is een ongeldig aantal spelers" << endl;
  }

  //Variabelen initialiseren
  if (nwNrSpelers % 4 == 1)
  {
    nrRondes = nwNrSpelers;
    nrTafels = (( (nwNrSpelers - 1) / 4)* nrRondes);
  }
  else
  {
    nrRondes = nwNrSpelers - 1;
    nrTafels = ((nwNrSpelers / 4) * nrRondes);
  }

  startPos = 0;
  nrSpelers = nwNrSpelers;
  myArray = (nrRondes * nwNrSpelers);

  /* vector<Speler> spelers;
  spelers.reserve(nrSpelers);
  for (int i = 0; i < nrSpelers; i++) {
    int id = i;
    spelers.push_back(Speler(id));
  } */
  /* cout << "vector Spelers heeft " << spelers.size() << " elementen." << endl;
  cout << "Speler 3 heeft id " << spelers[3].id << endl; */

  /* Speler speler0, Speler speler1, Speler speler2, Speler speler3, Speler speler4, 
  Speler speler5, Speler speler6, Speler speler7, Speler speler8, Speler speler9, 
  Speler speler10, Speler speler11, Speler speler12, Speler speler13, Speler speler14,
  Speler speler15, Speler speler16, Speler speler17, Speler speler18, Speler speler19, */

  drukAfSchema(schema);
}  // constructor met parameter

//*************************************************************************

bool Schema::leesInDeelschema (const char* invoerNaam)
{
  //Controleert of het bestand invoernaam te openen is
  ifstream invoer;
  invoer.open(invoerNaam, ios::in);
  if (invoer.fail() ) {
    cerr << "Kon het bestand '" << invoerNaam << "' niet openen." << endl;
    return false;
  }
  invoer >> nrSpelers >> bijRonde;
  if (nrSpelers % 4 == 1) {
    nrRondes = nrSpelers;
    sizeRonde = nrSpelers - 1;
  }
  else {
    nrRondes = nrSpelers - 1;
    sizeRonde = nrSpelers;
  }
  myArray = (nrRondes * sizeRonde);
  startPos = bijRonde * sizeRonde;
  cout << "start pos " << startPos << endl;

 //Leest het ingevoerde schema in
 for (int i = 0; i < (nrSpelers * bijRonde); i++) {
   invoer >> schema[i];
 }

  if (nrSpelers % 4 == 0)
  {
    nrRondes = nrSpelers-1;
    nrTafels = ((nrSpelers / 4) * nrRondes);
  }
  else
  {
    int spelerCorr = nrSpelers - 1;
    nrRondes = nrSpelers;
    nrTafels = ((spelerCorr / 4) * nrRondes);
  }
  //Controle, schema kopieren in vector
  if (isOngeldigSchema(schema)){
    return false;
  }
  vectorToArray();
 cout << "ingelezen schema: " << endl;
  drukAfSchema(schema);
cout << endl << "vector Schema: " << endl;
drukAfSchema(newSchema); 

  cout << endl;
  return true;
}  // leesInDeelschema

//*************************************************************************


//*************************************************************************

void Schema::drukAfSchema (int schema[MaxGrootteSchema]) {
  for (int i = 0; i < myArray; i++) {
    cout << schema[i] << ' ';
    if (((i + 1) % 4) == 0) {
      cout << "| ";
    }
    if (((i + 1) % sizeRonde) == 0) {
      cout << endl;
    }
  }
} // drukAfSchema

//************************************************************************

// Bepaal met behulp van backtracking een geldig schema voor het huidige
    // aantal spelers. Het maakt niet uit wat de `waarde' van dit schema is
    // (zie ook bepaalMinSchema).
    // Als er een deelschema van een aantal rondes is ingelezen, bouw
    // dan daarop verder.
    // Retourneer:
    // * true, als het lukt om een schema te bepalen
    // * false, als het niet lukt om een schema te bepalen
    // Pre:
    // * membervariabele nrSpelers heeft een bruikbare waarde
    // Post:
    // * als het lukt om een geldig schema te bepalen, bevat parameter `schema'
    //   zo'n schema. Alle rondes zitten daar dan achter elkaar, beginnend
    //   op positie 0 van het array.
    // * aantalDeelschemas is gelijk aan het aantal deelschemas dat we
    //   hebben gezien bij het bepalen van een schema

bool Schema::hulpSchemaBTV(long long &aantalDeelschemas) {
  int pos = ingedeeld.size();
  cout << "pos is " << pos << endl;
  //end pos == nrRondes * sizeRonde
  if(ingedeeld.size() == nrRondes * sizeRonde) {
    vectorToArray();
    /* if (isGeldig(newSchema)) {
      drukAfSchema(newSchema);
      return true;
    } */
    cout << "vector is " << endl;
    for (auto i: ingedeeld) {
      cout << i << ' ';
    }
    cout << "MaatMatrix" << endl;
    for (int i = 0; i < nrSpelers; i++) {
      for (int j = 0; j < nrSpelers; j++) {
        cout << maatMatrix[i][j] << ' ';
        if (j == nrSpelers - 1) {
          cout << endl;
        }
      }
    } //for maatmatrix
    return true;
  } //if
  //afdrukken Vector
  for (int i = 0; i < nrSpelers; i++) {
    addSpeler(i);
    aantalDeelschemas++;
    if (hulpSchemaBTV(aantalDeelschemas) == true) {
      return true;
    }
    deleteSpeler();
  }
  return false;
}

/* bool Schema::hulpSchemaBT (int pos, int schema[MaxGrootteSchema], long long &aantalDeelschemas) {
  cout << "BT pos:  " << pos << endl;
  aantalDeelschemas++;
  if (pos == 19) {
      return true;
    }
  
 for (int i = 0; i < nrSpelers; i++) {
    if (isPlaatsingGeldig(pos, i, schema) == true) {
      addSpeler(i);
      int toegevoegd = ingedeeld.back();
      cout << toegevoegd << endl;
      if (hulpSchemaBT(pos + 1, deelschema, aantalDeelschemas) == true) {
        return true;
      }
      deleteSpeler(i);
    }
  } */
  /* addSpeler(speler, pos, schema);
  if (isPlaatsingGeldig(pos, speler, schema)) {
    hulpSchemaBT(pos + 1, speler, schema, aantalDeelschemas);
  }

  deleteSpeler(speler, tafel, pos);
  hulpSchemaBT(pos, speler + 1, schema, aantalDeelschemas);
  return false;
} */

bool Schema::bepaalSchemaBT (int schema[MaxGrootteSchema],long long &aantalDeelschemas) {
  if (hulpSchemaBTV(aantalDeelschemas) == true) {
    return true;  
  }
  return false;
}  //  bepaalSchemaBT

//*************************************************************************

bool Schema::bepaalMinSchema (int schema[MaxGrootteSchema],
                          long long &aantalDeelschemas, bool bouwWaardeOp)
{

// TODO: implementeer deze memberfunctie
  return false;

}  // bepaalMinSchema

//*************************************************************************

void Schema::bepaalSchemaGretig (int schema[MaxGrootteSchema])
{

// TODO: implementeer deze memberfunctie

}  // bepaalSchemaGretig

//*************************************************************************
bool Schema::isVeilig() {
  if (ingedeeld.empty()) {
    return true;
  }
  if (vectorAlGespeeld() || vectorMaatGeweest() || vectorTegenGeweest()) {
    return false;
  }
  return true;
}

//*************************************************************************
/* True wanneer een speler al eerder is ingedeeld in de ronde. */
bool Schema::vectorAlGespeeld() {
  if (ingedeeld.empty()) { //als pos = 0;
    return false;
  }
  int pos = ingedeeld.size() - 1, speler = ingedeeld.back();
  int hulp = pos % sizeRonde, beginRonde = pos - hulp;
  if (hulp == 0) {  //eerste speler in ronde kan niet eerder hebben gespeeld in ronde
      return false; 
  }
  for (int i = pos; pos >= beginRonde; i--) {
    if (ingedeeld.at(i) == speler)
    //Kijk naar achteren ivm constructie recursie. 
    for (int i = pos - 1; i >= beginRonde; i--) {
      if (ingedeeld.at(i) == speler) {
         cout << "Speler " << speler << " heeft al eerder gespeeld op schema[" << i << "]" << endl;
        return true;
      } //if
    } //for
  } //for
  return false;
}
//*************************************************************************
/* True wanneer speler al eerder maat was van een eerder ingedeelde
speler. False als duo eerste keer maten zijn. */
bool Schema::vectorMaatGeweest() {
  if (ingedeeld.size() > 2) {
    int pos = ingedeeld.size() - 1, speler = ingedeeld.back();
    int maat = ingedeeld.at(pos - 2);
    if (maatMatrix[speler][maat] == 1) {
      return true;
    }
  }
  return false;
}
//*************************************************************************
/* True wanneer speler al 2x tegen eerder ingedeelde speler
heeft gespeeld. */
bool Schema::vectorTegenGeweest() {
  int pos, speler;
  if (ingedeeld.size() > 1) {
    pos = ingedeeld.size() - 1, speler = ingedeeld.back();
    int t1 = ingedeeld.at(pos - 1);
    if (tegenMatrix[speler][t1] >= 2) {
      return true;
    }
  }
  if (ingedeeld.size() > 3) {
    int t2 = ingedeeld.at(pos - 3);
    if (tegenMatrix[speler][t2] >= 2) {
      return true;
    }
  }
  return false;
}

//*************************************************************************
bool Schema::vectorVrijGeweest() {
  return false;
}
//*************************************************************************

 //*************************************************************************
  void Schema::addSpeler(int speler) {
  if (speler > 0) {
    speler = speler % nrSpelers;
  }
  if (!(ingedeeld.size() == myArray)){
  ingedeeld.push_back(speler);

  int pos = ingedeeld.size() - 1;
  cout << "addedSpeler " << speler << endl;

  if (!ingedeeld.empty()) {
    if (pos % 4 == 0) {

    }
    if (pos % 4 == 1) {
      int t1 = ingedeeld.at(pos-1);
      tegenMatrix[speler][t1]++, tegenMatrix[t1][speler]++;
    }
    if (pos % 4 == 2) {
      int myMaat = ingedeeld.at(pos - 2);
      cout <<  "voor speler " << speler << " my Maat: " << myMaat << " op pos-2: " << pos << endl;
      int t1 = ingedeeld.at(pos-1);
      maatMatrix[speler][myMaat]++, maatMatrix[myMaat][speler]++;
      tegenMatrix[speler][t1]++, tegenMatrix[t1][speler]++;
    }
    if (pos % 4 == 3) {
      int myMaat = ingedeeld.at(pos - 2);
      cout << "voor speler " << speler << " my Maat: " << myMaat << " op pos-2: " << pos << endl;
      int t1 = ingedeeld.at(pos - 1);
      int t2 = ingedeeld.at(pos - 3);
      maatMatrix[speler][myMaat]++, maatMatrix[myMaat][speler]++;
      tegenMatrix[speler][t1]++, tegenMatrix[t1][speler]++;
      tegenMatrix[speler][t2]++, tegenMatrix[t2][speler]++;
    }
  }}
 /* int tafel;
  if (pos == 0) {
   tafel = 0; 
  }
  else if (pos % 4 == 0 ) {
    tafel = pos / 4;
   } */
  /* if (pos % 4 == 1) {
    int t1 = getSpelerAt(schema, tafel, 1);
    tegenMatrix[speler][t1]++;
  }
  */
}
/* Werkt de matrices zodat boolean controle functies
blijven werken. Let op: verwijdert alleen de laatst geplaatste speler*/
void Schema::deleteSpeler() {
  int speler = ingedeeld.back();
  cout << "deleting player" << speler << endl;
  int pos = ingedeeld.size() - 1;

    if (pos % 4 == 1) {
      int t1 = ingedeeld.at(pos-1);
      tegenMatrix[speler][t1]--, tegenMatrix[t1][speler]--;
    }
    if (pos % 4 == 2) {
      int myMaat = ingedeeld.at(pos - 2);
      int t1 = ingedeeld.at(pos-1);
       cout <<  "voor speler " << speler << " my Maat: " << myMaat << " op pos-2: " << pos << endl;
      maatMatrix[speler][myMaat]--, maatMatrix[myMaat][speler]--;
      tegenMatrix[speler][t1]--, tegenMatrix[t1][speler]--;
    }
    if (pos % 4 == 3) {
      int myMaat = ingedeeld.at(pos - 2);
       cout <<  "voor speler " << speler << " my Maat: " << myMaat << " op pos-2: " << pos << endl;
      int t1 = ingedeeld.at(pos - 1);
      int t2 = ingedeeld.at(pos - 3);
      maatMatrix[speler][myMaat]--, maatMatrix[myMaat][speler]--;
      tegenMatrix[speler][t1]--, tegenMatrix[t1][speler]--;
      tegenMatrix[speler][t2]--, tegenMatrix[t2][speler]--;
    }
    ingedeeld.pop_back();
}



int* Schema::getRonde(int schema[MaxGrootteSchema], int rondeIx, int nrSpelers)
{
  return &schema[(rondeIx * nrSpelers)];
}
//*************************************************************************
int Schema::getPlekje(int schema[MaxGrootteSchema], int rondeIx, int nrSpelers, int spelerPos)
{
  int* plekje = getRonde(schema, rondeIx, nrSpelers);
  return plekje[spelerPos];
}
//*************************************************************************
//Telt hoe veel rondes een speler heeft gespeeld
int Schema::aantalRondesGespeeld(int speler, int pos, int schema[MaxGrootteSchema])
{
  int teller = 0;
  for (int i = 0; i < pos; i++) {
    if (schema[i] == speler)  {
      teller++;
    }
  }
  return teller;
}

bool Schema::alGespeeld(int speler, int pos, int schema[MaxGrootteSchema]) {
  if (pos == 0) {
    return false;
  }
  //eerste speler in ronde kan niet eerder hebben gespeeld in ronde
  else if (pos % sizeRonde == 0) {
    return false; 
  }
  else {
    int hulp = pos % sizeRonde;
    int beginRonde = pos - hulp;
    //Kijk naar achteren ivm constructie recursie. 
    for (int i = pos - 1; i >= beginRonde; i--) {
      if (schema[i] == speler) {
        cout << "Speler " << speler << " heeft al eerder gespeeld op schema[" << i << "]" << endl;
        return true;
      }
    }
    return false;
  }
}



//*************************************************************************
/* Deze functie zal het beginpunt van tafel n in totSchema aangeven.
Let op: returnt een pointer, dus gebruik in combi met getSpelerAt vooral. */
int* Schema::getTafel(int schema[MaxGrootteSchema], int tafelIx)
{
  return &schema[(tafelIx * 4)];
}
//*************************************************************************
// Returnt welke speler aan tafel n zit op de gevraagde positie.
int Schema::getSpelerAt(int schema[MaxGrootteSchema], int tafelIx, int spelerPos)
{
  int* tafel = getTafel(schema, tafelIx);
  if (spelerPos == 0)
  {
    return tafel[spelerPos];
  }
  else
  {
    return tafel[spelerPos % 4];
  }
}
//*************************************************************************
/* Deze functie zoekt de speler in het schema. Waneer de speler is gevonden,
wordt de maat gevonden met de functie getSpelerAt. Deze maat wordt in de
unordered set myMaten geplaatst. De functie unordered_set set.insert()
retourneert een pair, bestaande uit: een pointer naar het element, of een
equivalent element al in de set; en een boolean die false retourtneert indien
de set al het element bevatte.
INPUT: een schema

OUTPUT:
- TRUE indien de speler deze maat al eens heeft gehad
- FALSE indien er nooit een duplicaat wordt geplaatst in de set myMaten */
bool Schema::maatGeweest(int schema[MaxGrootteSchema], int speler, int pos)  // maatMatrix correct invullen op basis van schema
{
  int atTafel;
  int totHier = pos - 2;
  for (int i = 0; i <= totHier; i++) {
    if (i == 0) {
      atTafel = 0;
    }
    else {
      if (i % 4 == 0) {
        atTafel++;
      }
    } //else
    if (schema[i] == speler) { //speler gevonden"
      int myMaat = getSpelerAt(schema, atTafel, (i + 2));
      //Komt deze speler al voor in de verzameling myMaten?

      auto addMaat = myMaten.insert(myMaat);
      maatMatrix[speler][myMaat] = 1;
      if(addMaat.second == false) {
        myMaten.clear(); //clear cache
        return true;
      } //if
    } //if
  } //for
  myMaten.clear(); //clear cache
  return false;
} //maatGeweest

void Schema::vectorToArray() {
  int n = ingedeeld.size();
  for (int i = 0; i < n; i++) {
    newSchema[i] = ingedeeld[i];
  }
  drukAfSchema(newSchema);
}



/* Zoekt op in de maatMatrix of spelers al samen hebben gespeeld. 
Routerneert true als maatMatrix[speler][maat] = 1. Anders false. */
bool Schema::wasMaat(int speler, int maat) {
  cout << "Speler is " << speler << " en maat is " << maat << endl;
  if (maatMatrix[speler][maat] == 1) {
    return true;
  }
  else {
    return false;
  }
}

//*************************************************************************
/* Deze functie zoekt de speler in het schema. Wanneer de speler is gevonden,
worden de tegenstanders gevonden met de functie getSpelerAt. Deze tegen-
standers worden in de multiset myTegenstanders geplaatst.

INPUT: een schema, en een speler

OUTPUT:
- TRUE wanneer de verzameling tegenstanders meer dan 2x hetzelfde element bevat
- FALSE wanneer de verzameling tegenstanders max. 2x hetzelfde element bevat
  na zoeken door het gehele schema. */

bool Schema::tweedeKeerTegenGeweest(int schema[MaxGrootteSchema], int speler, int pos)
{
  int atTafel = 0;
  int totHier = pos - 3;
  for (int i = 0; i <= totHier; i++) {
    if (i == 0) {
      atTafel = 0;
    }
    else {
      if (i % 4 == 0) {
        atTafel++;
      }
    }
    if (schema[i] == speler) {
      int t1 = getSpelerAt(schema, atTafel, (i + 1));
      int t2 = getSpelerAt(schema, atTafel, (i + 3));
      myTegenstanders.insert(t1), myTegenstanders.insert(t2);
        //Heb ik al twee keer tegen deze spelers gespeeld
      if(myTegenstanders.count(t1) > 2 || myTegenstanders.count(t2) > 2) {
        myTegenstanders.clear();
        return true;
        }
      tegenMatrix[speler][t1] = myTegenstanders.count(t1), tegenMatrix[speler][t2] = myTegenstanders.count(t2);
      }
  } //for
  myTegenstanders.clear();
  return false;
} //tweedeKeerTegenGeweest

//*************************************************************************
/* Retourneert true als de speler al twee keer tegen de tegenstander heeft gespeeld*/
bool Schema::tegenGeweest(int speler, int t1, int t2) {
  if (tegenMatrix[speler][t1] >= 2 || tegenMatrix[speler][t2] >= 2) {
    return true;
  }
  return false;
}

//*************************************************************************

  bool Schema::isPlaatsingGeldig(int pos, int speler, int schema[MaxGrootteSchema]) {
    int tafel = atTafel(pos);
    cout << "isPlaatsingGeldig: tafel is " << tafel << " en pos is " << pos << endl;

    if (pos == 0) {
      cout << "Speler " << speler << " plaatsen op positie " << pos << "is geldig." << endl;
      return true;
    }
    if (alGespeeld(speler, pos, schema) == true) {
      cout << "Speler " << speler << "heeft al eerder gespeeld" << endl;
      return false;
    }
    if (pos % 4 == 1) {
      int t1 = getSpelerAt(schema, tafel, 0);
      cout << "t1 is " << t1 << endl;
      if (tegenGeweest(speler, t1, t1)) {
        cout << "Speler " << speler << " heeft al 2x tegen " << t1 << "gespeeld." << endl;
        return false;
      }
    }
    if (pos % 4 == 2) {
      int myMaat = getSpelerAt(schema, tafel, 0);
      cout << "myMaat is " << myMaat << endl;
      int t1 = getSpelerAt(schema, tafel, 1);
      cout << "t1 is " << t1 << endl;
      if (wasMaat(speler, myMaat)|| tegenGeweest(speler, t1, t1)) {
        cout << "Ongeldige plaatsing" << endl;
        return false;
      }
    }
    if (pos % 4 == 3) {
      int myMaat = getSpelerAt(schema, tafel, 1);
      cout << "myMaat is " << myMaat;
      int t1 = getSpelerAt(schema, tafel, 0);
      cout << "t1 is " << t1 << endl;
      int t2 = getSpelerAt(schema, tafel, 2);
      cout << "t2 is " << t2 << endl;
      if (wasMaat(speler, myMaat) || tegenGeweest(speler, t1, t1)) {
        cout << "ongeldige plaatsing" << endl;
       return false;
      }
    }
    if (pos % 4 == 0) {
      cout << "Speler " << speler << " plaatsen op beginpositie ronde" << pos << "is altijd geldig." << endl;
      return true;
      }
    cout << "Speler " << speler << " plaatsen op positie " << pos << "is geldig." << endl;
    return true;
    }
  //*************************************************************************
  int Schema::atRonde(int pos) {
    if (pos == 0) {
      return 1;
    }
    if (pos % sizeRonde == 0) {
      return pos/sizeRonde + 1;
      ;
    }
    else {
      int hulp = pos % sizeRonde;
      return atRonde(pos - hulp);
    }
  }
//*************************************************************************
  int Schema::atTafel(int pos) {
    if (pos == 0) {
      return 0;
    }
    if (pos % 4 == 0) {
      return pos/4;
    }
    else {
      int hulp = pos % 4;
      return atTafel(pos - hulp);
    }
  }
 



  /* if (pos % 4 == 1) {
    int t1 = getSpelerAt(schema, tafel, 1);
    tegenMatrix[speler][t1]--;
  }
  if (pos % 4 == 2) {
    int myMaat = getSpelerAt(schema, tafel, 0);
    int t1 = getSpelerAt(schema, tafel, 1);
    maatMatrix[speler][myMaat]++;
    tegenMatrix[speler][t1]--;
  }
  if (pos % 4 == 3) {
    int myMaat = getSpelerAt(schema, tafel, 1);
    int t1 = getSpelerAt(schema, tafel, 0);
    int t2 = getSpelerAt(schema, tafel, 2);
    maatMatrix[speler][myMaat]--;
    tegenMatrix[speler][t1]--;
    tegenMatrix[speler][t2]--;
  } */


bool Schema::isGeldigSchema(int pos, int schema[MaxGrootteSchema]) {
  for (int speler = 0; speler < nrSpelers; speler++) {
    if (aantalRondesGespeeld(speler, pos, schema) > atRonde(pos)) {
      return false;
    }
    if (maatGeweest(schema, speler, pos)) {
      return false;
    }
    if (tweedeKeerTegenGeweest(schema, speler, pos)) {
      return false;
    }
  }
  return true;
} //isGeldigSchema

/* Gebruiken bij het inlezen van een deelschema. Controleert ook parameters.
Functie zoekt door gehele array! */
bool Schema::isOngeldigSchema(int schema[MaxGrootteSchema])
{
  // Controleert of het aantal spelers bruikbaar is, binnen de grenzen van de opdracht,
  // en of het aantal rondes bruikbaar is.
  if (nrSpelers > MaxNrSpelers) {
  cerr << "Het maximum aantal spelers is 20." << endl;
  return true;
  }
  //Controleert het aantal rondes
  if (bijRonde > nrRondes) {
    cerr << "Het aantal rondes is niet bruikbaar." << endl;
    return true;
  }
  //Controleert of alle getallen in het deelschema geldige spelers voorstellen
  for (int i = 0; i < bijRonde * sizeRonde; i++) {
    int hulp = schema[i];
    ingedeeld.reserve(MaxGrootteSchema);
    ingedeeld.push_back(hulp);
    if (schema[i] >= nrSpelers) {
      cerr << "Dit schema heeft ongeldige speler(s) en kan niet worden gebruikt." << endl;
      return true;
    }
  }
  //Controleert of alle getallen samen geldig deelschema vormen.
  if (nrSpelers % 4 == 2 || nrSpelers % 4 == 3)  {
    cerr << "Dit schema heeft een ongeldig aantal spelers." << endl;
    return true;
  }
  //Controleert of iedere speler maximaal 1x per ronde voorkomt, 1x een speler
  //als maat heeft, 2x speler als tegenstander
  for (int speler = 0; speler < nrSpelers; speler++) {
    if (aantalRondesGespeeld(speler, (bijRonde * nrSpelers - 1), schema) > bijRonde) {
      cerr << "Speler " << speler << " komt meer dan 1x per ronde voor." << endl;
      return true;
    }
    if (maatGeweest(schema, speler, startPos)) {
      cerr << "Speler " << speler << " heeft 2x dezelfde maat." << endl;
      return true;
    }
    if (tweedeKeerTegenGeweest(schema, speler, startPos)) {
      cerr << "Speler " << speler << " heeft meer dan 2x dezelfde tegenstander." << endl;
      return true;
    }
  }
  return false;
} //isOngeldigSchema