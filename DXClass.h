#pragma once
#include "global.h"

class DXClass
{
private:
	SINGLETON(DXClass);

	ID3D11Device* p_d3d_device_;
	ID3D11DeviceContext* p_immediate_context_;
	IDXGISwapChain* p_swap_chain_;
	ID3D11RenderTargetView* p_render_target_view_;

	ID3D11VertexShader* p_vs_;
	ID3D11PixelShader* p_ps_;
	ID3D11Buffer* p_vertex_buffer_;
	ID3D11Buffer* p_idx_buffer_;
	ID3D11Buffer* p_const_buffer_on_resize_;//쉐이더에게 해상도 넘겨주기 위한 파라미터 버퍼
	ID3D11Buffer* p_const_buffer_on_render_;//텍스쳐 사용 여부와 color를 갖고 있는 파라미터 버퍼
	DXGI_FORMAT idx_format_;

	//이미지 렌더링용 샘플러
	ID3D11SamplerState* p_sampler_linear_;

	//텍스트 렌더링
	IDWriteFactory* p_dwrite_factory_;
	ID2D1Factory* p_d2d1_factory_;
	IDXGISurface1* p_d2d_rt_;
	ID2D1RenderTarget* p_text_render_target_;
	IDWriteTextFormat* p_text_format_;
	//말줄임표 설정
	DWRITE_TRIMMING trim_options_ = {
		DWRITE_TRIMMING_GRANULARITY_CHARACTER
	};
	IDWriteInlineObject* p_trim_sign_;

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
};

