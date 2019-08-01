#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

void MakeAllLowerCase(string& word);

int main()
{
   HashTable hTab;
   cout << "capacity initially: " << hTab.cap() << endl;
   cout << "used initially:     " << hTab.size() << endl;
   char dictOption;
   cout << "select dictionary (s = small, others = big): ";
   cin >> dictOption;
   cin.ignore(9999, '\n');
   ifstream fin;
   if (dictOption == 's' || dictOption == 'S')
      fin.open("dict0.txt", ios::in);
   else
      fin.open("dict1.txt", ios::in);
   if ( fin.fail() )
   {
      cerr << "Failed to open dictionary file "
           << ( (dictOption == 's') ? "dict0.txt" : "dict1.txt" ) << "..."
           << "\nMake dictionary files accessible and try again ..." << endl;
      exit(EXIT_FAILURE);
   }
   clock_t begLoad;   // for timing hashtable load
   clock_t endLoad;   // for timing hashtable load
   string oneWord;    // holder for word
   cout << "loading dictionary . . ." << endl;
   begLoad = clock();
   fin >> ws;
   while ( ! fin.eof() )
   {
      fin >> oneWord;
      if ( ! hTab.exists(oneWord) ) hTab.insert(oneWord);
      fin >> ws;
   }
   fin.close();
   endLoad = clock() - begLoad;
   cout << "dictionary loaded in "
        << (double)endLoad / ((double)CLOCKS_PER_SEC)
        << " seconds . . ." << endl;
   cout << "capacity post-load: " << hTab.cap() << endl;
   cout << "used post-load:     " << hTab.size() << endl;
   cout << "load-factor:        " << hTab.load_factor() << endl;
   hTab.grading_helper_print(cout);
   hTab.scat_plot(cout);

   char response;
   do
   {
      cout << "Enter word to spell check: ";
      cin >> oneWord;
      cin.ignore(9999, '\n'); // clear the cin buffer
      cout << endl;
      MakeAllLowerCase(oneWord);
      if ( hTab.search(oneWord) )
         cout << oneWord << " matches a word in dictionary ~ o ~" << endl;
      else
      {
         string altWord;
         bool suggLabPrinted = false;
         HashTable::size_type size = oneWord.size();
         for(HashTable::size_type x = 0; x < size; ++x)
         {
            altWord = oneWord;
            for(char c = 'a'; c <= 'z'; ++c)
            {
               altWord[x] = c;
               if( hTab.search(altWord) )
               {
                  if( ! suggLabPrinted)
                  {
                     cout << oneWord << " not found in dictionary . . .\n"
                          << "   near match(es): ";
                     suggLabPrinted = true;
                  }
                  cout << altWord << "  ";
               }
               altWord = oneWord;
            }
         }
         if(suggLabPrinted)
            cout << endl;
         else
            cout << oneWord << " not found in dictionary . . .\n"
                 << "   no near match(es) to suggest :-( \n";
      }
      cout << "\nMore word to spell check? (y/n): ";
      cin >> response;
      cin.ignore(9999, '\n'); // clear the cin buffer
   }
   while(response == 'y' || response == 'Y');

   cout << "******* bye *******\n";

   return EXIT_SUCCESS;
}

void MakeAllLowerCase(string& word)
{
   HashTable::size_type i = 0, size = word.size();
   while (i < size)
   {
      word[i] = word[i] | 32;
      ++i;
   }
}
