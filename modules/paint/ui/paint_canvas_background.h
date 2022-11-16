#ifndef PAINT_CANVAS_BACKGROUND_H
#define PAINT_CANVAS_BACKGROUND_H

/*
Copyright (c) 2019 Flairieve
Copyright (c) 2020-2022 cobrapitz
Copyright (c) 2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "scene/gui/texture_rect.h"

#include "core/object/reference.h"

class ShaderMaterial;
class Shader;
class Image;

class PaintCanvasBackground : public TextureRect {
	GDCLASS(PaintCanvasBackground, TextureRect);

public:
	float get_pixel_size() const;
	void set_pixel_size(const float val);

	PaintCanvasBackground();
	~PaintCanvasBackground();

protected:
	void _notification(int p_what);

	static void _bind_methods();

	float _pixel_size;

	Ref<ShaderMaterial> _material;
	Ref<Shader> _shader;
};

#endif