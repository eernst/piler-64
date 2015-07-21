#include "piler2.h"

static void WriteCrisp(FILE *f, const PileData &Pile, int PileIndex)
	{
	int FamIndex = Pile.FamIndex;
	assert(FamIndex >= 0);

	int ContigFrom;
	const char *ContigLabel = GlobalToContig(Pile.From, &ContigFrom);
	const int Length = Pile.To - Pile.From + 1;
	const int ContigTo = ContigFrom + Length - 1;
	const char Strand = Pile.Rev ? '-' : '+';

// GFF fields are:
// <seqname> <source> <feature> <start> <end> <score> <strand> <frame> [attributes] [comments]
//     0         1         2        3      4      5        6       7         8           9
	fprintf(f, "%s\tpiler\ttrs\t%d\t%d\t0\t%c\t.\tFamily %d ; Pile %d\n",
	  ContigLabel,
	  ContigFrom + 1,
	  ContigTo + 1,
	  Strand,
	  FamIndex,
	  PileIndex);
	}

void WriteCrispFile(const char *OutputFileName, const PileData *Piles, int PileCount)
	{
	FILE *f = OpenStdioFile(OutputFileName, FILEIO_MODE_WriteOnly);

	for (int PileIndex = 0; PileIndex < PileCount; ++PileIndex)
		{
		const PileData &Pile = Piles[PileIndex];
		if (-1 == Pile.FamIndex)
			continue;

		WriteCrisp(f, Pile, PileIndex);
		}

	fclose(f);
	}

void WriteArray(FILE *f, int FamIndex, int Lo, int Hi)
	{
	assert(FamIndex >= 0);

	int ContigFrom;
	const char *ContigLabel = GlobalToContig(Lo, &ContigFrom);
	const int Length = Hi - Lo + 1;
	const int ContigTo = ContigFrom + Length - 1;
	const char Strand = '+';

// GFF fields are:
// <seqname> <source> <feature> <start> <end> <score> <strand> <frame> [attributes] [comments]
//     0         1         2        3      4      5        6       7         8           9
	fprintf(f, "%s\tpiler\ttrs\t%d\t%d\t0\t%c\t.\tFamily %d\n",
	  ContigLabel,
	  ContigFrom + 1,
	  ContigTo + 1,
	  Strand,
	  FamIndex);
	}
