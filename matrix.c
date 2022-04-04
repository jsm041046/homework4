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

    char command; //char�� ���� command ����
    printf("[----- ������  2021041046 -----]\n"); //�̸� �й� ���

    int row, col; //�� ��, �� �� ����� int�� ���� row col ����
    srand(time(NULL)); //���� �� �õ带 ���� �ð��� ���� ����

    printf("Input row and col : "); //�� ���� �� �� �Է� �ȳ�
    scanf("%d %d", &row, &col); //�� ���� �� �� �Է�
    int** matrix_a = create_matrix(row, col); //��� A ����
    int** matrix_b = create_matrix(row, col); //��� B ����
    int** matrix_a_t = create_matrix(col, row); //��� A_T ����

    printf("Matrix Created.\n"); //�ȳ�

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //��� A�� B�� ���� ���� �� ���α׷� ������ ����

    do{ //����
        //���� ������ ��ɾ� �ȳ�
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = "); //�Է� �ȳ�
        scanf(" %c", &command); //�Է°� ����

        switch(command) { //�Է� ���� ���� �б�
        case 'z': case 'Z': //�Է°��� Z�� ���
            printf("Matrix Initialized\n"); //�ȳ�
            fill_data(matrix_a, row, col); //��� A ������ �Է�
            fill_data(matrix_b, row, col); //��� B ������ �Է�
            break; //case�� ����
        case 'p': case 'P': //�Է°��� P�� ���
            printf("Print matrix\n"); //�ȳ�
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //��� A ���
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //��� B ���
            break; //case�� ����
        case 'a': case 'A': //�Է°��� A�� ���
            printf("Add two matrices\n"); //�ȳ�
            addition_matrix(matrix_a, matrix_b, row, col); //��� A�� B�� ���ؼ� ���
            break; //case�� ����
        case 's': case 'S': //�Է°��� S�� ���
            printf("Subtract two matrices \n"); //�ȳ�
            subtraction_matrix(matrix_a, matrix_b, row, col); //��� A�� B�� ���� ���
            break; //case�� ����
        case 't': case 'T': //�Է°��� T�� ���
            printf("Transpose matrix_a \n"); //�ȳ�
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //��� A�� ��ġ�ؼ� A_T�� ����
            print_matrix(matrix_a_t, col, row); //��� A_T�� ���
            break; //case�� ����
        case 'm': case 'M': //�Է°��� M�� ���
            printf("Multiply matrix_a with transposed matrix_a \n"); //�ȳ�
            transpose_matrix(matrix_a, matrix_a_t, col, row); //��� A�� ��ġ�ؼ� A_T�� ����
            multiply_matrix(matrix_a, matrix_a_t, row, col); //��� A * A_T�� ���
            break; //case�� ����
        case 'q': case 'Q': //�Է°��� Q�� ���
            printf("Free all matrixes..\n"); //�ȳ�
            free_matrix(matrix_a_t, col, row); //��� A_T�� ���Ǵ� �޸𸮸� �Ҵ� ����
            free_matrix(matrix_a, row, col); //��� A�� ���Ǵ� �޸𸮸� �Ҵ� ����
            free_matrix(matrix_b, row, col); //��� B�� ���Ǵ� �޸𸮸� �Ҵ� ����
            break; //case�� ����
        default: //�Է°��� ��� �Ϳ��� �ش���� �ʴ� ���
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break; //case�� ����
        }

    }while(command != 'q' && command != 'Q'); //�Է� ��ɾ Q�� ��� ������ ��������

    return 1; //���α׷� ���� ����
}

int** create_matrix(int row, int col)
{
    if(row <= 0 || col <= 0) { //row �� col ���� 0���϶� ��� ������ �Ұ����� ���
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix; //���������� matrix ����
    //matrix ���������ͷ� int[row][col]������ ���߹迭 �Ҵ�
    matrix = (int**)malloc(sizeof(int*) * row); //�� ���� ���� ������ �迭 �Ҵ�
    if(matrix == NULL) //matrix ���� �������� �Ҵ��� ������ ���
    {
        printf("allocation failed!\n");
        return NULL;
    } else {
        for(int i = 0;i < row;i++)
        {
            matrix[i] = (int*)malloc(sizeof(int) * col); //�� �� �迭 �Ҵ�
            if(matrix[i] == NULL) //matrix�� �� �� �ϳ��� �Ҵ� ������ ���
            {
                printf("allocation failed!\n");
                return NULL;
            }
        }
    }
    
    return matrix; //�Ҵ� �� ������ ��ȯ
}

void print_matrix(int** matrix, int row, int col)
{
    if(matrix == NULL) //matrix �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix[i] == NULL) //matrix �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return;
        }
    }
    //��� ���ȣ �𼭸� ���κ�
    printf("��\t");
    for(int i = 0;i < col;i++)
        printf("\t");
    printf("��\n");

    //��� ���
    for(int i = 0;i < row;i++)
    {
        printf("|\t");
        for(int j = 0;j < col;j++)
        {
            printf("%d\t",matrix[i][j]);
        }
        printf("|\n");
    }

    //��� ���ȣ �𼭸� �Ʒ��κ�
    printf("��\t");
    for(int i = 0;i < col;i++)
        printf("\t");
    printf("��\n");
}


int free_matrix(int** matrix, int row, int col)
{
    if(matrix == NULL) //matrix �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix[i] == NULL) //matrix �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    for(int i = 0;i < row;i++)
    {
        free(matrix[i]); //�ش� ����� �� �� �޸� �Ҵ� ����
    }

    free(matrix); //�ش� ��� �Ҵ� ����

    return 1; //���� ó�� �Ϸ� ���
}


int fill_data(int** matrix, int row, int col)
{
    if(matrix == NULL) //matrix �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix[i] == NULL) //matrix �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j<col;j++)
            matrix[i][j] = rand() % 20; //��� ����� ���ҿ� 0~19������ �� ����
        
    return 1; //���� ó�� �Ϸ� ���
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(matrix_a == NULL) //matrix_a �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_a[i] == NULL) //matrix_a �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_b == NULL) //matrix_b �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_b[i] == NULL) //matrix_b �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    int** rmatrix; //������� ���� ���
    rmatrix = (int**)malloc(sizeof(int*) * row); //�� ���� ���� ������ �迭 �Ҵ�
    if(rmatrix == NULL) //rmatrix ���� �������� �Ҵ��� ������ ���
    {
        printf("allocation error!\n");
        return 0;
    } else {
        for(int i = 0;i < row;i++)
        {
            rmatrix[i] = (int*)malloc(sizeof(int) * col); //�� �� �迭 �Ҵ�
            if(rmatrix[i] == NULL) //rmatrix�� �� �� �ϳ��� �Ҵ� ������ ���
            {
                printf("allocation error!\n");
                return 0;
            }
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++)
            rmatrix[i][j] = matrix_a[i][j] + matrix_b[i][j]; //rmatrix�� ���� ij�� ��� A�� ��� B�� ij�� ���� �� ����
    print_matrix(rmatrix,row,col); //����� ���

    for(int i = 0;i < row;i++)
    {
        free(rmatrix[i]); //rmatrix�� �� �� �޸� �Ҵ� ����
    }

    free(rmatrix); //rmatrix �Ҵ� ����

    return 1; //���� ó�� �Ϸ� ���
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(matrix_a == NULL) //matrix_a �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_a[i] == NULL) //matrix_a �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_b == NULL) //matrix_b �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_b[i] == NULL) //matrix_b �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    int** rmatrix; //������� ���� ���
    rmatrix = (int**)malloc(sizeof(int*) * row); //�� ���� ���� ������ �迭 �Ҵ�
    if(rmatrix == NULL) //rmatrix ���� �������� �Ҵ��� ������ ���
    {
        printf("allocation error!\n");
        return 0;
    } else {
        for(int i = 0;i < row;i++)
        {
            rmatrix[i] = (int*)malloc(sizeof(int) * col); //�� �� �迭 �Ҵ�
            if(rmatrix[i] == NULL) //rmatrix�� �� �� �ϳ��� �Ҵ� ������ ���
            {
                printf("allocation error!\n");
                return 0;
            }
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++)
            rmatrix[i][j] = matrix_a[i][j] - matrix_b[i][j]; //rmatrix�� ���� ij�� ��� A�� ��� B�� ij���� ������ �� ����
    print_matrix(rmatrix,row,col); //����� ���
    
    for(int i = 0;i < row;i++)
    {
        free(rmatrix[i]); //rmatrix�� �� �� �޸� �Ҵ� ����
    }

    free(rmatrix); //rmatrix �Ҵ� ����

    return 1; //���� ó�� �Ϸ� ���
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if(matrix == NULL) //matrix �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < col;i++) //���� �޴� �μ��� matrix_t�� �������� �ϱ� ������ matrix�������δ� ��� ���� �ڹٲ��
    {
        if(matrix[i] == NULL) //matrix �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_t == NULL) //matrix_t �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++)
    {
        if(matrix_t[i] == NULL) //matrix_t �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++)
            matrix_t[i][j] = matrix[j][i]; //matrix_t�� ���� ij�� matrix�� ji���� ����

    return 1; //���� ó�� �Ϸ� ���
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    if(matrix_a == NULL) //matrix �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < row;i++) 
    {
        if(matrix_a[i] == NULL) //matrix �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    if(matrix_t == NULL) //matrix_t �����Ͱ� ����� ���޵��� �ʾ��� ��
    {
        printf("allocation error!\n");
        return 0;
    }

    for(int i = 0; i < col;i++) //���� �޴� �μ��� matrix_a�� �������� �ϱ� ������ matrix_t�������δ� ��� ���� �ڹٲ��
    {
        if(matrix_t[i] == NULL) //matrix_t �������� �� �� �Ҵ� ������ ���� ������ ��
        {
            printf("allocation error!\n");
            return 0;
        }
    }

    int** rmatrix; //������� ���� ���
    rmatrix = (int**)malloc(sizeof(int*) * row); //�� ���� ���� ������ �迭 �Ҵ�
    if(rmatrix == NULL) //rmatrix ���� �������� �Ҵ��� ������ ���
    {
        printf("allocation error!\n");
        return 0;
    } else {
        for(int i = 0;i < row;i++)
        {
            rmatrix[i] = (int*)malloc(sizeof(int) * row); //��ġ����� ���̹Ƿ� ��� ���� �� ��� row�� �ȴ�. <= (n x m ���) x (m x n ���) = n x n ���
            if(rmatrix[i] == NULL) //rmatrix�� �� �� �ϳ��� �Ҵ� ������ ���
            {
                printf("allocation error!\n");
                return 0;
            }
        }
    }

    int sum = 0; //�ӽ÷� matrix�� ��� matrix_t�� ���� ���� ���� ������ ��
    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j < row;j++)
        {
            sum = 0;
            for(int k = 0;k < col;k++)
            {
                sum += matrix_a[i][k] * matrix_t[k][j]; //matrix_a�� ���� ik�� matrix_t�� ���� kj�� ���� �� sum�� ����
            }
            rmatrix[i][j] = sum; //matrix_a�� i��� matrix_t�� j���� ���� ���� rmatrix�� ���� ij�� ����
        }
    }
    print_matrix(rmatrix,row,row); //rmatrix ���

    for(int i = 0;i < row;i++)
    {
        free(rmatrix[i]); //rmatrix�� �� �� �޸� �Ҵ� ����
    }

    free(rmatrix); //rmatrix �Ҵ� ����
}