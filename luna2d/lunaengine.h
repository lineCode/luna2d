//-----------------------------------------------------------------------------
// luna2d engine
// Copyright 2014-2017 Stepan Prokofjev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#pragma once

#include "lunaplatform.h"
#include "lunaconstants.h"
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <memory>
#include <functional>
#include <type_traits>
#include <algorithm>
#include <chrono>

namespace luna2d{

class LuaScript;
class LUNAFiles;
class LUNALog;
class LUNAPlatformUtils;
class LUNAPrefs;
class LUNAAudio;

class LUNAAssets;
class LUNAGraphics;
class LUNAScenes;
class LUNASizes;
class LUNAEvents;
class LUNAStrings;
class LUNADebug;
class LUNAConfig;

class LUNAServices;

class LUNAEngine
{
private:
	LUNAEngine();
public:
	~LUNAEngine();

private:
	// Platform-specific subsystems
	LUNAFiles* files = nullptr;
	LUNALog* log = nullptr;
	LUNAPlatformUtils* platformUtils = nullptr;
	LUNAPrefs* prefs = nullptr;

	// Common subsystems
	LuaScript* lua = nullptr;
	LUNAAssets* assets = nullptr;
	LUNAGraphics* graphics = nullptr;
	LUNAAudio* audio = nullptr;
	LUNAScenes* scenes = nullptr;
	LUNASizes* sizes = nullptr;
	LUNAEvents* events = nullptr;
	LUNAStrings* strings = nullptr;

	LUNAServices* services = nullptr;

#ifdef LUNA_DEBUG
	LUNADebug* debug = nullptr;
#endif

	std::shared_ptr<LUNAConfig> config;
	bool initialized = false;
	bool enablePauseHandling = true;

public:
	// Assemble engine with platform-specific modules. Must be called before "Initialize" method
	void Assemble(LUNAFiles* files, LUNALog* log, LUNAPlatformUtils* platformUtils, LUNAPrefs* prefs, LUNAServices* services);
	void Initialize(int screenWidth, int screenHeight);
	void Run();
	void Deinitialize();
	std::shared_ptr<const LUNAConfig> GetConfig();
	std::string GetGameName(); // Get name of running game
	void RunEmbeddedScripts();
	bool IsInitialized();

	// Enable/disable handling OnPause/OnResume events
	void EnablePauseHandling(bool enable);

	void MainLoop();
	void OnPause();
	void OnResume();
	void OnTouchDown(float x, float y, int touchIndex);
	void OnTouchMoved(float x, float y, int touchIndex);
	void OnTouchUp(float x, float y, int touchIndex);

	static LUNAEngine* Shared(); // Get shared instance of engine
	inline static LUNAFiles* SharedFiles() { return Shared()->files; }
	inline static LUNALog* SharedLog() { return Shared()->log; }
	inline static LUNAPlatformUtils* SharedPlatformUtils() { return Shared()->platformUtils; }
	inline static LUNAPrefs* SharedPrefs() { return Shared()->prefs; }
	inline static LuaScript* SharedLua() { return Shared()->lua; }
	inline static LUNAAssets* SharedAssets() { return Shared()->assets; }
	inline static LUNAGraphics* SharedGraphics() { return Shared()->graphics; }
	inline static LUNAAudio* SharedAudio() { return Shared()->audio; }
	inline static LUNAScenes* SharedScenes() { return Shared()->scenes; }
	inline static LUNASizes* SharedSizes() { return Shared()->sizes; }
	inline static LUNAEvents* SharedEvents() { return Shared()->events; }
	inline static LUNAStrings* SharedStrings() { return Shared()->strings; }
	inline static LUNAServices* SharedServices() { return Shared()->services; }

#ifdef LUNA_DEBUG
	inline static LUNADebug* SharedDebug() { return Shared()->debug; }
#endif
};

}
