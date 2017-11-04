/* !* MAIN C FILE accesslog_sorter.c
 *
 * \description Main file for accesslog sorter for Apache2
 *              log file
 *
 * \version Rev.: 01, 04.11.2017 - Created
 *
 */

#include "accesslog_sorter.h"

int main(void)
{
	FILE* pFin_log = NULL;
	FILE* pFout_log = NULL;
	char *file_buffer = NULL;
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
	
	char domain[100];
	char port[100];
	char ip[100];
	char time[100];
	char url[100];
	char user_ag[100];
	char os[100];
	
	clear();
	
/* ---- Open File ---- */
	
	pFin_log = fopen("/var/log/apache2/other_vhosts_access.log", "rb");
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
	
/* ---- Whole file is now in buffer, continue with writing file style ---- */
	
	pFout_log = fopen("/home/$USER/http-serverlog.txt", "wb");
	
	fputs("Domain\tPort\tIP-Adress\tTimestamp\tURL\tUser-Agent\tOS", pFout_log);
	
	linebreak_number = count_characters(file_buffer, '\n');
	
	while (counter < linebreak_number)
	{
		/* ---- DOMAIN ---- */
		
		part01 = strchr(file_buffer, ':');
		
		strncpy(domain, file_buffer, strlen(file_buffer) - strlen(part01));
		fprintf(pFout_log, "%s\t", domain);
		
		/* ---- PORT ---- */
		
		part02 = strchr(file_buffer, ' ');
		
		strncpy(port, file_buffer, strlen(part01) - strlen(part02));
		fprintf(pFout_log, "%s\t", port);
		
		/* ---- IP ---- */
		
		part03 = strchr(file_buffer, ' ');
		
		strncpy(ip, file_buffer, strlen(part02) - strlen(part03));
		fprintf(pFout_log, "%s\t", ip);
		
		/* ----- TIME ---- */
		
		part04 = strchr(file_buffer, '[');
		part05 = strchr(file_buffer, ' ');
		
		strncpy(time, file_buffer, strlen(part04) - strlen(part05));
		fprintf(pFout_log, "%s\t", time);
		
		/* ---- URL ---- */
		
		for (i = 0; i < URL_COUNT; i++)
		{
			part06 = strchr(file_buffer, '"');
		}
		part07 = strchr(file_buffer, '"');
		
		strncpy(url, file_buffer, strlen(part06) - strlen(part07));
		fprintf(pFout_log, "%s\t", url);
		
		/* ---- USER AGENT ---- */
		
		part08 = strchr(file_buffer, '"');
		part09 = strchr(file_buffer, ' ');
		
		strncpy(user_ag, file_buffer, strlen(part08) - strlen(part09));
		fprintf(pFout_log, "%s\t", user_ag);
		
		/* ---- OS ---- */
		
		part10 = strchr(file_buffer, '(');
		part11 = strchr(file_buffer, ')');
		
		strncpy(os, file_buffer, strlen(part10) - strlen(part11));
		fprintf(pFout_log, "%s\n", os);
		
		part12 = strchr(file_buffer, '\n');
		
		counter++;
	}
	
	
	
	fclose(pFout_log);
	free(file_buffer);
	return 0;
}
