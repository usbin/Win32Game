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
	//�ɼ�: DIB ���� ��Ʈ������ �о����, �ι�° ���ڸ� ���� ��η� �����ؼ� ���� ���Ͽ��� �о����
	// DDB���: ���ҽ��� ��Ʈ���� �ҷ��� DIB -> DDB�� ��ȯ�� DC�� �����ϴ� ���
	// DIB���: ���� ���� ������� ���� �о�� DIB�� ������ �̿��� ���� �ȼ��� ���� ���
	// DDB�� �������� �������� �ȼ� �۾��� �Ұ�, DIB�� �ȼ� ���� ���������� ���ϰ� ����
	// �� ���� ���� �߰� ����� DIB �����̶�� ��.
	
	GetObject(hbitmap_, sizeof(BITMAP), &bit_info_);

	//�޸�DC�� ��Ʈ���� ����
	HBITMAP org_bitmap = (HBITMAP)SelectObject(mem_hdc_, hbitmap_);
	DeleteObject(org_bitmap);


}
