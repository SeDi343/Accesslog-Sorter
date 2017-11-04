/* !* MAIN C FILE accesslog_sorter.c
 *
 * \description Main file for accesslog sorter for Apache2
 *              log file
 *
 * \version Rev.: 01, 04.11.2017 - Created
 *
 */

#include "accesslog_sorter.h"

int main(int argc, char *argv[])
{
	FILE* pFin_log = NULL;
	FILE* pFout_log = NULL;
	char *file_buffer = NULL;
	char *file_buffer_a = NULL;
	char *file_buffer_b = NULL;
	size_t newLen = 0;
	long file_size = 0;
	
	int linebreak_number = 0;
	int counter = 0;
	int i;
	
	char *part01 = NULL; //domain :
	char *part02 = NULL; //port \0
	char *part03 = NULL; //IP-Address \0
	char *part04 = NULL; //Time-Stamp [
	char *part05 = NULL; //Time-Stamp \0
	char *part06 = NULL; //URL 3x"
	char *part07 = NULL; //URL "
	char *part08 = NULL; //User Agent "
	char *part09 = NULL; //User Agent \0
	char *part10 = NULL; //OS (
	char *part11 = NULL; //OS )
	char *part12 = NULL; //Linebreak \n
	
	char domain_var[MAXSIZE];
	char port_var[MAXSIZE];
	char ip_var[MAXSIZE];
	char time_var[MAXSIZE];
	char url_var[MAXSIZE];
	char user_ag_var[MAXSIZE];
	char os_var[MAXSIZE];
	
	clear();
	
/* ---- Open File ---- */
	
	pFin_log = fopen("/var/log/apache2/other_vhosts_access.log", "r");
	if (pFin_log == NULL)
	{
		clear();
		printf(BOLD"\nERROR: Can not open \"/var/log/apache2/other_vhosts_access.log\"\n"RESET);
		return -1;
	}
	
/* ---- Allocate Memory for File Buffer ---- */
	
	if (fseek(pFin_log, 0L, SEEK_END) == 0)
	{
		file_size = ftell(pFin_log);
		if (file_size == -1)
		{
			clear();
			printf(BOLD"\nERROR: Can not read \"/var/log/apache2/other_vhosts_access.log\"\n"RESET);
			fclose(pFin_log);
			return -1;
		}
		
		file_buffer = (char *)malloc(sizeof(char) * (file_size +1));
		file_buffer_a = (char *)malloc(sizeof(char) * (file_size +1));
		file_buffer_b = (char *)malloc(sizeof(char) * (file_size +1));
		
/* ---- Go back to the beginning of the file ---- */
		
		if (fseek(pFin_log, 0L, SEEK_SET) != 0)
		{
			clear();
			printf(BOLD"\nERROR: Can not go back to the start of the file.\n"RESET);
			fclose(pFin_log);
			return -1;
		}
		
/* ---- Read the entire file into memory. ---- */
		
		newLen = fread(file_buffer, sizeof(char), file_size, pFin_log);
		if (newLen == 0)
		{
			clear();
			printf(BOLD"\nERROR: Error reading file into memory\n"RESET);
			fclose(pFin_log);
			return -1;
		}
		else
		{
			file_buffer[++newLen] = '\0';
		}
	}
	fclose(pFin_log);
	
	linebreak_number = count_characters(file_buffer, '\n');
	printf("Linebreak:\t"BOLD"%d"RESET"\n"
		   "Total Chars:\t"BOLD"%d"RESET"\n", linebreak_number, strlen(file_buffer));
	
/* ---- Whole file is now in buffer, continue with writing file style ---- */
	
	pFout_log = fopen("/home/server/http-server.log", "wb");
	
	fputs("Domain\tPort\tIP-Adress\tTimestamp\tURL\tUser-Agent\tOS", pFout_log);
	
	strncpy(file_buffer_a, file_buffer, strlen(file_buffer));
	
	while (counter < linebreak_number)
	{
/* ---- DOMAIN ---- */
		
		part01 = strchr(file_buffer_a, ':');
		
		strncpy(domain_var, file_buffer_a, strlen(file_buffer_a) - strlen(part01));
		fprintf(pFout_log, "%s\t", domain_var);
		
#if DEBUG
		printf("Difference1: %d\n", strlen(file_buffer_a) - strlen(part01));
#endif
		
		strncpy(file_buffer_b, file_buffer_a, strlen(part01));
		
/* ---- PORT ---- */
		
		part02 = strchr(file_buffer_b, ' ');
		
		strncpy(port_var, file_buffer_b, strlen(part01) - strlen(part02));
		fprintf(pFout_log, "%s\t", port_var);
		
#if DEBUG
		printf("Difference2: %d\n", strlen(part01) - strlen(part02));
#endif
		
		strncpy(file_buffer_a, file_buffer_b, strlen(part02));
		
/* ---- IP ---- */
		
		part03 = strchr(file_buffer_a, ' ');
		
		strncpy(ip_var, file_buffer_a, strlen(part02) - strlen(part03));
		fprintf(pFout_log, "%s\t", ip_var);
		
#if DEBUG
		printf("Difference3: %d\n", strlen(part02) - strlen(part03));
#endif
		
		strncpy(file_buffer_b, file_buffer_a, strlen(part03));
		
/* ----- TIME ---- */
		
		part04 = strchr(file_buffer_b, '[');
		part05 = strchr(file_buffer_b, ' ');
		
		strncpy(time_var, file_buffer_b, strlen(part04) - strlen(part05));
		fprintf(pFout_log, "%s\t", time_var);
		
#if DEBUG
		printf("Difference4: %d\n", strlen(part04) - strlen(part05));
#endif
		
		strncpy(file_buffer_a, file_buffer_b, strlen(part05));
		
/* ---- URL ---- */
		
		for (i = 0; i < URL_COUNT; i++)
		{
			part06 = strchr(file_buffer_a, '"');
		}
		part07 = strchr(file_buffer_a, '"');
		
		strncpy(url_var, file_buffer_a, strlen(part06) - strlen(part07));
		fprintf(pFout_log, "%s\t", url_var);
		
#if DEBUG
		printf("Difference5: %d\n", strlen(part06) - strlen(part07));
#endif
		
		strncpy(file_buffer_b, file_buffer_a, strlen(part07));
		
/* ---- USER AGENT ---- */
		
		part08 = strchr(file_buffer_b, '"');
		part09 = strchr(file_buffer_b, ' ');
		
		strncpy(user_ag_var, file_buffer_b, strlen(part08) - strlen(part09));
		fprintf(pFout_log, "%s\t", user_ag_var);
		
#if DEBUG
		printf("Difference6: %d\n", strlen(part08) - strlen(part09));
#endif
		
		strncpy(file_buffer_a, file_buffer_b, strlen(part09));
		
/* ---- OS ---- */
		
		part10 = strchr(file_buffer_a, '(');
		part11 = strchr(file_buffer_a, ')');
		
		strncpy(os_var, file_buffer_a, strlen(part10) - strlen(part11));
		fprintf(pFout_log, "%s\n", os_var);
		
#if DEBUG
		printf("Difference7: %d\n", strlen(part10) - strlen(part11));
#endif
		
		strncpy(file_buffer_b, file_buffer_a, strlen(part11));
		
		part12 = strchr(file_buffer_b, '\n');
		
		strncpy(file_buffer_a, file_buffer_b, strlen(part12));
		
		counter++;
	}
		
	fclose(pFout_log);
	free(file_buffer);
	return 0;
}
