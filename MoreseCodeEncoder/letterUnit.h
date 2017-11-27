#ifndef LETTERUNIT_H_INCLUDED
#define LETTERUNIT_H_INCLUDED

#include <string>
struct letterUnit 
{
   char letter;
   std::string code;

   bool operator == (const char inputLetter) 
   {
      return letter == inputLetter;
   }
};

#endif
