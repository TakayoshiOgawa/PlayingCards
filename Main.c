#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// トランプの役柄
enum tag_suit {
    SPADES,
    HEARTS,
    DIAMONDOS,
    CLUBS,
    SUIT_MAX,
}SUIT;
// トランプの強さ
#define CARDS_RANK_MAX (13)

// 山札の初期化
void DeckInit(short int* deck,  size_t length);
// 山札を混ぜる
void DeckShuffle(short int* deck, size_t length);
// 山札を引く
short int DeckDraw(short int* deck, size_t length, short int index);
// カードの表記
void PrintCards(short int id);

int main(void)
{
    // トランプの配列と値
    short int deck[SUIT_MAX * CARDS_RANK_MAX];
    size_t length = sizeof(deck)/sizeof(deck[0]);
    short int index;
    short int drawCnt;

    // 乱数の初期化
    srand((unsigned int)time(NULL));

    // 山札の初期化
    DeckInit(deck, length);

    // 山札を混ぜる
    DeckShuffle(deck, length);

    // トランプの文字列表記
    drawCnt = length;
    while(0 <= --drawCnt)
    {
        // トランプの内容を表記
        printf("%d：",drawCnt+1);
        PrintCards(DeckDraw(deck,length,drawCnt));
        printf("\n");
    }

    return 0;
}

// 山札の初期化
void DeckInit(short int* deck, size_t length)
{
    short int index = 0;
    for (index = 0; index < length; index++)
    {
        deck[index] = index+1;
    }
}

// 山札を混ぜる
void DeckShuffle(short int* deck, size_t length)
{
    short int rnd, tmp;
    short int index;

    for (index = 0; index < length; index++)
    {
        rnd = rand()%CARDS_RANK_MAX;
        tmp = deck[index];
        deck[index] = deck[rnd];
        deck[rnd] = tmp;
    }
}

// 山札を引く
short int DeckDraw(short int* deck, size_t length, short int index)
{
    short int result = -1;
    if (0<=index&&index<length)
    {
        result = deck[index];
        deck[index] = -1;
    }
    return result;
}

// カードの表記
void PrintCards(short int id)
{
    // トランプの役柄と強さを算出
    short int suit = (id-1)/CARDS_RANK_MAX;
    short int rank = (id%CARDS_RANK_MAX)+1;

    // 役柄の表記
    switch (suit)
    {
        case 0: printf("♤ "); break;
        case 1: printf("♡ "); break;
        case 2: printf("♢ "); break;
        case 3: printf("♧ "); break;
        default: printf("Joker"); break;
    }

    // 強さの表記
    switch (rank)
    {
        case 13: printf("K"); break;
        case 12: printf("Q"); break;
        case 11: printf("J"); break;
        case 1:  printf("A"); break;
        default: printf("%d", rank); break;
    }
}