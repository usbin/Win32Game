#include "pch.h"
#include "Texture.h"
#include "PathManager.h"
#include "Core.h"
Texture::Texture()
{
}

Texture::~Texture()
{
}
void Texture::Load()
{
	tstring texture_path = PathManager::GetInstance()->GetContentPath() + get_relative_path();

	mem_hdc_ = CreateCompatibleDC(Core::GetInstance()->get_main_hdc());
	hbitmap_ = (HBITMAP)LoadImage(nullptr, texture_path.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//옵션: DIB 섹션 비트맵으로 읽어오기, 두번째 인자를 파일 경로로 설정해서 직접 파일에서 읽어오기
	// DDB방식: 리소스로 비트맵을 불러와 DIB -> DDB로 변환해 DC가 선택하는 방법
	// DIB방식: 직접 파일 입출력을 통해 읽어와 DIB의 정보를 이용해 직접 픽셀을 찍어내는 방법
	// DDB는 가볍지만 세부적인 픽셀 작업이 불가, DIB는 픽셀 제어 가능하지만 부하가 심함
	// 이 둘을 섞은 중간 방식이 DIB 섹션이라고 함.
	
	GetObject(hbitmap_, sizeof(BITMAP), &bit_info_);

	//메모리DC와 비트맵을 연결
	HBITMAP org_bitmap = (HBITMAP)SelectObject(mem_hdc_, hbitmap_);
	DeleteObject(org_bitmap);


}
