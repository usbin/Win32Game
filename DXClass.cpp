#include "DXClass.h"
#include "PathManager.h"
#include "Core.h"
#include "Tile.h"
#include "RealObjectSprite.h"
#include "Texture.h"
DXClass::DXClass()
	: p_d3d_device_(nullptr)
	, p_immediate_context_(nullptr)
	, p_swap_chain_(nullptr)
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

	if (p_text_render_target_) p_text_render_target_->Release();

	for (int i = 0; i < (int)RENDER_LAYER::END; i++) {
		if (render_layer_targets_[i]) render_layer_targets_[i]->Release();
		if (render_layer_textures_[i]) render_layer_textures_[i]->Release();
		if (render_layer_resource_views_[i]) render_layer_resource_views_[i]->Release();
		if (text_bitmaps_[i]) text_bitmaps_[i]->Release();
	
	}
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

	////Stencil View 생성
	//ID3D11Texture2D* p_stencil = NULL;
	//ID3D11ShaderResourceView* p_stencil_rv = nullptr;
	//tstring texture_path = PathManager::GetInstance()->GetContentPath() + _T("texture\\PlayerLightMask.png");
	//D3DX11_IMAGE_LOAD_INFO texture_info;
	//ZeroMemory(&texture_info, sizeof(texture_info));
	//texture_info.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//texture_info.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//texture_info.Usage = D3D11_USAGE_DEFAULT;
	//texture_info.CpuAccessFlags = 0;
	//texture_info.MiscFlags = 0;
	//texture_info.MipLevels = 1;
	//

	//HRESULT hr;
	//ID3D11Resource* res;
	//if (FAILED(hr = D3DX11CreateTextureFromFile(p_d3d_device_, texture_path.c_str(), &texture_info, NULL, &res, NULL))) {
	//	return E_FAIL;
	//}
	//res->QueryInterface<ID3D11Texture2D>(&p_stencil);

	//D3D11_DEPTH_STENCIL_DESC stencil_desc;
	//ZeroMemory(&stencil_desc, sizeof(stencil_desc));
	////Stencil View 상태 생성
	//stencil_desc.DepthEnable = false;
	//stencil_desc.StencilEnable = true;
	//stencil_desc.StencilReadMask = 0xFF;
	//stencil_desc.StencilWriteMask = 0xFF;
	//// Stencil operations if pixel is front-facing
	//stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	//stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//// Stencil operations if pixel is back-facing
	//stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	//stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//// Create depth stencil state
	//hr = p_d3d_device_->CreateDepthStencilState(&stencil_desc, &p_stencil_state_);

	////Stencil View 생성
	//D3D11_DEPTH_STENCIL_VIEW_DESC stencil_view_desc;
	//ZeroMemory(&stencil_view_desc, sizeof(stencil_view_desc));
	//stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//stencil_view_desc.Texture2D.MipSlice = 0;
	//// Create the depth stencil view
	//hr = p_d3d_device_->CreateDepthStencilView(p_stencil, // Depth stencil texture
	//	&stencil_view_desc, // Depth stencil desc
	//	&p_stencil_view_);  // [out] Depth stencil view

	p_back_buffer->Release();
	p_immediate_context_->OMSetRenderTargets(1, &p_render_target_view_, NULL);

	HRESULT hr;

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
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;		//RGB 혼합 계수
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;			//RGB 혼합 연산자
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;			//A 혼합 계수
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;		//A 혼합 연산자
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(p_d3d_device_->CreateBlendState(&blendStateDesc, &p_blend_state)))
	{
		return E_FAIL;
	}


	p_immediate_context_->OMSetBlendState(p_blend_state, nullptr, 0xFFFFFFFF);


}

int DXClass::InitRenderLayers(Vector2 resolution)
{
	// 렌더 레이어용 텍스쳐, 렌더 타겟 뷰(출력용), 리소스 뷰(입력용) 생성
	ID3D11Texture2D* layer1_texture;
	ID3D11Texture2D* layer2_texture;
	ID3D11Texture2D* layer3_texture;
	ID3D11RenderTargetView* layer1_target_view;
	ID3D11RenderTargetView* layer2_target_view;
	ID3D11RenderTargetView* layer3_target_view;
	ID3D11ShaderResourceView* layer1_resource_view;
	ID3D11ShaderResourceView* layer2_resource_view;
	ID3D11ShaderResourceView* layer3_resource_view;

	D3D11_TEXTURE2D_DESC layer_texture_desc;
	D3D11_RENDER_TARGET_VIEW_DESC layer_target_view_desc;
	D3D11_SHADER_RESOURCE_VIEW_DESC layer_resource_view_desc;

	ZeroMemory(&layer_texture_desc, sizeof(layer_texture_desc));
	layer_texture_desc.Width = resolution.x;
	layer_texture_desc.Height = resolution.y;
	layer_texture_desc.MipLevels = 1;
	layer_texture_desc.ArraySize = 1;
	layer_texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	layer_texture_desc.SampleDesc.Count = 1;
	layer_texture_desc.Usage = D3D11_USAGE_DEFAULT;
	layer_texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	layer_texture_desc.CPUAccessFlags = 0;
	layer_texture_desc.MiscFlags = 0;
	if (FAILED(p_d3d_device_->CreateTexture2D(&layer_texture_desc, NULL, &layer1_texture))) return E_FAIL;
	if (FAILED(p_d3d_device_->CreateTexture2D(&layer_texture_desc, NULL, &layer2_texture))) return E_FAIL;
	if (FAILED(p_d3d_device_->CreateTexture2D(&layer_texture_desc, NULL, &layer3_texture))) return E_FAIL;

	ZeroMemory(&layer_target_view_desc, sizeof(layer_target_view_desc));
	layer_target_view_desc.Format = layer_texture_desc.Format;
	layer_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	layer_target_view_desc.Texture2D.MipSlice = 0;
	p_d3d_device_->CreateRenderTargetView(layer1_texture, &layer_target_view_desc, &layer1_target_view);
	p_d3d_device_->CreateRenderTargetView(layer2_texture, &layer_target_view_desc, &layer2_target_view);
	p_d3d_device_->CreateRenderTargetView(layer3_texture, &layer_target_view_desc, &layer3_target_view);

	ZeroMemory(&layer_resource_view_desc, sizeof(layer_resource_view_desc));
	layer_resource_view_desc.Format = layer_texture_desc.Format;
	layer_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	layer_resource_view_desc.Texture2D.MostDetailedMip = 0;
	layer_resource_view_desc.Texture2D.MipLevels = 1;
	if (FAILED(p_d3d_device_->CreateShaderResourceView(layer1_texture, &layer_resource_view_desc, &layer1_resource_view))) return E_FAIL;
	if (FAILED(p_d3d_device_->CreateShaderResourceView(layer2_texture, &layer_resource_view_desc, &layer2_resource_view))) return E_FAIL;
	if (FAILED(p_d3d_device_->CreateShaderResourceView(layer3_texture, &layer_resource_view_desc, &layer3_resource_view))) return E_FAIL;

	render_layer_targets_[(int)RENDER_LAYER::GROUND] = layer1_target_view;
	render_layer_targets_[(int)RENDER_LAYER::PLAYER] = layer2_target_view;
	render_layer_targets_[(int)RENDER_LAYER::TOP] = layer3_target_view;
	render_layer_textures_[(int)RENDER_LAYER::GROUND] = layer1_texture;
	render_layer_textures_[(int)RENDER_LAYER::PLAYER] = layer2_texture;
	render_layer_textures_[(int)RENDER_LAYER::TOP] = layer3_texture;
	render_layer_resource_views_[(int)RENDER_LAYER::GROUND] = layer1_resource_view;
	render_layer_resource_views_[(int)RENDER_LAYER::PLAYER] = layer2_resource_view;
	render_layer_resource_views_[(int)RENDER_LAYER::TOP] = layer3_resource_view;
	
	

	return S_OK;
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
void DXClass::RenderLayer(RENDER_LAYER layer)
{
	ID3D11Texture2D* texture = render_layer_textures_[(int)layer];
	Vector2 resolution = Core::GetInstance()->get_resolution();

	//점 좌표
	const int vertice_count = 4;
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(0,				0,				0.f), XMFLOAT2(0, 0)},
		{ XMFLOAT3(resolution.x,	0,				0.f), XMFLOAT2(1, 0)},
		{ XMFLOAT3(resolution.x,	resolution.y,	0.f), XMFLOAT2(1, 1)},
		{ XMFLOAT3(0,				resolution.y,	0.f), XMFLOAT2(0, 1)}
	};

	//면 인덱스
	const int plane_indices_count = 6;
	UINT plane_indices[] = {
		0, 1, 2,

		2, 3, 0
	};
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	//Plane Index Buffer 채우기
	DXClass::GetInstance()->WriteIndexBuffer(plane_indices, plane_indices_count);
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(TRUE, XMFLOAT4(0, 0, 0, 0));
	ID3D11RenderTargetView* layer_target_view = DXClass::GetInstance()->get_render_layer_target(layer);
	p_immediate_context_->OMSetRenderTargets(1, &p_render_target_view_, NULL);
	p_immediate_context_->PSSetShaderResources(0, 1, &render_layer_resource_views_[(int)layer]);
	// Set primitive topology
	p_immediate_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context_->DrawIndexed(6, 0, 0);
}

void DXClass::RenderTextLayer(RENDER_LAYER layer)
{
	p_text_render_target_->BeginDraw();
	ID2D1Bitmap* bitmap;
	text_bitmaps_[(int)layer]->GetBitmap(&bitmap);
	p_text_render_target_->DrawBitmap(bitmap);
	p_text_render_target_->EndDraw();
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
	D2D1_RENDER_TARGET_PROPERTIES d2d_rt_props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0);
	if (FAILED(p_d2d1_factory_->CreateDxgiSurfaceRenderTarget(p_d2d_rt_, &d2d_rt_props, &p_text_render_target_))) {
		return;
	}
	for (int i = 0; i < (int)RENDER_LAYER::END; i++) {
		D2D1_PIXEL_FORMAT pixel_format;
		pixel_format.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		pixel_format.format = DXGI_FORMAT_R8G8B8A8_UNORM;
		if (FAILED(p_text_render_target_->CreateCompatibleRenderTarget(p_text_render_target_->GetSize(), p_text_render_target_->GetPixelSize(), pixel_format, &text_bitmaps_[i]))) return;

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
	D2D1_RENDER_TARGET_PROPERTIES d2d_rt_props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM , D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0);
	if (FAILED(p_d2d1_factory_->CreateDxgiSurfaceRenderTarget(p_d2d_rt_, &d2d_rt_props, &p_text_render_target_))) {
		return;
	}
	for (int i = 0; i < (int)RENDER_LAYER::END; i++) {
		D2D1_PIXEL_FORMAT pixel_format;
		pixel_format.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		pixel_format.format = DXGI_FORMAT_R8G8B8A8_UNORM;
		if (FAILED(p_text_render_target_->CreateCompatibleRenderTarget(p_text_render_target_->GetSize(), p_text_render_target_->GetPixelSize(), pixel_format, &text_bitmaps_[i]))) return;


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
	if (FAILED(p_text_format_->SetTextAlignment(text_alighment))) {
		return;
	}
	if (FAILED(p_text_format_->SetParagraphAlignment(paragraph_alignment))) {
		return;
	}

	p_dwrite_factory_->CreateEllipsisTrimmingSign(p_text_format_, &p_trim_sign_);
	p_text_format_->SetTrimming(&trim_options_, p_trim_sign_);
}

void DXClass::RenderText(const TCHAR* text, UINT length, Vector2 pos, Vector2 scale, D2D1::ColorF color, RENDER_LAYER layer)
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
		static_cast<FLOAT>(pos.x) / dpi_scale_x,
		static_cast<FLOAT>(pos.y) / dpi_scale_y,
		static_cast<FLOAT>(pos.x+scale.x) / dpi_scale_x,
		static_cast<FLOAT>(pos.y+scale.y) / dpi_scale_y
	);
	text_bitmaps_[(int)layer]->BeginDraw();
	text_bitmaps_[(int)layer]->SetTransform(D2D1::IdentityMatrix());
	text_bitmaps_[(int)layer]->DrawTextW(
		text,
		length,
		p_text_format_,
		layout_rect,
		p_brush
	);
	text_bitmaps_[(int)layer]->EndDraw();


	p_brush->Release();
}

void DXClass::SaveMapfileToPng(const std::vector<GObject*>& tiles, Vector2 size)
{
	//1.타일맵을 출력할 쓰기용 텍스쳐와 렌더타겟뷰 생성
	ID3D11Texture2D* tilemap;
	ID3D11RenderTargetView* render_target_view_tilemap;

	D3D11_TEXTURE2D_DESC texture_desc;
	D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;

	ZeroMemory(&texture_desc, sizeof(texture_desc));
	texture_desc.Width = size.x;
	texture_desc.Height = size.y;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texture_desc.SampleDesc.Count = 1;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET;
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	if(FAILED(p_d3d_device_->CreateTexture2D(&texture_desc, NULL, &tilemap))) return;

	ZeroMemory(&render_target_view_desc, sizeof(render_target_view_desc));
	render_target_view_desc.Format = texture_desc.Format;
	render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	render_target_view_desc.Texture2D.MipSlice = 0;

	p_d3d_device_->CreateRenderTargetView(tilemap, &render_target_view_desc, &render_target_view_tilemap);

	//2. 쉐이더의 상수버퍼(해상도 저장됨)에 임시 해상도(타일맵의 크기) 입력, 출력 타겟 변경
	WriteConstantBufferOnResize(size);
	p_immediate_context_->OMSetRenderTargets(1, &render_target_view_tilemap, NULL);
	D3D11_VIEWPORT viewport;
	viewport.Width = size.x;
	viewport.Height = size.y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	p_immediate_context_->RSSetViewports(1, &viewport);

	//3. 출력
	for (UINT i = 0; i < tiles.size(); i++) {
		Tile* tile = dynamic_cast<Tile*>(tiles[i]);
		if (tile->get_render_component()){

			RealObjectSprite* tile_sprite = dynamic_cast<RealObjectSprite*>( tile->get_render_component()->get_sprite());
			if (tile_sprite)
			DrawTextureToRenderTarget(p_d3d_device_, tiles[i]->get_pos() - tiles[i]->get_scale() / 2.f, tiles[i]->get_scale(), tile_sprite->get_base_pos(), tile_sprite->get_scale(), tile_sprite->get_texture(), render_target_view_tilemap);
		}
	}
	p_immediate_context_->DrawIndexed(1, 0, 0);

	//4. PNG 파일로 저장.
	TCHAR file_path[256] = _T("");
	OPENFILENAME ofn = {};
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = Core::GetInstance()->get_main_hwnd();
	ofn.lpstrFilter = _T("PNG\0*.png\0");
	ofn.lpstrFile = file_path;
	ofn.nMaxFile = 256;
	if (GetSaveFileName(&ofn)) {
		D3DX11SaveTextureToFile(p_immediate_context_, tilemap, D3DX11_IMAGE_FILE_FORMAT::D3DX11_IFF_PNG, file_path);

	}

	//5. 해상도와 출력 타겟 되돌리기
	WriteConstantBufferOnResize(Core::GetInstance()->get_resolution());
	viewport.Width = Core::GetInstance()->get_resolution().x;
	viewport.Height = Core::GetInstance()->get_resolution().y;
	p_immediate_context_->RSSetViewports(1, &viewport);
	p_immediate_context_->OMSetRenderTargets(1, &p_render_target_view_, NULL);
	tilemap->Release();
	render_target_view_tilemap->Release();
	
}
