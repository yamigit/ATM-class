 #include<stdio.h>
 #include<stdlib.h>
 #include<malloc.h>
 #include<string.h>
 int Menu1();
 int Register();
 int foution(int,struct People *);
 void foution_yue(int,struct People *);
 void foution_password(int,int,struct People *);
 int Login(int,struct People *);
 void foution_ck(int,int,struct People *); 
 void foution_swap(int,int,struct People *);
 void foution_quKuang(int,int,struct People *);
 int file_size();
 void save(int,struct People *);
 struct People
 {
 	char name[5];
 	char ID[20];
 	float balance;
 	char password[20];
 	char account[10];
 };
 int main()
 {
    //��ȡ�ļ� 
	struct People *pLogin;
    FILE *fp;
    int temp;
    if(file_size()==-1)
    {
                       printf("Ŀǰ��û���κ����ݣ���ע��\n");
                       Register();
    }
    int size=file_size()/sizeof(struct People); //���ȡ�Ľṹ������  
	pLogin=(struct People*)malloc(sizeof(struct People)*size);
    fp=fopen("PeoInfo.dat","rb");
	fread(pLogin,sizeof(*pLogin),size,fp);
	//printf("%s",(pLogin+1)->account);
    fclose(fp);
    int Step;
    int perNum; 
 	while(1) //������ѭ�� 
 	{
 		Step=Menu1();
		 if(Step==1) 
		 {
			 int k=size;
             size=Register() ;
			 if(size!=k) //���¶�ȡ 
             { 
                 free(pLogin);
                 pLogin=(struct People*)malloc(sizeof(struct People)*size);
                 fp=fopen("PeoInfo.dat","rb");
                 fread(pLogin,sizeof(*pLogin),size,fp);
                 //printf("%s",(pLogin+1)->account);
                 fclose(fp);
             } 
		 }
		 else if(Step==2)
		 {
           perNum=Login(size,pLogin);
			if(perNum!=-1) 
	           {
	           	while(perNum!=-1)  //���ܽ����ѭ�� 
	           	{
				   temp=foution(perNum,pLogin);
				   switch(temp)
				   {
				   		case 1:foution_yue(perNum,pLogin);break;
		        		case 2:foution_ck(size,perNum,pLogin);break;
		          		case 3:perNum=Login(size,pLogin);break;
		          		case 4:foution_password(size,perNum,pLogin); break;
		          		case 5:foution_swap(size,perNum,pLogin); break;
		          		case 6:foution_quKuang(size,perNum,pLogin);break;
		          		default: printf("�����д�"); break; 
				   }
			  }
			   }
		
		 }
		 else if(Step==3) 
		 {
			break;
		 }
		 
 	}
 	free(pLogin);
    return 0;
 }
 
 int Menu1()
 {
 	int step;
 	printf("������Ҫ����������:\n");
	printf("1.ע��\n2.��¼\n3.�˳�����\n"); 
	while(1)
	{
		scanf("%d",&step);
 		if(step==1||step==2||step==3) 
		 {
			 return step;
			 break;
		 }
 		else 
	 	{
	 	printf("���������������������\n");
 		}
 	}
 }
 int Register()
 {
 	FILE *fp=NULL;
	struct People newp;
 	printf("�������ʺ�\n");
 	scanf("%s",newp.account);
	printf("�������������\n");
 	scanf("%s",newp.name);
 	printf("������������֤�ʺ�\n");
 	scanf("%s",newp.ID);
	printf("�������������\n");
	scanf("%s",newp.password);
	newp.balance=0.0; 
	if((fp=fopen("PeoInfo.dat","ab"))==NULL)
    {
        printf("���ļ�ʧ��");return 0;
    }
	else
    { 
    fwrite(&newp,sizeof(newp),1,fp);
    fclose(fp);
    printf("ע��ɹ�\n");
    int size=file_size()/sizeof(struct People);
    return size;
    }
 }
 
 int Login(int size,struct People *pLogin)
 {
      struct People p;
      int judge=0;
      printf("�������˺ţ�");
      scanf("%s",&p.account);
      for(int i=0;i<size;i++)
      {
              //printf("%s",(pLogin+1)->account); 
			  if(strcmp(p.account,(pLogin+i)->account)==0)
              {
              	  judge=1;
                  printf("����������:");
                  scanf("%s",&p.password);
                  if(strcmp(p.password,(pLogin+i)->password)==0)
                  {
                      printf("��¼�ɹ���");
                      return i; //��������ĺ����� 
                      break;
                  }
                  else judge=0;
			  } 
      } 
      if(judge==0) 
              {
                printf("�˺Ż���������������\n");
                return -1;
              }
              return -1;
      
 }
 
 int foution(int a,struct People *p)
 { 
      int fou;
      printf("1.��ѯ��� 2.��� 3.ע�� 4.�޸����� 5.ת�� 6.ȡ��\n");
      scanf("%d",&fou);
      return fou;
 }
 
 void foution_yue(int a,struct People *p)
 {
      printf("����ʺ����Ϊ��%f\n",(p+a)->balance);
 }
 
 void foution_password(int size,int a,struct People *p)
 {
     printf("�������µ����룺");
     scanf("%s",(p+a)->password);
     printf("�޸�����ɹ�!");
     save(size,p);
 }
 void foution_ck(int size,int a,struct People *p)
 {
 	float money;
 	printf("������Ҫ���Ľ��");
 	scanf("%f",&money);
 	//printf("%f",(p+a)->balance);
 	(p+a)->balance=(p+a)->balance+money;
 	//printf("%f",(p+a)->balance);
 	save(size,p);
 }
 void foution_swap(int size,int a,struct People *p)
 {
      struct People newp;
      int num=-1;
      int judge=0;
      float money;                 
      printf("������Է����˺ţ�");
      scanf("%s",&newp.account);
      for(int i=0;i<size;i++)
      {
              if(strcmp(newp.account,(p+i)->account)==0) 
              {
                  num=i;
                  judge=1;
                  break;
              }
      }
      if(judge==0) 
      {
	        printf("û������˺�\n");
	        return; 
      }
      printf("�Է�������Ϊ:%s\n������Ҫת�˵Ľ�",(p+num)->name);
      scanf("%f",&money);
      if((p+a)->balance<money)
      {
      	//printf("%d",num);
      	printf("���㣬���ֵ");
      	return; 
	  }
	  (p+a)->balance-=money;
      (p+num)->balance=(p+num)->balance+money;
      printf("ת�˳ɹ���");
      save(size,p);
      return;
  }
void foution_quKuang(int size,int a,struct People *p)
{
	float money;
	printf("��������Ҫȡ��Ľ��:");
	scanf("%f",&money);
	if((p+a)->balance<money)
      {
      	//printf("%d",num);
      	printf("���㣬���ֵ");
      	return; 
	  }
	(p+a)->balance-=money;
	printf("ȡ��ɹ���");
	save(size,p);
}
int file_size()  //��ȡ�ļ����ֽ��� 
{
	FILE *fp=fopen("PeoInfo.dat","r");
	if(!fp) return -1;
	fseek(fp,0L,SEEK_END);
	int size=ftell(fp);
	fclose(fp);
	return size;
}
void save(int size,struct People *p) //�����ļ� 
{
	 FILE *TEMP;
	 if((TEMP=fopen("tempinfo.dat","ab"))==NULL)
	 {
         printf("���ļ�ʧ��");
         return; 
     }
	 fwrite(p,sizeof(struct People),size,TEMP);
	 fclose(TEMP); 
	 remove("PeoInfo.dat");
	 rename("tempinfo.dat","PeoInfo.dat");
	 return;
}
