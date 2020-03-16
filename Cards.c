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

// 役柄の取得
short int GetSuit(short int id)
{
    return (id-1)/CARDS_RANK_MAX;
}

// 強さの取得
short int GetRank(short int id)
{
    return (id%CARDS_RANK_MAX)+1;
}

// 役柄の文字列を取得
void GetSuitStr(short int id, char* result)
{
    char* suit[SUIT_MAX] = {"♤ ","♡ ","♢ ","♧ "};
    sprintf(result, "%s", suit[GetSuit(id)]);
}

// 強さの文字列を取得
void GetRankStr(short int id, char* result)
{
    short int rank = GetRank(id);
    switch (rank)
    {
        case 13:    sprintf(result, "%s", "K");  break;
        case 12:    sprintf(result, "%s", "Q");  break;
        case 11:    sprintf(result, "%s", "J");  break;
        case 1:     sprintf(result, "%s", "A");  break;
        default:    sprintf(result, "%d", rank); break;
    }
}
