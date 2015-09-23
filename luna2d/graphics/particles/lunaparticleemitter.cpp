//-----------------------------------------------------------------------------
// luna2d engine
// Copyright 2014-2015 Stepan Prokofjev
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

#include "lunaparticleemitter.h"
#include "lunaassets.h"

using namespace luna2d;

LUNAParticleEmitter::LUNAParticleEmitter(const std::shared_ptr<LUNAParticleParams>& params) :
	params(params)
{
	LUNAAssets* assets = LUNAEngine::SharedAssets();

	for(const auto& path : params->textures)
	{
		auto region = assets->GetAssetByPath<LUNATextureRegion>(path);
		if(!region.expired())
		{
			sourceSprites.push_back(std::make_shared<LUNASprite>(region));
			continue;
		}

		auto texture = assets->GetAssetByPath<LUNATexture>(path);
		if(!texture.expired())
		{
			sourceSprites.push_back(std::make_shared<LUNASprite>(texture));
			continue;
		}

		LUNA_LOGE("Invalid texture or texture region \"%s\"", path.c_str());
	}

	particles.push_back(std::make_shared<LUNAParticle>(sourceSprites[0], params));
}

glm::vec2 LUNAParticleEmitter::GetPos()
{
	return pos;
}

void LUNAParticleEmitter::SetPos(const glm::vec2& pos)
{
	this->pos = pos + params->emitterPos;
}

void LUNAParticleEmitter::Update(float dt)
{
	for(auto& particle : particles) particle->Update(dt);
}

void LUNAParticleEmitter::Render()
{
	for(auto& particle : particles) particle->Render();
}