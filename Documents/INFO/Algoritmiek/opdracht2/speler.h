// Definitie van klasse Speler

#ifndef SpelerHVar  // voorkom dat dit bestand meerdere keren
#define SpelerHVar  // ge-include wordt

#include "constantes.h"
#include "schema.h"
#include <unordered_set>
#include <vector>

class Speler : public Schema 
{
  public:
    Speler();

    int id;
    std::unordered_set <int> myMaten;
    std::unordered_multiset <int> myTegenstanders;
    std::unordered_set <int> vrijGeweest;

    Speler(int i);
    void vindMaten(int schema[MaxGrootteSchema], int id);
    
};
#endif