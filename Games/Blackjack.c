#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Cards.h"
#include"../Util.h"

#define RANK_MAX (10)
#define BJ (21)

typedef enum tag_bj_command
{
    NONE,
    HIT,
    STAND,
    BJ_COMMAND_MAX,
}BJ_COMMAND;
char* commandList[BJ_COMMAND_MAX] = {"Surrender", "Hit", "Stand"};

// カードの表記
void _ShowCard(short int id);
// 配列の合計を算出
short int _ArrayTotal(short int* array, size_t length);
// ゲーム依存の値を取得
short int _GetValue(short int id);
// 手札の値を計算
short int _CalcHand(short int* hands, size_t length);

// ブラックジャック
int Blackjack(void)
{
    // 山札とシステム
    short int deck[SUIT_MAX * CARDS_RANK_MAX];
    const size_t LENGTH = CountOf(deck);
    int drawCnt = 0;
    int index = 0;
    int input = 0;

    // スタンドコマンドの選択
    BOOL selectStand = FALSE;

    // 手札の情報
    const int DEALER_HAND_MAX = 2;
    const int PLAYER_HAND_MAX = 9;
    short int dealer[DEALER_HAND_MAX];
    short int player[PLAYER_HAND_MAX];
    short int dealerHand = 0;
    short int playerHand = 0;
    short int handTotal = 0;
    int playerHandCnt = 0;
    // 手札の初期化
    for(index = 0; index < CountOf(dealer); index++) {dealer[index]=-1;}
    for(index = 0; index < CountOf(player); index++) {player[index]=-1;}

    // 乱数の初期化
    srand((unsigned int)time(NULL));
    // 山札の初期化
    DeckInit(deck,LENGTH);
    // 山札をシャッフル
    DeckShuffle(deck, LENGTH);

    // ディーラーが２枚引く
    dealer[0] = DeckDraw(deck,LENGTH,drawCnt++);
    dealer[1] = DeckDraw(deck,LENGTH,drawCnt++);
    // プレイヤーが２枚引く
    player[playerHandCnt++] = DeckDraw(deck,LENGTH,drawCnt++);
    player[playerHandCnt++] = DeckDraw(deck,LENGTH,drawCnt++);
    // プレイヤーの手札を計算
    playerHand=_CalcHand(player,playerHandCnt);

    // プレイヤーがバースト、もしくはスタンド選択で
    while (!selectStand&&playerHand<BJ)
    {
        // 消去コマンドの実行
        system("clear");

        // ディーラーの手札を表示（片方は非表示）
        printf("D[%d]", _GetValue(dealer[0]));
        _ShowCard(dealer[0]);
        printf(",%s", "??");
        printf("\n");

        // プレイヤの手札を表示
        printf("1[%d]", playerHand);
        for(index = 0; index < playerHandCnt; index++)
        {
            _ShowCard(player[index]);
            printf("%s", (index == playerHandCnt-1)?"\n":","); 
        }

        // コマンドの入力
        for (index = HIT; index < BJ_COMMAND_MAX; index++)
        {
            printf("%d:%s", index,commandList[index]);
            printf(" %s ", (index == BJ_COMMAND_MAX-1)?">":"/");
        }
        scanf("%d", &input);

        // コマンドの選択
        switch (input)
        {
            case HIT:   // ヒットなら１枚引く
                player[playerHandCnt++] = DeckDraw(deck,LENGTH,drawCnt++);
                break;
            case STAND: // スタンドなら終了
                selectStand=TRUE;
                break;
            default:
                return FALSE;
                break;
        }
        // プレイヤの手札合計を算出
        playerHand=_CalcHand(player,playerHandCnt);
    }

    // 消去コマンドの実行
    system("clear");
    // ゲームを抜けた理由を表記
    if (selectStand)
    {
        printf("%s\n","Stand!!");
    }
    else
    {
        printf("%s\n", (playerHand==BJ)?"BlackJack!":"Bust!!");
    }

    // 双方の手札を計算
    dealerHand = _CalcHand(dealer, DEALER_HAND_MAX);
    playerHand = _CalcHand(player, playerHandCnt);

    // ディーラーのカードを捲る
    printf("D[%d]", dealerHand);
    for(index = 0; index < DEALER_HAND_MAX; index++)
    {
        _ShowCard(dealer[index]);
        printf("%s", (index == DEALER_HAND_MAX-1)?"\n":","); 
    }
    // プレイヤーのカードを再表示       
    printf("1[%d]", playerHand);
    for(index = 0; index < playerHandCnt; index++)
    {
        _ShowCard(player[index]);
        printf("%s", (index == playerHandCnt-1)?"\n":","); 
    }

    // 勝敗を判定
    printf("\n");
    handTotal = playerHand - dealerHand;
    if (handTotal < 0 || (!selectStand&&handTotal!=BJ))
    {
        printf("You Lose...");
    }
    else if (handTotal == 0)
    {
        printf("Draw Game.");
    }
    else if (handTotal > 0)
    {
        printf("You Win!!");
    }
    printf("\n");
    printf("\n");

    return TRUE;
}

// カードの表記
void _ShowCard(short int id)
{
    char str[5];
    GetSuitStr(id, str);
    printf("%s ", str);
    GetRankStr(id, str);
    printf("%s", str);
}

// 配列の合計を算出
short int _ArrayTotal(short int* array, size_t length)
{
    short int result = 0;

    int index = 0;
    for (index = 0; index < length; index++)
    {
        result += array[index];
    }
    return result;
}

// ゲーム依存の値を取得
short int _GetValue(short int id)
{
    // カードの強さは１０以下になる
    short int result = 0;
    result = GetRank(id);
    result = Min(result, RANK_MAX);
    return result;
}

// 手札の値を計算
short int _CalcHand(short int* hands, size_t length)
{
    short int keep[length];
    int index = 0;

    for (index = 0; index < length; index++)
    {
        // 初期値の場合は処理をスキップ
        if (hands[index]==-1)
        {
            keep[index] = 0;
            continue;
        }

        // カードの強さを合算
        keep[index] = _GetValue(hands[index]);
    }
    
    // 「A」は手札の合計が11以下の場合は10加算される
    if (_ArrayTotal(keep, length)<=BJ-RANK_MAX)
    {
        for (index = 0; index < length; index++)
        {
            if (keep[index]==1)
            {
                keep[index]+=RANK_MAX;
                break;
            }
        }
    }
    return _ArrayTotal(keep, length);
}
