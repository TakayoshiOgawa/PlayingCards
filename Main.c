#include<stdio.h>

int main(void)
{
    // トランプの定数
    const int SUIT_MAX = 4;
    const int CARDS_RANK_MAX = 13;
    const int DECK_MAX = SUIT_MAX * CARDS_RANK_MAX;

    // トランプの配列と値
    short int deck[DECK_MAX];
    short int suit, rank;
    short int index;

    // 山札の初期化
    for (index = 0; index < DECK_MAX; index++)
    {
        deck[index] = index+1;
    }

    // トランプの文字列表記
    for (index = 0; index < DECK_MAX; index++)
    {
        // トランプの役柄と強さを算出
        suit = (deck[index]-1)/CARDS_RANK_MAX;
        rank = (deck[index]%CARDS_RANK_MAX)+1;

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

        // 役柄降順に並べた際の行区切り
        if (index%CARDS_RANK_MAX==CARDS_RANK_MAX-1)
        {
            printf("\n");
        }
        else
        {
            printf(",");
        }
    }

    return 0;
}