// Implementatie van klasse Schema

#include <iostream>
#include <fstream>
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
    nrRondes = nwNrSpelers - 1; //checken
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
  atTafel = 0;
  putHere = 0;
  mijnPlek = 0;

  drukAfSchema(schema);
  maatGeweest(schema);
  vrijGeweest(schema);
  tegenstanderGeweest(schema);  
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
  nrRondes = (nrSpelers - 1);
  myArray = (nrRondes * nrSpelers); //-1 belangrijk omdat index bij nul begint.

  // Controleert of het aantal spelers bruikbaar is, binnen de grenzen van de opdracht,
  // en of het aantal rondes bruikbaar is. Initialiseert nrRondes = maximum rondes

  if (nrSpelers > MaxNrSpelers) 
  { 
    cout << "Het aantal spelers is niet bruikbaar. Er kunnen maximaal 20 spelers zijn voor dit programma." << endl;
    return false;
  }
  if (atRonde >= nrRondes) 
  {
    cout << "Het aantal rondes is niet bruikbaar. Het aantal rondes is maximaal het aantal spelers - 1." << endl;
    return false;
  }

 //Leest het ingevoerde schema in
  for (int ronde = 0; ronde < atRonde; ++ronde) 
  {
    for (int spelers = 0; spelers < nrSpelers; ++spelers) 
    {
      mijnPlek = (ronde * nrSpelers + spelers);
      invoer >> schema[mijnPlek];
    }
  }

  //Controleert of alle getallen in het deelschema geldige spelers voorstellen
  for (int i = 0; i < myArray; i++) {
    if (schema[i] >= nrSpelers) {
      cout << "Dit schema heeft ongeldige speler(s) en kan niet worden gebruikt." << endl;
      return false;
    }
  }
  //Controleert of alle getallen samen geldig deelschema vormen.
  if (nrSpelers % 4 == 2 || nrSpelers % 4 == 3)  {
    cout << "Dit schema heeft een ongeldig aantal spelers." << endl;
    return false;
  }
  //Controleert of iedere speler maximaal 1x per ronde voorkomt
  for (int speler = 0; speler < nrSpelers; speler++)
  {
    if (aantalRondesGespeeld(speler) > atRonde)
    {
      cout << "Dit schema heeft speler(s) die meer dan 1x per ronde voorkomen." << endl;
      return false;
    }
  }

  //Initialiseert aantal tafel bij schema
  if (nrSpelers % 4 == 0)
  {
    nrTafels = ((nrSpelers / 4) * nrRondes);
    atTafel = ((nrSpelers / 4) * atRonde);
  }
  else
  {
    int spelerCorr = nrSpelers - 1;
    nrTafels = ((spelerCorr / 4) * nrRondes);
    atTafel = ((spelerCorr / 4) * atRonde);
  }
  putHere = (atRonde * nrSpelers);

  maatGeweest(schema);
  vrijGeweest(schema);
  tegenstanderGeweest(schema);
  drukAfSchema(schema);
  
  return true;
}  // leesInDeelschema

//*************************************************************************

void Schema::drukAfSchema (int schema[MaxGrootteSchema])
{
  for (int ronde = 0; ronde < nrRondes; ++ronde) 
  {
    for (int spelers = 0; spelers < nrSpelers; ++spelers) 
    {
      mijnPlek = ((ronde * nrSpelers) + spelers);
      cout << schema[mijnPlek] << ' ';
      //Einde van iedere tafel wordt gemarkeerd met een |
      if ((mijnPlek + 1) % 4 == 0)
      { 
        cout << "| ";
      }
      //Einde van iedere ronde wordt gemarkeerd met een linebreak
      if ((mijnPlek + 1) % nrSpelers == 0)
      {
        cout << endl;
      } 
    }
  }
  cout << "maatMatrix" << endl;
  for (int rij = 0; rij < nrSpelers; rij++) 
  { 
    for (int kolom = 0; kolom < nrSpelers; kolom++) 
    {
      cout << maat[kolom][rij] << ' ';
    }
    cout << endl;
  }
  cout << "tegenMatrix" << endl;
  for (int r = 0; r < nrSpelers; r++) 
  { 
    for (int kol = 0; kol < nrSpelers; kol++) 
    {
      cout << tegen[kol][r] << ' ';
    }
    cout << endl;
  }
}
  

  // drukAfSchema

//***************************** ************** *****************************

/*/ Deze functie voegt spelers toe van 0 tot 7 op posities 0 tot 7.
putHere wordt geinitialiseerd bij inlezen van een schema /*/
void Schema::addSpeler (int schema[MaxGrootteSchema])
{
  schema[putHere] = speler; //zet een speler erin
  speler = ((speler + 1) % nrSpelers);
  maatGeweest(schema); //Deze functies roep ik aan zodat de waardes worden bijgewerkt
  tegenstanderGeweest(schema);
  vrijGeweest(schema);
  putHere++;
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
bool Schema:: bepaalSchemaBT (int schema[MaxGrootteSchema],
                           long long &aantalDeelschemas)
{
    addSpeler(schema);
    aantalDeelschemas++;
    if (isOngeldigSchema()) //als het schema niet geldig is
    {putHere--;             //blijven we op dezelfde plek
    addSpeler(schema);}     //en voegen speler+1 toe
    if (!isOngeldigSchema())
    {return true;}
    else {return false;}
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

int* Schema::getRonde(int schema[MaxGrootteSchema], int rondeIx, int nrSpelers)
{
  return &schema[(rondeIx * nrSpelers)]; 
}

int Schema::getPlekje(int schema[MaxGrootteSchema], int rondeIx, int nrSpelers, int spelerPos)
{
  int* plekje = getRonde(schema, rondeIx, nrSpelers);
  return plekje[spelerPos];
}


//Telt hoe veel rondes een speler heeft gespeeld
int Schema::aantalRondesGespeeld(int speler)
{
  int teller = 0; 
  for (int i = 0; i < (atRonde * nrSpelers); i++)
  {
    if (schema[i] == speler)
    {
      teller++;
    }
  }
  return teller;
}

/* Deze functie zal het beginpunt van tafel n in totSchema aangeven.
Let op: returnt een pointer, dus gebruik in combi met getSpelerAt vooral. */
int* Schema::getTafel(int schema[MaxGrootteSchema], int tafelIx)
{
  return &schema[(tafelIx * 4)];
}

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

int Schema::maatMatrixMaken() //Matrix intializeren voor bijhouden of spelers met elkaar hebben gespeeld
{
    size_t M = MaxNrSpelers; //Zo groot als gegeven constante
    const int waarde = 0;
    int maat[M][M];
    std::fill(*maat, *maat + M*M, waarde);  //Vul de matrix met nullen
    return 0;
}

int Schema::vrijGeweestMaken() //Matrix intializeren voor bijhouden of speler ronde vrij is geweest
{
  if (nrSpelers % 4 == 1) //Relevant wanneer aantal deelnemers gelijk is aan 1 modulo 4
  {
    size_t M = nrRondes;       
    const int waarde = 0;
    int vrij[M][M];
    std::fill(*vrij, *vrij + M*M, waarde);
    return 0;
  }
  return 0;                           
}

int Schema::tegenstanderGeweestMaken()
{
  size_t M = nrRondes;
  const int waarde = 0;
  int tegen[M][M];
  std::fill(*tegen, *tegen + M*M, waarde);
  return 0;
}

void Schema::maatGeweest(int schema[MaxGrootteSchema])  // maatMatrix correct invullen op basis van schema
{
  for (int tafel = 0; tafel < nrTafels; tafel++)
  {
   for (int pos = 0; pos < 4; pos++)
   {
     int ik = getSpelerAt(schema, tafel, pos);
     int partner = getSpelerAt(schema, tafel, (pos + 2));
     maat[ik][partner]++;
   }
  }
  for (int i = 0; i < nrSpelers; i++)
  {
    maat[i][i] = 1;
  }
}

void Schema::vrijGeweest(int schema[MaxGrootteSchema])
{
  if (nrSpelers % 4 == 1) // Voer alleen uit als er een speler vrij moet zijn in een ronde
  {
    for (int j = 0; j < nrSpelers; j++) //Kijkt voor iedere speler
    {
      if ((aantalRondesGespeeld(j)) == (nrSpelers-2)) //of deze speler het aantal rondes - 1 maal heeft gespeeld.
      {
      vrij[j][j]++; //Indien waar, zet een 1 op de diagonaal van de matrix
      }
    }
  }
}

void Schema::tegenstanderGeweest(int schema[MaxGrootteSchema])
{
  //Loopt door posities van alle tafels
  for (int tafel = 0; tafel < nrTafels; tafel++)
  {
   for (int pos = 0; pos < 4; pos++)
   {
     int ik = getSpelerAt(schema, tafel, pos);
     int t1 = getSpelerAt(schema, tafel, (pos + 1));
     int t2 = getSpelerAt(schema, tafel, (pos + 3));
     tegen[ik][t1]++;
     tegen[ik][t2]++;
   }
  }
  //Op de diagonaal wil ik 2 zetten omdat je nooit je
  //eigen tegenstander bent
  for (int i = 0; i < nrSpelers; i++)
  {
    tegen[i][i] = 2;      
  }
}    

/* Deze functie kijkt of er max. 1x met iemand gespeeld
max. 2x tegen iemand, en of iedere speler max. 1 ronde vrij is. */
bool Schema::isOngeldigSchema()
{
  //Loop over alle kolommen en rijen
  for (int kolom = 0; kolom < nrSpelers; kolom++) 
  {
    for (int rij = 0; rij < nrRondes; rij++)
    {
      if (maat[kolom][rij] == 2) //Heeft een speler meer dan 1x met iemand gespeeld?
      { return true;}
      if (tegen[kolom][rij] == 3)  //Heeft een speler meer dan 2x tegen iemand gespeeld?
      { return true; }
      if (vrij[kolom][rij] == 2) //Is een speler 2 rondes vrij geweest?
      { return true; }
    }
  }
  return false;
}