#include"Cards.h"
#include<stdio.h>

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

    // 山札の枚数分入れ替え処理を行う
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
        // 範囲内の値を取得し、使用済みにする
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
        case SPADES:    printf("♤ ");      break;
        case HEARTS:    printf("♡ ");      break;
        case DIAMONDOS: printf("♢ ");      break;
        case CLUBS:     printf("♧ ");      break;
        default:        printf("Joker");   break;
    }

    // 強さの表記
    switch (rank)
    {
        case 13: printf("K");           break;
        case 12: printf("Q");           break;
        case 11: printf("J");           break;
        case 1:  printf("A");           break;
        default: printf("%d", rank);    break;
    }
}