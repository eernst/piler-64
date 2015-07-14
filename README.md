# PILER-64
"PILER is public domain software for analyzing repetitive DNA found in genome sequences." - http://drive5.com/piler/

PILER was originally conceived and implemented by Robert Edgar and Eugene Myers. This derivative version of PILER adds support for 64-bit architectures, and should run to completion without malloc errors on genomes with large, diverse repeat landscapes. Only changes to memory allocation code have been made, so results should be consistent for input data that successfully runs with the version distributed at drive5.com. If you notice discrepencies, please raise an issue here on GitHub. 

## License
The modifications to PILER distributed here are released to the public domain.

## Citing
R.C. Edgar and E.W. Myers, *PILER: identification and classification of genomic repeats.*
Bioinformatics. 2005 Jun 1;21 Suppl 1:i152-i158
