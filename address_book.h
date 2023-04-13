//
// Created by wyp on 2023/4/9.
//


#ifndef ADDRESS_BOOK_ADDRESS_BOOK_H
#define ADDRESS_BOOK_ADDRESS_BOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//为了保存联系人信息，定义一个联系人结构体
typedef struct{
    int age;
    char name[32];//尽量把相同类型的数据放在一起，减少内存对齐的补位
    char gender[8];
    char PhoneNum[16];
    char address[32];
}Contact;

#define INIT_CONTACT 2

typedef struct{
    Contact* contact;//避免魔幻数字的使用
    int capacity;//通讯录的容量
    int size;//记录当前通讯录中联系人的个数，当新增联系人的时候，新增联系人的数组小标刚好是size位置
}AddressBook;

int Welcome();
void Choice(AddressBook* address_book);
void Insert(AddressBook* address_book);
void Init(AddressBook* address_book);
void Display(AddressBook* addressBook);
void Delete(AddressBook* address_book);
void Find(AddressBook* address_book);
void Update(AddressBook* address_book);
void Clear(AddressBook* address_book);
void Sort(AddressBook* address_book);
void CheckCapacity(AddressBook* address_book);
void Destory(AddressBook* address_book);
void Load(AddressBook* address_book);
void Storage(AddressBook* address_book);

#endif //ADDRESS_BOOK_ADDRESS_BOOK_H