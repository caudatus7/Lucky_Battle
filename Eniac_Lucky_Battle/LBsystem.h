#pragma once
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

extern int Dn, Dice1, Dice2;
extern int P_Hp, P_Maxhp;
extern int P_Luck, P_Belief, P_Dn;
extern int Mob_Hp, Mob_Maxhp, Mob_Luck;
extern int Choice;
extern int Stage;
extern int Battlecount;
extern int Battleturn;
extern int Elite;
extern int Mob_Name;
extern int DMG;

//시스템 함수
void Clearscreen(); //화면 초기화
void Clear(); //변수 초기화
int Getrandom(int min, int max); //난수 생성
void Diceroll(); //주사위 굴리기
void Hidecursor(); //커서 숨기기
char* Mobname(); //몬스터 이름 정하기
void Mob_Spawn(); //몬스터 스탯 생성
void print_dice_pair(); //주사위 값 출력
int P_DMG(); //플레이어 공격력 계산
int Mob_DMG(); //몬스터 공격력 계산

//텍스트 함수
void Text_start();
void Text_prologue_1();
void Text_prologue_2();
void Text_tutorial();
void Text_tutorial_o();
void Text_tutorial_n();

void Battle_start();
void Battle_Boss();
void Battle_tutorial();
void Battle_1();
void Battle_ATK();
void Battle_DEF_1();
void Battle_DEF_2();
void Battle_HEAL();
void Battle_Escape();