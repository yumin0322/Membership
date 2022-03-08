#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MEMBER{
    char name[20];
    int id;
    char gender[5];
    int height;
    int weight;
    int phone_number;
    int months;
    char grade;

    struct MEMBER* prev; //struct MEMBER ����Ű�� �����ͺ���(�տ� �ִ� ����ü)
    struct MEMBER* next; //struct MEMBER ����Ű�� �����ͺ���(�ڿ� �ִ� ����ü)
}MEMBER_t;

MEMBER_t* head = NULL;     //���߿��Ḯ��Ʈ ���۳������
MEMBER_t* current = NULL;  //����ȭ�鿡 ǥ�õǴ� �������

char make_grade(int months);
int check_id(int id);

//���� 1 head �����ϱ�
void initialize_member(){
    head = (MEMBER_t *)calloc(1,sizeof(MEMBER_t));
    if(head == NULL){
        puts("\t�������� STUDENT ����ü ���� ����");
        getchar();
    }
return;
}

//���� 2 ��� �߰��ϱ�(ó�� �߰��ϱ� , �������߰��ϱ�)
void append_node(MEMBER_t* data){
    MEMBER_t* p = head;

    //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
    }
    p->next = data;

    //�߰��� node���� �ٷ� �� node ����Ŵ.
    if(p != head){
        data->prev = p;
    }
return;
}

//���� 3 ��� ����ϱ�
void print_member_data(){
    MEMBER_t* p = head;

    if(p == NULL){
        puts("\t����� ����Ÿ�� �����ϴ�.");
        return;
    }

    puts("\t=====================================================================");
    puts("\t�̸�   ȸ����ȣ ����\tŰ\t������\t��ȭ��ȣ    ��ϰ�����\t���");
    puts("\t=====================================================================");

    while(p->next != NULL){
        p = p->next;
        printf("\t%s\t%d\t%s\t%3d\t%3d\t010%3d\t%3d\t%3c\n",
           p->name,p->id,p->gender,p->height,p->weight,
           p->phone_number,p->months,p->grade);
    }
return;
}

void print_one_member_data(MEMBER_t* current){
    if(current == NULL){
        puts("\t����� MEMBER ����ü �����ϴ�. ");
        getchar();
        return;
    }

    printf("\t%14s [%s] \n","�̸�",current->name);
    printf("\t%14s [%4d] \n","ȸ����ȣ",current->id);
    printf("\t%14s [%s] \n","����",current->gender);
    printf("\t%14s [%3d] \n","Ű",current->height);
    printf("\t%14s [%3d] \n","������",current->weight);
    printf("\t%14s [010%3d] \n","��ȭ��ȣ",current->phone_number);
    printf("\t%14s [%3d] \n","��ϰ�����",current->months);
    printf("\t%14s [%3c] \n","ȸ�����",current->grade);
    puts("\t================================");

return;
}

MEMBER_t* new_member_data(){
    MEMBER_t* data = (MEMBER_t *)calloc(1,sizeof(MEMBER_t));
    int flag_id = 0;

    if(data == NULL){
        puts("\t�������� MEMBER ����ü �Է� ����");
        getchar();
        return NULL;
    }

    printf("\t%14s : ","�̸�");
    scanf_s("%s",data->name,sizeof(data->name));

    //id �ߺ� üũ ���
    while(!flag_id){
        printf("\t%14s : ","ȸ����ȣ(1~300)");
        scanf_s("%d",&data->id,sizeof(data->id));

        if(check_id(data->id) != 0){
            puts("\t���� ȸ����ȣ�� �����մϴ�.");
            continue;
        }
        flag_id = 1;
    }

    printf("\t%14s :","����");
    scanf_s("%s",data->gender,sizeof(data->gender));
    data->height          = input_info("Ű");
    data->weight       = input_info("������");
    data->phone_number        = input_info("��ȭ��ȣ(010���� �Է�)");
    data->months  = input_info("��ϰ�����");
    data->grade = make_grade(current->months);

return data;
}

void update_member_data(MEMBER_t* current){

    if(current == NULL){
        puts("\t������ MEMBER ����ü �������� �ʽ��ϴ�.");
        getchar();
        return;
    }

    current->height          = input_info("���� Ű");
    current->weight       = input_info("���� ������");
    current->phone_number        = input_info("���� ��ȭ��ȣ(010���� �Է�)");
    current->months  = input_info("��ϰ�����");
    current->grade = make_grade(current->months);

return;
}

MEMBER_t* search_member_data(){
    MEMBER_t* p = head;
    MEMBER_t* data = NULL;
    int id = 0;

    printf("\t�˻��� ȸ����ȣ(1~300): ");
    scanf("%d",&id);

       //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            data = p;
            break;
        }
    }

    if(data == NULL){
        printf("\tȸ����ȣ[%4d] �� ���� ȸ����ȣ�Դϴ�. \n",id);
        getchar();
        getchar();
    }

return data;
}

void insert_member_data(MEMBER_t* data){
    //1:head->next null ó�� ��ġ ����
    if(head->next == NULL){
        head->next = data;
        return;
    }

    if(current->prev == NULL){            //3 ó����� ����
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next == NULL){      //2.������ ��� ����
        data->prev = current;
        current->next = data;
    }else if(current->next != NULL && current->prev != NULL){  //4.�߰���� ����
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("\t���Կ� ���� �߻��޽��ϴ�.");
        getchar();
        getchar();
    }

return;
}

void delete_member_data(){
  MEMBER_t* p = current;

  //current ��尡 �����Ǳ� ���� current �������, �������, NULL����
  if(current->next != NULL){
    current = current->next;
  }else if(current->next == NULL && current->prev != NULL){
    current = current->prev;
  }else{
    current = NULL;
  }

  if(p->next != NULL && p->prev == NULL){        //ó�����
    p->next->prev = NULL;
    head->next = p->next;
  }else if(p->next != NULL && p->prev != NULL){  //�߰����
    p->next->prev = p->prev;
    p->prev->next = p->next;
  }else if(p->next == NULL && p->prev != NULL){  //������ ���
    p->prev->next = NULL;
  }else{
    head->next = NULL;
  }

  free(p);
return;
}


int input_info(char *subject){
    int info = 0;
    int flag = 0;
    while(!flag){
        printf("\t%14s :",subject);
        scanf_s("%d",&info);
        if(info < 0 || info > 99999999){
            printf("\t%s ���� ����� �Է����ּ���.\n",subject);
            continue;
        }
        flag = 1;
    }//end of while

return info;
}

char make_grade(int months){
    char grade = 0;

    if(months >= 12){
        grade = 'S';
    }else if(months >= 10){
        grade = 'A';
    }else if(months >= 7){
        grade = 'B';
    }else if(months >= 5){
        grade = 'C';
    }else{
        grade = 'D';
    }

return grade;
}

int check_id(int id){
    int find_id = 0;
    MEMBER_t* p = head;

    //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            find_id = p->id;
            break;
        }
    }

return find_id;
}



