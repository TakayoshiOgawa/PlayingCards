#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Cards.h"

int main(void)
{
    // トランプの配列と長さ
    short int deck[SUIT_MAX * CARDS_RANK_MAX];
    size_t length = sizeof(deck)/sizeof(deck[0]);
    // 確認用のドロー回数
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