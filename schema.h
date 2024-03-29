// Definitie van klasse Schema

#ifndef SchemaHVar  // voorkom dat dit bestand meerdere keren
#define SchemaHVar  // ge-include wordt

#include "constantes.h"
#include <unordered_set>

class Schema
{ public:

    // Default constructor
    Schema ();

    // Constructor met parameter
    // Controleer of de parameter nwNrSpelers een bruikbaar aantal spelers
    // is, binnen de grenzen van de opdracht.
    Schema (int nwNrSpelers);

    // Lees een deelschema, bestaande uit een geheel aantal rondes,
    // in uit invoernaam. De invoer bestaat uit
    // * een regel met twee getallen: het aantal spelers en het aantal rondes
    // * voor elke ronde (in hun volgorde in het deelschema, dus ronde 0,
    //   ronde 1, enzovoort) een regel met de spelers die in die ronde zijn
    //   ingedeeld (eveneens in de volgorde van het deelschema
    // Getallen op dezelfde regel worden gescheiden door enkele spaties.
    // Controleer of
    // * het bestand invoernaam te openen is
    // * het aantal spelers bruikbaar is, binnen de grenzen van de opdracht
    // * het aantal rondes bruikbaar is
    // * alle getallen in het deelschema geldige spelers voorstellen en samen
    //   een geldig deelschema vormen. HIERBIJ HOEFT NIET OP SYMMETRIE
    //   GECONTROLEERD TE WORDEN.
    // Retourneer:
    // * true, als alle controles goed uitpakken.
    //   In dat geval is alle ingelezen informatie in het object opgeslagen.
    // * false, anders
    bool leesInDeelschema (const char* invoerNaam);

    // Druk parameter schema overzichtelijk af op het scherm.
    // Pre:
    // * membervariabele nrSpelers heeft een bruikbare waarde
    // * parameter schema bevat een compleet schema dat past bij nrSpelers
    void drukAfSchema (int schema[MaxGrootteSchema]);

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
    bool bepaalSchemaBT (int schema[MaxGrootteSchema],
                         long long &aantalDeelschemas);

    // Bepaal met behulp van backtracking een geldig schema voor het huidige
    // aantal spelers, met een zo klein mogelijke `waarde'.
    // Als er een deelschema van een aantal rondes is ingelezen, bouw
    // dan daarop verder.
    // Als parameter bouwWaardeOp = true, wordt de waarde van het schema
    // al opgebouwd tijdens het opbouwen van het schema zelf, zodat je kunt
    // backtracken als de waarde van het huidige deelschema al slechter is
    // dan de waarde van het beste complete schema tot nu toe.
    // Als parameter bouwWaardeOp = false, wordt de waarde van het schema
    // pas berekend als er een compleet geldig schema is.
    // Retourneer:
    // * true, als het lukt om een schema te bepalen
    // * false, als het niet lukt om een schema te bepalen
    // Pre:
    // * membervariabele nrSpelers heeft een bruikbare waarde
    // Post:
    // * als het lukt om een geldig schema te bepalen, bevat parameter `schema'
    //   een schema met een minimale `waarde'. Alle rondes zitten daar dan
    //   achter elkaar, beginnend op positie 0 van het array.
    // * aantalDeelschemas is gelijk aan het aantal deelschemas dat we
    //   hebben gezien bij het bepalen van een minimaal schema
    bool bepaalMinSchema (int schema[MaxGrootteSchema],
                          long long &aantalDeelschemas, bool bouwWaardeOp);

    // Bepaal op een gretige manier een schema voor het huidige aantal
    // spelers. Ofwel:
    // * Vul het schema positie voor positie.
    // * Kies bij elke positie een speler die `zo goed mogelijk'
    //   aan de eisen voor een schema voldoet.
    // * Herzie nooit een eerder gemaakte keuze
    // Als er een deelschema van een aantal rondes is ingelezen, bouw
    // dan daarop verder.
    // Als het niet lukt om aan alle eisen voor een geldig schema te voldoen,
    // BEPAAL DAN TOCH EEN COMPLEET SCHEMA, dat `zo goed mogelijk' aan
    // de eisen voldoet.
    // Pre:
    // * membervariabele nrSpelers heeft een bruikbare waarde
    // Post:
    // * parameter `schema' bevat een compleet schema voor het huidige
    //   aantal spelers
    void bepaalSchemaGretig (int schema[MaxGrootteSchema]);




  private:
    /* Toegevoegde functies: */

    int opPlek(int rondeIx, int nrSpelers, int spelerIx);
    int* getRonde(int schema[MaxGrootteSchema], int rondeIx, int nrSpelers);
    int getPlekje(int schema[MaxGrootteSchema], int rondeIx, int nrSpelers, int spelerPos);
    int aantalRondesGespeeld(int speler);
    int* getTafel(int schema[MaxGrootteSchema], int tafelIx);

    /* Geeft de speler aan een tafel op de gegeven positie */
    int getSpelerAt(int schema[MaxGrootteSchema], int tafelIx, int spelerPos);

    void addSpeler (int i, int pos, int schema[MaxGrootteSchema]);
    void deleteSpeler(int schema[MaxGrootteSchema]);
    bool maatGeweest(int schema[MaxGrootteSchema], int speler, int putHere);
    bool tweedeKeerTegenGeweest(int schema[MaxGrootteSchema], int speler, int putHere);

    std::unordered_set <int> myMaten;
    std::unordered_multiset <int> myTegenstanders;
    std::unordered_set <int> vrijGeweest;


    bool isOngeldigSchema();
    bool isGeldigSchema();
    bool* isGeldig(int schema[MaxGrootteSchema]);
    bool* isOngeldig(int schema[MaxGrootteSchema]);


    int nrSpelers;       // aantal spelers bij dit schema
    int nrRondes;        // aantal rondes bij dit schema
    int atRonde;         // ronde waar schema nu is
    int nrTafels;        // aantal tafels bij dit schema
    int nowAtTafel;
    int myArray;         // maat van de array bij dit schema;
    int mijnPlek;        // geeft de juiste index als int om te zoeken in array
    int putHere;
    int schema[MaxGrootteSchema];
    int start;


// TODO: uw eigen private membervariabelen

};

#endif
