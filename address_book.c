//
// Created by wyp on 2023/4/9.
//
#include "address_book.h"

int Welcome() {
    system("cls");
    printf("*************  通讯录 **************\n");
    printf("*********0.退出      1.添加*********\n");
    printf("*********2.删除      3.查找*********\n");
    printf("*********4.修改      5.显示*********\n");
    printf("*********6.清空      7.排序*********\n");
    printf("************************************\n");
    int input;
    printf("请输入你的选择：");
    scanf("%d", &input);
    getchar();//取出最后按回车的换行
    return input;
}

void Init(AddressBook* address_book){
    address_book->contact=(Contact*)malloc(sizeof(Contact)*INIT_CONTACT);
    address_book->size=0;
    address_book->capacity=INIT_CONTACT;
    /*
    strcpy(address_book->contact[address_book->size].name,"张三");
    strcpy(address_book->contact[address_book->size].gender,"男");
    address_book->contact[address_book->size].age=20;
    strcpy(address_book->contact[address_book->size].PhoneNum,"13299998888");
    strcpy(address_book->contact[address_book->size].address,"陕科大");
    ++address_book->size;
    strcpy(address_book->contact[address_book->size].name,"李四");
    strcpy(address_book->contact[address_book->size].gender,"女");
    address_book->contact[address_book->size].age=18;
    strcpy(address_book->contact[address_book->size].PhoneNum,"14244445555");
    strcpy(address_book->contact[address_book->size].address,"西医");
    ++address_book->size;
    strcpy(address_book->contact[address_book->size].name,"王五");
    strcpy(address_book->contact[address_book->size].gender,"男");
    address_book->contact[address_book->size].age=30;
    strcpy(address_book->contact[address_book->size].PhoneNum,"19866667777");
    strcpy(address_book->contact[address_book->size].address,"西工院");
    ++address_book->size;
     */
    //在初始化结构完毕后，开始加载通讯录内容
    Load(address_book);
}

void CheckCapacity(AddressBook* address_book){
    //存储满就要扩容
    if(address_book->size==address_book->capacity){
        //如果容量在1024以内则翻倍增长，在1024以上则线性增长
        int capacity=address_book->capacity>=1024?address_book->capacity+1024*sizeof (Contact):address_book->capacity*sizeof(Contact)*2;
        //因为扩容有可能会失败，失败会返回NULL
        Contact* contact=(Contact*)realloc(address_book->contact,capacity);
        assert(contact!=NULL);//等于NULL就表示扩容失败了，失败了就退出
        address_book->contact=contact;//扩容成功再赋值
        address_book->capacity=capacity;//设置新容量
        printf("扩容成功！\n");
    }
}

void Insert(AddressBook* address_book){
    CheckCapacity(address_book);
    if(address_book->size==address_book->capacity){
        printf("通讯录已满，无法继续添加联系人！输入回车继续运行！\n");
        getchar();
        return ;
    }
    //新增联系人
    printf("请输入联系人姓名：");
    scanf("%s",address_book->contact[address_book->size].name);//address_book->size既是联系人数量，又是新增位置下标
    printf("请输入联系人性别：");
    scanf("%s",address_book->contact[address_book->size].gender);
    printf("请输入联系人年龄：");
    scanf("%d",&address_book->contact[address_book->size].age);
    printf("请输入联系人电话：");
    scanf("%s",address_book->contact[address_book->size].PhoneNum);
    printf("请输入联系人地址：");
    scanf("%s",address_book->contact[address_book->size].address);
    getchar();//这个getchar()是为了把输入的最后回车换行取出来
    ++address_book->size;//新增联系人完毕后一定要进行size的++
    system("cls");
    printf("联系人保存完毕！\n");
    printf("输入回车继续运行！\n");
    getchar();
}

void Display(AddressBook* address_book){
    system("cls");
    printf("%-10s\t%-4s\t%-4s\t%-11s\t%-32s\n","姓名","性别","年龄","电话","地址");
    for(int i=0;i<address_book->size;++i){
        printf("%-10s\t%-4s\t%-4d\t%-11s\t%-32s\n"
                ,address_book->contact[i].name
                ,address_book->contact[i].gender
                ,address_book->contact[i].age
                ,address_book->contact[i].PhoneNum
                ,address_book->contact[i].address);
    }
    printf("输入回车继续!\n");
    getchar();
}

int find_by_name(AddressBook* address_book,char* name){
    int i;
    for(i=0;i<address_book->size;++i){
        if(strcmp(name,address_book->contact[i].name)==0){
            break;
        }
    }
    if(i==address_book->size){
        return -1;//表示没找到
    }
    return i;
}

void Delete(AddressBook* address_book){
    //通过姓名来删除联系人
    char name[32]={0};
    printf("请输入要删除的联系人：");
    scanf("%s",name);
    getchar();//将输入的回车换行取出

    int pos= find_by_name(address_book,name);
    if(pos==-1){
        printf("没有找到要删除的联系人！输入回车继续！\n");
        getchar();
        return;
    }
    for(int j=pos+1;j<address_book->size;++j){
        address_book->contact[j-1]=address_book->contact[j];
    }
    --address_book->size;
    printf("删除联系人完成！\n输入回车继续运行!\n");
    getchar();//等待输入回车
}

void Find(AddressBook* address_book){
    //通过姓名查找联系人
    char name[32]={0};
    printf("请输入联系人姓名：");
    scanf("%s",name);
    getchar();//将输入最后的回车换行取出来

    int pos= find_by_name(address_book,name);
    if(pos==-1){
        printf("没有找到要查找的联系人！输入回车继续运行！\n");
        getchar();
        return;
    }
    printf("%-10s\t%-4s\t%-4s\t%-11s\t%-32s\n","姓名","性别","年龄","电话","地址");
    printf("%-10s\t%-4s\t%-4d\t%-11s\t%-32s\n"
            ,address_book->contact[pos].name
            ,address_book->contact[pos].gender
            ,address_book->contact[pos].age
            ,address_book->contact[pos].PhoneNum
            ,address_book->contact[pos].address);
    printf("输入回车继续运行！\n");
    getchar();
    system("pause");
}

void Update(AddressBook* address_book){
    system("cls");
    //通过姓名来查找联系人
    char name[32]={0};
    printf("请输入要修改的联系人姓名：");
    scanf("%s",name);
    getchar();

    int pos= find_by_name(address_book,name);
    if(pos==-1){
        printf("没有找到要查找的联系人！输入回车继续运行！\n");
        getchar();
        system("pause");
        return;
    }

    enum ContactInformation{
        EXIT,
        NAME,
        GENDER,
        AGE,
        PHONENUM,
        ADDRESS,
    };

    while(1){
        printf("************ 修改联系人信息 ************\n");
        printf("*******1.姓名              2.性别******\n");
        printf("*******3.年龄              4.电话******\n");
        printf("*******5.地址              0.退出******\n");
        int input;
        printf("请输入你的选择：");
        scanf("%d",&input);
        switch(input){
            case EXIT:
                getchar();
                printf("修改联系人完成！输入回车继续！\n");
                getchar();
                return;
            case NAME:
                printf("请输入联系人姓名：");
                scanf("%s",address_book->contact[pos].name);
                break;
            case GENDER:
                printf("请输入联系人性别：");
                scanf("%s",address_book->contact[pos].gender);
                break;
            case AGE:
                printf("请输入联系人年龄：");
                scanf("%d",&address_book->contact[pos].age);
                break;
            case PHONENUM:
                printf("请输入联系人电话：");
                scanf("%s",address_book->contact[pos].PhoneNum);
                break;
            case ADDRESS:
                printf("请输入联系人地址：");
                scanf("%s",address_book->contact[pos].address);
                break;
            default:
                printf("请输入正确选项！\n");
                break;
        }
        system("cls");
    }
}

void Clear(AddressBook* address_book){
    address_book->size=0;
    printf("清理通讯录完成！输入回车继续！\n");
    getchar();
}

int cmp_by_name(const void* e1,const void* e2){
    Contact* p1=(Contact*)e1;
    Contact* p2=(Contact*)e2;
    return strcmp(p1->name,p2->name);
}

int cmp_by_gender(const void* e1,const void* e2){
    Contact* p1=(Contact*)e1;
    Contact* p2=(Contact*)e2;
    return strcmp(p1->gender,p2->gender);
}

int cmp_by_age(const void* e1,const void* e2){
    Contact* p1=(Contact*)e1;
    Contact* p2=(Contact*)e2;
    return p1->age-p2->age;
}

int cmp_by_phonenum(const void* e1,const void* e2){
    Contact* p1=(Contact*)e1;
    Contact* p2=(Contact*)e2;
    return strcmp(p1->PhoneNum,p2->PhoneNum);
}

int cmp_by_address(const void* e1,const void* e2){
    Contact* p1=(Contact*)e1;
    Contact* p2=(Contact*)e2;
    return strcmp(p1->address,p2->address);
}

void Sort(AddressBook* address_book){
    system("cls");
    enum ContactInformation{
        EXIT,
        NAME,
        GENDER,
        AGE,
        PHONENUM,
        ADDRESS,
    };
    printf("************ 排序联系人信息 ************\n");
    printf("*******1.姓名              2.性别******\n");
    printf("*******3.年龄              4.电话******\n");
    printf("*******5.地址                   ******\n");
    int input;
    printf("请输入要排序的方式：");
    scanf("%d",&input);
    getchar();
    switch(input){
        case NAME:
            qsort(address_book->contact,address_book->size,sizeof(Contact),cmp_by_name);
            Display(address_book);
            break;
        case GENDER:
            qsort(address_book->contact,address_book->size,sizeof(Contact),cmp_by_gender);
            Display(address_book);
            break;
        case AGE:
            qsort(address_book->contact,address_book->size,sizeof(Contact),cmp_by_age);
            Display(address_book);
            break;
        case PHONENUM:
            qsort(address_book->contact,address_book->size,sizeof(Contact),cmp_by_phonenum);
            Display(address_book);
            break;
        case ADDRESS:
            qsort(address_book->contact,address_book->size,sizeof(Contact),cmp_by_address);
            Display(address_book);
            break;
        default:
            printf("请输入正确选项!");
            break;
    }
    printf("排序完成，输入回车继续\n");
    getchar();
}

void Choice(AddressBook* address_book){
    enum EnumMailList{
        EXIT,
        INSERT,
        DELETE,
        FIND,
        UPDATE,
        DISPLAY,
        CLEAR,
        SORT
    };
    while (1) {

        int choice = Welcome();
        switch (choice) {
            case EXIT:
                printf("感谢使用通讯录！再见！\n");
                //每次退出程序前，持久化通讯录内容
                Storage(address_book);
                Destory(address_book);
                system("pause");
                exit(0);//退出程序运行，参数0跟return 0是一个意思
            case INSERT:
                Insert(address_book);
                //每次插入联系人信息后，持久化通讯录内容
                Storage(address_book);
                break;
            case DELETE:
                Delete(address_book);
                //每次删除联系人后，持久化通讯录内容
                Storage(address_book);
                break;
            case FIND:
                Find(address_book);
                break;
            case UPDATE:
                //每次修改联系人后，持久化通讯录内容
                Storage(address_book);
                Update(address_book);
                break;
            case DISPLAY:
                Display(address_book);
                break;
            case CLEAR:
                //每次清空联系人后，持久化通讯录内容
                Storage(address_book);
                Clear(address_book);
                break;
            case SORT:
                Sort(address_book);
                break;
            default:
                system("cls");
                printf("请输入正确选择！\n");
                break;
        }
    }
}

void Destory(AddressBook* address_book){
    free(address_book->contact);
    address_book->size=0;
    address_book->contact=NULL;
}

//数据如何存储，决定了加载的时候如何解析
void Load(AddressBook* address_book){
    //打开文件，从文件中读取数据，将数据进行解析逐个填充到通讯录中
    FILE* fp=fopen("./address_book.txt","r");
    if(fp == NULL){
        return;
    }
    while(1){
        CheckCapacity(address_book);//进行空间检测，空间不够了就要扩容，然后再写入
        int ret = fscanf(fp,"%s%s%d%s%s"
               ,address_book->contact[address_book->size].name
               ,address_book->contact[address_book->size].gender
               ,&address_book->contact[address_book->size].age
               ,address_book->contact[address_book->size].PhoneNum
               ,address_book->contact[address_book->size].address);
        if(ret == EOF){
            break;
        }
        address_book->size+=1;
    }
    fclose(fp);
    printf("加载通讯录完毕\n");
}

void Storage(AddressBook* address_book){
    //打开文件，将通讯录内容写入到文件中持久化存储,在用户角度便于观察，因此以文本进行存储
    FILE *fp=fopen("./address_book.txt","w");
    if(fp == NULL){
        perror("fopen error");
        return;
    }
    for(int i=0;i<address_book->size;++i){
        fprintf(fp,"%-10s\t%-4s\t%-4d\t%-11s\t%-32s\n"
                ,address_book->contact[i].name
                ,address_book->contact[i].gender
                ,address_book->contact[i].age
                ,address_book->contact[i].PhoneNum
                ,address_book->contact[i].address);
    }
    fclose(fp);
    return;
}