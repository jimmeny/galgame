#include "menu.h"

MenuItem::MenuItem(int _id, float _x, float _y, float _delay, wchar_t *_title)
{
	float w;
	
	id=_id;
	fnt = new GfxFont(L"Microsoft YaHei",20);

	delay=_delay;
	title=_title;

	color.SetHWColor(0xFFFFE060);
	shadow.SetHWColor(0x30000000);

	offset=0.0f;
	timer=-1.0f;
	timer2=-1.0f;

	bStatic=false;
	bVisible=true;
	bEnabled=true;

	SIZE s;
	s=fnt->GetTextSize(title);
	rect.Set(_x-s.cx/2, _y, _x+s.cx/2, _y+s.cy);
}

void MenuItem::Render()
{
	fnt->SetColor(shadow.GetHWColor());
	fnt->Render(rect.x1+offset+3, rect.y1+3, title);
	fnt->SetColor(color.GetHWColor());
	fnt->Render(rect.x1-offset, rect.y1-offset, title);
}

void MenuItem::Update(float dt)
{
	if(timer2 != -1.0f)
	{
		timer2+=dt;
		if(timer2 >= delay+0.1f)
		{
			color=scolor2+dcolor2;
			shadow=sshadow+dshadow;
			offset=0.0f;
			timer2=-1.0f;
		}
		else
		{
			if(timer2 < delay) { color=scolor2; shadow=sshadow; }
			else { color=scolor2+dcolor2*(timer2-delay)*10; shadow=sshadow+dshadow*(timer2-delay)*10; }
		}
	}
	else if(timer != -1.0f)
	{
		timer+=dt;
		if(timer >= 0.2f)
		{
			color=scolor+dcolor;
			offset=soffset+doffset;
			timer=-1.0f;
		}
		else
		{
			color=scolor+dcolor*timer*5;
			offset=soffset+doffset*timer*5;
		}
	}
}

void MenuItem::Enter()
{
	hgeColor tcolor2;

	scolor2.SetHWColor(0x00FFE060);
	tcolor2.SetHWColor(0xFFFFE060);
	dcolor2=tcolor2-scolor2;

	sshadow.SetHWColor(0x00000000);
	tcolor2.SetHWColor(0x30000000);
	dshadow=tcolor2-sshadow;

	timer2=0.0f;
}

void MenuItem::Leave()
{
	hgeColor tcolor2;

	scolor2.SetHWColor(0xFFFFE060);
	tcolor2.SetHWColor(0x00FFE060);
	dcolor2=tcolor2-scolor2;

	sshadow.SetHWColor(0x30000000);
	tcolor2.SetHWColor(0x00000000);
	dshadow=tcolor2-sshadow;

	timer2=0.0f;
}

// This method is called to test whether the control
// have finished it's Enter/Leave animation
bool MenuItem::IsDone()
{
	if(timer2==-1.0f)
		return true;
	else
		return false;
}

// This method is called when the control
// receives or loses keyboard input focus
void MenuItem::Focus(bool bFocused)
{
	hgeColor tcolor;
	
	if(bFocused)
	{
		scolor.SetHWColor(0xFFFFE060);
		tcolor.SetHWColor(0xFFFFFFFF);
		soffset=0;
		doffset=4;
	}
	else
	{
		scolor.SetHWColor(0xFFFFFFFF);
		tcolor.SetHWColor(0xFFFFE060);
		soffset=4;
		doffset=-4;
	}

	dcolor=tcolor-scolor;
	timer=0.0f;
}

// This method is called to notify the control
// that the mouse cursor has entered or left it's area
void MenuItem::MouseOver(bool bOver)
{
	if(bOver)
		gui->SetFocus(id);
}

// This method is called to notify the control
// that the left mouse button state has changed.
// If it returns true - the caller will receive
// the control's ID
bool MenuItem::MouseLButton(bool bDown)
{
	if(!bDown)
	{
		offset=4;
		return true;
	}
	else 
	{
		offset=0;
		return false;
	}
}

bool MenuItem::KeyClick(int key, int chr)
{
	if(key==HGEK_ENTER || key==HGEK_SPACE)
	{
		MouseLButton(true);
		return MouseLButton(false);
	}

	return false;
}
