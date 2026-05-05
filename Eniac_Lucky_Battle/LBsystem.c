#include "LBsystem.h"
#include <stdio.h>

void Clearscreen() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) return;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD consoleSize;
	DWORD charsWritten;
	COORD homeCoords = { 0, 0 };

	// 현재 콘솔 정보 가져오기
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

	consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

	// 콘솔 문자 채우기 (공백으로)
	FillConsoleOutputCharacter(
		hConsole,
		' ',
		consoleSize,
		homeCoords,
		&charsWritten
	);

	// 콘솔 속성(색상 등)도 초기화
	FillConsoleOutputAttribute(
		hConsole,
		csbi.wAttributes,
		consoleSize,
		homeCoords,
		&charsWritten
	);

	// 커서 위치를 (0,0)으로 이동
	SetConsoleCursorPosition(hConsole, homeCoords);
	return;
}

void Clear() {
	Dice1 = 0, Dice2 = 0, Choice = 0, Battleturn = 0;
	Mob_Hp = 0, Mob_Maxhp = 0, Mob_Luck = 0, Elite = 0, Mob_Name = 100;
	return;
}

void Hidecursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(consoleHandle, &info); // 현재 커서 정보 가져오기
	info.bVisible = FALSE; // 커서 숨기기 설정 (TRUE는 보이기)
	SetConsoleCursorInfo(consoleHandle, &info); // 설정 적용
	return;
}

int Getrandom(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

void Diceroll() {
	if (Battleturn % 2 == 1) {
		Dice1 = Getrandom(1, Dn+P_Dn);
		Dice2 = Getrandom(1, Dn+P_Dn);
	}
	else if (Battleturn % 2 == 0) {
		if (Elite == 1) {
			Dice1 = Getrandom(1, Dn+1);
			Dice2 = Getrandom(1, Dn+1);
		}
		else if (Battlecount == 5) {
			Dice1 = Getrandom(1, Dn+2);
			Dice2 = Getrandom(1, Dn+2);
		}
		else {
			Dice1 = Getrandom(1, Dn);
			Dice2 = Getrandom(1, Dn);
		}
	}
	return;
}

int P_DMG() {
	int damage = (Dice1 == Dice2 ? (Dice1 + Dice2) * 2 : Dice1 + Dice2) + P_Luck;
	return damage;
}

int Mob_DMG() {
	int damage = (Dice1 == Dice2 ? (Dice1 + Dice2) * 2 : Dice1 + Dice2) + Mob_Luck;
	DMG = damage;
	return damage;
}

char* Mobname() {
	char* Mob_Name_1[20] = { "회색 늑대", "박쥐", "멧돼지", "들개", "거대 거미", "고블린", "슬라임", "독사", "참새", "아르마딜로",
	"거대 개미", "양귀비", "흡혈 식물", "고라니", "독버섯", "숲의 도적", "돼지후", "반달곰", "그림자 늑대", "살인 진드기" };
	char* Mob_Name_2[20] = { "샌드웜(?)", "전갈", "구울", "검은 독수리", "살아있는 모래폭풍", "도굴꾼", "생계형 도적", "황무지 까마귀", "사막 여우", "분노 멧돼지",
	"살인 거저리", "망가진 전투 인형", "흡혈 박쥐", "데저트 트래퍼", "거대 바퀴벌레", "선인장", "왜곡된 빛의 환영", "광기 어린 사냥꾼", "수분 강탈자", "고대 문명의 잔해" };
	char* Mob_Name_3[20] = { "눈사람", "설원 늑대", "곰", "곰 사냥꾼", "밀렵꾼", "산적", "지하탄광의 생존자", "스노우 오크", "쿠키커터 고블린", "화이트 놀",
	"제빵사였던 해골", "눈토끼", "사슴", "주술사", "아이스 슬라임", "예티", "와이반", "부숴진 바이올린", "온기를 탐하는 자", "설녀" };
	char* Mob_Boss[3] = { "어스골렘 = 숲의 수호자", "샌드웜 = 사막의 재앙", "드래곤 = 설산의 폭군" };
	if (Battlecount == 5) {
		return Mob_Boss[Stage-1];
	}
	else {
		if (Mob_Name == 100) {
			Mob_Name = Getrandom(0, 19);
			Elite = Mob_Name >= 14 ? 1 : 0;
		}

		if (Stage == 1) {
			return Mob_Name_1[Mob_Name];
		}
		else if (Stage == 2) {
			return Mob_Name_2[Mob_Name];
		}
		else if (Stage == 3) {
			return Mob_Name_3[Mob_Name];
		}
	}
}

void Mob_Spawn() {
	Mob_Hp = 20 + Getrandom(0,15) + (Stage * 10) + (Elite * 10);
	if (Battlecount == 5) {
		Mob_Hp += 20;
	}
	Mob_Maxhp = Mob_Hp;
	Mob_Luck = Stage + Getrandom(0, Stage*3);
}

