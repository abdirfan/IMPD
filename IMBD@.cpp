/**********************************************************
 * Program 4: IMBD

    Course: CS 141, Fall 2022.
    System: Windows 11 using Visual Studio
    Starter Code Author: Dr. Sara Riazi
    Student Author: Abdullah Irfan
 *
 **********************************************************/

#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>
#include<string>


using namespace std;


/*********************************************** Helper functions ***************************************/
//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}
/**********************************************************************************************************/
struct TitleRecord                                   //struct for title record and 4 columns we need
{
    string titleId;
    string startYear;
    string primarytitle;
    string genres;
};

struct NameRecord                                  //struct for name record and 5 columns needed
{
    string nameId;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};

struct PrincipalRecord                            //struct for principal record 3 columns needed
{
    string titleId;
    string nameId;
    string character;
};

string modify_string(string input) {             //function moidfying userinput to lower characters to match linearsearc
    string lower = "";
    for (int i = 0;i < input.size();i++) {
        lower += tolower(input[i]);
    }

    return lower;
}

void menu(vector<TitleRecord>& vtr, vector<NameRecord>& vnr, vector<PrincipalRecord>& vpr);

// performing linearsearch on the files title, year, genre
void searchInput(vector<TitleRecord> vtr, vector<NameRecord> vnr, vector<PrincipalRecord> vpr, string input) {
    vector<string> elements;
    string modify = modify_string(input);
    splitString(modify, '+', elements);
    vector<TitleRecord> matches;
    int counter = 0;

    for (int i = 0; i < vtr.size(); i++) {
        int temp = 0;

        while (temp < elements.size()) {
            if (modify_string(vtr[i].primarytitle).find(elements[temp]) != string::npos) {
                temp++;
            }
            else {
                break;
            }

        }


        if (temp == elements.size()) {
            cout << counter << ":" << endl;
            cout << "Title: " << vtr[i].primarytitle << endl;
            cout << "Year: " << vtr[i].startYear << endl;
            vector<string> realgenres;
            splitString(vtr[i].genres, ',', realgenres);             //setting search foramt to add comma in between
            cout << "Genres: ";
            for (int j = 0; j < realgenres.size(); j++) {
                cout << " " << realgenres.at(j);
            }
            cout << endl;
            cout << "---------------" << endl;
            counter++;
            matches.push_back(vtr[i]);
        }
    }

    if (matches.size() == 0) {
        cout << "No match found!" << endl;
    }

    cout << "Select a movie to see its actor/actress (-1 to go back to the previous menu): " << endl;
    int choice;
    cin >> choice;
    for (int i = 0;i < vpr.size();i++) {
        if (matches[choice].titleId == vpr[i].titleId && vpr[i].character != "\\N") {
            for (int j = 0; j < vnr.size();j++) {
                if (vpr[i].nameId == vnr[j].nameId) {
                    cout << vnr[j].primaryName << vpr[i].character << endl;
                }
            }
        }
    }
}

// performing linear search again for names/profession
void searchInput2(vector<TitleRecord> vtr, vector<NameRecord> vnr, vector<PrincipalRecord> vpr, string input_2) {
    vector<string> items;
    string modify = modify_string(input_2);
    splitString(modify, '+', items);
    vector<NameRecord> matches2;
    int counter2 = 0;
    for (int i = 0; i < vnr.size(); i++) {
        int temp2 = 0;
        while (temp2 < items.size()) {
            if (modify_string(vnr[i].primaryName).find(items[temp2]) != string::npos) {
                temp2++;
            }

            else {
                break;
            }

        }
        if (temp2 == items.size()) {
            cout << counter2 << ":" << endl;
            cout << "---------------" << endl;
            cout << vnr[i].primaryName << endl;
            cout << vnr[i].primaryProfession << endl;
            cout << "(" << vnr[i].birthYear << "-" << vnr[i].deathYear << ")" << endl;     //setting search foramt to add hyphen in between
            cout << "---------------" << endl;
            matches2.push_back(vnr[i]);
            counter2++;
        }
    }
    if (matches2.size() == 0) {
        cout << "No match found" << endl;
    }
    cout << "Select an actor/actress to see movie (-1 to go back to the previous menu): " << endl;
    int choice;
    cin >> choice;
    if (choice == -1) {
        menu(vtr, vnr, vpr);
        return;
    }
    for (int i = 0;i < vpr.size();i++) {
        if (matches2[choice].nameId == vpr[i].nameId) {
            for (int j = 0; j < vtr.size();j++) {
                if (vpr[i].titleId == vtr[j].titleId) {
                    cout << vtr[j].primarytitle << " " << vtr[j].startYear << " " << vpr[i].character << endl;
                }
            }

        }
    }

    cout << "Select an actor/actress to see movie (type done to go back to the previous menu): " << endl;
    string input;
    cin >> input;
    if (input == "done") {
        menu(vtr, vnr, vpr);
        return;
    }
    else {
        searchInput2(vtr, vnr, vpr, input);
    }



}

//creating menu option for respective user input search and appropriate choices then breaking if choice is 3
void menu(vector<TitleRecord>& vtr, vector<NameRecord>& vnr, vector<PrincipalRecord>& vpr) {
    int choice;
    int input;
    string done;

    while (choice != 3) {
        cout << "Select a menu option" << endl;
        cout << "    1. Search for movie" << endl;
        cout << "    2. Search for actor/ actresses" << endl;
        cout << "    3. Exit" << endl;



        cout << "Your choice --> ";
        cin >> choice;
        string user_input;

        if (choice == 1) {
            cout << "Enter search phrase: ";
            cin >> user_input;
            searchInput(vtr, vnr, vpr, user_input);
            cout << "----------------" << endl;
        }

        if (choice == 2) {
            cout << "Enter search phrase: " << endl;
            cin >> user_input;
            searchInput2(vtr, vnr, vpr, user_input);
            cout << "----------------" << endl;
        }
        break;
        
    }
    if (choice == 3) {
        cout << "Done." << endl;
    }

}


int run(string titlesFile, string namesFile, string principalsFile) {

    ifstream fin;                              //reading the movies.title.tsv file and creating vector 
    string line;
    vector<TitleRecord> vtr;
    fin.open(titlesFile);
    while (getline(fin, line)) {
        vector<string> movieTitles;
        splitString(line, '\t', movieTitles);
        TitleRecord tr;
        tr.titleId = movieTitles[0];
        tr.primarytitle = movieTitles[2];
        tr.startYear = movieTitles[5];
        tr.genres = movieTitles[8];
        vtr.push_back(tr);
    }


    ifstream fin2;                                  //reading movie.names.tsv file and creating vector 
    string line2;
    vector<NameRecord> vnr;
    fin2.open(namesFile);
    while (getline(fin2, line2)) {
        vector<string> namesTitles;
        splitString(line2, '\t', namesTitles);
        NameRecord nr;
        nr.nameId = namesTitles[0];
        nr.primaryName = namesTitles[1];
        nr.birthYear = namesTitles[2];
        nr.deathYear = namesTitles[3];
        nr.primaryProfession = namesTitles[4];

        vnr.push_back(nr);
    }



    ifstream fin3;                                       // reading movies.principal file and creating vector 
    string line3;
    vector<PrincipalRecord> vpr;
    fin3.open(principalsFile);
    while (getline(fin3, line3)) {
        vector<string> principalsTitles;
        splitString(line3, '\t', principalsTitles);
        PrincipalRecord pr;
        pr.titleId = principalsTitles[0];
        pr.nameId = principalsTitles[2];
        pr.character = principalsTitles[5];
        
        vpr.push_back(pr);
    }



    menu(vtr, vnr, vpr);
}


int main() {


    string titlesFile = "movie.titles.tsv";
    string namesFile = "movie.names.tsv";
    string principalsFile = "movie.principals.tsv";

    //DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);

    return 0;
}
