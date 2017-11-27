#ifndef ENCODER_H
#define ENCODER_H
#include <vector>
#include <iostream>
#include <fstream>
#include "bintree.h"
#include "letterUnit.h"
#include "codeUnit.h"

using namespace std;

class encoder
{
   private:
      vector<letterUnit> vecMorseCode;
      treespc::bintree<codeUnit> treeMorseCode;
      ifstream fin;
      ofstream fout;
   public:
      encoder();
      void convert(char* argv[], char encodeChar); 
      ~encoder();
};

#endif
