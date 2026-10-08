#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "libasm.h"

void	test_ft_read(void)
{
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

	/* ========================================================= */
	/* FIN                                                       */
	/* ========================================================= */
	printf("\n===== FIN DES TESTS =====\n");
}

int main(void) {
	int fd = open("Makefile", O_RDONLY);
	if (fd == -1) {
		return 1;
	}

	char buffer[32];

	ssize_t readed = ft_read(fd, buffer, sizeof(buffer));
	if (readed < 0) {
		close(fd);
		return 1;
	}

	printf("%s\n", buffer);

	close(fd);
	return 0;
}
