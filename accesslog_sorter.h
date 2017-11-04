/* !* HEADER FILE accesslog_sorter.H
 *
 * \description Header file for accesslog sorter for Apache2
 *              log file
 *
 * \version Rev.: 01, 04.11.2017 - Created
 *
 */

#ifndef accesslog_sorter_h
#define accesslog_sorter_h

/*------------------------------------------------------------------*/
/* I N C L U D E   L I B R A R I E S                                */
/*------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define DEBUG 1
#define URL_COUNT 3
#define MAXSIZE 500

/*------------------------------------------------------------------*/
/* T E R M I N A L   A N S I     F O R M A T I O N                  */
/*------------------------------------------------------------------*/

/* ---- ANSI FORMAT FOR TERMINAL ---- */

#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)

#define RESET         "\033[0m"
#define BLACK         "\033[30m"             /* Black */
#define RED           "\033[31m"             /* Red */
#define GREEN         "\033[32m"             /* Green */
#define CYAN          "\033[36m"             /* Cyan */

#define BOLD          "\033[1m"              /* Bold */
#define BOLDRED       "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN     "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLACK     "\033[1m\033[30m"      /* Bold Black */
#define BOLDCYAN      "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE     "\033[1m\033[37m"      /* Bold White */

#define BACKBLACK     "\033[100m"            /* Background Black */
#define BACKRED       "\033[101m"            /* Background Red */
#define BACKGREEN     "\033[102m"            /* Background Green */
#define BACKYELLOW    "\033[103m"            /* Background Yellow */
#define BACKBLUE      "\033[104m"            /* Background Blue */
#define BACKMAGENTA   "\033[105m"            /* Background Magenta */
#define BACKCYAN      "\033[106m"            /* Background Cyan */
#define BACKWHITE     "\033[107m"            /* Background White */

#define ITALIC        "\033[3m"              /* Italic Mode */

#endif

/* ---- ANSI FORMAT NOT SUPPORTED IN WINDOWS ---- */

#if defined(_WIN32) || defined(_WIN64)

#define RESET        ""
#define BLACK        ""
#define RED          ""
#define GREEN        ""
#define CYAN         ""

#define BOLD         ""
#define BOLDRED      ""
#define BOLDGREEN    ""
#define BOLDBLACK    ""
#define BOLDCYAN     ""
#define BOLDWHITE    ""

#define BACKBLACK    ""
#define BACKRED      ""
#define BACKGREEN    ""
#define BACKYELLOW   ""
#define BACKBLUE     ""
#define BACKMAGENTA  ""
#define BACKCYAN     ""
#define BACKWHITE    ""

#define ITALIC       ""

#endif

/*------------------------------------------------------------------*/
/* F U N C T I O N   D E C L A R A T I O N                          */
/*------------------------------------------------------------------*/

void clear(void);
void clearNoHelp(void);
void helpdesk_1(void);
int count_characters(const char *str, char character);

#endif /* accesslog_sorter_h */
