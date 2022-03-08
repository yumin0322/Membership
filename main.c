//������ ��� : ������ �޴� ���� ���
enum MAIN_MENU {END, READ, PRINT, EDIT, WRITE};
enum MAIN_MENU main_select;

//������ ��� : �������� �� �޴� ���� ���
enum EDIT_MENU {EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH};
enum EDIT_MENU edit_select;

#include "member_dll.h"

void read_member_data();   //member_data.txt ������ �о����
void write_member_data();  //member_data.txt ������ �����ϱ�

char member_file_name[] = "membership.txt";

int main()
{
    int flag = 0;
    initialize_member();   //���Ḯ��Ʈ head ����

    while(!flag && head != NULL){
        system("cls");
        puts("\t++++++++++++++++++++++++++++++++");
        puts("\t    �ｺ�� ȸ�� ���� ���α׷� \t");
        puts("\t++++++++++++++++++++++++++++++++");
        puts("\t1.ȸ�� ���� ���α׷� ���� �ε�");
        puts("\t2.ȸ�� ���� ���α׷� ��Ȳ����");
        puts("\t3.ȸ�� ���� �����ϱ�");
        puts("\t4.ȸ�� ���� ���Ͽ� �����ϱ�");
        puts("\t0.����");
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
                puts("\n\t�ٽü��� �ϼ���.~");
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

    printf("\n\t�о�� ȸ�� ���� �����̸� �Է� >> ");
    scanf_s("%s",member_file_name, sizeof(member_file_name));
    getchar();

    file = fopen(member_file_name, "rt");

    if(file == NULL){
        printf("\n\t%s ������ ���� ���߽��ϴ�. \n",member_file_name);
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

        append_node(data);  //���߿��Ḯ��Ʈ data ����ü �߰�����
        count++;

        printf("%s %d %s %d %d %d %d %c\n",
           data->name,data->id,data->gender,data->height,data->weight,
           data->phone_number,data->months,data->grade);
    }

    printf("\n\t%d ���� �����͸� �о����ϴ�. ",count);
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
        printf("\n\t%s ������ �������� ���߽��ϴ�. \n",member_file_name);
        return;
    }

    while(p->next != NULL){
        p = p->next;
        int result = fprintf(file,"\t\t%s %d %s %d %d %d %d %d %d %lf %c\n",
               p->name,p->id,p->gender,p->height,p->weight,
               p->phone_number,p->months,p->grade);

        if(result == EOF){
            printf("\n\t%s ������ ���嵵�߿� ������ �߻��߽��ϴ�. ",member_file_name);
            break;
        }
        count++;
    }

    printf("\n\t%d ���� �����͸� �����߽��ϴ�. ",count);
    fclose(file);
    getchar();

return;
}

//��������,��������,�������,��������,��������,�����˻�
void edit_member_data(){
   MEMBER_t* data = NULL;
   current = head->next;     //���� ����Ÿ�� ����� �����ġ ����
   int flag = 0;

   while(!flag && head != NULL){
        system("cls");
        puts("\n\t================================");
        puts("\t    ȸ�� ���� \t");
        puts("\t================================");

        if(current != NULL){
            print_one_member_data(current);
        }

        puts("\t1.���� ȸ��");
        puts("\t2.���� ȸ��");
        puts("\t3.ȸ�� ���");
        puts("\t4.ȸ�� ���� ����");
        puts("\t5.ȸ�� ���� ����");
        puts("\t6.ȸ�� �˻�");
        puts("\t0.���ư���");
        printf("\t>> ");
        scanf_s("%d",&edit_select);
        getchar();

        //������ node�� ���, ����, ����, ����, ����, �˻���� ���㰡
        //���, ���ư��� ��� �㰡
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
                //1,2,3,4 ���� ���� 1:head ����, 2:��������� ����, 3: ó����� ����, 4:�߰�������
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
                puts("�ٽü��� �ϼ���.~");
                getchar();
                break;
        }//end of switch

   }//end of while

return;
}






