#include <hge.h>
#include <hgegui.h>
#include <gfxfont.h>
#include <hgecolor.h>

class MenuItem : public hgeGUIObject
{
public:
	MenuItem(int id, float x, float y, float delay, wchar_t *title);

	virtual void Render();
	virtual void Update(float dt);

	virtual void Enter();
	virtual void Leave();
	virtual bool IsDone();
	virtual void Focus(bool bFocused);
	virtual void MouseOver(bool bOver);

	virtual bool MouseLButton(bool bDown);
	virtual bool KeyClick(int key, int chr);

private:
	GfxFont		*fnt;
	float		delay;
	wchar_t		*title;

	hgeColor	scolor, dcolor, scolor2, dcolor2, sshadow, dshadow;
	hgeColor	color, shadow;
	float		soffset, doffset, offset;
	float		timer, timer2;
};