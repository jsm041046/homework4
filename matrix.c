#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command; //char형 변수 command 선언
    printf("[----- 전설민  2021041046 -----]\n"); //이름 학번 출력

    int row, col; //열 수, 행 수 저장용 int형 변수 row col 선언
    srand(time(NULL)); //랜덤 값 시드를 현재 시간에 따라 변경

    printf("Input row and col : "); //행 수와 열 수 입력 안내
    scanf("%d %d", &row, &col); //행 수와 열 수 입력
    int** matrix_a = create_matrix(row, col); //행렬 A 생성
    int** matrix_b = create_matrix(row, col); //행렬 B 생성
    int** matrix_a_t = create_matrix(col, row); //행렬 A_T 생성

    printf("Matrix Created.\n"); //안내

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //행렬 A나 B가 생성 실패 시 프로그램 비정상 종료

    do{ //루프
        //실행 가능한 명령어 안내
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = "); //입력 안내
        scanf(" %c", &command); //입력값 받음

        switch(command) { //입력 값에 따른 분기
        case 'z': case 'Z': //입력값이 Z인 경우
            printf("Matrix Initialized\n"); //안내
            fill_data(matrix_a, row, col); //행렬 A 랜덤값 입력
            fill_data(matrix_b, row, col); //행렬 B 랜덤값 입력
            break; //case문 종료
        case 'p': case 'P': //입력값이 P인 경우
            printf("Print matrix\n"); //안내
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //행렬 A 출력
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //행렬 B 출력
            break; //case문 종료
        case 'a': case 'A': //입력값이 A인 경우
            printf("Add two matrices\n"); //안내
            addition_matrix(matrix_a, matrix_b, row, col); //행렬 A와 B를 더해서 출력
            break; //case문 종료
        case 's': case 'S': //입력값이 S인 경우
            printf("Subtract two matrices \n"); //안내
            subtraction_matrix(matrix_a, matrix_b, row, col); //행렬 A와 B를 빼서 출력
            break; //case문 종료
        case 't': case 'T': //입력값이 T인 경우
            printf("Transpose matrix_a \n"); //안내
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //행렬 A를 전치해서 A_T에 대입
            print_matrix(matrix_a_t, col, row); //행렬 A_T를 출력
            break; //case문 종료
        case 'm': case 'M': //입력값이 M인 경우
            printf("Multiply matrix_a with transposed matrix_a \n"); //안내
            transpose_matrix(matrix_a, matrix_a_t, col, row); //행렬 A를 전치해서 A_T에 대입
            multiply_matrix(matrix_a, matrix_a_t, row, col); //행렬 A * A_T를 출력
            break; //case문 종료
        case 'q': case 'Q': //입력값이 Q인 경우
            printf("Free all matrixes..\n"); //안내
            free_matrix(matrix_a_t, col, row); //행렬 A_T에 사용되는 메모리를 할당 해제
            free_matrix(matrix_a, row, col); //행렬 A에 사용되는 메모리를 할당 해제
            free_matrix(matrix_b, row, col); //행렬 B에 사용되는 메모리를 할당 해제
            break; //case문 종료
        default: //입력값이 어느 것에도 해당되지 않는 경우
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break; //case문 종료
        }

    }while(command != 'q' && command != 'Q'); //입력 명령어가 Q인 경우 루프를 빠져나옴

    return 1; //프로그램 정상 종료
}

int** create_matrix(int row, int col)
{
    if(row <= 0 || col <= 0) { //row 및 col 값이 0이하라서 행렬 생성이 불가능할 경우
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix; //이중포인터 matrix 선언
    //matrix 이중포인터로 int[row][col]형태의 이중배열 할당
    matrix = (int**)malloc(sizeof(int*) * row); //행 수에 따른 포인터 배열 할당
    if(matrix == NULL) //matrix 이중 포인터의 할당이 실패할 경우
    {
        printf("allocation failed!\n");
        return NULL;
    } else {
        for(int i = 0;i < row;i++)
        {
            matrix[i] = (int*)malloc(sizeof(int) * col); //행 별 배열 할당
            if(matrix[i] == NULL) //matrix의 행 중 하나라도 할당 실패할 경우
            {
                printf("allocation failed!\n");
                return NULL;
            }
        }
    }
    
    return matrix; //할당 된 포인터 반환
}

void print_matrix(int** matrix, int row, int col)
{
    if(matrix == NULL) //matrix 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix[i] == NULL) //matrix 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return;
        }
    }
    //행렬 대괄호 모서리 윗부분
    printf("┌\t");
    for(int i = 0;i < col;i++)
        printf("\t");
    printf("┐\n");

    //행렬 출력
    for(int i = 0;i < row;i++)
    {
        printf("|\t");
        for(int j = 0;j < col;j++)
        {
            printf("%d\t",matrix[i][j]);
        }
        printf("|\n");
    }

    //행렬 대괄호 모서리 아랫부분
    printf("└\t");
    for(int i = 0;i < col;i++)
        printf("\t");
    printf("┘\n");
}


int free_matrix(int** matrix, int row, int col)
{
    if(matrix == NULL) //matrix 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix[i] == NULL) //matrix 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    for(int i = 0;i < row;i++)
    {
        free(matrix[i]); //해당 행렬의 행 별 메모리 할당 해제
    }

    free(matrix); //해당 행렬 할당 해제

    return 1; //정상 처리 완료 출력
}


int fill_data(int** matrix, int row, int col)
{
    if(matrix == NULL) //matrix 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix[i] == NULL) //matrix 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j<col;j++)
            matrix[i][j] = rand() % 20; //모든 행렬의 원소에 0~19까지의 값 대입
        
    return 1; //정상 처리 완료 출력
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(matrix_a == NULL) //matrix_a 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_a[i] == NULL) //matrix_a 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_b == NULL) //matrix_b 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_b[i] == NULL) //matrix_b 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    int** rmatrix; //결과값을 담을 행렬
    rmatrix = (int**)malloc(sizeof(int*) * row); //행 수에 따른 포인터 배열 할당
    if(rmatrix == NULL) //rmatrix 이중 포인터의 할당이 실패할 경우
    {
        printf("allocation error!\n");
        return 0;
    } else {
        for(int i = 0;i < row;i++)
        {
            rmatrix[i] = (int*)malloc(sizeof(int) * col); //행 별 배열 할당
            if(rmatrix[i] == NULL) //rmatrix의 행 중 하나라도 할당 실패할 경우
            {
                printf("allocation error!\n");
                return 0;
            }
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++)
            rmatrix[i][j] = matrix_a[i][j] + matrix_b[i][j]; //rmatrix의 원소 ij에 행렬 A와 행렬 B의 ij값 가산 후 대입
    print_matrix(rmatrix,row,col); //결과값 출력

    for(int i = 0;i < row;i++)
    {
        free(rmatrix[i]); //rmatrix의 행 별 메모리 할당 해제
    }

    free(rmatrix); //rmatrix 할당 해제

    return 1; //정상 처리 완료 출력
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(matrix_a == NULL) //matrix_a 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_a[i] == NULL) //matrix_a 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_b == NULL) //matrix_b 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_b[i] == NULL) //matrix_b 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    int** rmatrix; //결과값을 담을 행렬
    rmatrix = (int**)malloc(sizeof(int*) * row); //행 수에 따른 포인터 배열 할당
    if(rmatrix == NULL) //rmatrix 이중 포인터의 할당이 실패할 경우
    {
        printf("allocation error!\n");
        return 0;
    } else {
        for(int i = 0;i < row;i++)
        {
            rmatrix[i] = (int*)malloc(sizeof(int) * col); //행 별 배열 할당
            if(rmatrix[i] == NULL) //rmatrix의 행 중 하나라도 할당 실패할 경우
            {
                printf("allocation error!\n");
                return 0;
            }
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++)
            rmatrix[i][j] = matrix_a[i][j] - matrix_b[i][j]; //rmatrix의 원소 ij에 행렬 A에 행렬 B의 ij값을 감산한 후 대입
    print_matrix(rmatrix,row,col); //결과값 출력
    
    for(int i = 0;i < row;i++)
    {
        free(rmatrix[i]); //rmatrix의 행 별 메모리 할당 해제
    }

    free(rmatrix); //rmatrix 할당 해제

    return 1; //정상 처리 완료 출력
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if(matrix == NULL) //matrix 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < col;i++) //전달 받는 인수가 matrix_t를 기준으로 하기 때문에 matrix기준으로는 행과 열이 뒤바뀐다
    {
        if(matrix[i] == NULL) //matrix 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_t == NULL) //matrix_t 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_t[i] == NULL) //matrix_t 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++)
            matrix_t[i][j] = matrix[j][i]; //matrix_t의 원소 ij에 matrix의 ji값을 대입

    return 1; //정상 처리 완료 출력
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    if(matrix_a == NULL) //matrix 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++) 
    {
        if(matrix_a[i] == NULL) //matrix 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_t == NULL) //matrix_t 포인터가 제대로 전달되지 않았을 시
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < col;i++) //전달 받는 인수가 matrix_a를 기준으로 하기 때문에 matrix_t기준으로는 행과 열이 뒤바뀐다
    {
        if(matrix_t[i] == NULL) //matrix_t 포인터의 행 중 할당 실패한 것이 존재할 시
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    int** rmatrix; //결과값을 담을 행렬
    rmatrix = (int**)malloc(sizeof(int*) * row); //행 수에 따른 포인터 배열 할당
    if(rmatrix == NULL) //rmatrix 이중 포인터의 할당이 실패할 경우
    {
        printf("allocation error!\n");
        return 0;
    } else {
        for(int i = 0;i < row;i++)
        {
            rmatrix[i] = (int*)malloc(sizeof(int) * row); //전치행렬의 곱이므로 행과 열의 수 모두 row가 된다. <= (n x m 행렬) x (m x n 행렬) = n x n 행렬
            if(rmatrix[i] == NULL) //rmatrix의 행 중 하나라도 할당 실패할 경우
            {
                printf("allocation error!\n");
                return 0;
            }
        }
    }

    int sum = 0; //임시로 matrix의 행과 matrix_t의 열의 곱의 합을 저장할 수
    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j < row;j++)
        {
            sum = 0;
            for(int k = 0;k < col;k++)
            {
                sum += matrix_a[i][k] * matrix_t[k][j]; //matrix_a의 원소 ik와 matrix_t의 원소 kj를 곱한 후 sum에 가산
            }
            rmatrix[i][j] = sum; //matrix_a의 i행과 matrix_t의 j열의 곱의 합을 rmatrix의 원소 ij에 대입
        }
    }
    print_matrix(rmatrix,row,row); //rmatrix 출력

    for(int i = 0;i < row;i++)
    {
        free(rmatrix[i]); //rmatrix의 행 별 메모리 할당 해제
    }

    free(rmatrix); //rmatrix 할당 해제
}