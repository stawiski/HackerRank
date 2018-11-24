#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DEBUG_PRINTF(...)
//#define DEBUG_PRINTF(...) printf(__VA_ARGS__);

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n)
{
	return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m)
{
	return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k)
{
	return document[k - 1];
}

char**** get_document(char* text)
{
	char c;
	char *word;
	char**** document;
	unsigned int iChars, iWords, iSentences, iParagraphs;
	unsigned int i;

	word = NULL;

	iChars = 0;
	iWords = 0;
	iSentences = 0;
	iParagraphs = 0;

	/* Preallocate the document's pointers. */
	document = malloc(sizeof(char****));
	document[iParagraphs] = malloc(sizeof(char***));
	document[iParagraphs][iSentences] = malloc(sizeof(char**));
	document[iParagraphs][iSentences][iWords] = malloc(sizeof(char*));

	i = 0;

	/* Loop until termination character. */
	while ((c = text[i++])) {
		/* Check if the character belongs to a-z or A-Z. */
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			iChars++;

			word = realloc(word, (iChars + 1)*sizeof(char)); /* Increase string memory if necessary. */
			word[iChars - 1] = c; /* Put the new character. */
			word[iChars] = 0; /* Terminate the word string. */
		} else
		/* Check if the character belongs to special expected characters that always finish the word. */
		if ((c == ' ') || (c == '.') || (c == '\n')) {

			/* Check if there are characters in a word. */
			if (iChars) {
				/* Reallocate the memory for the word. */
				document[iParagraphs][iSentences][iWords] = realloc(document[iParagraphs][iSentences][iWords], (iChars + 1) * sizeof(char));
				/* Put the word in it's place. */
				strcpy(document[iParagraphs][iSentences][iWords], word);
				/* Reset character counter. */
				iChars = 0;
			}

			/* Got a space, so the word is finished. */
			if (c == ' ') {
				DEBUG_PRINTF("Next word. Word = %s. Index of: Chars = %d, Words = %d, Sentences = %d, Paragraphs = %d.\r\n", word, iChars, iWords, iSentences, iParagraphs);
	  			iWords++;
				document[iParagraphs][iSentences] = realloc(document[iParagraphs][iSentences], (iWords + 1)*sizeof(char*)); /* Make space for next pointer to a string (word). */
				document[iParagraphs][iSentences][iWords] = NULL; /* Initialize word to NULL. */
			} else
			/* Got a dot, so the sentence is finished. */
			if (c == '.') {
				DEBUG_PRINTF("Next sentence. Word = %s. Index of: Chars = %d, Words = %d, Sentences = %d, Paragraphs = %d.\r\n", word, iChars, iWords, iSentences, iParagraphs);
				iWords = 0;
				iSentences++;
				document[iParagraphs] = realloc(document[iParagraphs], (iSentences + 1) * sizeof(char**)); /* Make space for next pointer to a sentence. */
				document[iParagraphs][iSentences] = malloc(sizeof(char**)); /* Make space for next pointer to a string (word). */
				document[iParagraphs][iSentences][iWords] = NULL; /* Initialize word to NULL. */
			} else
			/* Got a new line, so the paragraph is finished. */
			if (c == '\n') {
				DEBUG_PRINTF("Next paragraph. Word = %s. Index of: Chars = %d, Words = %d, Sentences = %d, Paragraphs = %d.\r\n", word, iChars, iWords, iSentences, iParagraphs);
				iWords = 0;
				iSentences = 0;
				iParagraphs++;
				document = realloc(document, (iParagraphs + 1) * sizeof(char****)); /* Make space for next pointer to a paragraph. */
				document[iParagraphs] = malloc(sizeof(char***)); /* Make space for next pointer to a sentence. */
				document[iParagraphs][iSentences] = malloc(sizeof(char**)); /* Make space for next pointer to a string (word). */
				document[iParagraphs][iSentences][iWords] = NULL; /* Initialize word to NULL. */
			}
		} else
		/* Unexpected character. */
		{
			DEBUG_PRINTF("\r\n");
		}
	}

	free(word);
	//free(document); // we will return locally allocated variable here and hope the program frees the memory later on

	return document;
}

char* get_input_text() {
	int paragraph_count;
	scanf("%d", &paragraph_count);

	char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
	memset(doc, 0, sizeof(doc));
	getchar();
	for (int i = 0; i < paragraph_count; i++) {
		scanf("%[^\n]%*c", p[i]);
		strcat(doc, p[i]);
		if (i != paragraph_count - 1)
			strcat(doc, "\n");
	}

	char* returnDoc = (char*)malloc((strlen(doc) + 1) * (sizeof(char)));
	strcpy(returnDoc, doc);
	return returnDoc;
}

void print_word(char* word) {
	printf("%s", word);
}

void print_sentence(char** sentence) {
	int word_count;
	scanf("%d", &word_count);
	for (int i = 0; i < word_count; i++) {
		printf("%s", sentence[i]);
		if (i != word_count - 1)
			printf(" ");
	}
}

void print_paragraph(char*** paragraph) {
	int sentence_count;
	scanf("%d", &sentence_count);
	for (int i = 0; i < sentence_count; i++) {
		print_sentence(*(paragraph + i));
		printf(".");
	}
}

int main()
{
	char* text = get_input_text();
	char**** document = get_document(text);

	int q;
	scanf("%d", &q);

	while (q--) {
		int type;
		scanf("%d", &type);

		if (type == 3) {
			int k, m, n;
			scanf("%d %d %d", &k, &m, &n);
			char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
			print_word(word);
		}

		else if (type == 2) {
			int k, m;
			scanf("%d %d", &k, &m);
			char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
			print_sentence(sentence);
		}

		else {
			int k;
			scanf("%d", &k);
			char*** paragraph = kth_paragraph(document, k);
			print_paragraph(paragraph);
		}
		printf("\n");
	}
}
