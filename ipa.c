#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define L 100

typedef struct N {int key;
				  char name[L]; 
                  struct N* next;
				  struct M* rel;
                 } entity;   //la prima struct definisce le entità, con puntatore alla seguente di queste e alla prima relazione 
				
typedef struct M {char conn[L];
                  char mitt[L];	
                  struct M* nxre;
                 } link;      //la seconda struct definisce le connessioni, con mittente e puntatore alla successiva di queste 

typedef struct Q {char name[L];
				  int key;
    			  int max;
				  int occorrenze;
				  struct Q* next;
				  struct N* massimi;
				 } relazione;  //questa struct tiene conto del numero di relazioni implementate, del numero di volte che compaiono, di chi le massimizza
				  
				 
typedef entity* pent;
typedef link* plink;  //definisco i due tipi di puntatori per gestire entità e relazioni
typedef relazione* prelaz; //il terzo puntatore all'elenco relazioni

prelaz correttore=NULL; //questa variabile globable serve a restituire elenco con delentfixup, cleanrel (con delrel non serve perché eliminazione unica la faccio nel main)

//fase dichiarativa delle funzioni
pent addent (pent lista, char* str);
pent ordent (pent lista, char* str);
pent delent (pent lista, char* str);
pent delentfixup(pent lista, prelaz elenco, char* str);
pent entsearch (pent lista, char* str);
plink addrel (plink lista, char* connessione, char* mittente);
plink relsearch (plink lista, char* connessione, char* mittente);
plink relsearch2 (plink lista, char* connessione, char* mittente);
plink delrel (plink lista, char* connessione, char* mittente);
plink cleanrel (plink lista, prelaz elenco);
void relstampa (plink lista);
prelaz ricerca (prelaz lista, char* str);
prelaz nuovarelazione (prelaz lista, char* str); 
prelaz eliminarelazione (prelaz lista, char* str);
prelaz reportfixup (pent lista, prelaz elenco);
pent addmax (pent lista, char* str);
pent svuotamax (pent lista) ;
void report(prelaz lista);
int contamax(plink lista, char* str);
void elencorelazioni (prelaz lista);
void entstampa (pent lista);
int keyfinder (char* str);


		
int main()
	{char st1[30], st2[30], st3[30], st4[30], ing[L];
	 char strend[]= "end\n";
	 int i,j, chiave, cont, controllo=0;
	 pent l=NULL, rif;          //rif serve a tenere conto di quale sia l'entità sulle cui relazioni sto lavorando
	 prelaz elen=NULL, point;       //point serve a tenere conto di quale relazione sto incrementando
	 plink provv=NULL;            //prov serve da riferimento per la chiamata di alcune funzioni
	 
	 do
		{//printf("cosa vuoi fare?\n"); 
		 fgets(ing, L, stdin);		//inserisco la stringa e alla fine pongo il carattere terminatore
		 //printf("\n\n" );
		  
		  
		  
		  
		  j=0;
		  for (i=0; ing[i]!=' ' && ing[i]!='\n'; i++) 
				{st1[j]=ing[i];
				 j++;
			    } //copio il comando
		  st1[j]='\0';
		  //printf("il comando inserito: %s \n", st1);
		  
		  
          
		  if (ing[i]==' ' && ing[i+1]=='"')
				{i=i+2;
			     j=0;
				 while(ing[i]!='"' && ing[i]!='\0' && i<L && ing[i]!='\n')
						{st2[j]=ing[i];
						 j++;
						 i++;
						}
				  st2[j]='\0';
				  //printf("il nome della prima entity : %s \n", st2);
				} //copio il nome della prima entità
		 
		 
		  if (ing[i]=='"' && ing[i+1]==' ' && ing[i+2]=='"')
				{i=i+3; 
				 j=0;
				  while(ing[i]!='"' && ing[i]!='\0' && i<L)
						{st3[j]=ing[i];
						 j++;
						 i++;
						} 
				 st3[j]='\0';
				 //printf("il nome della seconda entity: %s \n", st3);
				}  //copio il nome del destinatario
		  
		  
		  
		  if (ing[i]=='"' && ing[i+1]==' ' && ing[i+2]=='"')
				{i=i+3;
				 j=0;
				 while (ing[i]!='"' && ing[i]!='\0' && i<L) 
					{st4[j]=ing[i];
					 j++;
					 i++;
					}
				 st4[j]='\0';
				 //printf("il nome della relazione: %s \n", st4);
				} //copio il nome relazione
		
	      //printf("\n\n");  
		  
		  
		  
		  
		  
		 
		  //parte di controllo dei comandi
		

   		  if      (strcmp(st1, "addent")==0)
					{if (entsearch(l, st2)==NULL)
							{//printf("entro nella addent\n");
								l=addent(l, st2);}
					 else 
							{//printf("entity %s presente nel database\n", st2);
							}  //controlla che l'entity sia presente, se non lo è lo aggiunge
					
					fflush(stdin);
					}
		  else if (strcmp(st1, "delent")==0)
					{rif=entsearch(l, st2);
				    if (rif!=NULL)
							{if (rif->rel!=NULL)
									{rif->rel=cleanrel(rif->rel, elen);
									 elen=correttore;
									}   //prima di tutto cerca la entity e ne pulisce le relazioni ricevute
							 l=delent(l, st2);					 //poi esegui delent e infine delentfixup
							 l=delentfixup(l, elen, st2);
							 elen=correttore;
							 fflush(stdin);
							}
					 else
							{goto CYCLE;}
					 
					}
		  else if (strcmp(st1, "addrel")==0)
					{
						
					 //questa parte invece si occupa dell'inserimento nella sublista dell'entity ricevente
					 if (entsearch(l, st2)==NULL || entsearch(l, st3)==NULL)  //ricorda che qui st2 è il mittente, st3 è il destinatario
							{//printf("una delle due entity non appare nel database\n");
							 goto CYCLE;
							}
					 else 
							{rif=entsearch(l, st3);
						     if (rif->rel==NULL) 
									{rif->rel=addrel(rif->rel, st4, st2);}
							 else if (relsearch(rif->rel, st4, st2)==NULL)  //punto all'elenco relazioni di dest, e verifico che ci sia una relazione con st4 come conn e st2 come mitt
											{rif->rel=addrel(rif->rel, st4, st2);} 
							 else 
											{//printf("non serve aggiungere la relazione\n");
											 goto CYCLE;
											}
									
							
							 //la seguente parte si occupa dell'inserimento nell'elenco relazioni
							 if (elen==NULL)
									{elen=nuovarelazione(elen, st4);}
							 else if (ricerca(elen, st4)==NULL)
									{elen=nuovarelazione(elen, st4);}
							 else 
									{point=ricerca(elen,st4);
								     point->occorrenze++;}
							 
							 
							
							 //questa parte controlla se c'è da aggiornare la variabile max (SOSPESA PERCHE FACCIO FARE TUTTO A REPORT FIXUP)
							 /*rif=entsearch(l, st3);
							 provv=rif->rel;
							 cont=0;
							 point=ricerca(elen, st4);
							 cont=contamax(provv, st4);
							 if (cont > point->max)
								 	{point->max=cont;}*/
							}
					 
					

					 fflush(stdin);
					}
		  else if (strcmp(st1, "delrel")==0)
					{rif=entsearch(l,st3);
                     if (rif==NULL)
							{//printf("il destinatario non esiste\n");
							 goto CYCLE;
							}
					 else if (relsearch2(rif->rel, st4, st2)==NULL)
							{//printf("non è presente la relazione\n");
							 goto CYCLE;
							}
					 else 
							{rif->rel=delrel(rif->rel, st4, st2);  //se la relazione è presente la elimino, decremento cont dall'elenco generale e se serve la elimino
							 point=ricerca(elen, st4);
							 point->occorrenze--;
							 if (point->occorrenze==0)
									{elen=eliminarelazione(elen, st4);}
							}
						
					 fflush(stdin);
					}
		  else if (strcmp(st1, "report")==0)
					{if (elen==NULL)
							{printf("none\n");
						     goto CYCLE;
							}
					 else 
							{elen=reportfixup(l, elen);  //le due branche fanno la stessa cosa, fatto per debuggare
					         report(elen);
						    }
					 //esegui report
					 fflush(stdin);
					}
		  else if (strcmp(ing, strend)==0)
					{goto END;}
		  
		  else if (strcmp(ing, "entstampa\n")==0)
					{printf("stampo l'elenco delle entity:\n");
					 entstampa(l);
					}
		  else if (strcmp(st1, "relstampa")==0)
					{rif=entsearch(l, st2);
				     if(rif!=NULL) 
							{printf("la entity %s ha le seguenti:\n", st2);
							 relstampa(rif->rel);
							}
					}
		   else if (strcmp(st1, "elencorelazioni")==0)
					{if (elen!=NULL) 
							{printf("stampo l'elenco complessivo delle relazioni: \n");
							 elencorelazioni(elen);
							}
					 else 
							{printf("elenco complessivo delle relazioni vuoto\n");}
					}
		  else    
			 		{printf("comando non riconosciuto\n");
					 fflush(stdin);
					}  //questa catena di if riconosce il comando digitato o printa errore, poi opera di conseguenza
		  CYCLE:		
		  strcpy(st1, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");			  
		  strcpy(st2, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		  strcpy(st3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		  strcpy(st4, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		  //printf("\n");
		
		
		
		//ricorda di inserire quella serie di comandi che azzera le stringhe prima che il ciclo venga ripetuto
		} while (1);  //continuo a iterare finché la prima parte della stringa in ingresso non è il comando end 
	 END:	 
	 return 0;
	 
	}


//funzioni

/*	
int keyfinder (char*str)  //questa funzione calcola la key sommando i caratteri ASCII della stringa passata (MA NON FUNZIONA)
	{int i, num;
	 num=0;
	 for (i=0; *(str+i)='\0'; i++)
			{num=num+*(str+i);
			 printf("%d %c\n", *(str+i), *(str+i));}
	 printf("key calcolata: %d", num);
   	 return num;
	}
*/	
	
	
	
	
	
pent entsearch (pent lista, char* str) //questa funzione restituisce un puntatore alla entity se presente nella lista, NULL altrimenti
		{pent ptr;
		 ptr=lista;
		 while (1)
				{
			     if (ptr==NULL) {break;}
                 if (strcmp(ptr->name, str)==0) {break;}	
				 ptr=ptr->next;
				}
		 return ptr;
		}



pent addent (pent lista, char* str) //questa funzione permette l'inserimento in ordine alfabetico di una nuova entità
	{pent ptr, ptrprec, punt;
	 ptr=lista;
	 ptrprec=NULL;
	 punt=malloc(sizeof(entity));
	 strcpy(punt->name, str);
	 punt->rel=NULL;
	 if (ptr==NULL)
			{lista=punt;}
	 if (ptr!=NULL && strcmp(punt->name, ptr->name)<0)
			{punt->next=lista;
			 return punt;
			}
	 while (ptr!=NULL && strcmp(punt->name, ptr->name)>0)
			{ptrprec=ptr;
			 ptr=ptr->next;
			}
	 punt->next=ptr;
	 if (ptrprec!=NULL)
			{ptrprec->next=punt;}
	 //printf("ho inserito con successo %s nella lista entity \n", str);
	 return lista;
	}

/*
pent ordent (pent lista, char* str)   //questa funzione inserisce in maniera ordinata le entità nella loro lista, MA NON CAPISCO PERCHE' NON FUNZIONA DIOCANE
	{printf("provo a inserire %s in ordine alfabetico\n");
	 pent ptr, ptrprec;
     pent punt;
	 ptr=lista;
	 ptrprec=NULL;
	 punt=malloc(sizeof(entity));
	 strcpy(punt->name, str);
	 punt->rel=NULL;
	 if (ptr==NULL)
			{lista=punt;}
	 while (ptr!=NULL || strcmp(ptr->name, punt->name)<0)
			{ptrprec=ptr;
			 ptr=ptr->next;
			 if (ptr==NULL) {break;}
			}
	 punt->next=ptr;
	 if (ptrprec!=NULL)
			{ptrprec->next=punt;}
	 printf("ho aggiunto %s in ordine alfabeto nell'elenco entity\n", str);
	 return lista;
	}
	

pent addent (pent lista, char* str)          //copia di addent 
	{pent ptr, curr;
	 curr=lista;
	 ptr=malloc(sizeof(entity));
	 strcpy(ptr->name, str);
	 ptr->next=NULL;
	 ptr->rel=NULL;
	 if (curr==NULL)
			{lista=ptr;}
	 else   
			{while (curr->next!=NULL)
				{curr=curr->next;}
			 curr->next=ptr;
		    }
	 printf("ho inserito con successo %s nella lista\n", str);
	 return lista;
	}


	
*/




	
void entstampa (pent lista) //questa funzione permette la stampa di tutte le entità
	{pent curr;
	 if (curr==NULL)
			{printf("non ci sono entity da stampare\n");
		     return;
			}
	 for (curr=lista; curr!=NULL; curr=curr->next)
			{printf("%s - ", curr->name);}
	 printf("\n\n");
	 return;
	}


pent delent (pent lista, char* str)
	{pent preced, curr;
	 preced=NULL;
	 for (curr=lista; curr!=NULL && strcmp(str, curr->name)!=0; curr=curr->next)
			{preced=curr;}
	 if (curr==NULL)
			{return lista;}
	 if (preced==NULL)
			{lista=lista->next;}
	 else 
			{preced->next=curr->next;}
	 free(curr);
	 //printf("ho eliminato %s dall'elenco entity\n", str);
	 return lista;
	}
	 
pent delentfixup (pent lista, prelaz elenco, char *str)  //questa funzione elimina le relazioni cui una entity eliminata è mittente
	{pent punt;
	 plink preced, curr, prox;
	 prelaz rif;
	 int num;
	 for(punt=lista; punt!=NULL; punt=punt->next) //ciclo sulle entità 
			{preced=NULL;
		     curr=punt->rel;
			 if (curr==NULL) {goto LOOP;} //se non hanno relazioni passo alla prossima iterazione
			 prox=curr->nxre;             //prox tiene in memoria la relazione seguente
			 while (curr!=NULL)            //finché non finisco le relazioni ricevute
					{if (strcmp(curr->mitt, str)==0)   //se ne trovo una da quel mittente
							{if (preced==NULL)         //se non ho aggiornato preced
									{punt->rel=prox;
								     rif=ricerca(elenco, curr->conn);
									 rif->occorrenze--;
									 if (rif->occorrenze==0)
											{elenco=eliminarelazione(elenco, curr->conn);};              //questa parte serve a correggere le occorrenze quando si fa una eliminazione
								     free (curr);
									 
									}
						     else 
									{preced->nxre=prox;
									 rif=ricerca(elenco, curr->conn);
									 rif->occorrenze--;
									 if (rif->occorrenze==0)
											{elenco=eliminarelazione(elenco, curr->conn);}
									 free (curr);
									}
							 curr=prox;
							 if (prox==NULL) {break;}
							 prox=prox->nxre;
					        }
					 else 
							{preced=curr;
							 curr=prox;
							 if (prox==NULL) {break;}
							 prox=prox->nxre;
							}
					}
			 LOOP:
			 num++;
			}
	 //printf("ho rimosso dai vari elenchi le relazioni di cui %s era mittente\n", str);
	 correttore=elenco;
	 return lista;
	}
						
							 
							 
		
		
		
		
		
	 


plink addrel (plink lista, char* connessione, char* mittente) //questa funzione aggiunge una relazione in maniera ordinata nell'elenco legato al destinatario 
	{plink punt, ptr, ptrprec;
	 ptr=lista;
	 ptrprec=NULL;
	 punt=malloc(sizeof(link));
	 strcpy(punt->conn, connessione);
	 strcpy(punt->mitt, mittente); 
	 if (ptr==NULL) 
			{punt->nxre=NULL;
			 lista=punt;
			}
	 else
			{while (ptr!=NULL)
					{if (ptr==NULL) {break;}
					 if (strcmp(punt->conn, ptr->conn)<0) {break;}
					 
					 ptrprec=ptr;
					 ptr=ptr->nxre;
							
					 
					}
			 punt->nxre=ptr;
	         if (ptrprec!=NULL)
					{ptrprec->nxre=punt;}
			 else 
					{lista=punt;}
			}
	 //printf("ho rettificato la relazione al destinatario \n");
	 return lista;
	} 
	 
plink delrel (plink lista, char* connessione, char* mittente) //questa funzione esegue il comando delrel se la relazione è presente
	{plink preced, curr;
	 preced=NULL;
	 for(curr=lista; curr!=NULL && strcmp(connessione, curr->conn)!=0 && strcmp(mittente, curr->mitt)!=0; curr=curr->nxre)
			{preced=curr;}
	 if (curr==NULL)
			{return lista;}
	 if (preced==NULL)
			{lista=lista->nxre;}
	 else
			{preced->nxre=curr->nxre;}
	 free (curr);
	 //printf("ho eliminato la relazione %s con mittente %s\n", connessione, mittente);
	 return lista;
	}

	 	 
	 
plink relsearch (plink lista, char* connessione, char* mittente) //questa funzione cerca una relazione nell'elenco del destinatario
	{plink ptr;
	 ptr=lista;
	 while ( 1)
			{if (ptr==NULL) {break;}
			 if (strcmp(ptr->conn, connessione)==0 && strcmp(ptr->mitt, mittente)==0) {break;}
			 ptr=ptr->nxre;
		     
		    }
	 return ptr;
	}

plink relsearch2 (plink lista, char* connessione, char* mittente) //una variazione di quella sopra che non so perché funziona meglio con delrel
	{plink ptr;
	 ptr=lista;
	 while ( ptr!=NULL && (strcmp(ptr->conn, connessione)!=0 && strcmp(ptr->mitt, mittente)!=0))
			{ptr=ptr->nxre;
		    
		    }
	 return ptr;
	}

plink cleanrel (plink lista, prelaz elenco)  //questa funzione elimina l'elenco di relazioni ricevute di una entity quando questa viene eliminata
	{plink prec, curr;
	 prelaz rif;
	 curr=lista;
	 prec=NULL;
	 while (curr!=NULL)
		{prec=curr;
	     curr=curr->nxre;
		 rif=ricerca(elenco, prec->conn);
		 rif->occorrenze--;
		 if (rif->occorrenze==0)
				{elenco=eliminarelazione(elenco, prec->conn);}
		 free (prec);
		}
	 correttore=elenco;
	 return NULL;
	}
		
		
		

void relstampa (plink lista)  //questa funzione serve a stampare le relazioni di un certo destinatario
	{plink curr;
	 if (curr==NULL)
			{printf("non ci sono relazioni da stampare\n");}
	 else {for (curr=lista; curr!=NULL; curr=curr->nxre)
				{printf("una relazione di tipo   %s   che parte da   %s\n", curr->conn, curr->mitt);}
		  }
	 printf("\n\n");
	 return;
	}
	 
	
int contamax (plink lista, char* str)  //questa funzione conta le occorrenze di una data relazione per un dato destinatarioo
		{plink punt;
		 int num;
		 punt=lista;
		 num=0;
		 while(punt!=NULL)
				{if (strcmp(punt->conn,str)==0)
						{num++;}
				 punt=punt->nxre;
				}
		 return num;
		}
		 



	
prelaz nuovarelazione (prelaz lista, char* str) //questa funzione aggiunge relazioni all'elenco relazioni con contatore
	{prelaz ptr, ptrprec, punt;
	 ptr=lista;
	 punt=malloc(sizeof(relazione));		 
	 ptrprec=NULL;
	 strcpy(punt->name, str);
	 punt->max=0;
	 punt->occorrenze=1;
	 punt->massimi=NULL;
	 punt->next=NULL;
	 if (ptr==NULL)
			{punt->next=NULL;
			 lista=punt;  //se lista vuota metto next a NULL e poi assegno alla lista l'unico puntatore
			}
	 else 
			{while (ptr!=NULL)      //altrimenti al massimo finché ptr diventa null
					{if (ptr==NULL) {break;}
					 if (strcmp(punt->name, ptr->name)<0) {break;}
					 ptrprec=ptr;
					 ptr=ptr->next;
					 
					}
			 punt->next=ptr;
			 if(ptrprec!=NULL)
				{ptrprec->next=punt;}
			 else
				{lista=punt;}
			}
	 //printf("una nuova relazione appare nell'elenco di queste\n");
	 return lista;
	}
	  
prelaz eliminarelazione (prelaz lista, char* str)  //questa funzione elimina la relazione dall'elenco generale (invocata quando occorrenze scende a zero)
	{prelaz preced, curr;
	 preced=NULL;
	 curr=lista;
	 if (curr->next==NULL)
					{free (curr);
					 return NULL;
					}  //questo piccolo if serve a coprire il bug che non mette NULL quando svuoti completamente la lista relazioni
					
	 for (curr=lista; curr!=NULL && strcmp(curr->name, str)!=0; curr=curr->next)
			{
			 
		
			 preced=curr;
		     if (strcmp(curr->name, str)==0) {break;}
			}
	 if (curr==NULL)
			{return lista;}
	 if (preced==NULL)
			{lista=lista->next;}
	 else 
			{preced->next=curr->next;}
	 free(curr);
	 //printf("le occorrenze della relazione %s sono zero, pertanto la elimino dall'elenco generale\n" , str);
	 return lista;
	}


	 	 


prelaz ricerca (prelaz lista, char* str)  //questa funzione fa ricerca nell'elenco delle relazioni
	{prelaz punt;
	 punt=lista;
	 while (punt!=NULL && strcmp(punt->name, str)!=0)
			{punt=punt->next;}
	 return punt;
	}
	
void elencorelazioni (prelaz lista) //questa funzione stampa tutto l'elenco delle relazioni
	{prelaz punt;
	 punt=lista;
	 if (punt==NULL)
			{printf("non figura nessun tipo di relazione tra alcuna entity\n");}
	 while (punt!=NULL)
			{printf("figura %d volte la relazione %s con massimo pari a %d\n", punt->occorrenze, punt->name, punt->max);
		     punt=punt->next;
			}
     printf("\n\n");
	}
	 
	 
	 
prelaz reportfixup (pent lista, prelaz elenco) //questa funzione aggiusta la questione dei massimi preparando per l'esecuzione di report
	{int cont;
	 pent punt, mass;
	 prelaz ptr;
	 plink rif;
	 punt=lista;
	 cont=0;
	 while (punt!=NULL)  //finché non arrivo all'ultima entità
			{rif=punt->rel;	//punto alle relazioni di cui è destinatario
			 ptr=elenco;   //prendo l'elenco complessivo relazioni
			 while (rif!=NULL && ptr!=NULL) 
					{cont=0;
					 while (strcmp(rif->conn, ptr->name)==0)
							{cont++;
						     rif=rif->nxre;  //calcolo quante volte figura una certa relazione, appena ne trovo una diversa ciao (dopo aver uppato rif)
							 if (rif==NULL) {break;} //per evitare segmentation fault sulla strcmp
							}
					 if (cont>ptr->max)  //se i valori contati sono maggiori del massimo 
							{ptr->massimi=svuotamax(ptr->massimi); //svuoto l'elenco dei massimi
						     ptr->max=cont;           //inserisco il valore del nuovo massimo
							 ptr->massimi=addmax(ptr->massimi, punt->name);  //aggiungo i nuovi massimi
							 //printf("%s nuovo massimo di %s\n", punt->name, ptr->name); 
							}
					 else if (cont==0) 
							{cont=0;}  //se cont è zero non fa nulla
					 else if (cont==ptr->max) //se cont è uguale all'elenco dei massimi 
							{if (entsearch(ptr->massimi, punt->name)==NULL) 
									{ptr->massimi=addmax(ptr->massimi, punt->name);
									 //printf("%s aggiunto ai massimi di %s\n", punt->name, ptr->name);
									}
							}
					 //if (rif!=NULL) 
						//	{rif=rif->nxre;}
					 ptr=ptr->next;
					}
			 punt=punt->next;
		    }
	 return elenco;
	}

pent svuotamax (pent lista) //questa funzione svuota l'elenco dei massimi se trova un massimo maggiore
	{pent ptr, prec;
	 ptr=lista;
	 prec=NULL;
	 if (lista==NULL) 
			{return lista;}
	 while (ptr!=NULL)
			{prec=ptr;
			 ptr=ptr->next;
			 free(prec);
			}
	 lista=NULL;
	 return lista;
	}

pent addmax (pent lista, char * str) //questa funzione aggiunge un altro massimo in coda nell'elenco di una relazione
	{pent ptr, punt;
	 ptr=lista;
	 punt=malloc(sizeof(entity));
	 strcpy(punt->name, str);
	 punt->next=NULL;
	 if (ptr==NULL)
			{lista=punt;}
	 else 
			{while (ptr->next!=NULL)
					{//printf("era presente il massimo %s\n", ptr->name);
				     if (ptr==NULL) {break;}
					 ptr=ptr->next;
					}
			 ptr->next=punt;
			}
	 return lista;
	}



void report (prelaz lista) //questa funzione printa relazioni e corrispettivi massimi in ordine alfabetico
	{prelaz curr;
	 pent ptr;
	 curr=lista;
	 if (curr==NULL)
		{printf("none\n");}
	else
	   {while (curr!=NULL)
	 		{if (curr->occorrenze==0)
					{goto NEXT;}
			 printf("\"%s\" ", curr->name);
		     printf("\"%s\" ", curr->massimi->name);
			 while (1)
				{ptr=curr->massimi;
			     curr->massimi=curr->massimi->next;
				 if (curr->massimi==NULL) {break;}
				 printf("\"%s\" ", curr->massimi->name);
				 free (ptr);
				}
				printf("%d;", curr->max);
			 curr->max=0;
			 if(curr->next!=NULL) {printf(" ");}
			 NEXT:
			 curr=curr->next;
			}
      }
	 printf("\n");
	 return;
	}
 

	




	