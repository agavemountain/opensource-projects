/* schema.c
 
    build two C language schema files from CDATA schema
 input: <application>sch
 output: <application>.h contains:
        data element enums
        file enums
        record structs
        <application>.c contains
        ascii strings fro file and data element names
        data element masks array
        data element types array
        element length array
        data base schema arrays
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cdata.h"

static struct dict {
    char dename[NAMLEN+1];
    char detype;
    int delen;
    char *demask;
} dc [MXELE];

static int dectr = 0;
static int fctr = 0;
static char filenames [MXFILS][NAMLEN+1];
static int fileele[MXFILS][MXELE];
static int ndxele[MXFILS][MXINDEX][MXCAT];

static char word[NAMLEN+1];
static int lnctr = 0;
static char ln [160];

/* error codes */
enum error_codes {
    ER_NAME = 1,
    ER_LENGTH,
    ER_COMMA,
    ER_TYPE,
    ER_QUOTE,
    ER_SCHEMA,
    ER_COMMAND,
    ER_EOF,
    ER_DUPLNAME,
    ER_UNKOWN_ELEMENT,
    ER_TOOMANY_ELEMENTS,
    ER_MEMORY,
    ER_UNKNOWN_FILENAME,
    ER_TOOMANY_INDEXES,
    ER_TOOMANY_IN_INDEX,
    ER_DUPL_ELEMENT,
    ER_TOOMANY_FILES,
    ER_NOSCHEMA,
    ER_NOSUCH_SCHEMA,
    ER_TERMINAL
};

/* ERROR MESSAGES */
static struct {
    enum error_codes ec;
    char *errormsg;
} ers[] = {
    ER_NAME, "invalid name",
    ER_LENGTH, "invalid length",
    ER_COMMA, "comma missing",
    ER_TYPE, "invalid data type",
    ER_QUOTE, "quote missing",
    ER_SCHEMA, "#schema missing",
    ER_COMMAND, "#<command> missing",
    ER_EOF, "unexpected endo fo file",
    ER_DUPLNAME, "duplicate file name",
    ER_UNKOWN_ELEMENT, "unknown data element",
    ER_TOOMANY_ELEMENTS, "too any data elements",
    ER_MEMORY, "out of memory",
    ER_UNKNOWN_FILENAME, "unknown file name",
    ER_TOOMANY_INDEXES, "too any indexes in file",
    ER_TOOMANY_IN_INDEX, "too many elements in index",
    ER_DUPL_ELEMENT, "duplicate data element",
    ER_TOOMANY_FILES, "too many files",
    ER_NOSCHEMA, "no schema file specified",
    ER_NOSUCH_SCHEMA, "no such schema file",
    ER_TERMINAL, NULL
};

static void de_dict(void);
static void files(void);
static void keys(void);
static void defout(const char *);
static void schout(const char *);
static void lcase(char *, const char *);
static void error(const enum error_codes);
static void get_line(void);
static void skip_white(char **);
static char *get_word(char *);
static void name_val(void);
static void numb_val(void);
static void  expect_comma(char **);

#define iswhite(c) ((c)==' '||(c)=='\t')
#define REMARK ';'

static FILE *fp;

/* main program */
int main (int argc, char *argv[])
{
    char fname[64];
    char *cp;
    
    if (argc > 1) {
        strcpy(fname, argv[1]);
        if ((cp=strrchr(fname, '.')) == NULL) {
            cp = fname+strlen(fname);
            strcpy(cp, ".sch");
        }
        if ((fp = fopen(fname, "r")) == NULL) {
            error(ER_NOSUCH_SCHEMA);
            exit(1);
        }
        *cp = '\0';
        get_line();
        if(strncmp(ln, "#schema ",8))
            error(ER_SCHEMA);
        else {
            get_word(ln+8);
            name_val();
        }
        get_line();
        while(strncmp(ln, "#end schema", 11)) {
            if (strncmp(ln, "#dictionary", 11) == 0)
                de_dict();
            else if (strncmp(ln, "#file ", 6) == 0)
                files();
            else if (strncmp(ln, "#key ", 5) == 0)
                keys();
            else
                error(ER_COMMAND);
            get_line();
        }
        fclose(fp);
        defout(fname);
        schout(fname);
    }
    else
        error(ER_NOSCHEMA);
    exit(0);
    return 0;   // warning.
}

/* build the data element dictionary */
static void de_dict(void)
{
    char *cp, *cp1;
    int el, masklen, buildmask;
    while(TRUE) {
        get_line();
        if(strncmp(ln, "#end dictionary", 15)==0)
            break;
        if (dectr == MXELE) {
            error(ER_TOOMANY_ELEMENTS);
            continue;
        }
        cp = get_word(ln);
        name_val();
        for (el=0; el < dectr; el++)
            if (strcmp(word, dc[el].dename) == 0) {
                error(ER_DUPL_ELEMENT);
                continue;
            }
        strcpy(dc[dectr].dename, word);
        expect_comma(&cp);
        skip_white(&cp);
        switch (*cp) {
            case 'A':
            case 'Z':
            case 'C':
            case 'N':
            case 'D':   break;
            default: error(ER_TYPE);
                continue;
        }
        dc[dectr].detype = *cp++;
        expect_comma(&cp);
        cp = get_word(cp);
        numb_val();
        dc[dectr].delen = atoi(word);
        skip_white(&cp);
        if (*cp++ == ',') {
            buildmask= FALSE;
            /* comma means display mask is coded */
            skip_white(&cp);
            if (*cp != '\"') {
                error(ER_QUOTE);
                continue;
            }
            cp1=cp+1;
            while (*cp1 != '\"' && *cp1 && *cp1 != '\n') cp1++;
            if (*cp1++ != '\"') {
                error(ER_QUOTE);
                continue;
            }
            *cp1= '\0';
            masklen = (cp1 - cp) + 1;
        }
        else {
            // no display mask, build one
            buildmask = TRUE;
            masklen = dc[dectr].delen+3;
        }
        if ((dc[dectr].demask = malloc(masklen)) == NULL) {
            error(ER_MEMORY);
            exit(1);
        }
        if(buildmask) {
            dc[dectr].demask[0] = '\"';
            memset(dc[dectr].demask+1, '_', masklen-3);
            dc[dectr].demask[masklen-2]= '\"';
            dc[dectr].demask[masklen-1]= '\0';
        }
        else
            strcpy(dc[dectr].demask, cp);
        
        dectr++;
    
    }
}

static void files(void)
{
    int i, el=0;
    if (fctr == MXFILS) {
        error(ER_TOOMANY_FILES);
    }
    get_word(ln + 6);
    name_val();
    for (i=0; i< fctr; i++) {
        if (strcmp(word, filenames[i]) == 0) {
            error(ER_DUPLNAME);
        }
    }
    strcpy(filenames[fctr], word);
    // process the file's data elements.
    while(TRUE) {
        get_line();
        if (strncmp(ln, "#end file", 9) == 0) break;
        if (el== MXELE) {
            error(ER_TOOMANY_ELEMENTS);
            continue;
        }
        get_word(ln);
        for (i=0; i< dectr; i++) {
            if (strcmp(word, dc[i].dename) == 0)
                break;
        }
        if (i==dectr) error(ER_UNKOWN_ELEMENT);
        else if (fctr < MXFILS)
            fileele[fctr][el++] = i+1;
    }
    if (fctr < MXFILS)
        fctr++;
                
}

// build the index descriptions
static void keys(void)
{
    char *cp;
    int f, el, x, cat = 0;
    cp = get_word(ln + 5);  // get filename
    for (f =0; f < fctr; f++) // in schema?
        if (strcmp(word, filenames[f])==0) break;
    if (f == fctr) {
        error(ER_UNKNOWN_FILENAME);
        return;
    }
    for (x=0; x< MXINDEX; x++)
        if (*ndxele[f][x]==0) break;
    
    if (x == MXINDEX) {
        error(ER_TOOMANY_INDEXES);
        return;
    }
    while (cat < MXCAT) {
        cp = get_word(cp);  // get index name
        for (el=0; el< dectr; el++) // in dictionary
            if (strcmp(word, dc[el].dename)==0) break;
        if (el==dectr) {
            error(ER_UNKOWN_ELEMENT);
            break;
        }
        ndxele[f][x][cat++] = el + 1; // post element
        skip_white(&cp);
        if (*cp++ != ',') break;
        if (cat == MXCAT) {
            error(ER_TOOMANY_IN_INDEX);
            break;
        }
    }
}

// write the data base .h header file:
//  schema enumjs and struct definitions
static void defout(const char *fname)
{
    int f, el, fel;
    char name[NAMLEN+1];
    char fn[64];
    
    strcpy(fn, fname);
    strcat(fn, ".h");
    fp=fopen(fn, "w");
    
    fprintf(fp, "/* %s */\n", fn);
    fprintf(fp, "\n#define APPLICATION_H_\n");
    fprintf(fp, "\ntypedef enum elements {");
    for (el = 0; el < dectr; el++)
        fprintf(fp, "\n\t%s%s,", dc[el].dename, el ? "" : "=1");
    fprintf(fp, "\n\tTermElement = 32367");
    fprintf(fp, "\n} ELEMENT; \n");
    
    fprintf(fp, "\ntypedef enum files {");
    for (f=0; f< fctr; f++)
        fprintf(fp, "\n\t%s,", filenames[f]);
    fprintf(fp, "\n\tTermFile = 32367");
    fprintf(fp, "\n} DBFILE;\n");
    
    // write record structures.
    for(f=0; f<fctr; f++) {
        lcase(name, filenames[f]);
        fprintf(fp, "\nstruct %s {", name);
        el =0;
        while (( fel=fileele[f][el++]) != 0) {
            lcase(name, dc[fel-1].dename);
            fprintf(fp, "\n\tchar %s[%d];", name, dc[fel-1].delen +1 );
        }
        fprintf(fp, "\n};\n ");
    }
    fprintf(fp, "\n#include \"cdata.h\"\n");
    fclose(fp);
    
}

static void schout(const char *fname)
{
    int f, el, x, x1, cat, fel;
    char name[NAMLEN+1];
    char fn[64];
    
    strcpy(fn, fname);
    strcat(fn, ".c");
    fp=fopen(fn, "w");
    
    fprintf(fp, "/* %s */\n", fn);
    fprintf(fp, "\n#include \"%s.h\"\n", fname);
    
    fprintf(fp, "\nconst char *denames[] = {");
    for (el=0; el < dectr; el++)
        fprintf(fp, "\n\t\"%s\",",dc[el].dename);
    fprintf(fp, "\n\tNULL\n};\n");
    
    fprintf(fp, "\nconst char eltype[] = \"");
    for (el=0; el < dectr; el++) putc(dc[el].detype, fp);
    fprintf(fp, "\";\n");
    
    fprintf(fp, "\nconst char *elmask[] = {");
    for (el = 0; el < dectr; el++)
        fprintf(fp, (el < dectr-1 ? "\n\t%s," : "\n\t%s"), dc[el].demask);
    fprintf(fp, "\n};\n");
    free(dc[el].demask);
    
    fprintf(fp, "\nconst char *dbfiles[] = {");
    for (f=0; f<fctr; f++)
        fprintf(fp, "\n\t\"%s\",", filenames[f]);
    fprintf(fp, "\n\tNULL\n};\n");
    
    fprintf(fp, "\n\nconst int elen[] = {");
    for (el=0; el< dectr;el++) {
        if ((el %25) ==0) fprintf(fp, "\n\t");
        fprintf(fp, (el < dectr-1 ? "%d," : "%d"), dc[el].delen);
    }
    fprintf(fp, "\n};\n");
    
    for (f = 0; f < fctr; f++) {
        lcase(name, filenames[f]);
        fprintf(fp, "\n\nconst ELEMENT f_%s[] = {", name);
        el=0;
        while((fel = fileele[f] [el++]) != 0)
            fprintf(fp, "\n\t%s,", dc[fel-1].dename);
        fprintf(fp, "\n\t0\n;");
    }
    
    fprintf(fp, "\n\nconst ELEMENT *file_ele[] = {");
    for (f=0; f < fctr; f++) {
        lcase (name, filenames [f]);
        fprintf(fp, "\n\tf_%s,", name);
        
    }
    fprintf(fp, "\n\t0\n};\n");
            
    // write index arrays.
    for (f=0; f < fctr; f++) {
        lcase(name, filenames[f]);
        for (x=0; x < MXINDEX; x++) {
            if (*ndxele[f][x]==0) break;
            fprintf(fp, "\nconst ELEMENT x%d_%s[] = {", x+1, name);
            for (cat = 0; cat < MXCAT; cat++) {
                if (ndxele[f][x][cat]) fprintf(fp, "\n\t%s,", dc[ndxele[f][x][cat]-1].dename);
            }
            fprintf(fp, "\n\t0\n};\n");
        }
        fprintf(fp, "\ncopnst ELEMENT *x_%s[]={", name);
        
        for (x1=0; x1< x; x1++) fprintf(fp, "\n\tx%d_%s,", x1+1, name);
        fprintf(fp, "\n\tNULL\n};\n");
        
    }
    fprintf(fp, "\nconst ELEMENT **index_ele[] = {");
    for (f=0; f < fctr; f++) {
        lcase(name, filenames[f]);
        fprintf(fp, "\n\tx_%s,", name);
    }
    fprintf(fp, "\n\tNULL\n;\n");
    
    fprintf(fp, "\n\n#ifdef NULL_IS_DEFINED");
    fprintf(fp, "\n\t#undef NULL");
    fprintf(fp, "\n\t#undef NULL_IS_DEFINED");
    fprintf(fp, "\n#endif\n\n");
    
    fclose(fp);
    
}

static void lcase(char *s1, const char *s2)
{
    while (*s2) {
        *s1 = tolower(*s2);
        s1++;
        s2++;
    }
    *s1 = '\0';
}

// get a linhe of data from schema input stream */
static void get_line()
{
    char *cp ;
    *ln = '\0';
    while (*ln == '\0' || *ln == REMARK || *ln == '\n') {
           cp = fgets (ln, 120, fp);
           if (cp == NULL) {
               error(ER_EOF);
               exit(1);
           }
           lnctr++;
    }

}
           
static void skip_white(char **s)
{
   while (iswhite(**s)) (*s)++;
}

static char *get_word(char *cp)
{
   int wl=0, fst =0;
   skip_white(&cp);
   while(*cp && *cp != '\n' && *cp != ',' && iswhite(*cp) == 0) {
       if (wl == NAMLEN && fst == 0) {
           error(ER_NAME);
           fst++;
       }
       else word[wl++]= *cp++;
   }
   word[wl] = '\0';
   return cp;
   
}

static void name_val(void)
{
    char *s = word;
    if (isalpha(*s)) {
        while(isalpha(*s) || isdigit(*s) || *s == '_') {
            *s = toupper(*s);
            s++;
        }
        if (*s == '\0') return;
    }
    error(ER_NAME);
}

static void numb_val(void)
{
    char *s = word;
    do {
        if (isdigit(*s++)==0) {
            error(ER_LENGTH);
            break;
        }
    } while (*s);
}

static void expect_comma(char **cp)
{
    skip_white(cp);
    if (*(*cp)++ != ',')
        error(ER_COMMA);
}

static void error(const enum error_codes n)
{
    static int erct=0;
    static int erlin = 0;
    int err;
    
    for (err=0; ers[err].ec != ER_TERMINAL; err++)
        if (n==ers[err].ec) break;
    if (erlin != lnctr) {
        erlin = lnctr;
        fprintf(stderr, "\nLine %d: %s", lnctr, ln);
    }
    fprintf(stderr, "Error %d: %s\n", n, ers[err].errormsg);
    if (erct++ == 5) {
        erct = 0;
        fprintf(stderr, "\nContinue (y/n) ...");
        if (tolower(getc(stdin)) != 'y')
            exit(1);
    }
}

