#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*struct of book record is made, which has various fields laike book name, author name, publication year,
  number of available copies is kept. Also it has pointer of its own type which points to next node*/
  
typedef struct book_rec_tag
{
	char *book_name;
	char *auth_name;
	int pub_year;
	int ava_copies;
	struct book_rec_tag *next;
} rec_node;

/*typedef struct queue
{
	rec_node *front;
	rec_node *rear;
}rec_queue;

rec_queue array_queue[2000];                       //Assuming maximum copies can go only till 2000*/

int isempty(rec_node *head)   //returns 1 if list is empty otherwise 0
{
	if(head==NULL)
	   return 1;
	else
	   return 0;
}

int isfull(rec_node *head)
{
	rec_node *node;
	node=(rec_node*)malloc(sizeof(rec_node));
	if(node==NULL)
	  return 1;
	else
    {
    	free(node);
    	return 0;
	}	  
}
/*function returns 1 if node is to inserted after previous node i.e., prev and it returns 0 in case of update the node*/
int getposition(rec_node *head,rec_node *node,rec_node **prev)
{
	rec_node *temp;
	temp=head;
	if(strcmp(node->auth_name,temp->auth_name)<0)
	{
		*prev=NULL;
		return 1;
	}
	else if(strcmp(node->auth_name,temp->auth_name)==0)
	{
		if(strcmp(node->book_name,temp->book_name)==0)
		{
			*prev=NULL;
		    return 0;
		}
		else if(strcmp(node->book_name,temp->book_name)<0)
		{
			*prev=NULL;
			return 1;
		}
		
	}           //If node is to inserted before first node
	else
	{
		while(temp->next!=NULL)
		{
			*prev=temp;
       	    temp=temp->next;
       	    if(strcmp(node->auth_name,temp->auth_name)<0)
	        {
		        return 1;
	        }
	        else if(strcmp(node->auth_name,temp->auth_name)==0)
	        {
	        	if(strcmp(node->book_name,temp->book_name)==0)
	         	{
		        	return 0;
				}
				else if(strcmp(node->book_name,temp->book_name)<0)
				{
					return 1;
				}
	       	}
		}
	}             //if node is to inserted somewhere in between

  	if(strcmp(node->auth_name,temp->auth_name)<0)
    {
	    return 1;
    }
    else if(strcmp(node->auth_name,temp->auth_name)==0)
    {
	   	if(strcmp(node->book_name,temp->book_name)==0)
	   	{
		  	return 0;
		}
    	else if(strcmp(node->book_name,temp->book_name)<0)
		{
			return 1;
		}
	}             //if node is to be inserted  jst before last node
	if((*prev)==NULL)
	{
		(*prev)=temp;
	    return 1; 
	}
	else
	{
		(*prev)=(*prev)->next;
	    return 1;
	}
	
	   //if node is to be inserted after last node
}

int insert(rec_node **head,char *bname,char *au_name,int year,int av_copies)
{
	if(isfull(*head))
	{
		return 0;
	}
	else
	{
		rec_node *ptr;
		ptr=(rec_node*)malloc(sizeof(rec_node));
		 ptr->book_name=(char*)malloc(sizeof(char)*(strlen(bname)+1));
		 strcpy(ptr->book_name,bname);
		 ptr->auth_name=(char*)malloc(sizeof(char)*(strlen(au_name)+1));
		 strcpy(ptr->auth_name,au_name);
	   	 ptr->pub_year=year;
		 ptr->ava_copies=av_copies;
		 ptr->next=NULL;
		/*node is made with desired entries*/
		
		if(isempty(*head)==1)
		{
			*head=ptr;
			return 1;
		}
		else
		{
			rec_node *prev;
			prev=NULL;
			int ins;
			ins=getposition(*head,ptr,&prev);
			if(prev==NULL && ins==1)
			{
				ptr->next=*head;
				*head=ptr;
				return 1;
			}
			else if(prev==NULL && ins==0)
			{
				(*head)->ava_copies=ptr->ava_copies;
				(*head)->pub_year=ptr->pub_year;
				free(ptr);
				return 1;
			}
			else if(prev!=NULL && ins==1)
			{
				ptr->next=prev->next;
				prev->next=ptr;
				return 1;
			}
			else if(prev!=NULL && ins==0)
			{
				prev->next->ava_copies=ptr->ava_copies;
				prev->next->pub_year=ptr->pub_year;
				free(ptr);
				return 1;
				
			}
			
		}
	}
}

int count_rec(rec_node *head)
{
	rec_node *temp;
	temp=head;
	int count=-1;
	while(temp!=NULL)
	{
		temp=temp->next;
		count++;
	}
	return 0;
}
int delete_ele(rec_node **head,char *bname,char *au_name)
{
	rec_node *temp,*prev;
	prev=NULL;
	temp=*head;
	if(strcmp(temp->auth_name,au_name)==0 && strcmp(temp->book_name,bname)==0)
	{
		*head=temp->next;
		free(temp);
		return 1;
	}
	prev=temp;
	temp=temp->next;
	while(temp!=NULL)
	{
		if(strcmp(temp->auth_name,au_name)==0 && strcmp(temp->book_name,bname)==0)
		{
			prev->next=temp->next;
			free(temp);
			return 1;
		}
	}
	return 0;
}
/*
int get_top_auth(rec_node *head,char *bname,char* aname[])
{
	
	rec_node *temp;
	temp=head;
	int max_copies=-1,i=-1;
	while(temp!=NULL)
	{
		if(strcmp(temp->book_name,bname)==0)
		{
			if(max_copies==temp->ava_copies)
			{
				aname[++i]=temp->auth_name;
			}
		    else if((max_copies)< (temp->ava_copies))
		    {
		    	while(i>=0)
		    	{
		    		aname[i--]=NULL;
				}
		    	aname[++i]=temp->auth_name;
			    max_copies=temp->ava_copies;	
			}	
		}
	    temp=temp->next;
	}
	
	return i;	
}*/

rec_node* get_top_auth(rec_node *head,char *bname)
{
	int max_copies=0;
	rec_node *temp,*ret_head,*ptr,*temp_ret,*p,*prev;
	ret_head=NULL; temp=head;
	while(temp!=NULL)
	{
		if(strcmp(bname,temp->book_name)==0)
		{
			if(temp->ava_copies>=max_copies)
			{
				ptr=(rec_node*)malloc(sizeof(rec_node));
			 		ptr->auth_name=(char*)malloc(sizeof(char)*15);
			 		strcpy(ptr->auth_name,temp->auth_name);
			 		ptr->book_name=(char*)malloc(sizeof(char)*15);
			 		strcpy(ptr->book_name,temp->book_name);
			 		ptr->ava_copies=temp->ava_copies;
			 		ptr->pub_year=temp->pub_year;
			 		ptr->next=NULL;
				if(ret_head==NULL)
				{
					prev=NULL;
					ret_head=ptr;
					temp_ret=ptr;
				}
				else
				{
					prev=temp_ret;
					temp_ret->next=ptr;
					temp_ret=temp_ret->next;
				}
				max_copies=temp->ava_copies;
			}
	    }
		temp=temp->next;	
    }
    return ret_head;
}		
	

/*
int most_pop_auth(rec_node *head,char* author[])
{
	rec_node *temp;
	temp=head;
	int sum,max_size=-1,i=-1;
	char *aname;
	aname=temp->auth_name;
	while(temp!=NULL)
	{
		sum=0;
		while( (strcmp(aname,temp->auth_name))==0)
		{
			sum+=temp->ava_copies;
			if(temp->next==NULL)
			   break;
			else   
			   temp=temp->next;
		}
		if(sum==max_size)
		{
			author[++i]=aname;
		}
		if(sum>max_size)
		{
			while(i>=0)
			{
				author[i--]=NULL;
			}
			author[++i]=aname;
			aname=temp->auth_name;
			max_size=sum;
		}
		if(temp->next==NULL)
		{
			break;
		}
	}
	
	if(max_size==temp->ava_copies)                 //if last node element's author is most popular
	{
		author[++i]=temp->auth_name;
	}
	else if(max_size<temp->ava_copies)
	{
		while(i>=0)
	    	author[i--]=NULL;
	    author[++i]=temp->auth_name;
	}
	return i;
}*/

typedef struct kth_pop
{
	rec_node *node;
	struct kth_pop *next;
}kth_book;

void print_kth_book(kth_book *k)
{
	kth_book *temp;
	temp=k;
	while(temp!=NULL)
	{
		printf("\n\nAuthor Name:%s",temp->node->auth_name);
		printf("\nBook Name:%s",temp->node->book_name);
		printf("\nAvailable copies:%d",temp->node->ava_copies);
		printf("\nPublication Year:%d",temp->node->pub_year);
		temp=temp->next;
	}
}
kth_book* kth_popular_book(rec_node *head,int k)
{
	
	kth_book *hdr,*ptr,*t,*prev;
	ptr=(kth_book*)malloc(sizeof(kth_book));
	ptr->node=head;
	ptr->next=NULL;
	hdr=ptr;
	rec_node *temp;
	temp=head->next;
	while(temp!=NULL)
	{
		ptr=(kth_book*)malloc(sizeof(kth_book));
		ptr->node=temp;
		ptr->next=NULL;
		t=hdr; prev=NULL;
		if(temp->ava_copies > t->node->ava_copies)                   //bcox i need to make list which is in descending oreder i=of available copies
		{
			ptr->next=hdr;
			hdr=ptr;
		}
		else
		{
			while(t!=NULL && (temp->ava_copies <= t->node->ava_copies ))
			{
				prev=t;
				t=t->next;
			}
			prev->next=ptr;
			ptr->next=t;
			
		}
		temp=temp->next;
		
	}

	int l=0;
	int pop_book=hdr->node->ava_copies;
	l++;
	kth_book *p;
	while(hdr!=NULL && l<k)
	{
		while(hdr!=NULL && pop_book==hdr->node->ava_copies)
		{
			p=hdr;
			hdr=hdr->next;
			free(p);
				
		}
		if(hdr!=NULL)
	    	pop_book=hdr->node->ava_copies;
		l++;
	}                                  //after this loop hdr points to first node which is kth popular
	t=hdr;
	kth_book *pp;
	prev=NULL;
	
	while(t!=NULL && (t->node->ava_copies==pop_book))
	{
		prev=t;
		t=t->next;
	}                                   //after this t points to node which are after kth popular which we don't need, so deleting them
	
	if(t!=NULL)
	{
		prev->next=NULL;                //ending the list of kth popular book
		while(t!=NULL)
		{
			pp=t;
			t=t->next;
			free(pp);
		}
	}
	return hdr;
}

/*	while(t!=NULL && l<k)
	{
		while(pop_book==t->node->ava_copies && t->next!=NULL)
		{
			t=t->next;	
		}
		if(pop_book==t->node->ava_copies)                  //returns -1 if no kth popular book found
		{
			return -1;
		}
		pop_book=t->node->ava_copies;
		l++;
	}                                  //after this loop t points to first node which is kth popular
	l=-1;
	while(t!=NULL && (t->node->ava_copies==pop_book))
	{
		kth_books[++l]=t->node->book_name;
		t=t->next;
	}
	
	return l;*/


rec_node* most_pop_auth(rec_node *head)
{
	rec_node *ret_head,*temp,*ptr,*t;
	ret_head=NULL;
	int max=0,sum;
	temp=head;
	char *name,*name_ret;
	name=temp->auth_name;
	while(temp!=NULL)
	{
		sum=0;
		while(temp!=NULL && strcmp(name,temp->auth_name)==0)
		{
			sum+=temp->ava_copies;
			
			 ptr=(rec_node*)malloc(sizeof(rec_node));
			 ptr->auth_name=(char*)malloc(sizeof(char)*15);
			 strcpy(ptr->auth_name,temp->auth_name);
			 ptr->book_name=(char*)malloc(sizeof(char)*15);
			 strcpy(ptr->book_name,temp->book_name);
			 ptr->ava_copies=temp->ava_copies;
			 ptr->pub_year=temp->pub_year;
			 ptr->next=NULL;
			temp=temp->next;
			if(ret_head==NULL)
			   ret_head=ptr;
			else
			{
				ptr->next=ret_head;
				ret_head=ptr;
			}
		}
		rec_node *prev,*p;
		if(sum>max)
		{
			rec_node *prev,*p;
			prev=NULL;
			t=ret_head;
			name_ret=t->auth_name;
			while(t!=NULL && strcmp(name_ret,t->auth_name)==0)
			{
				prev=t;
				t=t->next;                                
			}                          //at end t is pointing to first node which has differnt name
			if(t!=NULL)
			{
				prev->next=NULL;
				while(t!=NULL)
				{
					p=t;
					t=t->next;
					free(p);
					
				}
			}
			max=sum;
			
		}
		else if(sum<max)
		{
			
			while(ret_head!=NULL && strcmp(name,ret_head->auth_name)==0)
			{
				p=ret_head;
				ret_head=ret_head->next;
				free(p);
			}
		}
		if(temp!=NULL)
			name=temp->auth_name;
	}
	return ret_head;
}

rec_node* least_pop_auth(rec_node *head,int p,int k)
{
	rec_node *ret_head,*temp,*ptr,*t;
	ret_head=NULL;
	int max=0,sum;
	temp=head;
	char *name,*name_ret;
	name=temp->auth_name;
	while(temp!=NULL)
	{
		sum=0;
		while(temp!=NULL && strcmp(name,temp->auth_name)==0)
		{
			sum+=temp->ava_copies;
			
			 ptr=(rec_node*)malloc(sizeof(rec_node));
			 ptr->auth_name=(char*)malloc(sizeof(char)*15);
			 strcpy(ptr->auth_name,temp->auth_name);
			 ptr->book_name=(char*)malloc(sizeof(char)*15);
			 strcpy(ptr->book_name,temp->book_name);
			 ptr->ava_copies=temp->ava_copies;
			 ptr->pub_year=temp->pub_year;
			 ptr->next=NULL;
			temp=temp->next;
			if(ret_head==NULL)
			   ret_head=ptr;
			else
			{
				ptr->next=ret_head;
				ret_head=ptr;
			}
		}
		rec_node *pp;
		if(p<=((sum*k)/100))
		{
			while(ret_head!=NULL && strcmp(name,ret_head->auth_name)==0)
			{
				pp=ret_head;
				ret_head=ret_head->next;
				free(pp);
			}
		}
		if(temp!=NULL)
			name=temp->auth_name;
		
	}
	return ret_head;
}
	


void print_list(rec_node *head)
{
	rec_node *temp;
	temp=head;
	while(temp!=NULL)
	{
		printf("\n\nAuthor Name:%s",temp->auth_name);
		printf("\nBook Name:%s",temp->book_name);
		printf("\nAvailable copies:%d",temp->ava_copies);
		printf("\nPublication Year:%d",temp->pub_year);
		temp=temp->next;
	}
}
int insert_union2(rec_node **head,char *bname,char *au_name,int year,int av_copies)
{
		rec_node *ptr;
		ptr=(rec_node*)malloc(sizeof(rec_node));
		 ptr->book_name=(char*)malloc(sizeof(char)*(strlen(bname)+1));
		 strcpy(ptr->book_name,bname);
		 ptr->auth_name=(char*)malloc(sizeof(char)*(strlen(au_name)+1));
		 strcpy(ptr->auth_name,au_name);
	   	 ptr->pub_year=year;
		 ptr->ava_copies=av_copies;
		 ptr->next=NULL;
		/*node is made with desired entries*/
		
		if(isempty(*head)==1)
		{
			*head=ptr;
		}
		else
		{
			rec_node *prev;
			prev=NULL;
			int ins;
			ins=getposition(*head,ptr,&prev);
			if(prev==NULL && ins==1)
			{
				ptr->next=*head;
				*head=ptr;
			}
			else if(prev==NULL && ins==0)
			{
				if(ptr->pub_year>= (*head)->pub_year)
				{
					(*head)->ava_copies=ptr->ava_copies;
					(*head)->pub_year=ptr->pub_year;
					free(ptr);
				}
				else
				{
					free(ptr);
				}
				
			}
			else if(prev!=NULL && ins==1)
			{
				ptr->next=prev->next;
				prev->next=ptr;
			}
			else if(prev!=NULL && ins==0)
			{
				if(ptr->pub_year>=prev->next->pub_year)    //for retaining the copy with latest publication year
				{
					prev->next->ava_copies=ptr->ava_copies;
					prev->next->pub_year=ptr->pub_year;
					free(ptr);
				}
				else
				{
					free(ptr);
				}
			}
		}
	return 1;
}
void insert_union1(rec_node **head3,rec_node *head)
{
	rec_node *temp,*temp3;
	temp=head;
	temp3=(rec_node*)malloc(sizeof(rec_node));
	temp3->auth_name=(char*)malloc(sizeof(char)*(strlen(temp->auth_name)+1));
	strcpy(temp3->auth_name,temp->auth_name);
	temp3->book_name=(char*)malloc(sizeof(char)*(strlen(temp->book_name)+1));
	strcpy(temp3->book_name,temp->book_name);
	temp3->ava_copies=temp->ava_copies;
	temp3->pub_year=temp->pub_year;
	temp3->next=NULL;
	*head3=temp3;
	rec_node *ptr;
	ptr=temp3;
	temp=temp->next;
	while(temp!=NULL)
	{
		temp3=(rec_node*)malloc(sizeof(rec_node));
		temp3->auth_name=(char*)malloc(sizeof(char)*(strlen(temp->auth_name)+1));
		strcpy(temp3->auth_name,temp->auth_name);
		temp3->book_name=(char*)malloc(sizeof(char)*(strlen(temp->book_name)+1));
		strcpy(temp3->book_name,temp->book_name);
		temp3->ava_copies=temp->ava_copies;
		temp3->pub_year=temp->pub_year;
		temp3->next=NULL;
		ptr->next=temp3;
		ptr=ptr->next;
		temp=temp->next;
	}
}
/*
void intersection(rec_node **head3,rec_node *head,rec_node *head2)
{
	rec_node *temp1,*temp2,*temp3,*ptr;
	temp1=head;
	temp2=head2;
	while(temp1!=NULL && temp2!=NULL)
	{
		while(strcmp(temp1->auth_name,temp2->auth_name)==0)
		{
			if((strcmp(temp1->book_name,temp2->book_name)==0) && temp1->ava_copies==temp2->ava_copies && temp1->pub_year==temp2->pub_year)
			{
				temp3=(rec_node*)malloc(sizeof(rec_node));
				temp3->auth_name=(char*)malloc(sizeof(char)*(strlen(temp1->auth_name)+1));
				strcpy(temp3->auth_name,temp1->auth_name);
				temp3->book_name=(char*)malloc(sizeof(char)*(strlen(temp1->book_name)+1));
				strcpy(temp3->book_name,temp1->book_name);
				temp3->ava_copies=temp1->ava_copies;
				temp3->pub_year=temp1->pub_year;
				temp3->next=NULL;
				if((*head3)==NULL)
				{
				   *head3=temp3;
				   ptr=temp3;
				}
				else
				{
					ptr->next=temp3;
					ptr=ptr->next;
				}
			}
			if(temp2->next!=NULL)
			    temp2=temp2->next;
			else
				break;	
		}
		temp1=temp1->next;
	}
	
}*/
void intersection(rec_node **head3,rec_node *head,rec_node *head2)
{
	rec_node *temp1,*temp2,*temp3,*ptr;
	temp1=head;
	temp2=head2;
	while(temp2!=NULL)
	{
		
		while(temp1!=NULL && strcmp(temp1->auth_name,temp2->auth_name)<0)
		{
			temp1=temp1->next;
		}
		if(temp1!=NULL)
		{
			if(strcmp(temp1->auth_name,temp2->auth_name)==0)
			{
				if((strcmp(temp1->book_name,temp2->book_name)==0) && temp1->ava_copies==temp2->ava_copies && temp1->pub_year==temp2->pub_year)
				{
					temp3=(rec_node*)malloc(sizeof(rec_node));
					temp3->auth_name=(char*)malloc(sizeof(char)*(strlen(temp1->auth_name)+1));
					strcpy(temp3->auth_name,temp1->auth_name);
					temp3->book_name=(char*)malloc(sizeof(char)*(strlen(temp1->book_name)+1));
					strcpy(temp3->book_name,temp1->book_name);
					temp3->ava_copies=temp1->ava_copies;
					temp3->pub_year=temp1->pub_year;
					temp3->next=NULL;
					if((*head3)==NULL)
					{
				   		*head3=temp3;
				   		ptr=temp3;
					}
					else
					{
						ptr->next=temp3;
						ptr=ptr->next;
					}
					temp1=temp1->next;
					temp2=temp2->next;
				}
				else
				{
					temp2=temp2->next;
				}
					
			}
			else
			{
				temp2=temp2->next;
			}
		
		}
		else
		{
			break;
		}
		
	}
}

void difference(rec_node **head3,rec_node *head2)
{
	rec_node *temp3,*temp2,*prev,*p;
	temp3=*head3;
	temp2=head2;
	prev=NULL;
	while(temp2!=NULL)
	{
		while(temp3!=NULL && strcmp(temp3->auth_name,temp2->auth_name)<0)
		{
			prev=temp3;
			temp3=temp3->next;
		}
		if(temp3!=NULL)
		{
			if(strcmp(temp3->auth_name,temp2->auth_name)==0)
			{
				if((strcmp(temp3->book_name,temp2->book_name)==0)&& temp3->ava_copies==temp2->ava_copies && temp3->pub_year==temp2->pub_year)
				{
					p=temp2;
					if(prev==NULL)
					{
						*head3=temp3->next;
						
					}
					else
					{
						prev->next=temp3->next;
					}
					
					temp2=temp2->next;
					free(p);
					temp3=temp3->next;
					prev=prev->next;
				}
				else
				{
					temp2=temp2->next;
				}
			}
			else
			{
				temp2=temp2->next;
			}
		}
	}
	
}
int main()
{
	rec_node *head;
	head=NULL;
	
	
	int ans=1,choice;
	while(ans)
	{
		system("cls");
		printf("\n\t\t\tBOOK RECORD!!!\n");
		printf("1.Insert in record\n");
		printf("2.Delete a record\n");
		printf("3.Get Top Most Book Author\n");
		printf("4.Print the list\n");
		printf("5.Most Popular Author\n");
		printf("6.Kth popular book\n");
		printf("7.Least Popular Author\n");
		printf("8.List Operations\n");
		printf("Exit\n");
		printf("Enter any of the above choice:");
		scanf("%d",&choice);
		int i;
		switch(choice)
		{
			case 1:
				char *bname,*aut_name;
				int year,copies_av,success_ret;
				printf("\nEnter the name of book:");
				bname=(char*)malloc(sizeof(char)*15);
				scanf("%s",bname);
				printf("\nEnter the name of author:");
				aut_name=(char*)malloc(sizeof(char)*15);
				scanf("%s",aut_name);
				printf("\nEnter the year of publication & no. of available copies:");
				scanf("%d %d",&year,&copies_av);
				success_ret=insert(&head,bname,aut_name,year,copies_av);
				if(success_ret)
				   printf("\n\n\t\tInsertion in record sussessful!!!");
				else
				   printf("\n\n\t\tError in insertion in record, try again!!");
				break;
			case 2:
				if(isempty(head))
				{
					printf("List is empty, cannot delete element");
					break;
				}
				char boname[15],au_name[15];
				int delete_ret;
				printf("\nEnter the name of book:");
				scanf("%s",boname);
				printf("\nEnter the name of author:");
				scanf("%s",au_name);
				delete_ret=delete_ele(&head,boname,au_name);
				if(delete_ret)
				   printf("\n\n\t\tElement deleted successfully!!");
				else
				   printf("\n\n\t\tError in deleting the node!!");
				break;
			case 3:
				if(isempty(head))
				{
					printf("\n\n\t\tList is empty,cannot perform this operation");
					break;
				}
				
				char book_name[15];
			 /*	char* aname[20];       //there can be more than 1 top author
			 	i=0;
			 	while(i<20)
			 	{
			 		aname[i]=NULL;
			 		i++;
				}  
				int ret;*/
				rec_node *top_auth_list;
				printf("\nEnter the name of book for which u wish to know topmost author:");
				scanf("%s",book_name);
				top_auth_list= get_top_auth(head,book_name);
			/*	if(ret==-1)
				   printf("\n\n\t\tNo such book found");
				else
				{
					printf("\n\n\t\t");
					for(i=0;i<=ret;i++)
					{
						printf("%s ",aname[i]);
					}
					printf("are the top author(s)");
				}*/
				if(top_auth_list==NULL)
				{
					printf("\n\n\t\tNo such book found");
				}
				else
				{
					print_list(top_auth_list);
				}
				break;
				
			case 4:
				print_list(head);
				break;
			case 5:
				if(isempty(head))
				{
					printf("\n\n\t\tList is empty,cannot perform this operation");
					break;
				}
				rec_node *h;
				h=NULL;
				h=most_pop_auth(head);
				
				printf("\n\n\t\t");
				print_list(h);
				printf("\nare the most popular author(s)!!");
				break;
			case 6:
				//char* kth_books[15];
				int k; kth_book *kth;
				printf("\nHere we find the Kth popular book(s). Thus enter the value of k:");
				scanf("%d",&k);
				kth=kth_popular_book(head,k);
				
				if(kth==NULL)
				{
					printf("\n\n\t\tNo %d popular book!!",k);
				}
				else
				{
					print_kth_book(kth);
				}
			/*	ret_books=kth_popular_book(head,k,kth_books);
				if(ret_books==-1)
				{
					printf("\n\n\t\tNo %d popular book!!",k);
				}
				else
				{
					printf("\n\n\t\t");
					for(i=0;i<=ret_books;i++)
					{
						printf("%s ",kth_books[i]);
					}
					printf("are the most popular author(s)!!");
				}*/
				break;
			case 7:
				int p; 
				rec_node *hh;
				printf("\nHere we are finding least popular author!! It is decided based on if it has less than p copies for \n k\% or more than k\% number of books written by the same author ");
				printf("\nHence enter p and k:");
				scanf("%d %d",&p,&k);
				hh=least_pop_auth(head,p,k);	
				print_list(hh);
				printf("\nare the least popular authors!!");
				break;	
			case 8:
				{
				printf("\t");
				rec_node *head2,*head3;
				head2=NULL; head3=NULL;
				int ans2=1,choice2;
				while(ans2)
				{
					system("cls");
					printf("\n");
					printf("\t1.Create nodes in list 2\n");
					printf("\t2.Print the list2\n");
					printf("\t3.Union of list 1 and list 2 in list 3\n");
					printf("\t4.Print the list3\n");
					printf("\t5.Intersection of list1 and list2 in list3\n");
					printf("\t6.Difference in 2 lists\n");
					printf("\t7.Symmetric Difference in 2 lists\n");
					printf("\tEnter ur choice:");
					scanf("%d",&choice2);
					switch(choice2)
					{
						case 1:
							{
								char *bname,*aut_name;
								int year,copies_av,success_ret;
								printf("\nEnter the name of book:");
								bname=(char*)malloc(sizeof(char)*15);
								scanf("%s",bname);
								printf("\nEnter the name of author:");
								aut_name=(char*)malloc(sizeof(char)*15);
								scanf("%s",aut_name);
								printf("\nEnter the year of publication & no. of available copies:");
								scanf("%d %d",&year,&copies_av);
								success_ret=insert(&head2,bname,aut_name,year,copies_av);
								if(success_ret)
				   					printf("\n\n\t\tInsertion in record sussessful!!!");
								else
				  				 	printf("\n\n\t\tError in insertion in record, try again!!");
							}
							break;
						case 2:
							print_list(head2);
							break;
						case 3:
							{
								rec_node *temp; 
								if(head!=NULL)
							    	insert_union1(&head3,head);
								temp=head2;
								while(temp!=NULL)
								{
									insert_union2(&head3,temp->book_name,temp->auth_name,temp->pub_year,temp->ava_copies);
									temp=temp->next;
								}
								printf("\n\n\t\tUnion done!!");
							}
							break;
						case 4:
							{
								print_list(head3);
							}
							break;
						case 5:
							{
								head3=NULL;
								if(head!=NULL && head2!=NULL)
								{
									intersection(&head3,head,head2);
									printf("\n\n\t\tIntersection done!!");
								}
								if(head3==NULL)
									printf("\n\n\t\tNo common node in list1 & list2 !!");
							}
							break;
						case 6:
							{
								head3=NULL;
								if(head!=NULL)
								{
									insert_union1(&head3,head);                  //makes list 3 same as list 1
								}
							    	
							    difference(&head3,head2);                       //elimanates from list 3 the same elements in list 2
							    printf("\n\n\t\tDifference of two list is done!!");
							}
							break;
						case 7:
							{                                       //A sym. diffe= (A union B)-(A intersection B)
								rec_node *hu,*hi;
								rec_node *temp; head3=NULL; hu=NULL; hi=NULL;
								if(head!=NULL)
							    	insert_union1(&hu,head);
								temp=head2;
								while(temp!=NULL)
								{
									insert_union2(&hu,temp->book_name,temp->auth_name,temp->pub_year,temp->ava_copies);
									temp=temp->next;
								}                                //A union B done stored in hu
								
								
								if(head!=NULL && head2!=NULL)
								{
									intersection(&hi,head,head2);     //A intersection B done in hi
							    }
							    if(hu!=NULL)
								{
									insert_union1(&head3,hu);                 
								}
							    	
							    difference(&head3,hi);          //A symmetric difference B sone
							    
							    printf("Symmetric Differnce of lists done!");
							}
							break;
							
						default:
							{
								printf("\n\n\t\tWrong Choice!!");
								break;
							}
					}
					printf("\n\nWant to perform more list opertion?(0/1)");
					scanf("%d",&ans2);
				}
				}
				break;	
			default:
				{
					printf("\n\n\tWrong Choice");
					break;
				}
				
			
		}
    	printf("\n\nWant to perform more opertions?(1/0)");
    	scanf("%d",&ans);
	}
	return 0;
}
