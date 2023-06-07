#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define L 120



typedef struct N {char key[L];
				  struct N* right;
				  struct N* left;
				  struct N* p;
				  struct M* firstmitt;
				  int nm;  //numero mittenti
				  char c; //definiamo i nodi dell'albero delle entità
				 } nodo;

typedef struct M { char mitt[35];
					struct M* next;
				  } mittente;
	
typedef struct Q {char relazione [35];
				  struct N* radice;
				  int max;
				  struct Q* next;
				 } treelenco;

typedef struct N* pnodo;
typedef struct M* pmitt;
typedef struct Q* pelen;


pnodo treeinsert (pnodo tree, pnodo nil, char* str);
pnodo entsearch (pnodo tree, pnodo nil, char* str);
pnodo delent (pnodo tree, pnodo eliminando, pnodo nil);
pnodo delentfixup (pnodo tree, pnodo nil, char* str);
void entstampa (pnodo tree, pnodo nil);
pnodo successor (pnodo tree, pnodo nil);
pnodo minimum (pnodo tree, pnodo nil);
pelen ricercarelazione (pelen lista, char* str);
pelen nuovarelazione (pelen lista, pnodo nil, char* str);
void elencorelazioni (pelen lista, pnodo nil);
pmitt newmitt (pmitt lista, char* str);
pmitt mittsearch (pmitt lista, char* str);
pmitt cleanmitt (pmitt lista);
void relstampa (pmitt lista, int num);
pmitt delmitt (pmitt lista, char* str);
int reportfixup (pnodo tree, pnodo nil, int num);
void report (pnodo tree, pnodo nil, int massimo);




int main()
	{char st1[35], st2[35], st3[35], st4[35], ing[L];
	 char strend[]= "end\n";
	 int i,j, cont=0, contatore=0, contafile=0;
	 pelen elenco, rimand;  
	 pnodo rif, nullo;
	 pmitt rinv;
	 FILE *fp;
	 fp=fopen("test6-1.txt", "r");
	 
	 elenco=malloc(sizeof(treelenco));
	 strcpy(elenco->relazione, "main");
	 elenco->next=NULL;
	 
	 //creo il nodo nil
	 nullo=malloc(sizeof(nodo));
	 strcpy(nullo->key, "nil");
	 nullo->p=nullo;
	 nullo->left=nullo;
	 nullo->right=nullo;
	 elenco->radice=nullo;
	 
	 
	 do
		{//printf("cosa vuoi fare?\n"); 
		 /*if (contafile==0)
			{fgets(ing, L, fp);}	//inserisco la stringa e alla fine pongo il carattere terminatore
		 else*/
		  fgets(ing, L, stdin); 
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
					{rif=elenco->radice;
					 if (rif==nullo)
						{elenco->radice=treeinsert(rif, nullo, st2);}
					 else if (entsearch(rif, nullo, st2)==nullo)
						{elenco->radice=treeinsert(rif, nullo, st2);}
					 else 
						{goto CYCLE;
						 //printf("non serve aggiungere la entity\n");
						}
					
					 fflush(stdin);
					}
		  else if (strcmp(st1, "delent")==0)
					{rif=elenco->radice;
					 rif=entsearch(rif, nullo, st2);  //cerco nell'elenco entity
				     if (rif!=nullo)  
							{elenco->radice=delent(elenco->radice, rif, nullo);  //se trovo la elimino
							 rimand=elenco->next;  //procedo nell'elenco alberi delle relazioni
							 while (rimand!=NULL)  //per tutto l'elenco degli alberi delle relazioni
								{if (rimand->radice!=nullo)   //se questo albero non è vuoto
									{rif=entsearch(rimand->radice, nullo, st2);  //se c'è la entity che ho cancellato la rimuovo
									 if (rif!=nullo)
											{rif->firstmitt=cleanmitt(rif->firstmitt);  //prima ovviamente ne pulisco i mittenti 
											 rimand->radice=delent(rimand->radice, rif, nullo);
											}
									if (rimand->radice!=nullo) 
											{rimand->radice=delentfixup(rimand->radice, nullo, st2);} //in seguito fixo gli elenchi dei mittenti
									}
							     rimand=rimand->next;  //scorro l'elenco alberi
								}
							}
					else 
							{goto CYCLE;
							 //printf("non ce sta nu cazz da cancella\n");
							}
					
					fflush(stdin);
					}
		  else if (strcmp(st1, "addrel")==0)
					{if (entsearch(elenco->radice, nullo, st2)==nullo || entsearch(elenco->radice, nullo, st3)==nullo)
							{//printf("non ci sono le entity per descrivere la relazione\n");
						     goto CYCLE;
							}
					 rimand=ricercarelazione(elenco->next, st4);
					 if (rimand==NULL)  //verifico se la tipologie di relazione è presente e nel caso costruisco un nuovo albero
							{elenco->next=nuovarelazione(elenco->next, nullo, st4);
							 rimand=ricercarelazione(elenco->next, st4);//se la relazione non esiste la aggiungo 
							 rimand->radice=nullo;
							
							 rif=entsearch(rimand->radice, nullo, st3); //prendo l'elemento nell'albero della relazione
							 if (rif==nullo) //se il destinatario non è presente
									{rimand->radice=treeinsert(rimand->radice, nullo, st3); //aggiungo la entity all'albero della relazione
									 rif=entsearch(rimand->radice, nullo, st3);
									 rif->firstmitt=newmitt(rif->firstmitt, st2); //aggiungo il mittente al neonato nodo dell'albero
									 rif->nm++;
									}
							 else 
									{if (mittsearch(rif->firstmitt, st2)==NULL)  //se la entity c'è aggiungo solamente il mittente, se serve
											{rif->firstmitt=newmitt(rif->firstmitt, st2);
											 rif->nm++;
											}
									 else {//printf("la relazione era presente \n");
									       goto CYCLE;
										  }
									}
						     
							}  
					 else //se l'albero è presente, faccio le stesse cose di prima tranne creare l'albero
							{rif=entsearch(rimand->radice, nullo, st3);
							 if (rif==nullo) //se il destinatario non è presente
									{rimand->radice=treeinsert(rimand->radice, nullo, st3); //aggiungo la entity all'albero della relazione
									 rif=entsearch(rimand->radice, nullo, st3);
									 rif->firstmitt=newmitt(rif->firstmitt, st2);	 //aggiungo il mittente al neonato nodo dell'albero
									 rif->nm++;
									}
							 else 
									{if (mittsearch(rif->firstmitt, st2)==NULL)  //se la entity c'è aggiungo solamente il mittente, se serve
											{rif->firstmitt=newmitt(rif->firstmitt, st2);
											 rif->nm++;}
									 else {//printf("la relazione era presente \n");
									       goto CYCLE;
										  }
									}
						     
							}
					
					 fflush(stdin);
					}
		  else if (strcmp(st1, "delrel")==0)
					{if (entsearch(elenco->radice, nullo, st2)==nullo || entsearch(elenco->radice, nullo, st3)==nullo)
							{//printf("mancano le entity, la relazione non esiste\n");
						     goto CYCLE;
							}
					 rimand=ricercarelazione(elenco->next, st4);
					 if (rimand==NULL)
							{//printf("il tipo di relazione menzionato non figura\n");
							 goto CYCLE;
							}
					 rif=entsearch(rimand->radice, nullo, st3);
					 if (rif==nullo)
							{//printf("il destinatario non appare\n");
							 goto CYCLE;
							}
					 rinv=mittsearch(rif->firstmitt, st2);
					 if (rinv==NULL)
							{//printf("il mittente non appare\n");	
							}
					 else
							{rif->firstmitt=delmitt(rif->firstmitt, st2);
						     rif->nm--;   //se la relazione è presente la elimino e decremento il numero di mittenti
							 if (rif->nm==0 || rif->firstmitt==NULL)
									{rimand->radice=delent(rimand->radice, rif, nullo);
							        }   											   //se numero di mittenti è zero elimino il destinatario
							}
						    
					 
					 fflush(stdin);
					}
		  else if (strcmp(st1, "report")==0)
					{rimand=elenco->next;
				     if (rimand==NULL)
							{fputs("none\n", stdout);
							 goto CYCLE;
							}
							
					 while (rimand!=NULL)
							{rimand->max=reportfixup(rimand->radice, nullo, rimand->max);
							 if (rimand->max>0) 
									{fputs("\"", stdout);
									 fputs(rimand->relazione, stdout);
									 fputs("\" ", stdout);    //stampo il nome della relazione con le dovute interruzioni
									 report(rimand->radice, nullo, rimand->max); //stampo i massimi 
									 printf("%d;", rimand->max);
									 if (rimand->next!=NULL)
											{fputs(" ", stdout);}
									 rimand->max=0;
									 contatore++;
									}
							 
							 rimand=rimand->next;  //ciclo sulle tipologie di relazione
							}
					 if (contatore==0)
							{fputs("none\n", stdout);
						     goto CYCLE;
							}
					 contatore=0;
					 fputs("\n", stdout);
					 fflush(stdin);
					}
		  else if (strcmp(ing, strend)==0)
					{goto END;}
		  else if (strcmp(ing, "fileout\n")==0)
					{contafile++;}
		  
		  else if (strcmp(ing, "entstampa\n")==0)
					{printf("stampo l'elenco delle entity:\n");
					 rif=elenco->radice;
					 if (rif==nullo)
							{printf("nun ce sta nu cazz da stampa\n");}
					 else 
							{entstampa(rif, nullo);
							 printf("\n");
							}
					 
					 
					}
		  else if (strcmp(st1, "relstampa")==0)
					{rimand=ricercarelazione(elenco->next, st3);
					 if (rimand!=NULL) 
							{rif=entsearch(rimand->radice, nullo, st2);
							 if (rif!=nullo)
									{relstampa(rif->firstmitt, rif->nm);
									}
							 else 
									{printf("non figura il destinatario cercato\n");}
							}
					 else 
							{printf("l'albero della relazione non figura\n");}
					}
		   else if (strcmp(st1, "elencorelazioni")==0)
					{
					 elencorelazioni(elenco->next, nullo);
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
		} while (strcmp(ing, "end")!=0);  //continuo a iterare finché la prima parte della stringa in ingresso non è il comando end 
	 END:	 
	 return 0;
	 
	}


//funzioni

pnodo treeinsert (pnodo tree, pnodo nil, char* str) //aggiunge una entity senza riequilibrare
	{pnodo punt, ptr, curr;
	 punt=malloc(sizeof(nodo));
	 punt->left=nil;
	 punt->right=nil;
	 punt->firstmitt=NULL;
	 punt->nm=0;
	 strcpy(punt->key, str);
	 //ora la parte che esegue la insert
	 curr=nil;
	 ptr=tree;
	 while (ptr!=nil)
			{curr=ptr;
			 if (strcmp (punt->key, ptr->key)<0)
					{ptr=ptr->left;}
		     else 
					{ptr=ptr->right;}
			}
	 punt->p=curr;
	 if (curr==nil)
			{tree=punt;}
	 else if (strcmp(punt->key, curr->key)<0)
			{curr->left=punt;}
	 else 
			{curr->right=punt;}
	 return tree;
	}


pnodo delent (pnodo tree, pnodo eliminando, pnodo nil)
	{pnodo curr, punt, ptr ; //curr(z), punt(y), ptr(x)
	 curr=eliminando;  //z è il nodo da eliminare
	 if (curr->left==nil || curr->right==nil)
			{punt=curr;}    //se gli manca un figlio metto curr su punt
	 else 
			{punt=successor(curr, nil);}   //altrimenti punt è il suo successore
	 if (punt->left!=nil)
			{ptr=punt->left;}  //se il sottoalbero sinistro del successore esiste lo assegno a ptr, sennò il sott. destro, che può anche essere nil
	 else
			{ptr=punt->right;}
	 if (ptr!=nil)
			{ptr->p=punt->p;}  //se ptr non è nil il padre di punt diventa suo padre
	 if (punt->p==nil)
			{tree=ptr;}
	 else if (punt==punt->p->left)
			{punt->p->left=ptr;}
	 else 
			{punt->p->right=ptr;}
	 if (punt!=curr)
			{strcpy(curr->key, punt->key);  //nel caso in cui devo eliminare il nodo successore, assegno a curr la key, il nm e il firstmitt del successore
		     curr->nm=punt->nm;
			 curr->firstmitt=punt->firstmitt;
			}
	 free (punt);
	 return tree;
	}
	
pnodo delentfixup (pnodo tree, pnodo nil, char* str)  //questa funzione elimina dagli elenchi dei mittenti una entity cancellata
	{pmitt prec, curr;
	 curr=tree->firstmitt;
	 prec=NULL;
	 if (curr!=NULL)  //se l'elenco mittenti non è vuoto
			{while (curr!=NULL)   //lo scorro
					{if (strcmp(curr->mitt, str)==0) {break;}  //ciclo migrando i puntatori finchè non arrivo a NULL o trovo qualcosa che combacia
					 if (strcmp(curr->mitt, str)>0) {goto SUP;}  //se trovo un nome alfabeticamente maggiore smetto di cercare e inoltro ai figli
					 prec=curr;
					 curr=curr->next;   //scorro prec e curr
					}
			 if (curr!=NULL)  //se breako ho trovato il mittente che volevo ed è puntato da curr
					{if (prec==NULL)                     //se era il primo aggancio la lista a next, decremento e elimino il nodo della lista
							{tree->firstmitt=tree->firstmitt->next;
							 tree->nm--;
							 free (curr);
							}
					 else 
							{prec->next=curr->next;   
							 tree->nm--; 						//altrimenti connetto il precedente con il dopo e elimino
							 free(curr);
							}                              //in entrambi i casi decremento il numero di relazioni
					}
			}
	 //if (tree->firstmitt==NULL)
			// {tree->nm=0;}
	 SUP:												//l'etichetta e il goto servono vada oltre la possibile posizione alfabetica
	 if (tree->left!=nil)
			{tree->left=delentfixup(tree->left, nil, str);}
	 if (tree->right!=nil)
			{tree->right=delentfixup(tree->right, nil, str);}   //propago nel sottoalbero sinistro o destro se questi sono diversi da nil
	 return tree;
	}	








void entstampa (pnodo tree, pnodo nil)
	{if (tree!=nil)
		{entstampa (tree->left, nil);
		 printf("%s ", tree->key);
		 entstampa(tree->right, nil);
		}
	}

		 
pnodo entsearch (pnodo tree, pnodo nil, char* str)
	{if (tree==nil)
			{return tree;}
	 if (strcmp(tree->key, str)==0)
			{return tree;}
	 if (strcmp(str, tree->key)<0)
			{return entsearch(tree->left, nil, str);}
	 else 
			{return entsearch (tree->right, nil, str);}
	}
		
	
pnodo minimum (pnodo tree, pnodo nil) //questa funzione trova il minimo per la successor
	{pnodo punt=tree;
	 while (punt->left!=nil)
			{punt=punt->left;}
	 return punt;
	}
	
	 
pnodo successor (pnodo tree, pnodo nil)  //questa funzione trova il successore per la delent
	{pnodo curr, punt=tree; //punt(x),curr (y)
	 if (punt->right!=nil)
			{return minimum (punt->right, nil);
			}
	 curr=punt->p;
	 while (curr!=nil && punt==curr->right)
			{punt=curr;
			 curr=curr->p;
			}
	 printf("%s successore di %s\n", curr->key ,tree->key);
	 return curr;
	}
	

pelen ricercarelazione (pelen lista, char* str)  //questa funzione cerca una relazione nell'elenco degli alberi
	{pelen punt;
	 punt=lista;
	 while (1)
			{if (punt==NULL) {break;}
			 if (strcmp(punt->relazione, str)==0) {break;}
			 if (strcmp(punt->relazione, str)>0) {return NULL;}
			 punt=punt->next;}
	 return punt;
	}

pelen nuovarelazione (pelen lista, pnodo nil, char* str)
	{pelen punt, ptr, ptrprec;
	 punt=malloc(sizeof(treelenco));
	 strcpy(punt->relazione, str);
	 punt->radice=nil;
	 punt->max=0;
	 ptr=lista;
	 ptrprec=NULL;
	 if (ptr==NULL)
			{punt->next=NULL;
			 lista=punt;  //se lista vuota metto next a NULL e poi assegno alla lista l'unico puntatore
			}
	 else 
			{while (1)
					{if (ptr==NULL) {break;}
					 if (strcmp(punt->relazione, ptr->relazione)<0) {break;}
					 ptrprec=ptr;
					 ptr=ptr->next;
					}
			 punt->next=ptr;
			 if (ptrprec!=NULL)
					{ptrprec->next=punt;}
			 else 
					{lista=punt;}
			}
	 return lista;
	}
	
	 
void elencorelazioni (pelen lista, pnodo nil)  //questa funzione printa gli alberi delle relazioni con i nomi dei loro destinatari
	{pelen punt;
	 punt=lista;
	 if (punt==NULL)
			{printf("non ce sta manco na cazz di relazione\n");
			 return;
			}
	 printf("sono presenti le seguenti tipologie di relazione\n");
	 while (punt!=NULL)
		{if(punt->radice!=nil)
				{printf("%s con i destinatari :\n", punt->relazione);
				 entstampa (punt->radice, nil);
				 printf("\n");
				}
		 punt=punt->next;
		}
	 printf("\n");
	 return;
	}


pmitt mittsearch (pmitt lista, char* str)  //questa funzione controlla la presenza di un mittente nell'elenco di un destinatario
	{pmitt punt;
	 punt=lista;
	 while (1)
		{if (punt==NULL) {break;}
		 if (strcmp(punt->mitt, str)==0) {break;}
		 if (strcmp(punt->mitt, str)>0) {return NULL;}
		 punt=punt->next;
		}
	 return punt;
	}

pmitt newmitt (pmitt lista, char* str)  //questa funzione aggiunge in maniera ordinata un mittente nell'elenco di un destinatario
	{pmitt punt, ptr, ptrprec;
	 punt=malloc(sizeof(mittente));
	 strcpy(punt->mitt, str);
	 ptr=lista;
	 ptrprec=NULL;
	 if (ptr==NULL)
			{punt->next=NULL;
		     lista=punt;
			}
	 else 
			{while (ptr!=NULL)
					{if (ptr==NULL) {break;}
					 if (strcmp(punt->mitt, ptr->mitt)<0) {break;}
					 
					 ptrprec=ptr;
					 ptr=ptr->next;
					}
			 punt->next=ptr;
			 if (ptrprec!=NULL)
					{ptrprec->next=punt;}
			 else 
					{lista=punt;}
			}
	 return lista;
	}

void relstampa (pmitt lista, int num)  //questa funzione stampa l'elenco mittenti di una certa entity
	{pmitt punt;
	 punt=lista;
	 if (punt==NULL)
			{printf("non ci sono mittenti da stampare (ovvero n %d)\n", num);}
	 else 
			{printf("sono presenti %d mittenti:\n", num);
			 while(punt!=NULL)
					{printf("%s ", punt->mitt);
				     punt=punt->next;
					}
			 printf("\n");
			}
     return;
	}

pmitt delmitt (pmitt lista, char* str)  //questa funzione elimina un mittente quando la delrel fa il suo lavoro
		{pmitt curr, prec;
		 prec=NULL;
		 for (curr=lista; curr!=NULL; curr=curr->next)
				{if (strcmp(str, curr->mitt)==0) {break;}
			     prec=curr;
		        }
         if (curr==NULL)
				{return lista;}
		 if (prec==NULL)
				{lista=lista->next;}
		 else 
				{prec->next=curr->next;}
		 //printf("ho eliminato il mittente %s\n", curr->mitt);
		 free (curr);
		 return lista;
		}

pmitt cleanmitt (pmitt lista)  //questa funzione svuota l'elenco dei mittenti prima che una entity venga eliminata
		{pmitt ptr, prec;
		 ptr=lista;
		 prec=NULL;
		 while (ptr!=NULL)
				{prec=ptr;
				 ptr=ptr->next;
				 free(prec);
				}
		 return ptr;
		}
				 

int reportfixup (pnodo tree, pnodo nil, int num)  //controlla se serve modifcare nuovo max, poi inoltra a destra e sinistra se diverso da max
	{pnodo punt;
	 punt=tree;
	 if (punt->left!=nil)
			{num=reportfixup(punt->left, nil, num);}
	 if (punt->right!=nil)
			{num=reportfixup(punt->right, nil, num);}
	 if (punt->nm > num)
			{num=punt->nm;}
     return num;
	}
	
void report (pnodo tree, pnodo nil, int massimo)  //scende inorder e se nm=massimo stampa
	{pnodo punt;
	 punt=tree;
	 if (punt->left!=nil)
			{report (punt->left, nil, massimo);}
	 if (punt->nm==massimo)
			{fputs("\"", stdout);
			 fputs(punt->key, stdout);
			 fputs("\" ", stdout);
			}
	 if (punt->right!=nil)
			{report(punt->right, nil, massimo);}
	 return;
	}

