#pragma once
struct Vector2 {
	float x;
	float y;
public:
	Vector2()
		: x(0)
		, y(0) {};
	Vector2(float _x, float _y)
		: x(_x)
		, y(_y) {};
	Vector2(double _x, double _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y)) {};
	Vector2(int _x, int _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y)) {};
	Vector2(const POINT& pt)
		: x(static_cast<float>(pt.x))
		, y(static_cast<float>(pt.y)) {};
	Vector2(UINT _x, UINT _y)
		: x(static_cast<float>(_x))
		, y(static_cast<float>(_y)){};
	Vector2(LONG _x, LONG _y)
		: x(static_cast<int>(_x))
		, y(static_cast<int>(_y)) {};
	float Length() {
		return sqrtf(x * x + y * y);
	}
	Vector2& Normalize() {
		if (abs(x) < FLT_EPSILON && abs(y) < FLT_EPSILON) {
			return *this;
		}
		x /= Length();
		y /= Length();
		return *this;
	}
	Vector2 operator+(const Vector2& o_v) {
		return Vector2{ x + o_v.x, y + o_v.y };
	}
	void operator+=(const Vector2& o_v) {
		x += o_v.x;
		y += o_v.y;
	}
	
	Vector2 operator+(const Vector2& o_v) const {
		return Vector2{ x + o_v.x, y + o_v.y };
	}
	Vector2 operator-(const Vector2& o_v) {
		return Vector2{ x - o_v.x, y - o_v.y };
	}
	Vector2 operator-(const Vector2& o_v) const {
		return Vector2{ x - o_v.x, y - o_v.y };
	}
	void operator-=(const Vector2& o_v) {
		x -= o_v.x;
		y -= o_v.y;
	}
	Vector2 operator*(int num) {
		return Vector2{ x * num, y * num };
	}
	Vector2 operator*(float num) {
		return Vector2{ x * num, y * num };
	}
	Vector2 operator*(const Vector2& o_v) {
		return Vector2{ x * o_v.x, y * o_v.y };
	}
	Vector2 operator/(const Vector2& o_v) const {
		return Vector2{ x / o_v.x, y / o_v.y };
	}
	Vector2 operator/(int num) {
		return Vector2{ x / num, y / num };
	}
	Vector2 operator/(double num) const {
		return Vector2{ x / num, y / num };
	}
	Vector2 operator/(float num) {
		return Vector2{ x / num, y / num };
	}
	bool operator<(const Vector2& o_v) {
		return x < o_v.x&& y < o_v.y;
	}
	bool operator<=(const Vector2& o_v) {
		return x <= o_v.x&& y <= o_v.y;
	}
	bool operator>(const Vector2& o_v) {
		return x > o_v.x && y > o_v.y;
	}
	bool operator>=(const Vector2& o_v) {
		return x >= o_v.x && y >= o_v.y;
	}
	bool operator!=(const Vector2& o_v) {
		return x != o_v.x || y != o_v.y;
	}
	bool operator==(const Vector2& o_v) {
		return x == o_v.x && y == o_v.y;
	}

};

struct Rect2 {
	float left;
	float top;
	float right;
	float bottom;
	Rect2()
		: left(0)
		, top(0)
		, right(0)
		, bottom(0) {};
	Rect2(float _left, float _top, float _right, float _bottom)
		: left(_left)
		, top(_top)
		, right(_right)
		, bottom(_bottom) {};
	Rect2(int _left, int _top, int _right, int _bottom)
		: left(static_cast<float>(_left))
		, top(static_cast<float>(_top))
		, right(static_cast<float>(_right))
		, bottom(static_cast<float>(_bottom)) {};

};

union ARGB {
	struct {
		BYTE a;
		BYTE r;
		BYTE g;
		BYTE b;
	};

	ARGB(DWORD _argb) {
		b = _argb & 0xFF;
		g = _argb >> 8 & 0xFF;
		r = _argb >> 16 & 0xFF;
		a = _argb >> 24 & 0xFF;
	};
};


union CollisionId {
	struct {
		UINT collider1_id;
		UINT collider2_id;
	};
	ULONGLONG Id;
};

//=======================
// 쉐이더에 쓰이는 구조체
//========================
//struct ColoredVertex {
//	XMFLOAT3 position;
//	XMFLOAT4 color;
//};
//struct TexturedVertex {
//	XMFLOAT3 position;
//	XMFLOAT2 texture_position;
//};

//Shader에서 읽을 때 16byte씩 맞춰줘야 함.
struct CustomVertex {
	XMFLOAT3 position;
	XMFLOAT2 texture_position;
};

// Constant Buffer들
struct ChangeOnResizeBuffer {
	XMMATRIX projection;
};
struct ChangeOnRenderBuffer {
	XMFLOAT4 mesh_color;
	BOOL use_texture;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
