#include "piler2.h"

static const char Letter[5] = { 'A', 'C', 'G', 'T', '-'};

static void GetCounts(const char *Seqs, int ColCount, int SeqCount,
  int ColIndex, int Counts[5])
	{
	memset(Counts, 0, 5*sizeof(unsigned));
	for (int SeqIndex = 0; SeqIndex < SeqCount; ++SeqIndex)
		{
		char c = Seqs[SeqIndex*ColCount + ColIndex];
		c = toupper(c);
		switch (c)
			{
		case 'a':
		case 'A':
			++(Counts[0]);
			break;
		case 'c':
		case 'C':
			++(Counts[1]);
			break;
		case 'g':
		case 'G':
			++(Counts[2]);
			break;
		case 't':
		case 'T':
			++(Counts[3]);
			break;
		case '-':
			++(Counts[4]);
			break;
			}
		}
	}

static bool Conserved(const char *Seqs, int ColCount, int SeqCount, int Col)
	{
	int Counts[5];
	GetCounts(Seqs, ColCount, SeqCount, Col, Counts);
	if (Counts[4] > 0)
		return false;

	for (int i = 0; i < 4; ++i)
		if (Counts[i] != 0 && Counts[i] != SeqCount)
			return false;

	return true;
	}

static void FindStartEndExact(const char *Seqs, int ColCount, int SeqCount,
  int *ptrStart, int *ptrEnd)
	{
	int BestLength = 0;
	int BestStart = 0;
	int BestEnd = 0;
	int Length = 0;
	int Start = 0;
	for (int Col = 0; Col <= ColCount; ++Col)
		{
		if (Col != ColCount && Conserved(Seqs, ColCount, SeqCount, Col))
			{
			if (Start == -1)
				{
				Start = Col;
				Length = 1;
				}
			else
				++Length;
			}
		else
			{
			if (Length > BestLength)
				{
				BestStart = Start;
				BestEnd = Col - 1;
				if (BestEnd - BestStart + 1 != Length)
					Quit("BestEnd");
				}
			Length = -1;
			Start = -1;
			}
		}
	*ptrStart = BestStart;
	*ptrEnd = BestEnd;
	}

void Cons()
	{
	const char *InputFileName = RequiredValueOpt("cons");
	const char *OutputFileName = RequiredValueOpt("out");
	const char *Label = RequiredValueOpt("label");
	bool Exact = FlagOpt("exact");

	ProgressStart("Reading alignment");
	int ColCount;
	int SeqCount;
	const char *Seqs = ReadAFA(InputFileName, &ColCount, &SeqCount);
	ProgressDone();
	
	Progress("%d seqs, length %d", SeqCount, ColCount);

	char *ConsSeq = all(char, ColCount+1);
	int ConsSeqLength = 0;

	int StartCol = 0;
	int EndCol = ColCount - 1;

	if (Exact)
		FindStartEndExact(Seqs, ColCount, SeqCount, &StartCol, &EndCol);

	for (int Col = StartCol; Col <= EndCol; ++Col)
		{
		int Counts[5];
		GetCounts(Seqs, ColCount, SeqCount, Col, Counts);
		int MaxCount = 0;
		char MaxLetter = 'A';
		for (int i = 0; i < 4; ++i)
			{
			if (Counts[i] > MaxCount)
				{
				MaxLetter = Letter[i];
				MaxCount = Counts[i];
				}
			}
		if (MaxLetter == '-')
			continue;
		ConsSeq[ConsSeqLength++] = MaxLetter;
		}

	FILE *f = OpenStdioFile(OutputFileName, FILEIO_MODE_WriteOnly);
	WriteFasta(f, ConsSeq, ConsSeqLength, Label);
	}
