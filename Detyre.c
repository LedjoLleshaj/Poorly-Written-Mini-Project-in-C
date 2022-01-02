#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    int id;
    char emerPerdorues[50];
    char fjalekalim[50];

    //1 eshte ne pune, 0 nuk eshte ne pune
    int status;
} profesor;

typedef struct {
    int id;
    char emerPerdorues[50];
    char fjalekalim[50];
    int piket;

    //1 aktiv, 0 alumni(ish-student)
    int status;
} student ;

typedef struct {
    char permbajtja[1000];
    char pergjigje;

    /* pike nese pergjigja e dhene eshte e sakte, 0 pike nese pergjigja e zgjedhur eshte “Nuk e di” dhe -1 pike nese pergjigja eshte e gabuar.*/
    int vleresimi;
} pyetje;


profesor prof_data[10];
student student_data[30];
pyetje res[10];
int idprof=0;
int idstud=0;
int loggedInProf=0;
int loggedInStud=0;
int pytjesakte[10]={0};
int pytjegabuar[10]={0};
int nrpglobal=0;



//------------------------------------------------------------------------------------------------------------------------------------------------------------
void printMenu(){
	
    printf("\n  Pershendetje\n");
    printf("->Shtyp 1 per Admin\n");
    printf("->Shtyp 2 per Profesor\n");
    printf("->Shtyp 3 per Student\n\n");
};

void printAdminMenu(){

    printf("\n  Pershendetje Admin\n");
    printf("->Shtyp 1 per te shtuar profesor\n");
    printf("->Shtyp 2 per te shtuar student\n");
    printf("->Shtyp 3 per tu kthyer mbrapa\n\n");

};
void printProfMenu()
{
    printf("\n  Pershendetje Profesor\n");
    printf("->Shtyp 1 per te hartuar provim\n");
    printf("->Shtyp 2 per te shikuar rezultatet\n");
    printf("->Shtyp 3 per te shikuar Raporte\n");
    printf("->Shtyp 4 per tu kthyer mbrapa\n\n");
};
void printStudentMenu()
{
    printf("\n  Pershendetje Student\n");
    printf("Shtyp 1 per te marre provim\n");
    printf("Shtyp 2 per te shikuar rezultatet\n");
    printf("Shtyp 3 per te shkuar mbrapa\n\n");

};

void load_data()
{
    FILE *file;
    file=fopen("profesor.txt","r");
    char buffer[20];
	int x=0;
		
	while(!feof(file)){
        
        fscanf(file,"%d",&prof_data[x].id);
        //printf("%d\n",prof_data[x].id);
        fscanf(file,"%s",prof_data[x].emerPerdorues);
      	//printf("%s\n",prof_data[x].emerPerdorues);
        fscanf(file,"%s",prof_data[x].fjalekalim);
        //printf("%s\n",prof_data[x].fjalekalim);
        fscanf(file,"%d",&prof_data[x].status);
        //printf("%d\n;;\n",prof_data[x].status);
		idprof++;
		x++;
	}




    fclose(file);




    file=fopen("studentet.txt","r");
	x=0;
    while(!feof(file)){

        fscanf(file,"%d",&student_data[x].id);
        //printf("%d\n",student_data[x].id);
        fscanf(file,"%s",student_data[x].emerPerdorues);
        //printf("%s\n",student_data[x].emerPerdorues);
        fscanf(file,"%s",student_data[x].fjalekalim);
        //printf("%s\n",student_data[x].fjalekalim);
        fscanf(file,"%d",&student_data[x].piket);
        //printf("%d\n",student_data[x].piket);
        fscanf(file,"%d",&student_data[x].status);
        //printf("%d\n",student_data[x].status);
		idstud++;
		x++;
    }
    fclose(file);
}
int gjeneroFjalekalim(int id, char emri[], char mbiemri[])
{
    int shuma=0;
	int l=strlen(emri);
	int l2=strlen(mbiemri);
    for(int i=0; i<l; i++)
    {
//        printf("shuma: %d, i: %d\n",shuma,i);
        shuma+=emri[i];
    }
    for(int i=0; i<l2; i++)
    {
//        printf("shuma: %d, i: %d\n",shuma,i);
        shuma+=mbiemri[i];
    }
    return id*shuma;
    return 0;
};

int checkAdmin(char emriPerdorues[], char fjalekalimi[]){

    char username[50];
    char psw[50];
    FILE *fileCred;

    fileCred=fopen("kredencialetAdmin.txt","r");
	if(fileCred){

    	fscanf(fileCred,"%s",username);
		fscanf(fileCred,"%s",psw);
		//printf("%s\n%s\n",username,psw);
    	if(!strcmp(username,emriPerdorues) && !strcmp(psw,fjalekalimi)){ //te dyja==0 qe te jene kredenciale valide
    	
        	printf("Login success!\n");
       		return 1;
    	}
    	else{
        	printf("Kredencialet e gabuara,provo perseri\n");
        	return 0;
    	}
    	fclose(fileCred);
	}
	else{
		printf("Error file : kredencialetAdmin.txt\n");
		return 0;
	}
};
int checkProf(char emriPerdorues[], char fjalekalimi[])
{

    int succes=-1;
   //printf("Gjithsej %d profesore\n",loggedInProf+1);
    for(int i=0; i<idprof+1; i++)
    {
        printf("%d: %s->%s\n",i,prof_data[i].emerPerdorues,prof_data[i].fjalekalim);
        if(!strcmp(emriPerdorues,prof_data[i].emerPerdorues) && !strcmp(fjalekalimi,prof_data[i].fjalekalim))
        {
			printf("succes\n");
            succes=i;
			loggedInProf=i+1;
        }
    }
    if(succes!=-1)
    {
        printf("Login success!\n");
        return 1;
    }
    else
    {
        printf("Kredencialet e gabuara\n");
        return 0;
    }
};
int checkStudent(char emriPerdorues[], char fjalekalimi[])
{

    int login=0;
//    printf("Size: %d\n",idprof);
    for(int i=0; i<idstud; i++)
    {
//        printf("%d: %s-%s\n",i,prof_data[i].emerPerdorues,prof_data[i].fjalekalim);
        if(!strcmp(emriPerdorues,student_data[i].emerPerdorues) && !strcmp(fjalekalimi,student_data[i].fjalekalim))
        {
            login=1;
            loggedInStud=i+1;
			
        }
    }
    if(login)
    {
        printf("Login success!\n");
        return 1;
    }
    else
    {
        printf("Kredencialet e gabuara\n");
        return 0;
    }
};

void shikoRezultatetProf(char *prefix)
{
    char filename[20];
	char id[5];
	sprintf(id,"%d",loggedInProf);
    strcpy(filename,prefix);
	strcat(filename,id);
    FILE *fp =fopen(strcat(filename,"res.txt"),"r");
    char c;

    while(1)
    {
        c = fgetc(fp);
        if( feof(fp) )
        {
            break ;
        }
        printf("%c", c);
    }
    fclose(fp);
	printf("\n");
}
void shikoRezultatetStud(char *prefix)
{
    char filename[20];
	char id[5];
    strcpy(filename,prefix);
	sprintf(id,"%d",loggedInStud);
	strcat(filename,id);
    FILE *fp =fopen(strcat(filename,"res.txt"),"r");
	if(!fp){
		printf("ERROR %s\n",filename);
		return;
	}
    char c;

    while(1)
    {
        c = fgetc(fp);
        if( feof(fp) )
        {
            break ;
        }
        printf("%c", c);
    }
    fclose(fp);
	printf("\n");
}

void shtoProfesor(char emerPerdorues[],int fjalekalim, int status)
{
    FILE *fileProf;
    fileProf=fopen("profesor.txt","a");
	if(fileProf){
    	fprintf(fileProf,"%d\n%s\n%d\n%d\n",idprof,emerPerdorues,fjalekalim,status);
   		fclose(fileProf);
		printf("U ruajt");
		idprof++;
	}
	else{
		printf("Error file : profesor.txt\n");
	}

};


void shtoStudent(char emerPerdorues[],int fjalekalim, int status)
{
    FILE *fileStudent;
    fileStudent=fopen("studentet.txt","a");
	if(fileStudent){
    	fprintf(fileStudent,"%d\n%s\n%d\n%d\n",idstud,emerPerdorues,fjalekalim,status);
    	fclose(fileStudent);
	    printf("U ruajt");
		idprof++;
	}
	else{
		printf("Error file : student.txt\n");
	}
};


void harto_Provim()
{
    int nrP;
    char pyetje[500];
    char alternativat[4][200];
    char temp[]= {'a','b','c','d'};
    char sakte;
	char idchar[20];
    FILE *file;
    char prefix[20]="prof";
	sprintf(idchar,"%d",loggedInProf);
    printf("loggedin: %s\n",strcat(prefix,idchar));
    file=fopen(strcat(prefix,".txt"),"w");
	if(!file){
		printf("Error ne hapjen e dokumentit\n");
		return;
	}
    printf("Jepni numrin e pyetjeve: ");
    scanf("%d",&nrP);
	fprintf(file,"%d\n",nrP);
    for(int i=0; i<nrP; i++)
    {
		getchar();
        printf("%d: ",i+1);
        fgets(pyetje,2000,stdin);
		printf("%s",pyetje);
        for(int j=0; j<4; j++)
        {
            printf("%c: ",temp[j]);
            fgets(alternativat[j],200,stdin);
        }
        printf("Alternativa e sakte: ");
        scanf("%c",&sakte);
        fprintf(file,"%d.%s",i+1,pyetje);
        for(int x=0; x<4; x++)
        {
            fprintf(file,"%c)%s",temp[x],alternativat[x]);
        }
        fprintf(file,"%c\n",sakte);
    }
    fclose(file);
};
void raportet()
{

    int nx=nrpglobal;
	int max=0,maxIndex,temp;
	int i=0;
	int index=0;    



    printf("\nStudentet me 0 pike\n");
    for(i=0; i<nx; i++)
    {
        if(student_data[i].piket==0)
            printf("Studenti me id %d\n",student_data[i].id);
        if(student_data[i].piket>max)
        {
            max=student_data[i].piket;
            maxIndex=i;
        }
    }
    printf("\n");
    printf("Studenti me piket me te larta: %s-> %d pike\n",student_data[maxIndex].emerPerdorues,max);

	
	for(i=0;i<10;i++){
		if(temp<pytjegabuar[i]){
			temp=pytjegabuar[i];
			index=i;

		}
	}
	printf("Pyetja qe eshte gabuar me shume here: (%d here) eshte pytja nr %d\n",temp,index+1);

	temp=0;
	index=0;
	for(i=0;i<10;i++){
		if(temp<pytjesakte[i]){
			temp=pytjesakte[i];
			index=i;
			index++;
		}
	}
	printf("Pyetja qe eshte pergjigjur sakte me shume here: (%d here) eshte pytja nr %d\n",temp,index);

    printf("\nRenditja e studenteve \n");
    shikoRezultatetStud("student");

};
void Provim()
{
    int input;
    int nrPyetje;
    char filename[10]="prof";
    char id[5];
    char alternative[100];
    int piketGjithsej=0;
    char *prof;
    int profID;
	char tmp[25],stud[25]="student";
    printf("Zgjidhni provimin:\n");
    for(int i=0; i<idprof; i++)
    {
        printf("%d: %s\n",prof_data[i].id,prof_data[i].emerPerdorues);
    }
    printf("Input: ");
    scanf("%d",&input);
    prof=prof_data[input].emerPerdorues;
    profID=input;

    sprintf(id,"%d",input);
    strcat(filename,id);
	strcpy(tmp,filename);

	sprintf(id,"%d",loggedInStud);
	strcat(stud,id);

    FILE *file=fopen(strcat(filename,".txt"),"r");

    fscanf(file,"%d",&nrPyetje);
    printf("Nr pyetje:%d \n\n",nrPyetje);
	nrpglobal=nrPyetje;
    fgets(id,4,file);
    pyetje pyetjet[nrPyetje];
    char pergj[nrPyetje];
    printf("\n");
    
	for(int i=0; i<nrPyetje; i++){
        fgets(pyetjet[i].permbajtja,1000,file);
        printf("%s",pyetjet[i].permbajtja);
        for(int j=0; j<4; j++)
        {
            fgets(alternative,100,file);
            printf("%s",alternative);
        }
        pyetjet[i].pergjigje=fgetc(file);
        printf("Jepni pergjigjen: ");
        getchar();
        pergj[i]=getchar();
        if(pergj[i]==pyetjet[i].pergjigje)
        {
            pyetjet[i].vleresimi=1;
			pytjesakte[i]++;
            piketGjithsej++;
			res[i].vleresimi++;
        }
        else if(pergj[i]=='d')
        {
            pyetjet[i].vleresimi=0;
        }
		else{
			pyetjet[i].vleresimi=-1;
			pytjegabuar[i]++;
            piketGjithsej--;
			res[i].vleresimi--;
		}
        fgetc(file);
    }
    fclose(file);
	FILE *profres=fopen(strcat(tmp,"res.txt"),"a+");
		fprintf(profres,"%d-> %d/%d\n",loggedInStud,piketGjithsej,nrPyetje);
	fclose(profres);
	
	FILE *studres=fopen(strcat(stud,"res.txt"),"a+");
		fprintf(studres,"%d-> %d/%d\n",loggedInStud,piketGjithsej,nrPyetje);
	fclose(studres);
	
	student_data[loggedInStud].piket=piketGjithsej;


    printf("\nProvimi u krye\n");
    printf("Shtyp 1 per te shikuar vetem rezultatin\n");
    printf("shtyp 2 per te shikuar listen e detajuar\n");
    printf("Inputi: ");
    scanf("%d",&input);
    if(input==1)
    {
        printf("\nPiket gjithsej: %d/%d\n",piketGjithsej,nrPyetje);
    }
    else if(input==2)
    {
        for(int i=0; i<nrPyetje; i++)
        {
            printf("%s",pyetjet[i].permbajtja);
            printf("\nAlternativa e sakte: %c\n",pyetjet[i].pergjigje);
            printf("\nAlternativa e dhene: %c\n",pergj[i]);
            printf("\nVleresimi: %d\n---\n",pyetjet[i].vleresimi);
        }
    }

};


void adminPage()
{
    int input;
    char emri[50];
    char mbiemri[50];
	int fjalekalimi;
	int gen;

    do
    {

        printAdminMenu();
        printf("Inputi: ");
        scanf("%d",&input);
        if(input==3)
            break;//ndalon


        printf("Jepni emrin: ");
        scanf("%s",emri);

        printf("Jepni mbiemrin: ");
        scanf("%s",mbiemri);

        int status;
        switch(input)
        {
        case 1:
            printf("Jepni statusin(1 aktiv, 0 ne pune): ");
            scanf("%d",&status);
			printf("Shtyp 1 per psw automatice ose 0 per ta vendosure vete\n");
			scanf("%d",&gen);
			if(gen==1)
        		fjalekalimi=gjeneroFjalekalim(loggedInProf,emri,mbiemri);
			else{
				printf("Shkruani psw tuaj\n");
				scanf("%d",&fjalekalimi);
			}
            shtoProfesor(emri,fjalekalimi,status);
            break;
        case 2:
            printf("Jepni statusin(1 aktiv, 0 alumni): ");
            scanf("%d",&status);
			printf("Shtyp 1 per psw automatice ose 0 per ta vendosure vete\n");
			scanf("%d",&gen);
			if(gen==1)
        		fjalekalimi=gjeneroFjalekalim(loggedInStud,emri,mbiemri);
			else{
				printf("Shkruani psw tuaj\n");
				scanf("%d",&fjalekalimi);
			}
            shtoStudent(emri,fjalekalimi,status);
            break;
        default:
            printf("Input i gabuar\n");
        }
    }
    while(input!=3);

};
void profPage()
{
    int input;
    do
    {
        printProfMenu();
        printf("Input: ");
        scanf("%d",&input);
		if(input==4)
            break;//mbrapa
        switch(input)
        {
        case 1:
            harto_Provim();
            break;
        case 2:
            shikoRezultatetProf("prof");
            break;
        case 3:
            raportet();
            break;
        default:
            printf("Input i gabuar\n");
        }
    }
    while(1);
};
void studentPage()
{
    int input;
    do
    {

        printStudentMenu();
        printf("Input: ");
        scanf("%d",&input);
        if(input==3)
            break;
        switch(input){
        case 1:
            Provim();
            break;
        case 2:
            shikoRezultatetStud("student");
            break;
        default:
            printf("Input i gabuar\n");
        }
    }
    while(1);
};


void loginAdmin()
{
    int flag;
    do
    {
        char user[50];
        char password[50];
        printf("LOGIN:\n");
        printf("Ju lutem shkruani emrin: ");
        scanf("%s",user);
        printf("Ju lutem shkruani fjalekalimin: ");
        scanf("%s",password);
		printf("Your input: %s %s\n",user,password);//to check

        flag=checkAdmin(user, password);
    }
    while(!flag);
    adminPage();
};

void loginProfesor()
{
    int x;
    do
    {
        char user[50];
        char password[50];
        printf("LOGIN:\n");
        printf("Ju lutem shkruani emrin: ");
        scanf("%s",user);
        printf("Ju lutem shkruani fjalekalimin: ");
        scanf("%s",password);
		//printf("Your input: %s %s\n",user,password);//to check

        x=checkProf(user, password);
    }
    while(x==0);
    profPage();
};
void loginStudent()
{
    int x;
    do
    {

        char user[50];
        char password[50];
        printf("Pershendetje Student\n");
        printf("LOGIN:\n");
        printf("Ju lutem shkruani emrin: ");
        scanf("%s",user);
        printf("Ju lutem shkruani fjalekalimin: ");
        scanf("%s",password);
//    printf("your input: %s %s\n",user,password);

        x=checkStudent(user, password);
    }
    while(x==0);
    studentPage();
}
//---------------------------------------------------------------------------------------
int main(){

	int in;


	do{

        printMenu();//ktu fillon
        printf("Input: ");
        scanf("%d",&in);
		load_data();
        switch(in)
        {
        case 1:
            loginAdmin();
            break;
        case 2:
            loginProfesor();
            break;
        case 3:
            loginStudent();
            break;
        default:
            printf("Input i pasakte,Provo perseri\n");
            break;
        }
    }
    while(1);
    return 0;
}


