#ifndef PROCEDURAL_TREE_3D_MESH_H
#define PROCEDURAL_TREE_3D_MESH_H

#include "scene/resources/mesh/mesh.h"

class ProceduralTreeMesh : public Mesh {
	GDCLASS(ProceduralTreeMesh, Mesh);

public:
	// General
	int get_seed() const;
	void set_seed(const int p_value);

	int get_branch_segments() const;
	void set_branch_segments(const int p_value);

	int get_branch_levels() const;
	void set_branch_levels(const int p_value);

	int get_trunk_forks() const;
	void set_trunk_forks(const int p_value);

	float get_texture_v_multiplier() const;
	void set_texture_v_multiplier(const float p_value);

	float get_twig_scale() const;
	void set_twig_scale(const float p_value);

	// Branching
	float branching_get_initial_length() const;
	void branching_set_initial_length(const float p_value);

	float branching_get_length_falloff_rate() const;
	void branching_set_length_falloff_rate(const float p_value);

	float branching_get_length_falloff_power() const;
	void branching_set_length_falloff_power(const float p_value);

	float branching_get_max_clumping() const;
	void branching_set_max_clumping(const float p_value);

	float branching_get_min_clumping() const;
	void branching_set_min_clumping(const float p_value);

	float branching_get_symmetry() const;
	void branching_set_symmetry(const float p_value);

	float branching_get_droop() const;
	void branching_set_droop(const float p_value);

	float branching_get_growth() const;
	void branching_set_growth(const float p_value);

	float branching_get_sweep() const;
	void branching_set_sweep(const float p_value);

	// Trunk
	float trunk_get_radius() const;
	void trunk_set_radius(const float p_value);

	float trunk_get_radius_falloff() const;
	void trunk_set_radius_falloff(const float p_value);

	float trunk_get_climb_rate() const;
	void trunk_set_climb_rate(const float p_value);

	float trunk_get_kink() const;
	void trunk_set_kink(const float p_value);

	float trunk_get_taper_rate() const;
	void trunk_set_taper_rate(const float p_value);

	float trunk_get_twists() const;
	void trunk_set_twists(const float p_value);

	float trunk_get_length() const;
	void trunk_set_length(const float p_value);

public:
	enum TreeSurfaces {
		TREE_SURFACE_TWIG = 0,
		TREE_SURFACE_TRUNK = 1,
		TREE_SURFACE_COUNT,
	};

	virtual int get_surface_count() const;
	virtual int surface_get_array_len(int p_idx) const;
	virtual int surface_get_array_index_len(int p_idx) const;
	virtual Array surface_get_arrays(int p_surface) const;
	virtual Array surface_get_blend_shape_arrays(int p_surface) const;
	virtual uint32_t surface_get_format(int p_idx) const;
	virtual Mesh::PrimitiveType surface_get_primitive_type(int p_idx) const;
	virtual void surface_set_material(int p_idx, const Ref<Material> &p_material);
	virtual Ref<Material> surface_get_material(int p_idx) const;
	virtual int get_blend_shape_count() const;
	virtual StringName get_blend_shape_name(int p_index) const;
	virtual void set_blend_shape_name(int p_index, const StringName &p_name);
	virtual AABB get_aabb() const;
	virtual RID get_rid() const;

	void set_twig_material(const Ref<Material> &p_material);
	Ref<Material> get_twig_material() const;

	void set_trunk_material(const Ref<Material> &p_material);
	Ref<Material> get_trunk_material() const;

	Array get_mesh_arrays() const;

	void set_custom_aabb(const AABB &p_custom);
	AABB get_custom_aabb() const;

	ProceduralTreeMesh();
	~ProceduralTreeMesh();

protected:
	static void _bind_methods();

	void _request_update();

private:
	// General
	int _seed; //mProperties.mSeed
	int _branch_segments; //mProperties.mSegments
	int _branch_levels; //mProperties.mLevels
	int _trunk_forks; //mProperties.mTreeSteps
	float _texture_v_multiplier; //mProperties.mVMultiplier
	float _twig_scale; //mProperties.mTwigScale

	// Branching
	float _branching_initial_length; //mProperties.mInitialBranchLength
	float _branching_length_falloff_rate; //mProperties.mLengthFalloffFactor
	float _branching_length_falloff_power; //mProperties.mLengthFalloffPower
	float _branching_max_clumping; //mProperties.mClumpMax
	float _branching_min_clumping; //mProperties.mClumpMin
	float _branching_symmetry; //mProperties.mBranchFactor
	float _branching_droop; //mProperties.mDropAmount
	float _branching_growth; //mProperties.mGrowAmount
	float _branching_sweep; //mProperties.mSweepAmount

	// Trunk
	float _trunk_radius; //mProperties.mMaxRadius
	float _trunk_radius_falloff; //mProperties.mRadiusFalloffRate
	float _trunk_climb_rate; //mProperties.mClimbRate
	float _trunk_kink; //mProperties.mTrunkKink
	float _trunk_taper_rate; //mProperties.mTaperRate
	float _trunk_twists; //mProperties.mTwistRate
	float _trunk_length; //mProperties.mTrunkLength

private:
	RID mesh;

	struct TreeSurface {
		Ref<Material> material;
	};

	TreeSurface _surfaces[TREE_SURFACE_COUNT];

	mutable AABB aabb;
	AABB custom_aabb;

	mutable bool pending_request;
	void _update() const;
};

VARIANT_ENUM_CAST(ProceduralTreeMesh::TreeSurfaces);

#endif