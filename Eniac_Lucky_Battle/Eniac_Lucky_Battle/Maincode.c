#include <stdio.h>
#include "LBsystem.h"
//게임 구조 변수
int Dn = 3, Dice1 = 0, Dice2 = 0, Choice = 0, Stage = 0, Battlecount = 0, Battleturn = 0;
int Event[21];
//플레이어 변수
int P_Hp = 1, P_Maxhp = 1;
int P_Luck = 0, P_Belief = 0, P_Dn = 0; //Dn에 더하는 변수
int P_Turn = 1; //플레이어, 적 주사위 굴리는 타이밍 정하는 변수 1이면 플레이어, 0이면 몬스터
//몬스터 변수
int Mob_Hp = 0, Mob_Maxhp = 0, Mob_Luck = 0, Elite = 0, Mob_Name = 0, DMG = 0; //몹 이름은 100으로 초기화

//메인 함수
int main() {
	srand((unsigned)time(NULL));
	Hidecursor();
	Event_Generate();
	/*
	Text_start();
	Clearscreen();
	*/
	if (P_Hp > 0) {
		/*
		Text_prologue_1();
		Text_prologue_2();
		*/
		Text_tutorial();
		Choice = _getch();

		Clearscreen();
		switch (Choice) {
		case 49: { //튜토리얼 시작
			//Text_tutorial_o();
			P_Hp = 20, P_Maxhp = 20;
			Mob_Hp = 100, Mob_Maxhp = 100;
			Battle_start();
			system("pause");
			Clearscreen();
			Battle_tutorial();
			break;
		}

		default: {
			Text_tutorial_n();
			break;
		}
		}
		Clear();
		MainEvent(); //스탯 정하는 튜토리얼
	}
	
	int event = 0;
	for (Stage = 1; Stage < 4 && P_Hp > 0; Stage++) { //스테이지
		for (Battlecount = 0; Battlecount < 5 && P_Hp > 0; Battlecount++) { //스테이지 내부
			Mobname();
			Mob_Spawn();

			Battle_start();
			Battle_Choice();

			switch (Choice) {
			case 49: {//배틀 실행
				Battle_System();
				if (Mob_Hp <= 0) {
					Battle_Win();
					Clear();

					Event_Run();//이벤트 실행
					break;
				}
			}

			case 50: { //도망치기
				Battle_Escape();
				Clear();
				continue;
			}
			}
		}

		while (P_Hp > 0) {//보스전
			Battle_Boss();
			Mob_Spawn();
			Battle_System();
			if (Mob_Hp <= 0) {
				Dn++;
				Battle_BossWin();
				Clear();
				break;
			}
		}
	}
	//if문 써서 체력이 0이 되었을 때 게임 오버
	//else if 문 써서 스테이지 4까지 클리어했을 때 엔딩
	return 0;
}