#pragma once
#include<stdlib.h>

// トランプの強さ
#define CARDS_RANK_MAX (13)

// トランプの役柄
enum tag_suit {
    SPADES,
    HEARTS,
    DIAMONDOS,
    CLUBS,
    SUIT_MAX,
}SUIT;

// 山札の初期化
void DeckInit(short int* deck,  size_t length);
// 山札を混ぜる
void DeckShuffle(short int* deck, size_t length);
// 山札を引く
short int DeckDraw(short int* deck, size_t length, short int index);
// カードの表記
void PrintCards(short int id);
