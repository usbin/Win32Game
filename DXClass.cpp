#include "DXClass.h"
#include "PathManager.h"
#include "Core.h"

DXClass::DXClass()
	: p_d3d_device_(nullptr)
	, p_immediate_context_(nullptr)
	, p_swap_chain_(nullptr)
	, p_render_target_view_(nullptr)
	, p_vs_(nullptr)
	, p_ps_(nullptr)
	, p_const_buffer_on_resize_(nullptr)
	, p_const_buffer_on_render_(nullptr)
	, p_vertex_buffer_(nullptr)
	, p_idx_buffer_(nullptr)
	, idx_format_{} {

	trim_options_ = {
		DWRITE_TRIMMING_GRANULARITY_CHARACTER
	}; 
};

DXClass::~DXClass() {
	if (p_d3d_device_ != NULL) p_d3d_device_->Release();
	if(p_vs_) p_vs_->Release();
	if(p_ps_) p_ps_->Release();
	if(p_const_buffer_on_resize_) p_const_buffer_on_resize_->Release();
	if (p_const_buffer_on_render_) p_const_buffer_on_render_->Release();
	if(p_vertex_buffer_) p_vertex_buffer_->Release();
	if (p_idx_buffer_) p_idx_buffer_->Release();
	if (p_immediate_context_) p_immediate_context_->Release();

	if (p_d2d1_factory_) p_d2d1_factory_->Release();
	if (p_dwrite_factory_) p_dwrite_factory_->Release();
	if(p_d2d_rt_) p_d2d_rt_->Release();
	if(p_text_render_target_) p_text_render_target_->Release();
};

int DXClass::Init(HWND hwnd, Vector2 resolution)
{

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	//DX Device, Immediate Context, Swap Chain 생성
	DXGI_SWAP_CHAIN_DESC swap_desc;
	ZeroMemory(&swap_desc, sizeof(swap_desc));

	swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_desc.BufferCount = 1;
	swap_desc.OutputWindow = hwnd;
	swap_desc.SampleDesc.Count = 1;
	swap_desc.SampleDesc.Quality = 0;
	swap_desc.BufferDesc.Width = resolution.x;
	swap_desc.BufferDesc.Height = resolution.y;
	swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_desc.Windowed = TRUE;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, featureLevels, numFeatureLevels,
		D3D11_SDK_VERSION, &swap_desc, &p_swap_chain_, &p_d3d_device_, NULL, &p_immediate_context_))) {
		return E_FAIL;
	}

	// Render Target View 생성
	ID3D11Texture2D* p_back_buffer;
	if (FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_back_buffer))) {
		return E_FAIL;
	}

	if (FAILED(p_d3d_device_->CreateRenderTargetView(p_back_buffer, NULL, &p_render_target_view_))) {
		p_back_buffer->Release();
		return E_FAIL;
	}
	p_back_buffer->Release();
	p_immediate_context_->OMSetRenderTargets(1, &p_render_target_view_, NULL);


	// Viewport 초기화
	D3D11_VIEWPORT viewport;
	viewport.Width = resolution.x;
	viewport.Height = resolution.y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	p_immediate_context_->RSSetViewports(1, &viewport);

	//Vertex Shader 생성
	tstring shader_path = PathManager::GetInstance()->GetContentPath() + _T("shader\\SimpleShader.hlsl");
	ID3DBlob* p_vs_blob;
	ID3DBlob* p_vs_error_blob;
	HRESULT hr;
	if (FAILED(hr = D3DCompileFromFile(shader_path.c_str(), NULL, NULL,
		"VS", "vs_4_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &p_vs_blob, &p_vs_error_blob)))
	{
		p_vs_error_blob->Release();
		return E_FAIL;
	}
	p_d3d_device_->CreateVertexShader(p_vs_blob->GetBufferPointer(), p_vs_blob->GetBufferSize(), NULL, &p_vs_);


	// Input Layout(Vertex Layout) 생성
	ID3D11InputLayout* p_input_layout;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT num_elements = ARRAYSIZE(layout);

	if (FAILED(p_d3d_device_->CreateInputLayout(layout, num_elements, p_vs_blob->GetBufferPointer(), p_vs_blob->GetBufferSize(), &p_input_layout)))
	{
		p_vs_blob->Release();
		return E_FAIL;
	}
	p_vs_blob->Release();
	p_immediate_context_->IASetInputLayout(p_input_layout);
	

	//Pixel Shader 생성
	ID3DBlob* p_ps_blob;
	ID3DBlob* p_ps_error_blob;
	if (FAILED(D3DCompileFromFile(shader_path.c_str(), NULL, NULL,
		"PS", "ps_4_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &p_ps_blob, &p_ps_error_blob)))
	{
		p_ps_error_blob->Release();
		return E_FAIL;
	}

	if (FAILED(p_d3d_device_->CreatePixelShader(p_ps_blob->GetBufferPointer(), p_ps_blob->GetBufferSize(), NULL, &p_ps_)))
	{
		p_ps_blob->Release();
		return E_FAIL;
	}
	p_ps_blob->Release();

	p_immediate_context_->VSSetShader(p_vs_, NULL, 0);
	p_immediate_context_->PSSetShader(p_ps_, NULL, 0);


	//Constant Buffer 생성(OnResize, OnRender 두 개)
	D3D11_BUFFER_DESC cb_on_resize_desc;
	ZeroMemory(&cb_on_resize_desc, sizeof(cb_on_resize_desc));
	cb_on_resize_desc.Usage = D3D11_USAGE_DYNAMIC;
	cb_on_resize_desc.ByteWidth = ((sizeof(cb_on_resize_desc) + 15) / 16) * 16;
	cb_on_resize_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_on_resize_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb_on_resize_desc.MiscFlags = 0;
	cb_on_resize_desc.StructureByteStride = 0;
	if (FAILED(p_d3d_device_->CreateBuffer(&cb_on_resize_desc, NULL, &p_const_buffer_on_resize_)))
	{
		return E_FAIL;
	}

	D3D11_BUFFER_DESC cb_on_render_desc;
	ZeroMemory(&cb_on_render_desc, sizeof(cb_on_render_desc));
	cb_on_render_desc.Usage = D3D11_USAGE_DYNAMIC;
	cb_on_render_desc.ByteWidth = ((sizeof(cb_on_render_desc) + 15) / 16) * 16;
	cb_on_render_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_on_render_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb_on_render_desc.MiscFlags = 0;
	cb_on_render_desc.StructureByteStride = 0;
	if (FAILED(p_d3d_device_->CreateBuffer(&cb_on_render_desc, NULL, &p_const_buffer_on_render_)))
	{
		return E_FAIL;
	}

	p_immediate_context_->VSSetConstantBuffers(0, 1, &p_const_buffer_on_resize_);
	p_immediate_context_->PSSetConstantBuffers(0, 1, &p_const_buffer_on_render_);

	//해상도를 프로젝션으로 변환해서 상수 버퍼에 쓰기
	XMMATRIX projection = XMMATRIX
	{
		2/viewport.Width ,		0,						0,	0,
		0,						2/viewport.Height ,		0,	0,
		0,						0,						0,	0,
		0,						0,						0,	1

	};
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	if (FAILED(p_immediate_context_->Map(p_const_buffer_on_resize_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource)))
	{
		return E_FAIL;
	}
	ChangeOnResizeBuffer* p_vs_const_data;
	p_vs_const_data = (ChangeOnResizeBuffer*)mapped_resource.pData;
	p_vs_const_data->projection = projection;
	p_immediate_context_->Unmap(p_const_buffer_on_resize_, 0);

	//Vertex Buffer 생성
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	buffer_desc.ByteWidth = sizeof(CustomVertex) * 65536;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	if (FAILED(p_d3d_device_->CreateBuffer(&buffer_desc, NULL, &p_vertex_buffer_))) {
		return E_FAIL;
	};

	// Set vertex buffer
	UINT stride = sizeof(CustomVertex);
	UINT offset = 0;
	p_immediate_context_->IASetVertexBuffers(0, 1, &p_vertex_buffer_, &stride, &offset);

	//Index Buffer 생성
	D3D11_BUFFER_DESC idx_buffer_desc;
	ZeroMemory(&idx_buffer_desc, sizeof(idx_buffer_desc));
	idx_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	idx_buffer_desc.ByteWidth = sizeof(float) * 65536;
	idx_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	idx_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	idx_buffer_desc.MiscFlags = 0;
	idx_buffer_desc.StructureByteStride = 0;

	if (FAILED(p_d3d_device_->CreateBuffer(&idx_buffer_desc, NULL, &p_idx_buffer_))) {
		return E_FAIL;
	}

	// Set index buffer
	idx_format_ = DXGI_FORMAT_R32_UINT;
	p_immediate_context_->IASetIndexBuffer(p_idx_buffer_, idx_format_, 0);


	// 텍스쳐 샘플러 설정
	D3D11_SAMPLER_DESC sample_desc;
	ZeroMemory(&sample_desc, sizeof(sample_desc));
	sample_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sample_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sample_desc.MinLOD = 0;
	sample_desc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(p_d3d_device_->CreateSamplerState(&sample_desc, &p_sampler_linear_))) {
		return E_FAIL;
	};

	p_immediate_context_->PSSetSamplers(0, 1, &p_sampler_linear_);
	

	ID3D11BlendState* p_blend_state;
	D3D11_BLEND_DESC blendStateDesc{};
	blendStateDesc.AlphaToCoverageEnable = FALSE;
	blendStateDesc.IndependentBlendEnable = FALSE;							//모든 렌더타겟에 대해 각각 블랜드 설정->FALSE
	blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(p_d3d_device_->CreateBlendState(&blendStateDesc, &p_blend_state)))
	{
		return E_FAIL;
	}


	p_immediate_context_->OMSetBlendState(p_blend_state, nullptr, 0xFFFFFFFF);


}




void DXClass::WriteVertexBuffer(CustomVertex* vertices, UINT vertex_count)
{
	ID3D11Buffer* p_vertex_buffer;
	UINT stride = sizeof(CustomVertex);
	UINT offset = 0;
	p_immediate_context_->IAGetVertexBuffers(0, 1, &p_vertex_buffer, &stride, &offset);

	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	if (FAILED(p_immediate_context_->Map(p_vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource)))
	{
		return;
	}
	CustomVertex* vertex_data = (CustomVertex*)mapped_resource.pData;
	for (int i = 0; i < vertex_count; i++) {
		vertex_data[i] = vertices[i];
	}
	p_immediate_context_->Unmap(p_vertex_buffer, 0);
}

void DXClass::WriteIndexBuffer(UINT* indices, UINT index_count)
{
	ID3D11Buffer* p_idx_buffer;
	DXGI_FORMAT idx_format = idx_format_;
	p_immediate_context_->IAGetIndexBuffer(&p_idx_buffer, &idx_format, 0);
	D3D11_MAPPED_SUBRESOURCE idx_mapped_resource;

	if (p_idx_buffer == NULL || FAILED(p_immediate_context_->Map(p_idx_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_mapped_resource)))
	{
		return;
	}
	UINT* idx_data = (UINT*)idx_mapped_resource.pData;
	for (int i = 0; i < index_count; i++) {
		idx_data[i] = indices[i];
	}
	p_immediate_context_->Unmap(p_idx_buffer, 0);
}
void DXClass::WriteConstantBufferOnResize(Vector2 resolution)
{
	XMMATRIX projection = XMMATRIX
	{
		2 / resolution.x ,		0,						0,	0,
		0,						2 / resolution.y ,		0,	0,
		0,						0,						0,	0,
		0,						0,						0,	1

	};
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	if (FAILED(p_immediate_context_->Map(p_const_buffer_on_resize_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource)))
	{
		return;
	}
	ChangeOnResizeBuffer* p_vs_const_data;
	p_vs_const_data = (ChangeOnResizeBuffer*)mapped_resource.pData;
	p_vs_const_data->projection = projection;
	p_immediate_context_->Unmap(p_const_buffer_on_resize_, NULL);
}

void DXClass::WriteConstantBufferOnRender(BOOL use_texture, XMFLOAT4 mesh_color)
{
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	if (FAILED(p_immediate_context_->Map(p_const_buffer_on_render_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource)))
	{
		return;
	}
	ChangeOnRenderBuffer* p_const_data;
	p_const_data = (ChangeOnRenderBuffer*)mapped_resource.pData;
	p_const_data->use_texture = use_texture;
	p_const_data->mesh_color = mesh_color;
	p_immediate_context_->Unmap(p_const_buffer_on_render_, NULL);
}

void DXClass::ResetResolution(Vector2 new_resolution)
{
	//==============================
	// 메인 Render Target View 재초기화
	//===============================
	p_render_target_view_->Release();
	p_swap_chain_->ResizeBuffers(1, new_resolution.x, new_resolution.y, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	// Render Target View 생성
	ID3D11Texture2D* p_back_buffer;
	if (FAILED(p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_back_buffer))) {
		return;
	}

	if (FAILED(p_d3d_device_->CreateRenderTargetView(p_back_buffer, NULL, &p_render_target_view_))) {
		p_back_buffer->Release();
		return;
	}
	p_back_buffer->Release();
	p_immediate_context_->OMSetRenderTargets(1, &p_render_target_view_, NULL);


	// Viewport 초기화
	D3D11_VIEWPORT viewport;
	viewport.Width = new_resolution.x;
	viewport.Height = new_resolution.y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	p_immediate_context_->RSSetViewports(1, &viewport);

	//==========================================
	// 텍스트 렌더링용 Render Target View 재초기화
	//==========================================
	if (p_d2d_rt_) {
		p_d2d_rt_->Release();
		p_d2d_rt_ = nullptr;
	}
	if (p_text_render_target_) {
		p_text_render_target_->Release();
		p_text_render_target_ = nullptr;
	}
	if (FAILED(p_swap_chain_->GetBuffer(0, IID_PPV_ARGS(&p_d2d_rt_)))) {
		return;
	};
	D2D1_RENDER_TARGET_PROPERTIES d2d_rt_props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0);
	if (FAILED(p_d2d1_factory_->CreateDxgiSurfaceRenderTarget(p_d2d_rt_, &d2d_rt_props, &p_text_render_target_))) {
		return;
	}


}

void DXClass::InitD2D1()
{

	//Release로 해제해줘야 하는 리소스임.
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, D2D1_FACTORY_OPTIONS(), &p_d2d1_factory_))) {
		return;
	}

	if (FAILED(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&p_dwrite_factory_)
	)))
	{
		return;
	}

	if (FAILED(p_swap_chain_->GetBuffer(0, IID_PPV_ARGS(&p_d2d_rt_)))) {
		return;
	};
	D2D1_RENDER_TARGET_PROPERTIES d2d_rt_props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0);
	if (FAILED(p_d2d1_factory_->CreateDxgiSurfaceRenderTarget(p_d2d_rt_, &d2d_rt_props, &p_text_render_target_))) {
		return;
	}


	//폰트 기본값 설정
	SetTextFormat(_T("둥근모꼴"), _T("ko-kr"), 20.0f, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	
}

void DXClass::SetTextFormat(tstring font_name, tstring font_locale, UINT font_size,
	DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight,
	DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment)
{
	if (p_text_format_) {
		p_text_format_->Release();
		p_text_format_ = nullptr;
	}
	if (p_trim_sign_) {
		p_trim_sign_->Release();
		p_trim_sign_ = nullptr;
	}
	//글꼴, 두께, 스트레치, 스타일 및 로캘 지정
	if (FAILED(p_dwrite_factory_->CreateTextFormat
	(	font_name.c_str()
		, NULL
		, font_weight
		, font_style
		, DWRITE_FONT_STRETCH_NORMAL
		, font_size
		, font_locale.c_str()
		, &p_text_format_
	)
	)) {
		return;
	}
	//정렬 설정
	if (FAILED(p_text_format_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER))) {
		return;
	}
	if (FAILED(p_text_format_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER))) {
		return;
	}

	p_dwrite_factory_->CreateEllipsisTrimmingSign(p_text_format_, &p_trim_sign_);
	p_text_format_->SetTrimming(&trim_options_, p_trim_sign_);
}

void DXClass::RenderText(const TCHAR* text, UINT length, Vector2 pos, Vector2 scale, D2D1::ColorF color)
{
	D2D1_RECT_F layout_rect;

	ID2D1SolidColorBrush* p_brush;
	if (FAILED(p_text_render_target_->CreateSolidColorBrush(
		D2D1::ColorF(color),
		&p_brush
	))) {
		return;
	}
	FLOAT dpi_scale_x = 1;
	FLOAT dpi_scale_y = 1;
	layout_rect = D2D1::RectF(
		static_cast<FLOAT>(pos.x - scale.x/2.f) / dpi_scale_x,
		static_cast<FLOAT>(pos.y - scale.y/2.f) / dpi_scale_y,
		static_cast<FLOAT>(pos.x+scale.x/2.f) / dpi_scale_x,
		static_cast<FLOAT>(pos.y+scale.y/2.f) / dpi_scale_y
	);

	p_text_render_target_->BeginDraw();
	p_text_render_target_->SetTransform(D2D1::IdentityMatrix());
	p_text_render_target_->DrawTextW(
		text,
		length,
		p_text_format_,
		layout_rect,
		p_brush
	);
	p_text_render_target_->EndDraw();


	p_brush->Release();
}
