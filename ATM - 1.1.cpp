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
    //读取文件 
	struct People *pLogin;
    FILE *fp;
    int temp;
    if(file_size()==-1)
    {
                       printf("目前还没有任何数据，请注册\n");
                       Register();
    }
    int size=file_size()/sizeof(struct People); //求获取的结构体数量  
	pLogin=(struct People*)malloc(sizeof(struct People)*size);
    fp=fopen("PeoInfo.dat","rb");
	fread(pLogin,sizeof(*pLogin),size,fp);
	//printf("%s",(pLogin+1)->account);
    fclose(fp);
    int Step;
    int perNum; 
 	while(1) //主界面循环 
 	{
 		Step=Menu1();
		 if(Step==1) 
		 {
			 int k=size;
             size=Register() ;
			 if(size!=k) //重新读取 
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
	           	while(perNum!=-1)  //功能界面的循环 
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
		          		default: printf("输入有错"); break; 
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
 	printf("请输入要操作的数字:\n");
	printf("1.注册\n2.登录\n3.退出程序\n"); 
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
	 	printf("你的输入有误，请重新输入\n");
 		}
 	}
 }
 int Register()
 {
 	FILE *fp=NULL;
	struct People newp;
 	printf("请输入帐号\n");
 	scanf("%s",newp.account);
	printf("请输入你的名字\n");
 	scanf("%s",newp.name);
 	printf("请输入你的身份证帐号\n");
 	scanf("%s",newp.ID);
	printf("请输入你的密码\n");
	scanf("%s",newp.password);
	newp.balance=0.0; 
	if((fp=fopen("PeoInfo.dat","ab"))==NULL)
    {
        printf("打开文件失败");return 0;
    }
	else
    { 
    fwrite(&newp,sizeof(newp),1,fp);
    fclose(fp);
    printf("注册成功\n");
    int size=file_size()/sizeof(struct People);
    return size;
    }
 }
 
 int Login(int size,struct People *pLogin)
 {
      struct People p;
      int judge=0;
      printf("请输入账号：");
      scanf("%s",&p.account);
      for(int i=0;i<size;i++)
      {
              //printf("%s",(pLogin+1)->account); 
			  if(strcmp(p.account,(pLogin+i)->account)==0)
              {
              	  judge=1;
                  printf("请输入密码:");
                  scanf("%s",&p.password);
                  if(strcmp(p.password,(pLogin+i)->password)==0)
                  {
                      printf("登录成功！");
                      return i; //返回人物的号码数 
                      break;
                  }
                  else judge=0;
			  } 
      } 
      if(judge==0) 
              {
                printf("账号或者密码输入有误\n");
                return -1;
              }
              return -1;
      
 }
 
 int foution(int a,struct People *p)
 { 
      int fou;
      printf("1.查询余额 2.存款 3.注销 4.修改密码 5.转账 6.取款\n");
      scanf("%d",&fou);
      return fou;
 }
 
 void foution_yue(int a,struct People *p)
 {
      printf("你的帐号余额为：%f\n",(p+a)->balance);
 }
 
 void foution_password(int size,int a,struct People *p)
 {
     printf("请输入新的密码：");
     scanf("%s",(p+a)->password);
     printf("修改密码成功!");
     save(size,p);
 }
 void foution_ck(int size,int a,struct People *p)
 {
 	float money;
 	printf("请输入要存款的金额");
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
      printf("请输入对方的账号：");
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
	        printf("没有这个账号\n");
	        return; 
      }
      printf("对方的名字为:%s\n请输入要转账的金额：",(p+num)->name);
      scanf("%f",&money);
      if((p+a)->balance<money)
      {
      	//printf("%d",num);
      	printf("余额不足，请充值");
      	return; 
	  }
	  (p+a)->balance-=money;
      (p+num)->balance=(p+num)->balance+money;
      printf("转账成功！");
      save(size,p);
      return;
  }
void foution_quKuang(int size,int a,struct People *p)
{
	float money;
	printf("请输入你要取款的金额:");
	scanf("%f",&money);
	if((p+a)->balance<money)
      {
      	//printf("%d",num);
      	printf("余额不足，请充值");
      	return; 
	  }
	(p+a)->balance-=money;
	printf("取款成功！");
	save(size,p);
}
int file_size()  //获取文件的字节数 
{
	FILE *fp=fopen("PeoInfo.dat","r");
	if(!fp) return -1;
	fseek(fp,0L,SEEK_END);
	int size=ftell(fp);
	fclose(fp);
	return size;
}
void save(int size,struct People *p) //保存文件 
{
	 FILE *TEMP;
	 if((TEMP=fopen("tempinfo.dat","ab"))==NULL)
	 {
         printf("打开文件失败");
         return; 
     }
	 fwrite(p,sizeof(struct People),size,TEMP);
	 fclose(TEMP); 
	 remove("PeoInfo.dat");
	 rename("tempinfo.dat","PeoInfo.dat");
	 return;
}
