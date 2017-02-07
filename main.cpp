#include <iostream>
#include <fstream>
#include <cstring>
#include "vector.h"
//#include "DSString.h"

using namespace std;

// Austin Chen
// Kevin Queenan
// Sorting Competition Data Structures Fall 2016

struct wordBucket
{
    int word_len;
    Vector<char*> wordlist;
};

int main(int argc, char* const argv[])
{
    // Declare input and output files
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    // Declare variables for 1st two lines of read-in
    int num_words;
    int num_words_to_output;

    // Buffer for max size of 40
    char buffer[41];

    fin >> num_words;
	fin >> num_words_to_output;

    // Create vector of word buckets
    Vector<wordBucket> words;

    // Add buckets of lengths 1-40
    for (int i = 1; i < 41; i++)
    {
        wordBucket tempWordBucket;
        tempWordBucket.word_len = i;

        words.add(tempWordBucket);
    }

    int buffStrLen = 0;

    // Parse through entire text file and add words to corresponding buckets
    while (!fin.eof())
    {
        fin >> buffer;

        // Break if end of file
        if (fin.eof()) break;

        buffStrLen = strlen(buffer);

        char* temp = new char[buffStrLen+1];

		strcpy(temp, buffer);

        words[buffStrLen-1].wordlist.add(temp);

		num_words--;
    }

    int bucketsToSort = 0;
    int tempSortInt = num_words_to_output;
    int bucketMoveIndex = 0;

    // Sorting optimization, only sort the buckets that need to be
    // sorted
    while (tempSortInt > 0)
    {
        tempSortInt -= words[bucketMoveIndex].wordlist.size();
        bucketsToSort++;
        bucketMoveIndex++;
    }

    for (int i = 0; i < bucketsToSort; i++)
    {
        if (words[i].wordlist.size() != 0)
        {
            words[i].wordlist.sort();
        }
    }

    int moveIndex = 0;
    int counter = 0;
    int printCounter = 0;
    int switchCounter = 0;

    // Prints out only the number of words specified in the file
    while (counter != num_words_to_output)
    {
        if (switchCounter >= words[moveIndex].wordlist.size())
        {
            switchCounter = 0;
            moveIndex++;
            printCounter = 0;
        }

        else if (words[moveIndex].wordlist.size() == 0)
        {
            moveIndex++;
            printCounter = 0;
        }

        else if (words[moveIndex].wordlist.size() > 0)
        {
            fout << words[moveIndex].wordlist[printCounter] << endl;
            printCounter++;
            counter++;
            switchCounter++;
        }
    }

    // Close files
    fin.close();
    fout.close();
    return 0;
}
