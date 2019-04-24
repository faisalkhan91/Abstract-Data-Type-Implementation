// File:        tools.cpp
// Author: 	Dr. Alice Fischer, UNH
// Edited by: 	Dr. Ted Markowitz, UNH (tmarkowitz@newhaven.edu)
// Last update:	08/24/15

// ---------------------------------------------------------------------------
// Assorted utility routines for use in assigned C++ programs.
// ---------------------------------------------------------------------------

#include "tools.hpp"

// ---------------------------------------------------------------------------
// I/O Manipulators
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Used to discard the remainder of the current input line
istream& cleanline( istream& is ) {
    return is.ignore( numeric_limits<streamsize>::max(), '\n' );
}

// ---------------------------------------------------------------------------
// Used to flush the cin buffer as in cin >> x >> flush;  or cin >> flush;
istream& flush( istream& is ) {
    return is.seekg( 0, ios::end );
}

// --------------------------------------------------------------------------
// Reset the formatting style from 'fixed' or 'scientific' back to default.
// Use: cout <<fixed <<x <<general <<y;
ostream& general( ostream& os ) {
    os.unsetf( ios::floatfield );
    return os;
}

// ----------------------------------------------------------------------------
// Routine process management.
// ----------------------------------------------------------------------------

// Print a neat header on console output.
// Use: fbanner( outstream ); // outstream is cout or another stream name.
void fbanner( ostream& fout ) {
    char date[16], time[10];
    when( date, time );
    fout << "----------------------------------------------------------------\n"
         << '\t' << NAME << '\n'
         << '\t' << CLASS << " - " << SEMESTER << '\n'
         << '\t' << date << " - " << time << '\n'
         << "----------------------------------------------------------------\n\n";
}

void banner() {
    fbanner( cout );
}

void bye( void ) {
    char hour[8];
    oclock( hour );
    hour[8] = '\0';
    cout << "\n\n[Program termination at " << hour << "]\n\n";
}

// --------------------------------------------------------------------------
//  Print message and wait for the user to type a newline.
void hold( void ) {
    cout << flush << endl << endl << "Press 'Enter' to continue... ";
    cin >> flush;
    getchar();
    cin >> flush;
}

// --------------------------------------------------------------------------
// Delay progress of program for some number of seconds
// First, determine proper version of sleep function to use: windows or unix

// Special code to handle sleep function on Windows systems

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__) || defined(WINDOWS)

#include <windows.h>

inline void delay( int sec ) {
    Sleep( sec * 1000 );
}

#else  /* presume POSIX */

#include <unistd.h>

inline void delay( int sec ) {
    usleep( sec * 1000 * 1000 );
}

#endif

// --------------------------------------------------------------------------
// say: A handy function for messages of all sorts.
// It formats, prints, and then rings the bell.
// It accepts a format priored by a variable number of data items to print.
void say ( const char* format, ... ) {
    va_list vargs;                               // optional arguments

    va_start( vargs, format );
    vfprintf( stderr, format, vargs );
    fprintf( stderr, "\n" );
}

// ----------------------------------------------------------------------------
//  Error handling and error recovery functions.
//-----------------------------------------------------------------------------

// fatal: a function for fatal error messages.
// It takes a format argument priored by any number of data arguments.
// It formats and prints an error message, then exits.
void fatal ( const char* format, ... ) {
    va_list vargs;                               // optional arguments

    cout << flush;
    va_start( vargs, format );
    vfprintf( stderr, format, vargs );
    fprintf( stderr, "\n" );
    fputs( "\n Error exit; press '.' and 'Enter' to continue", stderr );
    while ( getchar() != '.' ) // tight loop  ;
        exit( 1 );
}

// ----------------------------------------------------------------------------
//  Routines for handling the time and date.
// ----------------------------------------------------------------------------

// when: Store the current date and time in the arguments.
// System's date format is: "Fri Jun  9 10:15:55 1995\n"
// After extraction, date is: "Fri Jun  9 1995"    hour is: "10:15:55"
void when( char* date, char* hour ) {
    time_t now;           // Stores an integer encoding of the date and time.
    char* nowstring;    // Stores the date and time in a readable form.

    now = time( NULL );            // Get the date and time from the system.
    nowstring = ctime( &now );                 // Convert to string form.
    strncpy( date, nowstring, 10 );            // Extract day, month, date.
    strncpy( &date[10], &nowstring[19], 5 );   // Extract space and year.
    date[15]  = '\0';                          // Add the string terminator.
    strncpy( hour, &nowstring[11], 8 );        // Copy hour:minutes:seconds.
    hour[8]  = '\0';                           // Add the string terminator.
}

// --------------------------------------------------------------------------
// Store the current date in the argument and return a pointer to it.
//      date format is: "Fri Jun  9 1995"
char* today( char* date ) {
    time_t now;         // Stores an integer encoding of the date and time.
    char* nowstring;    // Stores the date and time in a readable form.

    now = time( NULL );            // Get the date and time from the system.
    nowstring = ctime( &now );                 // Convert to string form.
    strncpy( date, nowstring, 10 );            // Extract day, month, date.
    strncpy( &date[10], &nowstring[19], 5 );   // Extract space and year.
    date[15]  = '\0';                          // Add the string terminator.
    return ( date );
}

// --------------------------------------------------------------------------
// Store the current time in hour and return a pointer to it.
//      hour format is: "10:15:55"
char* oclock( char* hour ) {
    time_t now;          // Stores an integer encoding of the date and time.
    char* nowstring;    // Stores the date and time in a readable form.

    now = time( NULL );            // Get the date and time from the system.
    nowstring = ctime( &now );            // Convert to string form.
    strncpy( hour, &nowstring[11], 8 );   // Extract hour, minutes, seconds.
    hour[8]  = '\0';                      // Add the string terminator.
    return ( hour );
}

// ----------------------------------------------------------------------------
//  Menu handling
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Display a menu then read and validate a numeric menu choice.
int menu( char* title, int n, const char* menu[] ) {
    int choice;
    char next;

    cout << endl << title << endl << endl ;

    for ( ;; ) {
        for ( int k = 0; k < n; ++k )
            cout << "\t " << ( k + 1 ) << ". " << menu[k] << endl;

        cout << endl << " Enter number of desired item: ";
        cin >> choice;
        if ( 0 < choice && choice <= n ) break;
        cout << "\n Illegal choice or input error; try again.\n\n";
        while ( ( next = getchar() ) != '\n' && next != EOF ); // flush input buffer
    }
    return choice;
}

// Display a menu then read an alphabetic menu choice character.
char menu_c( char* title, int n, const char* menu[], char* valid ) {
    int k;
    char choice, next;

    cout << endl << title << endl << endl ;

    for ( ;; ) {
        for ( k = 0; k < n; ++k )
            cout << "\t " << menu[k] << endl;

        cout << endl << " Enter code of desired item: ";
        cin >> choice;
        if ( strchr( valid, choice ) != NULL ) break;
        cout << "\n Illegal choice; try again.\n\n";
        while ( ( next = getchar() ) != '\n' && next != EOF ); // flush input buffer
    }
    return choice;
}

