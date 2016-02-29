/* Processed by ecpg (4.11.0) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "sdap.pgc"
/*
 * File - sdap.pgc (Need the .pgc extension!) 
 *
 * Desc - This is a simple skeleton program using Embedded SQL to read all
 *        of the rows from the table "sales" and output to the console.
 *        Simple but it contains all of the essential features of ESQL 
 *        discussed in class!
 *
 * Steps to run this program : 
 *  1. In the program (L49), modify [dbname], [username], [password] to
 *     yours ([dbname] is the same as your [username] by default).
 *  2. Preprocessor - $ ecpg -I "C:\Program Files\PostgreSQL\9.4\include" sdap.pgc
 *  3. Compile      - $ gcc -c -I "C:\Program Files\PostgreSQL\9.4\include" sdap.c
 *  4. Link         - $ gcc -L "C:\Program Files\PostgreSQL\9.4\lib" -lecpg -o sdap sdap.o
 *  5. Execute      - $ .\sdap
 */

#include	<stdio.h>
#include <string.h>
//----------------------------------------------------------------------
// HOST VARIABLES definitions
//----------------------------------------------------------------------
/* exec sql begin declare section */
 
		
		
	    
	    
		 
		
		 
	

#line 32 "sdap.pgc"
 struct { 
#line 25 "sdap.pgc"
 char * cust ;
 
#line 26 "sdap.pgc"
 char * prod ;
 
#line 27 "sdap.pgc"
 short dd ;
 
#line 28 "sdap.pgc"
 short mm ;
 
#line 29 "sdap.pgc"
 short yy ;
 
#line 30 "sdap.pgc"
 char * state ;
 
#line 31 "sdap.pgc"
 long quant ;
 } sale_rec ;
/* exec sql end declare section */
#line 33 "sdap.pgc"


#line 1 "D:/Program Files/PostgreSQL/9.5/include/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#ifndef PGDLLIMPORT
#if  defined(WIN32) || defined(__CYGWIN__)
#define PGDLLIMPORT __declspec (dllimport)
#else
#define PGDLLIMPORT
#endif   /* __CYGWIN__ */
#endif   /* PGDLLIMPORT */

#define SQLERRMC_LEN	150

#ifdef __cplusplus
extern		"C"
{
#endif

struct sqlca_t
{
	char		sqlcaid[8];
	long		sqlabc;
	long		sqlcode;
	struct
	{
		int			sqlerrml;
		char		sqlerrmc[SQLERRMC_LEN];
	}			sqlerrm;
	char		sqlerrp[8];
	long		sqlerrd[6];
	/* Element 0: empty						*/
	/* 1: OID of processed tuple if applicable			*/
	/* 2: number of rows processed				*/
	/* after an INSERT, UPDATE or				*/
	/* DELETE statement					*/
	/* 3: empty						*/
	/* 4: empty						*/
	/* 5: empty						*/
	char		sqlwarn[8];
	/* Element 0: set to 'W' if at least one other is 'W'	*/
	/* 1: if 'W' at least one character string		*/
	/* value was truncated when it was			*/
	/* stored into a host variable.             */

	/*
	 * 2: if 'W' a (hopefully) non-fatal notice occurred
	 */	/* 3: empty */
	/* 4: empty						*/
	/* 5: empty						*/
	/* 6: empty						*/
	/* 7: empty						*/

	char		sqlstate[5];
};

struct sqlca_t *ECPGget_sqlca(void);

#ifndef POSTGRES_ECPG_INTERNAL
#define sqlca (*ECPGget_sqlca())
#endif

#ifdef __cplusplus
}
#endif

#endif

#line 34 "sdap.pgc"

//----------------------------------------------------------------------
// HOST VARIABLES definitions
//----------------------------------------------------------------------
struct Data{
   char    cust[20];
   char    prod[20];
   short   dd;
   short   mm;
   short   yy;
   char    state[3];
   long    quant; 
};
//----------------------------------------------------------------------
// FUNCTION PROTOTYPE declaration
//----------------------------------------------------------------------
void	store_record(struct Data *, int); //output records to the console
void  sort(struct Data *);
void  output1(struct Data *, int, int);
void  output2(struct Data *, int, int, int);
void  query1(struct Data *);
void  query2(struct Data *);
//----------------------------------------------------------------------
int main(int argc, char* argv[])
//----------------------------------------------------------------------
{
   struct Data data[500];
   int counter=0;
   //----------------------------------------------------------------------
   // DATABASE CONNECTION
   //----------------------------------------------------------------------
   { ECPGconnect(__LINE__, 0, "postgres@localhost:5432" , "postgres" , "zhy199208" , NULL, 0); }
#line 65 "sdap.pgc"

   
   if (sqlca.sqlcode != 0) {	// login error
   	printf ("Login error!!!\n");
   	return -1;
   }
   /* exec sql whenever sqlerror  sqlprint ; */
#line 71 "sdap.pgc"

   //----------------------------------------------------------------------
   // READ RECORDS
   //----------------------------------------------------------------------
   /* declare mycursor cursor for select * from sales */
#line 75 "sdap.pgc"

   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set transaction read only", ECPGt_EOIT, ECPGt_EORT);
#line 76 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 76 "sdap.pgc"

   // Open cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare mycursor cursor for select * from sales", ECPGt_EOIT, ECPGt_EORT);
#line 78 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 78 "sdap.pgc"

   // Fetch Data
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 80 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 80 "sdap.pgc"
 //fetch the first row
   while (sqlca.sqlcode == 0) {
      store_record(data, counter);
      { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch from mycursor", ECPGt_EOIT, 
	ECPGt_char,&(sale_rec.cust),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.prod),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.dd),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.mm),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(sale_rec.yy),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,&(sale_rec.state),(long)0,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(sale_rec.quant),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 83 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 83 "sdap.pgc"
 //fetch the rest rows
      counter++;
   }
   // Close cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close mycursor", ECPGt_EOIT, ECPGt_EORT);
#line 87 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 87 "sdap.pgc"

   sort(data);
   printf(" CUSTOMER  MAX_Q  MAX_PROD  MAX_DATE    ST  MIN_Q  MIN_PROD  MIN_DATE    ST  AVG_Q\n");
   printf(" ========  =====  ========  ==========  ==  =====  ========  ==========  ==  =====\n");
   query1(data);
   printf("\n\n");
   printf(" CUSTOMER  PRODUCT  NY_MAX  DATE        NJ_MIN  DATE        CT_MIN  DATE      \n");
   printf(" ========  =======  ======  ==========  ======  ==========  ======  ==========\n");
   query2(data);
   return 0;
}

//----------------------------------------------------------------------
void	store_record(struct Data *data, int i)
//----------------------------------------------------------------------
{
   strcpy(data[i].cust, sale_rec.cust);
   strcpy(data[i].prod, sale_rec.prod);
   strcpy(data[i].state, sale_rec.state);
   data[i].yy = sale_rec.yy;
   data[i].dd = sale_rec.dd;
   data[i].mm = sale_rec.mm;
   data[i].quant = sale_rec.quant;
}

//----------------------------------------------------------------------
void  sort(struct Data *data)
//----------------------------------------------------------------------
{
   int minindex;
   char tempstr[20];
   for(int i=0; i<500; i++){
      minindex = i;
      for(int j=i+1; j<500; j++){
         if(strcmp(data[minindex].cust,data[j].cust)>0)
            minindex = j;
         else if(strcmp(data[minindex].cust,data[j].cust)==0){
            if(strcmp(data[minindex].prod,data[j].prod)>0)
               minindex = j;
         }
      }
      strcpy(tempstr, data[i].cust);
      strcpy(data[i].cust, data[minindex].cust);
      strcpy(data[minindex].cust, tempstr);
      strcpy(tempstr, data[i].prod);
      strcpy(data[i].prod, data[minindex].prod);
      strcpy(data[minindex].prod, tempstr);
   }
}
//----------------------------------------------------------------------
void  output1(struct Data *data, int min, int max)
//----------------------------------------------------------------------
{
      printf(" %-8s ",data[max].cust);   // Customer
      printf(" %5d ",data[max].quant);  // Quantity
      printf(" %-8s ",data[max].prod);   // Product
      printf(" %02d/%02d/%04d ",data[max].mm, data[max].dd, data[max].yy); //date
      printf(" %-2s ",data[min].state);  // State
      printf(" %5d ",data[min].quant);  // Quantity
      printf(" %-8s ",data[min].prod);   // Product
      printf(" %02d/%02d/%04d ",data[min].mm, data[min].dd, data[min].yy); //date
      printf(" %-2s ",data[min].state);  // State
      printf(" %5d \n",(data[min].quant+data[max].quant)/2);  // Average


   /*
   int i=0;
   for(; i<500; i++)
   {
      printf(" %-5s |",data[i].cust);   // Customer
      printf(" %-7s |",data[i].prod);   // Product
      printf("  %2d |",data[i].dd);     // Day
      printf("  %2d |",data[i].mm);     // Month
      printf(" %4d |",data[i].yy);      // Year
      printf(" %-5s |",data[i].state);  // State
      printf(" %5d \n",data[i].quant);  // Quantity
   }
   */
}
//----------------------------------------------------------------------
void output2(struct Data *data, int NY, int NJ, int CT){
//----------------------------------------------------------------------
   int index;
   if(NY!=-1){
      index = NY;
   }
   else if(NJ!=-1){
      index = NJ;
   }
   else
      index = CT;
   printf(" %-8s ",data[index].cust);   // Customer
   printf(" %-7s ",data[index].prod);   // Product
   if(NY!=-1){
      printf(" %6d ",data[NY].quant);  // Quantity
      printf(" %02d/%02d/%04d ",data[NY].mm, data[NY].dd, data[NY].yy); //date
   }
   else{
      printf("    N/A ");
      printf("        N/A ");
   }
   if(NJ!=-1){
      printf(" %6d ",data[NJ].quant);  // Quantity
      printf(" %02d/%02d/%04d ",data[NJ].mm, data[NJ].dd, data[NJ].yy); //date
   }
   else{
      printf("    N/A ");
      printf("        N/A ");
   }
   if(CT!=-1){
      printf(" %6d ",data[CT].quant);  // Quantity
      printf(" %02d/%02d/%04d \n",data[CT].mm, data[CT].dd, data[CT].yy); //date
   }
   else{
      printf("    N/A ");
      printf("        N/A \n");
   }
}
//----------------------------------------------------------------------
void query1(struct Data *data){
//----------------------------------------------------------------------
   char checkstr[20];
   strcpy(checkstr, data[0].cust);
   int minquant=0;
   int maxquant=0;
   for(int i=1; i<500; i++){
      if(strcmp(checkstr, data[i].cust)!=0){
         output1(data, minquant, maxquant);
         minquant=maxquant=i;
         strcpy(checkstr, data[i].cust);
      }
      else{
         if(data[minquant].quant>data[i].quant)
            minquant=i;
         if(data[maxquant].quant<data[i].quant)
            maxquant=i;
      }

   }
}
//----------------------------------------------------------------------
void query2(struct Data *data){
//----------------------------------------------------------------------
   char checkstr[20];
   strcpy(checkstr, data[0].prod);
   int NJ=-1;
   int NY=-1;
   int CT=-1;
   for(int i=0; i<500; i++){
      if(strcmp(checkstr, data[i].prod)!=0){
         output2(data, NY, NJ, CT);
         NY=NJ=CT=-1;
         strcpy(checkstr, data[i].prod);
      }
      else{
         if(strcmp(data[i].state,"NY")==0&&(NY==-1||data[i].quant>data[NY].quant)&&data[i].yy>2000)
            NY=i;
         if(strcmp(data[i].state,"NJ")==0&&(NJ==-1||data[i].quant<data[NJ].quant)&&data[i].yy>2000)
            NJ=i;
         if(strcmp(data[i].state,"CT")==0&&(CT==-1||data[i].quant<data[CT].quant))
            CT=i;
      }
   }
}