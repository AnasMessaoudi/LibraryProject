#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct QNode{
    char client_name[256];
    struct QNode* next;
};
struct queue{
    struct QNode *front,*rear;
};
struct AllBooks{
    char Bookname[256];
    bool availability;
    struct queue clients_queue;
    struct AllBooks* next;
};
struct book{
    char bookname[256];
    struct book* next;
};
struct client{
    char name[256];
    int books_number;
    struct book* client_books;
    struct client* next;
};
void initQueue(struct queue q) {
    q.front = q.rear = NULL;
}
struct QNode* createqueue(char* s){
    struct QNode* temp=(struct QNode*)malloc(sizeof(struct QNode));
    strcpy(temp->client_name,s);
    temp->next=NULL;
    return temp;
}
void push_client_to_queue(struct queue* q,char* s){//function to add clients to the books queue
    struct QNode* temp=createqueue(s);
    if(q->rear==NULL){
        q->front=temp;
        q->rear=temp;
    }
    else{
        q->rear->next=temp;
        q->rear=q->rear->next;
    }
    printf("Mr %s you have been added to the book's queue we will inform you when the book is available !!",temp->client_name);
}
void pop_client_from_queue(struct queue* q){//function to delete clients to the books queue
    if(q->front==NULL || q->rear==NULL){
        return;
    }
    struct QNode* oldfront=q->front;
    q->front=oldfront->next;
    if(q->front==NULL){
        q->rear=NULL;
    }
    printf("Mr %s you have been removed from the book's queue !",oldfront->client_name);
    free(oldfront);
}
void add_clientToFile(char* name){//function to add clients to the file that contains clients names
    FILE* file=fopen("zaboun.txt", "a");
    if (file == NULL) {
        printf("Error opening file for creation.");
        return;
    }
    fprintf(file,"%s\n",name);
    fclose(file);
    printf("\nYour name has been added to the borrow list successfully !!");
}
bool search_clientInFile(char* name){//check if the client is in the file or not
    FILE* file=fopen("zaboun.txt","r");
    if (file == NULL) {
        printf("Error opening file for creation.\n");
    }
    else{
    char line[256];
    bool found = false;
    while(fgets(line,sizeof(line),file)!=NULL && found==false){
        line[strcspn(name, "\n")] = 0;
        if(strcmp(line,name)==0){
            printf("we have found your name in our list !");
            found=true;
        }
    }
    if(found==false){
        printf("we have not found you in our list !");
    }
    fclose(file);
    return found;
}
}
void deleting_book_from_client_data(struct client* temp,char* s){//delete the book from client LL
    struct book* book_to_remove=temp->client_books;
    struct book* prev_book = NULL;
    while(book_to_remove!=NULL && strcmp(book_to_remove->bookname,s)!=0){
        prev_book=book_to_remove;
        book_to_remove=book_to_remove->next;
    }
    if(book_to_remove==NULL){
        printf("no book to remove");
    }
    else if (prev_book == NULL){
        prev_book=book_to_remove;
        book_to_remove=prev_book->next;
        free(prev_book);
    }
    else{
        prev_book->next=book_to_remove->next;
        free(book_to_remove);
    }
}
struct client* Insert_NewClientInTailInLL(struct client* head,char* Name){
    struct client* newtail=malloc(sizeof(struct client));
    newtail->next=NULL;
    strcpy(newtail->name,Name);
    newtail->books_number=0;
    newtail->client_books=NULL;
    if(head==NULL){
        head=newtail;
        return newtail;
    }
    else{
    struct client* temp=head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newtail;
    }
    return head;
}
struct client* searchForClientInLL(struct client* head,char* Name){
    struct client* temp=head;
    while(temp!=NULL){
        if(strcmp(temp->name,Name)==0){
            return temp;
        }
        temp=temp->next;
    }
    return temp;
}
bool book_searchInFile(char* BOOK){//search book name in file to check if it exisist or not 
    FILE* file=fopen("C:\\Users\\anesm\\OneDrive\\Desktop\\Progs\\C progs\\C learning\\BOOKS.txt","r");
    if (file == NULL) {
        printf("Error opening file for creation.\n");
    }
    else{
        char line[256];
    while(fgets(line,sizeof(line),file)!=NULL){
        if(strcmp(line,BOOK)==0){
            printf("Book found!!\n");
            return true;
        }
    }
    }
    fclose(file);
    return false;
}
struct AllBooks* search_book_in_LL(struct AllBooks* firstbook,char* BOOK){
    struct AllBooks* s=firstbook;
    if(s==NULL){
        printf("error no book in the LL");
        return NULL;
    }
    BOOK[strcspn(BOOK, "\n")] = 0;
    while(s!=NULL && strcmp(s->Bookname,BOOK)!=0){
        s=s->next;
    }
    return s;
}
struct AllBooks* fill_books_in_LL(struct AllBooks* head){
    FILE* pf=fopen("C:\\Users\\anesm\\OneDrive\\Desktop\\Progs\\C progs\\C learning\\BOOKS.txt","r");
    if(pf==NULL){
        printf("error opening BOOKS file");
        return NULL;
    }
    struct AllBooks* temp=(struct AllBooks*)malloc(sizeof(struct AllBooks));
    if(head==NULL){
        head=temp;
    }
    else{
        head->next=temp;
    }
    char line[256];
    while(fgets(line,sizeof(line),pf)!=NULL){
        temp->availability=true;
        initQueue(temp->clients_queue);
        strcpy(temp->Bookname,line);
        temp->next=(struct AllBooks*)malloc(sizeof(struct AllBooks));
        temp=temp->next;
    }
    temp->next=NULL;
    return head;
}
struct book* add_book_to_client_data(struct client* temp,char* s){//add the book to client LL
    struct book* booktoadd=(struct book*)malloc(sizeof(struct book));
    strcpy(booktoadd->bookname,s);
    booktoadd->next=NULL;
    if(temp->client_books==NULL){
        temp->client_books=booktoadd;
    }
    else{
    struct book* temp2=temp->client_books;
    while(temp2->next!=NULL){
        temp2=temp2->next;
    }
    temp2->next=booktoadd;
}
return temp->client_books;
}
void put_clients_data_in_file(struct client* temp){//add the clients new data to the file 
    FILE* file=fopen("C:\\Users\\anesm\\OneDrive\\Desktop\\Progs\\C progs\\C learning\\zaboun_data.txt","a");
    if (file == NULL) {
        printf("Error1 opening file for creation.\n");
        return;
    }
    fprintf(file,"%s;%d ",temp->name,temp->books_number);
    struct book* ktob=temp->client_books;
    while(ktob!=NULL){
        fprintf(file,";%s",ktob->bookname);
        ktob=ktob->next;
    }
    fprintf(file,"\n");
    fclose(file);
}
struct client* create_CLIENTLL_from_file(){
    FILE* file=fopen("C:\\Users\\anesm\\OneDrive\\Desktop\\Progs\\C progs\\C learning\\zaboun_data.txt","r");
    if (file == NULL) {
        printf("Error2 opening file for creation.\n");
        return NULL;
    }
    char line[256];
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0)return NULL;
    rewind(file);
    struct client* clients=(struct client*)malloc(sizeof(struct client));
    struct client* tempc=clients;
    while(fgets(line,sizeof(line),file)!=NULL){
        char* token = strtok(line, ";");
        strcpy(tempc->name,token);
        token=strtok(NULL,";");
        tempc->books_number=atoi(token);
        tempc->client_books=malloc(sizeof(struct book));
        struct book* temp=tempc->client_books;
        if(token==NULL || strcmp(token,"0 \n")==0){
            tempc->client_books=NULL;
        }
        else{
            struct book* a=temp;
            while ((token = strtok(NULL, ";\n")) != NULL){
                strcpy(temp->bookname,token);
                temp->next=malloc(sizeof(struct book));
                a=temp;
                temp=temp->next;
            }
            a->next=NULL;
        }
        tempc->next=malloc(sizeof(struct client));
        tempc=tempc->next;
    }
    tempc->next=NULL;
    fclose(file);
    return clients;
}
void modify_book_data_in_file(struct AllBooks* head){
    FILE* file=fopen("C:\\Users\\anesm\\OneDrive\\Desktop\\Progs\\C progs\\C learning\\books_data.txt","w");
    if(file==NULL){
        printf("error opening the book data file to overwrite it");
    }
    else{
    struct AllBooks* temp=head;
    while(temp!=NULL){
        char av[10];
        if(temp->availability==true){strcpy(av,"true");}
        else{strcpy(av,"false");}
        fprintf(file,"%s,%s",temp->Bookname,av);
        struct QNode* temp2=temp->clients_queue.front;
        while(temp2!=NULL){
            fprintf(file,";%s",temp2->client_name);
            temp2=temp2->next;
        }
        fprintf(file,"\n");
        temp=temp->next;
    }
}
fclose(file);
}
struct AllBooks* fill_books_in_LL_from_file(){
    FILE* file=fopen("C:\\Users\\anesm\\OneDrive\\Desktop\\Progs\\C progs\\C learning\\books_data.txt","r");
    if(file==NULL){
        printf("error opening the book data file to create books LL from it");
        return NULL;
    }
    struct AllBooks* head=malloc(sizeof(struct AllBooks));
    struct AllBooks* temp=head;
    struct AllBooks* prev=head;
    temp->next=NULL;
    char line[256];
    while(fgets(line,sizeof(line),file)!=NULL){
        initQueue(temp->clients_queue);
        char* token = strtok(line, ",");
        strcpy(temp->Bookname,token);
        token=strtok(NULL,",");
        temp->availability=(strcmp(token,"true\n")==0 ||strcmp(token,"true")==0);
        if (token = strtok(NULL, ";\n"))
        {
            while((token = strtok(NULL, ";\n")) != NULL){
            push_client_to_queue(&temp->clients_queue,token);
        }
        }
        else{
            temp->clients_queue.front=NULL;
            temp->clients_queue.rear=NULL;
        }
        prev=temp;
        temp->next=malloc(sizeof(struct AllBooks));
        temp=temp->next;
        temp->next=NULL;
    }
    prev->next=NULL;
    fclose(file);
    return head;
}
int main(){
    int choice;
    char name[256];
    struct AllBooks* firstbook;
    firstbook=fill_books_in_LL_from_file(firstbook);
    struct AllBooks* f=firstbook;
    while(f!=NULL){
        printf("%s",f->Bookname);
        if(f->availability==true)printf(" true");
        else{printf(" false");}
        printf("\n");
        f=f->next;
    }
    struct client* head=create_CLIENTLL_from_file();//read clients LL from file
    printf("enter your name:");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    if(search_clientInFile(name)==false){
        printf("\nYour name will be added to the clients list");
        head=Insert_NewClientInTailInLL(head,name);
        add_clientToFile(name);
        struct client* newclient=malloc(sizeof(struct client));
        strcpy(newclient->name,name);
        newclient->books_number=0;
        newclient->next=NULL;
        newclient->client_books=NULL;
        put_clients_data_in_file(newclient);
        free(newclient);
    }
    do{
        printf("\nWhats your plan for today(enter 1 or 2) :\n1_Borrow a book\n2_Return books");    
        scanf("%d",&choice);
    }while(choice!=2 && choice!=1);
    struct client* temp=searchForClientInLL(head,name); 
    char bookname[256];
    if(choice==1){
        if(temp==NULL){ 
            printf("error NULL");
        }
        if(temp->books_number<3){
            while (getchar() != '\n');  
            printf("\nPlease enter the name of the book you'd like to borrow:");
            fgets(bookname, sizeof(bookname), stdin);       
            if(book_searchInFile(bookname)==false){
                printf("the book is not available in our library !!");
            }
            else{
            struct AllBooks* BOOK=search_book_in_LL(firstbook,bookname);
                if(BOOK->availability==true){
                    printf("you have borrowed the book successfully");
                    BOOK->availability=false;
                    temp->books_number+=1;
                    temp->client_books=add_book_to_client_data(temp,bookname);
                    put_clients_data_in_file(temp);//add new data to clients data file
                    modify_book_data_in_file(firstbook);
                }
                else{
                    printf("the book is not available for the moment you have been added to the queue!");
                    push_client_to_queue(&BOOK->clients_queue,temp->name);
                    if(BOOK->clients_queue.front==NULL){
                        printf("empty");
                    }
                    else{
                        printf("%s",BOOK->clients_queue.front->client_name);
                    }
                    modify_book_data_in_file(firstbook);
                }
            }
    }
        else{
            printf("You have exceeded the limit of the books that you can borrow at the same time !!!\nYOU SHOULD RETURN AT LEAST ONE BOOK FOR YOU TO BORROW AGAIN!!");
        }
    }
    else{
        if(temp->books_number <= 0){
            printf("How can u give back books while you have none ?\n YOU MUST BORROW FIRST!");
        }
        else{
        int n;
        do
        {
            printf("enter the nomber of books your going to give back:");
            scanf("%d",&n);
        } while (n>temp->books_number);
        for(int i=0;i<n;i++){
            printf("enter the name of the book that you want to give back:");
            scanf("%s",bookname);
            temp->books_number=temp->books_number-1;
            //need a function to modify clients
            struct AllBooks* BOOK=search_book_in_LL(firstbook,bookname);
            if(BOOK->clients_queue.front!=NULL){
                char waiter[256];
                strcpy(waiter,BOOK->clients_queue.front->client_name);
                printf("Mr.%s the book %s that you wanted to borrow is now available!!",waiter,bookname);
            }
            deleting_book_from_client_data(temp,bookname);
            struct client* c=head;
            /*while (c!=NULL)
            {
                if(c->client_books!=NULL)printf("%s,%s,%d",c->name,c->client_books->bookname,c->books_number);
                else{
                    printf("%s,%d",c->name,c->books_number);
                }
                c=c->next;
            }*/
            // i need to add functions to make changes in the book data file and to modify client data and not add new client with the same name and different data
        }
    }
    } 
return 0;  
}