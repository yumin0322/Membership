//열거형 상수 : 성적주 메뉴 선택 사용
enum MAIN_MENU {END, READ, PRINT, EDIT, WRITE};
enum MAIN_MENU main_select;

//열거형 상수 : 성적관리 부 메뉴 선택 사용
enum EDIT_MENU {EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH};
enum EDIT_MENU edit_select;

#include "member_dll.h"

void read_member_data();   //member_data.txt 데이터 읽어오기
void write_member_data();  //member_data.txt 데이터 저장하기

char member_file_name[] = "membership.txt";

int main()
{
    int flag = 0;
    initialize_member();   //연결리스트 head 생성

    while(!flag && head != NULL){
        system("cls");
        puts("\t++++++++++++++++++++++++++++++++");
        puts("\t    헬스장 회원 관리 프로그램 \t");
        puts("\t++++++++++++++++++++++++++++++++");
        puts("\t1.회원 관리 프로그램 파일 로딩");
        puts("\t2.회원 관리 프로그램 현황보기");
        puts("\t3.회원 관리 관리하기");
        puts("\t4.회원 관리 파일에 저장하기");
        puts("\t0.종료");
        puts("\t--------------------------------");
        printf("\t>> ");
        scanf_s("%d",&main_select);
        getchar();

        switch(main_select){
            case READ:
                read_member_data();
                getchar();
                break;
            case PRINT:
                print_member_data();
                getchar();
                break;
            case EDIT:
                edit_member_data();
                break;
            case WRITE:
                write_member_data();
                getchar();
                break;
            case END:
                flag = 1;
                break;
            default:
                puts("\n\t다시선택 하세요.~");
                getchar();
                break;
        }//end of switch

    }//end of while

    return 0;
}

void read_member_data(){
    MEMBER_t* data = NULL;
    FILE* file = NULL;
    int flag = 0;
    int count = 0;

    printf("\n\t읽어올 회원 정보 파일이름 입력 >> ");
    scanf_s("%s",member_file_name, sizeof(member_file_name));
    getchar();

    file = fopen(member_file_name, "rt");

    if(file == NULL){
        printf("\n\t%s 파일을 읽지 못했습니다. \n",member_file_name);
        return;
    }

    while(!flag){
        data = (MEMBER_t *)calloc(1,sizeof(MEMBER_t));
        int result = fscanf(file,"%s %d %s %d %d %d %d %c",
               data->name,&data->id,data->gender,&data->height,&data->weight,
               &data->phone_number,&data->months,&data->grade);

        if(result == EOF){
           flag = 1;
           continue;
        }

        append_node(data);  //이중연결리스트 data 구조체 추가연결
        count++;

        printf("%s %d %s %d %d %d %d %c\n",
           data->name,data->id,data->gender,data->height,data->weight,
           data->phone_number,data->months,data->grade);
    }

    printf("\n\t%d 개의 데이터를 읽었습니다. ",count);
    fclose(file);
    getchar();

    return;
}


void write_member_data(){
    MEMBER_t* p = head;
    FILE* file = NULL;
    int count = 0;

    file = fopen(member_file_name, "wt");

    if(file == NULL){
        printf("\n\t%s 파일을 저장하지 못했습니다. \n",member_file_name);
        return;
    }

    while(p->next != NULL){
        p = p->next;
        int result = fprintf(file,"\t\t%s %d %s %d %d %d %d %d %d %lf %c\n",
               p->name,p->id,p->gender,p->height,p->weight,
               p->phone_number,p->months,p->grade);

        if(result == EOF){
            printf("\n\t%s 파일을 저장도중에 문제가 발생했습니다. ",member_file_name);
            break;
        }
        count++;
    }

    printf("\n\t%d 개의 데이터를 저장했습니다. ",count);
    fclose(file);
    getchar();

return;
}

//이전성적,다음성적,성적등록,성적수정,성적삭제,성적검색
void edit_member_data(){
   MEMBER_t* data = NULL;
   current = head->next;     //실제 데이타가 저장된 노드위치 저장
   int flag = 0;

   while(!flag && head != NULL){
        system("cls");
        puts("\n\t================================");
        puts("\t    회원 관리 \t");
        puts("\t================================");

        if(current != NULL){
            print_one_member_data(current);
        }

        puts("\t1.이전 회원");
        puts("\t2.다음 회원");
        puts("\t3.회원 등록");
        puts("\t4.회원 정보 수정");
        puts("\t5.회원 정보 삭제");
        puts("\t6.회원 검색");
        puts("\t0.돌아가기");
        printf("\t>> ");
        scanf_s("%d",&edit_select);
        getchar();

        //보여줄 node가 없어서, 이전, 다음, 수정, 삭제, 검색기능 불허가
        //등록, 돌아가기 기능 허가
        if(current == NULL){
            switch(edit_select){
                case PREV:
                case NEXT:
                case MODIFY:
                case DELETE:
                case SEARCH:
                    continue;
            }
        }

        switch(edit_select){
            case PREV:
                if(current->prev != NULL){
                    current = current->prev;
                }
                break;
            case NEXT:
                if(current->next != NULL){
                    current = current->next;
                }
                break;
            case INSERT:
                data = new_member_data();
                //1,2,3,4 삽입 작전 1:head 삽입, 2:마지막노드 삽입, 3: 처음노드 삽입, 4:중간노드삽입
                insert_member_data(data);
                getchar();
                break;
            case MODIFY:
                update_member_data(current);
                getchar();
                break;
            case DELETE:
                delete_member_data();
                break;
           case SEARCH:
                data = search_member_data();
                if(data != NULL){
                    current = data;
                }
                break;
           case EXIT:
                flag = 1;
                break;
            default:
                puts("다시선택 하세요.~");
                getchar();
                break;
        }//end of switch

   }//end of while

return;
}






