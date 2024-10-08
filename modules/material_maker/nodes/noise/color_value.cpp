/*************************************************************************/
/*  color_value.cpp                                                      */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "color_value.h"

#include "../../algos/mm_algos.h"
#include "../../editor/mm_graph_node.h"
#include "../mm_material.h"

Ref<MMNodeUniversalProperty> MMColorValue::get_image() {
	return image;
}

void MMColorValue::set_image(const Ref<MMNodeUniversalProperty> &val) {
	image = val;
}

Vector2 MMColorValue::get_scale() {
	return scale;
}

void MMColorValue::set_scale(const Vector2 &val) {
	scale = val;
	set_dirty(true);
}

int MMColorValue::get_iterations() const {
	return iterations;
}

void MMColorValue::set_iterations(const int val) {
	iterations = val;
	set_dirty(true);
}

float MMColorValue::get_persistence() const {
	return persistence;
}

void MMColorValue::set_persistence(const float val) {
	persistence = val;
	set_dirty(true);
}

void MMColorValue::_init_properties() {
	if (!image.is_valid()) {
		image.instance();
		image->set_default_type(MMNodeUniversalProperty::DEFAULT_TYPE_IMAGE);
	}

	image->set_output_slot_type(MMNodeUniversalProperty::SLOT_TYPE_IMAGE);
	register_output_property(image);
}

void MMColorValue::_register_methods(MMGraphNode *mm_graph_node) {
	mm_graph_node->add_slot_texture_universal(image);
	//, Vector2(1, 10));
	mm_graph_node->add_slot_vector2("get_scale", "set_scale", "Scale");
	//, Vector2(0, 1));
	mm_graph_node->add_slot_int("get_iterations", "set_iterations", "Iterations");
	//, Vector2(0, 1));
	mm_graph_node->add_slot_float("get_persistence", "set_persistence", "Persistence", 0.01);
}

Color MMColorValue::_get_value_for(const Vector2 &uv, const int pseed) {
	float ps = 1.0 / float(pseed);
	//perlin_color($(uv), vec2($(scale_x), $(scale_y)), int($(iterations)), $(persistence), $(seed));
	return MMAlgos::perlin_colorc(uv, scale, iterations, persistence, ps);
}

void MMColorValue::_render(const Ref<MMMaterial> &material) {
	Ref<Image> img = render_image(material);
	image->set_value(img);
}

MMColorValue::MMColorValue() {
	scale = Vector2(4, 4);
	iterations = 3;
	persistence = 0.5;
}

MMColorValue::~MMColorValue() {
}

void MMColorValue::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_image"), &MMColorValue::get_image);
	ClassDB::bind_method(D_METHOD("set_image", "value"), &MMColorValue::set_image);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "image", PROPERTY_HINT_RESOURCE_TYPE, "MMNodeUniversalProperty"), "set_image", "get_image");

	ClassDB::bind_method(D_METHOD("get_scale"), &MMColorValue::get_scale);
	ClassDB::bind_method(D_METHOD("set_scale", "value"), &MMColorValue::set_scale);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "scale"), "set_scale", "get_scale");

	ClassDB::bind_method(D_METHOD("get_iterations"), &MMColorValue::get_iterations);
	ClassDB::bind_method(D_METHOD("set_iterations", "value"), &MMColorValue::set_iterations);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "iterations"), "set_iterations", "get_iterations");

	ClassDB::bind_method(D_METHOD("get_persistence"), &MMColorValue::get_persistence);
	ClassDB::bind_method(D_METHOD("set_persistence", "value"), &MMColorValue::set_persistence);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "persistence"), "set_persistence", "get_persistence");
}
