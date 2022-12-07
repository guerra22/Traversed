#ifndef __PANEL_LIBRARY_H_
#define __PANEL_LIBRARY_H_

#include "UiPanel.h"

//#include "LibraryManager.h"

struct FileSystemProperties;
class LibraryFolder;

class PanelLibrary : public UiPanel
{
public:
	PanelLibrary(bool enabled = false);
	~PanelLibrary();

	void Start();

	void Update();

private:
	void Hierarchy();
	void BoxView();

private:
	FileSystemProperties* fsIntance = nullptr;
	LibraryFolder* currentFolder = nullptr;
};


#endif