#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define L 120



typedef struct N {char key[L];
				  struct N* right;
				  struct N* left;
				  struct N* p;
				  struct N* firstmitt;
				  int nm;  //numero mittenti
				  char color; //definiamo i nodi dell'albero delle entità
				 } nodo;

typedef struct M { char mitt[35];
					struct M* next;
				  } mittente;
	
typedef struct Q {char relazione [35];
				  struct N* radice;
				  int max;
				  int stamp;
				  struct Q* next;
				 } treelenco;

typedef struct N* pnodo;
typedef struct M* pmitt;
typedef struct Q* pelen;


pnodo treeinsert (pnodo tree, pnodo nil, char* str);
pnodo treesearch (pnodo tree, pnodo nil, char* str);
pnodo delent (pnodo tree, pnodo eliminando, pnodo nil);
pnodo delentfixup (pnodo tree, pnodo nil, char* str);
void entstampa (pnodo tree, pnodo nil);
pnodo successor (pnodo tree, pnodo nil);
pnodo minimum (pnodo tree, pnodo nil);
pnodo cleanmitt (pnodo tree, pnodo nil);

pelen ricercarelazione (pelen lista, char* str);
pelen nuovarelazione (pelen lista, pnodo nil, char* str);
void elencorelazioni (pelen lista, pnodo nil);

/*pnodo newmitt (pnodo lista, char* str);
pnodo mittsearch (pnodo lista, char* str); 

void relstampa (pnodo lista, int num);
pnodo delmitt (pnodo lista, char* str);*/

int reportfixup (pnodo tree, pnodo nil, int num);
void report (pnodo tree, pnodo nil, int massimo);

pnodo leftrotate (pnodo tree, pnodo x, pnodo nil);
pnodo rightrotate (pnodo tree, pnodo y, pnodo nil);
pnodo rbinsertfixup (pnodo tree, pnodo z, pnodo nil);
pnodo rbdeletefixup (pnodo tree, pnodo x, pnodo nil);






int main()
	{char st1[35], st2[35], st3[35], st4[35], ing[L];
	 char strend[]= "end\n";
	 int i,j, cont=0, contatore=0, contafile=0;
	 pelen elenco, rimand;  
	 pnodo rif, nullo, rinv;
	 char s[]=" \"";
	 char z[]="\"\n";
	 char* token;
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
	 nullo->color='b';
	 elenco->radice=nullo;
	 
	 
	 do
		{//printf("cosa vuoi fare?\n"); 
		 /*if (contafile==0)
			{fgets(ing, L, fp);}	//inserisco la stringa e alla fine pongo il carattere terminatore
		 else
		   {fgets(ing, L, stdin);}*/
		 fgets(ing, L, stdin);
		 //printf("\n\n" );
		  
		  /* //parte di scomposizione con strtok
		  token=strtok(ing, s);
		  strcpy(st1, token);
		  token=strtok(NULL, s);
		  if (token!=NULL)
				{strcpy(st2, token);
				 token=strtok(NULL, s);
				 if (strcmp(token,"\n")!=0) 
						{strcpy(st3, token);
						 token=strtok(NULL, s);
						 strcpy(st4, token);
						}
				}
		  
		 
		  */
		  
		  //printf("la stringuzza è %s %s %s %s\n", st1, st2, st3, st4);
		  
		  
		  
		  
		  
		       // parte di scomposizione manuale
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
					 else if (treesearch(rif, nullo, st2)==nullo)
						{elenco->radice=treeinsert(rif, nullo, st2);}
					 else 
						{goto CYCLE;
						 //printf("non serve aggiungere la entity\n");
						}
					
					 fflush(stdin);
					}
		  else if (strcmp(st1, "delent")==0)
					{rif=elenco->radice;
					 rif=treesearch(rif, nullo, st2);  //cerco nell'elenco entity
				     if (rif!=nullo)  
							{elenco->radice=delent(elenco->radice, rif, nullo);  //se trovo la elimino
							 rimand=elenco->next;  //procedo nell'elenco alberi delle relazioni
							 while (rimand!=NULL)  //per tutto l'elenco degli alberi delle relazioni
								{if (rimand->radice!=nullo)   //se questo albero non è vuoto
									{rif=treesearch(rimand->radice, nullo, st2);  //se c'è la entity che ho cancellato la rimuovo
									 if (rif!=nullo)
											{rif->firstmitt=cleanmitt(rif->firstmitt, nullo);  //prima ovviamente ne pulisco i mittenti 
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
					{if (treesearch(elenco->radice, nullo, st2)==nullo || treesearch(elenco->radice, nullo, st3)==nullo)
							{//printf("non ci sono le entity per descrivere la relazione\n");
						     goto CYCLE;
							}
					 rimand=ricercarelazione(elenco->next, st4);
					 if (rimand==NULL)  //verifico se la tipologie di relazione è presente e nel caso costruisco un nuovo albero
							{elenco->next=nuovarelazione(elenco->next, nullo, st4);
							 rimand=ricercarelazione(elenco->next, st4);//se la relazione non esiste la aggiungo 
							 rimand->radice=nullo;
							
							 rif=treesearch(rimand->radice, nullo, st3); //prendo l'elemento nell'albero della relazione
							 if (rif==nullo) //se il destinatario non è presente
									{rimand->radice=treeinsert(rimand->radice, nullo, st3); //aggiungo la entity all'albero della relazione
									 rif=treesearch(rimand->radice, nullo, st3);
									 rif->firstmitt=treeinsert(rif->firstmitt, nullo, st2); //aggiungo il mittente al neonato nodo dell'albero
									 rif->nm++;
									}
							 else 
									{if (treesearch(rif->firstmitt, nullo, st2)==nullo)  //se la entity c'è aggiungo solamente il mittente, se serve
											{rif->firstmitt=treeinsert(rif->firstmitt, nullo, st2);
											 rif->nm++;
											}
									 else {//printf("la relazione era presente \n");
									       goto CYCLE;
										  }
									}
						     
							}  
					 else //se l'albero è presente, faccio le stesse cose di prima tranne creare l'albero
							{rif=treesearch(rimand->radice, nullo, st3);
							 if (rif==nullo) //se il destinatario non è presente
									{rimand->radice=treeinsert(rimand->radice, nullo, st3); //aggiungo la entity all'albero della relazione
									 rif=treesearch(rimand->radice, nullo, st3);
									 rif->firstmitt=treeinsert(rif->firstmitt, nullo, st2);	 //aggiungo il mittente al neonato nodo dell'albero
									 rif->nm++;
									}
							 else 
									{if (treesearch(rif->firstmitt, nullo, st2)==nullo)  //se la entity c'è aggiungo solamente il mittente, se serve
											{rif->firstmitt=treeinsert(rif->firstmitt, nullo, st2);
											 rif->nm++;}
									 else {//printf("la relazione era presente \n");
									       goto CYCLE;
										  }
									}
						     
							}
					
					 fflush(stdin);
					}
		  else if (strcmp(st1, "delrel")==0)
					{if (treesearch(elenco->radice, nullo, st2)==nullo || treesearch(elenco->radice, nullo, st3)==nullo)
							{//printf("mancano le entity, la relazione non esiste\n");
						     goto CYCLE;
							}
					 rimand=ricercarelazione(elenco->next, st4);
					 if (rimand==NULL)
							{//printf("il tipo di relazione menzionato non figura\n");
							 goto CYCLE;
							}
					 rif=treesearch(rimand->radice, nullo, st3);
					 if (rif==nullo)
							{//printf("il destinatario non appare\n");
							 goto CYCLE;
							}
					 rinv=treesearch(rif->firstmitt, nullo, st2);
					 if (rinv==nullo)
							{//printf("il mittente non appare\n");	
							}
					 else
							{rif->firstmitt=delent(rif->firstmitt, rinv, nullo);
						     rif->nm--;  //se la relazione è presente la elimino e decremento il numero di mittenti
							 if (rif->nm==0 || rif->firstmitt==nullo)
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
							{rif=treesearch(rimand->radice, nullo, st2);
							 if (rif!=nullo)
									{printf("ho %d mittenti:\n", rif->nm);
									 entstampa(rif->firstmitt, nullo);
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
		  strcpy(st1, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");			  
		  strcpy(st2, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		  strcpy(st3, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		  strcpy(st4, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
		  //printf("\n");
		
		
		
		//ricorda di inserire quella serie di comandi che azzera le stringhe prima che il ciclo venga ripetuto
		} while (strcmp(ing, "end")!=0);  //continuo a iterare finché la prima parte della stringa in ingresso non è il comando end 
	 END:	 
	 return 0;
	 
	}


//funzioni

pnodo treeinsert (pnodo tree, pnodo nil, char* str) //aggiunge una entity senza riequilibrare
	{pnodo punt, ptr, curr;         //curr (y), ptr (x), punt (z)
	 punt=malloc(sizeof(nodo));
	 punt->left=nil;
	 punt->right=nil;
	 punt->firstmitt=nil;
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
	 //righe aggiunte per implementazione rb
	 /*punt->left=nil;
	 punt->right=nil;
	 punt->color='r';
	 tree=rbinsertfixup(tree, punt, nil);*/
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
	//aggiungo l'if per la fixup degli rb
	// if (punt->color=='b')
			//{tree=rbdeletefixup(tree, ptr, nil);}
	 free (punt);
	 return tree;
	}
	
pnodo delentfixup (pnodo tree, pnodo nil, char* str)  //questa funzione elimina dagli elenchi dei mittenti una entity cancellata
	{pnodo punt;
	 punt=treesearch(tree->firstmitt, nil, str);  //semplicemente verifico che nell'albero dei mittenti sia presente, e se lo è, elimino
	 if (punt!=nil)
		{tree->firstmitt=delent(tree->firstmitt, punt, nil);
	     tree->nm--;
		}
	
	
	
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

		 
pnodo treesearch (pnodo tree, pnodo nil, char* str)
	{if (tree==nil)
			{return tree;}
	 if (strcmp(tree->key, str)==0)
			{return tree;}
	 if (strcmp(str, tree->key)<0)
			{return treesearch(tree->left, nil, str);}
	 else 
			{return treesearch (tree->right, nil, str);}
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
	 punt->stamp=0;
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

/*
pnodo mittsearch (pnodo lista, char* str)  //questa funzione controlla la presenza di un mittente nell'elenco di un destinatario
	{pnodo punt;
	 punt=lista;
	 while (1)
		{if (punt==NULL) {break;}
		 if (strcmp(punt->mitt, str)==0) {break;}
		 if (strcmp(punt->mitt, str)>0) {return NULL;}
		 punt=punt->next;
		}
	 return punt;
	}

pnodo newmitt (pnodo lista, char* str)  //questa funzione aggiunge in maniera ordinata un mittente nell'elenco di un destinatario
	{pnodo punt, ptr, ptrprec;
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


void relstampa (pnodo lista, int num)  //questa funzione stampa l'elenco mittenti di una certa entity
	{pnodo punt;
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

pnodo delmitt (pnodo lista, char* str)  //questa funzione elimina un mittente quando la delrel fa il suo lavoro
		{pnodo curr, prec;
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
*/
pnodo cleanmitt (pnodo tree, pnodo nil)  //questa funzione svuota l'elenco dei mittenti prima che una entity venga eliminata
		{/*if (tree->left!=nil)
				{tree->left=cleanmitt(tree->left, nil);}
		 if (tree->right!=nil)
				{tree->right=cleanmitt(tree->right, nil);}
		 if(tree->right==nil && tree->left==nil)
				{free (tree);
			     return nil;
				}*/      //versione scritta da me
				
		 //versione trovata su internet
		 if (tree==nil)
			{return nil;}
		 cleanmitt(tree->left, nil);
		 cleanmitt(tree->right, nil);
		 free(tree);
		 
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



pnodo leftrotate (pnodo tree, pnodo x, pnodo nil)
	{pnodo y;
	 y=x->right;
	 x->right=y->left;  //il sottoalbero sinistro di y diventa il destro di x
	 
	 
	 if (y->left!=nil)
			{y->left->p=x;}  //aggiusto il padre del sottoalbero prima menzionato
	 y->p=x->p;                //attacco il padre di x a y
	 if (x->p==nil)
			{tree=y;}         //verifico se y è la nuova radice
	 else if (x==x->p->left)
			{x->p->left=y;}
	 else 
			{x->p->right=y;}   //altrimenti gli metto il padre che gli spetta
	 y->left=x;                //x figlio sinistro di y
	 x->p=y;				 //y padre di x
	 return tree;
	}
	
	
pnodo rightrotate (pnodo tree, pnodo y, pnodo nil)  //scritta invertento x e y e right e left
	{pnodo x;
	 x=y->left;
	 y->left=x->right;
	 
	 if (x->right!=nil)
			{x->right->p=y;}
	 x->p=y->p;
	 if (y->p==nil)
			{tree=x;}
	 else if (y==y->p->right) 
			{y->p->right=x;}
	 else 
			{y->p->left=x;}
	 x->right=y;
	 y->p=x;
	 return tree;
	}
	
pnodo rbinsertfixup (pnodo tree, pnodo z, pnodo nil)   //questa è quella merda che fixa gli inserimenti!!
	{pnodo x, y;
	 if (z==tree)
			{tree->color='b';}  //se radice metto il colore a nero
     else 
			{x=z->p;     													//x è padre di z
		     if (x->color=='r')												//se è rosso faccio tutto il mio bel casino di robe
					{if (x==x->p->left)
							{y=x->p->right;
							 if (y->color=='r')
									{x->color='b';
									 y->color='b';
									 x->p->color='r';
									 tree=rbinsertfixup(tree, x->p, nil);
									}
							 else 
									{if (z==x->right)
											{z=x;
											 tree=leftrotate(tree, z, nil);
											 x=z->p;
											}
									 x->color='b';
									 x->p->color='r';
									 tree=rightrotate(tree, x->p, nil);
									}
							}
					 else
							{y=x->p->left;
							 if (y->color=='r')
									{x->color='b';
									 y->color='b';
									 x->p->color='r';
									 tree=rbinsertfixup(tree, x->p, nil);
									}
							 else 
									{if (z==x->left)
											{z=x;
											 tree=rightrotate(tree, z, nil);
											 x=z->p;
											}
									 x->color='b';
									 x->p->color='r';
									 tree=leftrotate(tree, x->p, nil);
									}
							}
							 
					}
			}
	 
	 return tree;	
	}
	
	

pnodo rbdeletefixup (pnodo tree, pnodo x, pnodo nil)    //la merdaccia che fixa gli rb dopo la delete
	{pnodo w;
	 if (x->color=='r' || x->p==nil)
			{x->color='b';}               //caso in cui opero su un rosso
	 else if (x==x->p->left)     //se è il figlio sinistro faccio sta roba
			{w=x->p->right;
			 if (w->color=='r')
					{w->color='b';
					 x->p->color='r';
					 tree=leftrotate(tree, x->p, nil);
					 w=x->p->right;
					}
			 if (w->left->color=='b' && w->right->color=='b')
					{w->color='r';
					 tree=rbdeletefixup(tree, x->p, nil);
					}
			 else 
					{if (w->right->color=='b')
							{w->left->color='b';
						     w->color='r';
							 tree=rightrotate(tree, w, nil);
							 w=x->p->right;
							}
					 w->color=x->p->color;
					 x->p->color='b';
					 w->right->color='b';
					 tree=leftrotate(tree, x->p, nil);
					}
			}
	 else {w=x->p->left;        //questa roba se x è figlio destro
		   if (w->color=='r')
					{w->color='b';
					 x->p->color='r';
					 tree=rightrotate(tree, x->p, nil);
					 w=x->p->left;
					}
		   if (w->right->color=='b' && w->left->color=='b')
					{w->color='r';
				     tree=rbdeletefixup(tree, x->p, nil);
					}
		   else 
					{if (w->left->color=='b')
							{w->right->color='b';
							 w->color='r';
							 tree=leftrotate(tree, w, nil);
							 w=x->p->left;
							}
					 w->color=x->p->color;
					 x->p->color='b';
					 w->left->color='b';
					 tree=rightrotate(tree, x->p, nil);
					}
		 
	      }
	  return tree;
	}
	
	
	