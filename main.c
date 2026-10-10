#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "libasm.h"

void	test_ft_read(void)
{
	printf("=== Test ft_strlen ===\n");
	int		fd;
	char	buffer[32];
	ssize_t	ret;

	/* ========================================================= */
	/* TEST 1 : Lecture normale                                  */
	/* ========================================================= */
	printf("\n===== TEST 1 : lecture normale =====\n");
	fd = open("Makefile", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	ret = ft_read(fd, buffer, sizeof(buffer));
	buffer[31] = '\0';
	printf("Retour de ft_read : %ld\n", ret);
	if (ret >= 0)
	{
		printf("Contenu lu :\n");
		write(1, buffer, ret);
		printf("\n");
	}
	else
		printf("Erreur de lecture\n");
	close(fd);

	/* ========================================================= */
	/* TEST 2 : FD invalide                                      */
	/* ========================================================= */
	printf("\n===== TEST 2 : FD invalide =====\n");
	ret = ft_read(-1, buffer, sizeof(buffer));
	printf("ft_read(-1) = %ld\n", ret);
	if (ret < 0)
		printf("Erreur detectee correctement !\n");
	else
		printf("ERREUR : ft_read aurait du echouer\n");

	/* ========================================================= */
	/* TEST 3 : count = 0                                        */
	/* ========================================================= */
	printf("\n===== TEST 3 : count = 0 =====\n");
	fd = open("Makefile", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	ret = ft_read(fd, buffer, 0);
	printf("ft_read(fd, buffer, 0) = %ld\n", ret);
	if (ret == 0)
		printf("Lecture de 0 octet : OK\n");
	else
		printf("Resultat inattendu\n");
	close(fd);

	/* ========================================================= */
	/* TEST 4 : buffer NULL                                      */
	/* ========================================================= */
	printf("\n===== TEST 4 : buffer NULL =====\n");
	fd = open("Makefile", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	ret = ft_read(fd, NULL, 10);
	printf("ft_read(fd, NULL, 10) = %ld\n", ret);
	if (ret < 0)
		printf("Erreur detectee correctement !\n");
	else
		printf("Resultat inattendu\n");
	close(fd);
	printf("\n===== FIN DES TESTS FT_READ =====\n");
}

void	test_ft_strlen(void)
{
	printf("=== Test ft_read ===\n");
	printf("\n===== TEST 1 : chaine normale =====\n");
	printf("ft_strlen(\"Hello\") = %ld\n", ft_strlen("Hello"));
	printf("Attendu : 5\n");

	printf("\n===== TEST 2 : chaine vide =====\n");
	printf("ft_strlen(\"\") = %ld\n", ft_strlen(""));
	printf("Attendu : 0\n");

	printf("\n===== TEST 3 : un seul caractere =====\n");
	printf("ft_strlen(\"A\") = %ld\n", ft_strlen("A"));
	printf("Attendu : 1\n");

	printf("\n===== TEST 4 : chaine longue =====\n");
	printf("ft_strlen(\"Bonjour le monde\") = %ld\n",
		ft_strlen("Bonjour le monde"));
	printf("Attendu : 16\n");

	printf("\n===== TEST 5 : espaces =====\n");
	printf("ft_strlen(\"Hello World !\") = %ld\n",
		ft_strlen("Hello World !"));
	printf("Attendu : 13\n");

	printf("\n===== FIN DES TESTS FT_STRLEN =====\n");
}


int main(void) {
	test_ft_read();

	test_ft_strlen();


	return 0;
}
