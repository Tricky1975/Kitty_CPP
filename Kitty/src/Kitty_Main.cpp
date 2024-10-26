// Lic:
// Kitty
// CLI Syntax Highlight Utility
// 
// 
// 
// (c) Jeroen P. Broks, 2019, 2020, 2023, 2024
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// Please note that some references to data like pictures or audio, do not automatically
// fall under this licenses. Mostly this is noted in the respective files.
// 
// Version: 24.10.05
// EndLic

#include <SlyvQCol.hpp>
#include <SlyvString.hpp>
#include <SlyvStream.hpp>
#include <SlyvDirry.hpp>

#include <Kitty_High.hpp>
#include <High_Headers.hpp>

using namespace Slyvina;
using namespace Slyvina::Units;
using namespace Slyvina::Kitty;

static auto slin{ true };
static void ViewFile(String a) {
	try {
		auto arg{ ChReplace(Dirry(a),'\\','/') };//= Dirry.AD(a).Replace("\\", "/");
		QCol->Doing("Reading", arg); _KittyHigh::PageBreak();
		auto src = FLoadString(arg);
		auto eoln = EOLNType(arg);
		// QCol->Doing("EOLN", eoln); // didn't work anyway
		//QCol->OriCol();
		auto ext = Lower(ExtractExt(arg));
		auto wf{ "WF:" + StripDir(arg) };
		KittyHigh Viewer = _KittyHigh::Langs["OTHER"];
		if (_KittyHigh::Langs.count(wf)) Viewer = _KittyHigh::Langs[wf];
		else if (_KittyHigh::Langs.count(ext)) Viewer = _KittyHigh::Langs[ext];
		if (!Viewer) { QCol->Error("Initiating Viewer failed"); return; }
		QCol->Doing("Type", Viewer->Language); _KittyHigh::PageBreak();
		_KittyHigh::WriteLine();
		Viewer->Show(src, slin);

	} catch (std::runtime_error ex) {
		QCol->Error(String(ex.what()) + "\n");
//#if DEBUG (works only in C#)
		//QCol->Magenta($"{ex.StackTrace}\n\n");
//#endif
	}
}

#define scs_case(want) else if (Lower(a)==want)
#define scs_case2(want1,want2) else if (Lower(a)==want1 || Lower(a)==want2)

int main(int _argc, char** _args) {

	// All this code is copied and adapted C# code.
	// No need to re-invent the wheel.
	std::vector<String> args; for (int i = 1; i < _argc; i++) args.push_back(_args[i]); // This to keep parameters on par with how C# works them out!


	// Header
	QCol->Red("Kitty "); QCol->Magenta("Coded by: Tricky\n");
	QCol->Yellow("(c) 2019-" + Right(__DATE__, 4) + " Jeroen P.Broks\n\n");
	// Init
	// Dirry.InitAltDrives(); // No longer needed. The volumes module does this by itself on its first call.

	QCol->Doing("Coded in", "C++");
	QCol->Doing("Platform", Platform(false));
	_KittyHigh::Init();
	KittyHigh_ALL();
	
	// new KittyHighGINI(); // GINI has officially been discontinued.
	

	if (args.size() == 0) {
		QCol->Green("Kitty is a simple program which will help you view source files in syntax highlight\n");
		QCol->Magenta("Usage:\t");
		QCol->Yellow("Kitty ");
		QCol->Cyan("<switches> ");
		QCol->White("<files>");
		QCol->Green("[");
		QCol->Cyan("<switches> ");
		QCol->White("<files>");
		QCol->Green("..]");
		std::cout << "\n\n";
		QCol->Yellow("Please note that switches affect all files defined after it not those that come before it. This allows you to configure each file shown\n\n");
		QCol->Cyan("-ln              "); QCol->Yellow("Toggle line numbers on/off (default is on)\n");
		QCol->Cyan("-nolinenumbers   "); QCol->Yellow("Turn line numbers off\n");
		QCol->Cyan("-Showlinenumbers "); QCol->Yellow("Turn line numbers on\n");
		QCol->Cyan("-re              "); QCol->Yellow("Toggle searching by RegEx (this allows limited support for Wild Cards and more nice things)\n");
		QCol->Cyan("-p, -more        "); QCol->Yellow("Turn \"more\" mode on/off. (Read note below)\n");
		QCol->Cyan("-support         "); QCol->Yellow("Show a list of all supported file formats\n");
		/*
		QCol->Red("\n\nThe \"more\" mode!\n");
		QCol->Yellow("Does not entirely work the same as the 'more' utility, but has the same primary function!\n");
		QCol->Yellow("When the \"more\" bar appears you can hit space to show the next line, Enter/Return to show the entire next page and escape to turn the more mode off\n");
		QCol->White("\n\nKitty can be used as as CLI tool, but the integry has been made to be included in your own projects, and has been released under the terms of the zlib license\n\n");
		//*/
		return 0;
	}
	// Go for it
	QCol->Doing("Called from", CurrentDir());

	// ViewFile function to top. C# supports functions inside functions
	// C++ does not.

	auto aregex{ false };
	for (auto a : args) {
		//printf("%d -> %s\n", (int)args.size(),a.c_str());
		if (Prefixed(a, "-")) {
			//switch (a.ToLower()) {
			if (false) {} // dirty code, but C# allows casing with strings, and C++ does not, and I don't want to switch it all with 'else if' (well, somehow I still did, but who cares?)
			scs_case("-ln") slin = !slin;
			scs_case("-nolinenumbers") slin = false; 
			scs_case("-showlinenumbers") slin = true; 
			scs_case2("-p", "-more") _KittyHigh::BrkLines = !_KittyHigh::BrkLines; 
			scs_case("-re") aregex = !aregex; 
			scs_case("-support") {
				for (auto ext : _KittyHigh::Langs) {
					QCol->Cyan(Left(ext.first + "                    ", 20));
					QCol->Yellow(ext.second->Language + "\n");
				}				
			} else QCol->Error("Unknown switch: " + a); 
			//printf("Ben er nog!"); // debug
		} else if (aregex) {
			QCol->Error("RegEx searching is not yet supported.");
			//QCol->Doing("Searching for RegEx", a);
			//var rgxl = RegExTree.Tree(a);
			//foreach(string af in rgxl) ViewFile(af);
		} else {
			ViewFile(a);
		}
	}
	return 0;
	// TrickyDebug.AttachWait(); No longer needed
}