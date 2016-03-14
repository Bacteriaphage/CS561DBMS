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
 *  1. In the program (L93), modify [dbname], [username], [password] to
 *     yours ([dbname] is the same as your [username] by default).
 *  2. Preprocessor - $ ecpg -I "C:\Program Files\PostgreSQL\9.4\include" sdap.pgc
 *  3. Compile      - $ gcc -c -I "C:\Program Files\PostgreSQL\9.4\include" sdap.c
 *  4. Link         - $ gcc -L "C:\Program Files\PostgreSQL\9.4\lib" -lecpg -o sdap sdap.o
 *  5. Execute      - $ .\sdap
 */

#include <stdio.h>
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
//query 1 data structure
//for each customer, store max and min quantity of product along with their date, state and finally calculate average 
struct Data1{
   char    cust[20];
   char    max_prod[20];
   char    min_prod[20];
   short   max_dd;
   short   max_mm;
   short   max_yy;
   char    max_state[3];
   long    max_quant; 
   short   min_dd;
   short   min_mm;
   short   min_yy;
   char    min_state[3];
   long    min_quant;
   long    sum;
   long    count;
};
//query 2 data structure
//for each combination of customer and product, store max quantity in NY, min quantity in NJ and CT along with their date
struct Data2{
   char    cust[20];
   char    prod[20];
   long    NY_MAX;
   short   NY_month;
   short   NY_day;
   short   NY_year;
   long    NJ_MIN;
   short   NJ_month;
   short   NJ_day;
   short   NJ_year;
   long    CT_MIN;
   short   CT_month;
   short   CT_day;
   short   CT_year;
};
//----------------------------------------------------------------------
// FUNCTION PROTOTYPE declaration
//----------------------------------------------------------------------
void  process1(struct Data1 *, int *);
void  process2(struct Data2 *, int *);
void  output1(struct Data1 *, int);
void  output2(struct Data2 *, int);
//----------------------------------------------------------------------
int main(int argc, char* argv[])
//----------------------------------------------------------------------
{
   struct Data1 data1[500];
   struct Data2 data2[500];
   int counter1=0;
   int counter2=0;
   //----------------------------------------------------------------------
   // DATABASE CONNECTION
   //----------------------------------------------------------------------
   { ECPGconnect(__LINE__, 0, "postgres@localhost:5432" , "postgres" , "zhy199208" , NULL, 0); }
#line 93 "sdap.pgc"

   
   if (sqlca.sqlcode != 0) {  // login error
      printf ("Login error!!!\n");
      return -1;
   }
   /* exec sql whenever sqlerror  sqlprint ; */
#line 99 "sdap.pgc"

   //----------------------------------------------------------------------
   // READ RECORDS
   //----------------------------------------------------------------------
   /* declare mycursor cursor for select * from sales */
#line 103 "sdap.pgc"

   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set transaction read only", ECPGt_EOIT, ECPGt_EORT);
#line 104 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 104 "sdap.pgc"

   // Open cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare mycursor cursor for select * from sales", ECPGt_EOIT, ECPGt_EORT);
#line 106 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 106 "sdap.pgc"

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
#line 108 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 108 "sdap.pgc"
 //fetch the first row
   while (sqlca.sqlcode == 0) {
      process1(data1, &counter1);
      process2(data2, &counter2);
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
#line 112 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 112 "sdap.pgc"
 //fetch the rest rows
   }
   // Close cursor
   { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close mycursor", ECPGt_EOIT, ECPGt_EORT);
#line 115 "sdap.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 115 "sdap.pgc"

   //query print out
   printf(" CUSTOMER  MAX_Q  MAX_PROD  MAX_DATE    ST  MIN_Q  MIN_PROD  MIN_DATE    ST  AVG_Q\n");
   printf(" ========  =====  ========  ==========  ==  =====  ========  ==========  ==  =====\n");
   output1(data1, counter1);
   printf("\n\n");
   printf(" CUSTOMER  PRODUCT  NY_MAX  DATE        NJ_MIN  DATE        CT_MIN  DATE      \n");
   printf(" ========  =======  ======  ==========  ======  ==========  ======  ==========\n");
   output2(data2, counter2);
   return 0;
}

//----------------------------------------------------------------------
void output1(struct Data1 *data, int i)
//----------------------------------------------------------------------
{  
   for(int j = 0; j < i; j++){
      printf(" %-8s ",data[j].cust);   // Customer
      printf(" %5d ",data[j].max_quant);  // Quantity
      printf(" %-8s ",data[j].max_prod);   // Product
      printf(" %02d/%02d/%04d ",data[j].max_mm, data[j].max_dd, data[j].max_yy); //date
      printf(" %-2s ",data[j].max_state);  // State
      printf(" %5d ",data[j].min_quant);  // Quantity
      printf(" %-8s ",data[j].min_prod);   // Product
      printf(" %02d/%02d/%04d ",data[j].min_mm, data[j].min_dd, data[j].min_yy); //date
      printf(" %-2s ",data[j].min_state);  // State
      printf(" %5d \n",(data[j].sum/data[j].count));  // Average
   }
}
//----------------------------------------------------------------------
void output2(struct Data2 *data, int i){
//----------------------------------------------------------------------
   for(int j=0; j<i; j++){
      printf(" %-8s ",data[j].cust);   // Customer
      printf(" %-7s ",data[j].prod);   // Product
      if(data[j].NY_MAX!=-1){
         printf(" %6d ",data[j].NY_MAX);  // Quantity
         printf(" %02d/%02d/%04d ",data[j].NY_month, data[j].NY_day, data[j].NY_year); //date
      }
      else{
         printf("    N/A ");
         printf("        N/A ");
      }
      if(data[j].NJ_MIN!=-1){
         printf(" %6d ",data[j].NJ_MIN);  // Quantity
         printf(" %02d/%02d/%04d ",data[j].NJ_month, data[j].NJ_day, data[j].NJ_year); //date
      }
      else{
         printf("    N/A ");
         printf("        N/A ");
      }
      if(data[j].CT_MIN!=-1){
         printf(" %6d ",data[j].CT_MIN);  // Quantity
         printf(" %02d/%02d/%04d \n",data[j].CT_month, data[j].CT_day, data[j].CT_year); //date
      }
      else{
         printf("    N/A ");
         printf("        N/A \n");
      }
   }
}
//----------------------------------------------------------------------
void process1(struct Data1 *data, int *i){
//----------------------------------------------------------------------
   int j;
   for(j=0; j<*i; j++)
      if(strcmp(data[j].cust, sale_rec.cust)==0) break;
   if(j==*i){                                              //if there is no record of this customer, create a new one
      strcpy(data[*i].cust, sale_rec.cust);
      strcpy(data[*i].max_prod, sale_rec.prod);
      strcpy(data[*i].min_prod, sale_rec.prod);
      strcpy(data[*i].max_state, sale_rec.state);
      strcpy(data[*i].min_state, sale_rec.state);
      data[*i].max_dd=sale_rec.dd;
      data[*i].max_mm=sale_rec.mm;
      data[*i].max_yy=sale_rec.yy;
      data[*i].min_dd=sale_rec.dd;
      data[*i].min_mm=sale_rec.mm;
      data[*i].min_yy=sale_rec.yy;
      data[*i].max_quant=sale_rec.quant;
      data[*i].min_quant=sale_rec.quant;
      data[*i].count=1;
      data[*i].sum=sale_rec.quant;
      (*i)++;
   }
   else{                                                 //updata the recond if new new quant is larger or smaller than old one
      if(sale_rec.quant>data[j].max_quant){
         strcpy(data[j].max_prod, sale_rec.prod);
         strcpy(data[j].max_state, sale_rec.state);
         data[j].max_dd=sale_rec.dd;
         data[j].max_mm=sale_rec.mm;
         data[j].max_yy=sale_rec.yy;
         data[j].max_quant=sale_rec.quant;
      }
      else if(sale_rec.quant<data[j].min_quant){
         strcpy(data[j].min_prod, sale_rec.prod);
         strcpy(data[j].min_state, sale_rec.state);
         data[j].min_dd=sale_rec.dd;
         data[j].min_mm=sale_rec.mm;
         data[j].min_yy=sale_rec.yy;
         data[j].min_quant=sale_rec.quant;
      }
      data[j].count++;
      data[j].sum+=sale_rec.quant;
   }
}
//----------------------------------------------------------------------
void process2(struct Data2 *data, int *i){
//----------------------------------------------------------------------
   int j;
   for(j=0; j<*i; j++){
      if(strcmp(data[j].cust, sale_rec.cust)==0 && strcmp(data[j].prod, sale_rec.prod)==0) break;    //search current combination in array
   }
   if(j==*i){                               //current combination doesn`t exist, create new one and store data in it
      strcpy(data[*i].cust, sale_rec.cust);
      strcpy(data[*i].prod, sale_rec.prod);
      if(strcmp(sale_rec.state, "NY")==0 && sale_rec.yy > 1999){
         data[*i].NY_MAX = sale_rec.quant;
         data[*i].NY_month = sale_rec.mm;
         data[*i].NY_day = sale_rec.dd;
         data[*i].NY_year = sale_rec.yy;
      }
      else data[*i].NY_MAX=-1;
      if(strcmp(sale_rec.state, "NJ")==0 && sale_rec.yy > 1999){
         data[*i].NJ_MIN = sale_rec.quant;
         data[*i].NJ_month = sale_rec.mm;
         data[*i].NJ_day = sale_rec.dd;
         data[*i].NJ_year = sale_rec.yy;
      }
      else data[*i].NJ_MIN=-1;
      if(strcmp(sale_rec.state, "CT")==0){
         data[*i].CT_MIN = sale_rec.quant;
         data[*i].CT_month = sale_rec.mm;
         data[*i].CT_day = sale_rec.dd;
         data[*i].CT_year = sale_rec.yy;
      }
      else data[*i].CT_MIN=-1;
      (*i)++;
   }
   else{                                    //current combination has been recorded, check whether this com should be updated  
      if(strcmp(sale_rec.state, "NY")==0 && sale_rec.yy > 1999 && (sale_rec.quant > data[j].NY_MAX || data[j].NY_MAX == -1)){
         data[j].NY_MAX = sale_rec.quant;
         data[j].NY_month = sale_rec.mm;
         data[j].NY_day = sale_rec.dd;
         data[j].NY_year = sale_rec.yy;
      }
      if(strcmp(sale_rec.state, "NJ")==0 && sale_rec.yy > 1999 && (sale_rec.quant < data[j].NJ_MIN || data[j].NJ_MIN == -1)){
         data[j].NJ_MIN = sale_rec.quant;
         data[j].NJ_month = sale_rec.mm;
         data[j].NJ_day = sale_rec.dd;
         data[j].NJ_year = sale_rec.yy;
      }
      if(strcmp(sale_rec.state, "CT")==0 && (sale_rec.quant < data[j].CT_MIN || data[j].CT_MIN == -1)){
         data[j].CT_MIN = sale_rec.quant;
         data[j].CT_month = sale_rec.mm;
         data[j].CT_day = sale_rec.dd;
         data[j].CT_year = sale_rec.yy;
      }
   }
}