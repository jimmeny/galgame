#ifndef GDIFONT_H
#define GDIFONT_H

#include <hgesprite.h>
#include <atlbase.h>
#include <stdio.h>

__inline float _floor(float f)
{
	static int _n;
	_asm fld f
	_asm fistp _n
	return (float)_n;
}
class GfxFont
{
public:
	static const unsigned char g_byAlphaLevel[65];
	GfxFont(const wchar_t* lpsFontName, int nFaceSize, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bAntialias = TRUE);
	~GfxFont(void);
public:
	virtual void Print( float x, float y, const wchar_t *format, ... );
	virtual void    Render(float x, float y, const wchar_t* text );

	virtual void    SetColor( DWORD dwColor, int i = -1 );
	virtual DWORD    GetColor( int i = 0 );

	virtual SIZE    GetTextSize( const wchar_t* text );

	virtual wchar_t    GetCharacterFromPos( const wchar_t* text, float pixel_x, float pixel_y);

	virtual void    SetKerningWidth( float kerning );
	virtual void    SetKerningHeight( float kerning );

	virtual float    GetKerningWidth();
	virtual float    GetKerningHeight();

	virtual float    GetFontSize();

private:
	unsigned int    GetGlyphByCharacter( wchar_t c );
	inline float    GetWidthFromCharacter( wchar_t c, bool original = false );
	inline void        CacheCharacter(unsigned int idx, wchar_t c);

	typedef struct tagEngineFontGlyph
	{
		HTEXTURE    t;
		float        w;
		float        h;
		float        x;
		float        y;
		float        c;
	}TENGINEFONTGLYPH;

	static const unsigned int font_count = 0xFFFF;
	TENGINEFONTGLYPH    m_Glyphs[font_count];
	UINT                m_nAntialias;
	LONG                m_nAscent;
	DWORD                m_dwFontColor;
	float                m_nFontSize;
	float                m_nKerningWidth;
	float                m_nKerningHeight;

	HGE*                m_pHGE;
	hgeSprite*            m_pSprite;

	HDC                    m_hMemDC;
	HFONT                m_hFont;
};




#endif//GDIFONT_H