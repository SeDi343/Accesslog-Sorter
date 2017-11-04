/* !* FUNCTIONS accesslog_sorter_functions.c
 *
 * \description Functions file for accesslog sorter for Apache2
 *              log file
 *
 * \version Rev.: 01, 04.11.2017 - Created
 *
 */

#include "accesslog_sorter.h"

/*------------------------------------------------------------------*/
/* F U N C T I O N   D E F I N I T I O N                            */
/*------------------------------------------------------------------*/

/* ---- CLEAR FUNCTION ---- */

void clear(void)
{
#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)
	system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
	helpdesk_1();
}

/* ---- CLEAR WITH NO HELP FUNCTION ---- */

void clearNoHelp(void)
{
#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)
	system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}

/* ---- HELPDESK FUNCTION ---- */

void helpdesk_1(void)
{
	printf("\n");
	printf(BOLD"ACCESSLOG SORTER @ v0.1\n"RESET);
	printf(BOLD"Created by Sebastian Dichler, 2017\n"RESET);
	printf("A simple program to sort the Apache2's access log file\n");
	
#if DEBUG
	printf(BOLDRED ITALIC"*** DEBUG MODE ACTIVE ***\n\n"RESET);
#endif
}
