
#include "SOC_Graphics.h"


SOC_Graphics::SOC_Graphics()
{
	factory = NULL;
	renderTarget = NULL;


	brush = NULL;
}

SOC_Graphics::~SOC_Graphics()
{
	if (factory)
	{
		factory->Release();
	}

	if (renderTarget)
	{
		renderTarget->Release();
	}

	if (brush)
	{
		brush->Release();
	}
}

bool SOC_Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (res != S_OK)
	{
		return false;
	}

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	windowSize = SOC_Vector2((float)rect.right, (float)rect.bottom);

	if(res != S_OK)
	{
		return false;
	}

	D2D1::ColorF defaultColor = (0, 0, 0, 1);

	res = renderTarget->CreateSolidColorBrush(defaultColor, &brush);

	if (res != S_OK)
	{
		return false;
	}


	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 20;

	// Create a Direct2D factory.
	res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	if (res == S_OK)
	{

		// Create a DirectWrite factory.
		res = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	}
	else
	{
		return false;
	}
	if (res == S_OK)
	{
		// Create a DirectWrite text format object.
		res = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat
		);
	}
	else
	{
		return false;
	}
	if (res == S_OK)
	{
		// Center the text horizontally and vertically.
		//m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

		//m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}
	else
	{
		return false;
	}

	if (res != S_OK)
	{
		return false;
	}

	return true;
}

void SOC_Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void SOC_Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);

}

void SOC_Graphics::DrawRectangle(float left, float top, float right, float bottom, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	//renderTarget->DrawRectangle(D2D1::RectF(x, y, width, height), brush, 3.0f);
	renderTarget->FillRectangle(D2D1::RectF(left, top, right, bottom), brush);
}


SOC_Vector2 SOC_Graphics::GetCursorPosFromGraphics()
{
	POINT actualCursorPos;
	GetCursorPos(&actualCursorPos);
	cursorPos = SOC_Vector2(actualCursorPos.x + windowPos.xVal, actualCursorPos.y + windowPos.yVal);
	return cursorPos;
}

void SOC_Graphics::RenderString(std::string newString, SOC_Vector2 pos)
{
	WCHAR *textMsg;

	textMsg = new WCHAR[newString.size()];

	for (int i = 0; i < newString.size(); i++)
	{
		textMsg[i] = newString[i];
	}

	// Retrieve the size of the render target.
	D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();

	//renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	renderTarget->DrawText(
		textMsg,
		newString.size(),
		m_pTextFormat,
		D2D1::RectF(pos.xVal, pos.yVal, renderTargetSize.width, renderTargetSize.height),
		brush
	);

	
}

