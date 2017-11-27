#include <algorithm>
#include <string.h>
#include <stdexcept>
#include <sstream>
#include <ctype.h>
#include "encoder.h"

using namespace std;

typedef std::vector<letterUnit>::iterator vecIterator;
typedef std::vector<letterUnit> morseVector;
typedef treespc::bintree<codeUnit> morseTree;
typedef treespc::const_iterator<codeUnit> treeIterator;

const char MORSECODEFILE[] = "morsecodes.txt";
const int MORSECODELINE = 50;
const int FILEIN = 2;
const int FILEOUT = 3;
const string STREAMERRORMSG = "unable to open ";

void fillCode(morseVector &morsVector, morseTree &morsTree, const char);
bool readline(ifstream &fin, char *line, int linesize, char delim);
bool getValue(char &letter, string &code, ifstream &fin);
void encode(ifstream &fin, ofstream &fout, morseVector &morsVector);
void convertToCode(morseVector &morsVector, const char letter, string &code);
void setFileStream(ifstream &fin, ofstream &fout, const char *fileIn, const char *fileOut);
void getFileInStream(ifstream &fin, const char *fileName);
void getFileOutStream(ofstream &fout, const char *fileName);
void decode(ifstream &fin, ofstream &fout, morseTree &morsTree);

encoder::encoder() {}

void encoder::convert(char* argv[], char encodeChar) 
{
   char *fileIn = argv[FILEIN];
   char *fileOut = argv[FILEOUT];
   fillCode(vecMorseCode, treeMorseCode, encodeChar);
   setFileStream(fin, fout, fileIn, fileOut);
   if (encodeChar == 'E') 
   {
      encode(fin, fout, vecMorseCode);
   }
   else 
   {
      decode(fin, fout, treeMorseCode);
   }
}

void fillCode(morseVector &morsVector, morseTree &morsTree, const char encodeChar) 
{
   ifstream fin;
   getFileInStream(fin, MORSECODEFILE);
   char letter;
   string code;
   while (getValue(letter, code, fin)) 
   {
      if (encodeChar == 'E') 
      {
         letterUnit aLetterUnit = { letter, code};
         morsVector.push_back(aLetterUnit); 		
      }
      else 
      {	
         codeUnit aCodeUnit = { code, letter };
         morsTree.insert(aCodeUnit);
         morsTree.rebalance();
      }
   }
}

bool getValue(char &letter, string &code, ifstream &fin) 
{
   char line[MORSECODELINE];
   std::stringstream stream;
   if (readline(fin, line, MORSECODELINE, '\n')) 
   {
      string str = string(line);
      stream.clear();
      stream.str(str);
      return stream >> letter >> code;
   }
   else
      return false;	
}

void encode(ifstream &fin, ofstream &fout, morseVector &morsVector) 
{
   char inputLetter;
   string code;
   while(fin.get(inputLetter))
   {
      if(fin.good())
      {
         convertToCode(morsVector, inputLetter, code);
      }
      fout << code;
   }
   fout.close();
}

void convertToCode(morseVector &morsVector, const char letter, string &code) 
{
   if (!isalpha(letter)) 
   {
      code = letter;
   }
   else 
   {
      vecIterator itr = std::find(morsVector.begin(), morsVector.end(), letter);
      code = itr -> code;
      code.append(" ");	
   }
}

void decode(ifstream &fin, ofstream &fout, morseTree &morsTree) 
{
   string code;
   char inputLetter;
   while (fin.get(inputLetter)) 
   {
      if (inputLetter == '*' || inputLetter == '-') 
      {
         code.push_back(inputLetter);
      }
      else if (code == "") 
      {
         fout << inputLetter;
      }
      else 
      {
         codeUnit aCode = { code };
         treeIterator itr = morsTree.find(aCode);
         fout << itr -> letter;
         code = "";
      }
   }
   fout.close();
}

bool readline(ifstream &fin, char *line, int linesize, char delim)
{
   if (fin.eof()) return false;
   fin.getline(line, linesize, delim);
   if (!fin.good()) return false;
   int last = strlen(line) - 1;
   if (line >= 0 && line[last] == '\r') line[last] = '\0';
   return true;
}

void setFileStream(ifstream &fin, ofstream &fout, const char *fileIn, const char *fileOut) 
{
   getFileInStream(fin, fileIn);
   getFileOutStream(fout, fileOut);
}

void getFileOutStream(ofstream &fout, const char *fileName) 
{
   fout.open(fileName);
   if (!fout) 
   {
      string errorMsg =  STREAMERRORMSG;
      throw std::runtime_error(errorMsg.append(fileName));
   }
}

void getFileInStream(ifstream &fin, const char *fileName) 
{
   fin.open(fileName);
   if(!fin) 
   {
      string errorMsg =  STREAMERRORMSG;
      throw std::runtime_error(errorMsg.append(fileName));
   }
}

encoder::~encoder()
{
   vecMorseCode.clear();
}




