#ifndef NAVIGATION_MESH_H
#define NAVIGATION_MESH_H

/*************************************************************************/
/*  navigation_mesh.h                                                    */
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

#include "scene/resources/mesh/mesh.h"

class Mesh;
class NavigationMeshGenerator;

class NavigationMesh : public Resource {
	GDCLASS(NavigationMesh, Resource);

	friend class NavigationMeshGenerator;

public:
	enum SamplePartitionType {
		SAMPLE_PARTITION_WATERSHED = 0,
		SAMPLE_PARTITION_MONOTONE,
		SAMPLE_PARTITION_LAYERS,
		SAMPLE_PARTITION_MAX
	};

	enum ParsedGeometryType {
		PARSED_GEOMETRY_MESH_INSTANCES = 0,
		PARSED_GEOMETRY_STATIC_COLLIDERS,
		PARSED_GEOMETRY_BOTH,
		PARSED_GEOMETRY_MAX
	};

	enum SourceGeometryMode {
		SOURCE_GEOMETRY_ROOT_NODE_CHILDREN = 0,
		SOURCE_GEOMETRY_GROUPS_WITH_CHILDREN,
		SOURCE_GEOMETRY_GROUPS_EXPLICIT,
		SOURCE_GEOMETRY_MAX
	};

public:
	// Recast settings
	void set_sample_partition_type(SamplePartitionType p_value);
	SamplePartitionType get_sample_partition_type() const;

	void set_parsed_geometry_type(ParsedGeometryType p_value);
	ParsedGeometryType get_parsed_geometry_type() const;

	void set_collision_mask(uint32_t p_mask);
	uint32_t get_collision_mask() const;

	void set_collision_mask_bit(int p_bit, bool p_value);
	bool get_collision_mask_bit(int p_bit) const;

	void set_source_geometry_mode(SourceGeometryMode p_geometry_mode);
	SourceGeometryMode get_source_geometry_mode() const;

	void set_source_group_name(StringName p_group_name);
	StringName get_source_group_name() const;

	void set_cell_size(float p_value);
	float get_cell_size() const;

	void set_cell_height(float p_value);
	float get_cell_height() const;

	void set_agent_height(float p_value);
	float get_agent_height() const;

	void set_agent_radius(float p_value);
	float get_agent_radius();

	void set_agent_max_climb(float p_value);
	float get_agent_max_climb() const;

	void set_agent_max_slope(float p_value);
	float get_agent_max_slope() const;

	void set_region_min_size(float p_value);
	float get_region_min_size() const;

	void set_region_merge_size(float p_value);
	float get_region_merge_size() const;

	void set_edge_max_length(float p_value);
	float get_edge_max_length() const;

	void set_edge_max_error(float p_value);
	float get_edge_max_error() const;

	void set_vertices_per_polygon(float p_value);
	float get_vertices_per_polygon() const;

	void set_detail_sample_distance(float p_value);
	float get_detail_sample_distance() const;

	void set_detail_sample_max_error(float p_value);
	float get_detail_sample_max_error() const;

	void set_filter_low_hanging_obstacles(bool p_value);
	bool get_filter_low_hanging_obstacles() const;

	void set_filter_ledge_spans(bool p_value);
	bool get_filter_ledge_spans() const;

	void set_filter_walkable_low_height_spans(bool p_value);
	bool get_filter_walkable_low_height_spans() const;

	void set_filter_baking_aabb(const AABB &p_aabb);
	AABB get_filter_baking_aabb() const;

	void set_filter_baking_aabb_offset(const Vector3 &p_aabb_offset);
	Vector3 get_filter_baking_aabb_offset() const;

	void create_from_mesh(const Ref<Mesh> &p_mesh);

	void set_vertices(const PoolVector<Vector3> &p_vertices);
	PoolVector<Vector3> get_vertices() const;

	void add_polygon(const Vector<int> &p_polygon);
	int get_polygon_count() const;
	Vector<int> get_polygon(int p_idx);
	void clear_polygons();

	void clear();
	void commit_changes();

	void set_polygons(const Vector<Vector<int>> &p_polygons);
	const Vector<Vector<int>> &get_polygons() const;

	void _set_polygons(const Array &p_array);
	Array _get_polygons() const;

	RID get_rid() const;

#ifdef DEBUG_ENABLED
	Ref<ArrayMesh> get_debug_mesh();
#endif

	NavigationMesh();
	~NavigationMesh();

protected:
	static void _bind_methods();
	virtual void _validate_property(PropertyInfo &property) const;

#ifndef DISABLE_DEPRECATED
	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
#endif // DISABLE_DEPRECATED

	float cell_size;
	float cell_height;
	float agent_height;
	float agent_radius;
	float agent_max_climb;
	float agent_max_slope;
	float region_min_size;
	float region_merge_size;
	float edge_max_length;
	float edge_max_error;
	float vertices_per_polygon;
	float detail_sample_distance;
	float detail_sample_max_error;

	SamplePartitionType partition_type;
	ParsedGeometryType parsed_geometry_type;
	uint32_t collision_mask;

	SourceGeometryMode source_geometry_mode;
	StringName source_group_name;

	bool filter_low_hanging_obstacles;
	bool filter_ledge_spans;
	bool filter_walkable_low_height_spans;
	AABB filter_baking_aabb;
	Vector3 filter_baking_aabb_offset;

private:
	RID navigation_mesh_rid;

	PoolVector<Vector3> vertices;

	Vector<Vector<int>> polygons;

	Ref<ArrayMesh> debug_mesh;

	bool navigation_mesh_dirty;
};

VARIANT_ENUM_CAST(NavigationMesh::SamplePartitionType);
VARIANT_ENUM_CAST(NavigationMesh::ParsedGeometryType);
VARIANT_ENUM_CAST(NavigationMesh::SourceGeometryMode);

#endif // NAVIGATION_MESH_H
