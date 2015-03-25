#ifndef EDITORAPP_H
#define EDITORAPP_H

#include <RfCore.h>

class EditorApp : D3DApp
{
public:
	EditorApp(HWND wnd) : D3DApp(wnd)
	{

	}
	~EditorApp()
	{
	}

	virtual bool Init();

	virtual void OnResize(unsigned int width, unsigned int height);

	virtual void UpdateScene(float dt);

	virtual void DrawScene();


private:
	POINT mLastMousePos;

	RenderFish::Scene mScene;
};

#endif // EDITORAPP_H