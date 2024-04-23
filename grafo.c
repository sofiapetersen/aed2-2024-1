#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Graph {
    int **pointer;
    int nodes;
    int links;
    int weight;
}; typedef struct Graph *graph;


void graph_setelem( graph *m, int x, int y, float elem );
graph *graph_create( void );
void graph_print( graph *m );
graph *heads_create( int x, int y );

int main () {

    graph *A = graph_create();
    graph_print( A );

    return 0;

}

graph *heads_create( int x, int y )
{
    int i;
    graph *head = ( graph * )malloc( sizeof( graph ) );//--->Cria a cabeça principal

    head->row = -1;
    head->column = -1;
    head->right = NULL;
    head->below = NULL;

    graph *head_row[x], *head_col[y];

    for ( i = 0; i < x; i++ )//--->Cria a cabeça de cada uma das linhas baseado na entrada 'm'
    {
        head_row[i] = ( graph * )malloc( sizeof( graph ) );
        head_row[i]->right = head_row[i];//--->Faz a cabeça de cada linha apontar para si própria
        head_row[i]->below = NULL;
        head_row[i]->row = -1;
    }

    for ( i = 0; i < y; i++ )//--->Cria a cabeça de cada uma das colunas baseado na entrada 'n'
    {
        head_col[i] = ( graph * )malloc( sizeof( graph ) );
        head_col[i]->below = head_col[i];//--->Faz a cabeça de cada coluna apontar para si própria
        head_col[i]->right = NULL;
        head_col[i]->column = -1;
    }

    head->right = head_col[0];//--->Faz a cabeça principal apontar para a cabeça que repesenta a primeira coluna
    head->below = head_row[0];//--->Faz a cabeça principal apontar para a cabeça que repesenta a primeira linha

    for ( i = 0; i < x - 1; i++ )//--->Faz a cabeça de cada linha apontar para a cabeça da linha de baixo
        head_row[i]->below = head_row[i+1];

    head_row[i]->below = head;//--->Faz a última linha apontar para a cabeça

    for ( i = 0; i < y - 1; i++ )//--->Faz a cabeça de cada coluna apontar para a cabeça da coluna do lado
        head_col[i]->right = head_col[i+1];

    head_col[i]->right = head;//--->Faz a última coluna apontar para a cabeça

    return head;
}

void graph_setelem( graph *m, int x, int y, float elem )
{
    int nRows = 1, nCols = 1;
    graph *new = ( graph * )malloc( sizeof( graph ) );
    new->row = x;
    new->column = y;
    new->info = elem;

    graph *p, *q, *r, *s;
    for ( r = m->right; r != m && y != nCols; r = r->right, nCols++ );//--->Conta a quantidade de Colunas
    for ( s = m->below; s != m && x != nRows; s = s->below, nRows++ );//--->Conta a quantidade de Linhas

    for ( q = r; q->below != r && q->below->row < x; q = q->below );//----->Encontra a linha onde a célula será inserida
    for ( p = s; p->right != s && p->right->column < y; p = p->right );//-->Encontra a coluna onde a célula será inserida
    

    new->right = p->right;
    p->right = new;
    new->below = q->below;
    q->below = new;

    if ( ( p->right->right->row == x && p->right->right->column == y ) )//->Se já houver alguma célula na mesma posição a antiga é desalocada, dando espaço para a nova
    {
        graph *temp = p->right->right;
        new->right = temp->right;
        temp->right = NULL;
        new->below = temp->below;
        temp->below = NULL;
        free( temp );
    }
}

graph *graph_create( void )
{
    int i, j, m, n;
    float value;

    printf( "\nEnter the number of rows and columns: " );
    scanf( "%d", &m );
    getchar();
    n = m;

    graph *head = heads_create( m, n );//----->Cria as cabeças da matriz

    while (1)
    {      
        printf( "\nEnter row, column, value (or 0 to exit): " );
        scanf( "%d", &i );

        if ( i == 0 )//------------------------------->Primeiro ele confere se o i não é 0, se for 0 quebra, se nao continua
            break;

        scanf( "%d %f", &j, &value );//----------------------->Pra inserir os proximos valores
            
        if ( i > m || j > n || i < 1 || j < 1 || value < 0 )//--------------->Se for maior que o numero de colunas/linhas ou se for menor que 1 ele solicita de novo
        {
            printf( "\nInvalid value, insert again!!" );
            continue;
        }
        graph_setelem( head, i, j, value );//-------------------->Cria uma nova célula a partir da função 'graph_setelem'
    }
    return head;
}

void graph_print( graph *m )
{
    graph *currentRow = NULL;
    int nRows = 1, nCols = 1;

    for ( currentRow = m->below; currentRow->below != m; currentRow = currentRow->below, nRows++ );//->Conta a quantidade de linhas
    for ( currentRow = m->right; currentRow->right != m; currentRow = currentRow->right, nCols++ );//->Conta a quantidade de colunas

    int curRow, curCol;

    float **graph = ( float ** )malloc( nRows * sizeof( float * ) );//--->Cria uma matriz de nRows x nCols dinamicamente
    for ( curRow = 0; curRow < nRows; curRow++ )
    {
        graph[curRow] = ( float * )malloc( nCols * sizeof( float ) );
    }

    for ( curRow = 0; curRow < nRows; curRow++ )//--->Inicializa todos o elementos da matriz em '0'
        for ( curCol = 0; curCol < nCols; curCol++ )
            graph[curRow][curCol] = 0;

    currentRow = m->below;//------>CurrentRow recebe a cabeça da primeira linha

    while ( currentRow != m )//--->Reepete enquanto o currentRow não voltar para a cabeça principal
    {
        graph *currentCell = currentRow->right;//-->CurrentCell recebe a primeira célula da linha

        while ( currentCell != currentRow )
        {
            graph[currentCell->row - 1][currentCell->column - 1] = currentCell->info;//-->A matriz criada recebe o valor que está na mesma posição da matriz esparsa
            currentCell = currentCell->right;//-->Vai para a próxima célula na mesma linha
        }

        currentRow = currentRow->below;//--->Terminada a linha, pula para a próxima
    }

    
    for ( curRow = 0; curRow < nRows; curRow++ )//->Printa a matriz esparsa com os '0's nas posições vazias
    {
        for ( curCol = 0; curCol < nCols; curCol++ )
        {
            if ( graph[curRow][curCol] < 10 ) {
                printf( "(%d, %d): %.2f   ", ( curRow + 1 ), ( curCol + 1 ), graph[curRow][curCol] );
            } else {
                printf( "(%d, %d): %.2f  ", ( curRow + 1 ), ( curCol + 1 ), graph[curRow][curCol] );
            }
        }
        printf( "\n" );//--->Pula uma linha depois de percorrer o curCol
    }
    printf( "\n\n" );

    
    for (curRow = 0; curRow < nRows; curRow++)//-->Libera a memória alocada para a matriz
        free(graph[curRow]);
    free(graph);
}
