#include <ctype.h>
#include <string.h>
#include <stdexcept>
#include "encoder.h"

using namespace std;

const int ENCODECHAR = 1;

int main(int argc, char* argv[])
{
   char upperEncodeChar = toupper(*argv[ENCODECHAR]);
   int encodeCharLength = strlen(argv[ENCODECHAR]);
   try 
   {
      if (argc != 4) 
      {
         throw runtime_error("syntax: program e|d filein fileout");
      }
      else if (encodeCharLength != 1) 
      {
         throw runtime_error("single character for encode character");
      }
      else if (upperEncodeChar != 'E' && upperEncodeChar != 'D') 
      {
         throw runtime_error("encode character should be 'd' or 'e'");
      }
      encoder newEncoder;
      newEncoder.convert(argv, upperEncodeChar);
   }
   catch (exception &ex) 
   {
      cout << "Error: " << ex.what() << endl;
   }
   return 0;
}
