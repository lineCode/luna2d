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

#include "lunaandroidsharing.h"
#include "lunafiles.h"

using namespace luna2d;

LUNAAndroidSharing::LUNAAndroidSharing()
{
	jni::Env env;

	// Get ref to java wrapper class
	jclass localRef = env->FindClass("com/stepanp/luna2d/services/LunaSharing");
	javaSharing = reinterpret_cast<jclass>(env->NewGlobalRef(localRef));
	env->DeleteLocalRef(localRef);

	// Get java wrapper method ids
	javaText = env->GetStaticMethodID(javaSharing, "text", "(Ljava/lang/String;)V");
	javaImage = env->GetStaticMethodID(javaSharing, "image", "(Ljava/lang/String;Ljava/lang/String;)V");
}

// Share given text using system sharing dialog
void LUNAAndroidSharing::Text(const std::string& text)
{
	jni::Env()->CallStaticVoidMethod(javaSharing, javaText, jni::ToJString(text).j_str());
}

// Share given image witg given text using system sharing dialog
// Image should be located in "LUNAFileLocation::APP_FOLDER"
void LUNAAndroidSharing::Image(const std::string& filename, const std::string& text)
{
	std::string path = LUNAEngine::SharedFiles()->GetRootFolder(LUNAFileLocation::APP_FOLDER) + filename;
	jni::Env()->CallStaticVoidMethod(javaSharing, javaImage, jni::ToJString(path).j_str(), jni::ToJString(text).j_str());
}
