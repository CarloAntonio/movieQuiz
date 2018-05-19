//Objective: Process movies list.
//Name: Carlo Antonio Bilbao
//Course: COMSC-110-8269
//Compiler: TDM MinGW
//Editor: MS NotePad

//libraries
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h> 
using namespace std;



//Programmer defined data types
struct Movie {
  string name; //movie title
  int year; //movie release year
};

//Special compiler dependent definitions
//NONE

//global constants/variables
//NONE

//Programmer defined functions
void introduction(string obj); //outputs introduction
int getNumOfMoviesInFile(); //returns number of movies in the movieData.txt file
void inputMovies(Movie* movies, int numMoviesInFile); //pulls moves from movieData.txt and add it to a movies array
int askMovie(Movie* movies, int numMoviesInFile); //prompts the user a movie question
bool yOrN(string question); //returns a bool after validating a yes or no
void outputList(Movie* movies, int numMoviesInFile); //outputs a sorted list of movies
void sortlist(Movie* movies, int numMoviesInFile); //sort list
void addMoreMovies(); //adds movies to movieData.txt

//main program
int main() {
  //data
  string objective="process movies list."; //program objective
  int maxMoviesPlusSpace; //array size with extra space for adding more movies to the array
  int numMoviesInFile; //the number of movies in the input file
  int gameScore; //user's game score
  bool seeAllMoviesInFile; //see movies list

  //introduction
  introduction(objective);

  //get number of movies in file
  numMoviesInFile = getNumOfMoviesInFile();

  //check for empty file
  if(numMoviesInFile != 0) {

    //create movies array-list with extra space for adding new movies
    maxMoviesPlusSpace = numMoviesInFile + 50;
    Movie movies[maxMoviesPlusSpace]; //array of movies

    //add movies from file to the movies array
    inputMovies(movies, numMoviesInFile);

    //ask movie question and keep doing to until user quits
    if(yOrN("Do you want to play the movies quiz game?")) {
      gameScore = askMovie(movies, numMoviesInFile);
      cout << "Your score for this session is "<< gameScore << "." << endl;
      cout << "Thanks for playing!" << endl << endl; 
    }

    //ask user if they want to see the complete list of movies
    if(yOrN("Do you want to see a complete list of the movies on file?")) {
      outputList(movies, numMoviesInFile);
    }

    //ask user if they want to edit the list
    if(yOrN("Do you want to add to the list of movies?")) {
      addMoreMovies();
    }

    //goodbye greeting
    cout << "Thanks for using this app!" << endl << endl;

  } else {
    cout << "Error: file does not contain any data." << endl << endl;
  }

}//main

void introduction(string obj) {
  cout << "Objective: This program will "; 
  cout << obj << endl;
  cout << "Programmer: Carlo Antonio Bilbao\n"; 
  cout << "Editor(s) used: Notepad\n"; 
  cout << "Compiler(s) used: TDM MinGW\n"; 
  cout << "File: " << __FILE__ << endl; 
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl; 
} //introduction

int getNumOfMoviesInFile() {
  //local data
  ifstream fin; //file handle
  string holder; //holds string input;
  int count = 0; //number of movies in file

  //open file
  fin.open("movieData.txt");
  if(!fin.good()) throw "I/O error";

  //extract number of movies in file
  while(fin.good()) {
    getline(fin, holder);
    if (holder == "") {
      //file is at end of list or empty file so break from loop
      break;
    } else {
      //file contain a data set, add to count
      count++;
      //skip past next to items(movie year + spacing)
      getline(fin, holder);
      getline(fin, holder);
    }
  }

  //close file
  fin.close();

  //return count
  return count;
} //end getNumOfMoviesInFile

void inputMovies(Movie* movies, int numMoviesInFile){
  //local data
  ifstream fin; //file handle
  string nameHolder; //holds name string input;
  int yearHolder; //holds year input
  int count = 0; //position of movies array index

  //open file
  fin.open("movieData.txt");
  if(!fin.good()) throw "I/O error";

  //extract data from file
  while(fin.good()) {
    //extract name
    getline(fin, nameHolder);
    movies[count].name = nameHolder;

    //extract year
    fin >> movies[count].year;
    fin.ignore(1000, 10);

    //skip spacing
    getline(fin, nameHolder);

    //progress to next index in the array
    count++;
  }

  //close file
  fin.close();
}

int askMovie(Movie* movies, int numMoviesInFile) {
  //local data
  int arrayIndex; //randomly chosen array index
  int userGuess; //user's guess to question
  bool keepPlaying = true; //keep playing sentinel
  int score = 0; //number of correct answers

  //initializes rand
  srand (time(0)); rand();

  while(keepPlaying) {
    //randomly choose an array index
    arrayIndex = rand() % numMoviesInFile;

    //output question
    cout << "What year did the movie " << movies[arrayIndex].name << " come out? [answer as number, ex: 1992] ";
    cin >> userGuess;
    cin.ignore(1000, 10); 

    //output response
    if(userGuess == movies[arrayIndex].year) {
      //correct response output & add to score
      cout << "Nice job! That's the correct answer!" << endl;
      score++;
    } else {
      //incorrect response output
      cout << "Not quite. The correct answer is " << movies[arrayIndex].year << "." << endl;
    }

    //check if user wants to play again and validate choice
    keepPlaying = yOrN("Another question?");
  }

  //return user's decision to keep playing or not
  return score;
}

bool yOrN(string question) {
  //local data
  char userDecision; //user's choice to keep playing or not
  bool response = false; //user choice to continue or not

  //check if user wants to play again and validate choice
  while(true) {
    cout << question << " (Y/N)";
    cin >> userDecision;
    cin.ignore(1000, 10);
    cout << endl;
    if(userDecision == 'Y' || userDecision == 'y') {
      response = true;
      break;
    } else if(userDecision == 'N' || userDecision == 'n') {
      response = false;
      break;
    } else {
      cout << "Invalid Input." << endl;
    }
  }//and valid answer loop

  return response;
}

void outputList(Movie* movies, int numMoviesInFile) {
  //sort movies in array
  sortlist(movies, numMoviesInFile);

  //create a header
  cout << setw(30) << left << "Movie Name" << setw(6) << left << "Year" << endl;

  //output sorted list
  for(int i = 0; i < numMoviesInFile; i++) {
    cout << setw(30) << left << movies[i].name;
    cout << setw(6) << left << movies[i].year;
    cout << endl;
  }

  cout << endl;
  
}

void sortlist(Movie* movies, int numMoviesInFile) {
  //local data
  int holder; //user to hold data while switching

  //sort by year
  for(int i = 0; i < numMoviesInFile; i++) {
    for(int j = i + 1; j < numMoviesInFile; j++) {
      if (movies[j].year < movies[i].year) {
        holder = movies[i].year;
        movies[i].year = movies[j].year;
        movies[j].year = holder;
      }
    }
  }
}

void addMoreMovies() {
  //local data
  string movieName; //movie name, user input
  int movieYear; //year movie was released, user input
  ofstream fout; //file handle for outputting data
  bool addMoreMovies = true; //sentinel for adding more movies
  
  //open file
  fout.open("movieData.txt", ios::app);
  if(!fout.good()) throw "I/O error";

  //add movie to file
  while(addMoreMovies) {
    //add movie name
    cout << "What is the name of the movie you want to add to the file? ";
    getline(cin, movieName);
   
    //add movie year
    cout << "What is the year of release for the movie? ";
    cin >> movieYear;
    cin.ignore(1000, 10);

    //add data to file + space for format requirement
    fout << movieName << endl;
    fout << movieYear << endl;
    fout << endl;

    //ask user if they want to add more movies
    addMoreMovies = yOrN("Do you want to add more movies to the file? ");
  }  
  
  //close file
  fout.close();
  
  //ui affermation
  cout << "Movie list updated!" << endl;
}