#pragma once
#include "global.h"
#include "Player.h"

/// <summary>
/// 프로그램 실행 중의 데이터를 저장하는 곳.
/// (플레이어 상태, 인벤토리 등)
/// 맵 이동시 동작
/// 1. 싱글톤 인벤토리Ui를 삭제한다.
/// 2. 싱글톤 콘솔Ui를 삭제한다.
/// 3. 이동한 맵에 플레이어가 존재하는지 체크, 있다면 enable을 true로 만들고 현재 맵의 플레이어와 데이터를 동기화한다. 없다면 새로 생성하고 데이터를 동기화한다.
///  - 동기화할 데이터: 전부...
/// </summary>
class RuntimeData
{
	SINGLETON(RuntimeData);
private:
	Player* player_ = nullptr;

public:
	void SavePlayerData(Player* player);	//내부에 플레이어 데이터를 저장
	void LoadPlayerData(Player* player);	//내부에 저장된 플레이어 데이터를 포인터의 플레이어에게 로드

	void OnDestroy();//시스템 종료할 때
};

