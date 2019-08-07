#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define NB_TRY 10

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	readchar()
{
	char letter;

	letter = getchar();
	letter = toupper(letter);
	while (getchar() != '\n');
	return (letter);
}

char	*hiddensword(char *str, char *copie, char letter)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (copie[i] > 'A' && copie[i] < 'Z')
		{
			i++;
		}
		if (str[i] == letter && copie[i] != letter)
		{
			copie[i] = letter;
		}
		i++;
	}
	return (copie);
}

char	*reset_word(char *copie, char *original)
{
	int i;

	i = 0;
	while (original[i] != '\0')
	{
		copie[i] = '*';
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

int		check_str(char *str, char *copie)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != copie[i])
		{
			return (0);
		}
	i++;
	}
	return (1);
}

int		ft_random_nbr(int nb_max)
{
	srand(time(NULL));
	return ((rand() % (nb_max - 1)));
}

char	*random_secretword(char *secretword)
{
	FILE *fichier = NULL;
	char sep;
	char letter = 0;
	int nb_word = 0;
	int nb_random = 0;
	int len = 0;

	sep = '\n';
	fichier = fopen("dictionnaire.txt", "r");
	if (fichier == NULL)
	{
		printf("Impossible d'ouvrir le fichier\n");
		return (0);
	}
	while (letter != EOF)
	{
		letter = fgetc(fichier);
		if (letter == sep)
		{
			nb_word++;
		}
	}
	nb_random = ft_random_nbr(nb_word);
	rewind(fichier);
	while (nb_random >= 0)
	{
		letter = fgetc(fichier);
		if (letter == sep)
		{
			nb_random--;
		}
	}
	fgets(secretword, 20, fichier);
	len = ft_strlen(secretword);
	secretword[len - 1] = '\0';
	fclose(fichier);
	return (secretword);
}

int		check_char(char c, char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int		main(void)
{
	int t;
	char myletter;
	char *secretword;
	char *copie;

	secretword = (char*)malloc(sizeof(char) * 20);
	if (secretword == NULL)
	{
		printf("Echec allocation mémoire\n");
		return (0);
	}
	secretword = random_secretword(secretword);
	t = NB_TRY;
	copie = (char*)malloc(sizeof(char) * (ft_strlen(secretword) + 1));
	if (copie == NULL)
	{
		printf("Echec allocation mémoire\n");
		return (0);
	}
	copie = reset_word(copie, secretword);
	printf("Bienvenu au jeu du pendu\n");
	
	while (t != 0)
	{
		printf("\nIl vous reste %d essais\n", t);
		printf("Quel est le mot secret ? %s\nProposez une lettre : ", copie);
		
		myletter = readchar();
		printf("\n");
		copie = hiddensword(secretword, copie, myletter);
		if (check_str(secretword, copie) == 1)
		{
			printf("%s\nVous avez gagné !\n", secretword);
			return (0);
		}
		if (check_char(myletter, secretword) == 0)
		{
			printf("Mauvaise lettre\n\n");
			t--;
		}
	}
	if (check_str(secretword, copie) == 0)
	{
		printf("Vous avez perdu !\nLa réponse était : %s\n", secretword);
	}
	free(copie);
	free(secretword);
	return (0);
}
