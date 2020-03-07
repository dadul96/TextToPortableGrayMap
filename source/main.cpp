#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getCharCount(char* pInFileName);
void generatePicture(char* pInFileName, char* pOutFileName);


int main() {
	char inFileName[] = "input.txt";
	char outFileName[] = "output.pgm";

	generatePicture(inFileName, outFileName);

	return 0;
}


int getCharCount(char* pInFileName) {
	FILE* inputFile;
	int count = 0;
	
	fopen_s(&inputFile, pInFileName, "rt");
	if (inputFile == NULL)
	{
		perror("ERROR: The input file could not be opened!");
	}
	else
	{
		int asciiValue = 0;
		do
		{
			asciiValue = fgetc(inputFile);
			count++;
		} while (asciiValue != EOF);
		fclose(inputFile);
	}
	return count;
}


void generatePicture(char* pInFileName, char* pOutFileName) {
	FILE* inputFile;
	FILE* outputFile;
	int charCount = 0;
	int picSize = 0;

	charCount = getCharCount(pInFileName);

	if (charCount > 0)
	{
		picSize = ((int)sqrt(charCount) + 1);	//calculate the n by n size of the picture
	}
	else
	{
		perror("ERROR: The input file does not contain any characters!");
	}
	

	fopen_s(&inputFile, pInFileName, "rt");
	fopen_s(&outputFile, pOutFileName, "wt");

	if (inputFile == NULL)
	{
		perror("ERROR: The input file could not be opened!");
	}
	else
	{
		if (outputFile == NULL)
		{
			perror("ERROR: The output file could not be opened!");
		}
		else
		{
			int inCharValue = 0;
			int outCharValue = 0;
			int columns = 0;

			//Portable GrayMap (.pgm) header:
			fprintf_s(outputFile, "P2\n");                          //Gray-scale ASCII mode
			fprintf_s(outputFile, "%d  %d\n", picSize, picSize);    //Image size n by n pixels
			fprintf_s(outputFile, "255\n");                         //Gray-scale resolution

			//Portable GrayMap (.pgm) picture data:
			do
			{
				inCharValue = fgetc(inputFile);
				if (inCharValue >= 0)
				{
					outCharValue = (inCharValue * 2) + 1;	//Algorithm to map values from 0-127 to 1-255
					if (columns < picSize)
					{
						columns++;
						fprintf_s(outputFile, "  %d", outCharValue);
					}
					else
					{
						columns = 0;
						fprintf_s(outputFile, "\n %d", outCharValue);
					}
				}
			} while (inCharValue != EOF);
			fclose(inputFile);

			fprintf_s(outputFile, "\n");
			fclose(outputFile);
		}
	}
}
