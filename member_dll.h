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

    struct MEMBER* prev; //struct MEMBER 가르키는 포인터변수(앞에 있는 구조체)
    struct MEMBER* next; //struct MEMBER 가르키느 포인터변수(뒤에 있는 구조체)
}MEMBER_t;

MEMBER_t* head = NULL;     //이중연결리스트 시작노드저장
MEMBER_t* current = NULL;  //현재화면에 표시되는 노드저장

char make_grade(int months);
int check_id(int id);

//패턴 1 head 생성하기
void initialize_member(){
    head = (MEMBER_t *)calloc(1,sizeof(MEMBER_t));
    if(head == NULL){
        puts("\t힙영역에 STUDENT 구조체 생성 실패");
        getchar();
    }
return;
}

//패턴 2 노드 추가하기(처음 추가하기 , 마지막추가하기)
void append_node(MEMBER_t* data){
    MEMBER_t* p = head;

    //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
    }
    p->next = data;

    //추가된 node에서 바로 앞 node 가르킴.
    if(p != head){
        data->prev = p;
    }
return;
}

//패턴 3 노드 출력하기
void print_member_data(){
    MEMBER_t* p = head;

    if(p == NULL){
        puts("\t출력할 데이타가 없습니다.");
        return;
    }

    puts("\t=====================================================================");
    puts("\t이름   회원번호 성별\t키\t몸무게\t전화번호    등록개월수\t등급");
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
        puts("\t출력할 MEMBER 구조체 없습니다. ");
        getchar();
        return;
    }

    printf("\t%14s [%s] \n","이름",current->name);
    printf("\t%14s [%4d] \n","회원번호",current->id);
    printf("\t%14s [%s] \n","성별",current->gender);
    printf("\t%14s [%3d] \n","키",current->height);
    printf("\t%14s [%3d] \n","몸무게",current->weight);
    printf("\t%14s [010%3d] \n","전화번호",current->phone_number);
    printf("\t%14s [%3d] \n","등록개월수",current->months);
    printf("\t%14s [%3c] \n","회원등급",current->grade);
    puts("\t================================");

return;
}

MEMBER_t* new_member_data(){
    MEMBER_t* data = (MEMBER_t *)calloc(1,sizeof(MEMBER_t));
    int flag_id = 0;

    if(data == NULL){
        puts("\t힙영역에 MEMBER 구조체 입력 실패");
        getchar();
        return NULL;
    }

    printf("\t%14s : ","이름");
    scanf_s("%s",data->name,sizeof(data->name));

    //id 중복 체크 기능
    while(!flag_id){
        printf("\t%14s : ","회원번호(1~300)");
        scanf_s("%d",&data->id,sizeof(data->id));

        if(check_id(data->id) != 0){
            puts("\t기존 회원번호이 존재합니다.");
            continue;
        }
        flag_id = 1;
    }

    printf("\t%14s :","성별");
    scanf_s("%s",data->gender,sizeof(data->gender));
    data->height          = input_info("키");
    data->weight       = input_info("몸무게");
    data->phone_number        = input_info("전화번호(010제외 입력)");
    data->months  = input_info("등록개월수");
    data->grade = make_grade(current->months);

return data;
}

void update_member_data(MEMBER_t* current){

    if(current == NULL){
        puts("\t수정할 MEMBER 구조체 존재하지 않습니다.");
        getchar();
        return;
    }

    current->height          = input_info("수정 키");
    current->weight       = input_info("수정 몸무게");
    current->phone_number        = input_info("수정 전화번호(010제외 입력)");
    current->months  = input_info("등록개월수");
    current->grade = make_grade(current->months);

return;
}

MEMBER_t* search_member_data(){
    MEMBER_t* p = head;
    MEMBER_t* data = NULL;
    int id = 0;

    printf("\t검색할 회원번호(1~300): ");
    scanf("%d",&id);

       //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            data = p;
            break;
        }
    }

    if(data == NULL){
        printf("\t회원번호[%4d] 는 없는 회원번호입니다. \n",id);
        getchar();
        getchar();
    }

return data;
}

void insert_member_data(MEMBER_t* data){
    //1:head->next null 처음 위치 삽입
    if(head->next == NULL){
        head->next = data;
        return;
    }

    if(current->prev == NULL){            //3 처음노드 삽입
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next == NULL){      //2.마지막 노드 삽입
        data->prev = current;
        current->next = data;
    }else if(current->next != NULL && current->prev != NULL){  //4.중간노드 삽입
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("\t삽입에 문제 발생햇습니다.");
        getchar();
        getchar();
    }

return;
}

void delete_member_data(){
  MEMBER_t* p = current;

  //current 노드가 삭제되기 때문 current 이전노드, 다음노드, NULL변경
  if(current->next != NULL){
    current = current->next;
  }else if(current->next == NULL && current->prev != NULL){
    current = current->prev;
  }else{
    current = NULL;
  }

  if(p->next != NULL && p->prev == NULL){        //처음노드
    p->next->prev = NULL;
    head->next = p->next;
  }else if(p->next != NULL && p->prev != NULL){  //중간노드
    p->next->prev = p->prev;
    p->prev->next = p->next;
  }else if(p->next == NULL && p->prev != NULL){  //마지막 노드
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
            printf("\t%s 값을 제대로 입력해주세요.\n",subject);
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

    //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
        if(p->id == id){
            find_id = p->id;
            break;
        }
    }

return find_id;
}



