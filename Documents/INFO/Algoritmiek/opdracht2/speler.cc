#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include "standaard.h"
#include "schema.h"
using namespace std;

Speler::Speler() {

};

Speler::Speler(int i) {
    id = i;
};

void Speler::vindMaten(int schema[MaxGrootteSchema], int id) {

    int atTafel;
    int totHier = startPos - 2;

  for (int i = 0; i <= totHier; i++) {
    if (i == 0) {
      atTafel = 0;
    }
    else {
      if (i % 4 == 0) {
        atTafel++;
      }
    } //else
    if (schema[i] == id) { //speler gevonden"
      int myMaat = getSpelerAt(schema, atTafel, (i + 2));
      //Komt deze speler al voor in de verzameling myMaten?

      auto addMaat = myMaten.insert(myMaat);
      } //if
    } //if
  } //for
;