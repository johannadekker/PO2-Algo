// Implementatie van klasse Schema

#include <iostream>
#include <fstream>
#include <unordered_set>
#include "standaard.h"
#include "schema.h"
using namespace std;

//*************************************************************************

Schema::Schema ()
{

// TODO: implementeer zo nodig deze constructor
this->nrSpelers = 0; // TODO: value
this->nrRondes = 0; // TODO: value.

}  // default constructor

//*************************************************************************

Schema::Schema (int nwNrSpelers)
{
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

  myArray = (nrRondes * nwNrSpelers);
  nrSpelers = nwNrSpelers;
  atRonde = 0;
  nowAtTafel = 0;
  putHere = 0;
  mijnPlek = 0;

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
  invoer >> nrSpelers >> atRonde;
  if (!(nrSpelers % 4 == 0)) {
    nrRondes = nrSpelers;
    }
  else {
    nrRondes = nrSpelers-1;
  }
  myArray = (nrRondes * nrSpelers);

 //Leest het ingevoerde schema in
 for (int i = 0; i < (nrSpelers * atRonde); i++) {
   invoer >> schema[i];
 }

  if (nrSpelers % 4 == 0)
  {
    nrRondes = nrSpelers-1;
    nrTafels = ((nrSpelers / 4) * nrRondes);
    nowAtTafel = ((nrSpelers / 4) * atRonde);
    putHere = nrSpelers * atRonde;

  }
  else
  {
    int spelerCorr = nrSpelers - 1;
    nrRondes = nrSpelers;
    nrTafels = ((spelerCorr / 4) * nrRondes);
    nowAtTafel = ((spelerCorr / 4) * atRonde);
    putHere = (spelerCorr * atRonde);
  }
  //Controle
  if (isOngeldigSchema()){
    return false;
  }
  drukAfSchema(schema);
  return true;
}  // leesInDeelschema

//*************************************************************************

bool Schema::isGeldigSchema() {
  for (int speler = 0; speler < nrSpelers; speler++) {
    if (aantalRondesGespeeld(speler) > atRonde) {
      cerr << "Speler " << speler << " komt meer dan 1x per ronde voor." << endl;
      return false;
    }
    if (maatGeweest(schema, speler, putHere)) {
      cerr << "Speler " << speler << " heeft 2x dezelfde maat." << endl;
      return false;
    }
    if (tweedeKeerTegenGeweest(schema, speler, putHere)) {
      cerr << "Speler " << speler << " heeft meer dan 2x dezelfde tegenstander." << endl;
      return false;
    }
  }
  return true;
} //isGeldigSchema

bool Schema::isOngeldigSchema()
{
  // Controleert of het aantal spelers bruikbaar is, binnen de grenzen van de opdracht,
  // en of het aantal rondes bruikbaar is. Initialiseert nrRondes = maximum rondes
  if (nrSpelers > MaxNrSpelers) {
  cerr << "Het maximum aantal spelers is 20." << endl;
  return true;
  }
  //Controleert het aantal rondes
  if (atRonde >= nrRondes) {
    cerr << "Het aantal rondes is niet bruikbaar." << endl;
    return true;
  }
  //Controleert of alle getallen in het deelschema geldige spelers voorstellen
  for (int i = 0; i < myArray; i++) {
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
  //Controleert of iedere speler maximaal 1x per ronde voorkomt
  for (int speler = 0; speler < nrSpelers; speler++) {
    if (aantalRondesGespeeld(speler) > atRonde) {
      cerr << "Speler " << speler << " komt meer dan 1x per ronde voor." << endl;
      return true;
    }
    if (maatGeweest(schema, speler, putHere)) {
      cerr << "Speler " << speler << " heeft 2x dezelfde maat." << endl;
      return true;
    }
    if (tweedeKeerTegenGeweest(schema, speler, putHere)) {
      cerr << "Speler " << speler << " heeft meer dan 2x dezelfde tegenstander." << endl;
      return true;
    }
  }
  return false;
} //isOngeldigSchema

//*************************************************************************

void Schema::drukAfSchema (int schema[MaxGrootteSchema]) {
  for (int i = 0; i < MaxGrootteSchema; i++) {
    cout << schema[i] << ' ';
    if ((i + 1) % 4 == 0) {
      cout << "| ";
    }
    if ((i + 1) % nrSpelers == 0) {
      cout << endl;
    }
  }
} // drukAfSchema

//************************************************************************

/*/ Deze functie voegt spelers toe van 0 tot 7 op posities 0 tot 7.
putHere wordt geinitialiseerd bij inlezen van een schema /*/
void Schema::addSpeler (int i, int pos, int schema[MaxGrootteSchema])
{
  schema[pos] = i; //zet een speler erin
}

void Schema::deleteSpeler(int schema[MaxGrootteSchema]) {
  schema[putHere] = 0;
}

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
bool Schema:: bepaalSchemaBT (int schema[MaxGrootteSchema],long long &aantalDeelschemas) {
  int* schema;
  for (int i = putHere; i < myArray; i++) {
    if (i == myArray - 1) {
      drukAfSchema(schema);
      return true;
    }
    else {
        for (int speler = 0; speler < nrSpelers; speler++) {
          schema[i] = speler;
          cout << schema[i] << endl;
          cout << "i is " << i << endl;
          cout << "pos is " << putHere <<endl;
          aantalDeelschemas++;
          if (isGeldigSchema()) {
            putHere++;
            bepaalSchemaBT(schema, aantalDeelschemas);
          } //if
          else {//ongeldig schema
            break;
          }
        }
      } //else
  } //for
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
int Schema::aantalRondesGespeeld(int speler)
{
  int teller = 0;
  for (int i = 0; i < (atRonde * nrSpelers); i++) {
    if (schema[i] == speler)  {
      teller++;
    }
  }
  return teller;
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

bool Schema::maatGeweest(int schema[MaxGrootteSchema], int speler, int putHere)  // maatMatrix correct invullen op basis van schema
{
  int atTafel;
  int totHier = putHere - 2;
  for (int i = 0; i <= totHier; i++) {
    if (i == 0) {
      atTafel = 0;
    }
    else {
      if (i % 4 == 0) {
        atTafel++;
      } 
    } //else
    if (schema[i] == speler) { //speler gevonden
      int myMaat = getSpelerAt(schema, atTafel, (i + 2));
      //Komt deze speler al voor in de verzameling myMaten?
      auto addMaat = myMaten.insert(myMaat);
      if(addMaat.second == false) { 
        myMaten.clear(); //clear cache
        return true;
      } //if
    } //if
  } //for
  myMaten.clear(); //clear cache
  return false; 
} //maatGeweest

//*************************************************************************
/* Deze functie zoekt de speler in het schema. Wanneer de speler is gevonden,
worden de tegenstanders gevonden met de functie getSpelerAt. Deze tegen-
standers worden in de multiset myTegenstanders geplaatst. 

INPUT: een schema, en een speler

OUTPUT:
- TRUE wanneer de verzameling tegenstanders meer dan 2x hetzelfde element bevat
- FALSE wanneer de verzameling tegenstanders max. 2x hetzelfde element bevat
  na zoeken door het gehele schema. */

bool Schema::tweedeKeerTegenGeweest(int schema[MaxGrootteSchema], int speler, int putHere)
{
  int atTafel = 0;
  int totHier = putHere - 3;
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
      }
  } //for
  myTegenstanders.clear();
  return false;
} //tweedeKeerTegenGeweest

//*************************************************************************
