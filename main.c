#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "libasm.h"

void	test_ft_read(void) {
	printf("\n" C_BLUE "=========================================================" C_RESET "\n");
	printf(C_WHITE "                    TESTS : ft_read                      " C_RESET "\n");
	printf(C_BLUE "=========================================================" C_RESET "\n");
	int		fd;
	char	buffer[32];
	ssize_t	ret;

	/* --------------------------------------------------------- */
	/* TEST 1 : Lecture normale                                  */
	/* --------------------------------------------------------- */
	printf("\n" C_CYAN "[TEST 1] Lecture normale (Makefile)" C_RESET "\n");
	fd = open("Makefile", O_RDONLY);
	if (fd == -1)
	{
		perror(C_RED "open" C_RESET);
		return ;
	}
	ret = ft_read(fd, buffer, sizeof(buffer));
	printf("-> Retour de ft_read : %ld\n", ret);
	if (ret >= 0)
	{
		buffer[ret < 32 ? ret : 31] = '\0';
		printf(C_YELLOW "--- Contenu lu ---" C_RESET "\n");
		write(1, buffer, ret);
		printf("\n" C_YELLOW "------------------" C_RESET "\n");
		printf(C_GREEN "[ OK ]" C_RESET " Lecture executee\n");
	}
	else
		printf(C_RED "[ KO ]" C_RESET " Erreur de lecture inattendue\n");
	close(fd);

	/* --------------------------------------------------------- */
	/* TEST 2 : FD invalide                                      */
	/* --------------------------------------------------------- */
	printf("\n" C_CYAN "[TEST 2] FD invalide (-1)" C_RESET "\n");
	ret = ft_read(-1, buffer, sizeof(buffer));
	printf("-> ft_read(-1) = %ld\n", ret);
	if (ret < 0)
		printf(C_GREEN "[ OK ]" C_RESET " Erreur detectee correctement !\n");
	else
		printf(C_RED "[ KO ]" C_RESET " ERREUR : ft_read aurait du echouer\n");

	/* --------------------------------------------------------- */
	/* TEST 3 : count = 0                                        */
	/* --------------------------------------------------------- */
	printf("\n" C_CYAN "[TEST 3] Count = 0" C_RESET "\n");
	fd = open("Makefile", O_RDONLY);
	if (fd == -1)
	{
		perror(C_RED "open" C_RESET);
		return ;
	}
	ret = ft_read(fd, buffer, 0);
	printf("-> ft_read(fd, buffer, 0) = %ld\n", ret);
	if (ret == 0)
		printf(C_GREEN "[ OK ]" C_RESET " Lecture de 0 octet conforme.\n");
	else
		printf(C_RED "[ KO ]" C_RESET " Resultat inattendu\n");
	close(fd);

	/* --------------------------------------------------------- */
	/* TEST 4 : buffer NULL                                      */
	/* --------------------------------------------------------- */
	printf("\n" C_CYAN "[TEST 4] Buffer NULL" C_RESET "\n");
	fd = open("Makefile", O_RDONLY);
	if (fd == -1)
	{
		perror(C_RED "open" C_RESET);
		return ;
	}
	ret = ft_read(fd, NULL, 10);
	printf("-> ft_read(fd, NULL, 10) = %ld\n", ret);
	if (ret < 0)
		printf(C_GREEN "[ OK ]" C_RESET " Erreur detectee correctement !\n");
	else
		printf(C_RED "[ KO ]" C_RESET " Resultat inattendu\n");
	close(fd);
}

void	test_ft_strlen(void) {
	printf("\n" C_BLUE "=========================================================" C_RESET "\n");
	printf(C_WHITE "                   TESTS : ft_strlen                     " C_RESET "\n");
	printf(C_BLUE "=========================================================" C_RESET "\n");

	char *tests[] = {"Hello", "", "A", "Bonjour le monde", "Hello World !"};
	long expected[] = {5, 0, 1, 16, 13};
	long res;

	for (int i = 0; i < 5; i++)
	{
		res = ft_strlen(tests[i]);
		printf("\n" C_CYAN "[TEST %d] Chaine : \"%s\"" C_RESET "\n", i + 1, tests[i]);
		printf("-> ft_strlen : %ld | Attendu : %ld\n", res, expected[i]);
		if (res == expected[i])
			printf(C_GREEN "[ OK ]" C_RESET " Valeurs identiques\n");
		else
			printf(C_RED "[ KO ]" C_RESET " Erreur de taille !\n");
	}
}

void	test_ft_strcmp(void) {
	printf("\n" C_BLUE "=========================================================" C_RESET "\n");
	printf(C_WHITE "                   TESTS : ft_strcmp                     " C_RESET "\n");
	printf(C_BLUE "=========================================================" C_RESET "\n");
	int		ret_ft;
	int		ret_sys;

	char *s1[] = {"Hello", "", "Hello", "Hello World", "abc", "test\200"};
	char *s2[] = {"Hello", "", "Hello World", "Hello", "ABC", "test\0"};
	char *desc[] = {
		"Chaines identiques",
		"Chaines vides",
		"s1 plus courte (inferieure)",
		"s1 plus longue (superieure)",
		"Difference de casse",
		"Caracteres speciaux / Extended ASCII"
	};

	for (int i = 0; i < 6; i++)
	{
		printf("\n" C_CYAN "[TEST %d] %s" C_RESET "\n", i + 1, desc[i]);
		ret_ft = ft_strcmp(s1[i], s2[i]);
		ret_sys = strcmp(s1[i], s2[i]);

		printf("-> ft_strcmp : %d\n", ret_ft);
		printf("-> strcmp    : %d\n", ret_sys);

		// Gestion stricte de l'égalité ou conformité du signe
		if (i < 2) // Pour les chaînes identiques (doit valoir 0)
		{
			if (ret_ft == ret_sys)
				printf(C_GREEN "[ OK ]" C_RESET " Resultats identiques (0)\n");
			else
				printf(C_RED "[ KO ]" C_RESET " Les resultats different !\n");
		}
		else // Pour les différences (on vérifie le signe)
		{
			if ((ret_ft < 0 && ret_sys < 0) || (ret_ft > 0 && ret_sys > 0))
				printf(C_GREEN "[ OK ]" C_RESET " Signe du resultat correct\n");
			else
				printf(C_RED "[ KO ]" C_RESET " Le signe differe !\n");
		}
	}
	printf("\n" C_BLUE "=========================================================" C_RESET "\n\n");
}

int main(void) {
	test_ft_read();
	test_ft_strlen();
	test_ft_strcmp();
	return (0);
}
