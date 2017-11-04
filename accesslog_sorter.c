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
	
	clear();
	
/* ---- Open File ---- */
	
	pFin_log = fopen("/var/log/apache2/other_vhosts_access.log", "rb");
	if (pFin_log == NULL)
	{
		clear();
		printf(BOLD"\nERROR: Can not open \"/var/log/apache2/other_vhosts_access.log\""RESET);
		return -1;
	}
	
/* ---- Allocate Memory for File Buffer ---- */
	
	if (fseek(pFin_log, 0L, SEEK_END) == 0)
	{
		file_size = ftell(pFin_log);
		if (file_size == -1)
		{
			clear();
			printf(BOLD"\nERROR: Can not read \"/var/log/apache2/other_vhosts_access.log\""RESET);
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
	
	fclose(pFout_log);
	free(file_buffer);
}
