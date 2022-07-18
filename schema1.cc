// Implementatie van klasse Schema

#include <iostream>
#include <fstream>
#include "standaard.h"
#include "schema.h"
using namespace std;

//*************************************************************************

/* Hier initialiseer ik variabelen en matrixen om het e.e.a. bij te houden
 */
Schema::Schema ()
{
  this->nrSpelers = 0; // TODO: value
  this->nrRondes = 0; // TODO: value.
  
}  // default constructor

//*************************************************************************

Schema::Schema (int nwNrSpelers)
{

// TODO: implementeer deze constructor
this->nrSpelers = nwNrSpelers;
this->nrRondes = 0; // TODO

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
  //if (invoernaam >= 30 {
    //cerr << "De naam van het bestand is te groot. Een bestandsnaam mag maximaal 30 karakters zijn." <, endl;
    //return false;
 // })

  invoer >> nrSpelers >> atRonde;
  nrRondes = (nrSpelers - 1);
  myArray = ((nrRondes * nrSpelers)-1); //-1  omdat index bij nul begint

  
  /* Controleert of het aantal spelers bruikbaar is, binnen de grenzen van 
  de opdracht, en of het aantal rondes bruikbaar is.  */
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

  /* Leest het ingevoerde schema in */
  for (int ronde = 0; ronde < atRonde; ++ronde) 
  {
    for (int spelers = 0; spelers < nrSpelers; ++spelers) 
    {
      const int i = ronde * nrSpelers + spelers; 
      invoer >> totSchema[i];
      cout<< totSchema[i];
    }
  }

  /* Controleert of alle getallen in het deelschema geldige spelers 
  voorstellen */
  for (int i = 0; i < myArray; i++) 
  {
    if (totSchema[i] >= nrSpelers) 
    {
      cout << "Dit schema heeft ongeldige speler(s) en kan niet worden gebruikt." << endl;
      return false;
    }
  }
  /*Controleert of alle getallen samen geldig deelschema vormen. */
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

  //Initialiseert aantal tafels bij schema
  if (nrSpelers % 4 == 0)
  {
    nrTafels = ((nrSpelers / 4) * nrRondes);
  }
  else
  {
    int spelerCorr = nrSpelers - 1;
    nrTafels = ((spelerCorr / 4) * nrRondes);
  }
   
  maatMatrixMaken();
  vrijGeweestMaken();
  tegenstanderGeweestMaken();

  return true;
}  // leesInDeelschema

//*************************************************************************

void Schema::drukAfSchema (int totSchema[MaxGrootteSchema])
{ 
  for (int ronde = 0; ronde < nrRondes; ++ronde) 
  {
    for (int spelers = 0; spelers < nrSpelers; ++spelers) 
    {
      cout << totSchema[MaxGrootteSchema] << endl;
      cout << endl;
    }
  cout << endl;
  }
  initAll(); //Datastructuren en variabelen initialiseren.
  maatGeweest();
  vrijGeweest();
  tegenstanderGeweest();

}
  // drukAfSchema

//***************************** ************** *****************************

void Schema::addSpeler () 
{ 
 
}

bool Schema:: bepaalSchemaBT (int schema[MaxGrootteSchema],
                           long long &aantalDeelschemas)
{ 
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

void Schema::initAll()
{ }

int* Schema::getRonde(int ronde)
{
  return &totSchema[ronde * getWidth()]; 
}

//*************************************************************************

int Schema::getPlayerPosition(int ronde, int pos) //De posities zijn vast, maar de speler op de positie wisselt
{
  return (this->getRonde(ronde))[pos]; 
}

//*************************************************************************

int Schema::getWidth()
{
  return nrSpelers; //breedte van de ronde en dus schema is aantal spelers = aantal kolommen in de matrix
}

//*************************************************************************

int Schema::getHeight()
{
  return nrRondes; //Aantal rijen in de matrix
}

//*************************************************************************

//Telt hoe veel rondes een speler heeft gespeeld
int Schema::aantalRondesGespeeld(int speler)
{
  int teller = 0; 
  for (int i = 0; i < (atRonde * nrSpelers); i++)
  {
    if (totSchema[i] == speler)
    {
      teller++;
    }
  }
  return teller;
}

// [a b c d a2 b2 c2 d2 ...]
// getTafel(^^, 0) -> [a b c d ....]
// getTafel(^^, 1) -> [a2 b2 c2 d2 ...]

// schema[2] -> "waarde van het 3e element!"
// &schema[2] -> "adres van het 3e element"

//*************************************************************************

// Geeft het beginpunt van de gegeven tafel.
int* Schema::getTafel(int schema[MaxGrootteSchema], int tafelIx)
{
  return &totSchema[(tafelIx * 4)];
}

//*************************************************************************

// Geeft de speler aan een tafel op de gegeven positie.
int Schema::getSpelerAt(int schema[MaxGrootteSchema], int tafelIx, int spelerPos)
{
  int* tafel = getTafel(totSchema, tafelIx);
  return tafel[spelerPos % 4];                    //Door modulus te nemen kijkt functie nooit voorbij een tafel 
}

//*************************************************************************

int Schema::maatMatrixMaken() //Matrix intializeren voor bijhouden of spelers met elkaar hebben gespeeld
{
    size_t M = MaxNrSpelers; //Zo groot als gegeven constante
    const int waarde = 0;
    int maat[M][M];
    std::fill(*maat, *maat + M*M, waarde);  //Vul de matrix met nullen
    return 0;
}

//*************************************************************************

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

//*************************************************************************

int Schema::tegenstanderGeweestMaken()
{
  size_t M = nrRondes;
  const int waarde = 0;
  int tegen[M][M];
  std::fill(*tegen, *tegen + M*M, waarde);
  return 0;
}

//*************************************************************************

/*/ Vult een matrix in die bijhoudt welke spelers samen hebben gespeeld.
maat[2][3] = 1 betekent dat spelers 2 en 3 samen hebben gespeeld. /*/
void Schema::maatGeweest()
{
  cout << endl;
  for (int i = 0; i < nrSpelers; i++)
    {
      maat[i][i] = 1;               //In feite ben je altijd je eigen partner
    }
  for (int j = 0; j < myArray; j++) //Loop de lengte van het ingelezen schema af (de 1D array)
    {    
    maat[(totSchema[j])][(totSchema[(j+2)])] = 1;  //Zet een 1 in de matrix indien een paar maten voorkomt in schema. NAGAAN WERKT NIET GEEN REKENING MET TAFELS GEHOUDEN.
    }
  //Loopt over alle posities en print waardes TEST
  for (int rij = 0; rij < nrSpelers; rij++) 
  { 
    for (int kolom = 0; kolom < nrSpelers; ++kolom) 
    {
      cout << maat[kolom][rij] << ' ';
    }
    cout << endl;
  }
}

//*************************************************************************

/*/ Vult in op de diagonaal van een matrix of een speler een ronde vrij is geweest. 
    Wordt alleen uitgevoerd wanneer nrSpelers % 4 == 1                          /*/
void Schema::vrijGeweest()
{
  if (nrSpelers % 4 == 1)
  {
    for (int i = 0; i < myArray; i++)
    {
      for (int j = 0; j < nrSpelers; j++)
      {
        if ((aantalRondesGespeeld(j)) == (nrRondes -1))
        {
        vrij[j][j] = 1;
        }
      }
    }
  
  //PRINT WAARDES TEST
    for (int rij = 0; rij < nrSpelers; rij++) 
    { cout << endl;
      cout << "VRIJ GEWEEST?" << endl;
      for (int kolom = 0; kolom < nrSpelers; ++kolom) 
      {
        cout << vrij[kolom][rij] << ' ';
      }
      cout << endl;
    }
  }
}

//*************************************************************************

/*/ Vult de matrix die bijhoudt hoe vaak spelers tegen elkaar hebben gespeeld.
tegen[4][7] = 2 betekent dat spelers 4 en 7 tweemaal samen hebben gespeeld. /*/
void Schema::tegenstanderGeweest()
{
  cout << endl;
  cout << "TEGENSTANDERS GEWEEST?" << endl;
  for (int i = 0; i < nrSpelers; i++)
  {
    tegen[i][i] = 2;      //Identiteitsmatrix van maken
  }
  for (int tafel = 0; tafel < nrTafels; tafel++)
  {
   for (int pos = 0; pos < 4; pos++)
   {
     int ik = getSpelerAt(totSchema, tafel, pos);
     int t1 = getSpelerAt(totSchema, tafel, (pos + 1));
     int t2 = getSpelerAt(totSchema, tafel, (pos + 3));
     tegen[ik][t1]++;
     tegen[ik][t2]++;
   }
   cout << endl;
  }
  //Loopt over alle posities en print waardes TEST
  for (int rij = 0; rij < nrSpelers; rij++) 
  { 
    for (int kolom = 0; kolom < nrSpelers; kolom++) 
    {
      cout << tegen[kolom][rij] << ' ';
    }
    cout << endl;
  }
}
