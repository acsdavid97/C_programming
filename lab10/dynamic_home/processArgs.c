/** Example of using getop for opening and input an an output file
* Process arguments to open input and output file
*
*/
#include "processArgs.h"

/** \brief Process command line arguments (passed here from main)
 *
 * \param argc int count of program args
 * \param argv[] char* program arguments from command line
 * \param fpIn FILE** pointer to FILE to return input stream pointer
 * \param fpOut FILE** pointer to FILE pointer return output stream pointer
 * \return int
 *
 */
int processArgs(int argc, char *argv[], FILE **fpIn, FILE **fpOut)
{
    char *inputFilename = NULL; // naem of inut file
    char *outputFilename = NULL; // name of output file
    int index; // to print unrecognized args
    int c; // current option switch

    while ((c = getopt (argc, argv, "i:o:")) != -1)
        switch (c)
        {
        case 'i':
            inputFilename = optarg;
            break;
        case 'o':
            outputFilename = optarg;
            break;
        case '?':
            if (optopt == 'i' || optopt == 'o')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
        }
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    // attempt to open input; on failure default to stdin
    if (inputFilename)
        *fpIn = fopen(inputFilename, "r");
    if (!*fpIn)
    {
        perror(inputFilename);
        puts("Input defaults to stdin");
        *fpIn = stdin;
    }
    else
    {
        printf("successfully opened input file: %s\n", inputFilename);
    }
    // attempt to open output; on failure default to stdout
    if (outputFilename)
        *fpOut = fopen(outputFilename, "w");
    if (!*fpOut)
    {
        perror(outputFilename);
        puts("Output defaults to stdout");
        *fpOut = stdout;
    }
    else
    {
        printf("successfully opened output file: %s\n", outputFilename);
    }
    return 1;
}
