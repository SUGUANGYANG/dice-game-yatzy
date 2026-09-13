// dice-game-yatzy
// C언어로 구현한 주사위 5개를 굴려 족보로 점수를 매기는 콘솔 게임
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 주사위 정렬 함수
void sortDice(int dice[], int n)
{
    int i,j,temp;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(dice[j]>dice[j+1]){
                temp = dice[j];
                dice[j]=dice[j+1];
                dice[j+1]=temp;
            }
        }
    }
}

// 스트레이트(1-5 또는 2-6) 판별
int isStraight(int dice[])
{
    int smallStraight = 1;
    int largeStraight = 1;

    for(int i=0;i<5;i++)
    {
        if(dice[i] != i + 1) smallStraight = 0;
        if(dice[i] != i + 2) largeStraight = 0;
    }

    return smallStraight || largeStraight;
}

// 족보에 따라 점수 계산
int calcScore(int dice[])
{
    int count[7]={0};
    for(int i=0;i<5;i++){
        count[dice[i]]++;
    }

    int pair=0, triple=0, four=0, yacht=0;

    for(int num=1;num<=6;num++)
    {
        if(count[num]==2) pair = num;
        if(count[num]==3) triple = num;
        if(count[num]==4) four = num;
        if(count[num]==5) yacht = num;
    }

    // 요트(5개 동일) 최우선 50점
    if(yacht != 0){
        return 50;
    }
    // 풀하우스 3개+2개 →25점
    if(triple!=0 && pair!=0){
        return 25;
    }
    // 스트레이트 4개이상 연속 →30점
    if(isStraight(dice)){
        return 30;
    }
    // 포카드 4개 동일
    if(four !=0){
        return four*4;
    }
    // 트리플 3개 동일
    if(triple !=0){
        return triple*3;
    }
    // 원페어 2개 동일
    if(pair !=0){
        return pair*2;
    }
    // 아무 족보도 없으면 0점
    return 0;
}

int main(void)
{
    srand((unsigned int)time(NULL));
    int total = 0;
    int round = 5;  // 총 5판

    printf("===== 요트(Yacht) 주사위 게임 =====\n");
    for(int r=1; r<=round; r++)
    {
        int dice[5];
        printf("\n【%d판】주사위 결과 : ",r);
        // 주사위 5개 랜덤 굴리기
        for(int i=0;i<5;i++)
        {
            dice[i] = rand()%6 +1;
            printf("%d ", dice[i]);
        }
        sortDice(dice,5);
        int sc = calcScore(dice);
        printf(" | 이번 판 점수 : %d\n", sc);
        total += sc;
    }
    printf("\n===== 게임 종료, 총점 : %d =====\n", total);
    return 0;
}
