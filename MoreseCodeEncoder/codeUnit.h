#ifndef CODEUNIT_H_INCLUDED
#define CODEUNIT_H_INCLUDED

#include <string>

struct codeUnit 
{	
   std::string code;
   char letter;

   bool operator == (const codeUnit &other) const
   {
      return code == other.code;
   }

   bool operator != (const codeUnit &other) const
   {
      return code != other.code;
   }

   bool operator < (const codeUnit &other) const
   {
      return code < other.code;
   }

   bool operator > (const codeUnit &other) const
   {
      return code > other.code;
   }
};

#endif
