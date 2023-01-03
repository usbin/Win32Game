#pragma once
#include "global.h"
class GObject;

class DXClass
{
private:
	SINGLETON(DXClass);

	ID3D11Device* p_d3d_device_ = nullptr;
	ID3D11DeviceContext* p_immediate_context_ = nullptr;
	IDXGISwapChain* p_swap_chain_ = nullptr;
	ID3D11RenderTargetView* p_render_target_view_ = nullptr;

	ID3D11VertexShader* p_vs_ = nullptr;
	ID3D11PixelShader* p_ps_ = nullptr;
	ID3D11Buffer* p_vertex_buffer_ = nullptr;
	ID3D11Buffer* p_idx_buffer_ = nullptr;
	ID3D11Buffer* p_const_buffer_on_resize_ = nullptr;//���̴����� �ػ� �Ѱ��ֱ� ���� �Ķ���� ����
	ID3D11Buffer* p_const_buffer_on_render_ = nullptr;//�ؽ��� ��� ���ο� color�� ���� �ִ� �Ķ���� ����
	DXGI_FORMAT idx_format_;

	//�̹��� �������� ���÷�
	ID3D11SamplerState* p_sampler_linear_ = nullptr;

	//�ؽ�Ʈ ������
	IDWriteFactory* p_dwrite_factory_ = nullptr;
	ID2D1Factory* p_d2d1_factory_ = nullptr;
	IDXGISurface1* p_d2d_rt_ = nullptr;
	ID2D1RenderTarget* p_text_render_target_ = nullptr;
	IDWriteTextFormat* p_text_format_ = nullptr;
	//������ǥ ����
	DWRITE_TRIMMING trim_options_ = {
		DWRITE_TRIMMING_GRANULARITY_CHARACTER
	};
	IDWriteInlineObject* p_trim_sign_ = nullptr;

public:
	int Init(HWND hwnd, Vector2 resolution);
	void WriteVertexBuffer(CustomVertex* vertices, UINT vertex_count);
	void WriteIndexBuffer(UINT* indices, UINT index_count);
	void WriteConstantBufferOnResize(Vector2 resolution);
	void WriteConstantBufferOnRender(BOOL use_texture, XMFLOAT4 mesh_color);
	void ResetResolution(Vector2 new_resolution);

	void InitD2D1();
	void SetTextFormat(tstring font_name, tstring font_locale, UINT font_size,
		DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight,
		DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment);
	void RenderText(const TCHAR* text, UINT length, Vector2 pos, Vector2 scale, D2D1::ColorF color);


	inline ID3D11Device* get_d3d_device() { return p_d3d_device_; };
	inline ID3D11DeviceContext* get_immediate_context() { return p_immediate_context_; };
	inline IDXGISwapChain* get_swap_chain() { return p_swap_chain_; };

	inline ID3D11RenderTargetView* get_render_target_view() { return p_render_target_view_; };
	inline const DXGI_FORMAT& get_idx_format() { return idx_format_; }
	inline ID3D11SamplerState* get_sampler_state() { return p_sampler_linear_; };


	//
	void SaveMapfileToPng(const std::vector<GObject*>& tiles, Vector2 size);
};

