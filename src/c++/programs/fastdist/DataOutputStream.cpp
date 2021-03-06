#include "DataOutputStream.hpp"
#include <cstdio>
#include <math.h>
#include <iostream>
using namespace std;

DataOutputStream::DataOutputStream(char * filename)
{ 
	fp = NULL;

	file_was_opened = false;
	if ( filename == NULL )
	{
		fp = stdout;
	}
	else
	{
		fp = open_write_file(filename);
	}
}
/*
bool WRITEXML;
void setXmlFlag(bool xmlFlag){
	WRITEXML=xmlFlag;
}*/

const char DataOutputStream::ONEDIGIT[128]={
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' ,
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7'};

const char DataOutputStream::TENDIGIT[128] ={
		'0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' ,
		'1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' ,
		'2' , '2' , '2' , '2' , '2' , '2' , '2' , '2' , '2' , '2' ,
		'3' , '3' , '3' , '3' , '3' , '3' , '3' , '3' , '3' , '3' ,
		'4' , '4' , '4' , '4' , '4' , '4' , '4' , '4' , '4' , '4' ,
		'5' , '5' , '5' , '5' , '5' , '5' , '5' , '5' , '5' , '5' ,
		'6' , '6' , '6' , '6' , '6' , '6' , '6' , '6' , '6' , '6' ,
		'7' , '7' , '7' , '7' , '7' , '7' , '7' , '7' , '7' , '7' ,
		'8' , '8' , '8' , '8' , '8' , '8' , '8' , '8' , '8' , '8' ,
		'9' , '9' , '9' , '9' , '9' , '9' , '9' , '9' , '9' , '9' ,
		'0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' , '0' ,
		'1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' , '1' ,
		'2' , '2' , '2' , '2' , '2' , '2' , '2' , '2' };


void
printPHYLIPfast(const StrDblMatrix &dm, FILE *out, bool flag ){

	bool WRITEXML=flag;
	const size_t numNodes = dm.getSize();

	//  xmlNodePtr dmNode;
	if ( WRITEXML ) {
		//    dmNode = xmlNewNode(0, ( const xmlChar * ) "dm");
		fprintf(out,"   <dm>\n");
	}
	else {
		fprintf(out,"%5lu\n",numNodes);
	}


	char defstr[11];// = "   .      ";
	defstr[0]=' ';
	defstr[3] = '.';
	defstr[10] = 0;
	//the names PENDING NAME LENGTH

	int entriesPerRow;


	if ( WRITEXML ) {
		entriesPerRow = 0;
	} else
	{
		entriesPerRow = numNodes;
	}
	for ( size_t i = 0 ; i < numNodes ; i++ ){

		//    xmlNodePtr rowNode;
		if (  WRITEXML )   {
			//      rowNode = xmlNewChild(dmNode,0, ( const xmlChar * ) "row",0);
			// xmlSetProp(rowNode, ( const xmlChar * ) "species",( const xmlChar * ) dm.getIdentifier(i).c_str() );

			//      fprintf(out,"    <row species=\"%s\">\n", dm.getIdentifier(i).c_str() );
			fprintf(out,"    <row>\n" );
		}
		else {
			fprintf(out,"%-10s", dm.getIdentifier(i).c_str());
		}

		if ( WRITEXML )  ( entriesPerRow++ );

		for ( size_t j = 0 ; j < entriesPerRow ; j++ ){
			float f = dm.getDistance(i,j);
			if ( ! isfinite(f) ){

				double zero= 0;
				f = zero;
				// End changes

			}
			//warning: this isn't enough to get the correct rounding but it is close
			f += 0.0000005;
			defstr[1]=' ';
			int intpart = (int) f;
			if ( intpart > 99 ){
				if ( f-intpart*1.0 <0.000001 ){

					if (  WRITEXML ) {
						// I guess 20 should be more than enough. Please lower this number if you know how it all works. /Erik Sjolund
						// char str[20];
						//	    snprintf(str,20,"%10d",intpart);
						//	    xmlNodePtr entryNode = xmlNewChild(rowNode,0, ( const xmlChar * ) "entry",  ( const xmlChar * ) str );
						fprintf(out,"     <entry>%10d</entry>\n", intpart );

					}
					else {
						fprintf(out,"%10d",intpart);
					}

					continue;
				}

				if (  WRITEXML ) {
					// I guess 20 should be more than enough. Please lower this number if you know how it all works. /Erik Sjolund
					//	  char str[20];
					//  snprintf(str,20,"%10f",f);
					// xmlNodePtr entryNode = xmlNewChild(rowNode,0, ( const xmlChar * ) "entry",  ( const xmlChar * ) str );
					fprintf(out,"     <entry>%10f</entry>\n", f );

				}
				else {
					fprintf(out,"%10f",f);
				}

				continue;
			}
			//      printf("F:%10.6f\n",f);
			float decimalpart = f-1.0*intpart;
			//warning: this isn't enough to get the correct rounding but it is close
			//decimalpart += 0.0000005;
			//write intpart
			if ( intpart == 0 )
				defstr[2] = '0';
			else {
				defstr[2] = DataOutputStream::ONEDIGIT[intpart];
				intpart = intpart /10;
				if ( intpart != 0 )
					defstr[1] = DataOutputStream::ONEDIGIT[intpart];
			}

			//write 6 decimals part
			int deci = 4;
			while ( deci <= 9 ){
				decimalpart = decimalpart*100.0;
				int index = (int) decimalpart;
				decimalpart = decimalpart-index;
				defstr[deci++] = DataOutputStream::TENDIGIT[index];
				defstr[deci++] = DataOutputStream::ONEDIGIT[index];
			}
			//      cout << defstr << endl;

			if (  WRITEXML ) {
				// skip leading spaces
				int i = 0;
				while ( defstr[i] == ' ' ) {
					i++;
				}
				//	xmlNodePtr entryNode = xmlNewChild(rowNode,0, ( const xmlChar * ) "entry",  ( const xmlChar * ) &defstr[i] );
				fprintf(out,"     <entry>%s</entry>\n", &defstr[i] );
			}
			else {
				fwrite(defstr,sizeof(char),10,out);
			}
		}

		if (  WRITEXML )    {
			fprintf(out,"    </row>\n");
		} else {
			fprintf(out,"\n");
		}
	}
	if (  WRITEXML ) {
		//    xmlElemDump(out, 0, dmNode);
		fprintf(out,"   </dm>\n");
		//  xmlFreeNode(dmNode);
	}
}



